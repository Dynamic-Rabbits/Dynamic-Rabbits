/*
 * tb_ta_cc_byt_src_src_dst.h
 *
 *  Created on: 15 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRC_DST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRC_DST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/**************************************************************************************
 * SRC SRC DST - DREG SREG SREG
 */

void tb_cc_byt_handle_src_src_dst_whole_dreg_2_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);

void tb_cc_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);

void tb_cc_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);
void tb_cc_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);

void tb_cc_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);
void tb_cc_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);
void tb_cc_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);


/**************************************************************************************
 * SRC SRC DST - DREG SMEM SREG
 */

void tb_cc_byt_handle_src_src_dst_whole_dreg_2_smem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1, uintptr_t src_reg_id2);

/**************************************************************************************
 * SRC SRC DST - DREG SREG SMEM
 */

void tb_cc_byt_handle_src_src_dst_whole_dreg_4_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_mem_id2);

void tb_cc_byt_handle_src_src_dst_whole_dreg_8_sreg_8_smem_8(
    tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
    uintptr_t src_reg_id1, uintptr_t src_mem_id2);

/**************************************************************************************
 * SRC SRC DST - DMEM SREG SREG (WHOLE)
 */

void tb_cc_byt_handle_src_src_dst_whole_dmem_2_sreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);

void tb_cc_byt_handle_src_src_dst_whole_dmem_4_sreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);

void tb_cc_byt_handle_src_src_dst_whole_dmem_8_sreg_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1, uintptr_t src_reg_id2);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRC_DST_H_ */
