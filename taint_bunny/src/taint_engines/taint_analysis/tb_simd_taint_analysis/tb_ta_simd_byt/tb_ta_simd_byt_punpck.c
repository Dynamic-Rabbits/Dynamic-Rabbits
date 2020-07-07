/*
 * tb_ta_simd_byt_punpck.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_punpck.h"
#include "../tb_ta_simd_byt_functionality.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_punpck.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

static void tb_simd_apply_weave(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, size_t size, size_t word_size, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg,
        reg_id_t meet_vectorised_reg, reg_id_t meet_vectorised_reg2,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_vectorised_reg2,
        reg_id_t scratch_scaler_reg, reg_id_t scratch_scaler_reg2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_inc_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);

    opnd_t meet_label_opnd = opnd_create_reg(meet_vectorised_reg);
    opnd_t meet_label_opnd2 = opnd_create_reg(meet_vectorised_reg2);

    bool weave = false;

    for (size_t i = 0; i < size; i += word_size) {

        if (weave) {

            for (size_t k = 0; k < word_size; k += sizeof(void *)) {

                // Set partial size
                int partial_size = tb_simd_calculate_partial_size(size, i)
                        * sizeof(void *);

                opnd_t dst_opnd = opnd_create_base_disp(dst_reg, DR_REG_NULL, 1,
                        sizeof(void *) * (i + k),
                        opnd_size_from_bytes(partial_size));

                tb_simd_insert_get_new_label_from_1_src(tb_ctx, drcontext,
                        ilist, where, pc, false, scratch_vectorised_reg,
                        &meet_label_opnd, scratch_vectorised_reg2,
                        scratch_scaler_reg);

                tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist,
                        where, &dst_opnd, scratch_vectorised_reg,
                        scratch_vectorised_reg2, scratch_scaler_reg,
                        scratch_scaler_reg2);
            }

        } else {

            for (size_t k = 0; k < word_size; k += sizeof(void *)) {

                // Set partial size
                int partial_size = tb_simd_calculate_partial_size(size, i)
                        * sizeof(void *);

                opnd_t dst_opnd = opnd_create_base_disp(dst_reg, DR_REG_NULL, 1,
                        sizeof(void *) * (i + k),
                        opnd_size_from_bytes(partial_size));

                tb_simd_insert_get_new_label_from_1_src(tb_ctx, drcontext,
                        ilist, where, pc, false, scratch_vectorised_reg,
                        &meet_label_opnd2, scratch_vectorised_reg2,
                        scratch_scaler_reg);

                tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist,
                        where, &dst_opnd, scratch_vectorised_reg,
                        scratch_vectorised_reg2, scratch_scaler_reg,
                        scratch_scaler_reg2);
            }

        }

        weave = !weave;
    }

    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg,
            scratch_vectorised_reg, scratch_scaler_reg);
    tb_simd_delete_ref(tb_ctx, drcontext, ilist, where, meet_vectorised_reg2,
            scratch_vectorised_reg, scratch_scaler_reg);
}

static void tb_simd_handle_punpckx_propagation(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, bool is_high, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, bool is_src_faulty,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    // Determine whether or not we have to set high or low part of register
    size_t start = 0;
    size_t src_size = size;

    if (is_high)
        start = size / 2;
    else
        src_size = size / 2;

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, start, src_size,
            drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
            is_src_faulty, spill_info->scaler_regs[3], src_reg_id,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2]);

    reg_id_t meet_reg2 = src_reg_id;
    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, start, src_size,
            drcontext, ilist, where, tb_raw_get_app_pc(app_instr), false,
            meet_reg2, srcdst_reg_id, spill_info->xmm_regs[0],
            spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[1],
            meet_reg2);

    tb_simd_apply_weave(instr_hndlr_info, drcontext, size, word_size, ilist,
            where, tb_raw_get_app_pc(app_instr), srcdst_reg_id,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->xmm_regs[3],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

}

static void tb_simd_handle_punpckx_src_srcdst_dreg_sreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, bool is_high, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, reg_id_t srcdst_reg_id,
        reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

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

    tb_simd_handle_punpckx_propagation(instr_hndlr_info, size, word_size,
            is_high, drcontext, ilist, where, app_instr, false, srcdst_reg_id,
            src_reg_id, spill_info);
}

static void tb_simd_handle_punpckx_src_srcdst_dreg_smem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        size_t word_size, bool is_high, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, reg_id_t srcdst_reg_id,
        reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

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

    tb_simd_handle_punpckx_propagation(instr_hndlr_info, size, word_size,
            is_high, drcontext, ilist, where, app_instr, true, srcdst_reg_id,
            src_mem_id, spill_info);
}

/*************************************************************
 * PUNPCKLBW SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_low_punpcklbw_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklbw_dreg_8_sreg_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_low_punpcklbw_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklbw_dreg_16_sreg_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_low_punpcklbw_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklbw_dreg_8_smem_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_low_punpcklbw_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklbw_dreg_16_smem_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/*************************************************************
 * PUNPCKLWD SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_low_punpcklwd_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklwd_dreg_8_sreg_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKLWD SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_low_punpcklwd_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklwd_dreg_8_smem_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/*************************************************************
 * PUNPCKLDQ SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_low_punpckldq_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
    false, drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_low_punpckldq_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
    false, drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKLDQ SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_low_punpckldq_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 4,
    false, drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_low_punpckldq_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 4,
    false, drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/*************************************************************
 * PUNPCKLQDQ SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_low_punpcklqdq_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 8,
    false, drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKLQDQ SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_low_punpcklqdq_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 8,
    false, drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_high_punpckhbw_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhbw_dreg_8_sreg_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_high_punpckhbw_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhbw_dreg_16_sreg_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_high_punpckhbw_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhbw_dreg_8_smem_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_high_punpckhbw_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhbw_dreg_16_smem_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHWD SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_high_punpckhwd_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhwd_dreg_8_sreg_8_sreg_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHWD SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_high_punpckhwd_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(instr_hndlr_info,
            drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHDQ SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_high_punpckhdq_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
    true, drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_high_punpckhdq_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
    true, drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHDQ SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_high_punpckhdq_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 4,
    true, drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_high_punpckhdq_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 4,
    true, drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHQDQ SRC SRCDST - DREG SREG
 */

void tb_simd_byt_handle_high_punpckhqdq_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 8,
    true, drcontext, ilist, where, app_instr, srcdst_reg_id, src_reg_id,
            spill_info);
}

/*************************************************************
 * PUNPCKHQDQ SRC SRCDST - DREG SMEM
 */

void tb_simd_byt_handle_high_punpckhqdq_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_simd_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 8,
    true, drcontext, ilist, where, app_instr, srcdst_reg_id, src_mem_id,
            spill_info);
}
