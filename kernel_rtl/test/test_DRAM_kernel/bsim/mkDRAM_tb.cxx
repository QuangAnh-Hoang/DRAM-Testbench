/*
 * Generated by Bluespec Compiler (build e4c11968)
 * 
 * On Wed Sep  4 18:50:21 PDT 2024
 * 
 */
#include "bluesim_primitives.h"
#include "mkDRAM_tb.h"


/* String declarations */
static std::string const __str_literal_2("Error: \"DRAM_tb.bsv\", line 20, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l20c9] and\n  [RL_action_l28c9, RL_action_l35c9, RL_action_l39c9, RL_action_l43c9,\n  RL_action_l47c9, RL_action_l51c9, RL_action_l58c9, RL_action_l61c9,\n  RL_action_l64c9, RL_action_l67c9, RL_action_l70c9, RL_action_l77c9,\n  RL_action_l81c9, RL_action_l85c9, RL_action_l89c9] ) fired in the same clock\n  cycle.\n",
					 415u);
static std::string const __str_literal_3("Error: \"DRAM_tb.bsv\", line 28, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l28c9] and\n  [RL_action_l35c9, RL_action_l39c9, RL_action_l43c9, RL_action_l47c9,\n  RL_action_l51c9, RL_action_l58c9, RL_action_l61c9, RL_action_l64c9,\n  RL_action_l67c9, RL_action_l70c9, RL_action_l77c9, RL_action_l81c9,\n  RL_action_l85c9, RL_action_l89c9] ) fired in the same clock cycle.\n",
					 396u);
static std::string const __str_literal_4("Error: \"DRAM_tb.bsv\", line 35, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l35c9] and\n  [RL_action_l39c9, RL_action_l43c9, RL_action_l47c9, RL_action_l51c9,\n  RL_action_l58c9, RL_action_l61c9, RL_action_l64c9, RL_action_l67c9,\n  RL_action_l70c9, RL_action_l77c9, RL_action_l81c9, RL_action_l85c9,\n  RL_action_l89c9] ) fired in the same clock cycle.\n",
					 379u);
static std::string const __str_literal_5("Error: \"DRAM_tb.bsv\", line 39, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l39c9] and\n  [RL_action_l43c9, RL_action_l47c9, RL_action_l51c9, RL_action_l58c9,\n  RL_action_l61c9, RL_action_l64c9, RL_action_l67c9, RL_action_l70c9,\n  RL_action_l77c9, RL_action_l81c9, RL_action_l85c9, RL_action_l89c9] ) fired\n  in the same clock cycle.\n",
					 362u);
static std::string const __str_literal_6("Error: \"DRAM_tb.bsv\", line 43, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l43c9] and\n  [RL_action_l47c9, RL_action_l51c9, RL_action_l58c9, RL_action_l61c9,\n  RL_action_l64c9, RL_action_l67c9, RL_action_l70c9, RL_action_l77c9,\n  RL_action_l81c9, RL_action_l85c9, RL_action_l89c9] ) fired in the same clock\n  cycle.\n",
					 345u);
static std::string const __str_literal_7("Error: \"DRAM_tb.bsv\", line 47, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l47c9] and\n  [RL_action_l51c9, RL_action_l58c9, RL_action_l61c9, RL_action_l64c9,\n  RL_action_l67c9, RL_action_l70c9, RL_action_l77c9, RL_action_l81c9,\n  RL_action_l85c9, RL_action_l89c9] ) fired in the same clock cycle.\n",
					 326u);
static std::string const __str_literal_8("Error: \"DRAM_tb.bsv\", line 51, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l51c9] and\n  [RL_action_l58c9, RL_action_l61c9, RL_action_l64c9, RL_action_l67c9,\n  RL_action_l70c9, RL_action_l77c9, RL_action_l81c9, RL_action_l85c9,\n  RL_action_l89c9] ) fired in the same clock cycle.\n",
					 309u);
static std::string const __str_literal_9("Error: \"DRAM_tb.bsv\", line 58, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l58c9] and\n  [RL_action_l61c9, RL_action_l64c9, RL_action_l67c9, RL_action_l70c9,\n  RL_action_l77c9, RL_action_l81c9, RL_action_l85c9, RL_action_l89c9] ) fired\n  in the same clock cycle.\n",
					 292u);
