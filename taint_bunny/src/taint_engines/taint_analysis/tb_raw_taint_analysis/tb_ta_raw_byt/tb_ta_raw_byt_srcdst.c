/*
 * tb_ta_raw_byt_srcdst.c
 *
 *      Author: john
 */

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_srcdst.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

/**************************************************************
 * HELPERS
 */

static void tb_raw_byte_handle_srcdst_dreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 2);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[1]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[1], reg_id);

    for (size_t i = 0; i < size; i++) {

        // Get source opnd label
        opnd_t srcdst_opnd = OPND_CREATE_MEMPTR(reg_id, sizeof(void *) * i);

        // Get new reg
        tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[1], &srcdst_opnd,
                spill_info->scaler_regs[2]);

        // Insert to reg
        tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &srcdst_opnd, spill_info->scaler_regs[1],
                spill_info->scaler_regs[2]);
    }

    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[1], spill_info->scaler_regs[2]);
}

static void tb_raw_byte_handle_srcdst_whole_dreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[1]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[1], reg_id);

    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[1],
            reg_id, spill_info->scaler_regs[2]);

    tb_raw_apply_to_1_reg_from_1_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), true, reg_id, 0, size,
            spill_info->scaler_regs[1], spill_info->scaler_regs[2],
            spill_info->scaler_regs[3]);

    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[1], spill_info->scaler_regs[2]);
}

static void tb_raw_byte_handle_srcdst_dmem_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 2);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // We begin the translation here!
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, mem_addr_reg, spill_info->scaler_regs[1]);

    for (size_t i = 0; i < size; i++) {

        // Create dereference operand that access the src taint label
        opnd_t srcdst_label_opnd =
                OPND_CREATE_MEMPTR(mem_addr_reg, sizeof(void *) * i);

        // Get the new label from callback and store it in scratch_reg 2
        tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[1], &srcdst_label_opnd,
                spill_info->scaler_regs[2]);

        tb_raw_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where,
                tb_raw_get_app_pc(app_instr), &srcdst_label_opnd,
                spill_info->scaler_regs[1], spill_info->scaler_regs[2]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[1], spill_info->scaler_regs[2]);
}

static void tb_raw_byte_handle_srcdst_whole_dmem_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // We begin the translation here!
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, mem_addr_reg, spill_info->scaler_regs[1]);

    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[1],
            mem_addr_reg, spill_info->scaler_regs[2]);

    tb_raw_apply_to_1_mem_from_1_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), mem_addr_reg, 0, size,
            spill_info->scaler_regs[1], spill_info->scaler_regs[2],
            spill_info->scaler_regs[3]);

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->scaler_regs[1], spill_info->scaler_regs[2]);

}

/**************************************************************
 * SRCDST DREG
 */

void tb_raw_byt_handle_srcdst_dsreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dreg_sreg(instr_hndlr_info, 1, drcontext, ilist,
            where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_dsreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dreg_sreg(instr_hndlr_info, 2, drcontext, ilist,
            where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_dsreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dreg_sreg(instr_hndlr_info, 4, drcontext, ilist,
            where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_dsreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dreg_sreg(instr_hndlr_info, 8, drcontext, ilist,
            where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_dsreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dreg_sreg(instr_hndlr_info, 16, drcontext, ilist,
            where, app_instr, reg_id, spill_info);
}

/**************************************************************
 * SRCDST DREG (WHOLE)
 */

void tb_raw_byt_handle_srcdst_whole_dsreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 1, drcontext,
            ilist, where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 2, drcontext,
            ilist, where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 4, drcontext,
            ilist, where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 8, drcontext,
            ilist, where, app_instr, reg_id, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, reg_id_t reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 16, drcontext,
            ilist, where, app_instr, reg_id, spill_info);
}

/**************************************************************
 * SRCDST DMEM
 */

void tb_raw_byt_handle_srcdst_dsmem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dmem_smem(instr_hndlr_info, 1, drcontext, ilist,
            where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_dsmem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dmem_smem(instr_hndlr_info, 2, drcontext, ilist,
            where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_dsmem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dmem_smem(instr_hndlr_info, 4, drcontext, ilist,
            where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_dsmem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dmem_smem(instr_hndlr_info, 8, drcontext, ilist,
            where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_dsmem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_dmem_smem(instr_hndlr_info, 16, drcontext, ilist,
            where, app_instr, mem_addr_reg, spill_info);
}

/**************************************************************
 * SRCDST DMEM (WHOLE)
 */

void tb_raw_byt_handle_srcdst_whole_dsmem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 1, drcontext,
            ilist, where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsmem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 2, drcontext,
            ilist, where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsmem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 4, drcontext,
            ilist, where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsmem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 8, drcontext,
            ilist, where, app_instr, mem_addr_reg, spill_info);
}

void tb_raw_byt_handle_srcdst_whole_dsmem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_addr_reg, tb_spill_info_t *spill_info) {

    tb_raw_byte_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 16, drcontext,
            ilist, where, app_instr, mem_addr_reg, spill_info);
}
