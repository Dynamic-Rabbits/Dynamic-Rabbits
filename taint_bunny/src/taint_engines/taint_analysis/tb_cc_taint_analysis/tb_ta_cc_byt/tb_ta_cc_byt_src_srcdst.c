/*
 * tb_ta_cc_byt_src_srcdst.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_src_srcdst.h"

#include "../tb_ta_cc_byt_functionality.h"
#include "../../../../tb_bunny_private.h"
#include "../../../../tls_access/tb_tls_access.h"
#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#include "utility_bunny.h"

#include <stdint.h>

/**************************************************************************************
 * SRC SRCDST - DREG SREG SREG (WHOLE)
 */

static void tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t dsize, size_t ssize,
        uintptr_t srcdst_reg_id, uintptr_t src_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    for (size_t i = 0; i < ssize; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                src_reg_id + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);

        if (stop1)
            break;
    }

    for (size_t i = 0; i < dsize; i++) {

        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);

        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop2)
            break;
    }

    if (tb_ctx->new_ref_func) {

        if (meet_src_label1)
            tb_ctx->new_ref_func(meet_src_label1);

        if (meet_src_label2)
            tb_ctx->new_ref_func(meet_src_label2);
    }

    for (size_t i = 0; i < dsize; i++) {

        void *result_label = tb_ctx->propogate_func_1dst_2src(meet_src_label1,
                meet_src_label2);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
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

void tb_cc_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 1, 1,
            dst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 2, 2,
            dst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 4, 4,
            dst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 8,
            dst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 16,
            dst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 2, 1,
            dst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 4, 1,
            dst_reg_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 1,
            dst_reg_id, src_reg_id1);

}

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG (WHOLE)
 */

static void tb_cc_handle_whole_dreg_smem_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id1) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;
    void *reg_map = tb_get_reg_map(tb_ctx);

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

    if (tb_ctx->new_ref_func) {

        if (meet_src_label1)
            tb_ctx->new_ref_func(meet_src_label1);

        if (meet_src_label2)
            tb_ctx->new_ref_func(meet_src_label2);
    }

    for (size_t i = 0; i < size; i++) {

        void *result_label = tb_ctx->propogate_func_1dst_2src(meet_src_label1,
                meet_src_label2);
        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
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

void tb_cc_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_whole_dreg_smem_sreg(instr_hndlr_info, 1, dst_reg_id,
            src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_whole_dreg_smem_sreg(instr_hndlr_info, 2, dst_reg_id,
            src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_4_smem_4_sreg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_whole_dreg_smem_sreg(instr_hndlr_info, 4, dst_reg_id,
            src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_whole_dreg_smem_sreg(instr_hndlr_info, 8, dst_reg_id,
            src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_whole_dreg_smem_sreg(instr_hndlr_info, 16, dst_reg_id,
            src_mem_id1);
}

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM (WHOLE)
 */

static void tb_cc_handle_whole_dmem_sreg_smem(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t dsize, size_t ssize,
        uintptr_t srcdst_mem_id, uintptr_t src_reg_id1) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;
    void *reg_map = tb_get_reg_map(tb_ctx);

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    for (size_t i = 0; i < ssize; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                src_reg_id1 + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);

        if (stop1)
            break;
    }

    for (size_t i = 0; i < dsize; i++) {

        void *src_label2 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                srcdst_mem_id + i);

        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop2)
            break;
    }

    if (tb_ctx->new_ref_func) {

        if (meet_src_label1)
            tb_ctx->new_ref_func(meet_src_label1);

        if (meet_src_label2)
            tb_ctx->new_ref_func(meet_src_label2);
    }


    for (size_t i = 0; i < dsize; i++) {

        void *result_label = tb_ctx->propogate_func_1dst_2src(meet_src_label1,
                meet_src_label2);

        bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, srcdst_mem_id + i,
                result_label, !succ);
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

void tb_cc_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 1, 1, dst_mem_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 2, 2, dst_mem_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 4, 4, dst_mem_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_8_smem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 8, 8, dst_mem_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dmem_16_sreg_16_smem_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 16, 16, dst_mem_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_1_smem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 2, 1, dst_mem_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_1_smem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 4, 1, dst_mem_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_1_smem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_whole_dmem_sreg_smem(instr_hndlr_info, 8, 1, dst_mem_id,
            src_reg_id1);
}

/**************************************************************************************
 * SRC SRCDST - DREG SREG SREG
 */

static void tb_cc_handle_src_srcdst_dreg_sreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id, uintptr_t src_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                src_reg_id + i);
        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);

        void *result_label = tb_ctx->propogate_func_1dst_2src(src_label,
                src_label2);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 1, dst_reg_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 2, dst_reg_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_4_sreg_4_sreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 4, dst_reg_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, dst_reg_id,
            src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, dst_reg_id,
            src_reg_id1);
}

/**************************************************************************************
 * SRC SRCDST - DREG SMEM DREG
 */

static void tb_cc_handle_dreg_smem_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id1) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;
    void *reg_map = tb_get_reg_map(tb_ctx);

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                src_mem_id1 + i);
        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);

        void *result_label = tb_ctx->propogate_func_1dst_2src(src_label,
                src_label2);
        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_dreg_smem_sreg(instr_hndlr_info, 1, dst_reg_id, src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_dreg_smem_sreg(instr_hndlr_info, 2, dst_reg_id, src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_4_smem_4_sreg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_dreg_smem_sreg(instr_hndlr_info, 4, dst_reg_id, src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_dreg_smem_sreg(instr_hndlr_info, 8, dst_reg_id, src_mem_id1);
}

void tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
        uintptr_t src_mem_id1) {

    tb_cc_handle_dreg_smem_sreg(instr_hndlr_info, 16, dst_reg_id, src_mem_id1);
}

/**************************************************************************************
 * SRC SRCDST - DMEM SREG DMEM
 */

static void tb_cc_handle_dmem_sreg_smem(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_mem_id, uintptr_t src_reg_id1) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;
    void *reg_map = tb_get_reg_map(tb_ctx);

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                src_reg_id1 + i);
        void *src_label2 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                srcdst_mem_id + i);

        void *result_label = tb_ctx->propogate_func_1dst_2src(src_label,
                src_label2);

        bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, srcdst_mem_id + i,
                result_label, !succ);
        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_dmem_sreg_smem(instr_hndlr_info, 1, dst_mem_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_dmem_sreg_smem(instr_hndlr_info, 2, dst_mem_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dmem_4_sreg_4_smem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_dmem_sreg_smem(instr_hndlr_info, 4, dst_mem_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dmem_8_sreg_8_smem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_dmem_sreg_smem(instr_hndlr_info, 8, dst_mem_id, src_reg_id1);
}

void tb_cc_byt_handle_src_srcdst_dmem_16_sreg_16_smem_16(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_mem_id,
        uintptr_t src_reg_id1) {

    tb_cc_handle_dmem_sreg_smem(instr_hndlr_info, 16, dst_mem_id, src_reg_id1);
}

