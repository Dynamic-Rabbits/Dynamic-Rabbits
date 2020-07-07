/*
 * tb_ta_simd_byt_xchg.h
 *
 *  Created on: 3 Feb 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_XCHG_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_XCHG_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

void tb_simd_byt_handle_xchg_reg_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_reg_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_reg_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_reg_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info);

/*****************************************************************************
 * XCHG SRCDST SRCDST - DMEM DREG
 */

void tb_simd_byt_handle_xchg_mem_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_mem_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_mem_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_mem_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info);

/*****************************************************************************
 * XCHG SRCDST SRCDST - DREG DMEM
 */

void tb_simd_byt_handle_xchg_reg_1_mem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_reg_2_mem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_reg_4_mem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xchg_reg_8_mem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info);

/********************************************************************
 * SRCDST - DREG
 */

void tb_simd_byt_handle_bswap_dsreg_4(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
         void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t srcdst_reg_id, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_bswap_dsreg_8(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
         void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t srcdst_reg_id, tb_spill_info_t *spill_info);

/********************************************************************
 * SRCDST - DMEM
 */

void tb_simd_byt_handle_bswap_dsmem_4(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_bswap_dsmem_8(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, tb_spill_info_t *spill_info);

/******************************************************************************
 * XADD
 */

void tb_simd_byt_handle_xadd_reg_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xadd_reg_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xadd_reg_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xadd_reg_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xadd_mem_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xadd_mem_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xadd_mem_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

void tb_simd_byt_handle_xadd_mem_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_XCHG_H_ */