static std::string const __str_literal_10("Error: \"DRAM_tb.bsv\", line 61, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l61c9] and\n  [RL_action_l64c9, RL_action_l67c9, RL_action_l70c9, RL_action_l77c9,\n  RL_action_l81c9, RL_action_l85c9, RL_action_l89c9] ) fired in the same clock\n  cycle.\n",
					  275u);
static std::string const __str_literal_11("Error: \"DRAM_tb.bsv\", line 64, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l64c9] and\n  [RL_action_l67c9, RL_action_l70c9, RL_action_l77c9, RL_action_l81c9,\n  RL_action_l85c9, RL_action_l89c9] ) fired in the same clock cycle.\n",
					  256u);
static std::string const __str_literal_12("Error: \"DRAM_tb.bsv\", line 67, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l67c9] and\n  [RL_action_l70c9, RL_action_l77c9, RL_action_l81c9, RL_action_l85c9,\n  RL_action_l89c9] ) fired in the same clock cycle.\n",
					  239u);
static std::string const __str_literal_13("Error: \"DRAM_tb.bsv\", line 70, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l70c9] and\n  [RL_action_l77c9, RL_action_l81c9, RL_action_l85c9, RL_action_l89c9] ) fired\n  in the same clock cycle.\n",
					  222u);
static std::string const __str_literal_14("Error: \"DRAM_tb.bsv\", line 77, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l77c9] and\n  [RL_action_l81c9, RL_action_l85c9, RL_action_l89c9] ) fired in the same\n  clock cycle.\n",
					  205u);
static std::string const __str_literal_15("Error: \"DRAM_tb.bsv\", line 81, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l81c9] and\n  [RL_action_l85c9, RL_action_l89c9] ) fired in the same clock cycle.\n",
					  186u);
static std::string const __str_literal_16("Error: \"DRAM_tb.bsv\", line 85, column 9: (R0001)\n  Mutually exclusive rules (from the ME sets [RL_action_l85c9] and\n  [RL_action_l89c9] ) fired in the same clock cycle.\n",
					  169u);
static std::string const __str_literal_1("Read data: %x", 13u);


/* Constructor */
MOD_mkDRAM_tb::MOD_mkDRAM_tb(tSimStateHdl simHdl, char const *name, Module *parent)
  : Module(simHdl, name, parent),
    __clk_handle_0(BAD_CLOCK_HANDLE),
    INST_abort(simHdl, "abort", this, 1u, (tUInt8)0u),
    INST_dut(simHdl, "dut", this),
    INST_running(simHdl, "running", this, 1u, (tUInt8)0u, (tUInt8)0u),
    INST_start_reg(simHdl, "start_reg", this, 1u, (tUInt8)0u, (tUInt8)0u),
    INST_start_reg_1(simHdl, "start_reg_1", this, 1u, (tUInt8)0u, (tUInt8)0u),
    INST_start_reg_2(simHdl, "start_reg_2", this, 1u, (tUInt8)0u),
    INST_start_wire(simHdl, "start_wire", this, 1u, (tUInt8)0u),
    INST_state_can_overlap(simHdl, "state_can_overlap", this, 1u, (tUInt8)1u, (tUInt8)0u),
    INST_state_fired(simHdl, "state_fired", this, 1u, (tUInt8)0u, (tUInt8)0u),
    INST_state_fired_1(simHdl, "state_fired_1", this, 1u, (tUInt8)0u),
    INST_state_mkFSMstate(simHdl, "state_mkFSMstate", this, 5u, (tUInt8)0u, (tUInt8)0u),
    INST_state_overlap_pw(simHdl, "state_overlap_pw", this, 0u),
    INST_state_set_pw(simHdl, "state_set_pw", this, 0u),
    PORT_RST_N((tUInt8)1u)
{
  symbol_count = 69u;
  symbols = new tSym[symbol_count];
  init_symbols_0();
}


/* Symbol init fns */

