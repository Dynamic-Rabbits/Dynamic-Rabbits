/*
 * tb_raw_taint_analysis_helper.c
 *
 *      Author: john
 */

#include "../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

#include "../../../tls_access/tb_tls_access.h"
#include "../../../tb_bunny_private.h"
#include "../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>

/**
 * Returns the pc of an instruction. The function accepts NULL as a parameter,
 * which in results in returning NULL.
 */
app_pc tb_raw_get_app_pc(instr_t *app_instr) {

    if (app_instr)
        return instr_get_app_pc(app_instr);
    else
        return NULL;
}

/**
 *  Loads taint bunny context in a register.
 *
 *  @param tb_reg The register to have the context stored in.
 */
void tb_raw_load_tb_ctx(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t tb_reg) {

    opnd_t opnd = opnd_create_reg(tb_reg);
    instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) tb_ctx, opnd, ilist,
            where, NULL, NULL);
}

/**
 * We make use of flags, stored in the thread local storage, to determine whether to
 * call pre and post propagate functions.
 *
 * TODO: Using memory may not be the most efficient way especially if scratch regs
 * are available. Do something about this!
 *
 * The function clears (initialises) the flags.
 */
void tb_raw_clear_pre_post_propagate_flags(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where) {

    // Check if the functions have been initialised. If not, don't even bother including
    // the code.
    if (instr_hndlr_info->pre_prop_func || instr_hndlr_info->post_prop_func) {

        opnd_t mem_opnd = tb_raw_get_tls_raw_slot_opnd(instr_hndlr_info->tb_ctx,
        TB_RAW_SLOT_IDX_PRE_PROP_CALLED);
        instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, mem_opnd,
                ilist, where, NULL, NULL);
    }
}

/**
 * Should be called after all propagation has been completed. It checks whether
 * to trigger the post propagate function.
 */
void tb_raw_check_post_propagate(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t scratch_reg, reg_id_t scratch_reg2) {

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
                scratch_reg2);

        // We make the call
        tb_raw_insert_post_propagate_func_t post_prop_func =
                (tb_raw_insert_post_propagate_func_t) instr_hndlr_info->post_prop_func;
        post_prop_func(drcontext, ilist, where, scratch_reg2, scratch_reg);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

static void tb_raw_handle_pre_prop_call(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg) {

    // Note we assume that the check whether label is not NULL is done prior.
    // This function only *handles* the pre prop call.
    DR_ASSERT(label_reg != scratch_reg);

    // If the pre propagate function is not set, dont even bother
    // including the following code.
    if (instr_hndlr_info->pre_prop_func) {

        // Load the pre prop flag. If it not equal to 0, it means that the pre prop function
        // has been called.

        opnd_t mem_opnd = tb_raw_get_tls_raw_slot_opnd(instr_hndlr_info->tb_ctx,
        TB_RAW_SLOT_IDX_PRE_PROP_CALLED);

        instr_t* restore_label = INSTR_CREATE_label(drcontext);

        ub_instrum_check_mem_null_false_case(drcontext, ilist, where, NULL,
                &mem_opnd, restore_label);

        // Set the flag so we dont call the pre propagation function in the future.
        instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) 1, mem_opnd,
                ilist, where, NULL, NULL);

        // Spill the label
        mem_opnd = tb_raw_get_tls_raw_slot_opnd(instr_hndlr_info->tb_ctx,
        TB_RAW_SLOT_IDX_PRE_POST_PROP_LABEL);

        instr_t *instr;
        opnd_t opnd = opnd_create_reg(label_reg);
        instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, opnd);
        instrlist_meta_preinsert(ilist, where, instr);

        tb_raw_load_tb_ctx(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
                scratch_reg);

        tb_raw_insert_pre_propagate_func_t pre_prop_func =
                (tb_raw_insert_pre_propagate_func_t) instr_hndlr_info->pre_prop_func;
        pre_prop_func(drcontext, ilist, where, scratch_reg, label_reg);

        instrlist_meta_preinsert(ilist, where, restore_label);

        // Restore label reg which was saved to thread local storage.
        mem_opnd = tb_raw_get_tls_raw_slot_opnd(instr_hndlr_info->tb_ctx,
        TB_RAW_SLOT_IDX_PRE_POST_PROP_LABEL);

        opnd = opnd_create_reg(label_reg);
        instr = INSTR_CREATE_mov_ld(drcontext, opnd, mem_opnd);
        instrlist_meta_preinsert(ilist, where, instr);
    }
}

