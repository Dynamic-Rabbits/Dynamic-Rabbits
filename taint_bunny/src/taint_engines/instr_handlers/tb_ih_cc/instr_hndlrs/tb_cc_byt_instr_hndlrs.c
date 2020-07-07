/*
 * tb_cc_oapp_instr_hndlrs.c
 *
 *      Author: john
 */

#include "tb_cc_byt_instr_hndlrs.h"
#include "tb_cc_execution.h"
#include "../../../taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt.h"

/*****************************************************************************
 * SRC SRCDST
 */

void tb_cc_byt_execute_src_srcdst_dreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1);
}

void tb_cc_byt_execute_src_srcdst_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2);
}

void tb_cc_byt_execute_src_srcdst_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_4_sreg_4_sreg_4);
}

void tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_src_srcdst_dreg_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1);
}

void tb_cc_byt_execute_src_srcdst_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2);
}

void tb_cc_byt_execute_src_srcdst_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_4_smem_4_sreg_4);
}

void tb_cc_byt_execute_src_srcdst_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_src_srcdst_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_src_srcdst_dmem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1);
}

void tb_cc_byt_execute_src_srcdst_dmem_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2);
}

void tb_cc_byt_execute_src_srcdst_dmem_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dmem_4_sreg_4_smem_4);
}

void tb_cc_byt_execute_src_srcdst_dmem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dmem_8_sreg_8_smem_8);
}

void tb_cc_byt_execute_src_srcdst_dmem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dmem_16_sreg_16_smem_16);
}

/*****************************************************************************
 * SRC SRCDST (WHOLE)
 */

void tb_cc_byt_execute_whole_src_srcdst_dreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_4);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_4_smem_4_sreg_4);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_whole_src_srcdst_dmem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1);
}

void tb_cc_byt_execute_whole_src_srcdst_dmem_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2);
}

void tb_cc_byt_execute_whole_src_srcdst_dmem_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_4_smem_4);
}

void tb_cc_byt_execute_whole_src_srcdst_dmem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_8_smem_8);
}

void tb_cc_byt_execute_whole_src_srcdst_dmem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_16_sreg_16_smem_16);
}

/****************************************************************************
 * P SRC SRCDST
 * */

void tb_cc_byt_execute_pb_src_srcdst_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pb_src_srcdst_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_pb_src_srcdst_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pb_src_srcdst_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pw_src_srcdst_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pw_src_srcdst_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_pw_src_srcdst_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pw_src_srcdst_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pd_src_srcdst_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pd_src_srcdst_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_pd_src_srcdst_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pd_src_srcdst_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pq_src_srcdst_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pq_src_srcdst_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_pq_src_srcdst_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pq_src_srcdst_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

/** PMADDWD **/

void tb_cc_byt_execute_pmaddwd_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pmaddwd_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pmaddwd_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_pmaddwd_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pmaddwd_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pmaddwd_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16);
}

/*******************************************************************
 * Same SRC/DST (WHOLE)
 */

void tb_cc_byt_execute_whole_srcdst_dsreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsreg_1);
}

void tb_cc_byt_execute_whole_srcdst_dsreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsreg_2);
}

void tb_cc_byt_execute_whole_srcdst_dsreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsreg_4);
}

void tb_cc_byt_execute_whole_srcdst_dsreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsreg_8);
}

void tb_cc_byt_execute_whole_srcdst_dsreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsreg_16);
}

void tb_cc_byt_execute_srcdst_dsreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsreg_1);
}

void tb_cc_byt_execute_srcdst_dsreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsreg_2);
}

void tb_cc_byt_execute_srcdst_dsreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsreg_4);
}

void tb_cc_byt_execute_srcdst_dsreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsreg_8);
}

void tb_cc_byt_execute_srcdst_dsreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsreg_16);
}

void tb_cc_byt_execute_whole_srcdst_dsmem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsmem_1);
}

void tb_cc_byt_execute_whole_srcdst_dsmem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsmem_2);
}

