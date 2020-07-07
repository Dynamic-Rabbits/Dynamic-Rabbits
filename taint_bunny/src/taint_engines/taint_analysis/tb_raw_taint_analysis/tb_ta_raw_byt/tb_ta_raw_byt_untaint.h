/*
 * tb_ta_raw_byt_untaint.h
 *
 *  Created on: 21 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_UNTAINT_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_UNTAINT_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"


void tb_raw_byt_handle_untaint_reg_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info);

void tb_raw_byt_handle_untaint_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_reg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info);

void tb_raw_byt_handle_untaint_mem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_mem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_mem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_mem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info);
void tb_raw_byt_handle_untaint_mem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_UNTAINT_H_ */