void tb_raw_inc_ref(tb_context_t *tb_ctx, void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t label_reg, reg_id_t scratch_reg) {

    if (tb_ctx->insert_new_ref_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        ub_instrum_check_null_true_case(drcontext, ilist, where, label_reg,
                done_label);

        if (tb_ctx->insert_new_ref_func) {
            // if label is not null we increment the ref counter.
            tb_ctx->insert_new_ref_func(drcontext, ilist, where, label_reg,
                    scratch_reg);
        }

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

void tb_raw_delete_ref(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg) {

    if (tb_ctx->insert_delete_ref_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        ub_instrum_check_null_true_case(drcontext, ilist, where, label_reg,
                done_label);

        tb_ctx->insert_delete_ref_func(drcontext, ilist, where, label_reg,
                scratch_reg);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

/**
 * Increments ref of label, as well as calls pre propagation function call
 * if it hasnt done so already.
 */
void tb_raw_insert_new_ref_and_pre_prop_call_handle(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (tb_ctx->insert_new_ref_func || instr_hndlr_info->pre_prop_func) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);

        ub_instrum_check_null_true_case(drcontext, ilist, where, label_reg,
                done_label);

        if (tb_ctx->insert_new_ref_func) {
            // if label is not null we increment the ref counter.
            tb_ctx->insert_new_ref_func(drcontext, ilist, where, label_reg,
                    scratch_reg);
        }

        tb_raw_handle_pre_prop_call(instr_hndlr_info, drcontext, ilist, where,
                label_reg, scratch_reg);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

bool tb_raw_consider_untaint_and_delete(tb_context_t *tb_ctx) {

    return (tb_ctx->insert_untaint_reg_func || tb_ctx->insert_delete_ref_func);

}

/**
 * Calls the Untaint CB as well as deletes the label.
 */
void tb_raw_insert_untaint_and_delete_handle(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg) {

    if (tb_raw_consider_untaint_and_delete(tb_ctx)) {

        instr_t* done_label = INSTR_CREATE_label(drcontext);
        instr_t* process_label = INSTR_CREATE_label(drcontext);

        ub_instrum_check_null_true_case(drcontext, ilist, where, label_reg,
                done_label);

        instrlist_meta_preinsert(ilist, where, process_label);

        if (tb_ctx->insert_untaint_reg_func)
            tb_ctx->insert_untaint_reg_func(drcontext, ilist, where, label_reg,
                    scratch_reg);

        if (tb_ctx->insert_delete_ref_func)
            tb_ctx->insert_delete_ref_func(drcontext, ilist, where, label_reg,
                    scratch_reg);

        instrlist_meta_preinsert(ilist, where, done_label);
    }
}

void tb_raw_insert_get_new_label_from_1_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, opnd_t *src_opnd, reg_id_t scratch_reg) {

    DR_ASSERT(tb_ctx->insert_propogate_func_1dst_1src);

    tb_ctx->insert_propogate_func_1dst_1src(drcontext, ilist, where, pc,
            dst_reg, src_opnd, scratch_reg);
}

void tb_raw_insert_get_new_label_from_2_src(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, opnd_t *src_opnd, opnd_t *src_opnd2,
        reg_id_t scratch_reg) {

    DR_ASSERT(tb_ctx->insert_propogate_func_1dst_2src);

    tb_ctx->insert_propogate_func_1dst_2src(drcontext, ilist, where, pc,
            dst_reg, src_opnd, src_opnd2, scratch_reg);
}

/**
 * Untaints a reg byte ID.
 *
 */
void tb_raw_insert_set_untaint_reg(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd, reg_id_t old_reg,
        reg_id_t scratch_reg) {

    bool get_old = tb_raw_consider_untaint_and_delete(tb_ctx);

    tb_raw_arraymap_insert_set_untaint_reg_and_get_old(drcontext, ilist, where,
            tl_opnd, old_reg, get_old);

    tb_raw_insert_untaint_and_delete_handle(tb_ctx, drcontext, ilist, where,
            old_reg, scratch_reg);
}

/**
 * Untaints a mem ID.
 */
void tb_raw_insert_set_untaint_mem(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t old_reg, reg_id_t scratch_reg) {

    bool get_old = tb_raw_consider_untaint_and_delete(tb_ctx);

    tb_raw_umbra_insert_set_untaint_mem_and_get_old(drcontext, ilist, where, pc,
            tl_opnd, old_reg, get_old);

    tb_raw_insert_untaint_and_delete_handle(tb_ctx, drcontext, ilist, where,
            old_reg, scratch_reg);
}

/**
 * Propagates taint from 1 source.
 *
 * @param reg_id Contains reg byte ID destination (NOT Clobbered)
 * @param label_reg_xcx Contains 1st src label (Clobbered) (Needs to be REG XCX)
 * @param scratch_reg Scratch (Clobbered)
 */
void tb_raw_insert_prop_reg(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t label_reg, reg_id_t scratch_reg) {

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, label_reg, scratch_reg);

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    // Insert the label and associate it with the 2nd src.
    tb_raw_arraymap_insert_set_taint_reg_and_get_old(drcontext, ilist, where,
            tl_opnd, label_reg, scratch_reg, get_old);

    // Call untaint and delete for old label.
    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg, label_reg);
}

/**
 * Propagates taint from 1 source.
 */
void tb_raw_insert_prop_mem(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        opnd_t *tl_opnd, reg_id_t label_reg, reg_id_t scratch_reg) {

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, label_reg, scratch_reg);

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    tb_raw_umbra_insert_set_taint_mem_and_get_old(drcontext, ilist, where, pc,
            tl_opnd, label_reg, scratch_reg, get_old);

    // Call untaint and delete for old label.
    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg, label_reg);
}

