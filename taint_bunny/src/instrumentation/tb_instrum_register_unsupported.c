/*
 * tb_instrum_register_unsupported.c
 *
 *      Author: john
 */

#include "tb_instrum_register_unsupported.h"
#include "instrumentation_bunny.h"
#include "../taint_engines/instr_handlers/tb_ih_cc/tb_ih_cc_instrum.h"

/**
 *  Hooks the default code cache to untaint all destination operands of all instruction
 *  which we do not handle for now.
 */
void tb_register_default_hooks(tb_context_t *tb_ctx) {

    /* We dont implement an inlined version for unsupported instructions. */

    ib_insert_hndle_data_t cc_data;
    cc_data.user_data = (void *) tb_ctx;
    cc_data.spill_reg_func = NULL;
    cc_data.restore_reg_func = NULL;
    cc_data.spilling_user_data = NULL;
    cc_data.user_instrum_func = tb_ih_cc_insert_unsupported_handle;

    // We require the number of srcs and dsts opnds, as wll as the

    const IB_INSTRUM_OPT default_option = tb_ctx->instrum_options |
            IB_OPT_FULL_OPND_INFO | IB_OPT_REG_OPND_INFO | IB_OPT_ADDR_OPND_INFO | IB_OPT_OPND_COUNT_INFO | IB_OPT_LOC_SIZE_INFO
            | IB_OPT_LOC_TYPE_INFO | IB_OPT_PC_INFO;

    ib_hook_to_default(tb_ctx->tool_info, &cc_data, default_option);
}

