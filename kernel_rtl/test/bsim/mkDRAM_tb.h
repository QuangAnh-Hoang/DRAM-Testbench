/*
 * Generated by Bluespec Compiler (build e4c11968)
 * 
 * On Sun Aug 18 22:18:52 PDT 2024
 * 
 */

/* Generation options: */
#ifndef __mkDRAM_tb_h__
#define __mkDRAM_tb_h__

#include "bluesim_types.h"
#include "bs_module.h"
#include "bluesim_primitives.h"
#include "bs_vcd.h"


/* Class declaration for the mkDRAM_tb module */
class MOD_mkDRAM_tb : public Module {
 
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
  MOD_Wire<tUInt8> INST_abort;
  MOD_Fifo<tUInt32> INST_dut_addrQ;
  MOD_Reg<tUInt32> INST_dut_burstCounter;
  MOD_Fifo<tUInt8> INST_dut_commandQ;
  MOD_Reg<tUInt32> INST_dut_currAddr;
  MOD_Reg<tUInt32> INST_dut_currColAddr;
  MOD_Reg<tUInt8> INST_dut_currCommand;
  MOD_Reg<tUInt32> INST_dut_currRowAddr;
  MOD_Reg<tUInt8> INST_dut_currState;
  MOD_Reg<tUInt32> INST_dut_cycleCounter;
  MOD_Fifo<tUInt8> INST_dut_inputDataQ;
  MOD_Fifo<tUInt32> INST_dut_instQ;
  MOD_Reg<tUInt8> INST_dut_kernelDone;
  MOD_Reg<tUInt8> INST_dut_kernelStarted;
  MOD_BRAM<tUInt32,tUWide,tUInt8> INST_dut_mem_cells_mem_bank;
  MOD_Fifo<tUInt8> INST_dut_outputDataBuff;
  MOD_Reg<tUWide> INST_dut_rowBuffer;
  MOD_Reg<tUWide> INST_dut_rowMask;
  MOD_Reg<tUInt32> INST_dut_stallCycles;
  MOD_Reg<tUInt8> INST_running;
  MOD_Reg<tUInt8> INST_start_reg;
  MOD_Reg<tUInt8> INST_start_reg_1;
  MOD_Wire<tUInt8> INST_start_reg_2;
  MOD_Wire<tUInt8> INST_start_wire;
  MOD_Reg<tUInt8> INST_state_can_overlap;
  MOD_Reg<tUInt8> INST_state_fired;
  MOD_Wire<tUInt8> INST_state_fired_1;
  MOD_ConfigReg<tUInt8> INST_state_mkFSMstate;
  MOD_Wire<tUInt8> INST_state_overlap_pw;
  MOD_Wire<tUInt8> INST_state_set_pw;
 