void tb_cc_byt_execute_whole_srcdst_dsmem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsmem_4);
}

void tb_cc_byt_execute_whole_srcdst_dsmem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsmem_8);
}

void tb_cc_byt_execute_whole_srcdst_dsmem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_whole_dsmem_16);
}

void tb_cc_byt_execute_srcdst_dsmem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsmem_1);
}

void tb_cc_byt_execute_srcdst_dsmem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsmem_2);
}

void tb_cc_byt_execute_srcdst_dsmem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsmem_4);
}

void tb_cc_byt_execute_srcdst_dsmem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsmem_8);
}

void tb_cc_byt_execute_srcdst_dsmem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_srcdst_dsmem_16);
}

/****************************************************************************
 * PUSH
 **/

void tb_cc_byt_execute_push_dmem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_1_sreg_1);
}

void tb_cc_byt_execute_push_dmem_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_2_sreg_2);
}

void tb_cc_byt_execute_push_dmem_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_4_sreg_4);
}

void tb_cc_byt_execute_push_dmem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_8_sreg_8);
}

void tb_cc_byt_execute_push_dmem_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_1_smem_1);
}

void tb_cc_byt_execute_push_dmem_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_2_smem_2);
}

void tb_cc_byt_execute_push_dmem_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_4_smem_4);
}

void tb_cc_byt_execute_push_dmem_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_8_smem_8);
}

/**********************************************************************
 * POP
 **/

void tb_cc_byt_execute_pop_dreg_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_pop_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_1_smem_1);
}

void tb_cc_byt_execute_pop_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_pop_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_2_smem_2);
}

void tb_cc_byt_execute_pop_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_pop_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_4_smem_4);
}

void tb_cc_byt_execute_pop_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_pop_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_8_smem_8);
}

/******************************************************************************
 * SRC SRC DST
 */

void tb_cc_byt_execute_src_src_dst_whole_dreg_2_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_2_sreg_1_sreg_1);
}

void tb_cc_byt_execute_src_src_dst_whole_dreg_2_smem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_2_smem_1_sreg_1);
}

void tb_cc_byt_execute_src_src_dst_whole_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_4);
}

void tb_cc_byt_execute_src_src_dst_whole_dreg_4_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_4_sreg_4_smem_4);
}

void tb_cc_byt_execute_src_src_dst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_src_src_dst_whole_dreg_8_sreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_8_sreg_8_smem_8);
}

/***********************************************************************
 *  SRC SRC DST DST
 **/

void tb_cc_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4);
}

void tb_cc_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4);
}

/** SRC SRC SRC DST DST **/

void tb_cc_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_smem_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_srcdst_dreg_4_dreg_4_smem_4_sreg_4_sreg_4);
}

void tb_cc_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_srcdst_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4);
}

void tb_cc_byt_execute_src_src_dst_dst_dreg_1_dreg_1_smem_1_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_srcdst_dreg_1_dreg_1_smem_1_sreg_1_sreg_1);
}

void tb_cc_byt_execute_src_src_dst_dst_dreg_1_dreg_1_sreg_1_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_srcdst_dreg_1_dreg_1_sreg_1_sreg_1_sreg_1);
}

/******************************************************************************************
 * SRC DST (WHOLE)
 **/

void tb_cc_byt_execute_whole_mov_dmem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_1_sreg_1);
}

void tb_cc_byt_execute_whole_mov_dmem_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_2_sreg_2);

}

void tb_cc_byt_execute_whole_mov_dmem_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_4);
}

void tb_cc_byt_execute_whole_mov_dmem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_8);
}

void tb_cc_byt_execute_whole_mov_dmem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_16_sreg_16);

}

void tb_cc_byt_execute_whole_mov_dreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_1);
}

void tb_cc_byt_execute_whole_mov_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_2);
}

void tb_cc_byt_execute_whole_mov_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_4);
}

void tb_cc_byt_execute_whole_mov_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_8);
}

void tb_cc_byt_execute_whole_mov_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_16_sreg_16);
}

