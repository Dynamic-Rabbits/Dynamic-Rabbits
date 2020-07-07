/*
 * tb_ta_cc_byt_src_srcdst_dst.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_src_srcdst_dst.h"

#include "../tb_ta_cc_byt_functionality.h"
#include "../../../../tb_bunny_private.h"
#include "../../../../tls_access/tb_tls_access.h"
#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#include "utility_bunny.h"

#include <stdint.h>

/*************************************************************************
 * Helpers
 */
static void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_dreg_sreg_sreg(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        uintptr_t dst_reg_id1, uintptr_t srcdst_reg_id2, uintptr_t src_reg_id1) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;
    void *reg_map = tb_get_reg_map(tb_ctx);

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                src_reg_id1 + i);
        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id2 + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);
        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop1 && stop2)
            break;
    }

    if (tb_ctx->new_ref_func){

        if (meet_src_label1)
        tb_ctx->new_ref_func(meet_src_label1);

        if (meet_src_label2)
        tb_ctx->new_ref_func(meet_src_label2);
    }

    for (size_t i = 0; i < size; i++) {

        void *result_label = tb_ctx->propogate_func_1dst_2src(meet_src_label1,
                meet_src_label2);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                dst_reg_id1 + i, result_label, !succ);
        succ = succ || temp_res;

        result_label = tb_ctx->propogate_func_1dst_2src(meet_src_label1,
                meet_src_label2);

        temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id2 + i, result_label, !succ);

        succ = succ || temp_res;

    }


    if (tb_ctx->delete_ref_func){

        if (meet_src_label1)
        tb_ctx->delete_ref_func(meet_src_label1);

        if (meet_src_label2)
        tb_ctx->delete_ref_func(meet_src_label2);
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_src_srcdst_dst_whole_dreg_dreg_smem_sreg(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        uintptr_t dst_reg_id1, uintptr_t srcdst_reg_id, uintptr_t src_mem_id1) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                src_mem_id1 + i);
        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);
        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop1 && stop2)
            break;
    }

    if (tb_ctx->new_ref_func){

        if (meet_src_label1)
        tb_ctx->new_ref_func(meet_src_label1);

        if (meet_src_label2)
        tb_ctx->new_ref_func(meet_src_label2);
    }

    for (size_t i = 0; i < size; i++) {

        void *result_label = tb_ctx->propogate_func_1dst_2src(meet_src_label1,
                meet_src_label2);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                dst_reg_id1 + i, result_label, !succ);
        succ = succ || temp_res;

        result_label = tb_ctx->propogate_func_1dst_2src(meet_src_label1,
                meet_src_label2);

        temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
        succ = succ || temp_res;

    }

    if (tb_ctx->delete_ref_func){

        if (meet_src_label1)
        tb_ctx->delete_ref_func(meet_src_label1);

        if (meet_src_label2)
        tb_ctx->delete_ref_func(meet_src_label2);
    }


    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

/*************************************************************************
 * SRC SRCDST DST - REG REG REG
 */

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_1_dreg_1_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id, uintptr_t src_reg_id1) {

    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_dreg_sreg_sreg(instr_hndlr_info,
            1, dst_reg_id1, srcdst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_2_dreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id, uintptr_t src_reg_id1) {

    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_dreg_sreg_sreg(instr_hndlr_info,
            2, dst_reg_id1, srcdst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id2, uintptr_t src_reg_id1) {

    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_dreg_sreg_sreg(instr_hndlr_info,
            4, dst_reg_id1, srcdst_reg_id2, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_8_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id, uintptr_t src_reg_id1) {

    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_dreg_sreg_sreg(instr_hndlr_info,
            8, dst_reg_id1, srcdst_reg_id, src_reg_id1);
}

/*************************************************************************
 * SRC SRCDST DST - MEM REG REG
 */

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_1_dreg_1_smem_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id1) {

    tb_cc_handle_src_srcdst_dst_whole_dreg_dreg_smem_sreg(instr_hndlr_info, 1,
            dst_reg_id1, srcdst_reg_id, src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_2_dreg_2_smem_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id1) {

    tb_cc_handle_src_srcdst_dst_whole_dreg_dreg_smem_sreg(instr_hndlr_info, 2,
            dst_reg_id1, srcdst_reg_id, src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id1) {

    tb_cc_handle_src_srcdst_dst_whole_dreg_dreg_smem_sreg(instr_hndlr_info, 4,
            dst_reg_id1, srcdst_reg_id, src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_8_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id1,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id1) {

    tb_cc_handle_src_srcdst_dst_whole_dreg_dreg_smem_sreg(instr_hndlr_info, 8,
            dst_reg_id1, srcdst_reg_id, src_mem_id1);
}

