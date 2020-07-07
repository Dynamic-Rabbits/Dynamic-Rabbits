/*
 * tb_ta_raw_byt_p_src_srcdst.c
 *
 *      Author: john
 */

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_p_src_srcdst.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

static void tb_raw_handle_px_src_srcdst_whole_dreg_sreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 5);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    for (size_t i = 0; i < size; i += word_size) {

        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + word_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[3], src_reg_id,
                spill_info->scaler_regs[2]);

        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + word_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[4], srcdst_reg_id, spill_info->scaler_regs[2]);

        tb_raw_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), true, srcdst_reg_id, i,
                i + word_size, spill_info->scaler_regs[3], spill_info->scaler_regs[4],
                spill_info->scaler_regs[2], spill_info->scaler_regs[5]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist,
            where, spill_info->scaler_regs[2], spill_info->scaler_regs[4]);
}

static void tb_raw_handle_px_src_srcdst_whole_dreg_smem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 5);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:

    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_reg_id, spill_info->scaler_regs[3]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    for (size_t i = 0; i < size; i += word_size) {

        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + word_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[3], src_reg_id,
                spill_info->scaler_regs[2]);
        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + word_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[4], srcdst_reg_id, spill_info->scaler_regs[2]);

        tb_raw_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), true, srcdst_reg_id, i,
                i + word_size, spill_info->scaler_regs[3], spill_info->scaler_regs[4],
                spill_info->scaler_regs[2], spill_info->scaler_regs[5]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist,
            where, spill_info->scaler_regs[2], spill_info->scaler_regs[4]);
}

/**************************************************************
 * PW SRC SRCDST - DREG SREG SREG
 */

void tb_raw_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 2,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_raw_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 2,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************
 * PW SRC SRCDST - DREG SMEM SREG
 */

void tb_raw_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 2,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_raw_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 2,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/**************************************************************
 * PD SRC SRCDST - DREG SREG SREG
 */

void tb_raw_byt_handle_pd_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_raw_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************
 * PD SRC SRCDST - DREG SMEM SREG
 */

void tb_raw_byt_handle_pd_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_raw_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 4,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/**************************************************************
 * PQ SRC SRCDST - DREG SREG SREG
 */

void tb_raw_byt_handle_pq_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_raw_byt_handle_pq_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************
 * PQ SRC SRCDST - DREG SMEM SREG
 */

void tb_raw_byt_handle_pq_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_raw_byt_handle_pq_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/***************************************************************************
 * PMADDWD HELPERS
 */

static void tb_raw_handle_pmaddwd_src_srcdst_whole_dreg_sreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 5);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    const size_t dw_size = 4;

    for (size_t i = 0; i < size; i += dw_size) {

        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + dw_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[3], srcdst_reg_id,
                spill_info->scaler_regs[2]);

        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + dw_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[4], src_reg_id,
                spill_info->scaler_regs[2]);

        tb_raw_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), true, srcdst_reg_id, i,
                i + dw_size, spill_info->scaler_regs[3],
                spill_info->scaler_regs[4], spill_info->scaler_regs[2],
                spill_info->scaler_regs[5]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist,
            where, spill_info->scaler_regs[2], spill_info->scaler_regs[4]);

}

static void tb_raw_handle_pmaddwd_src_srcdst_whole_dreg_smem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 5);
    DR_ASSERT(spill_info->xmm_cnt == 0);

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[3]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], srcdst_reg_id);

    const size_t dw_size = 4;

    for (size_t i = 0; i < size; i += dw_size) {

        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + dw_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[3], srcdst_reg_id,
                spill_info->scaler_regs[2]);

        tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, i, i + dw_size,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                spill_info->scaler_regs[4], src_mem_id,
                spill_info->scaler_regs[2]);

        tb_raw_apply_to_1_reg_from_2_src(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), true, srcdst_reg_id, i,
                i + dw_size, spill_info->scaler_regs[3],
                spill_info->scaler_regs[4], spill_info->scaler_regs[2],
                spill_info->scaler_regs[5]);
    }

    // We check whether we perform the post propagation call.
    tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist,
            where, spill_info->scaler_regs[2], spill_info->scaler_regs[4]);

}

/**************************************************************
 * PMADDWD SRCDST - DREG SREG SREG
 */

void tb_raw_byt_handle_pmaddwd_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_pmaddwd_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_raw_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_pmaddwd_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/**************************************************************
 * PMADDWD SRCDST - DREG SMEM SREG
 */

void tb_raw_byt_handle_pmaddwd_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_pmaddwd_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_raw_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_handle_pmaddwd_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}
