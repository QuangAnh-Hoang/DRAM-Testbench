import BRAMCore :: *;

interface BRAM_Ifc #(numeric type addrSz, numeric type dataSz);
    method Action request(Bit#(addrSz) addr, Bit#(dataSz) data, Bool write_not_read);
    method Bit#(dataSz) read_response;
endinterface

module mkBRAM (BRAM_Ifc#(addrSz, dataSz));
    // BRAM_DUAL_PORT#(Bit#(addrSz), Bit#(dataSz)) mem_bank <- mkBRAMCore2(2**fromInteger(valueof(addrSz)), False);

    // String filename = strConcat(strConcat("mem%x", bitToString(id)), ".txt");
// module mkBRAM(BRAM_Ifc#(addrSz, dataSz));
    BRAM_DUAL_PORT#(Bit#(addrSz), Bit#(dataSz)) mem_bank <- mkBRAMCore2Load(2**fromInteger(valueof(addrSz)), False, "mem_0.txt", False);

    method Action request(Bit#(addrSz) addr, Bit#(dataSz) data, Bool write_not_read);
        if (write_not_read) mem_bank.a.put(True, addr, data);
        else mem_bank.b.put(False, addr, 0);
    endmethod

    method Bit#(dataSz) read_response;
        let dataOut = mem_bank.b.read;
        return dataOut;
    endmethod
endmodule