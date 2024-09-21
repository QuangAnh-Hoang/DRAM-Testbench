import DRAM_Kernel::*;
import DRAM_Bank::*;
import DRAM_Config::*;

import FIFOF::*;
import Vector::*;

function Bool maskbit(Bit#(INPUT_WIDTH) data, Integer n);
    let mask = 1 << n;
    return ((data & mask) >> n) == 1;
endfunction : maskbit

function Bit#(ROW_ADDR_WIDTH) maskRowAddr(Bit#(INPUT_WIDTH) data);
    let mask = -1 << valueof(ROW_ADDR_WIDTH);
    return (truncate(data) & mask);
endfunction : maskRowAddr

function Bit#(COL_ADDR_WIDTH) maskColAddr(Bit#(INPUT_WIDTH) data);
    let mask = -1 << valueof(COL_ADDR_WIDTH);
    return (truncate(data) & mask);
endfunction : maskColAddr


interface DRAMCmdDec_Ifc;
    method Action queue_input_inst(Bit#(INPUT_WIDTH) inputInst);
    method ActionValue#(CMD) get_mem_cmd();
    method ActionValue#(Bit#(ADDR_WIDTH)) get_addr();
endinterface

module mkDRAMCmdDec(DRAMCmdDec_Ifc);
    FIFOF#(Bit#(INPUT_WIDTH)) inputQ <- mkFIFOF();
    FIFOF#(CMD) outputCmdQ <- mkFIFOF();
    FIFOF#(Bit#(ADDR_WIDTH)) outputAddrQ <- mkFIFOF();

    Wire#(Bit#(INPUT_WIDTH)) currInst <- mkWire();

    Wire#(Bool) n_CS <- mkWire();
    Wire#(Bool) n_ACT <- mkWire();
    Wire#(Bool) n_RAS <- mkWire();
    Wire#(Bool) n_CAS <- mkWire();
    Wire#(Bool) n_WE <- mkWire();

    rule get_inst;
        if ( inputQ.notEmpty() ) begin
            inputQ.deq();
            currInst <= inputQ.first;
        end else currInst <= -1 << 18;
    endrule

    rule get_ctrl_signals;
        n_CS <= maskbit(currInst, 18);
        n_ACT <= maskbit(currInst, 17);
        n_RAS <= maskbit(currInst, 16);
        n_CAS <= maskbit(currInst, 15);
        n_WE <= maskbit(currInst, 14);
    endrule

    rule queue_nop (!n_CS && n_ACT && n_RAS && n_CAS && n_WE)
        outputCmdQ.enq(NOP);
    endrule

    rule queue_precharge (!n_CS && n_ACT && !n_RAS && n_CAS && !n_WE);
        outputCmdQ.enq(PRE);
    endrule

    rule queue_activate (!n_CS && !n_ACT);
        outputCmdQ.enq(ACT);
        outputCmdQ.enq(NOP);
        outputAddrQ.enq(extend(maskRowAddr(currInst)));
    endrule

    rule queue_write (!n_CS && n_ACT && !n_RAS && n_CAS && !n_WE);
        outputCmdQ.enq(WR);
        for (int i = 0; i < fromInteger(valueof(BURST_LENGTH)); i = i+1)
            outputCmdQ.enq(NOP);
        outputAddrQ.enq(extend(maskColAddr(currInst)));
    endrule

    rule queue_read (!n_CS && n_ACT && !n_RAS && n_CAS && !n_WE);
        outputCmdQ.enq(RD);
        for (int i = 0; i < fromInteger(valueof(BURST_LENGTH)); i = i+1)
            outputCmdQ.enq(NOP);
        outputAddrQ.enq(extend(maskColAddr(currInst)));
    endrule

	//////////////////////////////////////////////////////////////////////////

    method Action queue_input_inst(Bit#(INPUT_WIDTH) inputInst);
        inputQ.enq(inputInst);
    endmethod

    method ActionValue#(CMD) get_mem_cmd();
        outputCmdQ.deq();
        return outputCmdQ.first;
    endmethod

    method ActionValue#(Bit#(ADDR_WIDTH)) get_addr();
        outputAddrQ.deq();
        return outputAddrQ.first;
    endmethod

endmodule