/*
 * tb_ta_cc_byt_punpck.h
 *
 *  Created on: 16 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_PUNPCK_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_PUNPCK_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/*************************************************************
 * PUNPCKLBW SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpcklbw_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_low_punpcklbw_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpcklbw_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_low_punpcklbw_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/*************************************************************
 * PUNPCKLWD SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpcklwd_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKLWD SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpcklwd_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/*************************************************************
 * PUNPCKLDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpckldq_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_low_punpckldq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKLDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpckldq_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_low_punpckldq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/*************************************************************
 * PUNPCKLQDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpcklqdq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKLQDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpcklqdq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhbw_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_high_punpckhbw_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhbw_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_high_punpckhbw_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/*************************************************************
 * PUNPCKHWD SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhwd_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKHWD SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhwd_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/*************************************************************
 * PUNPCKHDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhdq_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

void tb_cc_byt_handle_high_punpckhdq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKHDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhdq_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

void tb_cc_byt_handle_high_punpckhdq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

/*************************************************************
 * PUNPCKHQDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhqdq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id);

/*************************************************************
 * PUNPCKHQDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhqdq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_PUNPCK_H_ */