void tb_cc_byt_execute_whole_mov_dreg_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_1_smem_1);
}

void tb_cc_byt_execute_whole_mov_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_2_smem_2);
}

void tb_cc_byt_execute_whole_mov_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_4_smem_4);
}

void tb_cc_byt_execute_whole_mov_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_8_smem_8);
}

void tb_cc_byt_execute_whole_mov_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_16_smem_16);
}

void tb_cc_byt_execute_whole_high_mov_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_src_dst_dreg_16_sreg_16);
}

void tb_cc_byt_execute_whole_high_mov_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_src_dst_dreg_16_smem_16);
}

/** SRC DST **/

void tb_cc_byt_execute_mov_dmem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_1_sreg_1);
}

void tb_cc_byt_execute_mov_dmem_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_2_sreg_2);
}

void tb_cc_byt_execute_mov_dmem_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_4_sreg_4);
}

void tb_cc_byt_execute_mov_dmem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_8_sreg_8);
}

void tb_cc_byt_execute_mov_dmem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_16_sreg_16);
}

void tb_cc_byt_execute_mov_dreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_1_sreg_1);
}

void tb_cc_byt_execute_mov_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
}

void tb_cc_byt_execute_mov_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
}

void tb_cc_byt_execute_mov_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
}

void tb_cc_byt_execute_mov_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_16_sreg_16);
}

void tb_cc_byt_execute_mov_dmem_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_1_smem_1);
}

void tb_cc_byt_execute_mov_dmem_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_2_smem_2);
}

void tb_cc_byt_execute_mov_dmem_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_4_smem_4);
}

void tb_cc_byt_execute_mov_dmem_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_8_smem_8);
}

void tb_cc_byt_execute_mov_dmem_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_16_smem_16);
}

void tb_cc_byt_execute_mov_dreg_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_1_smem_1);
}

void tb_cc_byt_execute_mov_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_2_smem_2);
}

void tb_cc_byt_execute_mov_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_4_smem_4);
}

void tb_cc_byt_execute_mov_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_8_smem_8);
}

void tb_cc_byt_execute_mov_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_16_smem_16);
}

void tb_cc_byt_execute_mov_dmem_8_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dmem_8_sreg_8);
}

void tb_cc_byt_execute_mov_dreg_16_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_8_smem_8);
}

/** LEA **/

void tb_cc_byt_execute_lea_dreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_2);
}

void tb_cc_byt_execute_lea_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_4);
}

void tb_cc_byt_execute_lea_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_base_lea_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_base_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_2);
}

void tb_cc_byt_execute_base_lea_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_base_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_4);
}

void tb_cc_byt_execute_base_lea_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_base_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_8);
}

void tb_cc_byt_execute_index_lea_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_index_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_2);
}

void tb_cc_byt_execute_index_lea_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_index_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_4);
}

void tb_cc_byt_execute_index_lea_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_lea_index_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_8);
}

/** XCHG **/

void tb_cc_byt_execute_xchg_reg_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_1_reg_1);
}

void tb_cc_byt_execute_xchg_reg_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_2_reg_2);

}

void tb_cc_byt_execute_xchg_reg_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_4_reg_4);
}

void tb_cc_byt_execute_xchg_reg_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_8_reg_8);
}

void tb_cc_byt_execute_xchg_reg_1_mem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_1_mem_1);
}

void tb_cc_byt_execute_xchg_reg_2_mem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_2_mem_2);
}

void tb_cc_byt_execute_xchg_reg_4_mem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_4_mem_4);
}

void tb_cc_byt_execute_xchg_reg_8_mem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_reg_8_mem_8);
}

void tb_cc_byt_execute_xchg_mem_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_mem_1_reg_1);
}

void tb_cc_byt_execute_xchg_mem_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_mem_2_reg_2);
}

void tb_cc_byt_execute_xchg_mem_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_mem_4_reg_4);

}

void tb_cc_byt_execute_xchg_mem_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xchg_mem_8_reg_8);
}

