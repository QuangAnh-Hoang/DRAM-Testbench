import DRAM_Kernel :: *;
import DRAM_Bank :: *;

import FIFOF::*;
import FIFO::*;
import Vector::*;

typedef 512 HBM_DATAWIDTH;
typedef 32 DRAM_INST_WIDTH;
typedef 16 DRAM_DATA_WIDTH;

typedef TDiv#(HBM_DATAWIDTH, DRAM_INST_WIDTH) INST_PER_MEM_REQ;
typedef TDiv#(HBM_DATAWIDTH, DRAM_DATA_WIDTH) WORD_PER_MEM_REQ;

typedef 64 MEM_PORT_ADDR_WIDTH;
typedef 32 MEM_PORT_DATA_WIDTH;

typedef 3 MemPortCnt;

interface MemPortIfc;
	method ActionValue#(MemPortReq) readReq;
	method ActionValue#(MemPortReq) writeReq;
	method ActionValue#(Bit#(HBM_DATAWIDTH)) writeWord;
	method Action readWord(Bit#(HBM_DATAWIDTH) word);
endinterface

interface KernelMainIfc;
    method Action start(Bit#(32) totalInst, Bit#(32) wordsToRead, Bit#(32) wordsToWrite);
	method Bool started;
    method Bool done;
    interface Vector#(MemPortCnt, MemPortIfc) mem;
endinterface

typedef struct {
	Bit#(MEM_PORT_ADDR_WIDTH) addr;
	Bit#(MEM_PORT_DATA_WIDTH) bytes;
} MemPortReq deriving (Eq,Bits);

module mkKernelMain(KernelMainIfc)
	provisos(Add#(DRAM_DATA_WIDTH, 0, WORD_SIZE));

    Vector#(MemPortCnt, FIFO#(MemPortReq)) readReqQs <- replicateM(mkFIFO);
	Vector#(MemPortCnt, FIFO#(MemPortReq)) writeReqQs <- replicateM(mkFIFO);
	Vector#(MemPortCnt, FIFO#(Bit#(HBM_DATAWIDTH))) writeWordQs <- replicateM(mkFIFO);
	Vector#(MemPortCnt, FIFO#(Bit#(HBM_DATAWIDTH))) readWordQs <- replicateM(mkFIFO);

	DRAM_Kernel_Ifc mem_kernel <- mkDRAM_Kernel();

	Reg#(Bit#(32)) cycleCounter <- mkReg(0);
	Reg#(Bool) kernelStarted <- mkReg(False);
	Reg#(Bit#(32)) remainInst <- mkReg(0);
	Reg#(Bit#(32)) readCounter <- mkReg(0);
	Reg#(Bit#(32)) writeCounter <- mkReg(0);

	rule incCycle (kernelStarted);
		cycleCounter <= cycleCounter + 1;
	endrule

	Reg#(Bool) kernelDone <- mkReg(False);

//////////////////////////////////////////////////////////////////////////
// POV: IP-central, sending read requests to HBM (not BRAM)

	//////////////////////////////////////////////////////////////////////////
	// Read memory instructions from HBM
    Reg#(Bit#(32)) readReqInstOff <- mkReg(0);
	Reg#(Bit#(32)) readInstCouter <- mkReg(0);

    rule sendReadReqInst ( kernelStarted && remainInst > 0 );
		$display("\t\t[%d] sendReadReqInst : remainInst = %d", cycleCounter, remainInst);
		let inst_per_mem_req = fromInteger(valueof(INST_PER_MEM_REQ));
		let bytes_per_mem_req = fromInteger(valueof(HBM_DATAWIDTH)) >> 3;

		if ( remainInst > inst_per_mem_req ) begin
			remainInst <= remainInst - inst_per_mem_req;
			readReqQs[0].enq(MemPortReq{addr:zeroExtend(readReqInstOff), bytes:bytes_per_mem_req});
			readReqInstOff <= readReqInstOff + bytes_per_mem_req;
			readInstCouter <= inst_per_mem_req;
		end else begin
			let b = remainInst * 4;
			readReqQs[0].enq(MemPortReq{addr:zeroExtend(readReqInstOff), bytes:b});
			readReqInstOff <= readReqInstOff + b;
			remainInst <= 0;
			readInstCouter <= remainInst;
		end
	endrule

	Reg#(Bit#(32)) inst_serializerCouter <- mkReg(0);
	Reg#(Bit#(HBM_DATAWIDTH)) inst_serializerBuff <- mkReg(0);
	FIFOF#(Bit#(DRAM_INST_WIDTH)) inst_compactedQ <- mkFIFOF();

	rule recvReadRespInst ( kernelStarted );
		$display("\t\t[%d] recvReadRespInst : inst_serializerCouter = %d", cycleCounter, inst_serializerCouter);

		if ( inst_serializerCouter == 0 ) begin
			let d = readWordQs[0].first;
			readWordQs[0].deq;
			inst_compactedQ.enq(truncate(d));
			inst_serializerBuff <= (d >> valueof(DRAM_INST_WIDTH));
			inst_serializerCouter <= readInstCouter - 1;
		end else begin
			inst_serializerCouter <= inst_serializerCouter - 1;
			inst_serializerBuff <= (inst_serializerBuff >> valueof(DRAM_INST_WIDTH));
			inst_compactedQ.enq(truncate(inst_serializerBuff));
		end
	endrule

	rule enqueueInst ( kernelStarted );
		if (inst_compactedQ.notEmpty()) begin
			let d = inst_compactedQ.first;
			inst_compactedQ.deq;
			mem_kernel.put_mem_control(truncate(d));

			$display("\t\t[%d] enqueueInst : mem_kernel.put_mem_control(truncate(%x))", cycleCounter, d);
		end
	endrule

	//////////////////////////////////////////////////////////////////////////
	// Read data to be written from HBM
    Reg#(Bit#(32)) readReqDataInOff <- mkReg(0);
	Reg#(Bit#(32)) readDataCouter <- mkReg(0);

    rule sendReadReqDataIn ( kernelStarted && readCounter > 0 );
		$display("\t\t[%d] sendReadReqDataIn : readCounter = %d", cycleCounter, readCounter);
		let word_per_mem_req = fromInteger(valueof(WORD_PER_MEM_REQ));
		let bytes_per_mem_req = fromInteger(valueof(HBM_DATAWIDTH)) >> 3;

		if ( readCounter > word_per_mem_req ) begin
			readCounter <= readCounter - word_per_mem_req;
			readReqQs[1].enq(MemPortReq{addr:zeroExtend(readReqDataInOff), bytes:bytes_per_mem_req});
			readReqDataInOff <= readReqDataInOff + bytes_per_mem_req;
			readDataCouter <= word_per_mem_req - 1;
		end else begin 
			let b = readCounter * 16;
			readReqQs[1].enq(MemPortReq{addr:zeroExtend(readReqDataInOff), bytes:b});
			readReqDataInOff <= readReqDataInOff + b;
			readCounter <= 0;
			readDataCouter <= readCounter;
		end
	endrule

	Reg#(Bit#(32)) data_serializerCouter <- mkReg(0);
	Reg#(Bit#(HBM_DATAWIDTH)) data_serializerBuff <- mkReg(0);
	FIFOF#(Bit#(DRAM_INST_WIDTH)) data_compactedQ <- mkFIFOF();

	rule recvReadRespDataIn ( kernelStarted );
		$display("\t\t[%d] recvReadRespDataIn : data_serializerCouter = %d", cycleCounter, data_serializerCouter);

		if ( data_serializerCouter == 0 ) begin
			let d = readWordQs[1].first;
			readWordQs[1].deq;
			data_compactedQ.enq(truncate(d));
			data_serializerBuff <= (d >> valueof(DRAM_DATA_WIDTH));
			data_serializerCouter <= readDataCouter;
		end else begin
			data_serializerCouter <= data_serializerCouter - 1;
			data_serializerBuff <= (data_serializerBuff >> valueof(DRAM_DATA_WIDTH));
			data_compactedQ.enq(truncate(data_serializerBuff));
		end
	endrule

	rule enqueueDataIn ( kernelStarted );
		if (data_compactedQ.notEmpty()) begin
			let d = data_compactedQ.first;
			data_compactedQ.deq;
			mem_kernel.put_mem_data(truncate(d));

			$display("\t\t[%d] enqueueDataIn : mem_kernel.put_mem_data(truncate(%x))", cycleCounter, d);
		end
	endrule

	//////////////////////////////////////////////////////////////////////////

	Reg#(Bit#(HBM_DATAWIDTH)) writeDes <- mkReg(0);
	Reg#(Bit#(32)) writeReqOff <- mkReg(0);
	Reg#(Bit#(32)) writeCnt <- mkReg(0);

	rule writeback ( kernelStarted && (writeCounter > 0) && mem_kernel.data_response_ready());
		// Bit#(MEM_PORT_DATA_WIDTH) bytes_per_mem_req = fromInteger(valueof(HBM_DATAWIDTH)) >> 3;
		let d <- mem_kernel.get_data_response();

		if (writeCnt >= writeCounter - 1) begin
			Bit#(MEM_PORT_DATA_WIDTH) b = writeCounter * (fromInteger(valueof(DRAM_DATA_WIDTH)) >> 3);
			Bit#(HBM_DATAWIDTH) r = writeDes | (zeroExtend(d) << writeCnt*fromInteger(valueof(DRAM_DATA_WIDTH)));

			$display("\t\t[%d] writeback : writeCnt = %d, writeCounter = %d, MemPortReq(%x, %d)\n\t\twrite_data = %x", cycleCounter, writeCnt, writeCounter, writeReqOff, b, r);

			writeReqQs[2].enq(MemPortReq{addr:zeroExtend(writeReqOff), bytes:b});
			writeWordQs[2].enq(r);

			writeCnt <= 0;
			writeCounter <= 0;

			writeReqOff <= writeReqOff + b;
			writeDes <= 0;

		end else if ( writeCnt >= fromInteger(valueof(WORD_PER_MEM_REQ)) - 1 ) begin
			Bit#(MEM_PORT_DATA_WIDTH) bytes_per_mem_req = fromInteger(valueof(HBM_DATAWIDTH)) >> 3;
			Bit#(HBM_DATAWIDTH) r = writeDes | (zeroExtend(d) << writeCnt*fromInteger(valueof(DRAM_DATA_WIDTH)));

			$display("\t\t[%d] writeback : writeCnt = %d, writeCounter = %d, MemPortReq(%x, %d)\n\t\twrite_data = %x", cycleCounter, writeCnt, writeCounter, writeReqOff, bytes_per_mem_req, r);

			writeReqQs[2].enq(MemPortReq{addr:zeroExtend(writeReqOff), bytes:bytes_per_mem_req});
			writeWordQs[2].enq(r);

			writeCnt <= 0;
			writeCounter <= writeCounter - fromInteger(valueof(WORD_PER_MEM_REQ));

			writeReqOff <= writeReqOff + bytes_per_mem_req;
			writeDes <= 0;

		end else begin
			$display("\t\t[%d] writeback : writeCnt = %d, writeCounter = %d\n\t\twriteDes = %x", cycleCounter, writeCnt, writeCounter, writeDes);

			writeDes <= writeDes | (zeroExtend(d) << writeCnt*fromInteger(valueof(DRAM_DATA_WIDTH)));
			writeCnt <= writeCnt + 1;
		end
	endrule

	//////////////////////////////////////////////////////////////////////////
	rule checkKernelDone ( kernelStarted );
		kernelDone <= ( (remainInst == 0) && (readCounter == 0) && (writeCounter == 0) );
		$display("\t\t[%d] checkKernelDone : remainInst = %d, readCounter = %d, writeCounter = %d", cycleCounter, remainInst, readCounter, writeCounter);
	endrule

	Vector#(MemPortCnt, MemPortIfc) mem_;
	for (Integer i = 0; i < valueOf(MemPortCnt); i=i+1) begin
		mem_[i] = interface MemPortIfc;
			method ActionValue#(MemPortReq) readReq;
				readReqQs[i].deq;
				return readReqQs[i].first;
			endmethod
			method ActionValue#(MemPortReq) writeReq;
				writeReqQs[i].deq;
				return writeReqQs[i].first;
			endmethod
			method ActionValue#(Bit#(512)) writeWord;
				writeWordQs[i].deq;
				return writeWordQs[i].first;
			endmethod
			method Action readWord(Bit#(512) word);
				readWordQs[i].enq(word);
			endmethod
		endinterface;
	end
    method Action start(Bit#(32) totalInst, Bit#(32) wordsToRead, Bit#(32) wordsToWrite);
		kernelStarted <= True;
		kernelDone <= False;
		remainInst <= totalInst;
		readCounter <= wordsToRead;
		writeCounter <= wordsToWrite;
		$display("\t[%d] Kernel started (%d, %d, %d)", cycleCounter, totalInst, wordsToRead, wordsToWrite);
	endmethod
	method Bool started;
		return kernelStarted;
	endmethod
	method Bool done;
		return kernelDone;
	endmethod
	interface mem = mem_;

endmodule
