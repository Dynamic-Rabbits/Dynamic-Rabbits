/*
 * tb_ta_simd_byt_src_srcdst.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_src_srcdst.h"
#include "../tb_ta_simd_byt_functionality.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_srcdst.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

/**************************************************************************************
 * HELPERS
 */

static void tb_simd_handle_whole_src_srcdst_dreg_propagate(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        bool is_src_faulty, reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), is_src_faulty,
            spill_info->scaler_regs[3], src_reg_id, spill_info->xmm_regs[0],
            spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, dsize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), false, meet_reg2,
            srcdst_reg_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    tb_simd_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), srcdst_reg_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

/**************************************************************************************
 * SRC SRCDST - DREG SREG SREG (WHOLE)
 */

static void tb_simd_handle_whole_src_srcdst_dreg_sreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
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

    tb_simd_handle_whole_src_srcdst_dreg_propagate(instr_hndlr_info, dsize,
            ssize, drcontext, ilist, where, app_instr, false, srcdst_reg_id,
            src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 4, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 16,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

static void tb_simd_handle_whole_src_srcdst_dreg_sreg_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize,
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

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, 1, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[3],
            src_reg_id, spill_info->scaler_regs[2]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, dsize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), false, meet_reg2,
            srcdst_reg_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    tb_simd_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), srcdst_reg_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_srcdst_dreg_sreg_sreg_1(instr_hndlr_info, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_srcdst_dreg_sreg_sreg_1(instr_hndlr_info, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG (WHOLE)
 */

static void tb_simd_handle_whole_dreg_smem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
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

    tb_simd_handle_whole_src_srcdst_dreg_propagate(instr_hndlr_info, dsize,
            ssize, drcontext, ilist, where, app_instr, true, srcdst_reg_id,
            src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_4_smem_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_dreg_smem_sreg(instr_hndlr_info, 4, 4, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_dreg_smem_sreg(instr_hndlr_info, 8, 8, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_dreg_smem_sreg(instr_hndlr_info, 16, 16, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_mem_id, spill_info);
}

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM (WHOLE)
 */

static void tb_simd_handle_whole_dmem_propagate(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), false,
            spill_info->scaler_regs[3], src_reg_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, dsize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), true, meet_reg2,
            srcdst_mem_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    tb_simd_apply_to_1_mem_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), true, srcdst_mem_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_simd_handle_whole_dmem_sreg_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 3);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, srcdst_mem_id, spill_info->scaler_regs[3]);

    tb_simd_handle_whole_dmem_propagate(instr_hndlr_info, dsize, ssize,
            drcontext, ilist, where, app_instr, srcdst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_4_sreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_dmem_sreg_smem(instr_hndlr_info, 4, 4, drcontext,
            ilist, where, app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_8_sreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_dmem_sreg_smem(instr_hndlr_info, 8, 8, drcontext,
            ilist, where, app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_16_sreg_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_dmem_sreg_smem(instr_hndlr_info, 16, 16, drcontext,
            ilist, where, app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

static void tb_simd_handle_whole_dmem_sreg_1_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 3);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, srcdst_mem_id, spill_info->scaler_regs[3]);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, 1, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[3],
            src_reg_id, spill_info->scaler_regs[2]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, dsize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), true, meet_reg2,
            srcdst_mem_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    tb_simd_apply_to_1_mem_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), true, srcdst_mem_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_2_sreg_1_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_whole_dmem_2_sreg_1_smem_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_4_sreg_1_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_simd_handle_whole_dmem_sreg_1_smem(instr_hndlr_info, 4, drcontext, ilist,
            where, app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_whole_dmem_8_sreg_1_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_simd_handle_whole_dmem_sreg_1_smem(instr_hndlr_info, 8, drcontext, ilist,
            where, app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

/**************************************************************************************
 * SRC SRCDST - DREG SREG SREG
 */

static void tb_simd_handle_src_srcdst_dreg_propagate(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr, bool is_src_faulty,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    for (size_t i = 0; i < size; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(size, i)
                * sizeof(void *);

        opnd_t src1_tl_opnd = opnd_create_base_disp(src_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        opnd_t srcdst_tl_opnd = opnd_create_base_disp(srcdst_reg_id,
                DR_REG_NULL, 1, sizeof(void *) * i,
                opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_2_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr), is_src_faulty,
                spill_info->xmm_regs[0], &src1_tl_opnd, &srcdst_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &srcdst_tl_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[2],
                spill_info->scaler_regs[3]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_simd_handle_src_srcdst_dreg_sreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    tb_simd_handle_src_srcdst_dreg_propagate(instr_hndlr_info, size, drcontext,
            ilist, where, app_instr, false, srcdst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 4, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, drcontext,
            ilist, where, app_instr, srcdst_reg_id, src_reg_id, spill_info);
}

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG
 */

static void tb_simd_handle_dreg_smem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id1, spill_info->scaler_regs[3]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    tb_simd_handle_src_srcdst_dreg_propagate(instr_hndlr_info, size, drcontext,
            ilist, where, app_instr, true, srcdst_reg_id, src_mem_id1, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id1,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id1,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_4_smem_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_dreg_smem_sreg(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, srcdst_reg_id, src_mem_id1, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_dreg_smem_sreg(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, srcdst_reg_id, src_mem_id1, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id1,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_dreg_smem_sreg(instr_hndlr_info, 16, drcontext, ilist, where,
            app_instr, srcdst_reg_id, src_mem_id1, spill_info);
}

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM
 */

static void tb_simd_handle_dmem_propagate(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    for (size_t i = 0; i < size; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(size, i)
                * sizeof(void *);

        opnd_t src1_tl_opnd = opnd_create_base_disp(src_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        opnd_t srcdst_tl_opnd = opnd_create_base_disp(srcdst_mem_id,
                DR_REG_NULL, 1, sizeof(void *) * i,
                opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_2_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr), true,
                spill_info->xmm_regs[0], &srcdst_tl_opnd, &src1_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where,
                tb_raw_get_app_pc(app_instr), &srcdst_tl_opnd,
                spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

}

static void tb_simd_handle_dmem_sreg_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, srcdst_mem_id, spill_info->scaler_regs[3]);

    tb_simd_handle_dmem_propagate(instr_hndlr_info, size, drcontext, ilist,
            where, app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_srcdst_dmem_4_sreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_dmem_sreg_smem(instr_hndlr_info, 4, drcontext, ilist, where,
            app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dmem_8_sreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_dmem_sreg_smem(instr_hndlr_info, 8, drcontext, ilist, where,
            app_instr, srcdst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_srcdst_dmem_16_sreg_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_dmem_sreg_smem(instr_hndlr_info, 16, drcontext, ilist, where,
            app_instr, srcdst_mem_id, src_reg_id, spill_info);
}