void tb_cc_byt_execute_xadd_reg_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_reg_1_reg_1);
}

void tb_cc_byt_execute_xadd_reg_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_reg_2_reg_2);
}

void tb_cc_byt_execute_xadd_reg_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_reg_4_reg_4);
}

void tb_cc_byt_execute_xadd_reg_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_reg_8_reg_8);
}

void tb_cc_byt_execute_xadd_mem_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_mem_1_reg_1);
}

void tb_cc_byt_execute_xadd_mem_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_mem_2_reg_2);
}

void tb_cc_byt_execute_xadd_mem_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_mem_4_reg_4);
}

void tb_cc_byt_execute_xadd_mem_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_xchg_helper(instr_hndlr_info,
            tb_cc_byt_handle_xadd_mem_8_reg_8);
}

/** LEAVE **/

void tb_cc_byt_execute_leave_dreg_4_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_leave_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_4_sreg_4,
            tb_cc_byt_handle_src_dst_dreg_4_smem_4);
}

void tb_cc_byt_execute_leave_dreg_8_sreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_leave_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_dreg_8_sreg_8,
            tb_cc_byt_handle_src_dst_dreg_8_smem_8);
}

/**************************************************************************
 * CONDITIONAL
 **/

void tb_cc_byt_execute_cmovb_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovb_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovb_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovb_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovb_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovb_check_flag()) {

        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovb_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmovb
 */

void tb_cc_byt_execute_cmovnb_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovnb_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovnb_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovnb_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnb_check_flag()) {

        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);

    }
}

void tb_cc_byt_execute_cmovnb_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);

    }
}

void tb_cc_byt_execute_cmovnb_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnb_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);

    }
}

/**********************************************************************************
 * tb_cc_execute_cmovbe
 */

void tb_cc_byt_execute_cmovbe_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovbe_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovbe_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovbe_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovbe_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);

    }
}

void tb_cc_byt_execute_cmovbe_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);

    }
}

/**********************************************************************************
 * tb_cc_execute_cmovnbe
 */

void tb_cc_byt_execute_cmovnbe_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnbe_check_flag()) {

        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovnbe_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovnbe_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovnbe_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);

    }
}

void tb_cc_byt_execute_cmovnbe_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);

    }
}

void tb_cc_byt_execute_cmovnbe_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnbe_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);

    }
}

/**********************************************************************************
 * tb_cc_execute_cmovo
 */

void tb_cc_byt_execute_cmovo_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovo_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmovo_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovo_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovo_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovo_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovo_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovo_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);

    }
}

void tb_cc_byt_execute_cmovo_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovo_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);

    }
}

void tb_cc_byt_execute_cmovo_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovo_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);

    }
}

/**********************************************************************************
 * tb_cc_execute_cmovno
 */

void tb_cc_byt_execute_cmovno_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovno_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovno_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovno_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovno_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovno_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovno_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovno_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);

    }
}

void tb_cc_byt_execute_cmovno_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovno_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);

    }
}

void tb_cc_byt_execute_cmovno_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovno_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);

    }
}

/**********************************************************************************
 * tb_cc_execute_cmovp
 */

void tb_cc_byt_execute_cmovp_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovp_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovp_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovp_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);

    }
}

void tb_cc_byt_execute_cmovp_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);

    }
}

void tb_cc_byt_execute_cmovp_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);

    }
}

/**********************************************************************************
 * tb_cc_execute_cmovnp
 */

void tb_cc_byt_execute_cmovnp_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovnp_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmovnp_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmovnp_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovnp_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);

    }
}

void tb_cc_byt_execute_cmovnp_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovnp_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);

    }
}

/**********************************************************************************
 * tb_cc_execute_cmovs
 */

void tb_cc_byt_execute_cmovs_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovs_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);

    }
}

void tb_cc_byt_execute_cmovs_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovs_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);

    }
}

