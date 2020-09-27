/*
 * tb_max6_taint_analysis_helper.h
 *
 *  Created on: 3 Jun 2018
 *      Author: john
 */

#ifndef TAINT_ANALYSIS_INLINE_PRE_POST_HANDLERS_TB_TA_PRE_POST_HANDLERS_H_
#define TAINT_ANALYSIS_INLINE_PRE_POST_HANDLERS_TB_TA_PRE_POST_HANDLERS_H_

#include <stdint.h>
#include "../../../tb_bunny_private.h"

app_pc tb_raw_get_app_pc(instr_t *app_instr);

void tb_raw_load_tb_ctx(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t tb_reg);

void tb_raw_clear_pre_post_propagate_flags(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where);

void tb_raw_check_post_propagate(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t scratch_reg, reg_id_t scratch_reg2);

void tb_raw_inc_ref(tb_context_t *tb_ctx, void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t label_reg, reg_id_t scratch_reg);

void tb_raw_delete_ref(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg);

void tb_raw_insert_new_ref_and_pre_prop_call_handle(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg);

bool tb_raw_consider_untaint_and_delete(tb_context_t *tb_ctx);

void tb_raw_insert_untaint_and_delete_handle(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg);

void tb_raw_insert_get_new_label_from_1_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, opnd_t *src_opnd, reg_id_t scratch_reg);

void tb_raw_insert_get_new_label_from_2_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, opnd_t *src_opnd, opnd_t *src_opnd2,
        reg_id_t scratch_reg);

void tb_raw_insert_set_untaint_reg(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd, reg_id_t old_reg,
        reg_id_t scratch_reg);

void tb_raw_meet_from_1_src(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t meet_reg, reg_id_t src_reg, reg_id_t scratch_reg);

void tb_raw_meet_from_2_src(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t meet_reg, reg_id_t src_reg, reg_id_t src_reg2,
        reg_id_t scratch_reg);

void tb_raw_insert_prop_reg(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t label_reg, reg_id_t scratch_reg);

void tb_raw_insert_set_untaint_mem(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
         reg_id_t old_reg, reg_id_t scratch_reg);

void tb_raw_insert_prop_mem(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        opnd_t *tl_opnd, reg_id_t label_reg,
        reg_id_t scratch_reg);

/**************************************************************************
 * Apply
 */

void tb_raw_apply_to_1_reg_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dsize, reg_id_t meet_reg,
        reg_id_t scratch_reg, reg_id_t scratch_reg2);

void tb_raw_apply_to_1_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dend, reg_id_t meet_reg,
        reg_id_t meet_reg2, reg_id_t scratch_reg, reg_id_t scratch_reg2);

void tb_raw_apply_to_2_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t dst_reg2, size_t dstart2,
        size_t dsize2, reg_id_t meet_reg, reg_id_t meet_reg2,
        reg_id_t scratch_reg, reg_id_t scratch_reg2);

/********************************************************************************
 * Apply to mem functions.
 */

void tb_raw_apply_to_1_mem_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t meet_reg, reg_id_t scratch_reg,
        reg_id_t scratch_reg2);

void tb_raw_apply_to_1_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dsize, reg_id_t meet_reg,
        reg_id_t meet_reg2, reg_id_t scratch_reg, reg_id_t scratch_reg2);

void tb_raw_apply_to_2_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t dst_reg2, size_t dstart2,
        size_t dsize2, reg_id_t meet_reg, reg_id_t meet_reg2,
        reg_id_t scratch_reg, reg_id_t scratch_reg2);

#endif /* TAINT_ANALYSIS_INLINE_PRE_POST_HANDLERS_TB_TA_PRE_POST_HANDLERS_H_ */
