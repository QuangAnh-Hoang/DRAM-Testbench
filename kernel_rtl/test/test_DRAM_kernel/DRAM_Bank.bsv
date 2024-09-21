import BRAM_Kernel::*;

import FIFOF::*;
import Vector::*;

// Bank config parameters
typedef 14 ROW_ADDR_WIDTH;
typedef 6  COL_ADDR_WIDTH;
typedef 4 BANK_ADDR_WIDTH;

typedef ROW_ADDR_WIDTH ADDR_WIDTH;

typedef TExp#(ROW_ADDR_WIDTH) NUM_ROWS_PER_BANK;
typedef TExp#(COL_ADDR_WIDTH) NUM_COLS_PER_BANK;

typedef 4 BURST_LENGTH;
typedef 4 NUM_ARRAY_PER_BANK;
typedef NUM_ARRAY_PER_BANK WORD_SIZE;

typedef TMul#(NUM_COLS_PER_BANK, WORD_SIZE) ROW_DATA_WIDTH;

typedef enum {
    ACT = 5'b00000,
    PRE = 5'b01010,
    RD = 5'b01101,
    WR = 5'b01100,
    NOP = 5'b01111
} BankCMD deriving (Bits, Eq);

typedef enum {
    Idle,
    Activating,
    BankActive,
    Reading,
    Writing,
    Precharging
} BankState deriving (Bits, Eq);

interface DRAM_Bank_Ifc;
    method Action put_bank_cmd(BankCMD cmd, Bit#(ADDR_WIDTH) addr);
    method Action put_bank_data(Bit#(WORD_SIZE) data);
    method Bool data_response_ready;
    method ActionValue#(Bit#(WORD_SIZE)) get_data_response;
    method Bit#(ADDR_WIDTH) get_active_row;
endinterface

(* synthesize *)
module mkDRAM_Bank (DRAM_Bank_Ifc);
    // String filename = strConcat(strConcat("mem%x", bitToString(bankid)), ".txt");

// module mkDRAM_Bank(DRAM_Bank_Ifc);

    // Instantiate a DRAM bank with 16386 words (ROW_ADDR_WIDTH = 14).
    // One word in BRAM corresponds with one row in DRAM, which has 
    // the size of NUM_COLS_PER_BANK*WORD_SIZE so that in one read 
    // request, all data on the same row is read.
    // Integer ROW_DATA_WIDTH = NUM_COLS_PER_BANK*WORD_SIZE;
    BRAM_Ifc#(ROW_ADDR_WIDTH, ROW_DATA_WIDTH) mem_cells <- mkBRAM(); 

    FIFOF#(BankCMD) cmdQ <- mkFIFOF();
    FIFOF#(Bit#(ADDR_WIDTH)) addrQ <- mkFIFOF();
    FIFOF#(Bit#(WORD_SIZE)) dataQ <- mkFIFOF();

    Reg#(Bit#(ADDR_WIDTH)) activeRowAddr <- mkReg(0); 
    Reg#(Bit#(ADDR_WIDTH)) currColAddr <- mkReg(0); 

    Reg#(Bit#(ROW_DATA_WIDTH)) rowBuffer <- mkReg(0); 

    FIFOF#(Bit#(WORD_SIZE)) outputDataBuff <- mkSizedFIFOF(valueof(BURST_LENGTH));

    Reg#(BankState) currState <- mkReg(Idle);
    Reg#(BankCMD) currCommand <- mkReg(NOP);
    Reg#(Bit#(ADDR_WIDTH)) currAddress <- mkReg(0);

    Reg#(Bit#(ADDR_WIDTH)) stallCounter <- mkReg(0);
    Reg#(Bit#(ADDR_WIDTH)) burstCounter <- mkReg(0);
    Reg#(Bit#(ROW_DATA_WIDTH)) rowMask <- mkReg(0);

    //////////////////////////////////////////////////////////////////////////

    // Make sure each command corresponds with one address in queue
    rule fetch (cmdQ.notEmpty() && addrQ.notEmpty() && (stallCounter == 0));
        cmdQ.deq();
        addrQ.deq();

        currCommand <= cmdQ.first;
        currAddress <= addrQ.first;
    endrule

    rule process_ACT (currCommand == ACT);
        stallCounter <= 1;
        currCommand <= NOP;

        currState <= Activating;
        activeRowAddr <= currAddress;
        mem_cells.request(currAddress, 0, False);
    endrule

    rule process_PRE (currCommand == PRE);
        stallCounter <= 1;
        currCommand <= NOP;

        currState <= Precharging;
        mem_cells.request(activeRowAddr, rowBuffer, True);
    endrule

    rule process_RD (currCommand == RD);
        stallCounter <= fromInteger(valueof(BURST_LENGTH));
        currCommand <= NOP;

        currState <= Reading;
        burstCounter <= 0;
        currColAddr <= currAddress;
    endrule

    rule process_WR (currCommand == WR);
        stallCounter <= fromInteger(valueof(BURST_LENGTH));
        currCommand <= NOP;

        currState <= Writing;
        burstCounter <= 0;
        currColAddr <= currAddress;

        Bit#(WORD_SIZE) m = -1;
        Bit#(ROW_DATA_WIDTH) d = zeroExtend(m);
        let s = currAddress << log2(valueof(WORD_SIZE));
        rowMask <= d << s;
    endrule

    rule process_NOP ((currCommand == NOP));
        if (stallCounter > 0) stallCounter <= stallCounter - 1;

        case (currState) matches
            Activating: 
                begin
                    let d = mem_cells.read_response;
                    rowBuffer <= d;
                    currState <= BankActive;
                end

            Reading:
                begin
                    if (burstCounter >= fromInteger(valueof(BURST_LENGTH))) currState <= BankActive;
                    else begin
                        let offset = (currColAddr + burstCounter) << log2(valueof(WORD_SIZE));
                        Bit#(WORD_SIZE) d = rowBuffer[offset + fromInteger(valueof(WORD_SIZE)) - 1 : offset];
                        outputDataBuff.enq(d);
                        burstCounter <= burstCounter + 1;
                    end
                end

            Writing:
                begin
                    if (burstCounter >= fromInteger(valueof(BURST_LENGTH))) currState <= BankActive;
                    else begin
                        let offset = (currColAddr + burstCounter) << log2(valueof(WORD_SIZE));
                        dataQ.deq();
                        Bit#(WORD_SIZE) d = dataQ.first;
                        Bit#(ROW_DATA_WIDTH) rep_d = zeroExtend(d) << offset;

                        rowBuffer <= (rep_d & rowMask) | (rowBuffer & ~rowMask);
                        rowMask <= rotateBitsBy(rowMask, fromInteger(valueof(WORD_SIZE)));

                        burstCounter <= burstCounter + 1;
                    end
                end

            Idle: currState <= Idle;
            BankActive: currState <= BankActive;
            Precharging: currState <= Idle;
        endcase
    endrule

    //////////////////////////////////////////////////////////////////////////

    method Action put_bank_cmd(BankCMD cmd, Bit#(ADDR_WIDTH) addr);
        cmdQ.enq(cmd);
        addrQ.enq(addr);
    endmethod

    method Action put_bank_data(Bit#(WORD_SIZE) data);
        dataQ.enq(data);
    endmethod

    method Bool data_response_ready;
        return outputDataBuff.notEmpty();
    endmethod

    method ActionValue#(Bit#(WORD_SIZE)) get_data_response;
        outputDataBuff.deq();
        return outputDataBuff.first;
    endmethod

    method Bit#(ADDR_WIDTH) get_active_row;
        return activeRowAddr;
    endmethod
endmodule