void tb_cc_byt_execute_cmovs_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovs_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmovs_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovs_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovs_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovs_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovs_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovs_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmovs
 */

void tb_cc_byt_execute_cmovns_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovns_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmovns_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovns_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmovns_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovns_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmovns_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovns_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovns_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovns_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovns_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovns_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmove
 */

void tb_cc_byt_execute_cmove_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmove_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmove_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmove_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmove_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmove_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmove_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmove_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmove_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmove_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmove_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmove_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmovne
 */

void tb_cc_byt_execute_cmovne_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovne_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmovne_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovne_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmovne_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovne_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmovne_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovne_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovne_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovne_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovne_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovne_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmovg
 */

void tb_cc_byt_execute_cmovg_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovg_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmovg_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovg_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmovg_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovg_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmovg_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovg_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovg_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovg_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovg_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovg_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmovge
 */

void tb_cc_byt_execute_cmovge_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovge_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmovge_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovge_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmovge_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovge_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmovge_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovge_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovge_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovge_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovge_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovge_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmovl
 */

void tb_cc_byt_execute_cmovl_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovl_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmovl_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovl_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmovl_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovl_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
    }
}

void tb_cc_byt_execute_cmovl_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovl_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovl_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovl_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovl_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovl_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/**********************************************************************************
 * tb_cc_execute_cmovl
 */

void tb_cc_byt_execute_cmovle_dreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovle_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
    }
}

void tb_cc_byt_execute_cmovle_dreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovle_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
    }
}

void tb_cc_byt_execute_cmovle_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovle_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_sreg_8);

    }
}

void tb_cc_byt_execute_cmovle_dreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovle_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_2_smem_2);
    }
}

void tb_cc_byt_execute_cmovle_dreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovle_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_4_smem_4);
    }
}

void tb_cc_byt_execute_cmovle_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    if (tb_cc_cmovle_check_flag()) {
        tb_cc_execute_src_dst_helper(instr_hndlr_info,
                tb_cc_byt_handle_src_dst_dreg_8_smem_8);
    }
}

/** PUNPCKLBW **/

void tb_cc_byt_execute_punpcklbw_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklbw_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_punpcklbw_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklbw_dreg_8_smem_8_sreg_8);

}

void tb_cc_byt_execute_punpcklbw_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklbw_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpcklbw_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklbw_dreg_16_smem_16_sreg_16);
}

/** PUNPCKLWD **/

void tb_cc_byt_execute_punpcklwd_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklwd_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_punpcklwd_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklwd_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_punpcklwd_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpcklwd_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16);
}

/** OP_PUNPCKLDQ **/

void tb_cc_byt_execute_punpckldq_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpckldq_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_punpckldq_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpckldq_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_punpckldq_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpckldq_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpckldq_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpckldq_dreg_16_smem_16_sreg_16);
}

/** PACKSWB **/

void tb_cc_byt_execute_packswb_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_packswb_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_packswb_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_packswb_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_16_smem_16_sreg_16);
}

/** PACKSDW **/

void tb_cc_byt_execute_packsdw_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_packsdw_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_packsdw_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_packsdw_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pack_dreg_16_smem_16_sreg_16);
}

/** PCMPB **/

void tb_cc_byt_execute_pcmpb_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pcmpb_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pcmpb_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pcmpb_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16);
}

/** PCMPW **/

void tb_cc_byt_execute_pcmpw_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pcmpw_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pcmpw_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pcmpw_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

/** PCMPD **/

void tb_cc_byt_execute_pcmpd_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pcmpd_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pcmpd_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pcmpd_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

/** PCMPQ **/

void tb_cc_byt_execute_pcmpq_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pcmpq_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pcmpq_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pcmpq_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

/** PUNPCKHBW **/

void tb_cc_byt_execute_punpckhbw_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhbw_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_punpckhbw_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhbw_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_punpckhbw_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhbw_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpckhbw_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhbw_dreg_16_smem_16_sreg_16);
}

/** PUNPCKHWD **/

