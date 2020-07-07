/*
 * tb_ta_cc_byt_pack.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_pack.h"

#include "../tb_ta_cc_byt_functionality.h"
#include "../../../../tb_bunny_private.h"
#include "../../../../tls_access/tb_tls_access.h"
#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#include "utility_bunny.h"

#include <stdint.h>

/**************************************************************
 * HELPERS
 */

static void tb_cc_handle_packx_src_srcdst_dreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id, uintptr_t src_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    // Step 1: Handle DST
    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);
        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);

        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                src_reg_id + i);

        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop1 && stop2)
            break;
    }

    if (tb_ctx->new_ref_func) {

        if (meet_src_label1)
            tb_ctx->new_ref_func(meet_src_label1);

        if (meet_src_label2)
            tb_ctx->new_ref_func(meet_src_label2);
    }

    int dest_pos = size / 2;

    // Step 1: Handle SRC
    for (int i = 0, j = dest_pos; i < dest_pos; j++, i++) {

        void *result_label = tb_ctx->propogate_func_1dst_1src(meet_src_label1);
        void *result_label2 = tb_ctx->propogate_func_1dst_1src(meet_src_label2);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
        succ = succ || temp_res;

        temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + j, result_label2, !succ);
        succ = succ || temp_res;
    }

    if (tb_ctx->delete_ref_func) {

        if (meet_src_label1)
            tb_ctx->delete_ref_func(meet_src_label1);

        if (meet_src_label2)
            tb_ctx->delete_ref_func(meet_src_label2);
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_packx_src_srcdst_dreg_smem(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    // Step 1: Handle DST
    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);
        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);

        void *src_label2 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                src_mem_id + i);

        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop1 && stop2)
            break;
    }

    if (tb_ctx->new_ref_func) {

        if (meet_src_label1)
            tb_ctx->new_ref_func(meet_src_label1);

        if (meet_src_label2)
            tb_ctx->new_ref_func(meet_src_label2);
    }

    size_t dest_pos = size / 2;

    // Step 1: Handle SRC
    for (size_t i = 0, j = dest_pos; i < dest_pos; j++, i++) {

        void *result_label = tb_ctx->propogate_func_1dst_1src(meet_src_label1);
        void *result_label2 = tb_ctx->propogate_func_1dst_1src(meet_src_label2);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
        succ = succ || temp_res;

        temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + j, result_label2, !succ);
        succ = succ || temp_res;
    }

    if (tb_ctx->delete_ref_func) {

        if (meet_src_label1)
            tb_ctx->delete_ref_func(meet_src_label1);

        if (meet_src_label2)
            tb_ctx->delete_ref_func(meet_src_label2);
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);

}

/***************************************************************************
 * PACKSWB SRC SRCDST - DREG DREG
 **/

void tb_cc_byt_handle_pack_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_packx_src_srcdst_dreg_sreg(instr_hndlr_info, 8, srcdst_reg_id,
            src_reg_id);
}

void tb_cc_byt_handle_pack_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_packx_src_srcdst_dreg_sreg(instr_hndlr_info, 16, srcdst_reg_id,
            src_reg_id);
}

/***************************************************************************
 * PACKSWB SRC SRCDST - DREG DMEM
 **/

void tb_cc_byt_handle_pack_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_packx_src_srcdst_dreg_smem(instr_hndlr_info, 8, srcdst_reg_id,
            src_reg_id);
}

void tb_cc_byt_handle_pack_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_packx_src_srcdst_dreg_smem(instr_hndlr_info, 16, srcdst_reg_id,
            src_reg_id);
}
