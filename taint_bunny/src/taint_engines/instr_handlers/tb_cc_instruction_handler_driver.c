/*
 * taint_engine.c
 *
 *      Author: john
 */

#include "tb_cc_instruction_handler_driver.h"
#include "tb_instruction_handler.h"
#include "tb_ih_cc/tb_ih_cc_instrum.h"

tb_te_instr_hndlrs_t *tb_ih_cc_init_instr_handlers(tb_context_t *tb_ctx,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info) {

    tb_te_instr_hndlrs_t *instr_hndlrs =
            (tb_te_instr_hndlrs_t *) dr_global_alloc(
                    sizeof(tb_te_instr_hndlrs_t));

    if (tb_ctx->is_inline) {
        tb_ih_cc_in_init_instr_hndlrs(instr_hndlrs, pre_info, post_info,
                tb_ctx);
    } else {
        tb_ih_cc_cache_init_instr_hndlrs(instr_hndlrs, pre_info, post_info,
                tb_ctx);
    }

    return instr_hndlrs;
}

void tb_ih_cc_destroy_instr_hndlrs(tb_te_instr_hndlrs_t * instr_hndlrs) {

    DR_ASSERT(instr_hndlrs);
    dr_global_free(instr_hndlrs, sizeof(tb_te_instr_hndlrs_t));
}
