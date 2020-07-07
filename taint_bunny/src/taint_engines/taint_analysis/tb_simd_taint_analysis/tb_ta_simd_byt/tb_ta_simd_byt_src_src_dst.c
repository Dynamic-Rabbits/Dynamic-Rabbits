/*
 * tb_ta_simd_byt_src_src_dst.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_src_src_dst.h"
#include "../tb_ta_simd_byt_functionality.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_src_dst.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

static void tb_simd_handle_src_src_dst_whole_dreg_propagation(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        size_t ssize2, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, bool is_first_src_faulty, reg_id_t dst_reg_id, reg_id_t src_reg_id,
        reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Gets Meets
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), is_first_src_faulty,
            spill_info->scaler_regs[4], src_reg_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[3]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize2, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), false, meet_reg2, src_reg_id2,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1], spill_info->scaler_regs[3]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[4]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    // Apply to destination
    tb_simd_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), dst_reg_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[3], meet_reg2);

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[3], spill_info->scaler_regs[4]);
}

static void tb_simd_handle_src_src_dst_whole_dreg_smem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        size_t ssize2, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t dst_reg_id, reg_id_t src_mem_id,
        reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 4);
    DR_ASSERT(spill_info->xmm_cnt > 3);

    // Load Reg Map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[4]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id2);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);

    tb_simd_handle_src_src_dst_whole_dreg_propagation(instr_hndlr_info, dsize,
            ssize, ssize2, drcontext, ilist, where, app_instr, true, dst_reg_id,
            src_mem_id, src_reg_id2, spill_info);
}

static void tb_simd_handle_src_src_dst_whole_dreg_sreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        size_t ssize2, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t dst_reg_id, reg_id_t src_reg_id,
        reg_id_t src_reg_id2, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 4);
    DR_ASSERT(spill_info->xmm_cnt > 3);

    // Load Reg Map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id2);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);

    tb_simd_handle_src_src_dst_whole_dreg_propagation(instr_hndlr_info, dsize,
            ssize, ssize2, drcontext, ilist, where, app_instr, false, dst_reg_id,
            src_reg_id, src_reg_id2, spill_info);
}

static void tb_simd_handle_src_src_dst_whole_dreg_sreg_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 4);
    DR_ASSERT(spill_info->xmm_cnt > 3);

    // Load Reg Map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id2);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);
    // Gets Meets
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), false,
            spill_info->scaler_regs[4], src_reg_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[3]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, 1, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), meet_reg2, src_reg_id2,
            spill_info->scaler_regs[3]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[4]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    // Apply to destination
    tb_simd_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), dst_reg_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[3], meet_reg2);

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[3], spill_info->scaler_regs[4]);
}

static void tb_simd_handle_src_src_dst_whole_dmem_sreg_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_addr, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 4);
    DR_ASSERT(spill_info->xmm_cnt > 3);


    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Reg Map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id2);
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, dst_mem_addr, spill_info->scaler_regs[4]);

    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), false,
            spill_info->scaler_regs[4], src_reg_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[3]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, 1, drcontext, ilist,
            where, tb_raw_get_app_pc(app_instr), meet_reg2, src_reg_id2,
            spill_info->scaler_regs[3]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[4]);

    // Broadcast it to xmm register
    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    tb_simd_apply_to_1_mem_from_2_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), true, dst_mem_addr, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[3], meet_reg2);

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[3], spill_info->scaler_regs[4]);
}

/**************************************************************************************
 * SRC SRC DST - DREG SREG SREG (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dreg_2_sreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_src_dst_whole_dreg_2_sreg_1_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dreg_sreg_sreg(instr_hndlr_info, 4, 4, 4,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 8, 8,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_src_dst_whole_dreg_2_sreg_2_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dreg_4_sreg_4_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dreg_sreg_sreg_1(instr_hndlr_info, 4, 4,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dreg_8_sreg_8_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dreg_sreg_sreg_1(instr_hndlr_info, 8, 8,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            src_reg_id2, spill_info);
}

/**************************************************************************************
 * SRC SRC DST - DREG SMEM SREG (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dreg_2_smem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_src_dst_whole_dreg_2_smem_1_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_mem_id,
            src_reg_id2, spill_info);
}

/**************************************************************************************
 * SRC SRC DST - DREG SREG SMEM (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dreg_4_sreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_mem_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dreg_smem_sreg(instr_hndlr_info, 4, 4, 4,
            drcontext, ilist, where, app_instr, dst_reg_id, src_mem_id2,
            src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dreg_8_sreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, reg_id_t src_mem_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 8, 8,
            drcontext, ilist, where, app_instr, dst_reg_id, src_mem_id2,
            src_reg_id, spill_info);
}

/**************************************************************************************
 * SRC SRC DST - DMEM SREG SREG (WHOLE)
 */

void tb_simd_byt_handle_src_src_dst_whole_dmem_2_sreg_2_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_src_dst_whole_dmem_2_sreg_2_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dmem_4_sreg_4_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dmem_sreg_sreg_1(instr_hndlr_info, 4, 4,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            src_reg_id2, spill_info);
}

void tb_simd_byt_handle_src_src_dst_whole_dmem_8_sreg_8_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, reg_id_t src_reg_id2,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_src_src_dst_whole_dmem_sreg_sreg_1(instr_hndlr_info, 8, 8,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            src_reg_id2, spill_info);
}
