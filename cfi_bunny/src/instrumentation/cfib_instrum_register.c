#include "cfib_instrum_register.h"

#include "dr_defines.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"
#include "string.h"
#include <stdio.h>

#include "handlers/cfib_handlers.h"

void cfib_register_detection_hooks(cfib_context_t * cfib_ctx) {

    DR_ASSERT(cfib_ctx->detection_options != CFIB_EV_ERROR);

    if (cfib_ctx->detection_options & CFIB_EV_DETECT_RET) {

        ib_insert_hndle_data_t ret_instrum_data;
        ret_instrum_data.spill_reg_func = NULL;
        ret_instrum_data.restore_reg_func = NULL;
        ret_instrum_data.spilling_user_data = NULL;
        ret_instrum_data.user_instrum_func = cfib_instrument_ret_checker;
        ret_instrum_data.user_data = (void *) cfib_ctx;

        ib_hook_to_instr_ex(cfib_ctx->tool_id, OP_ret, &ret_instrum_data,
                cfib_ctx->instrum_opts | IB_OPT_ADDR_OPND_INFO | IB_OPT_FULL_OPND_INFO, IB_INSTRUM_BEFORE,
                ub_is_ret_instr, IB_GUARD_HOOK);

        ib_insert_hndle_data_t ret_immed_instrum_data;
        ret_immed_instrum_data.spill_reg_func = NULL;
        ret_immed_instrum_data.restore_reg_func = NULL;
        ret_immed_instrum_data.spilling_user_data = NULL;
        ret_immed_instrum_data.user_instrum_func =
                cfib_instrument_ret_immed_checker;
        ret_immed_instrum_data.user_data = (void *) cfib_ctx;

        ib_hook_to_instr_ex(cfib_ctx->tool_id, OP_ret, &ret_immed_instrum_data,
                cfib_ctx->instrum_opts | IB_OPT_ADDR_OPND_INFO | IB_OPT_FULL_OPND_INFO,
                IB_INSTRUM_BEFORE, ub_is_ret_imm_instr, IB_GUARD_HOOK);
    }

    if (cfib_ctx->detection_options & CFIB_EV_DETECT_CALL) {

        ib_insert_hndle_data_t call_ind_reg_instrum_data;
        call_ind_reg_instrum_data.spill_reg_func = NULL;
        call_ind_reg_instrum_data.restore_reg_func = NULL;
        call_ind_reg_instrum_data.spilling_user_data = NULL;
        call_ind_reg_instrum_data.user_instrum_func =
                cfib_instrument_call_reg_checker;
        call_ind_reg_instrum_data.user_data = (void *) cfib_ctx;

        ib_hook_to_instr_ex(cfib_ctx->tool_id, OP_call_ind,
                &call_ind_reg_instrum_data,
                cfib_ctx->instrum_opts | IB_OPT_REG_OPND_INFO | IB_OPT_FULL_OPND_INFO,
                IB_INSTRUM_BEFORE, ub_is_cti_reg_instr, IB_GUARD_HOOK);

        ib_insert_hndle_data_t call_ind_mem_instrum_data;
        call_ind_mem_instrum_data.spill_reg_func = NULL;
        call_ind_mem_instrum_data.restore_reg_func = NULL;
        call_ind_mem_instrum_data.spilling_user_data = NULL;
        call_ind_mem_instrum_data.user_instrum_func =
                cfib_instrument_call_mem_checker;
        call_ind_mem_instrum_data.user_data = (void *) cfib_ctx;

        ib_hook_to_instr_ex(cfib_ctx->tool_id, OP_call_ind,
                &call_ind_mem_instrum_data,
                cfib_ctx->instrum_opts | IB_OPT_ADDR_OPND_INFO | IB_OPT_FULL_OPND_INFO,
                IB_INSTRUM_BEFORE, ub_is_cti_mem_instr, IB_GUARD_HOOK);
    }

    if (cfib_ctx->detection_options & CFIB_EV_DETECT_JMP) {

        int cmp_instrs[17] = { OP_jmp_ind, OP_jo, OP_jno, OP_jb, OP_jnb, OP_jz,
                OP_jnz, OP_jbe, OP_jnbe, OP_js, OP_jns, OP_jp, OP_jnp, OP_jl,
                OP_jnl, OP_jle, OP_jnle };

        ib_insert_hndle_data_t jmp_ind_reg_instrum_data;
        jmp_ind_reg_instrum_data.spill_reg_func = NULL;
        jmp_ind_reg_instrum_data.restore_reg_func = NULL;
        jmp_ind_reg_instrum_data.spilling_user_data = NULL;
        jmp_ind_reg_instrum_data.user_instrum_func =
                cfib_instrument_jmp_reg_checker;
        jmp_ind_reg_instrum_data.user_data = (void *) cfib_ctx;

        // Hate magic numbers for array size, but keep calm; it's just a prototype.
        for (int i = 0; i < 17; i++) {

            ib_hook_to_instr_ex(cfib_ctx->tool_id, cmp_instrs[i],
                    &jmp_ind_reg_instrum_data,
                    cfib_ctx->instrum_opts | IB_OPT_REG_OPND_INFO | IB_OPT_FULL_OPND_INFO,
                    IB_INSTRUM_BEFORE, ub_is_cti_reg_instr, IB_GUARD_HOOK);
        }
    }
}
