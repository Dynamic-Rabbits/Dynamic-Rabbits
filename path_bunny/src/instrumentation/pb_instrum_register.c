/*
 * pb_instrument.c
 *
 *      Author: john
 */

#include "dr_defines.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"
#include "string.h"
#include <stdio.h>
#include "pb_instrum_register.h"
#include "handlers/pb_handlers.h"
#include "pb_spill.h"

void pb_register_standard_cmp(pb_context_t * pb_ctx,
        ib_insert_hndle_data_t *cache_data, IB_INSTRUM_OPT options,
        int cmp_instr) {

    DR_ASSERT(cmp_instr == OP_test || cmp_instr == OP_cmp);

    cache_data->spill_reg_func = pb_spill_four_regs;
    cache_data->restore_reg_func = pb_restore_four_regs;

    if (pb_ctx->funcs.pb_cmp_reg_1_tainted_mem_1_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_1_mem_1_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_1_tainted_mem_1_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_1_smem_1_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_1_smem_1_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_reg_2_tainted_mem_2_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_2_mem_2_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_2_tainted_mem_2_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_2_smem_2_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_2_smem_2_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_reg_4_tainted_mem_4_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_4_mem_4_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_4_tainted_mem_4_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_4_smem_4_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_4_smem_4_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_reg_8_tainted_mem_8_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_8_mem_8_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_8_tainted_mem_8_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_8_smem_8_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_8_smem_8_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_mem_1_tainted_reg_1_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_1_reg_1_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_1_tainted_reg_1_func) {

        cache_data->user_instrum_func = pb_instrument_smem_1_sreg_1_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options,
                IB_INSTRUM_BEFORE, ub_is_cmp_smem_1_sreg_1_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_mem_2_tainted_reg_2_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_2_reg_2_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_2_tainted_reg_2_func) {

        cache_data->user_instrum_func = pb_instrument_smem_2_sreg_2_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_smem_2_sreg_2_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_mem_4_tainted_reg_4_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_4_reg_4_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_4_tainted_reg_4_func) {

        cache_data->user_instrum_func = pb_instrument_smem_4_sreg_4_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_smem_4_sreg_4_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_mem_8_tainted_reg_8_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_8_reg_8_func
            || pb_ctx->funcs.pb_cmp_tainted_mem_8_tainted_reg_8_func) {

        cache_data->user_instrum_func = pb_instrument_smem_8_sreg_8_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_smem_8_sreg_8_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_reg_1_tainted_reg_1_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_1_reg_1_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_1_tainted_reg_1_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_1_sreg_1_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_1_sreg_1_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_reg_2_tainted_reg_2_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_2_reg_2_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_2_tainted_reg_2_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_2_sreg_2_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_2_sreg_2_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_reg_4_tainted_reg_4_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_4_reg_4_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_4_tainted_reg_4_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_4_sreg_4_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_4_sreg_4_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_reg_8_tainted_reg_8_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_8_reg_8_func
            || pb_ctx->funcs.pb_cmp_tainted_reg_8_tainted_reg_8_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_8_sreg_8_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_8_sreg_8_instr,
                IB_GUARD_HOOK);
    }

    cache_data->spill_reg_func = pb_spill_three_regs;
    cache_data->restore_reg_func = pb_restore_three_regs;

    if (pb_ctx->funcs.pb_cmp_tainted_reg_1_imm_1_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_1_simm_1_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_1_simm_1_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_tainted_reg_2_imm_2_func) {

        cache_data->user_instrum_func = pb_instrument_sreg_2_simm_2_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_2_simm_2_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_tainted_reg_4_imm_4_func) {
        cache_data->user_instrum_func = pb_instrument_sreg_4_simm_4_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_sreg_4_simm_4_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_tainted_mem_1_imm_1_func) {
        cache_data->user_instrum_func = pb_instrument_smem_1_simm_1_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_smem_1_simm_1_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_tainted_reg_2_imm_2_func) {
        cache_data->user_instrum_func = pb_instrument_smem_2_simm_2_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_smem_2_simm_2_instr,
                IB_GUARD_HOOK);
    }

    if (pb_ctx->funcs.pb_cmp_tainted_reg_4_imm_4_func) {
        cache_data->user_instrum_func = pb_instrument_smem_4_simm_4_check;
        ib_hook_cache_to_instr_ex(pb_ctx->tool_id, cmp_instr, cache_data,
                options, IB_INSTRUM_BEFORE, ub_is_cmp_smem_4_simm_4_instr,
                IB_GUARD_HOOK);
    }
}