void MOD_mkDRAM_tb::init_symbols_0()
{
  init_symbol(&symbols[0u], "__me_check_10", SYM_RULE);
  init_symbol(&symbols[1u], "__me_check_11", SYM_RULE);
  init_symbol(&symbols[2u], "__me_check_12", SYM_RULE);
  init_symbol(&symbols[3u], "__me_check_13", SYM_RULE);
  init_symbol(&symbols[4u], "__me_check_14", SYM_RULE);
  init_symbol(&symbols[5u], "__me_check_15", SYM_RULE);
  init_symbol(&symbols[6u], "__me_check_16", SYM_RULE);
  init_symbol(&symbols[7u], "__me_check_17", SYM_RULE);
  init_symbol(&symbols[8u], "__me_check_18", SYM_RULE);
  init_symbol(&symbols[9u], "__me_check_19", SYM_RULE);
  init_symbol(&symbols[10u], "__me_check_5", SYM_RULE);
  init_symbol(&symbols[11u], "__me_check_6", SYM_RULE);
  init_symbol(&symbols[12u], "__me_check_7", SYM_RULE);
  init_symbol(&symbols[13u], "__me_check_8", SYM_RULE);
  init_symbol(&symbols[14u], "__me_check_9", SYM_RULE);
  init_symbol(&symbols[15u], "abort", SYM_MODULE, &INST_abort);
  init_symbol(&symbols[16u], "dut", SYM_MODULE, &INST_dut);
  init_symbol(&symbols[17u], "RL_action_l20c9", SYM_RULE);
  init_symbol(&symbols[18u], "RL_action_l28c9", SYM_RULE);
  init_symbol(&symbols[19u], "RL_action_l35c9", SYM_RULE);
  init_symbol(&symbols[20u], "RL_action_l39c9", SYM_RULE);
  init_symbol(&symbols[21u], "RL_action_l43c9", SYM_RULE);
  init_symbol(&symbols[22u], "RL_action_l47c9", SYM_RULE);
  init_symbol(&symbols[23u], "RL_action_l51c9", SYM_RULE);
  init_symbol(&symbols[24u], "RL_action_l58c9", SYM_RULE);
  init_symbol(&symbols[25u], "RL_action_l61c9", SYM_RULE);
  init_symbol(&symbols[26u], "RL_action_l64c9", SYM_RULE);
  init_symbol(&symbols[27u], "RL_action_l67c9", SYM_RULE);
  init_symbol(&symbols[28u], "RL_action_l70c9", SYM_RULE);
  init_symbol(&symbols[29u], "RL_action_l77c9", SYM_RULE);
  init_symbol(&symbols[30u], "RL_action_l81c9", SYM_RULE);
  init_symbol(&symbols[31u], "RL_action_l85c9", SYM_RULE);
  init_symbol(&symbols[32u], "RL_action_l89c9", SYM_RULE);
  init_symbol(&symbols[33u], "RL_auto_finish", SYM_RULE);
  init_symbol(&symbols[34u], "RL_auto_start", SYM_RULE);
  init_symbol(&symbols[35u], "RL_fsm_start", SYM_RULE);
  init_symbol(&symbols[36u], "RL_idle_l19c6", SYM_RULE);
  init_symbol(&symbols[37u], "RL_restart", SYM_RULE);
  init_symbol(&symbols[38u], "RL_start_reg__dreg_update", SYM_RULE);
  init_symbol(&symbols[39u], "RL_state_every", SYM_RULE);
  init_symbol(&symbols[40u], "RL_state_fired__dreg_update", SYM_RULE);
  init_symbol(&symbols[41u], "RL_state_handle_abort", SYM_RULE);
  init_symbol(&symbols[42u], "running", SYM_MODULE, &INST_running);
  init_symbol(&symbols[43u], "start_reg", SYM_MODULE, &INST_start_reg);
  init_symbol(&symbols[44u], "start_reg_1", SYM_MODULE, &INST_start_reg_1);
  init_symbol(&symbols[45u], "start_reg_2", SYM_MODULE, &INST_start_reg_2);
  init_symbol(&symbols[46u], "start_wire", SYM_MODULE, &INST_start_wire);
  init_symbol(&symbols[47u], "state_can_overlap", SYM_MODULE, &INST_state_can_overlap);
  init_symbol(&symbols[48u], "state_fired", SYM_MODULE, &INST_state_fired);
  init_symbol(&symbols[49u], "state_fired_1", SYM_MODULE, &INST_state_fired_1);
  init_symbol(&symbols[50u], "state_mkFSMstate", SYM_MODULE, &INST_state_mkFSMstate);
  init_symbol(&symbols[51u], "state_overlap_pw", SYM_MODULE, &INST_state_overlap_pw);
  init_symbol(&symbols[52u], "state_set_pw", SYM_MODULE, &INST_state_set_pw);
  init_symbol(&symbols[53u],
	      "WILL_FIRE_RL_action_l20c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l20c9,
	      1u);
  init_symbol(&symbols[54u],
	      "WILL_FIRE_RL_action_l28c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l28c9,
	      1u);
  init_symbol(&symbols[55u],
	      "WILL_FIRE_RL_action_l35c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l35c9,
	      1u);
  init_symbol(&symbols[56u],
	      "WILL_FIRE_RL_action_l39c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l39c9,
	      1u);
  init_symbol(&symbols[57u],
	      "WILL_FIRE_RL_action_l43c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l43c9,
	      1u);
  init_symbol(&symbols[58u],
	      "WILL_FIRE_RL_action_l47c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l47c9,
	      1u);
  init_symbol(&symbols[59u],
	      "WILL_FIRE_RL_action_l51c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l51c9,
	      1u);
  init_symbol(&symbols[60u],
	      "WILL_FIRE_RL_action_l58c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l58c9,
	      1u);
  init_symbol(&symbols[61u],
	      "WILL_FIRE_RL_action_l61c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l61c9,
	      1u);
  init_symbol(&symbols[62u],
	      "WILL_FIRE_RL_action_l64c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l64c9,
	      1u);
  init_symbol(&symbols[63u],
	      "WILL_FIRE_RL_action_l67c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l67c9,
	      1u);
  init_symbol(&symbols[64u],
	      "WILL_FIRE_RL_action_l70c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l70c9,
	      1u);
  init_symbol(&symbols[65u],
	      "WILL_FIRE_RL_action_l77c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l77c9,
	      1u);
  init_symbol(&symbols[66u],
	      "WILL_FIRE_RL_action_l81c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l81c9,
	      1u);
  init_symbol(&symbols[67u],
	      "WILL_FIRE_RL_action_l85c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l85c9,
	      1u);
  init_symbol(&symbols[68u],
	      "WILL_FIRE_RL_action_l89c9",
	      SYM_DEF,
	      &DEF_WILL_FIRE_RL_action_l89c9,
	      1u);
}


