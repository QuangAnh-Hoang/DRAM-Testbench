/*
 * Generated by Bluespec Compiler (build e4c11968)
 * 
 * On Wed Sep  4 18:50:21 PDT 2024
 * 
 */

/* Generation options: */
#ifndef __mkDRAM_tb_h__
#define __mkDRAM_tb_h__

#include "bluesim_types.h"
#include "bs_module.h"
#include "bluesim_primitives.h"
#include "bs_vcd.h"
#include "mkDRAM_Kernel.h"


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
  MOD_mkDRAM_Kernel INST_dut;
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
  tUInt8 DEF_WILL_FIRE_RL_action_l89c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l85c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l81c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l77c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l70c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l67c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l64c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l61c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l58c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l51c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l47c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l43c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l39c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l35c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l28c9;
  tUInt8 DEF_WILL_FIRE_RL_action_l20c9;
 
 /* Local definitions */
 private:
  tUInt8 DEF_v__h27968;
 
 /* Rules */
 public:
  void RL_start_reg__dreg_update();
  void RL_state_handle_abort();
  void RL_state_fired__dreg_update();
  void RL_state_every();
  void RL_restart();
  void RL_action_l20c9();
  void RL_action_l28c9();
  void RL_action_l35c9();
  void RL_action_l39c9();
  void RL_action_l43c9();
  void RL_action_l47c9();
  void RL_action_l51c9();
  void RL_action_l58c9();
  void RL_action_l61c9();
  void RL_action_l64c9();
  void RL_action_l67c9();
  void RL_action_l70c9();
  void RL_action_l77c9();
  void RL_action_l81c9();
  void RL_action_l85c9();
  void RL_action_l89c9();
  void RL_idle_l19c6();
  void RL_fsm_start();
  void RL_auto_start();
  void RL_auto_finish();
  void __me_check_5();
  void __me_check_6();
  void __me_check_7();
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
  void vcd_submodules(tVCDDumpType dt, unsigned int levels, MOD_mkDRAM_tb &backing);
};

#endif /* ifndef __mkDRAM_tb_h__ */