void tb_cc_byt_execute_punpckhwd_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhwd_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_punpckhwd_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhwd_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_punpckhwd_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpckhwd_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16);
}

/** OP_PUNPCKHDQ **/

void tb_cc_byt_execute_punpckhdq_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhdq_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_punpckhdq_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhdq_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_punpckhdq_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhdq_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpckhdq_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhdq_dreg_16_smem_16_sreg_16);
}

// OP_PUNPCKLQDQ:

void tb_cc_byt_execute_punpcklqdq_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklqdq_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpcklqdq_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_low_punpcklqdq_dreg_16_smem_16_sreg_16);
}

// OP_PUNPCKHQDQ:

void tb_cc_byt_execute_punpckhqdq_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhqdq_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_punpckhqdq_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_high_punpckhqdq_dreg_16_smem_16_sreg_16);
}

/* Shift */

void tb_cc_byt_execute_shift_dsmem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1);

}

void tb_cc_byt_execute_shift_dsmem_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_1_smem_2);
}

void tb_cc_byt_execute_shift_dsmem_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_1_smem_4);
}

void tb_cc_byt_execute_shift_dsmem_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_1_smem_8);
}

void tb_cc_byt_execute_shift_dsreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1);
}

void tb_cc_byt_execute_shift_dsreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_1);
}

void tb_cc_byt_execute_shift_dsreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_1);
}

void tb_cc_byt_execute_shift_dsreg_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_1);
}

void tb_cc_byt_execute_shiftd_dreg_2_sreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_1);
}

void tb_cc_byt_execute_shiftd_dreg_4_sreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_1);
}

void tb_cc_byt_execute_shiftd_dreg_8_sreg_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_1);
}

void tb_cc_byt_execute_shiftd_dmem_2_sreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dmem_2_sreg_2_sreg_1);
}

void tb_cc_byt_execute_shiftd_dmem_4_sreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dmem_4_sreg_4_sreg_1);
}

void tb_cc_byt_execute_shiftd_dmem_8_sreg_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_src_dst_whole_dmem_8_sreg_8_sreg_1);
}

/***********************************************************
 *  CMPXCHG**/

void tb_cc_byt_execute_cmpxchg_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_src_dst_dreg_1_sreg_1,
            tb_cc_byt_handle_src_dst_dreg_1_sreg_1);
}

void tb_cc_byt_execute_cmpxchg_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_src_dst_dreg_2_sreg_2,
            tb_cc_byt_handle_src_dst_dreg_2_sreg_2);
}

void tb_cc_byt_execute_cmpxchg_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_src_dst_dreg_4_sreg_4,
            tb_cc_byt_handle_src_dst_dreg_4_sreg_4);
}

void tb_cc_byt_execute_cmpxchg_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 8,
            tb_cc_byt_handle_src_dst_dreg_8_sreg_8,
            tb_cc_byt_handle_src_dst_dreg_8_sreg_8);
}

void tb_cc_byt_execute_cmpxchg_sreg_1_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_src_dst_dreg_1_smem_1,
            tb_cc_byt_handle_src_dst_dmem_1_sreg_1);
}

void tb_cc_byt_execute_cmpxchg_sreg_2_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_src_dst_dreg_2_smem_2,
            tb_cc_byt_handle_src_dst_dmem_2_sreg_2);
}

void tb_cc_byt_execute_cmpxchg_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_src_dst_dreg_4_smem_4,
            tb_cc_byt_handle_src_dst_dmem_4_sreg_4);
}

void tb_cc_byt_execute_cmpxchg_sreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_cmpxchg_helper(instr_hndlr_info, 8,
            tb_cc_byt_handle_src_dst_dreg_8_smem_8,
            tb_cc_byt_handle_src_dst_dmem_8_sreg_8);

}

/*************************************************************
 * MOVZX
 **/

void tb_cc_byt_execute_movzx_dreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_2_sreg_1);
}

void tb_cc_byt_execute_movzx_dreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_1);
}

void tb_cc_byt_execute_movzx_dreg_4_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_2);
}

