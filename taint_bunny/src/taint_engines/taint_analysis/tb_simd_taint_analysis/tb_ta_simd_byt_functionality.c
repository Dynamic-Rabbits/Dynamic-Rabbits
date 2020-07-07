/*
 * tb_ta_simd]_byt_functionality.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_functionality.h"
#include "../../../tls_access/tb_tls_access.h"
#include "../../../tb_bunny_private.h"
#include "../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

int tb_simd_calculate_partial_size(int total_size, int iteration) {

    int partial_size = total_size - iteration;
    return (partial_size > 4) ? 4 : partial_size;
}

void tb_simd_inc_ref(tb_context_t *tb_ctx, void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg) {

    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));

    if (tb_ctx->insert_simd_new_ref_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        // TODO Optimise branch.
        ub_instrum_check_simd_null_true_case(drcontext, ilist, where,
                label_vectorised_reg, done_label);

        // if label is not null we increment the ref counter.
        tb_ctx->insert_simd_new_ref_func(drcontext, ilist, where,
                label_vectorised_reg, scratch_vectorised_reg,
                scratch_scaler_reg);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

void tb_simd_delete_ref(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg) {

    if (tb_ctx->insert_simd_delete_ref_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        // TODO Optimise branch.
        ub_instrum_check_simd_null_true_case(drcontext, ilist, where,
                label_vectorised_reg, done_label);

        tb_ctx->insert_simd_delete_ref_func(drcontext, ilist, where,
                label_vectorised_reg, scratch_vectorised_reg,
                scratch_scaler_reg);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

void tb_simd_check_post_propagate(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2) {

    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg2));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg2));

    if (instr_hndlr_info->post_prop_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);
        opnd_t mem_opnd = tb_raw_get_tls_raw_slot_opnd(instr_hndlr_info->tb_ctx,
        TB_RAW_SLOT_IDX_PRE_PROP_CALLED);

        // If it is null, simply jump to done label.
        ub_instrum_check_mem_null_true_case(drcontext, ilist, where, NULL,
                &mem_opnd, done_label);

        // The following code is executed if pre_prop_called does not contain a 0 value.

        // We load the tb context in scratch.
        tb_raw_load_tb_ctx(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
                scratch_scaler_reg);

        // We make the call
        tb_simd_insert_post_propagate_func_t post_prop_func =
                (tb_simd_insert_post_propagate_func_t) instr_hndlr_info->pre_prop_func;
        post_prop_func(drcontext, ilist, where, scratch_scaler_reg,
                scratch_vectorised_reg, scratch_vectorised_reg2,
                scratch_scaler_reg2);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

static void tb_simd_handle_pre_prop_call(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2) {

    // Note we assume that the check whether label is not NULL is done prior.
    // This function only *handles* the pre prop call.
    DR_ASSERT(label_vectorised_reg != scratch_vectorised_reg2);
    DR_ASSERT(reg_is_xmm(label_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg2));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg2));

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    // If the pre propagate function is not set, dont even bother
    // including the following code.
    if (instr_hndlr_info->pre_prop_func) {

        // Load the pre prop flag. If it not equal to 0, it means that the pre prop function
        // has been called.

        opnd_t mem_opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx,
        TB_RAW_SLOT_IDX_PRE_PROP_CALLED);

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        // If the pre prop func has been called already, jump to done label.
        ub_instrum_check_mem_null_false_case(drcontext, ilist, where, NULL,
                &mem_opnd, done_label);

        // Set the flag so we dont call the pre propagation function in the future.
        instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) 1, mem_opnd,
                ilist, where, NULL, NULL);

        tb_raw_load_tb_ctx(tb_ctx, drcontext, ilist, where, scratch_scaler_reg);

        tb_simd_insert_pre_propagate_func_t pre_prop_func =
                (tb_simd_insert_pre_propagate_func_t) instr_hndlr_info->pre_prop_func;
        pre_prop_func(drcontext, ilist, where, scratch_scaler_reg,
                label_vectorised_reg, scratch_vectorised_reg2,
                scratch_scaler_reg2);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

void tb_simd_insert_new_ref_and_pre_prop_call_handle(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg,
        reg_id_t scratch_reg2) {

    DR_ASSERT(reg_is_xmm(label_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg2));

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (tb_ctx->insert_simd_new_ref_func || instr_hndlr_info->pre_prop_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        ub_instrum_simd_check_null_true_case(drcontext, ilist, where,
                label_vectorised_reg, done_label);

        if (tb_ctx->insert_simd_new_ref_func) {

            // if label is not null we increment the ref counter.
            tb_ctx->insert_simd_new_ref_func(drcontext, ilist, where,
                    label_vectorised_reg, scratch_vectorised_reg, scratch_reg);
        }

        tb_simd_handle_pre_prop_call(instr_hndlr_info, drcontext, ilist, where,
                label_vectorised_reg, scratch_vectorised_reg, scratch_reg,
                scratch_reg2);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

void tb_simd_insert_untaint_and_delete_handle(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg) {

    DR_ASSERT(reg_is_xmm(label_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (tb_ctx->insert_simd_untaint_reg_func
            || tb_ctx->insert_simd_delete_ref_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        // If there are no labels, just jump to done label
        ub_instrum_simd_check_null_true_case(drcontext, ilist, where,
                label_vectorised_reg, done_label);

        if (tb_ctx->insert_simd_untaint_reg_func)
            tb_ctx->insert_simd_untaint_reg_func(drcontext, ilist, where,
                    label_vectorised_reg, scratch_vectorised_reg,
                    scratch_scaler_reg);

        if (tb_ctx->insert_simd_delete_ref_func)
            tb_ctx->insert_simd_delete_ref_func(drcontext, ilist, where,
                    label_vectorised_reg, scratch_vectorised_reg,
                    scratch_scaler_reg);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

void tb_simd_insert_get_new_label_from_1_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t dst_vectorised_reg, opnd_t *src1_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg) {

    DR_ASSERT(tb_ctx->insert_simd_propogate_func_1dst_1src);
    DR_ASSERT(reg_is_xmm(dst_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(dst_vectorised_reg != scratch_vectorised_reg);
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));

    opnd_t new_src;
    if (is_src_faulty) {

        DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));

        tb_simd_umbra_insert_get_mem(drcontext, ilist, where, pc, src1_opnd,
                scratch_vectorised_reg);
        new_src = opnd_create_reg(scratch_vectorised_reg);
        src1_opnd = &new_src;
    }

    tb_ctx->insert_simd_propogate_func_1dst_1src(drcontext, ilist, where, pc,
            dst_vectorised_reg, src1_opnd, scratch_vectorised_reg,
            scratch_scaler_reg);
}

void tb_simd_insert_get_new_label_from_2_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t dst_vectorised_reg, opnd_t *src1_opnd,
        opnd_t *src2_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_scaler_reg) {

    DR_ASSERT(tb_ctx->insert_simd_propogate_func_1dst_2src);
    DR_ASSERT(dst_vectorised_reg != scratch_vectorised_reg);
    DR_ASSERT(reg_is_xmm(dst_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));

    opnd_t new_src;
    if (is_src_faulty) {

        tb_simd_umbra_insert_get_mem(drcontext, ilist, where, pc, src1_opnd,
                dst_vectorised_reg);
        new_src = opnd_create_reg(dst_vectorised_reg);
        src1_opnd = &new_src;
    }

    tb_ctx->insert_simd_propogate_func_1dst_2src(drcontext, ilist, where, pc,
            dst_vectorised_reg, src1_opnd, src2_opnd, scratch_vectorised_reg,
            scratch_scaler_reg);
}

void tb_simd_insert_set_untaint_reg(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t old_vectorised_reg, reg_id_t scratch_vectorised_reg,
        reg_id_t scaler_scratch_reg) {

    DR_ASSERT(reg_is_xmm(old_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scaler_scratch_reg));

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    tb_simd_arraymap_insert_set_untaint_reg_and_get_old(drcontext, ilist, where,
            tl_opnd, old_vectorised_reg, scratch_vectorised_reg, get_old);

    tb_simd_insert_untaint_and_delete_handle(instr_hndlr_info, drcontext, ilist,
            where, old_vectorised_reg, scratch_vectorised_reg,
            scaler_scratch_reg);
}

void tb_simd_insert_set_untaint_mem(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        opnd_t *tl_opnd, reg_id_t old_vector_reg, reg_id_t vector_scratch_reg,
        reg_id_t scratch_reg) {

    DR_ASSERT(reg_is_xmm(vector_scratch_reg));
    DR_ASSERT(reg_is_xmm(old_vector_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg));

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    tb_simd_umbra_insert_set_untaint_mem_and_get_old(drcontext, ilist, where,
            pc, tl_opnd, old_vector_reg, vector_scratch_reg, get_old);

    tb_simd_insert_untaint_and_delete_handle(instr_hndlr_info, drcontext, ilist,
            where, old_vector_reg, vector_scratch_reg, scratch_reg);
}

void tb_simd_insert_prop_mem(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        opnd_t *tl_opnd, reg_id_t label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg,
        reg_id_t scaler_scratch_reg2) {

    DR_ASSERT(reg_is_xmm(label_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(reg_is_gpr(scaler_scratch_reg2));
    DR_ASSERT(scratch_scaler_reg != scaler_scratch_reg2);
    DR_ASSERT(label_vectorised_reg != scratch_vectorised_reg);

    // Increment ref count of label
    tb_simd_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, label_vectorised_reg, scratch_vectorised_reg,
            scratch_scaler_reg, scaler_scratch_reg2);

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);
    tb_simd_umbra_insert_set_taint_mem_and_get_old(drcontext, ilist, where, pc,
            tl_opnd, label_vectorised_reg, scratch_vectorised_reg, get_old);

    // Call untaint and delete on old label.
    tb_simd_insert_untaint_and_delete_handle(instr_hndlr_info, drcontext, ilist,
            where, scratch_vectorised_reg, label_vectorised_reg,
            scratch_scaler_reg);
}

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
        reg_id_t scaler_scratch_reg, reg_id_t scaler_scratch_reg2) {

    DR_ASSERT(reg_is_xmm(label_vector_reg));
    DR_ASSERT(reg_is_xmm(scratch_vector_reg));
    DR_ASSERT(reg_is_gpr(scaler_scratch_reg2));

    DR_ASSERT(label_vector_reg != scratch_vector_reg);

    // Increment ref count of label
    tb_simd_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, label_vector_reg, scratch_vector_reg,
            scaler_scratch_reg, scaler_scratch_reg2);

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    // Insert the label and associate it with the 2nd src.
    tb_simd_arraymap_insert_set_taint_reg_and_get_old(drcontext, ilist, where,
            tl_opnd, label_vector_reg, scratch_vector_reg, get_old);

    // Call untaint and delete for old label.
    tb_simd_insert_untaint_and_delete_handle(instr_hndlr_info, drcontext, ilist,
            where, scratch_vector_reg, label_vector_reg, scaler_scratch_reg);
}

/******************************************************************************
 * Meet Functionality
 */

