/*
 * tb_ta_cc_byt_srcdst.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_srcdst.h"

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

static void tb_cc_handle_srcdst_dreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);

        void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_srcdst_whole_dreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    void *meet_src_label = NULL;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                srcdst_reg_id + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label, src_label);

        if (stop1)
            break;
    }

    if (tb_ctx->new_ref_func) {

        if (meet_src_label)
            tb_ctx->new_ref_func(meet_src_label);
    }

    for (size_t i = 0; i < size; i++) {

        void *result_label = tb_ctx->propogate_func_1dst_1src(meet_src_label);

        bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                srcdst_reg_id + i, result_label, !succ);
        succ = succ || temp_res;
    }

    if (tb_ctx->delete_ref_func) {

        if (meet_src_label)
            tb_ctx->delete_ref_func(meet_src_label);
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_srcdst_dmem_smem(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                srcdst_reg_id + i);

        void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

        bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, srcdst_reg_id + i,
                result_label, !succ);
        succ = succ || temp_res;
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_srcdst_whole_dmem_smem(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    bool succ = false;

    void *meet_src_label = NULL;

    for (size_t i = 0; i < size; i++) {

        void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                srcdst_reg_id + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label, src_label);

        if (stop1)
            break;
    }


    if (tb_ctx->new_ref_func) {

        if (meet_src_label)
            tb_ctx->new_ref_func(meet_src_label);
    }
    for (size_t i = 0; i < size; i++) {

        void *result_label = tb_ctx->propogate_func_1dst_1src(meet_src_label);

        bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, srcdst_reg_id + i,
                result_label, !succ);
        succ = succ || temp_res;
    }

    if (tb_ctx->delete_ref_func) {

        if (meet_src_label)
            tb_ctx->delete_ref_func(meet_src_label);
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

/**************************************************************
 * SRCDST DREG
 */

void tb_cc_byt_handle_srcdst_dsreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dreg_sreg(instr_hndlr_info, 1, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dreg_sreg(instr_hndlr_info, 2, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dreg_sreg(instr_hndlr_info, 4, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dreg_sreg(instr_hndlr_info, 8, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dreg_sreg(instr_hndlr_info, 16, srcdst_reg_id);

}


/**************************************************************
 * SRCDST DREG (WHOLE)
 */

void tb_cc_byt_handle_srcdst_whole_dsreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 1, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 2, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 4, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 8, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dreg_sreg(instr_hndlr_info, 16, srcdst_reg_id);

}

/**************************************************************
 * SRCDST DMEM
 */

void tb_cc_byt_handle_srcdst_dsmem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dmem_smem(instr_hndlr_info, 1, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsmem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dmem_smem(instr_hndlr_info, 2, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsmem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dmem_smem(instr_hndlr_info, 4, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsmem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dmem_smem(instr_hndlr_info, 8, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_dsmem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_dmem_smem(instr_hndlr_info, 16, srcdst_reg_id);
}

/**************************************************************
 * SRCDST DMEM (WHOLE)
 */

void tb_cc_byt_handle_srcdst_whole_dsmem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 1, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsmem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 2, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsmem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 4, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsmem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 8, srcdst_reg_id);
}

void tb_cc_byt_handle_srcdst_whole_dsmem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id) {

    tb_cc_handle_srcdst_whole_dmem_smem(instr_hndlr_info, 16, srcdst_reg_id);
}
