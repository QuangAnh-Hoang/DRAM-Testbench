import DRAM_Bank::*;

import FIFOF::*;
import Vector::*;

// function String getFilename(Bit#(4) bankid);
//     case (bits) matches
//         4'h0: return "mem_0.txt";
//         4'h1: return "mem_1.txt";
//         4'h2: return "mem_2.txt";
//         4'h3: return "mem_3.txt";

//         4'h4: return "mem_4.txt";
//         4'h5: return "mem_5.txt";
//         4'h6: return "mem_6.txt";
//         4'h7: return "mem_7.txt";

//         4'h8: return "mem_8.txt";
//         4'h9: return "mem_9.txt";
//         4'ha: return "mem_a.txt";
//         4'hb: return "mem_b.txt";

//         4'hc: return "mem_c.txt";
//         4'hd: return "mem_d.txt";
//         4'he: return "mem_e.txt";
//         4'hf: return "mem_f.txt";
//     endcase
// endfunction : getFilename

typedef 16 NUM_BANKS;

// typedef 8 CMD_WIDTH;
// typedef TAdd#(TAdd#(COL_ADDR_WIDTH, ROW_ADDR_WIDTH), TAdd#(BANK_ADDR_WIDTH,CMD_WIDTH)) CTRL_WIDTH;

typedef 5 CMD_WIDTH;
typedef TAdd#(TAdd#(CMD_WIDTH, BANK_ADDR_WIDTH), ADDR_WIDTH) CTRL_WIDTH;

