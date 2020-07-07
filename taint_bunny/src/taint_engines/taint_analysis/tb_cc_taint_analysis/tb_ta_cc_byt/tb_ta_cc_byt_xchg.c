/*
 * tb_ta_cc_byt_xchg.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_xchg.h"

#include <stdint.h>
#include "utility_bunny.h"
#include "../tb_ta_cc_byt_functionality.h"
#include "../../../../tls_access/tb_tls_access.h"
#include "../../../../tb_bunny_private.h"
#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

/*****************************************************************************
 * XCHG HELPER
 */
static void tb_cc_handle_xchg_reg_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        size_t size, uintptr_t reg_id1, uintptr_t reg_id2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i++) {

        void *label1 = tb_cc_arraymap_get_reg_taint_label(reg_map, reg_id1 + i);
        void *label2 = tb_cc_arraymap_get_reg_taint_label(reg_map, reg_id2 + i);

        bool temp_res = tb_ta_cc_prop_xchg_reg_reg(instr_hndlr_info, reg_map,
                reg_id1 + i, label1, reg_id2 + i, label2, !succ);

        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_xchg_mem_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        size_t size, uintptr_t addr_id1, uintptr_t reg_id2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i++) {

        void *label1 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                addr_id1 + i);
        void *label2 = tb_cc_arraymap_get_reg_taint_label(reg_map, reg_id2 + i);

        bool temp_res = tb_ta_cc_prop_xchg_mem_reg(instr_hndlr_info, reg_map,
                addr_id1 + i, label1, reg_id2 + i, label2, !succ);

        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_hp_xchg_reg_mem(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t reg_id1, uintptr_t mem_id2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);

    bool succ = false;
    for (size_t i = 0; i < size; i++) {

        void *label1 = tb_cc_arraymap_get_reg_taint_label(reg_map, reg_id1 + i);
        void *label2 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                mem_id2 + i);

        bool temp_res = tb_ta_cc_prop_xchg_mem_reg(instr_hndlr_info, reg_map,
                mem_id2 + i, label2, reg_id1 + i, label1, !succ);
        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

/*****************************************************************************
 * XCHG SRCDST SRCDST - DREG DREG
 */

void tb_cc_byt_handle_xchg_reg_1_reg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_reg_reg(instr_hndlr_info, 1, reg_id1, reg_id2);
}

void tb_cc_byt_handle_xchg_reg_2_reg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_reg_reg(instr_hndlr_info, 2, reg_id1, reg_id2);
}

void tb_cc_byt_handle_xchg_reg_4_reg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_reg_reg(instr_hndlr_info, 4, reg_id1, reg_id2);
}

void tb_cc_byt_handle_xchg_reg_8_reg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_reg_reg(instr_hndlr_info, 8, reg_id1, reg_id2);
}

/*****************************************************************************
 * XCHG SRCDST SRCDST - DMEM DREG
 */

void tb_cc_byt_handle_xchg_mem_1_reg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_mem_reg(instr_hndlr_info, 1, addr_id1, reg_id2);
}

void tb_cc_byt_handle_xchg_mem_2_reg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_mem_reg(instr_hndlr_info, 2, addr_id1, reg_id2);
}

void tb_cc_byt_handle_xchg_mem_4_reg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_mem_reg(instr_hndlr_info, 4, addr_id1, reg_id2);
}

void tb_cc_byt_handle_xchg_mem_8_reg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2) {

    tb_cc_handle_xchg_mem_reg(instr_hndlr_info, 8, addr_id1, reg_id2);
}

/*****************************************************************************
 * XCHG SRCDST SRCDST - DREG DMEM
 */

void tb_cc_byt_handle_xchg_reg_1_mem_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2) {

    tb_cc_handle_hp_xchg_reg_mem(instr_hndlr_info, 1, reg_id1, mem_id2);
}

void tb_cc_byt_handle_xchg_reg_2_mem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2) {

    tb_cc_handle_hp_xchg_reg_mem(instr_hndlr_info, 2, reg_id1, mem_id2);
}

void tb_cc_byt_handle_xchg_reg_4_mem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2) {

    tb_cc_handle_hp_xchg_reg_mem(instr_hndlr_info, 4, reg_id1, mem_id2);
}

void tb_cc_byt_handle_xchg_reg_8_mem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2) {

    tb_cc_handle_hp_xchg_reg_mem(instr_hndlr_info, 8, reg_id1, mem_id2);
}

/********************************************************************
 * BSWAP HELPERS
 */

static void tb_cc_handle_bswap_dreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;
    void *reg_map = tb_get_reg_map(tb_ctx);

    uintptr_t srcdst_reg_id_end = srcdst_reg_id + (size - 1);

    for (size_t i = 0; i < size / 2; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);
        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id_end);

        void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);
        void *result_label2 = tb_ctx->propogate_func_1dst_1src(src_label2);

        bool temp_res = tb_ta_cc_prop_xchg_reg_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, srcdst_reg_id_end,
                result_label2, !succ);

        succ = succ || temp_res;

        srcdst_reg_id_end--;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_bswap_dmem_smem(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;
    void *reg_map = tb_get_reg_map(tb_ctx);

    uintptr_t srcdst_reg_id_end = srcdst_reg_id + (size - 1);

    for (size_t i = 0; i < size / 2; i++) {

        void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                srcdst_reg_id + i);
        void *src_label2 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                srcdst_reg_id_end);

        void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);
        void *result_label2 = tb_ctx->propogate_func_1dst_1src(src_label2);

        bool temp_res = tb_ta_cc_prop_xchg_mem_mem(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, srcdst_reg_id_end,
                result_label2, !succ);
        succ = succ || temp_res;

        srcdst_reg_id_end--;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

