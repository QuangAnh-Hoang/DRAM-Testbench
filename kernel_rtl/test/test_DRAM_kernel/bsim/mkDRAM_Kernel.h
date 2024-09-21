/*
 * Generated by Bluespec Compiler (build e4c11968)
 * 
 * On Wed Sep  4 18:43:50 PDT 2024
 * 
 */

/* Generation options: */
#ifndef __mkDRAM_Kernel_h__
#define __mkDRAM_Kernel_h__

#include "bluesim_types.h"
#include "bs_module.h"
#include "bluesim_primitives.h"
#include "bs_vcd.h"
#include "mkDRAM_Bank.h"


/* Class declaration for the mkDRAM_Kernel module */
class MOD_mkDRAM_Kernel : public Module {
 
 /* Clock handles */
 private:
  tClock __clk_handle_0;
 
 /* Clock gate handles */
 public:
  tUInt8 *clk_gate[0];
 
 /* Instantiation parameters */
 public:
 
 /* Module state */
 public:
  MOD_Reg<tUInt8> INST_bank_to_read;
  MOD_Reg<tUInt8> INST_bank_to_write;
  MOD_Fifo<tUInt32> INST_controlQ;
  MOD_Fifo<tUInt8> INST_dataInQ;
  MOD_Fifo<tUInt8> INST_dataOutQ;
  MOD_Reg<tUInt8> INST_dram_bank_read_burst_counter;
  MOD_Fifo<tUInt8> INST_dram_bank_read_queue;
  MOD_Reg<tUInt8> INST_dram_bank_write_burst_counter;
  MOD_Fifo<tUInt8> INST_dram_bank_write_queue;
  MOD_mkDRAM_Bank INST_dram_banks_0;
  MOD_mkDRAM_Bank INST_dram_banks_1;
  MOD_mkDRAM_Bank INST_dram_banks_10;
  MOD_mkDRAM_Bank INST_dram_banks_11;
  MOD_mkDRAM_Bank INST_dram_banks_12;
  MOD_mkDRAM_Bank INST_dram_banks_13;
  MOD_mkDRAM_Bank INST_dram_banks_14;
  MOD_mkDRAM_Bank INST_dram_banks_15;
  MOD_mkDRAM_Bank INST_dram_banks_2;
  MOD_mkDRAM_Bank INST_dram_banks_3;
  MOD_mkDRAM_Bank INST_dram_banks_4;
  MOD_mkDRAM_Bank INST_dram_banks_5;
  MOD_mkDRAM_Bank INST_dram_banks_6;
  MOD_mkDRAM_Bank INST_dram_banks_7;
  MOD_mkDRAM_Bank INST_dram_banks_8;
  MOD_mkDRAM_Bank INST_dram_banks_9;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_0;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_1;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_10;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_11;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_12;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_13;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_14;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_15;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_2;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_3;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_4;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_5;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_6;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_7;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_8;
  MOD_Fifo<tUInt32> INST_dram_banks_addrQ_9;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_0;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_1;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_10;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_11;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_12;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_13;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_14;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_15;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_2;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_3;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_4;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_5;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_6;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_7;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_8;
  MOD_Fifo<tUInt8> INST_dram_banks_cmdQ_9;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_0;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_1;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_10;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_11;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_12;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_13;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_14;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_15;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_2;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_3;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_4;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_5;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_6;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_7;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_8;
  MOD_Reg<tUInt8> INST_dram_banks_stall_cnt_9;
 
 /* Constructor */
 public:
  MOD_mkDRAM_Kernel(tSimStateHdl simHdl, char const *name, Module *parent);
 
 /* Symbol init methods */
 private:
  void init_symbols_0();
 
 /* Reset signal definitions */
 private:
  tUInt8 PORT_RST_N;
 
 /* Port definitions */
 public:
 
 /* Publicly accessible definitions */
 public:
  tUInt8 DEF_x__h10434;
  tUInt8 DEF_cmd__h6813;
  tUInt32 DEF_controlQ_first____d19;
  tUInt8 DEF__read__h6736;
  tUInt8 DEF__read__h6705;
  tUInt8 DEF__read__h6674;
  tUInt8 DEF__read__h6643;
  tUInt8 DEF__read__h6612;
  tUInt8 DEF__read__h6581;
  tUInt8 DEF__read__h6550;
  tUInt8 DEF__read__h6519;
  tUInt8 DEF__read__h6488;
  tUInt8 DEF__read__h6457;
  tUInt8 DEF__read__h6426;
  tUInt8 DEF__read__h6395;
  tUInt8 DEF__read__h6364;
  tUInt8 DEF__read__h6333;
  tUInt8 DEF__read__h6302;
  tUInt8 DEF__read__h6271;
  tUInt8 DEF_x__h10672;
  tUInt8 DEF_x__h10273;
  tUInt8 DEF_x__h9999;
  tUInt8 DEF_bankidx__h6812;
  tUInt8 DEF_x__h7523;
  tUInt8 DEF_SEL_ARR_dram_banks_0_data_response_ready__73_d_ETC___d191;
  tUInt8 DEF_controlQ_first__9_BITS_22_TO_18_6_EQ_0b1101___d46;
  tUInt8 DEF_SEL_ARR_dram_banks_stall_cnt_0_dram_banks_stal_ETC___d22;
  tUInt8 DEF_controlQ_first__9_BITS_22_TO_18_6_EQ_0b1100___d49;
  tUInt8 DEF_controlQ_first__9_BITS_22_TO_18_6_EQ_0b1010___d27;
  tUInt8 DEF_controlQ_first__9_BITS_22_TO_21_4_EQ_0b0___d25;
  tUInt8 DEF_NOT_SEL_ARR_dram_banks_stall_cnt_0_dram_banks__ETC___d23;
 
 /* Local definitions */
 private:
 
 /* Rules */
 public:
  void RL_decode();
  void RL_setBankToRead();
  void RL_readDataFromBank();
  void RL_setBankToWrite();
  void RL_writeDataToBank();
 
 /* Methods */
 public:
  void METH_put_mem_control(tUInt32 ARG_put_mem_control_control);
  tUInt8 METH_RDY_put_mem_control();
  void METH_put_mem_data(tUInt8 ARG_put_mem_data_data);
  tUInt8 METH_RDY_put_mem_data();
  tUInt8 METH_get_data_response();
  tUInt8 METH_RDY_get_data_response();
 
 /* Reset routines */
 public:
  void reset_RST_N(tUInt8 ARG_rst_in);
 
 /* Static handles to reset routines */
 public:
 
 /* Pointers to reset fns in parent module for asserting output resets */
 private:
 
 /* Functions for the parent module to register its reset fns */
 public:
 
 /* Functions to set the elaborated clock id */
 public:
  void set_clk_0(char const *s);
 
 /* State dumping routine */
 public:
  void dump_state(unsigned int indent);
 
 /* VCD dumping routines */
 public:
  unsigned int dump_VCD_defs(unsigned int levels);
  void dump_VCD(tVCDDumpType dt, unsigned int levels, MOD_mkDRAM_Kernel &backing);
  void vcd_defs(tVCDDumpType dt, MOD_mkDRAM_Kernel &backing);
  void vcd_prims(tVCDDumpType dt, MOD_mkDRAM_Kernel &backing);
  void vcd_submodules(tVCDDumpType dt, unsigned int levels, MOD_mkDRAM_Kernel &backing);
};

#endif /* ifndef __mkDRAM_Kernel_h__ */