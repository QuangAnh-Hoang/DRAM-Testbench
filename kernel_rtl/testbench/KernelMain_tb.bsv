import KernelMain :: *;

import StmtFSM :: *;
import Clocks :: *;

(* synthesize *)
module mkKernelMain_tb();
    Reg#(Bit#(512)) inputArray <- mkReg(500);
    Reg#(Bit#(512)) outputArray <- mkReg(0);

    KernelMainIfc kernelMain <- mkKernelMain;

    Reg#(Bit#(32)) cycleCounter <- mkReg(0);
	rule incCycle;
		cycleCounter <= cycleCounter + 1;
	endrule

	Reg#(Bool) started <- mkReg(False);
	rule checkStart (!started);
		started <= kernelMain.started;
	endrule

    Reg#(Bool) done <- mkReg(False);
	rule checkDone ( started );
		done <= kernelMain.done;
        // $display("[%d] Checking done status : %b", cycleCounter, done);
	endrule
	for ( Integer i = 0; i < valueOf(MemPortCnt); i=i+1 ) begin
		rule relayReadReq ( started );
			let r <- kernelMain.mem[i].readReq;
            let d = inputArray;
            kernelMain.mem[i].readWord(d);
			// if ( i == 0 ) axi4mem[i].readReq(axi4control.mem_addr+r.addr,zeroExtend(r.bytes));
			// else axi4mem[i].readReq(axi4control.file_addr+r.addr,zeroExtend(r.bytes));
		endrule
		rule relayWriteReq ( started );
			let r <- kernelMain.mem[i].writeReq;
			let d <- kernelMain.mem[i].writeWord;
            outputArray <= d;
        	// if ( i == 0 ) axi4mem[i].writeReq(axi4control.mem_addr+r.addr,zeroExtend(r.bytes));
			// else axi4mem[i].writeReq(axi4control.file_addr+r.addr,zeroExtend(r.bytes));
		endrule

		// rule relayWriteWord ( started );
		// 	let r <- kernelMain.mem[i].writeWord;
		// 	// axi4mem[i].write(r);
		// endrule
		// rule relayReadWord ( started );
		// 	// let d <- axi4mem[i].read;
		// 	kernelMain.mem[i].readWord(d);
		// endrule
	end

    Stmt test = 
    (seq
        // action
        //     for (Bit#(8) i = 0; i < 10; i=i+1)
        //         begin
		// 			$display("Initializing input array[%d] = %d", i, inputArray[i]);
        //             inputArray[i] <= extend(i);
        //             // $display("Initializing input array[%d] = %d", i, inputArray[i]);
        //         end
        // endaction
        action
            $display("[%d] Starting BRAM kernel with %d bytes to read and write.", cycleCounter, 640);
            kernelMain.start(64);
        endaction
        delay(200);
        action
            $display("[%d] Checking done status : %b", cycleCounter, done);
			$display("[%d] Input value = %x", cycleCounter, inputArray);
			$display("[%d] Output value = %x", cycleCounter, outputArray);
        endaction
		// action
        //     for (Bit#(8) i = 0; i < 10; i=i+1)
        //         begin
        //             $display("Examining output array[%d] = %d", i, outputArray[i]);
        //         end        
		// endaction
    endseq);
    mkAutoFSM(test);

endmodule