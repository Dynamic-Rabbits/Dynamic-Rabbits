/*
 * tb_ta_simd_byt_p_src_srcdst.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_p_src_srcdst.h"
#include "../tb_ta_simd_byt_functionality.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_p_src_srcdst.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

static void tb_simd_handle_px_propagation(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, bool is_src_faulty, reg_id_t srcdst_id, reg_id_t src_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    for (size_t i = 0; i < size; i += word_size) {

        tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + word_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr), is_src_faulty,
                spill_info->scaler_regs[3], src_id, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2]);

        // Broadcast it to xmm register
        tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
                spill_info->scaler_regs[3]);

        tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + word_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),false,
                spill_info->scaler_regs[3], srcdst_id, spill_info->xmm_regs[1], spill_info->xmm_regs[2],
                spill_info->scaler_regs[2]);

        // Broadcast it to xmm register
        tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
                spill_info->scaler_regs[3]);

        // Apply to destination
        tb_simd_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), srcdst_id, i,
                i + word_size, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->xmm_regs[2], spill_info->xmm_regs[3],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_simd_handle_px_src_srcdst_whole_dreg_sreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
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

    tb_simd_handle_px_propagation(instr_hndlr_info, size, word_size, drcontext,
            ilist, where, app_instr, false, srcdst_reg_id, src_reg_id, spill_info);
}

static void tb_simd_handle_px_src_srcdst_whole_dreg_smem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
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

    tb_simd_handle_px_propagation(instr_hndlr_info, size, word_size, drcontext,
            ilist, where, app_instr, true, srcdst_reg_id, src_mem_id, spill_info);
}

/**************************************************************
 * PW SRC SRCDST - DREG SREG SREG
 */

void tb_simd_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
            instr_hndlr_info, drcontext, ilist, where, app_instr, srcdst_reg_id,
            src_reg_id, spill_info);
}

/**************************************************************
 * PW SRC SRCDST - DREG SMEM SREG
 */

void tb_simd_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16(
            instr_hndlr_info, drcontext, ilist, where, app_instr, srcdst_reg_id,
            src_mem_id, spill_info);
}

/**************************************************************
 * PD SRC SRCDST - DREG SREG SREG
 */

void tb_simd_byt_handle_pd_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************
 * PD SRC SRCDST - DREG SMEM SREG
 */

void tb_simd_byt_handle_pd_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/**************************************************************
 * PQ SRC SRCDST - DREG SREG SREG
 */

void tb_simd_byt_handle_pq_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_pq_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************
 * PQ SRC SRCDST - DREG SMEM SREG
 */

void tb_simd_byt_handle_pq_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_pq_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/**************************************************************
 * PMADDWD SRCDST - DREG SREG SREG
 */

void tb_simd_byt_handle_pmaddwd_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************
 * PMADDWD SRCDST - DREG SMEM SREG
 */

void tb_simd_byt_handle_pmaddwd_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}
