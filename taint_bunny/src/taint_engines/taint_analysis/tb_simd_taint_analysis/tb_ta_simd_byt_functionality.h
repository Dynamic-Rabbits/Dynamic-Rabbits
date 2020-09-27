/*
 * tb_ta_simd_byt_functionality.h
 *
 *  Created on: 3 Feb 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_FUNCTIONALITY_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_FUNCTIONALITY_H_

#include <stdint.h>
#include "../../../tb_bunny_private.h"

int tb_simd_calculate_partial_size(int total_size, int iteration);

void tb_simd_inc_ref(tb_context_t *tb_ctx, void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

void tb_simd_delete_ref(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

void tb_simd_check_post_propagate(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2);

void tb_simd_insert_new_ref_and_pre_prop_call_handle(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg,
        reg_id_t scratch_reg2);

void tb_simd_insert_untaint_and_delete_handle(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

void tb_simd_insert_get_new_label_from_1_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t dst_vectorised_reg, opnd_t *src1_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

void tb_simd_insert_get_new_label_from_2_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t dst_vectorised_reg, opnd_t *src1_opnd,
        opnd_t *src2_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_scaler_reg);

void tb_simd_insert_set_untaint_reg(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t old_reg, reg_id_t vector_scratch_reg,
        reg_id_t scaler_scratch_reg);

void tb_simd_insert_set_untaint_mem(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        opnd_t *tl_opnd, reg_id_t old_vector_reg, reg_id_t vector_scratch_reg,
        reg_id_t scratch_reg);

void tb_simd_insert_prop_mem(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        opnd_t *tl_opnd, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg,
        reg_id_t scaler_scratch_reg2);
/**
 * Propagates taint from 1 source.
 *
 * @param reg_id Contains reg byte ID destination (NOT Clobbered)
 * @param label_reg_xcx Contains 1st src label (Clobbered) (Needs to be REG XCX)
 * @param scratch_reg Scratch (Clobbered)
 */
void tb_simd_insert_prop_reg(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t label_vector_reg, reg_id_t scratch_vector_reg,
        reg_id_t scaler_scratch_reg, reg_id_t scaler_scratch_reg2);

/******************************************************************************
 * Meet Functionality
 */

void tb_simd_meet_from_1_src(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t meet_reg, reg_id_t src_reg,
        reg_id_t scratch_vector_reg, reg_id_t faulty_scratch_vector_reg,
        reg_id_t scratch_scaler_reg);

void tb_simd_meet_from_2_src(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t meet_reg, reg_id_t src_reg,
        reg_id_t src_reg2, reg_id_t vector_scratch_reg,
        reg_id_t faulty_scratch_vector_reg, reg_id_t scratch_scaler_reg);

void tb_simd_apply_to_1_reg_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dend,
        reg_id_t meet_vectorised_reg, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2);

void tb_simd_apply_to_1_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dend, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2);

void tb_simd_apply_to_2_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dend, reg_id_t dst_reg2, size_t dstart2,
        size_t dend2, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2);

/********************************************************************************
 * Apply to mem functions.
 */

void tb_simd_broadcast_meet(void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t destination_vectorised_reg, reg_id_t src_scaler_reg);

void tb_simd_apply_to_1_mem_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t meet_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2);

void tb_simd_apply_to_1_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dsize,
        reg_id_t meet_vectorised_reg, reg_id_t meet_vectorised_reg2,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2);

void tb_simd_apply_to_2_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t dst_reg2, size_t dstart2,
        size_t dsize2, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_SIMD_TAINT_ANALYSIS_TB_TA_SIMD_BYT_FUNCTIONALITY_H_ */