 /* Constructor */
 public:
  MOD_mkDRAM_tb(tSimStateHdl simHdl, char const *name, Module *parent);
 
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
  tUInt8 DEF_WILL_FIRE_RL_action_l59c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l55c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l52c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l49c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l46c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l41c9;
  tUInt8 DEF_WILL_FIRE_RL_action_np;
  tUInt8 DEF_WILL_FIRE_RL_action_l37c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l33c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l29c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l22c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l16c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l13c9;
  tUInt8 DEF_dut_currCommand__h1927;
  tUInt8 DEF_dut_currState__h2066;
  tUInt8 DEF_dut_burstCounter_7_ULT_4___d88;
  tUInt8 DEF_dut_addrQ_notEmpty____d77;
  tUInt8 DEF_dut_inputDataQ_notEmpty____d94;
  tUInt8 DEF_dut_commandQ_notEmpty____d73;
  tUInt8 DEF_dut_instQ_notEmpty____d5;
  tUInt8 DEF_decodedCmd__h1233;
  tUInt8 DEF_dut_instQ_first_BITS_18_TO_17_2_EQ_0b0_3_OR_du_ETC___d17;
  tUInt32 DEF_x__h1169;
  tUInt32 DEF_dut_instQ_first____d8;
  tUInt32 DEF_x__h2612;
  tUInt8 DEF_dut_kernelDone__h1040;
  tUInt8 DEF_dut_kernelStarted__h1038;
  tUInt8 DEF_dut_currState_4_EQ_1___d85;
  tUInt8 DEF_dut_currCommand_1_EQ_15___d82;
  tUInt8 DEF_dut_stallCycles_EQ_0___d4;
  tUInt8 DEF_dut_instQ_first_BITS_18_TO_17_2_EQ_0b0___d13;
  tUInt8 DEF_dut_instQ_first_BITS_18_TO_14_EQ_0b1100___d15;
  tUInt8 DEF_dut_instQ_first_BITS_18_TO_14_EQ_0b1111___d10;
  tUInt8 DEF_dut_instQ_first_BITS_18_TO_14_EQ_0b1101___d14;
  tUInt8 DEF_dut_currState_4_EQ_3___d86;
  tUInt8 DEF_dut_instQ_first_BITS_18_TO_14_EQ_0b1010___d20;
  tUInt8 DEF_dut_currState_4_EQ_4___d92;
  tUInt8 DEF_NOT_dut_currCommand_1_EQ_15_2___d83;
  tUInt8 DEF_NOT_dut_burstCounter_7_ULT_4_8___d89;
 
 /* Local definitions */
 private:
  tUWide DEF_x__h2405;
  tUWide DEF_x__h2403;
  tUWide DEF_x__h2191;
  tUInt32 DEF_x__h988;
  tUInt8 DEF_v__h25708;
  tUWide DEF_dut_rowMask_BITS_4091_TO_0___h2442;
  tUWide DEF_d__h2097;
  tUWide DEF_IF_dut_currState_4_EQ_1_5_THEN_dut_mem_cells_m_ETC___d173;
  tUWide DEF_x__h2339;
  tUWide DEF_IF_dut_currCommand_1_EQ_15_2_THEN_dut_rowMask__ETC___d157;
  tUWide DEF_x__h2419;
  tUWide DEF_x__h2776;
  tUWide DEF__0_CONCAT_dut_inputDataQ_first__61___d162;
  tUWide DEF_y__h2404;
  tUWide DEF_rep_d__h2329;
  tUWide DEF_x__h2368;
  tUWide DEF_y__h2369;
 
 /* Rules */
 public:
  void RL_dut_incCycle();
  void RL_dut_decodeCommand();
  void RL_dut_processCommand();
  void RL_start_reg__dreg_update();
  void RL_state_handle_abort();
  void RL_state_fired__dreg_update();
  void RL_state_every();
  void RL_restart();
  void RL_action_l13c9();
  void RL_action_l16c9();
  void RL_action_l22c9();
  void RL_action_l29c9();
  void RL_action_l33c9();
  void RL_action_l37c9();
  void RL_action_np();
  void RL_action_l41c9();
  void RL_action_l46c9();
  void RL_action_l49c9();
  void RL_action_l52c9();
  void RL_action_l55c9();
  void RL_action_l59c9();
  void RL_idle_l12c6();
  void RL_fsm_start();
  void RL_auto_start();
  void RL_auto_finish();
  void __me_check_8();
  void __me_check_9();
  void __me_check_10();
  void __me_check_11();
  void __me_check_12();
  void __me_check_13();
  void __me_check_14();
  void __me_check_15();
  void __me_check_16();
  void __me_check_17();
  void __me_check_18();
  void __me_check_19();
 
 /* Methods */
 public:
 
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
  void dump_VCD(tVCDDumpType dt, unsigned int levels, MOD_mkDRAM_tb &backing);
  void vcd_defs(tVCDDumpType dt, MOD_mkDRAM_tb &backing);
  void vcd_prims(tVCDDumpType dt, MOD_mkDRAM_tb &backing);
};

#endif /* ifndef __mkDRAM_tb_h__ */