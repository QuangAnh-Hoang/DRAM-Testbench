import DRAM_Kernel :: *;

import StmtFSM :: *;
import Clocks :: *;

    // ACT = 5'b00000,
    // PRE = 5'b01010,
    // RD = 5'b01101,
    // WR = 5'b01100,
    // NOP = 5'b01111

(* synthesize *)
module mkDRAM_tb();

    DRAM_Kernel_Ifc dut <- mkDRAM_Kernel();
    // DRAM_Bank_Ifc dut <- mkDRAM_Bank();

    Stmt test = 
    (seq
        action
            Bit#(5) cmd =5'b00000;
            Bit#(4) ba =4'b0000;
            Bit#(14) ra =14'h00000;
            Bit#(23) ctrl = {cmd, ba, ra};
            dut.put_mem_control(ctrl);
        endaction
        // delay(1);
        action
            Bit#(5) cmd =5'b01101;
            Bit#(4) ba =4'b0000;
            Bit#(14) ra =14'h00000;
            Bit#(23) ctrl = {cmd, ba, ra};
            dut.put_mem_control(ctrl);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
        action
            Bit#(5) cmd =5'b01100;
            Bit#(4) ba =4'b0000;
            Bit#(14) ra =14'h00000;
            Bit#(23) ctrl = {cmd, ba, ra};
            dut.put_mem_control(ctrl);
        endaction
        action
            dut.put_mem_data('ha);
        endaction
        action
            dut.put_mem_data('hb);
        endaction
        action
            dut.put_mem_data('hc);
        endaction
        action
            dut.put_mem_data('hd);
        endaction
        action
            Bit#(5) cmd =5'b01101;
            Bit#(4) ba =4'b0000;
            Bit#(14) ra =14'h00000;
            Bit#(23) ctrl = {cmd, ba, ra};
            dut.put_mem_control(ctrl);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
        action
            let d <- dut.get_data_response;
            $display("Read data: %x", d);
        endaction
    endseq);
    mkAutoFSM(test);

endmodule