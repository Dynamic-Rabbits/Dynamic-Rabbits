/*
 * tb_ta_simd_byt_src_srcdst.h
 *
 *  Created on: 4 Feb 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRC_SRCDST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRC_SRCDST_H_

/*
 * tb_ta_simd_byt_src_srcdst.h
 *
 *  Created on: 3 Feb 2019
 *      Author: john
 */

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

void tb_simd_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG (WHOLE)
 */

void tb_simd_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_4_smem_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM (WHOLE)
 */

void tb_simd_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dmem_4_sreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dmem_8_sreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dmem_16_sreg_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_src_srcdst_whole_dmem_2_sreg_1_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dmem_4_sreg_1_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_whole_dmem_8_sreg_1_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRCDST - DREG SREG SREG
 */

void tb_simd_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG
 */

void tb_simd_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_4_smem_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM
 */

void tb_simd_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dmem_4_sreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dmem_8_sreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_src_srcdst_dmem_16_sreg_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRC_SRCDST_H_ */