static void tb_simd_perform_meet(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t meet_reg, reg_id_t src_reg,
        reg_id_t vector_scratch_reg, reg_id_t faulty_scratch_vector_reg,
        reg_id_t scaler_scratch_reg) {

    DR_ASSERT(start < end);
    DR_ASSERT((end - start) >= 4);
    DR_ASSERT(tb_ctx->insert_simd_meet);
    DR_ASSERT(reg_is_xmm(vector_scratch_reg));
    DR_ASSERT(reg_is_gpr(meet_reg));
    DR_ASSERT(reg_is_gpr(scaler_scratch_reg));

    for (size_t i = start; i < end; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(end, i)
                * sizeof(void *);

        opnd_t src_label_opnd = opnd_create_base_disp(src_reg, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        if (is_src_faulty) {

            DR_ASSERT(reg_is_xmm(faulty_scratch_vector_reg));

            tb_simd_umbra_insert_get_mem(drcontext, ilist, where, pc,
                    &src_label_opnd, faulty_scratch_vector_reg);
            src_label_opnd = opnd_create_reg(faulty_scratch_vector_reg);
        }

        tb_ctx->insert_simd_meet(drcontext, ilist, where, pc, meet_reg,
                &src_label_opnd, vector_scratch_reg, scaler_scratch_reg);
    }
}

void tb_simd_meet_from_1_src(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t meet_reg, reg_id_t src_reg,
        reg_id_t scratch_vector_reg, reg_id_t faulty_scratch_vector_reg,
        reg_id_t scratch_scaler_reg) {

    DR_ASSERT(start < end);
    DR_ASSERT((start - end) >= 4);
    DR_ASSERT(reg_is_gpr(meet_reg));
    DR_ASSERT(reg_is_gpr(src_reg));
    DR_ASSERT(reg_is_xmm(scratch_vector_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));

    // Clear the meet!
    ub_instrum_clear_reg(drcontext, ilist, where, meet_reg);
    tb_simd_perform_meet(tb_ctx, start, end, drcontext, ilist, where, pc,
            is_src_faulty, meet_reg, src_reg, scratch_vector_reg,
            faulty_scratch_vector_reg, scratch_scaler_reg);
}

void tb_simd_meet_from_2_src(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        bool is_src_faulty, reg_id_t meet_reg, reg_id_t src_reg,
        reg_id_t src_reg2, reg_id_t vector_scratch_reg,
        reg_id_t faulty_scratch_vector_reg, reg_id_t scratch_scaler_reg) {

    DR_ASSERT(start < end);
    DR_ASSERT((start - end) >= 4);
    DR_ASSERT(reg_is_gpr(meet_reg));
    DR_ASSERT(reg_is_gpr(src_reg));
    DR_ASSERT(reg_is_xmm(vector_scratch_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));

    ub_instrum_clear_reg(drcontext, ilist, where, meet_reg);

    tb_simd_perform_meet(tb_ctx, start, end, drcontext, ilist, where, pc,
            is_src_faulty, meet_reg, src_reg, vector_scratch_reg,
            faulty_scratch_vector_reg, scratch_scaler_reg);
    tb_simd_perform_meet(tb_ctx, start, end, drcontext, ilist, where, pc, false,
            meet_reg, src_reg2, vector_scratch_reg, faulty_scratch_vector_reg,
            scratch_scaler_reg);
}

static void tb_simd_apply_to_reg_from_1_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, reg_id_t meet_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2) {

    DR_ASSERT(reg_is_gpr(dst_reg));
    DR_ASSERT(reg_is_xmm(meet_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg2));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg2));
    DR_ASSERT(start < size);

    for (size_t i = start; i < size; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(size, i)
                * sizeof(void *);

        opnd_t meet_vectored_label_opnd = opnd_create_reg(meet_vectorised_reg);
        opnd_t dst_label_opnd = opnd_create_base_disp(dst_reg, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, false, scratch_vectorised_reg2,
                &meet_vectored_label_opnd, scratch_vectorised_reg,
                scratch_scaler_reg);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_label_opnd, scratch_vectorised_reg2,
                scratch_vectorised_reg, scratch_scaler_reg,
                scratch_scaler_reg2);
    }
}

