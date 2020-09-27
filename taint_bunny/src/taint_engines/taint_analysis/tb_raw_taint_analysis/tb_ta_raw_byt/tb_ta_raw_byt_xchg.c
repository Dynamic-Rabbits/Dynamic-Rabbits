/*
 * tb_ta_raw_byt_xchg.c
 *
 *      Author: john
 */

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_xchg.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

/*****************************************************************************
 * XCHG HELPER
 */

static void tb_raw_handle_exchange_reg_reg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t srcdst_label_opnd,
        opnd_t srcdst_label_opnd2, reg_id_t scratch_reg1, reg_id_t scratch_reg2,
        reg_id_t scratch_reg3) {

    // Get new label.
    tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, pc, scratch_reg1, &srcdst_label_opnd, scratch_reg2);

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, scratch_reg1, scratch_reg2);

    // Insert new label. Scratch reg now stores the old label.
    tb_raw_arraymap_insert_set_taint_reg_and_get_old(drcontext, ilist, where,
            &srcdst_label_opnd2, scratch_reg1, scratch_reg2, true);

    opnd_t src2_reg_tl_opnd = opnd_create_reg(scratch_reg2);

    // Get new label
    tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, pc, scratch_reg1, &src2_reg_tl_opnd, scratch_reg3);

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, scratch_reg1, scratch_reg3);

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    // Insert new label. Scratch reg now stores the old label.
    tb_raw_arraymap_insert_set_taint_reg_and_get_old(drcontext, ilist, where,
            &srcdst_label_opnd, scratch_reg1, scratch_reg3, get_old);

    // Scratch and Scratch2 store old labels.
    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg2, scratch_reg1);

    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg3, scratch_reg1);
}

static void tb_raw_handle_exchange_mem_reg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t srcdst_label_opnd,
        opnd_t srcdst_label_opnd2, reg_id_t scratch_reg1, reg_id_t scratch_reg2,
        reg_id_t scratch_reg3) {

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    // Get new label.
    tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, pc, scratch_reg1, &srcdst_label_opnd, scratch_reg2);

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, scratch_reg1, scratch_reg2);

    // Insert new label. Scratch reg now stores the old label.
    tb_raw_arraymap_insert_set_taint_reg_and_get_old(drcontext, ilist, where,
            &srcdst_label_opnd2, scratch_reg1, scratch_reg2, true);

    opnd_t src2_reg_tl_opnd = opnd_create_reg(scratch_reg2);

    // Get new label
    tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, pc, scratch_reg1, &src2_reg_tl_opnd, scratch_reg3);

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, scratch_reg1, scratch_reg3);

    // Insert new label. Scratch reg now stores the old label.

    // Insert new label. Scratch reg now stores the old label.
    tb_raw_umbra_insert_set_taint_mem_and_get_old(drcontext, ilist, where, pc,
            &srcdst_label_opnd, scratch_reg1, scratch_reg3, get_old);

    // Scratch and Scratch2 store old labels.
    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg2, scratch_reg1);

    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg3, scratch_reg1);
}

static void tb_raw_handle_exchange_mem_mem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t srcdst_label_opnd,
        opnd_t srcdst_label_opnd2, reg_id_t scratch_reg1, reg_id_t scratch_reg2,
        reg_id_t scratch_reg3) {

    bool get_old = tb_raw_consider_untaint_and_delete(instr_hndlr_info->tb_ctx);

    // Get new label.
    tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, pc, scratch_reg1, &srcdst_label_opnd, scratch_reg2);

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, scratch_reg1, scratch_reg2);

    // Insert new label. Scratch reg now stores the old label.
    tb_raw_umbra_insert_set_taint_mem_and_get_old(drcontext, ilist, where, pc,
            &srcdst_label_opnd, scratch_reg1, scratch_reg2, true);

    opnd_t src2_reg_tl_opnd = opnd_create_reg(scratch_reg2);

    // Get new label
    tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, pc, scratch_reg1, &src2_reg_tl_opnd, scratch_reg3);

    // Increment ref count of label
    tb_raw_insert_new_ref_and_pre_prop_call_handle(instr_hndlr_info, drcontext,
            ilist, where, scratch_reg1, scratch_reg3);

    // Insert new label. Scratch reg now stores the old label.
    tb_raw_umbra_insert_set_taint_mem_and_get_old(drcontext, ilist, where, pc,
            &srcdst_label_opnd, scratch_reg1, scratch_reg3, get_old);

    // Scratch and Scratch2 store old labels.
    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg2, scratch_reg1);

    tb_raw_insert_untaint_and_delete_handle(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, scratch_reg3, scratch_reg1);
}