void pb_register_cmp_hooks(pb_context_t * pb_ctx) {

    if ((pb_ctx->pb_opts & PB_EV_REP_CMP))
        DR_ASSERT_MSG(false, "PB options not yet implemented.");

    ib_insert_hndle_data_t cache_data;
    cache_data.spilling_user_data = NULL;
    cache_data.user_data = pb_ctx;

    IB_INSTRUM_OPT options = pb_ctx->ib_options | IB_OPT_REG_OPND_INFO
            | IB_OPT_IMMED_OPND_INFO | IB_OPT_ADDR_OPND_INFO | IB_OPT_FULL_OPND_INFO;

    if (pb_ctx->pb_opts & PB_EV_CMP) {

        pb_register_standard_cmp(pb_ctx, &cache_data, options, OP_cmp);

        cache_data.spill_reg_func = pb_spill_four_regs;
        cache_data.restore_reg_func = pb_restore_four_regs;

        if (pb_ctx->funcs.pb_cmp_mem_1_tainted_mem_1_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_1_mem_1_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_1_tainted_mem_1_func) {

            cache_data.user_instrum_func = pb_instrument_smem_1_smem_1_check;
            ib_hook_cache_to_instr_ex(pb_ctx->tool_id, OP_cmps, &cache_data,
                    options, IB_INSTRUM_BEFORE, ub_is_cmp_smem_1_smem_1_instr,
                    IB_GUARD_HOOK);
        }

        if (pb_ctx->funcs.pb_cmp_mem_2_tainted_mem_2_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_2_mem_2_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_2_tainted_mem_2_func) {

            cache_data.user_instrum_func = pb_instrument_smem_2_smem_2_check;
            ib_hook_cache_to_instr_ex(pb_ctx->tool_id, OP_cmps, &cache_data,
                    options,
                    IB_INSTRUM_BEFORE, ub_is_cmp_smem_2_smem_2_instr,
                    IB_GUARD_HOOK);
        }

        if (pb_ctx->funcs.pb_cmp_mem_4_tainted_mem_4_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_4_mem_4_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_4_tainted_mem_4_func) {

            cache_data.user_instrum_func = pb_instrument_smem_4_smem_4_check;
            ib_hook_cache_to_instr_ex(pb_ctx->tool_id, OP_cmps, &cache_data,
                    options,
                    IB_INSTRUM_BEFORE, ub_is_cmp_smem_4_smem_4_instr,
                    IB_GUARD_HOOK);
        }

        if (pb_ctx->funcs.pb_cmp_mem_8_tainted_mem_8_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_8_mem_8_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_8_tainted_mem_8_func) {

            cache_data.user_instrum_func = pb_instrument_smem_8_smem_8_check;
            ib_hook_cache_to_instr_ex(pb_ctx->tool_id, OP_cmps, &cache_data,
                    options,
                    IB_INSTRUM_BEFORE, ub_is_cmp_smem_8_smem_8_instr,
                    IB_GUARD_HOOK);
        }

    }

    if (pb_ctx->pb_opts & PB_EV_TEST) {

        pb_register_standard_cmp(pb_ctx, &cache_data, options, OP_test);
    }

    /**
     * TODO: Support REP instructions.
     * Keep calm, it's just a prototype.
     */

//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_scas,
//            instrument_rep_scas_m8_m8_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, cmp_guard_m8_m8);
//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_scas,
//            instrument_rep_scas_m16_m16_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, cmp_guard_m16_m16);
//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_scas,
//            instrument_rep_scas_m32_m32_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, cmp_guard_m32_m32);
//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_scas,
//            instrument_rep_scas_m64_m64_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, cmp_guard_m64_m64);
//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_cmps,
//            instrument_rep_cmp_m8_m8_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, ub_is_cmp_smem_1_smem_1_instr);
//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_cmps,
//            instrument_rep_cmp_m16_m16_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, ub_is_cmp_smem_2_smem_2_instr);
//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_cmps,
//            instrument_rep_cmp_m32_m32_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, ub_is_cmp_smem_4_smem_4_instr);
//    ib_hook_to_instr_ex(pb_ctx->tool_id, OP_rep_cmps,
//            instrument_rep_cmp_m64_m64_check, (void *) pb_ctx,
//            options,
//            IB_INSTRUM_BEFORE, ub_is_cmp_smem_8_smem_8_instr);

    if (pb_ctx->pb_opts & PB_EV_PSIMD) {

        /* TODO: Consider pcmp instructions */

        cache_data.spill_reg_func = pb_spill_four_regs;
        cache_data.restore_reg_func = pb_restore_four_regs;

        if (pb_ctx->funcs.pb_cmp_reg_16_tainted_mem_16_func
                || pb_ctx->funcs.pb_cmp_tainted_reg_16_mem_16_func
                || pb_ctx->funcs.pb_cmp_tainted_reg_16_tainted_mem_16_func) {
            cache_data.user_instrum_func = pb_instrument_sreg_16_smem_16_check;
            ib_hook_to_instr_ex(pb_ctx->tool_id, OP_ptest, &cache_data, options,
            IB_INSTRUM_BEFORE, ub_is_cmp_sreg_16_smem_16_instr, IB_GUARD_HOOK);
        }

        if (pb_ctx->funcs.pb_cmp_mem_16_tainted_reg_16_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_16_reg_16_func
                || pb_ctx->funcs.pb_cmp_tainted_mem_16_tainted_reg_16_func) {
            cache_data.user_instrum_func = pb_instrument_smem_16_sreg_16_check;
            ib_hook_to_instr_ex(pb_ctx->tool_id, OP_ptest, &cache_data, options,
            IB_INSTRUM_BEFORE, ub_is_cmp_smem_16_sreg_16_instr, IB_GUARD_HOOK);
        }

        if (pb_ctx->funcs.pb_cmp_reg_16_tainted_reg_16_func
                || pb_ctx->funcs.pb_cmp_tainted_reg_16_reg_16_func
                || pb_ctx->funcs.pb_cmp_tainted_reg_16_tainted_reg_16_func) {
            cache_data.user_instrum_func = pb_instrument_sreg_16_sreg_16_check;
            ib_hook_to_instr_ex(pb_ctx->tool_id, OP_ptest, &cache_data, options,
            IB_INSTRUM_BEFORE, ub_is_cmp_sreg_16_sreg_16_instr, IB_GUARD_HOOK);
        }
    }
}
