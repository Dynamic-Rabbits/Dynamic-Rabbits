/*
 * tb_ta_simd_byt_srcdst.h
 *
 *  Created on: 2 Feb 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRCDST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRCDST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

void tb_simd_byt_handle_srcdst_dsreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);

/**************************************************************
 * SRCDST DREG (WHOLE)
 */

void tb_simd_byt_handle_srcdst_whole_dsreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info);

/**************************************************************
 * SRCDST DMEM
 */

void tb_simd_byt_handle_srcdst_dsmem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsmem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsmem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsmem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_dsmem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);

/**************************************************************
 * SRCDST DMEM (WHOLE)
 */

void tb_simd_byt_handle_srcdst_whole_dsmem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsmem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsmem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsmem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);
void tb_simd_byt_handle_srcdst_whole_dsmem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info);


#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_TB_TA_SIMD_BYT_SRCDST_H_ */
