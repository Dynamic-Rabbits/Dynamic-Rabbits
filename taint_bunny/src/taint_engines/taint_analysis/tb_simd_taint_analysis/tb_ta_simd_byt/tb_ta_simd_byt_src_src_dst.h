/*
 * tb_ta_simd_byt_src_src_dst.h
 *
 *  Created on: 3 Feb 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRC_SRC_DST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRC_SRC_DST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"


/**************************************************************************************
 * SRC SRC DST - DREG SREG SREG (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dreg_2_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRC DST - DREG SMEM SREG (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dreg_2_smem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRC DST - DREG SREG SMEM (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dreg_4_sreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_mem_id2,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_src_src_dst_whole_dreg_8_sreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_mem_id2,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRC DST - DMEM SREG SREG (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dmem_2_sreg_2_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_src_dst_whole_dmem_4_sreg_4_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_src_dst_whole_dmem_8_sreg_8_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRC_SRC_DST_H_ */
