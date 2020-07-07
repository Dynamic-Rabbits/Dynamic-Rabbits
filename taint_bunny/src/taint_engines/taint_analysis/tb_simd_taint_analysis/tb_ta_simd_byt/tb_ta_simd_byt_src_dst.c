/*
 * tb_ta_simd_byt_src_dst.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_src_dst.h"
#include "../tb_ta_simd_byt_functionality.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_dst.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

/****************************************************************************
 * HELPERS
 */

static void tb_simd_handle_src_dst_dmem_propagation(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        bool is_src_faulty, reg_id_t dst_mem_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    for (size_t i = 0; i < size; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(size, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_mem_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_mem_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                is_src_faulty, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where,
                tb_raw_get_app_pc(app_instr), &dst_tl_opnd,
                spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_simd_handle_src_dst_dreg_propagation(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size, size_t start,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        bool is_src_faulty, reg_id_t dst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    for (size_t i = 0; i < size; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(size, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                is_src_faulty, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

/****************************************************************************
 * SRC DST - DMEM SMEM
 */

static void tb_simd_handle_src_dst_dmem_smem_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        size_t size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t dst_mem_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    // Translation
    if (translate) {
        tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
                ilist, where, src_mem_id, spill_info->scaler_regs[2]);
        tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
                ilist, where, dst_mem_id, spill_info->scaler_regs[2]);
    }

    tb_simd_handle_src_dst_dmem_propagation(instr_hndlr_info, size, drcontext,
            ilist, where, app_instr, true, dst_mem_id, src_mem_id, spill_info);
}

static void tb_simd_handle_src_dst_dmem_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_smem_ex(instr_hndlr_info, true, size, drcontext,
            ilist, where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_1_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_1_smem_1(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_2_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_2_smem_2(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_smem(instr_hndlr_info, 4, drcontext, ilist,
            where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_smem(instr_hndlr_info, 8, drcontext, ilist,
            where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_smem(instr_hndlr_info, 16, drcontext, ilist,
            where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_1_smem_1_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_1_smem_1_ex(instr_hndlr_info, translate,
            drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_2_smem_2_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_2_smem_2_ex(instr_hndlr_info, translate,
            drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_4_smem_4_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 4,
            drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_8_smem_8_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 8,
            drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_16_smem_16_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 16,
            drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
            spill_info);
}

/*****************************************************************************
 * SRC DST - DMEM SREG
 */

static void tb_simd_handle_src_dst_dmem_sreg_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        size_t size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, reg_id_t dst_mem_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    if (translate) {
        tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, spill_info->scaler_regs[3],
                src_reg_id);
        tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
                ilist, where, dst_mem_id, spill_info->scaler_regs[2]);
    }

    tb_simd_handle_src_dst_dmem_propagation(instr_hndlr_info, size, drcontext,
            ilist, where, app_instr, false, dst_mem_id, src_reg_id, spill_info);
}

static void tb_simd_handle_src_dst_dmem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, true, size, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_1_sreg_1(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_2_sreg_2(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_sreg(instr_hndlr_info, 4, drcontext, ilist,
            where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_sreg(instr_hndlr_info, 8, drcontext, ilist,
            where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_sreg(instr_hndlr_info, 16, drcontext, ilist,
            where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_1_sreg_1_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_1_sreg_1_ex(instr_hndlr_info, translate,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_2_sreg_2_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dmem_2_sreg_2_ex(instr_hndlr_info, translate,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_4_sreg_4_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 4,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_8_sreg_8_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 8,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dmem_16_sreg_16_ex(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 16,
            drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
            spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SREG
 */

static void tb_simd_handle_src_dst_dreg_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size, size_t start,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    DR_ASSERT(start < size);

    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);

    tb_simd_handle_src_dst_dreg_propagation(instr_hndlr_info, size, start,
            drcontext, ilist, where, app_instr, false, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dreg_1_sreg_1(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dreg_2_sreg_2(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_sreg(instr_hndlr_info, 4, 0, drcontext, ilist,
            where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_sreg(instr_hndlr_info, 8, 0, drcontext, ilist,
            where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_sreg(instr_hndlr_info, 16, 0, drcontext, ilist,
            where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SMEM
 */

static void tb_simd_handle_src_dst_dreg_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size, size_t start,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    DR_ASSERT(start < size);

    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[2]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);

    tb_simd_handle_src_dst_dreg_propagation(instr_hndlr_info, size, start,
            drcontext, ilist, where, app_instr, true, dst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_1_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dreg_1_smem_1(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_2_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_dreg_2_smem_2(instr_hndlr_info, drcontext, ilist,
            where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_smem(instr_hndlr_info, 4, 0, drcontext, ilist,
            where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_smem(instr_hndlr_info, 8, 0, drcontext, ilist,
            where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_dreg_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_smem(instr_hndlr_info, 16, 0, drcontext, ilist,
            where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SREG (EXTENSION)
 */

void tb_simd_byt_handle_src_dst_extension_dreg_2_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_extension_dreg_2_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_extension_dreg_4_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_extension_dreg_4_sreg_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_extension_dreg_4_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_extension_dreg_4_sreg_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_extension_dreg_8_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Map
        tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
                ilist, where, spill_info->scaler_regs[2]);

    // Translation:
        tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
        tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

    for (size_t i = 0; i < 4; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(4, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                false, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    for (size_t i = 4; i < 8; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(8, i)
                * sizeof(void *);

        opnd_t dst_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext, ilist,
                where, &dst_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_simd_byt_handle_src_dst_extension_dreg_16_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Map
        tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
                ilist, where, spill_info->scaler_regs[2]);

    // Translation:
        tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
        tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

    for (size_t i = 0; i < 4; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(4, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                false, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    for (size_t i = 4; i < 16; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(16, i)
                * sizeof(void *);

        opnd_t dst_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext, ilist,
                where, &dst_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_simd_byt_handle_src_dst_extension_dreg_16_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    // Load Map
        tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
                ilist, where, spill_info->scaler_regs[2]);

    // Translation:
        tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
        tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

    for (size_t i = 0; i < 8; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(8, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                false, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    for (size_t i = 8; i < 16; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(16, i)
                * sizeof(void *);

        opnd_t dst_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext, ilist,
                where, &dst_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_simd_byt_handle_src_dst_extension_dreg_2_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_extension_dreg_2_smem_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_extension_dreg_4_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_extension_dreg_4_smem_1(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_mem_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_extension_dreg_4_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_extension_dreg_4_smem_2(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_mem_id,
            spill_info);

}

void tb_simd_byt_handle_src_dst_extension_dreg_16_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[2]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);


    for (size_t i = 0; i < 4; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(4, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_mem_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                true, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    for (size_t i = 4; i < 16; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(16, i)
                * sizeof(void *);

        opnd_t dst_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext, ilist,
                where, &dst_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

}

void tb_simd_byt_handle_src_dst_extension_dreg_8_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[2]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);


    for (size_t i = 0; i < 4; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(4, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_mem_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                true, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    for (size_t i = 4; i < 8; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(8, i)
                * sizeof(void *);

        opnd_t dst_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext, ilist,
                where, &dst_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_simd_byt_handle_src_dst_extension_dreg_16_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[3]);

    // Translation
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[2]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);


    for (size_t i = 0; i < 8; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(8, i)
                * sizeof(void *);

        opnd_t src_tl_opnd = opnd_create_base_disp(src_mem_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));
        opnd_t dst_tl_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        // Get new label.
        tb_simd_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
                drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
                true, spill_info->xmm_regs[0], &src_tl_opnd,
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

        tb_simd_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
                &dst_tl_opnd, spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
    }

    for (size_t i = 8; i < 16; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(16, i)
                * sizeof(void *);

        opnd_t dst_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext, ilist,
                where, &dst_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[2]);
    }

    // We check whether we perform the post propagation call.
    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);

}

/****************************************************************************
 * HELPERS
 */

static void tb_simd_handle_whole_src_dst_dmem_propagate(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        bool is_src_faulty, reg_id_t dst_mem_id, reg_id_t src_id,
        tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), is_src_faulty,
            spill_info->scaler_regs[3], src_id, spill_info->xmm_regs[0],
            spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    tb_simd_apply_to_1_mem_from_1_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), dst_mem_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->scaler_regs[3],
            spill_info->scaler_regs[2]);

    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

static void tb_simd_handle_src_dst_whole_dreg_untaint_propagate(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize,
        size_t dsize_untaint, size_t ssize, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, bool is_src_faulty,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
            where);

    tb_simd_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext,
            ilist, where, tb_raw_get_app_pc(app_instr), is_src_faulty,
            spill_info->scaler_regs[3], src_reg_id, spill_info->xmm_regs[0],
            spill_info->xmm_regs[1], spill_info->scaler_regs[2]);

    tb_simd_broadcast_meet(drcontext, ilist, where, spill_info->xmm_regs[0],
            spill_info->scaler_regs[3]);

    tb_simd_apply_to_1_reg_from_1_src(instr_hndlr_info, drcontext, ilist, where,
            tb_raw_get_app_pc(app_instr), true, dst_reg_id, 0, dsize,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->xmm_regs[2], spill_info->scaler_regs[2], src_reg_id);

    for (size_t i = dsize; i < dsize_untaint; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(dsize_untaint, i)
                * sizeof(void *);

        opnd_t dst_opnd = opnd_create_base_disp(dst_reg_id, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext, ilist,
                where, &dst_opnd, spill_info->xmm_regs[0],
                spill_info->scaler_regs[2], spill_info->xmm_regs[1]);
    }

    tb_simd_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
            spill_info->xmm_regs[0], spill_info->xmm_regs[1],
            spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

/*****************************************************************************
 * SRC DST - DREG SREG (WHOLE)
 */

static void tb_simd_handle_src_dst_whole_dreg_sreg_untaint(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize,
        size_t dsize_untaint, size_t ssize, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, reg_id_t dst_reg_id,
        reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 2);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

    tb_simd_handle_src_dst_whole_dreg_untaint_propagate(instr_hndlr_info, dsize,
            dsize_untaint, ssize, drcontext, ilist, where, app_instr, false,
            dst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_1(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_2(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 4, 0, 4,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 8, 0, 8,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 16, 0, 16,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_4(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_4(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_4(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_4(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_8(instr_hndlr_info,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_4_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 4, 0, 16,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_8_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 8, 0, 16,
            drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
            spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SMEM (WHOLE)
 */

static void tb_simd_handle_whole_src_dst_dreg_smem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 2);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, src_mem_id, spill_info->scaler_regs[3]);
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

    tb_simd_handle_src_dst_whole_dreg_untaint_propagate(instr_hndlr_info, size,
            0, size, drcontext, ilist, where, app_instr, true, dst_reg_id,
            src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_1_smem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_1_smem_1(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_2_smem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dreg_2_smem_2(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_4_smem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 4, drcontext,
            ilist, where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_8_smem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 8, drcontext,
            ilist, where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dreg_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 16, drcontext,
            ilist, where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

/*****************************************************************************
 * SRC DST - DMEM SREG (WHOLE)
 */

static void tb_simd_handle_whole_src_dst_dmem_sreg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 3);
    DR_ASSERT(spill_info->xmm_cnt > 2);

    // Load reg map
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[2]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, dst_mem_id, spill_info->scaler_regs[3]);

    tb_simd_handle_whole_src_dst_dmem_propagate(instr_hndlr_info, dsize, ssize,
            drcontext, ilist, where, app_instr, false, dst_mem_id, src_reg_id,
            spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_1_sreg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dmem_1_sreg_1(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_2_sreg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dmem_2_sreg_2(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_4_sreg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 4, 4, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 8, 8, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 16, 16, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_1_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dmem_1_sreg_16(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_2_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    /** DON'T USE SIMD **/
    tb_raw_byt_handle_src_dst_whole_dmem_2_sreg_16(instr_hndlr_info, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_4_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 4, 16, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_simd_byt_handle_src_dst_whole_dmem_8_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 8, 16, drcontext,
            ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

/***********************************************************************
 * HIGH Mov
 */

void tb_simd_byt_handle_high_src_dst_dreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_sreg(instr_hndlr_info, 16, 8, drcontext, ilist,
            where, app_instr, dst_reg_id, src_reg_id, spill_info);

}

void tb_simd_byt_handle_high_src_dst_dreg_16_smem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

    tb_simd_handle_src_dst_dreg_smem(instr_hndlr_info, 16, 8, drcontext, ilist,
            where, app_instr, dst_reg_id, src_reg_id, spill_info);

}
