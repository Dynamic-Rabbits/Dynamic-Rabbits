/*
 * tb_ta_raw_byt_src_srcdst_srcdst.h
 *
 *  Created on: 21 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_SRC_SRCDST_SRCDST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_SRC_SRCDST_SRCDST_H_


#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"


/************************************************************************
 * SRC SRCDST SRCDST - MEM REG REG
 */

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_1_dreg_1_smem_1_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_2_dreg_2_smem_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_4_dreg_4_smem_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_8_dreg_8_smem_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info);

/************************************************************************
 * SRC SRCDST SRCDST - REG REG REG
 */

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_1_dreg_1_sreg_1_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_reg_id1,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_2_dreg_2_sreg_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_reg_id1,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_reg_id1,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_src_srcdst_srcdst_dreg_8_dreg_8_sreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id1, reg_id_t srcdst_reg_id2, reg_id_t src_reg_id1,
        tb_spill_info_t *spill_info);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_SRC_SRCDST_SRCDST_H_ */
