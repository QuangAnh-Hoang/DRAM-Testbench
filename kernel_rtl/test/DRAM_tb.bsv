import DRAM_Kernel :: *;

import StmtFSM :: *;
import Clocks :: *;

(* synthesize *)
module mkDRAM_tb();

    DRAMKernel_Ifc dut <- mkDRAM_Kernel();

    Stmt test = 
    (seq
        action
            let cmd = 5'b00000;
            let addr = 14'b1011;
            dut.put_mem_inst(bitconcat(cmd, addr));
        endaction
        // delay(1);
        action
            let cmd = 5'b01100;
            let addr = 14'b1010;
            dut.put_mem_inst(bitconcat(cmd, addr));
            dut.put_data('h9);
        endaction
        // delay(1);
        action
            dut.put_data('h8);
        endaction
        // delay(1);
        action
            dut.put_data('h7);
        endaction
        // delay(1);
        action
            dut.put_data('h6);
        endaction
        delay(1);
        action
            let cmd = 5'b01101;
            let addr = 14'b1010;
            dut.put_mem_inst(bitconcat(cmd, addr));
        endaction
        action
            $display("Output buffer data: %h", dut.get_data_response);
        endaction
        action
            $display("Output buffer data: %h", dut.get_data_response);
        endaction
        action
            $display("Output buffer data: %h", dut.get_data_response);
        endaction
        action
            $display("Output buffer data: %h", dut.get_data_response);
        endaction

        action
            let cmd = 5'b01010;
            let addr = 14'b0000;
            dut.put_mem_inst(bitconcat(cmd, addr));
        endaction
    endseq);
    mkAutoFSM(test);

    // Stmt test = 
    // (seq
    //     action
    //         dut.set_command(ACT);
    //         dut.set_address('b1011);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //     endaction
    //     action
    //         dut.set_command(WR);
    //         dut.set_address('b1010);
    //         dut.put_data('h9);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //         dut.put_data('h8);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //         dut.put_data('h7);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //         dut.put_data('h6);
    //     endaction


    //     action
    //         dut.set_command(ACT);
    //         dut.set_address('b1110);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //     endaction
    //     action
    //         dut.set_command(WR);
    //         dut.set_address('b1010);
    //         dut.put_data('h5);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //         dut.put_data('h4);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //         dut.put_data('h3);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //         dut.put_data('h2);
    //     endaction
    //     action
    //         dut.set_command(ACT);
    //         dut.set_address('b1110);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //     endaction
    //     action
    //         dut.set_command(RD);
    //         dut.set_address('b1010);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //     endaction
    //     action
    //         dut.set_command(NOP);
    //     endaction
    //     delay(30);
    //     action
    //         $display("Output buffer data: %h", dut.get_data_response);
    //     endaction
    //     action
    //         $display("Output buffer data: %h", dut.get_data_response);
    //     endaction
    //     action
    //         $display("Output buffer data: %h", dut.get_data_response);
    //     endaction
    //     action
    //         $display("Output buffer data: %h", dut.get_data_response);
    //     endaction
    // endseq);
    // mkAutoFSM(test);
endmodule