/*****************************************************************************
 * Meet instructions
 */

static void tb_raw_perform_meet(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t meet_reg, reg_id_t src_reg, reg_id_t scratch_reg) {

    DR_ASSERT(start < end);
    opnd_t lowest_opnd = opnd_create_reg(meet_reg);
    DR_ASSERT(tb_ctx->insert_raw_meet);

    for (size_t i = start; i < end; i++) {

        opnd_t label_opnd = OPND_CREATE_MEMPTR(src_reg, sizeof(void *) * i);

        tb_ctx->insert_raw_meet(drcontext, ilist, where, pc, meet_reg,
                &lowest_opnd, &label_opnd, scratch_reg);
    }
}

void tb_raw_meet_from_1_src(tb_context_t *tb_ctx, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t meet_reg, reg_id_t src_reg, reg_id_t scratch_reg) {

    DR_ASSERT(start < end);

    // If we only have one source byte, simply load it in meet reg.
    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, pc, src_reg, 0,
            meet_reg);

    if ((end - start) == 1)
        return;

    tb_raw_perform_meet(tb_ctx, start + 1, end, drcontext, ilist, where, pc,
            meet_reg, src_reg, scratch_reg);
}

void tb_raw_meet_from_2_src(tb_context_t *tb_ctx, size_t start, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t meet_reg, reg_id_t src_reg, reg_id_t src_reg2,
        reg_id_t scratch_reg) {

    DR_ASSERT(start < size);

    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, pc, src_reg, 0,
            meet_reg);

    if ((size - start) != 1)
        tb_raw_perform_meet(tb_ctx, start + 1, size, drcontext, ilist, where, pc,
            meet_reg, src_reg, scratch_reg);

    tb_raw_perform_meet(tb_ctx, start, size, drcontext, ilist, where, pc,
            meet_reg, src_reg2, scratch_reg);
}

static void tb_raw_apply_to_reg_from_1_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, reg_id_t meet_reg, reg_id_t scratch_reg,
        reg_id_t scratch_reg2) {

    DR_ASSERT(start < size);

    opnd_t meet_label_opnd = opnd_create_reg(meet_reg);

    for (size_t i = start; i < size; i++) {

        tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, scratch_reg, &meet_label_opnd,
                scratch_reg2);

        opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg, sizeof(void *) * i);

        tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_opnd, scratch_reg, scratch_reg2);
    }
}

static void tb_raw_apply_to_reg_from_2_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, reg_id_t meet_reg, reg_id_t meet_reg2,
        reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    DR_ASSERT(start < end);

    opnd_t meet_label_opnd = opnd_create_reg(meet_reg);
    opnd_t meet_label_opnd2 = opnd_create_reg(meet_reg2);

    for (size_t i = start; i < end; i++) {

        tb_raw_insert_get_new_label_from_2_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, scratch_reg, &meet_label_opnd,
                &meet_label_opnd2, scratch_reg2);

        opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg, sizeof(void *) * i);

        tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_opnd, scratch_reg, scratch_reg2);
    }
}

void tb_raw_apply_to_1_reg_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dsize, reg_id_t meet_reg,
        reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (ref_count)
        tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);

    tb_raw_apply_to_reg_from_1_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_reg, scratch_reg,
            scratch_reg2);

    if (ref_count)
        tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg,
                scratch_reg);
}