static void tb_simd_apply_to_reg_from_2_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_scaler_reg, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2) {

    DR_ASSERT(reg_is_gpr(dst_scaler_reg));
    DR_ASSERT(reg_is_xmm(meet_vectorised_reg));
    DR_ASSERT(reg_is_xmm(meet_vectorised_reg2));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg2));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg2));

    for (size_t i = start; i < end; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(end, i)
                * sizeof(void *);

        opnd_t meet_vectored_label_opnd = opnd_create_reg(meet_vectorised_reg);
        opnd_t meet_vectored_label_opnd2 = opnd_create_reg(
                meet_vectorised_reg2);
        opnd_t dst_label_opnd = opnd_create_base_disp(dst_scaler_reg,
                DR_REG_NULL, 1, sizeof(void *) * i,
                opnd_size_from_bytes(partial_size));

        tb_simd_insert_get_new_label_from_2_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, false, scratch_vectorised_reg2,
                &meet_vectored_label_opnd, &meet_vectored_label_opnd2,
                scratch_vectorised_reg, scratch_scaler_reg);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_label_opnd, scratch_vectorised_reg2,
                scratch_vectorised_reg, scratch_scaler_reg,
                scratch_scaler_reg2);
    }
}

void tb_simd_apply_to_1_reg_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dend,
        reg_id_t meet_vectorised_reg, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2) {

    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg2));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg2));
    DR_ASSERT(reg_is_xmm(meet_vectorised_reg));

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    // Increment the labels in the meet vector
    if (ref_count)
        tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
                scratch_vectorised_reg, scratch_scaler_reg);

    tb_simd_apply_to_reg_from_1_src_helper(instr_hndlr_info, dstart, dend,
            drcontext, ilist, where, pc, dst_reg, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_vectorised_reg2, scratch_scaler_reg,
            scratch_scaler_reg2);

    // Decrement the labels in the meet vector

    if (ref_count)
        tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
                scratch_vectorised_reg, scratch_scaler_reg);
}

