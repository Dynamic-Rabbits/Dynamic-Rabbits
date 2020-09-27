/**
 *  @file ib_option.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../options/ib_option.h"

static void test1() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_BARE) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_BARE) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opnd_count_enabled(IB_OPT_BARE) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_addr_gen_mode_enabled(IB_OPT_BARE) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_BARE) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_BARE) == false,
            "ub_ib_option_test - test1 failed...");
}

static void test2() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_CONC_INFO) == true,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_CONC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opnd_count_enabled(IB_OPT_CONC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_CONC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_CONC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_CONC_INFO) == false,
            "ub_ib_option_test - test1 failed...");
}

static void test3() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_OPCODE_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_OPCODE_INFO) == true,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opnd_count_enabled(IB_OPT_OPCODE_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_OPCODE_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_OPCODE_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_OPCODE_INFO) == false,
            "ub_ib_option_test - test1 failed...");
}

static void test4() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_OPND_COUNT_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_OPND_COUNT_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_opnd_count_enabled(IB_OPT_OPND_COUNT_INFO) == true,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_OPND_COUNT_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_OPND_COUNT_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_OPND_COUNT_INFO) == false,
            "ub_ib_option_test - test1 failed...");
}

static void test5() {

    DR_ASSERT_MSG(
            ib_options_is_conc_enabled(IB_OPT_ADDR_GEN_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_opcode_enabled(IB_OPT_ADDR_GEN_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_opnd_count_enabled(IB_OPT_ADDR_GEN_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_ADDR_GEN_INFO) == true,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_flag_enabled(IB_OPT_ADDR_GEN_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_pc_enabled(IB_OPT_ADDR_GEN_INFO) == false,
            "ub_ib_option_test - test1 failed...");
}

static void test6() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_FLAG_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_FLAG_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opnd_count_enabled(IB_OPT_FLAG_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_FLAG_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_FLAG_INFO) == true,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_FLAG_INFO) == false,
            "ub_ib_option_test - test1 failed...");
}

static void test7() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_PC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_PC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opnd_count_enabled(IB_OPT_PC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_addr_gen_mode_enabled(IB_OPT_PC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_PC_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_PC_INFO) == true,
            "ub_ib_option_test - test1 failed...");
}

static void test8() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_ADDR_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_ADDR_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_opnd_count_enabled(IB_OPT_ADDR_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_ADDR_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_ADDR_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_ADDR_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_opnd_enabled(IB_OPT_ADDR_OPND_INFO) == true,
            "ub_ib_option_test - test1 failed...");

}

static void test9() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_REG_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_REG_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_opnd_count_enabled(IB_OPT_REG_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_REG_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_REG_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_ADDR_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_opnd_enabled(IB_OPT_REG_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_reg_opnd_enabled(IB_OPT_REG_OPND_INFO) == true,
            "ub_ib_option_test - test1 failed...");
}

static void test10() {

    DR_ASSERT_MSG(ib_options_is_conc_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_opcode_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_opnd_count_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_gen_mode_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_flag_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(ib_options_is_pc_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_addr_opnd_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_reg_opnd_enabled(IB_OPT_IMMED_OPND_INFO) == false,
            "ub_ib_option_test - test1 failed...");

    DR_ASSERT_MSG(
            ib_options_is_immed_opnd_enabled(IB_OPT_IMMED_OPND_INFO) == true,
            "ub_ib_option_test - test1 failed...");

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
}