/* Rule actions */

void MOD_mkDRAM_tb::RL_start_reg__dreg_update()
{
  tUInt8 DEF_start_reg_2_whas_AND_start_reg_2_wget___d3;
  DEF_start_reg_2_whas_AND_start_reg_2_wget___d3 = INST_start_reg_2.METH_whas() && INST_start_reg_2.METH_wget();
  INST_start_reg_1.METH_write(DEF_start_reg_2_whas_AND_start_reg_2_wget___d3);
}

void MOD_mkDRAM_tb::RL_state_handle_abort()
{
  INST_state_mkFSMstate.METH_write((tUInt8)0u);
}

void MOD_mkDRAM_tb::RL_state_fired__dreg_update()
{
  tUInt8 DEF_state_fired_1_whas__3_AND_state_fired_1_wget__4___d15;
  DEF_state_fired_1_whas__3_AND_state_fired_1_wget__4___d15 = INST_state_fired_1.METH_whas() && INST_state_fired_1.METH_wget();
  INST_state_fired.METH_write(DEF_state_fired_1_whas__3_AND_state_fired_1_wget__4___d15);
}

void MOD_mkDRAM_tb::RL_state_every()
{
  tUInt8 DEF_state_set_pw_whas__6_OR_NOT_state_overlap_pw_w_ETC___d21;
  tUInt8 DEF_state_can_overlap__h4071;
  DEF_state_can_overlap__h4071 = INST_state_can_overlap.METH_read();
  DEF_state_set_pw_whas__6_OR_NOT_state_overlap_pw_w_ETC___d21 = INST_state_set_pw.METH_whas() || (!INST_state_overlap_pw.METH_whas() && DEF_state_can_overlap__h4071);
  INST_state_can_overlap.METH_write(DEF_state_set_pw_whas__6_OR_NOT_state_overlap_pw_w_ETC___d21);
}

void MOD_mkDRAM_tb::RL_restart()
{
  INST_start_wire.METH_wset((tUInt8)1u);
  INST_start_reg_2.METH_wset((tUInt8)1u);
}

void MOD_mkDRAM_tb::RL_action_l20c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)1u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_control(0u);
}

void MOD_mkDRAM_tb::RL_action_l28c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)2u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_control(3407872u);
}

void MOD_mkDRAM_tb::RL_action_l35c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)3u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_action_l39c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)4u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_action_l43c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)5u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_action_l47c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)6u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_action_l51c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)7u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_control(3145728u);
}

void MOD_mkDRAM_tb::RL_action_l58c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)8u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_data((tUInt8)10u);
}

