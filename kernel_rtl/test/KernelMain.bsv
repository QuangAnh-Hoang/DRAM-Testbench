import BRAM_Kernel :: *;

import FIFO::*;
import Vector::*;

typedef 2 MemPortCnt;

interface MemPortIfc;
	method ActionValue#(MemPortReq) readReq;
	method ActionValue#(MemPortReq) writeReq;
	method ActionValue#(Bit#(512)) writeWord;
	method Action readWord(Bit#(512) word);
endinterface

interface KernelMainIfc;
    method Action start(Bit#(32) param);
	method Bool started;
    method Bool done;
    interface Vector#(MemPortCnt, MemPortIfc) mem;
endinterface

typedef struct {
	Bit#(64) addr;
	Bit#(32) bytes;
} MemPortReq deriving (Eq,Bits);

module mkKernelMain(KernelMainIfc);
    Vector#(MemPortCnt, FIFO#(MemPortReq)) readReqQs <- replicateM(mkFIFO);
	Vector#(MemPortCnt, FIFO#(MemPortReq)) writeReqQs <- replicateM(mkFIFO);
	Vector#(MemPortCnt, FIFO#(Bit#(512))) writeWordQs <- replicateM(mkFIFO);
	Vector#(MemPortCnt, FIFO#(Bit#(512))) readWordQs <- replicateM(mkFIFO);

    BRAM_Ifc#(32,32) mem_bank <- mkBRAM();

	Reg#(Bit#(32)) cycleCounter <- mkReg(0);
	Reg#(Bool) kernelStarted <- mkReg(False);
	Reg#(Bit#(32)) totalBytes <- mkReg(0);
	Reg#(Bit#(32)) bytesToRead <- mkReg(0);

	rule incCycle (kernelStarted);
		cycleCounter <= cycleCounter + 1;
	endrule

	Reg#(Bool) kernelDone <- mkReg(False);

	//////////////////////////////////////////////////////////////////////////
    // POV: IP-central, sending read requests to HBM (not BRAM)
    Reg#(Bit#(32)) readReqOff <- mkReg(0);
    rule sendReadReq ( kernelStarted && bytesToRead > 0 );
		// $display("\t[%d] sendReadReq : bytesToRead = %d", cycleCounter, bytesToRead);

		if ( bytesToRead > 64 ) bytesToRead <= bytesToRead - 64;
		else bytesToRead <= 0;

		readReqQs[0].enq(MemPortReq{addr:zeroExtend(readReqOff), bytes:64});
		readReqOff <= readReqOff + 64;
	endrule

	Reg#(Bit#(512)) serializerBuff <- mkReg(0);
	Reg#(Bit#(32)) serializerCouter <- mkReg(0);
	FIFO#(Bit#(32)) compactedQ <- mkFIFO;

	rule recvReadResp ( kernelStarted );
		// $display("\t[%d] recvReadResp : serializerCouter = %d", cycleCounter, serializerCouter);

		if ( serializerCouter == 0 ) begin
			let d = readWordQs[0].first;
			readWordQs[0].deq;
			compactedQ.enq(truncate(d));
			serializerBuff <= (d>>32);
			serializerCouter <= 15;
		end else begin
			serializerCouter <= serializerCouter - 1;
			serializerBuff <= (serializerBuff>>32);
			compactedQ.enq(truncate(serializerBuff));
		end
	endrule

	Reg#(Bit#(32)) writeBRAMOff <- mkReg(0);
	Reg#(Bool) writeBRAMDone <- mkReg(False);
    rule writeToBRAM ( kernelStarted );
		// $display("\t[%d] writeToBRAM : writeBRAMOff (%d) < totalBytes (%d) ? (kernelStarted && writeBRAMDone) = %d", 
		// 	cycleCounter, writeBRAMOff, totalBytes, (kernelStarted && writeBRAMDone)
		// );

		if (writeBRAMOff >= zeroExtend(totalBytes)) writeBRAMDone <= True;
		else
			begin
				compactedQ.deq;
				let d = compactedQ.first;
				// $display("\t[%d] writeToBRAM : mem_bank.request(%d, %x, True);", cycleCounter, writeBRAMOff, d);

				mem_bank.request(writeBRAMOff, d, True);
				writeBRAMOff <= writeBRAMOff + 4;
			end
    endrule

	Reg#(Bit#(32)) readBRAMOff <- mkReg(0);
	FIFO#(Bit#(32)) readDataQ <- mkFIFO;
	rule readFromBRAM (kernelStarted && writeBRAMDone && (readBRAMOff <= totalBytes));
		// $display("\t[%d] readFromBRAM : mem_bank.request(%d, 0, False);", cycleCounter, readBRAMOff);
		
		let d = mem_bank.read_response;
		// $display("\t[%d] readFromBRAM : mem_bank.read_response = %x;", cycleCounter, d);
		readDataQ.enq(d);
		
		mem_bank.request(readBRAMOff, 0, False);
		readBRAMOff <= readBRAMOff + 4;
	endrule

	Reg#(Bit#(32)) writeCnt <- mkReg(0);
	Reg#(Bit#(512)) writeDes <- mkReg(0);
	Reg#(Bit#(32)) writeReqOff <- mkReg(0);
	rule writeback ( kernelStarted && writeBRAMDone && ! kernelDone );
		kernelDone <= ( writeReqOff >= totalBytes );
		// $display("\t[%d] writeback : writeReqOff = %d, totalBytes = %d, kernelDone = %b", cycleCounter, writeReqOff, totalBytes, kernelDone);

		readDataQ.deq;

		if (writeCnt >= 15) begin
			writeReqQs[1].enq(MemPortReq{addr:zeroExtend(writeReqOff), bytes:64});
			writeWordQs[1].enq(writeDes);
			$display("\t[%d] writeback : MemPortReq(%x, %d)\n\t\twriteDes = %x", cycleCounter, writeReqOff, 64, writeDes);

			writeCnt <= 0;
			writeReqOff <= writeReqOff + 64;
			writeDes <= zeroExtend(readDataQ.first);
		end else begin
			writeDes <= writeDes | (zeroExtend(readDataQ.first) << 32*writeCnt);
			writeCnt <= writeCnt + 1;
		end

		// $display("\t[%d] writeback : writeCnt = %d, \n\t\twriteDes = %x", cycleCounter, writeCnt, writeDes);

	endrule

	//////////////////////////////////////////////////////////////////////////
	// rule checkKernelDone;
	// 	kernelDone <= ( writeReqOff >= totalBytes );
	// 	$display("\t[%d] checkKernelDone : writeReqOff (%d) >= totalBytes (%d) : %b", cycleCounter, writeReqOff, totalBytes, kernelDone);
	// endrule

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
	method Action start(Bit#(32) param);
		kernelStarted <= True;
		bytesToRead <= param;
		totalBytes <= param;
		$display("\t[%d] Kernel started (%d)", cycleCounter, param);
	endmethod
	method Bool started;
		return kernelStarted;
	endmethod
	method Bool done;
		return kernelDone;
	endmethod
	interface mem = mem_;

endmodule
