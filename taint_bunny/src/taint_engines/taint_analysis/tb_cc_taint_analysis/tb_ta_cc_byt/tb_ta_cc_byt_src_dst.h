/*
 * tb_ta_cc_byt_src_dst.h
 *
 *  Created on: 15 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_DST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_DST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/****************************************************************************
 * SRC DST - DMEM SMEM
 */

void tb_cc_byt_handle_src_dst_dmem_1_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_dmem_2_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_dmem_4_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_dmem_8_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_dmem_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id);

/*****************************************************************************
 * SRC DST - DMEM SREG
 */

void tb_cc_byt_handle_src_dst_dmem_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dmem_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dmem_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dmem_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dmem_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);

/*****************************************************************************
 * SRC DST - DREG SREG
 */

void tb_cc_byt_handle_src_dst_dreg_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dreg_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dreg_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dreg_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_dreg_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

/*****************************************************************************
 * SRC DST - DREG SMEM
 */

void tb_cc_byt_handle_src_dst_dreg_1_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_dreg_2_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_dreg_4_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_dreg_8_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_dreg_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

/*****************************************************************************
 * SRC DST - DREG SREG (EXTENSION)
 */

void tb_cc_byt_handle_src_dst_extension_dreg_2_sreg_1(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_1(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_2(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_extension_dreg_8_sreg_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_extension_dreg_16_sreg_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_extension_dreg_16_sreg_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_extension_dreg_2_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_extension_dreg_4_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_extension_dreg_4_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_extension_dreg_8_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_extension_dreg_16_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id);
void tb_cc_byt_handle_src_dst_extension_dreg_16_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id);

/*****************************************************************************
 * (WHOLE)
 */

void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_16(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_16(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_whole_dreg_1_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_2_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_4_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_8_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dreg_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_whole_dmem_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dmem_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dmem_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_src_dst_whole_dmem_1_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dmem_2_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);
void tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id);

/***********************************************************************
 * HIGH Mov
 */

void tb_cc_byt_handle_high_src_dst_dreg_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

void tb_cc_byt_handle_high_src_dst_dreg_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_DST_H_ */