void tb_simd_apply_to_1_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dend, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);

    tb_simd_apply_to_reg_from_2_src_helper(instr_hndlr_info, dstart, dend,
            drcontext, ilist, where, pc, dst_reg, meet_vectorised_reg,
            meet_vectorised_reg2, scratch_vectorised_reg,
            scratch_vectorised_reg2, scratch_scaler_reg, scratch_scaler_reg2);

    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);
}

void tb_simd_apply_to_2_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dend, reg_id_t dst_reg2, size_t dstart2,
        size_t dend2, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);

    tb_simd_apply_to_reg_from_2_src_helper(instr_hndlr_info, dstart, dend,
            drcontext, ilist, where, pc, dst_reg, meet_vectorised_reg,
            meet_vectorised_reg2, scratch_vectorised_reg,
            scratch_vectorised_reg2, scratch_scaler_reg, scratch_scaler_reg2);

    tb_simd_apply_to_reg_from_2_src_helper(instr_hndlr_info, dstart2, dend2,
            drcontext, ilist, where, pc, dst_reg2, meet_vectorised_reg,
            meet_vectorised_reg2, scratch_vectorised_reg,
            scratch_vectorised_reg2, scratch_scaler_reg, scratch_scaler_reg2);

    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);
}

/********************************************************************************
 * Apply to mem functions.
 */

