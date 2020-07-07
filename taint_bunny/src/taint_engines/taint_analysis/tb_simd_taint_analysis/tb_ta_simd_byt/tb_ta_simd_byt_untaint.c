/*
 * tb_ta_simd_byt_untaint.c
 *
 *      Author: john
 */

#include "tb_ta_simd_byt_untaint.h"
#include "../tb_ta_simd_byt_functionality.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_untaint.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

void tb_simd_byt_handle_untaint_reg_ex(
        tb_raw_instr_hndlr_info_t* instr_hndlr_info, size_t start, size_t end,
        void* drcontext, instrlist_t* ilist, instr_t* where, instr_t* app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t* spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 1);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    // Load Reg Map:
    tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, spill_info->scaler_regs[1]);

    // Translation:
    tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
            drcontext, ilist, where, spill_info->scaler_regs[1],
            reg_id_untaint);

    for (size_t i = start; i < end; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(end, i)
                * sizeof(void *);

        // Create dereference operand that access the src taint label
        opnd_t untaint_label_opnd = opnd_create_base_disp(reg_id_untaint,
                DR_REG_NULL, 1, sizeof(void *) * i,
                opnd_size_from_bytes(partial_size));

        // Untaint reg byte
        tb_simd_insert_set_untaint_reg(instr_hndlr_info, drcontext,
                ilist, where, &untaint_label_opnd, spill_info->xmm_regs[0],
                spill_info->xmm_regs[1], spill_info->scaler_regs[1]);
    }
}

static void tb_simd_byte_handle_untaint_reg(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info) {

    tb_simd_byt_handle_untaint_reg_ex(instr_hndlr_info, 0, size, drcontext,
            ilist, where, app_instr, reg_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_reg_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_untaint_reg_1(instr_hndlr_info, drcontext, ilist, where,
            app_instr, reg_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_reg_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_untaint_reg_2(instr_hndlr_info, drcontext, ilist, where,
            app_instr, reg_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_reg_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info) {

    tb_simd_byte_handle_untaint_reg(instr_hndlr_info, 4, drcontext, ilist,
            where, app_instr, reg_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_reg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info) {

    tb_simd_byte_handle_untaint_reg(instr_hndlr_info, 8, drcontext, ilist,
            where, app_instr, reg_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_reg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info) {

    tb_simd_byte_handle_untaint_reg(instr_hndlr_info, 16, drcontext, ilist,
            app_instr, where, reg_id_untaint, spill_info);
}

static void tb_simd_byte_handle_hp_untaint_mem(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info) {

    DR_ASSERT(spill_info->scaler_cnt > 1);
    DR_ASSERT(spill_info->xmm_cnt > 1);

    tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
            ilist, where, mem_id_untaint, spill_info->scaler_regs[1]);

    for (size_t i = 0; i < size; i += sizeof(void *)) {

        // Set partial size
        int partial_size = tb_simd_calculate_partial_size(size, i)
                * sizeof(void *);

        // Create dereference operand that access the src taint label
        opnd_t untaint_label_opnd = opnd_create_base_disp(mem_id_untaint,
                DR_REG_NULL, 1, sizeof(void *) * i,
                opnd_size_from_bytes(partial_size));

        tb_simd_insert_set_untaint_mem(instr_hndlr_info, drcontext, ilist,
                where, tb_raw_get_app_pc(app_instr), &untaint_label_opnd,
                spill_info->xmm_regs[0], spill_info->xmm_regs[1],
                spill_info->scaler_regs[1]);
    }
}

void tb_simd_byt_handle_untaint_mem_1(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_untaint_mem_1(instr_hndlr_info, drcontext, ilist, where,
            app_instr, mem_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_mem_2(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info) {

    /** DONT USE SIMD **/
    tb_raw_byt_handle_untaint_mem_2(instr_hndlr_info, drcontext, ilist, where,
            app_instr, mem_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_mem_4(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info) {

    tb_simd_byte_handle_hp_untaint_mem(instr_hndlr_info, 4, drcontext, ilist,
            where, app_instr, mem_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_mem_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info) {

    tb_simd_byte_handle_hp_untaint_mem(instr_hndlr_info, 8, drcontext, ilist,
            where, app_instr, mem_id_untaint, spill_info);
}

void tb_simd_byt_handle_untaint_mem_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t mem_id_untaint, tb_spill_info_t *spill_info) {

    tb_simd_byte_handle_hp_untaint_mem(instr_hndlr_info, 16, drcontext, ilist,
            where, app_instr, mem_id_untaint, spill_info);
}