void MOD_mkDRAM_tb::RL_action_l61c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)9u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_data((tUInt8)11u);
}

void MOD_mkDRAM_tb::RL_action_l64c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)10u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_data((tUInt8)12u);
}

void MOD_mkDRAM_tb::RL_action_l67c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)11u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_data((tUInt8)13u);
}

void MOD_mkDRAM_tb::RL_action_l70c9()
{
  INST_state_mkFSMstate.METH_write((tUInt8)12u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  INST_dut.METH_put_mem_control(3407872u);
}

void MOD_mkDRAM_tb::RL_action_l77c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)13u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_action_l81c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)14u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_action_l85c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)15u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_action_l89c9()
{
  tUInt8 DEF_AVMeth_dut_get_data_response;
  INST_state_mkFSMstate.METH_write((tUInt8)16u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
  DEF_AVMeth_dut_get_data_response = INST_dut.METH_get_data_response();
  DEF_v__h27968 = DEF_AVMeth_dut_get_data_response;
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_display(sim_hdl, this, "s,4", &__str_literal_1, DEF_v__h27968);
}

void MOD_mkDRAM_tb::RL_idle_l19c6()
{
  INST_state_mkFSMstate.METH_write((tUInt8)0u);
  INST_state_fired_1.METH_wset((tUInt8)1u);
  INST_state_set_pw.METH_wset();
}

void MOD_mkDRAM_tb::RL_fsm_start()
{
  INST_start_wire.METH_wset((tUInt8)1u);
  INST_start_reg_2.METH_wset((tUInt8)1u);
  INST_start_reg.METH_write((tUInt8)0u);
}

void MOD_mkDRAM_tb::RL_auto_start()
{
  INST_start_reg.METH_write((tUInt8)1u);
  INST_running.METH_write((tUInt8)1u);
}

void MOD_mkDRAM_tb::RL_auto_finish()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    dollar_finish(sim_hdl, "32", 0u);
}

