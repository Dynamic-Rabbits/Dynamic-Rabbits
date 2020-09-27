/*
 * tb_ta_cc_byt_p_src_srcdst.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_p_src_srcdst.h"

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

static void tb_cc_handle_px_src_srcdst_whole_dreg_sreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        size_t word_size, uintptr_t srcdst_reg_id, uintptr_t src_reg_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i += word_size) {

        void *meet_src_label1 = NULL;
        void *meet_src_label2 = NULL;

        for (size_t j = 0; j < word_size; j++) {

            void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                    src_reg_id + i + j);
            void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                    srcdst_reg_id + i + j);

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

        for (size_t j = 0; j < word_size; j++) {

            void *result_label = tb_ctx->propogate_func_1dst_2src(
                    meet_src_label1, meet_src_label2);

            bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                    srcdst_reg_id + i + j, result_label, !succ);
            succ = succ || temp_res;
        }

        if (tb_ctx->delete_ref_func) {

            if (meet_src_label1)
                tb_ctx->delete_ref_func(meet_src_label1);

            if (meet_src_label2)
                tb_ctx->delete_ref_func(meet_src_label2);
        }

    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_px_src_srcdst_whole_dreg_smem_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        size_t word_size, uintptr_t srcdst_reg_id, uintptr_t src_mem_id) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i += word_size) {

        void *meet_src_label1 = NULL;
        void *meet_src_label2 = NULL;

        for (size_t j = 0; j < word_size; j++) {

            void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                    src_mem_id + i + j);
            void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                    srcdst_reg_id + i + j);

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

        for (size_t j = 0; j < word_size; j++) {

            void *result_label = tb_ctx->propogate_func_1dst_2src(
                    meet_src_label1, meet_src_label2);

            bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                    srcdst_reg_id + i + j, result_label, !succ);
            succ = succ || temp_res;
        }

        if (tb_ctx->delete_ref_func) {

            if (meet_src_label1)
                tb_ctx->delete_ref_func(meet_src_label1);

            if (meet_src_label2)
                tb_ctx->delete_ref_func(meet_src_label2);
        }
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

/**************************************************************
 * PW SRC SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 2,
            srcdst_reg_id, src_reg_id);

}

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 2,
            srcdst_reg_id, src_reg_id);
}

/**************************************************************
 * PW SRC SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 2,
            srcdst_reg_id, src_mem_id);
}

void tb_cc_byt_handle_pw_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 2,
            srcdst_reg_id, src_mem_id);
}

/**************************************************************
 * PD SRC SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
            srcdst_reg_id, src_reg_id);

}

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
            srcdst_reg_id, src_reg_id);

}

/**************************************************************
 * PD SRC SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 4,
            srcdst_reg_id, src_mem_id);
}

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 4,
            srcdst_reg_id, src_mem_id);
}

/**************************************************************
 * PQ SRC SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8, 8,
            srcdst_reg_id, src_reg_id);

}

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16, 8,
            srcdst_reg_id, src_reg_id);

}

/**************************************************************
 * PQ SRC SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8, 8,
            srcdst_reg_id, src_mem_id);
}

void tb_cc_byt_handle_pq_src_srcdst_whole_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_px_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16, 8,
            srcdst_reg_id, src_mem_id);
}

/***************************************************************************
 * PMADDWD HELPERS
 */

