import BRAM_Kernel :: *;

import StmtFSM :: *;
import Clocks :: *;

(* synthesize *)
module mkBRAM_tb();

    BRAM_Ifc#(32,8) dut <- mkBRAM();

    Stmt test = 
    (seq
        action
            $display("Writing to BRAM cell @ %x : %x", 0, 2);
            dut.request(0, 2, True);
            $display("BRAM cell @ %x : %x", 0, dut.read_response);
        endaction
        action
            $display("Writing to BRAM cell @ %x : %x", 2, 5);
            dut.request(2, 5, True);
            $display("BRAM cell @ %x : %x", 2, dut.read_response);
        endaction
        action
            $display("Reading from BRAM cell @ %x", 0);
            dut.request(0, 0, False);
            $display("BRAM cell @ %x : %x", 0, dut.read_response);
        endaction
        action
            $display("BRAM cell @ %x : %x", 0, dut.read_response);
        endaction
        action
            $display("BRAM cell @ %x : %x", 0, dut.read_response);
        endaction
    endseq);
    mkAutoFSM(test);
endmodule