void tb_simd_broadcast_meet(void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t destination_vectorised_reg, reg_id_t src_scaler_reg) {

    // TODO Use vbroadcast if AVX is supported?

    DR_ASSERT(reg_is_xmm(destination_vectorised_reg));
    DR_ASSERT(reg_is_gpr(src_scaler_reg));

    opnd_t src_opnd = opnd_create_reg(src_scaler_reg);
    opnd_t dst_opnd = opnd_create_reg(destination_vectorised_reg);
    instr_t *instr = INSTR_CREATE_movd(drcontext, dst_opnd, src_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t imm_opnd = opnd_create_immed_uint(0, opnd_size_from_bytes(1));
    instr = INSTR_CREATE_pshufd(drcontext, dst_opnd, dst_opnd, imm_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

static void tb_simd_apply_to_mem_from_1_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, reg_id_t meet_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2) {

    DR_ASSERT(reg_is_gpr(dst_reg));
    DR_ASSERT(reg_is_xmm(meet_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg2));
    DR_ASSERT(start < size);

    for (size_t i = start; i < size; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(size, i)
                * sizeof(void *);

        opnd_t meet_vectored_label_opnd = opnd_create_reg(meet_vectorised_reg);
        opnd_t dst_label_opnd = opnd_create_base_disp(dst_reg, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, false, scratch_vectorised_reg2,
                &meet_vectored_label_opnd, scratch_vectorised_reg,
                scratch_scaler_reg);

        tb_simd_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where, pc,
                &dst_label_opnd, scratch_vectorised_reg2,
                scratch_vectorised_reg, scratch_scaler_reg,
                scratch_scaler_reg2);
    }
}

static void tb_simd_apply_to_mem_from_2_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_scaler_reg, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2) {

    DR_ASSERT(reg_is_gpr(dst_scaler_reg));
    DR_ASSERT(reg_is_xmm(meet_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));
    DR_ASSERT(start < end);

    int partial_size;

    for (size_t i = start; i < end; i += sizeof(void *)) {

        // Set partial size
        partial_size = tb_simd_calculate_partial_size(end, i) * sizeof(void *);

        opnd_t meet_vectored_label_opnd = opnd_create_reg(meet_vectorised_reg);
        opnd_t meet_vectored_label_opnd2 = opnd_create_reg(
                meet_vectorised_reg2);
        opnd_t dst_label_opnd = opnd_create_base_disp(dst_scaler_reg,
                DR_REG_NULL, 1, sizeof(void *) * i,
                opnd_size_from_bytes(partial_size));

        tb_simd_insert_get_new_label_from_2_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, false, scratch_vectorised_reg2,
                &meet_vectored_label_opnd, &meet_vectored_label_opnd2,
                scratch_vectorised_reg, scratch_scaler_reg);

        tb_simd_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where, pc,
                &dst_label_opnd, scratch_vectorised_reg2,
                scratch_vectorised_reg, scratch_scaler_reg,
                scratch_scaler_reg2);
    }
}