static void tb_raw_handle_xchg_reg_reg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 4);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Reg Map:
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2],
            srcdst_reg_id2);

    // we could load label into the register first to avoid xchg propagation, but we will leave it
    // like this for now.

    for (size_t i = 0; i < size; i++) {

        opnd_t srcdst_label_opnd =
        OPND_CREATE_MEMPTR(srcdst_reg_id, sizeof(void *) * i);
        opnd_t srcdst_label_opnd2 =
        OPND_CREATE_MEMPTR(srcdst_reg_id2, sizeof(void *) * i);

        tb_raw_handle_exchange_reg_reg(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), srcdst_label_opnd,
                srcdst_label_opnd2, spill_info->scaler_regs[2],
                spill_info->scaler_regs[3], spill_info->scaler_regs[4]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_raw_handle_xchg_mem_reg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 4);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Reg Map:
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, srcdst_mem_id, spill_info->scaler_regs[3]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    for (size_t i = 0; i < size; i++) {

        opnd_t src_label_opnd =
        OPND_CREATE_MEMPTR(srcdst_mem_id, sizeof(void *) * i);
        opnd_t src_label_opnd2 =
        OPND_CREATE_MEMPTR(srcdst_reg_id, sizeof(void *) * i);

        tb_raw_handle_exchange_mem_reg(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), src_label_opnd,
                src_label_opnd2, spill_info->scaler_regs[2],
                spill_info->scaler_regs[3], spill_info->scaler_regs[4]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_raw_handle_xchg_reg_mem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_mem_reg(instr_hndlr_info, size, drcontext, ilist, where,
            app_instr, srcdst_mem_id, srcdst_reg_id, spill_info);
}

/*****************************************************************************
 * XCHG SRCDST SRCDST - DREG DREG
 */

void tb_raw_byt_handle_xchg_reg_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_reg(instr_hndlr_info, 1, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_reg_id2, spill_info);
}

void tb_raw_byt_handle_xchg_reg_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_reg(instr_hndlr_info, 2, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_reg_id2, spill_info);
}

void tb_raw_byt_handle_xchg_reg_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_reg(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_reg_id2, spill_info);
}

void tb_raw_byt_handle_xchg_reg_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_reg(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_reg_id2, spill_info);
}

/*****************************************************************************
 * XCHG SRCDST SRCDST - DMEM DREG
 */

void tb_raw_byt_handle_xchg_mem_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_mem_reg(instr_hndlr_info, 1, drcontext, ilist, where,
            app_instr, srcdst_mem_id, srcdst_reg_id, spill_info);
}

void tb_raw_byt_handle_xchg_mem_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_mem_reg(instr_hndlr_info, 2, drcontext, ilist, where,
            app_instr, srcdst_mem_id, srcdst_reg_id, spill_info);
}

void tb_raw_byt_handle_xchg_mem_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_mem_reg(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, srcdst_mem_id, srcdst_reg_id, spill_info);
}

void tb_raw_byt_handle_xchg_mem_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t srcdst_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_mem_reg(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, srcdst_mem_id, srcdst_reg_id, spill_info);
}

/*****************************************************************************
 * XCHG SRCDST SRCDST - DREG DMEM
 */

void tb_raw_byt_handle_xchg_reg_1_mem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_mem(instr_hndlr_info, 1, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_mem_id, spill_info);
}

void tb_raw_byt_handle_xchg_reg_2_mem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_mem(instr_hndlr_info, 2, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_mem_id, spill_info);
}

void tb_raw_byt_handle_xchg_reg_4_mem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_mem(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_mem_id, spill_info);
}

void tb_raw_byt_handle_xchg_reg_8_mem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t srcdst_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_xchg_reg_mem(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, srcdst_reg_id, srcdst_mem_id, spill_info);
}

/********************************************************************
 * BSWAP HELPERS
 */

static void tb_raw_handle_bswap_dreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Reg Map:
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    int end = size - 1;

    // we could load label into the register first to avoid xchg propagation, but we will leave it
    // like this for now.

    for (size_t i = 0; i < size / 2; i++) {

        int swap_byte_disp = end - i;
        opnd_t srcdst_label_opnd =
        OPND_CREATE_MEMPTR(srcdst_reg_id, sizeof(void *) * i);
        opnd_t srcdst_label_opnd2 =
        OPND_CREATE_MEMPTR(srcdst_reg_id, sizeof(void *) * swap_byte_disp);

        tb_raw_handle_exchange_reg_reg(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), srcdst_label_opnd,
                srcdst_label_opnd2, spill_info->scaler_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_raw_handle_bswap_dmem_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, srcdst_mem_id, spill_info->scaler_regs[3]);

    int end = size - 1;

    // we could load label into the register first to avoid xchg propagation, but we will leave it
    // like this for now.

    for (size_t i = 0; i < size / 2; i++) {

        int swap_byte_disp = end - i;
        opnd_t srcdst_label_opnd =
        OPND_CREATE_MEMPTR(srcdst_mem_id, sizeof(void *) * i);
        opnd_t srcdst_label_opnd2 =
        OPND_CREATE_MEMPTR(srcdst_mem_id, sizeof(void *) * swap_byte_disp);

        tb_raw_handle_exchange_mem_mem(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), srcdst_label_opnd,
                srcdst_label_opnd2, spill_info->scaler_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[1], spill_info->scaler_regs[2]);
}

