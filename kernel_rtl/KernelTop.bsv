import Axi4LiteControllerXrt::*;
import Axi4MemoryMaster::*;

import Vector::*;
import Clocks :: *;

import KernelMain::*;

interface KernelTopIfc;
	(* always_ready *)
	interface Axi4MemoryMasterPinsIfc#(64,512) inst;
	(* always_ready *)
	interface Axi4MemoryMasterPinsIfc#(64,512) data_in;
	(* always_ready *)
	interface Axi4MemoryMasterPinsIfc#(64,512) data_out;
	(* always_ready *)
	interface Axi4LiteControllerXrtPinsIfc#(12,32) s_axi_control;
	(* always_ready *)
	method Bool interrupt;
endinterface

(* synthesize *)
(* default_reset="ap_rst_n", default_clock_osc="ap_clk" *)
module krnl (KernelTopIfc);
	Clock defaultClock <- exposeCurrentClock;
	Reset defaultReset <- exposeCurrentReset;

	Axi4LiteControllerXrtIfc#(12,32) axi4control <- mkAxi4LiteControllerXrt(defaultClock, defaultReset);
	Vector#(3, Axi4MemoryMasterIfc#(64,512)) axi4mem <- replicateM(mkAxi4MemoryMaster);
	//Axi4MemoryMasterIfc#(64,512) axi4file <- mkAxi4MemoryMaster;

/*
	Reg#(Bool) started <- mkReg(False);
	Reg#(Bool) done <- mkReg(False);
	rule checkscalar ( started == False );
		if ( axi4control.ap_start ) started <= True;
	endrule
*/
	Reg#(Bit#(32)) cycleCounter <- mkReg(0);
	rule incCycle;
		cycleCounter <= cycleCounter + 1;
	endrule

	Reg#(Bool) started <- mkReg(False);

	KernelMainIfc kernelMain <- mkKernelMain;
	rule checkStart (!started);
		if ( axi4control.ap_start ) begin
			$display("[%d] checkStart: %x, %d, %d, %d, %x, %x, %x", cycleCounter, axi4control.ap_start, axi4control.scalar00, axi4control.scalar01, axi4control.scalar02, axi4control.inst_q_addr, axi4control.data_in_q_addr, axi4control.data_out_q_addr);
			kernelMain.start(axi4control.scalar00, axi4control.scalar01, axi4control.scalar02);
			started <= True;
		end
	endrule
	rule checkDone ( started );
		// $display("[%d] checkStart: %x, %d, %d, %d, %x, %x, %x", cycleCounter, axi4control.ap_start, axi4control.scalar00, axi4control.scalar01, axi4control.scalar02, axi4control.inst_q_addr, axi4control.data_in_q_addr, axi4control.data_out_q_addr);
		Bool done = kernelMain.done;
		if ( done ) axi4control.ap_done();
	endrule
	for ( Integer i = 0; i < valueOf(MemPortCnt); i=i+1 ) begin
		rule relayReadReq00 ( started );
			let r <- kernelMain.mem[i].readReq;
			if ( i == 0 ) begin
				axi4mem[i].readReq(axi4control.inst_q_addr+r.addr,zeroExtend(r.bytes));
				$display("[%d] relayReadReq00 : axi4mem[%d].readReq(%x + %x, %x)", cycleCounter, i, axi4control.inst_q_addr, r.addr, r.bytes);
			end else if ( i == 1 ) begin
				axi4mem[i].readReq(axi4control.data_in_q_addr+r.addr,zeroExtend(r.bytes));
				$display("[%d] relayReadReq00 : axi4mem[%d].readReq(%x + %x, %x)", cycleCounter, i, axi4control.data_in_q_addr, r.addr, r.bytes);
			end else begin
				axi4mem[i].readReq(axi4control.data_out_q_addr+r.addr,zeroExtend(r.bytes));
				$display("[%d] relayReadReq00 : axi4mem[%d].readReq(%x + %x, %x)", cycleCounter, i, axi4control.data_out_q_addr, r.addr, r.bytes);
			end
		endrule
		rule relayWriteReq ( started );
			let r <- kernelMain.mem[i].writeReq;
			if ( i == 0 ) begin
				axi4mem[i].writeReq(axi4control.inst_q_addr+r.addr,zeroExtend(r.bytes));
				$display("[%d] relayWriteReq : axi4mem[%d].writeReq(%x + %x, %x)", cycleCounter, i, axi4control.inst_q_addr, r.addr, r.bytes);
			end else if ( i == 1 ) begin
				axi4mem[i].writeReq(axi4control.data_in_q_addr+r.addr,zeroExtend(r.bytes));
				$display("[%d] relayWriteReq : axi4mem[%d].writeReq(%x + %x, %x)", cycleCounter, i, axi4control.data_in_q_addr, r.addr, r.bytes);
			end else begin
				axi4mem[i].writeReq(axi4control.data_out_q_addr+r.addr,zeroExtend(r.bytes));
				$display("[%d] relayWriteReq : axi4mem[%d].writeReq(%x + %x, %x)", cycleCounter, i, axi4control.data_out_q_addr, r.addr, r.bytes);
			end
		endrule
		rule relayWriteWord ( started );
			let r <- kernelMain.mem[i].writeWord;
			axi4mem[i].write(r);
			$display("[%d] relayWriteWord : kernelMain.mem[%d].writeWord = %x", cycleCounter, i, r);
		endrule
		rule relayReadWord ( started );
			let d <- axi4mem[i].read;
			kernelMain.mem[i].readWord(d);
			$display("[%d] relayReadWord : axi4mem[%d].read = %x", cycleCounter, i, d);
		endrule
	end


	interface inst = axi4mem[0].pins;
	interface data_in = axi4mem[1].pins;
	interface data_out = axi4mem[2].pins;
	
	interface s_axi_control = axi4control.pins;
	interface interrupt = axi4control.interrupt;
endmodule
