/*
 * tb_ta_cc_byt_punpck.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_punpck.h"

#include "../tb_ta_cc_byt_functionality.h"
#include "../../../../tb_bunny_private.h"
#include "../../../../tls_access/tb_tls_access.h"
#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#include "utility_bunny.h"

#include <stdint.h>

/*************************************************************
 * Helpers
 */

static void tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        size_t word_size, bool is_high, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    // Determine whether or not we have to set high or low part of register
    size_t start = 0;
    size_t src_size = size;

    if (is_high)
        start = size / 2;
    else {
        src_size = size / 2;
    }

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    for (size_t i = start; i < src_size; i++) {

        void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
                src_reg_id + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);

        if (stop1)
            break;
    }

    for (size_t i = start; i < src_size; i++) {

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

    bool weave = false;

    for (size_t i = 0; i < size; i += word_size) {

        if (weave) {
            for (size_t k = 0; k < word_size; k++) {

                void *result_label = tb_ctx->propogate_func_1dst_1src(
                        meet_src_label1);

                bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                        srcdst_reg_id + i + k, result_label, !succ);
                succ = succ || temp_res;
            }
        } else {

            for (size_t k = 0; k < word_size; k++) {

                void *result_label = tb_ctx->propogate_func_1dst_1src(
                        meet_src_label2);

                bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                        srcdst_reg_id + i + k, result_label, !succ);
                succ = succ || temp_res;
            }
        }

        weave = !weave;
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

static void tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
        size_t word_size, bool is_high, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    // Determine whether or not we have to set high or low part of register
    size_t start = 0;
    size_t src_size = size;

    if (is_high)
        start = size / 2;
    else {
        src_size = size / 2;
    }

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    void *reg_map = tb_get_reg_map(tb_ctx);
    bool succ = false;

    void *meet_src_label1 = NULL;
    void *meet_src_label2 = NULL;

    for (size_t i = start; i < src_size; i++) {

        void * src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                src_mem_id + i);

        bool stop1 = tb_ctx->meet_func(&meet_src_label1, src_label);

        if (stop1)
            break;
    }

    for (size_t i = start; i < src_size; i++) {

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

    bool weave = false;

    for (size_t i = 0; i < size; i += word_size) {

        if (weave) {

            for (size_t k = 0; k < word_size; k++) {

                void *result_label = tb_ctx->propogate_func_1dst_1src(
                        meet_src_label1);

                bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                        srcdst_reg_id + i + k, result_label, !succ);
                succ = succ || temp_res;
            }
        } else {

            for (size_t k = 0; k < word_size; k++) {

                void *result_label = tb_ctx->propogate_func_1dst_1src(
                        meet_src_label2);

                bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
                        srcdst_reg_id + i + k, result_label, !succ);
                succ = succ || temp_res;
            }
        }

        weave = !weave;
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

/*************************************************************
 * PUNPCKLBW SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpcklbw_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 1, false,
            srcdst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_low_punpcklbw_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 1, false,
            srcdst_reg_id, src_reg_id);
}

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpcklbw_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 1, false,
            srcdst_reg_id, src_mem_id);
}

void tb_cc_byt_handle_low_punpcklbw_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 1, false,
            srcdst_reg_id, src_mem_id);
}

/*************************************************************
 * PUNPCKLWD SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpcklwd_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 2,
    false, srcdst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 2,
    false, srcdst_reg_id, src_reg_id);

}

/*************************************************************
 * PUNPCKLWD SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpcklwd_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 2,
    false, srcdst_reg_id, src_mem_id);

}

void tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 2,
    false, srcdst_reg_id, src_mem_id);
}

/*************************************************************
 * PUNPCKLDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpckldq_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
    false, srcdst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_low_punpckldq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
    false, srcdst_reg_id, src_reg_id);
}

/*************************************************************
 * PUNPCKLDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpckldq_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 4,
    false, srcdst_reg_id, src_mem_id);
}

void tb_cc_byt_handle_low_punpckldq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 4,
    false, srcdst_reg_id, src_mem_id);
}

/*************************************************************
 * PUNPCKLQDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_low_punpcklqdq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 8,
    false, srcdst_reg_id, src_reg_id);
}

/*************************************************************
 * PUNPCKLQDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_low_punpcklqdq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 8,
    false, srcdst_reg_id, src_mem_id);
}

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhbw_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 1, true,
            srcdst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_high_punpckhbw_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 1, true,
            srcdst_reg_id, src_reg_id);
}

/*************************************************************
 * PUNPCKHBW SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhbw_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 1, true,
            srcdst_reg_id, src_mem_id);
}

void tb_cc_byt_handle_high_punpckhbw_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 1, true,
            srcdst_reg_id, src_mem_id);
}

/*************************************************************
 * PUNPCKHWD SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhwd_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 2,
    true, srcdst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 2,
    true, srcdst_reg_id, src_reg_id);

}

/*************************************************************
 * PUNPCKHWD SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhwd_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 2,
    true, srcdst_reg_id, src_mem_id);

}

void tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 2,
    true, srcdst_reg_id, src_mem_id);
}

/*************************************************************
 * PUNPCKHDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhdq_dreg_8_sreg_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 8, 4,
    true, srcdst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_high_punpckhdq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 4,
    true, srcdst_reg_id, src_reg_id);
}

/*************************************************************
 * PUNPCKHDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhdq_dreg_8_smem_8_sreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 8, 4,
    true, srcdst_reg_id, src_mem_id);

}

void tb_cc_byt_handle_high_punpckhdq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 4,
    true, srcdst_reg_id, src_mem_id);

}

/*************************************************************
 * PUNPCKHQDQ SRC SRCDST - DREG SREG
 */

void tb_cc_byt_handle_high_punpckhqdq_dreg_16_sreg_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_reg_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_sreg_sreg(instr_hndlr_info, 16, 8,
    true, srcdst_reg_id, src_reg_id);
}

/*************************************************************
 * PUNPCKHQDQ SRC SRCDST - DREG SMEM
 */

void tb_cc_byt_handle_high_punpckhqdq_dreg_16_smem_16_sreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id,
        uintptr_t src_mem_id) {

    tb_cc_handle_punpckx_src_srcdst_dreg_smem_sreg(instr_hndlr_info, 16, 8,
    true, srcdst_reg_id, src_mem_id);
}