/********************************************************************
 * SRCDST - DREG
 */

void tb_cc_byt_handle_bswap_dsreg_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id) {

    tb_cc_handle_bswap_dreg_sreg(instr_hndlr_info, 4, srcdst_reg_id);
}

void tb_cc_byt_handle_bswap_dsreg_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id) {

    tb_cc_handle_bswap_dreg_sreg(instr_hndlr_info, 8, srcdst_reg_id);
}

/********************************************************************
 * SRCDST - DMEM
 */

void tb_cc_byt_handle_bswap_dsmem_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id) {

    tb_cc_handle_bswap_dmem_smem(instr_hndlr_info, 4, srcdst_reg_id);
}

void tb_cc_byt_handle_bswap_dsmem_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id) {

    tb_cc_handle_bswap_dmem_smem(instr_hndlr_info, 8, srcdst_reg_id);
}

static void tb_cc_byt_handle_xadd_reg_reg(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        uintptr_t reg_id1, uintptr_t reg_id2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);

    void *meet_src_label = NULL;
    void *meet_src_label2 = NULL;

    bool succ = false;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                reg_id1 + i);
        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                reg_id2 + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label, src_label);
        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop1 && stop2)
            break;
    }

    if (tb_ctx->new_ref_func) {

        if (meet_src_label)
            tb_ctx->new_ref_func(meet_src_label);

        if (meet_src_label2)
            tb_ctx->new_ref_func(meet_src_label2);
    }

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                reg_id1 + i);

        void *result_label1 = tb_ctx->propogate_func_1dst_1src(src_label);
        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                reg_id2 + i, result_label1, !succ);
        succ = succ || temp_res;
    }


    for (size_t i = 0; i < size; i++) {

        void *result_label1 = tb_ctx->propogate_func_1dst_2src(meet_src_label,
                meet_src_label2);
        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                reg_id1 + i, result_label1, !succ);
        succ = succ || temp_res;
    }

    if (tb_ctx->delete_ref_func) {

        if (meet_src_label)
            tb_ctx->delete_ref_func(meet_src_label);

        if (meet_src_label2)
            tb_ctx->delete_ref_func(meet_src_label2);
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_xadd_reg_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_reg_reg(instr_hndlr_info, 1, reg_id1, reg_id2);
}

void tb_cc_byt_handle_xadd_reg_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_reg_reg(instr_hndlr_info, 2, reg_id1, reg_id2);
}

void tb_cc_byt_handle_xadd_reg_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_reg_reg(instr_hndlr_info, 4, reg_id1, reg_id2);
}

void tb_cc_byt_handle_xadd_reg_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_reg_reg(instr_hndlr_info, 8, reg_id1, reg_id2);
}

static void tb_cc_byt_handle_xadd_mem_reg(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, size_t size,
        uintptr_t mem_id1, uintptr_t reg_id2) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);

    void *meet_src_label = NULL;
    void *meet_src_label2 = NULL;

    bool succ = false;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                mem_id1 + i);
        void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                reg_id2 + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label, src_label);
        bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);

        if (stop1 && stop2)
            break;
    }

    if (tb_ctx->new_ref_func) {

        if (meet_src_label)
            tb_ctx->new_ref_func(meet_src_label);

        if (meet_src_label2)
            tb_ctx->new_ref_func(meet_src_label2);
    }

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                mem_id1 + i);

        void *result_label1 = tb_ctx->propogate_func_1dst_1src(src_label);
        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                reg_id2 + i, result_label1, !succ);
        succ = succ || temp_res;
    }

    for (size_t i = 0; i < size; i++) {

        void *result_label1 = tb_ctx->propogate_func_1dst_2src(meet_src_label,
                meet_src_label2);
        bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, mem_id1 + i,
                result_label1, !succ);
        succ = succ || temp_res;
    }

    if (tb_ctx->delete_ref_func) {

        if (meet_src_label)
            tb_ctx->delete_ref_func(meet_src_label);

        if (meet_src_label2)
            tb_ctx->delete_ref_func(meet_src_label2);
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_xadd_mem_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_mem_reg(instr_hndlr_info, 1, mem_id1, reg_id2);
}

void tb_cc_byt_handle_xadd_mem_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_mem_reg(instr_hndlr_info, 2, mem_id1, reg_id2);
}

void tb_cc_byt_handle_xadd_mem_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_mem_reg(instr_hndlr_info, 4, mem_id1, reg_id2);
}

void tb_cc_byt_handle_xadd_mem_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id1,
        uintptr_t reg_id2) {

    tb_cc_byt_handle_xadd_mem_reg(instr_hndlr_info, 8, mem_id1, reg_id2);
}

