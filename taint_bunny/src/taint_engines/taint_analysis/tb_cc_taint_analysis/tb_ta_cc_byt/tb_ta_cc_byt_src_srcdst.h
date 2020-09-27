/*
 * tb_ta_cc_byt_src_srcdst.h
 *
 *  Created on: 15 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/**************************************************************************************
 * SRC SRCDST - DREG SREG DREG (WHOLE)
 */

void tb_cc_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);

void tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG (WHOLE)
 */

void tb_cc_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_4_smem_4_sreg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id, uintptr_t src_mem_id1);

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM (WHOLE)
 */

void tb_cc_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_8_smem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dmem_16_sreg_16_smem_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);

void tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_1_smem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_1_smem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_1_smem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);

/**************************************************************************************
 * SRC SRCDST - DREG SREG DREG
 */

void tb_cc_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1);

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG
 */

void tb_cc_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_dreg_4_smem_4_sreg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1);

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM
 */

void tb_cc_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dmem_4_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dmem_8_sreg_8_smem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);
void tb_cc_byt_handle_src_srcdst_dmem_16_sreg_16_smem_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_H_ */