void MOD_mkDRAM_tb::__me_check_5()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l20c9 && ((((((((((((((DEF_WILL_FIRE_RL_action_l28c9 || DEF_WILL_FIRE_RL_action_l35c9) || DEF_WILL_FIRE_RL_action_l39c9) || DEF_WILL_FIRE_RL_action_l43c9) || DEF_WILL_FIRE_RL_action_l47c9) || DEF_WILL_FIRE_RL_action_l51c9) || DEF_WILL_FIRE_RL_action_l58c9) || DEF_WILL_FIRE_RL_action_l61c9) || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_2);
}

void MOD_mkDRAM_tb::__me_check_6()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l28c9 && (((((((((((((DEF_WILL_FIRE_RL_action_l35c9 || DEF_WILL_FIRE_RL_action_l39c9) || DEF_WILL_FIRE_RL_action_l43c9) || DEF_WILL_FIRE_RL_action_l47c9) || DEF_WILL_FIRE_RL_action_l51c9) || DEF_WILL_FIRE_RL_action_l58c9) || DEF_WILL_FIRE_RL_action_l61c9) || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_3);
}

void MOD_mkDRAM_tb::__me_check_7()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l35c9 && ((((((((((((DEF_WILL_FIRE_RL_action_l39c9 || DEF_WILL_FIRE_RL_action_l43c9) || DEF_WILL_FIRE_RL_action_l47c9) || DEF_WILL_FIRE_RL_action_l51c9) || DEF_WILL_FIRE_RL_action_l58c9) || DEF_WILL_FIRE_RL_action_l61c9) || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_4);
}

void MOD_mkDRAM_tb::__me_check_8()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l39c9 && (((((((((((DEF_WILL_FIRE_RL_action_l43c9 || DEF_WILL_FIRE_RL_action_l47c9) || DEF_WILL_FIRE_RL_action_l51c9) || DEF_WILL_FIRE_RL_action_l58c9) || DEF_WILL_FIRE_RL_action_l61c9) || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_5);
}

void MOD_mkDRAM_tb::__me_check_9()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l43c9 && ((((((((((DEF_WILL_FIRE_RL_action_l47c9 || DEF_WILL_FIRE_RL_action_l51c9) || DEF_WILL_FIRE_RL_action_l58c9) || DEF_WILL_FIRE_RL_action_l61c9) || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_6);
}

void MOD_mkDRAM_tb::__me_check_10()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l47c9 && (((((((((DEF_WILL_FIRE_RL_action_l51c9 || DEF_WILL_FIRE_RL_action_l58c9) || DEF_WILL_FIRE_RL_action_l61c9) || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_7);
}

void MOD_mkDRAM_tb::__me_check_11()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l51c9 && ((((((((DEF_WILL_FIRE_RL_action_l58c9 || DEF_WILL_FIRE_RL_action_l61c9) || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_8);
}

void MOD_mkDRAM_tb::__me_check_12()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l58c9 && (((((((DEF_WILL_FIRE_RL_action_l61c9 || DEF_WILL_FIRE_RL_action_l64c9) || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_9);
}

void MOD_mkDRAM_tb::__me_check_13()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l61c9 && ((((((DEF_WILL_FIRE_RL_action_l64c9 || DEF_WILL_FIRE_RL_action_l67c9) || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_10);
}

void MOD_mkDRAM_tb::__me_check_14()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l64c9 && (((((DEF_WILL_FIRE_RL_action_l67c9 || DEF_WILL_FIRE_RL_action_l70c9) || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_11);
}

void MOD_mkDRAM_tb::__me_check_15()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l67c9 && ((((DEF_WILL_FIRE_RL_action_l70c9 || DEF_WILL_FIRE_RL_action_l77c9) || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_12);
}

void MOD_mkDRAM_tb::__me_check_16()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l70c9 && (((DEF_WILL_FIRE_RL_action_l77c9 || DEF_WILL_FIRE_RL_action_l81c9) || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_13);
}

void MOD_mkDRAM_tb::__me_check_17()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l77c9 && ((DEF_WILL_FIRE_RL_action_l81c9 || DEF_WILL_FIRE_RL_action_l85c9) || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_14);
}

void MOD_mkDRAM_tb::__me_check_18()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l81c9 && (DEF_WILL_FIRE_RL_action_l85c9 || DEF_WILL_FIRE_RL_action_l89c9))
      dollar_error(sim_hdl, this, "s", &__str_literal_15);
}

void MOD_mkDRAM_tb::__me_check_19()
{
  if (!(PORT_RST_N == (tUInt8)0u))
    if (DEF_WILL_FIRE_RL_action_l85c9 && DEF_WILL_FIRE_RL_action_l89c9)
      dollar_error(sim_hdl, this, "s", &__str_literal_16);
}


/* Methods */


/* Reset routines */

void MOD_mkDRAM_tb::reset_RST_N(tUInt8 ARG_rst_in)
{
  PORT_RST_N = ARG_rst_in;
  INST_state_mkFSMstate.reset_RST(ARG_rst_in);
  INST_state_fired.reset_RST(ARG_rst_in);
  INST_state_can_overlap.reset_RST(ARG_rst_in);
  INST_start_reg_1.reset_RST(ARG_rst_in);
  INST_start_reg.reset_RST(ARG_rst_in);
  INST_running.reset_RST(ARG_rst_in);
  INST_dut.reset_RST_N(ARG_rst_in);
}


/* Static handles to reset routines */


/* Functions for the parent module to register its reset fns */


/* Functions to set the elaborated clock id */

void MOD_mkDRAM_tb::set_clk_0(char const *s)
{
  __clk_handle_0 = bk_get_or_define_clock(sim_hdl, s);
}


/* State dumping routine */
void MOD_mkDRAM_tb::dump_state(unsigned int indent)
{
  printf("%*s%s:\n", indent, "", inst_name);
  INST_abort.dump_state(indent + 2u);
  INST_dut.dump_state(indent + 2u);
  INST_running.dump_state(indent + 2u);
  INST_start_reg.dump_state(indent + 2u);
  INST_start_reg_1.dump_state(indent + 2u);
  INST_start_reg_2.dump_state(indent + 2u);
  INST_start_wire.dump_state(indent + 2u);
  INST_state_can_overlap.dump_state(indent + 2u);
  INST_state_fired.dump_state(indent + 2u);
  INST_state_fired_1.dump_state(indent + 2u);
  INST_state_mkFSMstate.dump_state(indent + 2u);
  INST_state_overlap_pw.dump_state(indent + 2u);
  INST_state_set_pw.dump_state(indent + 2u);
}


/* VCD dumping routines */

unsigned int MOD_mkDRAM_tb::dump_VCD_defs(unsigned int levels)
{
  vcd_write_scope_start(sim_hdl, inst_name);
  vcd_num = vcd_reserve_ids(sim_hdl, 30u);
  unsigned int num = vcd_num;
  for (unsigned int clk = 0u; clk < bk_num_clocks(sim_hdl); ++clk)
    vcd_add_clock_def(sim_hdl, this, bk_clock_name(sim_hdl, clk), bk_clock_vcd_num(sim_hdl, clk));
  vcd_write_def(sim_hdl, bk_clock_vcd_num(sim_hdl, __clk_handle_0), "CLK", 1u);
  vcd_write_def(sim_hdl, num++, "RST_N", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l20c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l28c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l35c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l39c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l43c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l47c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l51c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l58c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l61c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l64c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l67c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l70c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l77c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l81c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l85c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "WILL_FIRE_RL_action_l89c9", 1u);
  vcd_set_clock(sim_hdl, num, __clk_handle_0);
  vcd_write_def(sim_hdl, num++, "v__h27968", 4u);
  num = INST_abort.dump_VCD_defs(num);
  num = INST_running.dump_VCD_defs(num);
  num = INST_start_reg.dump_VCD_defs(num);
  num = INST_start_reg_1.dump_VCD_defs(num);
  num = INST_start_reg_2.dump_VCD_defs(num);
  num = INST_start_wire.dump_VCD_defs(num);
  num = INST_state_can_overlap.dump_VCD_defs(num);
  num = INST_state_fired.dump_VCD_defs(num);
  num = INST_state_fired_1.dump_VCD_defs(num);
  num = INST_state_mkFSMstate.dump_VCD_defs(num);
  num = INST_state_overlap_pw.dump_VCD_defs(num);
  num = INST_state_set_pw.dump_VCD_defs(num);
  if (levels != 1u)
  {
    unsigned int l = levels == 0u ? 0u : levels - 1u;
    num = INST_dut.dump_VCD_defs(l);
  }
  vcd_write_scope_end(sim_hdl);
  return num;
}

void MOD_mkDRAM_tb::dump_VCD(tVCDDumpType dt, unsigned int levels, MOD_mkDRAM_tb &backing)
{
  vcd_defs(dt, backing);
  vcd_prims(dt, backing);
  if (levels != 1u)
    vcd_submodules(dt, levels - 1u, backing);
}

void MOD_mkDRAM_tb::vcd_defs(tVCDDumpType dt, MOD_mkDRAM_tb &backing)
{
  unsigned int num = vcd_num;
  if (dt == VCD_DUMP_XS)
  {
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 1u);
    vcd_write_x(sim_hdl, num++, 4u);
  }
  else
    if (dt == VCD_DUMP_CHANGES)
    {
      if ((backing.PORT_RST_N) != PORT_RST_N)
      {
	vcd_write_val(sim_hdl, num, PORT_RST_N, 1u);
	backing.PORT_RST_N = PORT_RST_N;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l20c9) != DEF_WILL_FIRE_RL_action_l20c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l20c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l20c9 = DEF_WILL_FIRE_RL_action_l20c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l28c9) != DEF_WILL_FIRE_RL_action_l28c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l28c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l28c9 = DEF_WILL_FIRE_RL_action_l28c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l35c9) != DEF_WILL_FIRE_RL_action_l35c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l35c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l35c9 = DEF_WILL_FIRE_RL_action_l35c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l39c9) != DEF_WILL_FIRE_RL_action_l39c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l39c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l39c9 = DEF_WILL_FIRE_RL_action_l39c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l43c9) != DEF_WILL_FIRE_RL_action_l43c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l43c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l43c9 = DEF_WILL_FIRE_RL_action_l43c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l47c9) != DEF_WILL_FIRE_RL_action_l47c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l47c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l47c9 = DEF_WILL_FIRE_RL_action_l47c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l51c9) != DEF_WILL_FIRE_RL_action_l51c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l51c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l51c9 = DEF_WILL_FIRE_RL_action_l51c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l58c9) != DEF_WILL_FIRE_RL_action_l58c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l58c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l58c9 = DEF_WILL_FIRE_RL_action_l58c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l61c9) != DEF_WILL_FIRE_RL_action_l61c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l61c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l61c9 = DEF_WILL_FIRE_RL_action_l61c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l64c9) != DEF_WILL_FIRE_RL_action_l64c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l64c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l64c9 = DEF_WILL_FIRE_RL_action_l64c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l67c9) != DEF_WILL_FIRE_RL_action_l67c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l67c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l67c9 = DEF_WILL_FIRE_RL_action_l67c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l70c9) != DEF_WILL_FIRE_RL_action_l70c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l70c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l70c9 = DEF_WILL_FIRE_RL_action_l70c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l77c9) != DEF_WILL_FIRE_RL_action_l77c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l77c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l77c9 = DEF_WILL_FIRE_RL_action_l77c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l81c9) != DEF_WILL_FIRE_RL_action_l81c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l81c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l81c9 = DEF_WILL_FIRE_RL_action_l81c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l85c9) != DEF_WILL_FIRE_RL_action_l85c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l85c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l85c9 = DEF_WILL_FIRE_RL_action_l85c9;
      }
      ++num;
      if ((backing.DEF_WILL_FIRE_RL_action_l89c9) != DEF_WILL_FIRE_RL_action_l89c9)
      {
	vcd_write_val(sim_hdl, num, DEF_WILL_FIRE_RL_action_l89c9, 1u);
	backing.DEF_WILL_FIRE_RL_action_l89c9 = DEF_WILL_FIRE_RL_action_l89c9;
      }
      ++num;
      if ((backing.DEF_v__h27968) != DEF_v__h27968)
      {
	vcd_write_val(sim_hdl, num, DEF_v__h27968, 4u);
	backing.DEF_v__h27968 = DEF_v__h27968;
      }
      ++num;
    }
    else
    {
      vcd_write_val(sim_hdl, num++, PORT_RST_N, 1u);
      backing.PORT_RST_N = PORT_RST_N;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l20c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l20c9 = DEF_WILL_FIRE_RL_action_l20c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l28c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l28c9 = DEF_WILL_FIRE_RL_action_l28c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l35c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l35c9 = DEF_WILL_FIRE_RL_action_l35c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l39c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l39c9 = DEF_WILL_FIRE_RL_action_l39c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l43c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l43c9 = DEF_WILL_FIRE_RL_action_l43c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l47c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l47c9 = DEF_WILL_FIRE_RL_action_l47c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l51c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l51c9 = DEF_WILL_FIRE_RL_action_l51c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l58c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l58c9 = DEF_WILL_FIRE_RL_action_l58c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l61c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l61c9 = DEF_WILL_FIRE_RL_action_l61c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l64c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l64c9 = DEF_WILL_FIRE_RL_action_l64c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l67c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l67c9 = DEF_WILL_FIRE_RL_action_l67c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l70c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l70c9 = DEF_WILL_FIRE_RL_action_l70c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l77c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l77c9 = DEF_WILL_FIRE_RL_action_l77c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l81c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l81c9 = DEF_WILL_FIRE_RL_action_l81c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l85c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l85c9 = DEF_WILL_FIRE_RL_action_l85c9;
      vcd_write_val(sim_hdl, num++, DEF_WILL_FIRE_RL_action_l89c9, 1u);
      backing.DEF_WILL_FIRE_RL_action_l89c9 = DEF_WILL_FIRE_RL_action_l89c9;
      vcd_write_val(sim_hdl, num++, DEF_v__h27968, 4u);
      backing.DEF_v__h27968 = DEF_v__h27968;
    }
}

void MOD_mkDRAM_tb::vcd_prims(tVCDDumpType dt, MOD_mkDRAM_tb &backing)
{
  INST_abort.dump_VCD(dt, backing.INST_abort);
  INST_running.dump_VCD(dt, backing.INST_running);
  INST_start_reg.dump_VCD(dt, backing.INST_start_reg);
  INST_start_reg_1.dump_VCD(dt, backing.INST_start_reg_1);
  INST_start_reg_2.dump_VCD(dt, backing.INST_start_reg_2);
  INST_start_wire.dump_VCD(dt, backing.INST_start_wire);
  INST_state_can_overlap.dump_VCD(dt, backing.INST_state_can_overlap);
  INST_state_fired.dump_VCD(dt, backing.INST_state_fired);
  INST_state_fired_1.dump_VCD(dt, backing.INST_state_fired_1);
  INST_state_mkFSMstate.dump_VCD(dt, backing.INST_state_mkFSMstate);
  INST_state_overlap_pw.dump_VCD(dt, backing.INST_state_overlap_pw);
  INST_state_set_pw.dump_VCD(dt, backing.INST_state_set_pw);
}

void MOD_mkDRAM_tb::vcd_submodules(tVCDDumpType dt, unsigned int levels, MOD_mkDRAM_tb &backing)
{
  INST_dut.dump_VCD(dt, levels, backing.INST_dut);
}