interface DRAM_Kernel_Ifc;
    method Action put_mem_control(Bit#(CTRL_WIDTH) control);
    method Action put_mem_data(Bit#(WORD_SIZE) data);
    method Bool data_response_ready;
    method ActionValue#(Bit#(WORD_SIZE)) get_data_response;
endinterface

(* synthesize *)
module mkDRAM_Kernel(DRAM_Kernel_Ifc);

    // DRAM Kernel-Main interface
    FIFOF#(Bit#(CTRL_WIDTH)) controlQ <- mkFIFOF();
    FIFOF#(Bit#(WORD_SIZE)) dataInQ <- mkFIFOF();
    FIFOF#(Bit#(WORD_SIZE)) dataOutQ <- mkFIFOF();

    // DRAM banks and Kernel-bank interface
    // Vector#(NUM_BANKS, DRAM_Bank_Ifc) dram_banks <- genWithM(compose(mkDRAM_Bank, compose(getFilename, fromInteger)));
    Vector#(NUM_BANKS, DRAM_Bank_Ifc) dram_banks <- replicateM(mkDRAM_Bank);

    Vector#(NUM_BANKS, FIFOF#(Bit#(CMD_WIDTH))) dram_banks_cmdQ <- replicateM(mkFIFOF());
    Vector#(NUM_BANKS, FIFOF#(Bit#(ADDR_WIDTH))) dram_banks_addrQ <- replicateM(mkFIFOF());

    // Internal control signals/registers/queues
    FIFOF#(Bit#(BANK_ADDR_WIDTH)) dram_bank_read_queue <- mkSizedFIFOF(valueof(BURST_LENGTH));
    FIFOF#(Bit#(BANK_ADDR_WIDTH)) dram_bank_write_queue <- mkSizedFIFOF(valueof(BURST_LENGTH));
    Reg#(Bit#(8)) dram_bank_read_burst_counter <- mkReg(0);
    Reg#(Bit#(8)) dram_bank_write_burst_counter <- mkReg(0);

    Vector#(NUM_BANKS, Reg#(Bit#(8))) dram_banks_stall_cnt <- replicateM(mkReg(0));
    // Vector#(NUM_BANKS, Reg#(BankState)) dram_banks_status <- replicateM(mkReg(Idle));
    // Reg#(Bit#(BANK_ADDR_WIDTH)) dram_data_in_bus_lock <- mkReg(0);
    // Reg#(Bit#(BANK_ADDR_WIDTH)) dram_data_out_bus_lock <- mkReg(0);

    //////////////////////////////////////////////////////////////////////////

    rule decode (controlQ.notEmpty());
        let c = controlQ.first;
        Bit#(ADDR_WIDTH) addr = truncate(c);
        Bit#(BANK_ADDR_WIDTH) bankidx = truncate(c >> valueof(BANK_ADDR_WIDTH));
        Bit#(CMD_WIDTH) cmd = truncate(c >> (valueof(ADDR_WIDTH) + valueof(BANK_ADDR_WIDTH)));

        $display("Decoding: %d, %x, %x", bankidx, cmd, addr);

        if (dram_banks_stall_cnt[bankidx] > 0) dram_banks_stall_cnt[bankidx] <= dram_banks_stall_cnt[bankidx] - 1;
        else begin
            controlQ.deq();

            case (cmd) matches
                5'b00???: // ACT command
                    begin
                        $display("\tACT: %d, %x", bankidx, addr);
                        dram_banks[bankidx].put_bank_cmd(ACT, addr);
                        dram_banks_stall_cnt[bankidx] <= 1;
                    end
                5'b01010: // PRE command
                    begin
                        $display("\tPRE: %d, %x", bankidx, addr);
                        dram_banks[bankidx].put_bank_cmd(PRE, addr);
                        dram_banks_stall_cnt[bankidx] <= 1;
                    end
                5'b01101: // RD command
                    begin
                        $display("\tRD: %d, %x", bankidx, addr);
                        dram_banks[bankidx].put_bank_cmd(RD, addr);
                        dram_bank_read_queue.enq(bankidx);
                        dram_banks_stall_cnt[bankidx] <= fromInteger(valueof(BURST_LENGTH));
                    end
                5'b01100: // WR command
                    begin
                        $display("\tWR: %d, %x", bankidx, addr);
                        dram_banks[bankidx].put_bank_cmd(WR, addr);
                        dram_bank_write_queue.enq(bankidx);
                        dram_banks_stall_cnt[bankidx] <= fromInteger(valueof(BURST_LENGTH));
                    end
            endcase
        end
    endrule

    Reg#(Bit#(BANK_ADDR_WIDTH)) bank_to_read <- mkReg(0);
    Reg#(Bit#(BANK_ADDR_WIDTH)) bank_to_write <- mkReg(0);

    rule setBankToRead ( dram_bank_read_queue.notEmpty() && (dram_bank_read_burst_counter == 0) );
        $display("\tSet to read from bank: %d", dram_bank_read_queue.first);

        dram_bank_read_queue.deq();
        bank_to_read <= dram_bank_read_queue.first;
        dram_bank_read_burst_counter <= fromInteger(valueof(BURST_LENGTH));
    endrule

    rule readDataFromBank (dram_bank_read_burst_counter > 0);
        if (dram_banks[bank_to_read].data_response_ready()) begin
            let d <- dram_banks[bank_to_read].get_data_response;
            dataOutQ.enq(d);
            dram_bank_read_burst_counter <= dram_bank_read_burst_counter - 1;
        end
    endrule

    rule setBankToWrite ( dram_bank_write_queue.notEmpty() && (dram_bank_write_burst_counter == 0) );
        $display("\tSet to write to bank: %d", dram_bank_write_queue.first);
        
        dram_bank_write_queue.deq();
        bank_to_write <= dram_bank_write_queue.first;
        dram_bank_write_burst_counter <= fromInteger(valueof(BURST_LENGTH));
    endrule

    rule writeDataToBank ( dram_bank_write_burst_counter > 0 );
        dataInQ.deq();
        let d = dataInQ.first;
        dram_banks[bank_to_write].put_bank_data(d);
        dram_bank_write_burst_counter <= dram_bank_write_burst_counter - 1;
    endrule 

    //////////////////////////////////////////////////////////////////////////

    method Action put_mem_control(Bit#(CTRL_WIDTH) control);
        controlQ.enq(control);
    endmethod

    method Action put_mem_data(Bit#(WORD_SIZE) data);
        dataInQ.enq(data);
    endmethod

    method Bool data_response_ready;
        return dataOutQ.notEmpty();
    endmethod

    method ActionValue#(Bit#(WORD_SIZE)) get_data_response;
        dataOutQ.deq();
        return dataOutQ.first;
    endmethod

endmodule