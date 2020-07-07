/*
 * tb_ta_simd_byt_pack.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_pack.h"
#include "../tb_ta_simd_byt_functionality.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_punpck.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

static void tb_simd_handle_packx_propagation(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        bool is_src_faulty, reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), is_src_faulty,
            spill_info->scaler_regs[3], src_reg_id, spill_info->xmm_regs[0],
            spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    reg_id_t meet_reg2 = src_reg_id; // We can clobber src as it is no longer needed.
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), false, meet_reg2,
            srcdst_reg_id, spill_info->xmm_regs[1], spill_info->xmm_regs[2],
            spill_info->scaler_regs[2]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    int dest_pos = size / 2;

    tb_simd_inc_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->xmm_regs[3], spill_info->scaler_regs[3]);
    tb_simd_inc_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where, spill_info->xmm_regs[1],
            spill_info->xmm_regs[3], spill_info->scaler_regs[3]);

    tb_simd_apply_to_1_reg_from_1_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), false, srcdst_reg_id, 0, dest_pos,
            spill_info->xmm_regs[0], spill_info->xmm_regs[2],
            spill_info->xmm_regs[3], spill_info->scaler_regs[2],
            spill_info->scaler_regs[3]);

    tb_simd_apply_to_1_reg_from_1_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), false, srcdst_reg_id, dest_pos, size,
            spill_info->xmm_regs[1], spill_info->xmm_regs[2],
            spill_info->xmm_regs[3], spill_info->scaler_regs[2],
            spill_info->scaler_regs[3]);

    tb_simd_delete_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->xmm_regs[3], spill_info->scaler_regs[3]);
    tb_simd_delete_ref(instr_hndlr_info->tb_ctx, drcontext, ilist, where, spill_info->xmm_regs[1],
            spill_info->xmm_regs[3], spill_info->scaler_regs[3]);

    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_simd_handle_packx_src_srcdst_dreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 3);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    tb_simd_handle_packx_propagation(instr_hndlr_info, size, drcontext, ilist,
            where, app_instr, false, srcdst_reg_id, src_reg_id, spill_info);
}

static void tb_simd_handle_packx_src_srcdst_dreg_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 3);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[3]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    tb_simd_handle_packx_propagation(instr_hndlr_info, size, drcontext, ilist,
            where, app_instr, true, srcdst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_pack_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_packx_src_srcdst_dreg_sreg(instr_hndlr_info, 8, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_pack_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_packx_src_srcdst_dreg_sreg(instr_hndlr_info, 16, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_pack_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_packx_src_srcdst_dreg_smem(instr_hndlr_info, 8, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_pack_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_packx_src_srcdst_dreg_smem(instr_hndlr_info, 16, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_mem_id, spill_info);
}