void tb_raw_apply_to_1_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dend, reg_id_t meet_reg,
        reg_id_t meet_reg2, reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (ref_count) {
        tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);
        tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg2, scratch_reg);
    }

    tb_raw_apply_to_reg_from_2_src_helper(instr_hndlr_info, dstart, dend,
            drcontext, ilist, where, pc, dst_reg, meet_reg, meet_reg2,
            scratch_reg, scratch_reg2);

    if (ref_count) {
        tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg,
                scratch_reg);
        tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg2,
                scratch_reg);
    }
}

void tb_raw_apply_to_2_reg_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t dst_reg2, size_t dstart2,
        size_t dsize2, reg_id_t meet_reg, reg_id_t meet_reg2,
        reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);
    tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg2, scratch_reg);

    tb_raw_apply_to_reg_from_2_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_reg, meet_reg2,
            scratch_reg, scratch_reg2);

    tb_raw_apply_to_reg_from_2_src_helper(instr_hndlr_info, dstart2, dsize2,
            drcontext, ilist, where, pc, dst_reg2, meet_reg, meet_reg2,
            scratch_reg, scratch_reg2);

    tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);
    tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg2, scratch_reg);
}

/********************************************************************************
 * Apply to mem functions.
 */

static void tb_raw_apply_to_mem_from_1_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, reg_id_t meet_reg, reg_id_t scratch_reg,
        reg_id_t scratch_reg2) {

    DR_ASSERT(start < size);

    opnd_t meet_label_opnd = opnd_create_reg(meet_reg);

    for (size_t i = start; i < size; i++) {

        tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, scratch_reg, &meet_label_opnd,
                scratch_reg2);

        opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg, sizeof(void *) * i);

        tb_raw_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where, pc,
                &dst_opnd, scratch_reg, scratch_reg2);
    }
}

static void tb_raw_apply_to_mem_from_2_src_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_reg, reg_id_t meet_reg, reg_id_t meet_reg2,
        reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    DR_ASSERT(start < size);

    opnd_t meet_label_opnd = opnd_create_reg(meet_reg);
    opnd_t meet_label_opnd2 = opnd_create_reg(meet_reg2);

    for (size_t i = start; i < size; i++) {

        tb_raw_insert_get_new_label_from_2_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, pc, scratch_reg, &meet_label_opnd,
                &meet_label_opnd2, scratch_reg2);

        opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg, sizeof(void *) * i);

        tb_raw_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where, pc,
                &dst_opnd, scratch_reg, scratch_reg2);
    }
}

void tb_raw_apply_to_1_mem_from_1_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t meet_reg, reg_id_t scratch_reg,
        reg_id_t scratch_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);

    tb_raw_apply_to_mem_from_1_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_reg, scratch_reg,
            scratch_reg2);

    tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);
}

void tb_raw_apply_to_1_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, bool ref_count,
        reg_id_t dst_reg, size_t dstart, size_t dsize, reg_id_t meet_reg,
        reg_id_t meet_reg2, reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (ref_count) {
        tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);
        tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg2, scratch_reg);
    }

    tb_raw_apply_to_mem_from_2_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_reg, meet_reg2,
            scratch_reg, scratch_reg2);

    if (ref_count) {
        tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg,
                scratch_reg);
        tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg2,
                scratch_reg);
    }
}

void tb_raw_apply_to_2_mem_from_2_src(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, reg_id_t dst_reg,
        size_t dstart, size_t dsize, reg_id_t dst_reg2, size_t dstart2,
        size_t dsize2, reg_id_t meet_reg, reg_id_t meet_reg2,
        reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);
    tb_raw_inc_ref(tb_ctx, drcontext, ilist, where, meet_reg2, scratch_reg);

    tb_raw_apply_to_mem_from_2_src_helper(instr_hndlr_info, dstart, dsize,
            drcontext, ilist, where, pc, dst_reg, meet_reg, meet_reg2,
            scratch_reg, scratch_reg2);

    tb_raw_apply_to_mem_from_2_src_helper(instr_hndlr_info, dstart2, dsize2,
            drcontext, ilist, where, pc, dst_reg2, meet_reg, meet_reg2,
            scratch_reg, scratch_reg2);

    tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg, scratch_reg);
    tb_raw_delete_ref(tb_ctx, drcontext, ilist, where, meet_reg2, scratch_reg);
}

