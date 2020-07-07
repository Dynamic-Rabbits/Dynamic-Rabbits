/*
 * tb_ta_cc_byt_p_src_srcdst.h
 *
 *  Created on: 15 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_P_SRC_SRCDST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_P_SRC_SRCDST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/**************************************************************
 * PW SRC SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/**************************************************************
 * PW SRC SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/**************************************************************
 * PD SRC SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/**************************************************************
 * PD SRC SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/**************************************************************
 * PQ SRC SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/**************************************************************
 * PQ SRC SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/**************************************************************
 * PMADDWD SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pmaddwd_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/**************************************************************
 * PMADDWD SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pmaddwd_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_P_SRC_SRCDST_H_ */