static void tb_cc_handle_pmaddwd_src_srcdst_whole_dreg_sreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id, uintptr_t src_mem_id) {

    // The instruction adds 2 words between source and destination.
    // Then multiplies adjacent!

    const size_t dw_size = 4;
    const size_t w_size = 2;

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i += dw_size) {

        void *meet_src_label1 = NULL;
        void *meet_src_label2 = NULL;

        for (size_t j = 0; j < w_size; j++) {

            void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                    src_mem_id + i + j);
            void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                    srcdst_reg_id + i + j);
            void *src_label3 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                    src_mem_id + i + j + w_size);
            void *src_label4 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                    srcdst_reg_id + i + j + w_size);

            bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);
            bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);
            bool stop3 = tb_ctx->meet_func(&meet_src_label1, src_label3);
            bool stop4 = tb_ctx->meet_func(&meet_src_label2, src_label4);

            if (stop1 && stop2 && stop3 && stop4)
                break;
        }

        if (tb_ctx->new_ref_func) {

            if (meet_src_label1)
                tb_ctx->new_ref_func(meet_src_label1);

            if (meet_src_label2)
                tb_ctx->new_ref_func(meet_src_label2);
        }

        for (size_t j = 0; j < dw_size; j++) {

            void *result_label = tb_ctx->propogate_func_1dst_2src(
                    meet_src_label1, meet_src_label2);

            bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                    srcdst_reg_id + i + j, result_label, !succ);
            succ = succ || temp_res;
        }

        if (tb_ctx->delete_ref_func) {

            if (meet_src_label1)
                tb_ctx->delete_ref_func(meet_src_label1);

            if (meet_src_label2)
                tb_ctx->delete_ref_func(meet_src_label2);

        }
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

static void tb_cc_handle_pmaddwd_src_srcdst_whole_dreg_smem_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        uintptr_t srcdst_reg_id, uintptr_t src_reg_id) {

    // Adds 2 words between source and destination. Then multiplies adjacent!

    const size_t dw_size = 4;
    const size_t w_size = 2;

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    for (size_t i = 0; i < size; i += dw_size) {

        void *meet_src_label1 = NULL;
        void *meet_src_label2 = NULL;

        for (size_t j = 0; j < w_size; j++) {

            void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                    src_reg_id + i + j);
            void *src_label2 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                    srcdst_reg_id + i + j);
            void *src_label3 = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                    src_reg_id + i + j + w_size);
            void *src_label4 = tb_cc_arraymap_get_reg_taint_label(reg_map,
                    srcdst_reg_id + i + j + w_size);

            bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);
            bool stop2 = tb_ctx->meet_func(&meet_src_label2, src_label2);
            bool stop3 = tb_ctx->meet_func(&meet_src_label1, src_label3);
            bool stop4 = tb_ctx->meet_func(&meet_src_label2, src_label4);

            if (stop1 && stop2 && stop3 && stop4)
                break;
        }

        if (tb_ctx->new_ref_func) {

            if (meet_src_label1)
                tb_ctx->new_ref_func(meet_src_label1);

            if (meet_src_label2)
                tb_ctx->new_ref_func(meet_src_label2);
        }

        for (size_t j = 0; j < dw_size; j++) {

            void *result_label = tb_ctx->propogate_func_1dst_2src(
                    meet_src_label1, meet_src_label2);

            bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                    srcdst_reg_id + i + j, result_label, !succ);
            succ = succ || temp_res;
        }

        if (tb_ctx->delete_ref_func) {

            if (meet_src_label1)
                tb_ctx->delete_ref_func(meet_src_label1);

            if (meet_src_label2)
                tb_ctx->delete_ref_func(meet_src_label2);
        }
    }

    if (succ && instr_hndlr_info->post_prop_func)
        instr_hndlr_info->post_prop_func(tb_ctx);
}

/**************************************************************
 * PMADDWD SRCDST - DREG SREG SREG
 */

void tb_cc_byt_handle_pmaddwd_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_pmaddwd_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 8,
            srcdst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_pmaddwd_src_srcdst_whole_dreg_sreg_sreg(instr_hndlr_info, 16,
            srcdst_reg_id, src_reg_id);
}

/**************************************************************
 * PMADDWD SRCDST - DREG SMEM SREG
 */

void tb_cc_byt_handle_pmaddwd_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_pmaddwd_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 8,
            srcdst_reg_id, src_mem_id);
}

void tb_cc_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_pmaddwd_src_srcdst_whole_dreg_smem_sreg(instr_hndlr_info, 16,
            srcdst_reg_id, src_mem_id);
}
