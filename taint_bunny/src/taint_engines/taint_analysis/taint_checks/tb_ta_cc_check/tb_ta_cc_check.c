/*
 * tb_ta_cc_check.c
 *
 *      Author: john
 */

#include "tb_ta_cc_check.h"

/**********************************************************************************
 * Taint Check
 ***********************************************************************************/

void *tb_ta_cc_get_mem_label(tb_context_t *tb_ctx, uintptr_t addr) {

    DR_ASSERT(tb_ctx->mem_map != NULL);

    return tb_umbra_get_mem_taint_label(tb_ctx->mem_map, addr);
}

void tb_ta_cc_get_mem_labels_from_block(tb_context_t *tb_ctx, uintptr_t addr,
        size_t block_size, size_t label_buf_size, void **label_buf) {

    DR_ASSERT(tb_ctx->mem_map != NULL);
    tb_umbra_get_mem_taint_block_labels(tb_ctx->mem_map, addr,
            block_size, label_buf_size, label_buf);
}

void *tb_ta_cc_get_reg_label(tb_context_t *tb_ctx, void *taint_map,
        unsigned int byte_id) {

    DR_ASSERT(taint_map != NULL);

    return tb_cc_arraymap_get_reg_taint_label(taint_map, byte_id);
}

bool tb_ta_cc_is_some_reg_tainted(tb_context_t *tb_ctx, void *taint_map,
        uintptr_t start_id, size_t block_size) {

    DR_ASSERT(taint_map != NULL);

    for (size_t i = 0; i < block_size; i++) {

        void * label = tb_cc_arraymap_get_reg_taint_label(taint_map,
                start_id + i);

        if (label != NULL) {
            return true;
        }
    }

    return false;
}

bool tb_ta_cc_is_some_mem_tainted(tb_context_t *tb_ctx, uintptr_t start_id,
        size_t block_size) {

    DR_ASSERT(tb_ctx->mem_map != NULL);

    for (size_t i = 0; i < block_size; i++) {

        void *label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
                start_id + i);

        if (label != NULL) {
            return true;
        }
    }

    return false;
}

bool tb_ta_cc_is_all_reg_tainted(tb_context_t *tb_ctx, void *taint_map,
        uintptr_t start_id, size_t block_size) {

    DR_ASSERT(taint_map != NULL);

    for (size_t i = 0; i < block_size; i++) {
        if (tb_cc_arraymap_get_reg_taint_label(taint_map, start_id + i) == NULL)
            return false;
    }

    return true;
}

bool tb_ta_cc_is_all_mem_tainted(tb_context_t *tb_ctx, uintptr_t start_id,
        size_t block_size) {

    DR_ASSERT(tb_ctx->mem_map != NULL);

    for (size_t i = 0; i < block_size; i++) {

        if (tb_umbra_get_mem_taint_label(tb_ctx->mem_map, start_id + i) == NULL)
            return false;
    }

    return true;
}