void tb_cc_byt_execute_movzx_dreg_8_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_8_sreg_4);
}

void tb_cc_byt_execute_movzx_dreg_16_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_16_sreg_4);
}

void tb_cc_byt_execute_movzx_dreg_16_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_16_sreg_8);
}

void tb_cc_byt_execute_movzx_dreg_2_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_2_smem_1);
}

void tb_cc_byt_execute_movzx_dreg_4_smem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_4_smem_1);
}

void tb_cc_byt_execute_movzx_dreg_4_smem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_4_smem_2);
}

void tb_cc_byt_execute_movzx_dreg_8_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_8_smem_4);
}

void tb_cc_byt_execute_movzx_dreg_16_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_16_smem_4);
}

void tb_cc_byt_execute_movzx_dreg_16_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_extension_dreg_16_smem_8);
}

/** PEXTRACT **/

void tb_cc_byt_execute_pextb_dreg_4_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_4);
}

void tb_cc_byt_execute_pextb_dmem_1_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_1_sreg_16);
}

void tb_cc_byt_execute_pextw_dreg_4_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_4);
}

void tb_cc_byt_execute_pextw_dreg_4_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_4);
}

void tb_cc_byt_execute_pextw_dmem_2_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_2_sreg_16);
}

void tb_cc_byt_execute_pextd_dreg_4_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_16);
}

void tb_cc_byt_execute_pextd_dmem_4_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_16);
}

void tb_cc_byt_execute_pextq_dmem_8_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_16);

}

/** BSWAP **/

void tb_cc_byt_execute_bswap_dsreg_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_bswap_dsreg_4);
}

void tb_cc_byt_execute_bswap_dsreg_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_bswap_dsreg_8);
}

void tb_cc_byt_execute_bswap_dsmem_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_bswap_dsmem_4);
}

void tb_cc_byt_execute_bswap_dsmem_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_bswap_dsmem_8);
}

/** PMOVMSK **/

void tb_cc_byt_execute_pmovmsk_dreg_4_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_4);
}

void tb_cc_byt_execute_pmovmsk_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_8);
}

void tb_cc_byt_execute_pmovmsk_dreg_4_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_4);
}

void tb_cc_byt_execute_pmovmsk_dreg_8_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_dst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_8);
}

/** PMINMAX **/

void tb_cc_byt_execute_pminmaxb_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pminmaxb_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pminmaxb_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pminmaxb_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_pminmaxw_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pminmaxw_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pminmaxw_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pminmaxw_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

void tb_cc_byt_execute_pminmaxd_dreg_8_smem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_smem_8_sreg_8);
}

void tb_cc_byt_execute_pminmaxd_dreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_sreg_8_sreg_8);
}

void tb_cc_byt_execute_pminmaxd_dreg_16_smem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16);
}

void tb_cc_byt_execute_pminmaxd_dreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_src_srcdst_helper(instr_hndlr_info,
            tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16);
}

/** REP **/
void tb_cc_byt_execute_rep_movsb(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_movs_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_src_dst_dmem_1_smem_1);
}

void tb_cc_byt_execute_rep_movsw(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_movs_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_src_dst_dmem_2_smem_2);
}

void tb_cc_byt_execute_rep_movsd(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_movs_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_src_dst_dmem_4_smem_4);
}

void tb_cc_byt_execute_rep_movsq(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_movs_helper(instr_hndlr_info, 8,
            tb_cc_byt_handle_src_dst_dmem_8_smem_8);
}

void tb_cc_byt_execute_rep_stosb(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_stos_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_src_dst_dmem_1_sreg_1);
}

void tb_cc_byt_execute_rep_stosw(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_stos_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_src_dst_dmem_2_sreg_2);
}

void tb_cc_byt_execute_rep_stosd(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_stos_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_src_dst_dmem_4_sreg_4);
}

void tb_cc_byt_execute_rep_stosq(tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_rep_stos_helper(instr_hndlr_info, 8,
            tb_cc_byt_handle_src_dst_dmem_8_sreg_8);
}

