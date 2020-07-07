/*
 * tb_instruction_handler.c

 *
 *      Author: john
 */
#include "tb_instruction_handler.h"
#include "../../tb_bunny_private.h"

static void tb_ih_instr_hndlr_helper(tb_instr_hndlr_t * ih,
        ib_insert_hndle_func_t instr_handler_func, void *user_data,
        IB_INSTRUM_OPT options, ib_spill_regs_func_t spill_reg_func,
        ib_restore_regs_func_t restore_reg_func, void *spill_data) {

    ih->options = options;

    ih->instr_handler_data.user_instrum_func = instr_handler_func;
    ih->instr_handler_data.user_data = user_data;
    ih->instr_handler_data.spill_reg_func = spill_reg_func;
    ih->instr_handler_data.restore_reg_func = restore_reg_func;
    ih->instr_handler_data.spilling_user_data = spill_data;
}

tb_instr_hndlr_t tb_ih_set_inline_instr_hndlr(
        ib_insert_hndle_func_t instr_handler_func, void *user_data,
        IB_INSTRUM_OPT options, ib_spill_regs_func_t spill_reg_func,
        ib_restore_regs_func_t restore_reg_func, void *spill_data) {

    tb_instr_hndlr_t instr_handler;
    instr_handler.is_cached = false;

    tb_ih_instr_hndlr_helper(&instr_handler, instr_handler_func, user_data,
            options, spill_reg_func, restore_reg_func, spill_data);

    return instr_handler;
}

tb_instr_hndlr_t tb_ih_set_cache_instr_hndlr(
        ib_insert_hndle_func_t instr_handler_func, void *user_data,
        IB_INSTRUM_OPT options, ib_spill_regs_func_t spill_reg_func,
        ib_restore_regs_func_t restore_reg_func, void *spill_data) {

    tb_instr_hndlr_t instr_handler;
    instr_handler.is_cached = true;

    tb_ih_instr_hndlr_helper(&instr_handler, instr_handler_func, user_data,
            options, spill_reg_func, restore_reg_func, spill_data);

    return instr_handler;
}

/* Functionality checks */

bool tb_ih_apply_bit_tracking(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
    return tb_ctx->is_fast_path_mode;
}


