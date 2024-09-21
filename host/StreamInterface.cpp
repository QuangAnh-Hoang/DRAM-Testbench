#include "StreamInterface.h"

#include <signal.h>


StreamInterface*
StreamInterface::m_pInstance = NULL;

StreamInterface::StreamInterface() {
	std::string binaryFile = "./krnl.xclbin";
	int device_index = 0;

	// Open the FPGA device
	std::cout << "Open the device " << device_index << std::endl;
	auto device = xrt::device(device_index);
	
	// Load the .xclbin file onto the FPGA
	std::cout << "Load the xclbin " << binaryFile << std::endl;
	auto uuid = device.load_xclbin("./krnl.xclbin");

	// Create the kernel object
	m_kernel = xrt::kernel(device, uuid, "krnl", xrt::kernel::cu_access_mode::exclusive);
	std::cout << "Initialized kernel -- " << m_kernel.get_name() << std::endl;

	for (auto ip : m_kernel.get_xclbin().get_ips()) {
		std::cout << "Kernel IPs -- " << ip.get_name() << std::endl;
		for (auto arg : ip.get_args()) {
			std::cout << "\t IP argument -- " << arg.get_name() << std::endl;
		}
	}

	// Allocate input and output buffers
	// Match kernel arguments to RTL kernel
	for ( int i = 0; i < XRT_QUEUE_CNT; i++ ) {
		m_instBufDev[i] = xrt::bo(device, BUFFER_BYTES, m_kernel.group_id(3));
		m_dataInBufDev[i] = xrt::bo(device, BUFFER_BYTES, m_kernel.group_id(4));
		m_dataOutBufDev[i] = xrt::bo(device, BUFFER_BYTES, m_kernel.group_id(5));

		m_instBufHost[i] = m_instBufDev[i].map();
		m_dataInBufHost[i] = m_dataInBufDev[i].map();
		m_dataOutBufHost[i] = m_dataOutBufDev[i].map();

		std::fill((uint8_t*)m_instBufHost[i], (uint8_t*)m_instBufHost[i] + (BUFFER_BYTES), 0);
		std::fill((uint8_t*)m_dataInBufHost[i], (uint8_t*)m_dataInBufHost[i] + (BUFFER_BYTES), 0);
		std::fill((uint8_t*)m_dataOutBufHost[i],(uint8_t*)m_dataOutBufHost[i] + (BUFFER_BYTES), 0);
	}
	for ( int i = 0; i < XRT_QUEUE_CNT; i++ ) {
		m_instBufHost[i] = malloc(BUFFER_BYTES);
		m_dataInBufHost[i] = malloc(BUFFER_BYTES);
		m_dataOutBufHost[i] = malloc(BUFFER_BYTES);
	}

	m_curInQueue = 0;
	m_curOutQueue = 0;
	for ( int i = 0; i < XRT_QUEUE_CNT; i++ ) {
		m_outQueueState[i] = BUF_INIT;
	}

	printf( "Initialized kernel stream access\n" ); fflush(stdout);
}

// FIXME send both memory instructions and data to be written
int32_t
StreamInterface::send(void* inst, void* data, int32_t data_size_in_bytes) {
	if ( (m_curDataInByteOff + data_size_in_bytes > BUFFER_BYTES) ||
		 (m_curInstByteOff + sizeof(uint32_t) > BUFFER_BYTES) ) 
	{
		bool ret = this->flush();
		if ( !ret ) return -1; // flush failed (probably because there was no receive buffer space)
	}

	memcpy(((uint8_t*) m_instBufHost[m_curInQueue]) + m_curInstByteOff, inst, sizeof(uint32_t));
	if (std::memcmp(((uint8_t*) m_instBufHost[m_curInQueue]) + m_curInstByteOff, inst, sizeof(uint32_t)))
			printf("\tWARNING: SENDING DATA MISMATCH\n");
	m_curInstByteOff += sizeof(uint32_t);
	m_totalInst[m_curInQueue] += 1;

	uint32_t readInstBase = RD_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH);
	uint32_t writeInstBase = WR_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH);

	uint32_t check_readInst = ((uint32_t*) inst)[0] & readInstBase;
	uint32_t check_writeInst = ((uint32_t*) inst)[0] & writeInstBase;

	if (!memcmp(&readInstBase, &check_readInst, sizeof(uint32_t))) {
		m_totalReadInst[m_curInQueue] += BURST_LENGTH;
		m_bytesToRead[m_curInQueue] += BURST_LENGTH * sizeof(uint16_t);
	} else if (!memcmp(&writeInstBase, &check_writeInst, sizeof(uint32_t))) {
		m_totalWriteInst[m_curInQueue] += BURST_LENGTH;
	}

	if (data_size_in_bytes > 0) {
		memcpy(((uint8_t*) m_dataInBufHost[m_curInQueue]) + m_curDataInByteOff, data, data_size_in_bytes); //FIXME no safety!
		if (std::memcmp(((uint8_t*) m_dataInBufHost[m_curInQueue]) + m_curDataInByteOff, data, data_size_in_bytes))
			printf("\tWARNING: SENDING DATA MISMATCH\n");
		m_curDataInByteOff += data_size_in_bytes;
		return data_size_in_bytes;
	}
	return sizeof(uint16_t);
}