/********************************************************************
 * SRCDST - DREG
 */

void tb_raw_byt_handle_bswap_dsreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, tb_spill_info_t *spill_info) {

    tb_raw_handle_bswap_dreg_sreg(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, srcdst_reg_id, spill_info);
}

void tb_raw_byt_handle_bswap_dsreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, tb_spill_info_t *spill_info) {

    tb_raw_handle_bswap_dreg_sreg(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, srcdst_reg_id, spill_info);
}

/********************************************************************
 * SRCDST - DMEM
 */

void tb_raw_byt_handle_bswap_dsmem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, tb_spill_info_t *spill_info) {

    tb_raw_handle_bswap_dmem_smem(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, srcdst_mem_id, spill_info);
}

void tb_raw_byt_handle_bswap_dsmem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, tb_spill_info_t *spill_info) {

    tb_raw_handle_bswap_dmem_smem(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, srcdst_mem_id, spill_info);
}

/******************************************************************************
 * XADD
 */

static void tb_raw_byt_handle_xadd_reg_reg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 5);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Reg Map:
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id2);

    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[3],
            src_reg_id, spill_info->scaler_regs[2]);
    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[4],
            src_reg_id2, spill_info->scaler_regs[2]);

    tb_raw_inc_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[3], spill_info->scaler_regs[5]);
    tb_raw_inc_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[4], spill_info->scaler_regs[5]);

    // Transfer src reg to src2
    for (size_t i = 0; i < size; i++) {

        opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, i * sizeof(void *));
        opnd_t dst_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id2, i * sizeof(void *));

        // Get new label.
        tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[5], &src_tl_opnd,
                spill_info->scaler_regs[2]);

        tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->scaler_regs[5],
                spill_info->scaler_regs[2]);
    }

    // Apply to destination
    tb_raw_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), false, src_reg_id, 0, size,
            spill_info->scaler_regs[3], spill_info->scaler_regs[4],
            spill_info->scaler_regs[2], spill_info->scaler_regs[5]);

    tb_raw_delete_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[3], spill_info->scaler_regs[5]);
    tb_raw_delete_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[4], spill_info->scaler_regs[5]);

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[3], spill_info->scaler_regs[2]);
}

void tb_raw_byt_handle_xadd_reg_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_reg_reg(instr_hndlr_info, 1, drcontext, ilist, where,
            app_instr, src_reg_id, src_reg_id2, spill_info);
}

void tb_raw_byt_handle_xadd_reg_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_reg_reg(instr_hndlr_info, 2, drcontext, ilist, where,
            app_instr, src_reg_id, src_reg_id2, spill_info);
}

void tb_raw_byt_handle_xadd_reg_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_reg_reg(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, src_reg_id, src_reg_id2, spill_info);
}

void tb_raw_byt_handle_xadd_reg_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_reg_reg(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, src_reg_id, src_reg_id2, spill_info);
}

static void tb_raw_byt_handle_xadd_mem_reg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 5);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Reg Map:
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[3]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id2);

    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[3],
            src_mem_id, spill_info->scaler_regs[2]);
    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[4],
            src_reg_id2, spill_info->scaler_regs[2]);

    tb_raw_inc_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[3], spill_info->scaler_regs[5]);
    tb_raw_inc_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[4], spill_info->scaler_regs[5]);

    // Transfer src reg to src2
    for (size_t i = 0; i < size; i++) {

        opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_mem_id, i * sizeof(void *));
        opnd_t dst_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id2, i * sizeof(void *));

        // Get new label.
        tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[5], &src_tl_opnd,
                spill_info->scaler_regs[2]);

        tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->scaler_regs[5],
                spill_info->scaler_regs[2]);
    }

    // Apply to destination
    tb_raw_apply_to_1_mem_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), false, src_mem_id, 0, size,
            spill_info->scaler_regs[3], spill_info->scaler_regs[4],
            spill_info->scaler_regs[2], spill_info->scaler_regs[5]);

    tb_raw_delete_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[3], spill_info->scaler_regs[5]);
    tb_raw_delete_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where,
            spill_info->scaler_regs[4], spill_info->scaler_regs[5]);

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[3], spill_info->scaler_regs[2]);
}

void tb_raw_byt_handle_xadd_mem_1_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_mem_reg(instr_hndlr_info, 1, drcontext, ilist, where,
            app_instr, src_mem_id, src_reg_id2, spill_info);
}

void tb_raw_byt_handle_xadd_mem_2_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_mem_reg(instr_hndlr_info, 2, drcontext, ilist, where,
            app_instr, src_mem_id, src_reg_id2, spill_info);
}

void tb_raw_byt_handle_xadd_mem_4_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_mem_reg(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, src_mem_id, src_reg_id2, spill_info);
}

void tb_raw_byt_handle_xadd_mem_8_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_mem_id, reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_byt_handle_xadd_mem_reg(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, src_mem_id, src_reg_id2, spill_info);
}
