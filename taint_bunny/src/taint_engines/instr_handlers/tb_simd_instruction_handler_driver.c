/*
 * tb_simd_instruction_handler_driver.c
 *
 *      Author: john
 */

#include "tb_simd_instruction_handler_driver.h"
#include "tb_instruction_handler.h"
#include "tb_ih_raw/tb_ih_raw_instrum.h"
#include "../../tb_bunny_private.h"

tb_te_instr_hndlrs_t *tb_ih_simd_init_instr_handlers(tb_context_t *tb_ctx,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info) {

    tb_te_instr_hndlrs_t *instr_hndlrs =
            (tb_te_instr_hndlrs_t *) dr_global_alloc(
                    sizeof(tb_te_instr_hndlrs_t));

    if (tb_ctx->is_inline) {
        tb_ih_simd_in_init_instr_hndlrs(instr_hndlrs, pre_info, post_info,
                tb_ctx);
    } else {
        tb_ih_simd_cache_init_instr_hndlrs(instr_hndlrs, pre_info, post_info,
                tb_ctx);
    }

    return instr_hndlrs;
}

void tb_ih_simd_destroy_instr_hndlrs(tb_te_instr_hndlrs_t * instr_hndlrs) {

    DR_ASSERT(instr_hndlrs);
    dr_global_free(instr_hndlrs, sizeof(tb_te_instr_hndlrs_t));
}