bool 
StreamInterface::flush() {

	BufferState bufstate = m_outQueueState[m_curInQueue];
	if ( bufstate == BUF_INFLIGHT ) {
		this->m_writeBackEventQueue[m_curInQueue].wait();
		bufstate = BUF_USEREADY;
		m_outQueueState[m_curInQueue] = bufstate;
	}
	// user needs to read out buffer first
	if ( !(bufstate == BUF_INIT || bufstate == BUF_USEDONE) ) return false;

	xrt::run& grun = m_kernelRun[m_curInQueue];

	grun = xrt::run(m_kernel);

	void* bh_inst = m_instBufHost[m_curInQueue];
	void* bh_dataIn = m_dataInBufHost[m_curInQueue];
	void* bh_dataOut = m_dataOutBufHost[m_curInQueue];

	xrt::bo b_inst = m_instBufDev[m_curInQueue];
	xrt::bo b_dataIn = m_dataInBufDev[m_curInQueue];
	xrt::bo b_dataOut = m_dataOutBufDev[m_curInQueue];

	grun.set_arg(0, m_totalInst[m_curInQueue]); // number of memory commands
	grun.set_arg(1, m_totalWriteInst[m_curInQueue]); // number of write commands
	grun.set_arg(2, m_totalReadInst[m_curInQueue]); // number of read commands
	
	grun.set_arg(3, m_instBufDev[m_curInQueue]);
	grun.set_arg(4, m_dataInBufDev[m_curInQueue]);
	grun.set_arg(5, m_dataOutBufDev[m_curInQueue]);

	printf( "Starting kernel @ %d/2 in queue: %s(%d, %d, %d, %x, %x, %x)\n", \
		m_curInQueue,
		m_kernel.get_name().c_str(),
		m_totalInst[m_curInQueue],
		m_totalWriteInst[m_curInQueue],
		m_totalReadInst[m_curInQueue],

		m_instBufDev[m_curInQueue],
		m_dataInBufDev[m_curInQueue],
		m_dataOutBufDev[m_curInQueue]
	);
	fflush(stdout);

	// m_instBufDev[m_curInQueue].write(m_instBufHost[m_curInQueue]);
	// m_instBufDev[m_curInQueue].sync(XCL_BO_SYNC_BO_TO_DEVICE);

	// m_dataInBufDev[m_curInQueue].write(m_dataInBufHost[m_curInQueue]);
	// m_dataInBufDev[m_curInQueue].sync(XCL_BO_SYNC_BO_TO_DEVICE);

	int inst_send_bytes = m_curInstByteOff;
	int dataIn_send_bytes = m_curDataInByteOff;
	int dataOut_send_bytes = m_bytesToRead[m_curInQueue];

	m_asyncQueue[m_curInQueue].enqueue([ &b_inst, &bh_inst, inst_send_bytes ] {
		b_inst.write(bh_inst);
		b_inst.sync(XCL_BO_SYNC_BO_TO_DEVICE, inst_send_bytes, 0); 
	});
	m_asyncQueue[m_curInQueue].enqueue([ &b_dataIn, &bh_dataIn, dataIn_send_bytes ] {
		b_dataIn.write(bh_dataIn);
		b_dataIn.sync(XCL_BO_SYNC_BO_TO_DEVICE, dataIn_send_bytes, 0); 
	});

	// grun.start();
	// grun.wait();

	printf( "Starting kernel\n" ); fflush(stdout);

	xrt::queue::event start_kernel = m_asyncQueue[m_curInQueue].enqueue([ &grun ] {grun.start(); grun.wait(); });
	start_kernel.wait();

	// m_dataOutBufDev[m_curInQueue].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
	// m_dataOutBufDev[m_curInQueue].read(m_dataOutBufHost[m_curInQueue]);

	// m_asyncQueue[m_curInQueue].enqueue([ &b_inst, &bh_inst, inst_send_bytes ] {
	// 	b_inst.sync(XCL_BO_SYNC_BO_FROM_DEVICE, inst_send_bytes, 0); 
	// 	b_inst.read(bh_inst);
	// });
	// m_asyncQueue[m_curInQueue].enqueue([ &b_dataIn, &bh_dataIn, dataIn_send_bytes ] {
	// 	b_dataIn.sync(XCL_BO_SYNC_BO_FROM_DEVICE, dataIn_send_bytes, 0); 
	// 	b_dataIn.read(bh_dataIn);
	// });

	printf( "Enqueuing read of %d bytes from kernel @ %x to host @ %x\n", dataOut_send_bytes, b_dataOut, bh_dataOut ); fflush(stdout);

	this->m_writeBackEventQueue[m_curInQueue] = m_asyncQueue[m_curInQueue].enqueue([ &b_dataOut, &bh_dataOut, dataOut_send_bytes ] {
		b_dataOut.sync(XCL_BO_SYNC_BO_FROM_DEVICE, dataOut_send_bytes, 0); 
		b_dataOut.read(bh_dataOut);
	});

	// Asynchronously deploy and run kernels (include syncing input + output buffers)
	//
	// xrt::queue::event sync_send = m_asyncQueue[m_curInQueue].enqueue([&bh, src_ptr, send_bytes] { 
	// 	// bh.sync(XCL_BO_SYNC_BO_TO_DEVICE, send_bytes, 0); 
	// 	// bh.write(src_ptr, send_bytes, 0);
	// });
	// xrt::queue::event run_kernel = m_asyncQueue[m_curInQueue].enqueue([&grun] {
	// 	grun.start();
	// 	grun.wait();
	// });

	// //FIXME need to sync full buffer every time?
	// // maybe only read back 8KB or so first, and see what's there
	// xrt::bo bd = m_outBufDev[m_curInQueue];
	// //int recv_off = m_curInQueue<<BUFFER_BYTES_LG;
	// this->m_writeBackEventQueue[m_curInQueue] = m_asyncQueue[m_curInQueue].enqueue([&bd] { bd.sync(XCL_BO_SYNC_BO_FROM_DEVICE); });
	// printf( "Sent buffer\n" ); fflush(stdout);

	m_writeBackEventQueue[m_curInQueue].wait();
	
	m_outQueueState[m_curInQueue] = BUF_INFLIGHT;

	m_curInQueue = (m_curInQueue + 1)%XRT_QUEUE_CNT;
	m_curInstByteOff = 0;
	m_curDataInByteOff = 0;

	return true;
}
int32_t
StreamInterface::recv(void* ptr, int32_t bytes) {
	BufferState cstate = m_outQueueState[m_curOutQueue];
	
	// if USEREADY and used up buffer space, need to initialize again
	if ( cstate  == BUF_USEREADY && ( m_curDataOutByteOff + bytes > BUFFER_BYTES )) {
		cstate = BUF_USEDONE;
		m_outQueueState[m_curOutQueue] = cstate;

		m_curOutQueue ++;
		if ( m_curOutQueue >= XRT_QUEUE_CNT ) m_curOutQueue = 0;
	}

	// if INFLIGHT, try wait
	if ( m_outQueueState[m_curOutQueue] == BUF_INFLIGHT ) {
		this->m_writeBackEventQueue[m_curOutQueue].wait();
		m_outQueueState[m_curOutQueue] = BUF_USEREADY;
	}
	if ( m_outQueueState[m_curOutQueue] != BUF_USEREADY ) return -1;

	printf( "[%d/2] Receiving %d bytes from kernel @ (%x + %x)\n", m_curOutQueue, bytes, (m_dataOutBufHost[m_curOutQueue]), m_curDataOutByteOff ); fflush(stdout);

	memcpy(ptr, (uint8_t*)(m_dataOutBufHost[m_curOutQueue]) + m_curDataOutByteOff, bytes);
	m_curDataOutByteOff += bytes;
	m_bytesToRead[m_curOutQueue] -= bytes;

	return bytes;
}
bool 
StreamInterface::inflight() {
	for ( int i = 0; i < XRT_QUEUE_CNT; i++ ) {
		BufferState bufstate = m_outQueueState[i];
		if ( !(bufstate == BUF_INIT || bufstate == BUF_USEDONE) ) return true;
	}
	return false;
}
