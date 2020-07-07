/*
 * tb_ta_cc_byt_src_srcdst_srcdst.h
 *
 *  Created on: 16 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_SRCDST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_SRCDST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/************************************************************************
 * SRC SRCDST SRCDST - MEM REG REG
 */

void tb_cc_byt_handle_src_srcdst_srcdst_dreg_1_dreg_1_smem_1_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_srcdst_dreg_2_dreg_2_smem_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_srcdst_dreg_4_dreg_4_smem_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_mem_id1);
void tb_cc_byt_handle_src_srcdst_srcdst_dreg_8_dreg_8_smem_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_mem_id1);

/************************************************************************
 * SRC SRCDST SRCDST - REG REG REG
 */

void tb_cc_byt_handle_src_srcdst_srcdst_dreg_1_dreg_1_sreg_1_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_reg_id3);
void tb_cc_byt_handle_src_srcdst_srcdst_dreg_2_dreg_2_sreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_reg_id3);
void tb_cc_byt_handle_src_srcdst_srcdst_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_reg_id3);
void tb_cc_byt_handle_src_srcdst_srcdst_dreg_8_dreg_8_sreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_reg_id3);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_SRCDST_H_ */