/** UNTAINT **/

void tb_cc_byt_execute_untaint_dreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_reg_1);
}

void tb_cc_byt_execute_untaint_dreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_reg_2);
}

void tb_cc_byt_execute_untaint_dreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_reg_4);
}

void tb_cc_byt_execute_untaint_dreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_reg_8);
}

void tb_cc_byt_execute_untaint_dreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_reg_16);
}

void tb_cc_execute_untaint_first_2_dregs_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_untaint_reg_1);
}

void tb_cc_execute_untaint_first_2_dregs_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_untaint_reg_2);
}

void tb_cc_execute_untaint_first_2_dregs_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_untaint_reg_4);
}

void tb_cc_execute_untaint_first_2_dregs_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_untaint_reg_8);
}

void tb_cc_execute_untaint_first_2_dregs_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 2,
            tb_cc_byt_handle_untaint_reg_16);
}

void tb_cc_execute_untaint_first_3_dregs_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 3,
            tb_cc_byt_handle_untaint_reg_1);
}

void tb_cc_execute_untaint_first_3_dregs_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 3,
            tb_cc_byt_handle_untaint_reg_2);
}

void tb_cc_execute_untaint_first_3_dregs_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 3,
            tb_cc_byt_handle_untaint_reg_4);
}

void tb_cc_execute_untaint_first_3_dregs_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 3,
            tb_cc_byt_handle_untaint_reg_8);
}

void tb_cc_execute_untaint_first_3_dregs_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 3,
            tb_cc_byt_handle_untaint_reg_16);
}

void tb_cc_execute_untaint_first_4_dregs_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_untaint_reg_1);
}

void tb_cc_execute_untaint_first_4_dregs_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_untaint_reg_2);
}

void tb_cc_execute_untaint_first_4_dregs_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_untaint_reg_4);
}

void tb_cc_execute_untaint_first_4_dregs_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_untaint_reg_8);
}

void tb_cc_execute_untaint_first_4_dregs_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 4,
            tb_cc_byt_handle_untaint_reg_16);
}

void tb_cc_byt_execute_untaint_dmem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_mem_1);
}

void tb_cc_byt_execute_untaint_dmem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_mem_2);
}

void tb_cc_byt_execute_untaint_dmem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_mem_4);
}

void tb_cc_byt_execute_untaint_dmem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_mem_8);
}

void tb_cc_byt_execute_untaint_dmem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_first_n_helper(instr_hndlr_info, 1,
            tb_cc_byt_handle_untaint_mem_16);
}

void tb_cc_byt_execute_untaint_dmem_2nd_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_immed_untaint_helper(instr_hndlr_info,
            tb_cc_byt_handle_untaint_mem_1);
}

void tb_cc_byt_execute_untaint_dmem_2nd_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_immed_untaint_helper(instr_hndlr_info,
            tb_cc_byt_handle_untaint_mem_2);
}

void tb_cc_byt_execute_untaint_dmem_2nd_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_immed_untaint_helper(instr_hndlr_info,
            tb_cc_byt_handle_untaint_mem_4);
}

void tb_cc_byt_execute_untaint_dmem_2nd_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_push_immed_untaint_helper(instr_hndlr_info,
            tb_cc_byt_handle_untaint_mem_8);
}

/** Untaints the 3rd and 4th byte of the 1st operand. **/
void tb_cc_byt_execute_untaint_dreg_untaint_1st_sub_3rd_4th(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info) {

    tb_cc_execute_untaint_sub_byte_helper(instr_hndlr_info, 0, 2, 4,
            tb_cc_byt_handle_untaint_reg_1);
}

/************************************************************
 *  Unsupported Instruction
 **/

void tb_cc_byt_execute_unsupported_instr(void *tb_ctx) {

    tb_cc_execute_unsup_instr(tb_ctx, tb_cc_byt_handle_untaint_reg_1,
            tb_cc_byt_handle_untaint_mem_1);
}