void tb_simd_apply_to_1_mem_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t meet_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);

    tb_simd_apply_to_mem_from_1_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_vectorised_reg2, scratch_scaler_reg,
            scratch_scaler_reg2);

    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
}

void tb_simd_apply_to_1_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dsize,
        reg_id_t meet_vectorised_reg, reg_id_t meet_vectorised_reg2,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (ref_count) {
        tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
                scratch_vectorised_reg, scratch_scaler_reg);
        tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
                scratch_vectorised_reg, scratch_scaler_reg);
    }

    tb_simd_apply_to_mem_from_2_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_vectorised_reg,
            meet_vectorised_reg2, scratch_vectorised_reg,
            scratch_vectorised_reg2, scratch_scaler_reg, scratch_scaler_reg2);

    if (ref_count) {
        tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
                scratch_vectorised_reg, scratch_scaler_reg);
        tb_simd_delete_ref(tb_ctx, drcontext, ilist, where,
                meet_vectorised_reg2, scratch_vectorised_reg,
                scratch_scaler_reg);
    }
}

void tb_simd_apply_to_2_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t dst_reg2, size_t dstart2,
        size_t dsize2, reg_id_t meet_vectorised_reg,
        reg_id_t meet_vectorised_reg2, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_vectorised_reg2, reg_id_t scratch_scaler_reg,
        reg_id_t scratch_scaler_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);

    tb_simd_apply_to_mem_from_2_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_vectorised_reg,
            meet_vectorised_reg2, scratch_vectorised_reg,
            scratch_vectorised_reg2, scratch_scaler_reg, scratch_scaler_reg2);

    tb_simd_apply_to_mem_from_2_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg2, meet_vectorised_reg,
            meet_vectorised_reg2, scratch_vectorised_reg,
            scratch_vectorised_reg2, scratch_scaler_reg, scratch_scaler_reg2);

    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);
}
