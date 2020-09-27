/**
 * @file tb_dispatcher
 * @brief The dispatcher instruments the appr// OPriate taint handles for
 * instructions.
 * @author John F.X. Galea
 */

#include "tb_instrum_register.h"

#include "tb_instrum_register_unsupported.h"
#include "../tb_bunny_private.h"
#include "instrumentation_bunny.h"

/************************************************************************************
 * Prototypes
 */

/************************************************************************************
 * Implementation
 */

void tb_register_instrumentation_hooks(tb_context_t *tb_ctx) {

    const IB_INSTRUM_OPT init_option = tb_ctx->instrum_options;
    tb_te_instr_hndlrs_t *taint_engine = tb_ctx->instr_hndlrs;

    // -- OP_LABEL:
    ib_hook_skip(tb_ctx->tool_info, OP_LABEL);

    // -- OP_add:
    tb_register_srcdst_src_reg(tb_ctx, OP_add, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_1_SMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADD_DMEM_8_SIMM_1]));

    // -- OP_or:
    tb_register_srcdst_src_reg(tb_ctx, OP_or, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_1_SMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_OR_DMEM_8_SIMM_1]));

    // -- OP_adc:
    tb_register_srcdst_src_reg(tb_ctx, OP_adc, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_1_SMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ADC_DMEM_8_SIMM_1]));

    // -- OP_sbb:
    tb_register_srcdst_src_reg(tb_ctx, OP_sbb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_1_SMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SBB_DMEM_8_SIMM_1]));

    // -- OP_and:
    tb_register_srcdst_src_reg(tb_ctx, OP_and, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_1_SMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_AND_DMEM_8_SIMM_1]));

    // -- OP_daa:

    // -- OP_sub:
    tb_register_srcdst_src_reg(tb_ctx, OP_sub, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_1_SMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_1_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_1_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_2_SIMM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_4_SIMM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SUB_DMEM_8_SIMM_1]));

    // -- OP_das:

    // -- OP_xor:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_1_SMEM_1]),
            init_option, ub_is_srcdst_src_dreg_1_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_2_SMEM_2]),
            init_option, ub_is_srcdst_src_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_4_SMEM_4]),
            init_option, ub_is_srcdst_src_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_8_SMEM_8]),
            init_option, ub_is_srcdst_src_dreg_8_smem_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_1_SREG_1]),
            init_option, ub_is_srcdst_src_diff_dreg_1_sreg_1_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_2_SREG_2]),
            init_option, ub_is_srcdst_src_diff_dreg_2_sreg_2_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_4_SREG_4]),
            init_option, ub_is_srcdst_src_diff_dreg_4_sreg_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_8_SREG_8]),
            init_option, ub_is_srcdst_src_diff_dreg_8_sreg_8_instr,
            IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            init_option, ub_is_srcdst_src_same_dreg_1_sreg_1_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_2]),
            init_option, ub_is_srcdst_src_same_dreg_2_sreg_2_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_4]),
            init_option, ub_is_srcdst_src_same_dreg_4_sreg_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_8]),
            init_option, ub_is_srcdst_src_same_dreg_8_sreg_8_instr,
            IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_1_SIMM_1]),
            init_option, ub_is_srcdst_src_dreg_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_2_SIMM_2]),
            init_option, ub_is_srcdst_src_dreg_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_4_SIMM_4]),
            init_option, ub_is_srcdst_src_dreg_4_simm_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_1_SREG_1]),
            init_option, ub_is_srcdst_src_dmem_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_2_SREG_2]),
            init_option, ub_is_srcdst_src_dmem_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_4_SREG_4]),
            init_option, ub_is_srcdst_src_dmem_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_8_SREG_8]),
            init_option, ub_is_srcdst_src_dmem_8_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_1_SIMM_1]),
            init_option, ub_is_srcdst_src_dmem_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_2_SIMM_2]),
            init_option, ub_is_srcdst_src_dmem_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_4_SIMM_4]),
            init_option, ub_is_srcdst_src_dmem_4_simm_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_2_SIMM_1]),
            init_option, ub_is_srcdst_src_dreg_2_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_4_SIMM_1]),
            init_option, ub_is_srcdst_src_dreg_4_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DREG_8_SIMM_1]),
            init_option, ub_is_srcdst_src_dreg_8_simm_1_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_2_SIMM_1]),
            init_option, ub_is_srcdst_src_dmem_2_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_4_SIMM_1]),
            init_option, ub_is_srcdst_src_dmem_4_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XOR_DMEM_8_SIMM_1]),
            init_option, ub_is_srcdst_src_dmem_8_simm_1_instr, IB_GUARD_HOOK);

    // -- OP_aaa:

    // -- OP_cmp:
    ib_hook_skip(tb_ctx->tool_info, OP_cmp);

    // -- OP_aas:

    // -- OP_inc:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSMEM_1]),
            init_option, ub_is_dmem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSMEM_2]),
            init_option, ub_is_dmem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSMEM_4]),
            init_option, ub_is_dmem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSMEM_8]),
            init_option, ub_is_dmem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSREG_1]),
            init_option, ub_is_dreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSREG_2]),
            init_option, ub_is_dreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSREG_4]),
            init_option, ub_is_dreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_inc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_INC_DSREG_8]),
            init_option, ub_is_dreg_8_instr, IB_GUARD_HOOK);

    // -- OP_dec:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSMEM_1]),
            init_option, ub_is_dmem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSMEM_2]),
            init_option, ub_is_dmem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSMEM_4]),
            init_option, ub_is_dmem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSMEM_8]),
            init_option, ub_is_dmem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSREG_1]),
            init_option, ub_is_dreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSREG_2]),
            init_option, ub_is_dreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSREG_4]),
            init_option, ub_is_dreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_dec,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DEC_DSREG_8]),
            init_option, ub_is_dreg_8_instr, IB_GUARD_HOOK);

    // -- OP_push:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_1_SREG_1]),
            init_option, ub_is_push_dmem_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_2_SREG_2]),
            init_option, ub_is_push_dmem_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_4_SREG_4]),
            init_option, ub_is_push_dmem_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_8_SREG_8]),
            init_option, ub_is_push_dmem_8_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_1_SMEM_1]),
            init_option, ub_is_push_dmem_1_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_2_SMEM_2]),
            init_option, ub_is_push_dmem_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_4_SMEM_4]),
            init_option, ub_is_push_dmem_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUSH_DMEM_8_SMEM_8]),
            init_option, ub_is_push_dmem_8_smem_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_1]),
            init_option, ub_is_push_dmem_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_2]),
            init_option, ub_is_push_dmem_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_4]),
            init_option, ub_is_push_dmem_4_simm_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_8]),
            init_option, ub_is_push_dmem_8_simm_8_instr, IB_GUARD_HOOK);

    // -- OP_push_imm:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_1]),
            init_option, ub_is_push_dmem_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_2]),
            init_option, ub_is_push_dmem_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_4]),
            init_option, ub_is_push_dmem_4_simm_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_push_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_8]),
            init_option, ub_is_push_dmem_8_simm_8_instr, IB_GUARD_HOOK);

    // -- OP_pop:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pop,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POP_DREG_1_SMEM_1]),
            init_option, ub_is_pop_dreg_1_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pop,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POP_DREG_2_SMEM_2]),
            init_option, ub_is_pop_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pop,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POP_DREG_4_SMEM_4]),
            init_option, ub_is_pop_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pop,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POP_DREG_8_SMEM_8]),
            init_option, ub_is_pop_dreg_8_smem_8_instr, IB_GUARD_HOOK);

    // -- OP_pusha:
    // -- OP_popa:
    // -- OP_bound:
    // -- OP_arpl:

    // -- OP_imul:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_2_SREG_1_SREG_1]),
            init_option, ub_is_mult_dreg_2_sreg_1_sreg_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_2_SMEM_1_SREG_1]),
            init_option, ub_is_mult_dreg_2_smem_1_sreg_1, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_4_DREG_4_SREG_4_SREG_4]),
            init_option, ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_4_DREG_4_SMEM_4_SREG_4]),
            init_option, ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr,
            IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_2_SMEM_2]),
            init_option, ub_is_srcdst_src_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_4_SMEM_4]),
            init_option, ub_is_srcdst_src_dreg_4_smem_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_2_SREG_2]),
            init_option, ub_is_srcdst_src_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_4_SREG_4]),
            init_option, ub_is_srcdst_src_dreg_4_sreg_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_2_SIMM_2]),
            init_option, ub_is_srcdst_src_dreg_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_4_SIMM_4]),
            init_option, ub_is_srcdst_src_dreg_4_simm_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_2_SREG_2_SIMM_2]),
            init_option, ub_is_mult_dreg_2_sreg_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_4_SREG_4_SIMM_4]),
            init_option, ub_is_mult_dreg_4_sreg_4_simm_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_2_SMEM_2_SIMM_2]),
            init_option, ub_is_mult_dreg_2_smem_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_imul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IMUL_DREG_4_SMEM_4_SIMM_4]),
            init_option, ub_is_mult_dreg_4_smem_4_simm_4_instr, IB_GUARD_HOOK);

    // -- OP_jo_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jo_short);

    // -- OP_jno_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jno_short);

    // -- OP_jb_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jb_short);

    // -- OP_jnb_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jnb_short);

    // -- OP_jz_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jz_short);

    // -- OP_jnz_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jnz_short);

    // -- OP_jbe_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jbe_short);

    // -- OP_jnbe_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jnbe_short);

    // -- OP_js_short:
    ib_hook_skip(tb_ctx->tool_info, OP_js_short);

    // -- OP_jns_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jns_short);

    // -- OP_jp_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jp_short);

    // -- OP_jnp_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jnp_short);

    // -- OP_jl_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jl_short);

    // -- OP_jnl_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jnl_short);

    // -- OP_jle_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jle_short);

    // -- OP_jnle_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jnle_short);

    // -- OP_call:
    tb_register_call(tb_ctx, OP_call, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_8]));

    // -- OP_call_ind:
    tb_register_call(tb_ctx, OP_call_ind, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_8]));

    // -- OP_call_far:
    tb_register_call(tb_ctx, OP_call_far, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_8]));

    // -- OP_call_far_ind:
    tb_register_call(tb_ctx, OP_call_far_ind, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_8]));

    // -- OP_jmp:
    ib_hook_skip(tb_ctx->tool_info, OP_jmp);

    // -- OP_jmp_short:
    ib_hook_skip(tb_ctx->tool_info, OP_jmp_short);

    // -- OP_jmp_ind:
    ib_hook_skip(tb_ctx->tool_info, OP_jmp_ind);

    // -- OP_jmp_far:
    ib_hook_skip(tb_ctx->tool_info, OP_jmp_far);

    // -- OP_jmp_far_ind:
    ib_hook_skip(tb_ctx->tool_info, OP_jmp_far_ind);

    // -- OP_loopne:

    // -- OP_loope:

    // -- OP_loop:

    // -- OP_jecxz:
    ib_hook_skip(tb_ctx->tool_info, OP_jecxz);

    // -- OP_mov_ld:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_1_SMEM_1]),
            init_option, ub_is_mov_dreg_1_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_2_SMEM_2]),
            init_option, ub_is_mov_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_4_SMEM_4]),
            init_option, ub_is_mov_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_8_SMEM_8]),
            init_option, ub_is_mov_dreg_8_smem_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_1_SREG_1]),
            init_option, ub_is_mov_dreg_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_2_SREG_2]),
            init_option, ub_is_mov_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_4_SREG_4]),
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_ld,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_8_SREG_8]),
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);

    // -- OP_mov_st:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_1_SREG_1]),
            init_option, ub_is_mov_dreg_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_2_SREG_2]),
            init_option, ub_is_mov_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_4_SREG_4]),
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DREG_8_SREG_8]),
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DMEM_1_SREG_1]),
            init_option, ub_is_mov_dmem_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DMEM_2_SREG_2]),
            init_option, ub_is_mov_dmem_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DMEM_4_SREG_4]),
            init_option, ub_is_mov_dmem_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOV_DMEM_8_SREG_8]),
            init_option, ub_is_mov_dmem_8_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]),
            init_option, ub_is_mov_dmem_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2]),
            init_option, ub_is_mov_dmem_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_4]),
            init_option, ub_is_mov_dmem_4_simm_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_8]),
            init_option, ub_is_mov_dmem_8_simm_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            init_option, ub_is_mov_dreg_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_2]),
            init_option, ub_is_mov_dreg_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_4]),
            init_option, ub_is_mov_dreg_4_simm_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_st,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_8]),
            init_option, ub_is_mov_dreg_8_simm_8_instr, IB_GUARD_HOOK);

    // -- OP_mov_imm:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]),
            init_option, ub_is_mov_dmem_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_2]),
            init_option, ub_is_mov_dmem_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_4]),
            init_option, ub_is_mov_dmem_4_simm_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_8]),
            init_option, ub_is_mov_dmem_8_simm_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            init_option, ub_is_mov_dreg_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_2]),
            init_option, ub_is_mov_dreg_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_4]),
            init_option, ub_is_mov_dreg_4_simm_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mov_imm,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_8]),
            init_option, ub_is_mov_dreg_8_simm_8_instr, IB_GUARD_HOOK);

    // -- OP_mov_seg:
    // -- OP_mov_priv:

    // -- OP_test:
    ib_hook_skip(tb_ctx->tool_info, OP_test);

    // -- OP_lea:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_DREG_2_SREG_2_SREG_2]),
            init_option, ub_is_lea_dreg_2_sreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_DREG_4_SREG_4_SREG_4]),
            init_option, ub_is_lea_dreg_4_sreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_DREG_8_SREG_8_SREG_8]),
            init_option, ub_is_lea_dreg_8_sreg_8_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_BASE_DREG_2_SREG_2]),
            init_option, ub_is_lea_base_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_BASE_DREG_4_SREG_4]),
            init_option, ub_is_lea_base_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_BASE_DREG_8_SREG_8]),
            init_option, ub_is_lea_base_dreg_8_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_INDEX_DREG_2_SREG_2]),
            init_option, ub_is_lea_index_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_INDEX_DREG_4_SREG_4]),
            init_option, ub_is_lea_index_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEA_INDEX_DREG_8_SREG_8]),
            init_option, ub_is_lea_index_dreg_8_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_2]),
            init_option, ub_is_lea_dreg_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_4]),
            init_option, ub_is_lea_dreg_4_simm_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lea,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_8]),
            init_option, ub_is_lea_dreg_8_simm_8_instr, IB_GUARD_HOOK);

    // -- OP_xchg:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_1_REG_1]),
            init_option, ub_is_xchg_reg_1_reg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_2_REG_2]),
            init_option, ub_is_xchg_reg_2_reg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_4_REG_4]),
            init_option, ub_is_xchg_reg_4_reg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_8_REG_8]),
            init_option, ub_is_xchg_reg_8_reg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_1_MEM_1]),
            init_option, ub_is_xchg_reg_1_mem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_2_MEM_2]),
            init_option, ub_is_xchg_reg_2_mem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_4_MEM_4]),
            init_option, ub_is_xchg_reg_4_mem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_REG_8_MEM_8]),
            init_option, ub_is_xchg_reg_8_mem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_MEM_1_REG_1]),
            init_option, ub_is_xchg_mem_1_reg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_MEM_2_REG_2]),
            init_option, ub_is_xchg_mem_2_reg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_MEM_4_REG_4]),
            init_option, ub_is_xchg_mem_4_reg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XCHG_MEM_8_REG_8]),
            init_option, ub_is_xchg_mem_8_reg_8_instr, IB_GUARD_HOOK);

    // -- OP_cwde:

    tb_register_hook_instrum_hndlr(tb_ctx, OP_cwde,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1ST_SUB_3RD_4TH]),
            init_option, NULL, IB_GUARD_HOOK);
    // -- OP_cdq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_cdq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_4]),
            init_option,
            NULL, IB_GUARD_HOOK);

    // -- OP_fwait:

    // -- OP_pushf:
    // -- OP_popf:
    // -- OP_sahf:
    // -- OP_lahf:

    // -- OP_ret:
    ib_hook_skip(tb_ctx->tool_info, OP_ret);

    // -- OP_ret_far:
    ib_hook_skip(tb_ctx->tool_info, OP_ret_far);

    // -- OP_les:

    // -- OP_lds:

    // -- OP_enter:

    // -- OP_leave:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_leave,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEAVE_DREG_4_DREG_4_SREG_4_SMEM_4]),
            init_option, ub_is_leave_dreg_4_dreg_4_sreg_4_smem_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_leave,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LEAVE_DREG_8_DREG_8_SREG_8_SMEM_8]),
            init_option, ub_is_leave_dreg_8_dreg_8_sreg_8_smem_8_instr,
            IB_GUARD_HOOK);

    // -- OP_int3:
    ib_hook_skip(tb_ctx->tool_info, OP_int3);

    // -- OP_int:
    ib_hook_skip(tb_ctx->tool_info, OP_int);

    // -- OP_into:

    // -- OP_iret:
    ib_hook_skip(tb_ctx->tool_info, OP_iret);

    // -- OP_aam:

    // -- OP_aad:

    // -- OP_xlat:
    // -- OP_in:
    // -- OP_out:
    // -- OP_hlt:

    // -- OP_cmc:
    ib_hook_skip(tb_ctx->tool_info, OP_cmc);

    // -- OP_clc:
    ib_hook_skip(tb_ctx->tool_info, OP_clc);

    // -- OP_stc:
    ib_hook_skip(tb_ctx->tool_info, OP_stc);

    // -- OP_cli:
    ib_hook_skip(tb_ctx->tool_info, OP_cli);

    // -- OP_sti:
    ib_hook_skip(tb_ctx->tool_info, OP_sti);

    // -- OP_cld:
    ib_hook_skip(tb_ctx->tool_info, OP_cld);

    // -- OP_std:
    ib_hook_skip(tb_ctx->tool_info, OP_std);

    // -- OP_lar:
    // -- OP_lsl:
    // -- OP_syscall:
    ib_hook_skip(tb_ctx->tool_info, OP_syscall);

    // -- OP_clts:
    // -- OP_sysret:
    // -- OP_invd:
    // -- OP_wbinvd:
    // -- OP_ud2a:
    // -- OP_nop_modrm:
    // -- OP_movntps:

    // -- OP_movntpd:

    // -- OP_wrmsr:

    // -- OP_rdtsc:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rdtsc,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_FIRST_2_DREGS_4]),
            init_option,
            NULL, IB_GUARD_HOOK);

    // -- OP_rdmsr:
    // -- OP_rdpmc:

    // -- OP_sysenter:
    ib_hook_skip(tb_ctx->tool_info, OP_sysenter);

    // -- OP_sysexit:
    ib_hook_skip(tb_ctx->tool_info, OP_sysexit);

    // -- OP_cmovo:
    tb_register_cmov(tb_ctx, OP_cmovo, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVO_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVO_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVO_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVO_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVO_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVO_DREG_8_SREG_8]));

    // -- OP_cmovno:
    tb_register_cmov(tb_ctx, OP_cmovno, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNO_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNO_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNO_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNO_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNO_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNO_DREG_8_SREG_8]));

    // -- OP_cmovb:
    tb_register_cmov(tb_ctx, OP_cmovb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVB_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVB_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVB_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVB_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVB_DREG_8_SREG_8]));

    // -- OP_cmovnb:
    tb_register_cmov(tb_ctx, OP_cmovnb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNB_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNB_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNB_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNB_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNB_DREG_8_SREG_8]));

    // -- OP_cmovz:
    tb_register_cmov(tb_ctx, OP_cmovz, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVE_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVE_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVE_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVE_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVE_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVE_DREG_8_SREG_8]));

    // -- OP_cmovnz:
    tb_register_cmov(tb_ctx, OP_cmovnz, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNE_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNE_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNE_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNE_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNE_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNE_DREG_8_SREG_8]));

    // -- OP_cmovbe:
    tb_register_cmov(tb_ctx, OP_cmovbe, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVBE_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVBE_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVBE_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVBE_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVBE_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVBE_DREG_8_SREG_8]));

    // -- OP_cmovnbe:
    tb_register_cmov(tb_ctx, OP_cmovnbe, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNBE_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNBE_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNBE_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNBE_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNBE_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNBE_DREG_8_SREG_8]));

    // -- OP_cmovs:
    tb_register_cmov(tb_ctx, OP_cmovs, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVS_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVS_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVS_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVS_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVS_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVS_DREG_8_SREG_8]));

    // -- OP_cmovns:
    tb_register_cmov(tb_ctx, OP_cmovns, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNS_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNS_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNS_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNS_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNS_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNS_DREG_8_SREG_8]));

    // -- OP_cmovp:
    tb_register_cmov(tb_ctx, OP_cmovp, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVP_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVP_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVP_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVP_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVP_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVP_DREG_8_SREG_8]));

    // -- OP_cmovnp:
    tb_register_cmov(tb_ctx, OP_cmovnp, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNP_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNP_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNP_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNP_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNP_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVNP_DREG_8_SREG_8]));

    // -- OP_cmovl:
    tb_register_cmov(tb_ctx, OP_cmovl, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVL_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVL_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVL_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVL_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVL_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVL_DREG_8_SREG_8]));

    // -- OP_cmovnl:
    tb_register_cmov(tb_ctx, OP_cmovnl, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVGE_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVGE_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVGE_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVGE_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVGE_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVGE_DREG_8_SREG_8]));

    // -- OP_cmovle:
    tb_register_cmov(tb_ctx, OP_cmovle, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVLE_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVLE_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVLE_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVLE_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVLE_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVLE_DREG_8_SREG_8]));

    // -- OP_cmovnle:
    tb_register_cmov(tb_ctx, OP_cmovnle, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVG_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVG_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVG_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVG_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVG_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMOVG_DREG_8_SREG_8]));

    // -- OP_punpcklbw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_punpcklbw,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLBW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLBW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLBW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLBW_DREG_16_SREG_16]));

    // -- OP_punpcklwd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_punpcklwd,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLWD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLWD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLWD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLWD_DREG_16_SREG_16]));

    // -- OP_punpckldq:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_punpckldq,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLDQ_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLDQ_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLDQ_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLDQ_DREG_16_SREG_16]));

    // -- OP_packsswb:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_packsswb,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSWB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSWB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSWB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSWB_DREG_16_SREG_16]));

    // -- OP_pcmpgtb:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpgtb,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTB_DREG_16_SREG_16]));

    // -- OP_pcmpgtw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpgtw,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTW_DREG_16_SMEM_16]));

    // -- OP_pcmpgtd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpgtd,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTD_DREG_16_SREG_16]));

    // -- OP_packuswb:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_packuswb,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKUSWB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKUSWB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKUSWB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKUSWB_DREG_16_SREG_16]));

    // -- OP_punpckhbw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_punpckhbw,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHBW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHBW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHBW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHBW_DREG_16_SREG_16]));

    // -- OP_punpckhwd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_punpckhwd,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHWD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHWD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHWD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHWD_DREG_16_SREG_16]));

    // -- OP_punpckhdq:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_punpckhdq,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHDQ_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHDQ_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHDQ_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHDQ_DREG_16_SREG_16]));

    // -- OP_packssdw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_packssdw,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSDW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSDW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSDW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKSSDW_DREG_16_SREG_16]));

    // -- OP_punpcklqdq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_punpcklqdq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLQDQ_DREG_16_SREG_16]),
            init_option, ub_is_punpck_dreg_16_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_punpcklqdq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKLQDQ_DREG_16_SMEM_16]),
            init_option, ub_is_punpck_dreg_16_smem_16, IB_GUARD_HOOK);

    // -- OP_punpckhqdq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_punpckhqdq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHQDQ_DREG_16_SREG_16]),
            init_option, ub_is_punpck_dreg_16_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_punpckhqdq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PUNPCKHQDQ_DREG_16_SMEM_16]),
            init_option, ub_is_punpck_dreg_16_smem_16, IB_GUARD_HOOK);

    // -- OP_movd:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_4_SMEM_4]),
            init_option, ub_is_mov_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_4_SREG_4]),
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DMEM_4_SREG_4]),
            init_option, ub_is_mov_dmem_4_sreg_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_8_SMEM_4]),
            init_option, ub_is_mov_dreg_8_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_8_SREG_4]),
            init_option, ub_is_mov_dreg_8_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_4_SREG_8]),
            init_option, ub_is_mov_dreg_4_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DMEM_4_SREG_8]),
            init_option, ub_is_mov_dmem_4_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_16_SMEM_4]),
            init_option, ub_is_mov_dreg_16_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_16_SREG_4]),
            init_option, ub_is_mov_dreg_16_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DMEM_4_SREG_16]),
            init_option, ub_is_mov_dmem_4_sreg_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVD_DREG_4_SREG_16]),
            init_option, ub_is_mov_dreg_4_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_movq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ_DREG_8_SMEM_8]),
            init_option, ub_is_mov_dreg_8_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ_DREG_8_SREG_8]),
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ_DMEM_8_SREG_8]),
            init_option, ub_is_mov_dmem_8_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ_DREG_16_SMEM_8]),
            init_option, ub_is_mov_dreg_16_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ_DREG_16_SREG_8]),
            init_option, ub_is_mov_dreg_16_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ_DMEM_8_SREG_16]),
            init_option, ub_is_mov_dmem_8_sreg_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ_DREG_8_SREG_16]),
            init_option, ub_is_mov_dreg_8_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_movdqu:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movdqu,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQU_DREG_16_SMEM_16]),
            init_option, ub_is_mov_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movdqu,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQU_DREG_16_SREG_16]),
            init_option, ub_is_mov_dreg_16_sreg_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movdqu,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQU_DMEM_16_SREG_16]),
            init_option, ub_is_mov_dmem_16_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_movdqa:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movdqa,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQA_DREG_16_SMEM_16]),
            init_option, ub_is_mov_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movdqa,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQA_DREG_16_SREG_16]),
            init_option, ub_is_mov_dreg_16_sreg_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movdqa,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQA_DMEM_16_SREG_16]),
            init_option, ub_is_mov_dmem_16_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_pshufw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pshufw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFW_DREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFW_DREG_16_SREG_16]));

    // -- OP_pshufd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pshufd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFD_DREG_16_SREG_16]));

    // -- OP_pshufhw:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshufhw,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFHW_DREG_16_SREG_16]),
            init_option, ub_is_pshuf_dreg_16_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshufhw,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFHW_DREG_16_SMEM_16]),
            init_option, ub_is_pshuf_dreg_16_smem_16, IB_GUARD_HOOK);

    // -- OP_pshuflw:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshuflw,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFLW_DREG_16_SREG_16]),
            init_option, ub_is_pshuf_dreg_16_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshuflw,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFLW_DREG_16_SMEM_16]),
            init_option, ub_is_pshuf_dreg_16_smem_16, IB_GUARD_HOOK);

    // -- OP_pcmpeqb:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpeqb,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQB_DREG_16_SREG_16]));

    // -- OP_pcmpeqw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpeqw,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQW_DREG_16_SREG_16]));

    // -- OP_pcmpeqd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpeqd,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQD_DREG_16_SREG_16]));

    // -- OP_emms:

    // -- OP_jo:
    ib_hook_skip(tb_ctx->tool_info, OP_jo);

    // -- OP_jno:
    ib_hook_skip(tb_ctx->tool_info, OP_jno);

    // -- OP_jb:
    ib_hook_skip(tb_ctx->tool_info, OP_jb);

    // -- OP_jnb:
    ib_hook_skip(tb_ctx->tool_info, OP_jnb);

    // -- OP_jz:
    ib_hook_skip(tb_ctx->tool_info, OP_jz);

    // -- OP_jnz:
    ib_hook_skip(tb_ctx->tool_info, OP_jnz);

    // -- OP_jbe:
    ib_hook_skip(tb_ctx->tool_info, OP_jbe);

    // -- OP_jnbe:
    ib_hook_skip(tb_ctx->tool_info, OP_jnbe);

    // -- OP_js:
    ib_hook_skip(tb_ctx->tool_info, OP_js);

    // -- OP_jns:
    ib_hook_skip(tb_ctx->tool_info, OP_jns);

    // -- OP_jp:
    ib_hook_skip(tb_ctx->tool_info, OP_jp);

    // -- OP_jnp:
    ib_hook_skip(tb_ctx->tool_info, OP_jnp);

    // -- OP_jl:
    ib_hook_skip(tb_ctx->tool_info, OP_jl);

    // -- OP_jnl:
    ib_hook_skip(tb_ctx->tool_info, OP_jnl);

    // -- OP_jle:
    ib_hook_skip(tb_ctx->tool_info, OP_jle);

    // -- OP_jnle:
    ib_hook_skip(tb_ctx->tool_info, OP_jnle);

    // -- OP_seto:
    tb_register_set(tb_ctx, OP_seto, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setno:
    tb_register_set(tb_ctx, OP_setno, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setb:
    tb_register_set(tb_ctx, OP_setb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setnb:
    tb_register_set(tb_ctx, OP_setnb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setz:
    tb_register_set(tb_ctx, OP_setz, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setnz:
    tb_register_set(tb_ctx, OP_setnz, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setbe:
    tb_register_set(tb_ctx, OP_setbe, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setnbe:
    tb_register_set(tb_ctx, OP_setnbe, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_sets:
    tb_register_set(tb_ctx, OP_sets, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setns:
    tb_register_set(tb_ctx, OP_setns, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setp:
    tb_register_set(tb_ctx, OP_setp, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setnp:
    tb_register_set(tb_ctx, OP_setnp, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setl:
    tb_register_set(tb_ctx, OP_setl, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setnl:
    tb_register_set(tb_ctx, OP_setnl, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setle:
    tb_register_set(tb_ctx, OP_setle, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_setnle:
    tb_register_set(tb_ctx, OP_setnle, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DMEM_1]));

    // -- OP_cpuid:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_cpuid,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_FIRST_4_DREGS_4]),
            init_option,
            NULL, IB_GUARD_HOOK);

    // -- OP_bt:
    ib_hook_skip(tb_ctx->tool_info, OP_bt);

    // -- OP_shld:
    tb_register_pshiftd(tb_ctx, OP_shld, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DMEM_2_SREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DMEM_4_SREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DMEM_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DREG_2_SREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DREG_4_SREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DMEM_2_SREG_2_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DMEM_4_SREG_4_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DMEM_8_SREG_8_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DREG_2_SREG_2_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DREG_4_SREG_4_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHLD_DREG_8_SREG_8_SREG_1]));

    // -- OP_rsm:
    // -- OP_bts:

    // -- OP_shrd:

    tb_register_pshiftd(tb_ctx, OP_shrd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DMEM_2_SREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DMEM_4_SREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DMEM_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DREG_2_SREG_2_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DREG_4_SREG_4_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DMEM_2_SREG_2_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DMEM_4_SREG_4_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DMEM_8_SREG_8_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DREG_2_SREG_2_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DREG_4_SREG_4_SREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHRD_DREG_8_SREG_8_SREG_1]));

    // -- OP_cmpxchg:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_cmpxchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMPXCHG_SREG_1_SREG_1]),
            init_option, ub_is_cmpxchg_sreg_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_cmpxchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMPXCHG_SREG_2_SREG_2]),
            init_option, ub_is_cmpxchg_sreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_cmpxchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMPXCHG_SREG_4_SREG_4]),
            init_option, ub_is_cmpxchg_sreg_4_sreg_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_cmpxchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMPXCHG_SREG_1_SMEM_1]),
            init_option, ub_is_cmpxchg_sreg_1_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_cmpxchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMPXCHG_SREG_2_SMEM_2]),
            init_option, ub_is_cmpxchg_sreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_cmpxchg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_CMPXCHG_SREG_4_SMEM_4]),
            init_option, ub_is_cmpxchg_sreg_4_smem_4_instr, IB_GUARD_HOOK);



    // -- OP_lss:
    // -- OP_btr:
    // -- OP_lfs:
    // -- OP_lgs:

    // -- OP_movzx:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movzx,
                &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVZX_DREG_2_SREG_1]),
                init_option, ub_is_movzx_dreg_2_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movzx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVZX_DREG_4_SREG_1]),
            init_option, ub_is_movzx_dreg_4_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movzx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVZX_DREG_4_SREG_2]),
            init_option, ub_is_movzx_dreg_4_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movzx,
                &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVZX_DREG_2_SMEM_1]),
                init_option, ub_is_movzx_dreg_2_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movzx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVZX_DREG_4_SMEM_1]),
            init_option, ub_is_movzx_dreg_4_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movzx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVZX_DREG_4_SMEM_2]),
            init_option, ub_is_movzx_dreg_4_smem_2_instr, IB_GUARD_HOOK);

    // -- OP_ud2b:
    // -- OP_btc:

    // -- OP_bsf:
    tb_register_bs(tb_ctx, OP_bsf, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSF_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSF_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSF_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSF_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSF_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSF_DREG_8_SREG_8]));

    // -- OP_bsr:
    tb_register_bs(tb_ctx, OP_bsr, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSR_DREG_2_SMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSR_DREG_4_SMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSR_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSR_DREG_2_SREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSR_DREG_4_SREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSR_DREG_8_SREG_8]));

    // -- OP_movsx:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movsx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVSX_DREG_2_SREG_1]),
            init_option, ub_is_movzx_dreg_2_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movsx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVSX_DREG_4_SREG_1]),
            init_option, ub_is_movzx_dreg_4_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movsx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVSX_DREG_4_SREG_2]),
            init_option, ub_is_movzx_dreg_4_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movsx,
                &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVSX_DREG_2_SMEM_1]),
                init_option, ub_is_movzx_dreg_2_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movsx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVSX_DREG_4_SMEM_1]),
            init_option, ub_is_movzx_dreg_4_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movsx,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVSX_DREG_4_SMEM_2]),
            init_option, ub_is_movzx_dreg_4_smem_2_instr, IB_GUARD_HOOK);

    // -- OP_xadd:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_REG_1_REG_1]),
            init_option, ub_is_xchg_reg_1_reg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_REG_2_REG_2]),
            init_option, ub_is_xchg_reg_2_reg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_REG_4_REG_4]),
            init_option, ub_is_xchg_reg_4_reg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_REG_8_REG_8]),
            init_option, ub_is_xchg_reg_8_reg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_MEM_1_REG_1]),
            init_option, ub_is_xchg_mem_1_reg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_MEM_2_REG_2]),
            init_option, ub_is_xchg_mem_2_reg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_MEM_4_REG_4]),
            init_option, ub_is_xchg_mem_4_reg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xadd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XADD_MEM_8_REG_8]),
            init_option, ub_is_xchg_mem_8_reg_8_instr, IB_GUARD_HOOK);

    // -- OP_movnti:

    // -- OP_pinsrw:

    // -- OP_pextrw:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pextrw,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXTRW_DREG_4_SREG_16]),
            init_option, ub_is_pextr_dreg_4_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pextrw,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXTRW_DREG_4_SREG_8]),
            init_option, ub_is_pextr_dreg_4_sreg_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pextrw,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXTRW_DMEM_2_SREG_16]),
            init_option, ub_is_pextr_dmem_2_sreg_16, IB_GUARD_HOOK);

    // -- OP_bswap:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_bswap,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSWAP_DSREG_4]),
            init_option, ub_is_dreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_bswap,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSWAP_DSREG_8]),
            init_option, ub_is_dreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_bswap,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSWAP_DSMEM_4]),
            init_option, ub_is_dmem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_bswap,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_BSWAP_DSMEM_8]),
            init_option, ub_is_dmem_8_instr, IB_GUARD_HOOK);

    // -- OP_psrlw:
    tb_register_pshift(tb_ctx, OP_psrlw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLW_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLW_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLW_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLW_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLW_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLW_DREG_16_SREG_16_SIMM_1]));

    // -- OP_psrld:
    tb_register_pshift(tb_ctx, OP_psrld, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLD_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLD_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLD_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLD_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLD_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLD_DREG_16_SREG_16_SIMM_1]));

    // -- OP_psrlq:
    tb_register_pshift(tb_ctx, OP_psrlq, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLQ_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLQ_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLQ_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLQ_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLQ_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLQ_DREG_16_SREG_16_SIMM_1]));

    // -- OP_paddq:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_paddq, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDQ_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDQ_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDQ_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDQ_DREG_16_SREG_16]));

    // -- OP_pmullw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pmullw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULLW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULLW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULLW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULLW_DREG_16_SMEM_16]));

    // -- OP_pmovmskb:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pmovmskb,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMOVMSK_DREG_4_SREG_8]),
            init_option, ub_is_pmovmsk_dreg_4_sreg_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pmovmskb,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMOVMSK_DREG_4_SREG_16]),
            init_option, ub_is_pmovmsk_dreg_4_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pmovmskb,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMOVMSK_DREG_8_SREG_8]),
            init_option, ub_is_pmovmsk_dreg_8_sreg_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pmovmskb,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMOVMSK_DREG_8_SREG_16]),
            init_option, ub_is_pmovmsk_dreg_8_sreg_16, IB_GUARD_HOOK);

    // -- OP_psubusb:

    // -- OP_psubusw:

    // -- OP_pminub:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pminub, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUB_DREG_16_SREG_16]));

    // -- OP_pand:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pand, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PAND_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PAND_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PAND_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PAND_DREG_16_SREG_16]));

    // -- OP_paddusb:

    // -- OP_paddusw:

    // -- OP_pmaxub:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pmaxub, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUB_DREG_16_SREG_16]));

    // -- OP_pandn:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pandn, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PANDN_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PANDN_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PANDN_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PANDN_DREG_16_SREG_16]));

    // -- OP_pavgb:

    // -- OP_psraw:
    tb_register_pshift(tb_ctx, OP_psraw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAW_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAW_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAW_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAW_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAW_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAW_DREG_16_SREG_16_SIMM_1]));

    // -- OP_psrad:
    tb_register_pshift(tb_ctx, OP_psrad, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAD_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAD_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAD_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAD_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAD_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRAD_DREG_16_SREG_16_SIMM_1]));

    // -- OP_pavgw:

    // -- OP_pmulhuw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pmulhuw,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHUW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHUW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHUW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHUW_DREG_16_SREG_16]));

    // -- OP_pmulhw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pmulhw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULHW_DREG_16_SREG_16]));

    // -- OP_movntq:

    // -- OP_movntdq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movntdq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQU_DMEM_16_SREG_16]),
            init_option, ub_is_mov_dmem_16_sreg_16_instr, IB_GUARD_HOOK);


    // -- OP_psubsb:

    // -- OP_psubsw:

    // -- OP_pminsw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pminsw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSW_DREG_16_SREG_16]));

    // -- OP_por:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_por, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POR_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POR_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POR_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POR_DREG_16_SREG_16]));

    // -- OP_paddsb:

    // -- OP_paddsw:

    // -- OP_pmaxsw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pmaxsw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSW_DREG_16_SREG_16]));

    // -- OP_pxor:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pxor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PXOR_DREG_16_SMEM_16]),
            init_option, ub_is_srcdst_src_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pxor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PXOR_DREG_16_SREG_16]),
            init_option, ub_is_srcdst_src_diff_dreg_16_sreg_16_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pxor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_16]),
            init_option, ub_is_srcdst_src_same_dreg_16_sreg_16_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pxor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PXOR_DREG_8_SMEM_8]),
            init_option, ub_is_srcdst_src_dreg_8_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pxor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PXOR_DREG_8_SREG_8]),
            init_option, ub_is_srcdst_src_diff_dreg_8_sreg_8_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pxor,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_8]),
            init_option, ub_is_srcdst_src_same_dreg_8_sreg_8_instr,
            IB_GUARD_HOOK);

    // -- OP_psllw:
    tb_register_pshift(tb_ctx, OP_psllw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLW_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLW_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLW_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLW_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLW_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLW_DREG_16_SREG_16_SIMM_1]));

    // -- OP_pslld:
    tb_register_pshift(tb_ctx, OP_pslld, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLD_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLD_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLD_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLD_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLD_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLD_DREG_16_SREG_16_SIMM_1]));

    // -- OP_psllq:
    tb_register_pshift(tb_ctx, OP_psllq, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLQ_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLQ_DREG_16_SREG_16_SREG_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLQ_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLQ_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLQ_DREG_8_SREG_8_SIMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLQ_DREG_16_SREG_16_SIMM_1]));

    // -- OP_pmuludq:

    // -- OP_pmaddwd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pmaddwd,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMADDWD_DREG_8_SREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMADDWD_DREG_8_SREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMADDWD_DREG_16_SREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMADDWD_DREG_16_SREG_16_SREG_16]));

    // -- OP_psadbw:
    // -- OP_maskmovq:
    // -- OP_maskmovdqu:

    // -- OP_psubb:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_psubb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBB_DREG_16_SREG_16]));

    // -- OP_psubw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_psubw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBB_DREG_16_SREG_16]));

    // -- OP_psubd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_psubd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBD_DREG_16_SREG_16]));

    // -- OP_psubq:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_psubq, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBQ_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBQ_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBQ_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSUBQ_DREG_16_SREG_16]));

    // -- OP_paddb:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_paddb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDB_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDB_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDB_DREG_16_SREG_16]));

    // -- OP_paddw:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_paddw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDW_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDW_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDW_DREG_16_SREG_16]));

    // -- OP_paddd:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_paddd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDD_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDD_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PADDD_DREG_16_SREG_16]));

    // -- OP_psrldq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_psrldq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSRLDQ_DREG_16_SREG_16_SIMM_1]),
            init_option, ub_is_immed_reg_shift_16, IB_GUARD_HOOK);

    // -- OP_pslldq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pslldq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSLLDQ_DREG_16_SREG_16_SIMM_1]),
            init_option, ub_is_immed_reg_shift_16, IB_GUARD_HOOK);

    // -- OP_rol:
    tb_register_shift(tb_ctx, OP_rol, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DREG_8_REG_1]),

            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_SOLE_DMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROL_DMEM_8_REG_1]));

    // -- OP_ror:
    tb_register_shift(tb_ctx, OP_ror, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DREG_8_REG_1]),

            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_SOLE_DMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ROR_DMEM_8_REG_1]));

    // -- OP_rcl:
    tb_register_shift(tb_ctx, OP_rcl, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DREG_8_REG_1]),

            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_SOLE_DMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCL_DMEM_8_REG_1])
            );

    // -- OP_rcr:
    tb_register_shift(tb_ctx, OP_rcr, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DREG_8_REG_1]),

            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_SOLE_DMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_RCR_DMEM_8_REG_1]));

    // -- OP_shl:
    tb_register_shift(tb_ctx, OP_shl, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DREG_8_REG_1]),

            & (taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_SOLE_DMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHL_DMEM_8_REG_1]));

    // -- OP_shr:
    tb_register_shift(tb_ctx, OP_shr, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DREG_8_REG_1]),

            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_SOLE_DMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SHR_DMEM_8_REG_1]));

    // -- OP_sar:
    tb_register_shift(tb_ctx, OP_sar, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DREG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DREG_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DREG_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DREG_8_REG_1]),

            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DMEM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DMEM_2]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DMEM_4]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_SOLE_DMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_1_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_2_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_4_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_8_IMM_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_1_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_2_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_4_REG_1]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_SAR_DMEM_8_REG_1])

            );

    // -- OP_not:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DREG_1_DREG_1]),
            init_option, ub_is_dreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DREG_2_DREG_2]),
            init_option, ub_is_dreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DREG_4_DREG_4]),
            init_option, ub_is_dreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DREG_8_DREG_8]),
            init_option, ub_is_dreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DMEM_1_DMEM_1]),
            init_option, ub_is_dmem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DMEM_2_DMEM_2]),
            init_option, ub_is_dmem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DMEM_4_DMEM_4]),
            init_option, ub_is_dmem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_not,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NOT_DMEM_8_DMEM_8]),
            init_option, ub_is_dmem_8_instr, IB_GUARD_HOOK);

    // -- OP_neg:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DREG_1_DREG_1]),
            init_option, ub_is_dreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DREG_2_DREG_2]),
            init_option, ub_is_dreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DREG_4_DREG_4]),
            init_option, ub_is_dreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DREG_8_DREG_8]),
            init_option, ub_is_dreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DMEM_1_DMEM_1]),
            init_option, ub_is_dmem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DMEM_2_DMEM_2]),
            init_option, ub_is_dmem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DMEM_4_DMEM_4]),
            init_option, ub_is_dmem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_neg,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_NEG_DMEM_8_DMEM_8]),
            init_option, ub_is_dmem_8_instr, IB_GUARD_HOOK);

    // -- OP_mul:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MUL_DREG_2_SREG_1_SREG_1]),
            init_option, ub_is_mult_dreg_2_sreg_1_sreg_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MUL_DREG_2_SMEM_1_SREG_1]),
            init_option, ub_is_mult_dreg_2_smem_1_sreg_1, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_mul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MUL_DREG_4_DREG_4_SREG_4_SREG_4]),
            init_option, ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_mul,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MUL_DREG_4_DREG_4_SMEM_4_SREG_4]),
            init_option, ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr,
            IB_GUARD_HOOK);

    // -- OP_div:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_div,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DIV_DREG_4_DREG_4_SMEM_4_SREG_4_SREG_4]),
            init_option, ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_div,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DIV_DREG_4_DREG_4_SREG_4_SREG_4_SREG_4]),
            init_option, ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_div,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DIV_DREG_1_DREG_1_SREG_1_SREG_2]),
            init_option, ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_div,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_DIV_DREG_1_DREG_1_SMEM_1_SREG_2]),
            init_option, ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr,
            IB_GUARD_HOOK);

    // -- OP_idiv:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_idiv,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IDIV_DREG_4_DREG_4_SMEM_4_SREG_4_SREG_4]),
            init_option, ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_idiv,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IDIV_DREG_4_DREG_4_SREG_4_SREG_4_SREG_4]),
            init_option, ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr,
            IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, OP_idiv,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IDIV_DREG_1_DREG_1_SREG_1_SREG_2]),
            init_option, ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_idiv,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_IDIV_DREG_1_DREG_1_SMEM_1_SREG_2]),
            init_option, ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr,
            IB_GUARD_HOOK);

    // -- OP_sldt:
    // -- OP_str:
    // -- OP_lldt:
    // -- OP_ltr:
    // -- OP_verr:
    // -- OP_verw:
    // -- OP_sgdt:
    // -- OP_sidt:
    // -- OP_lgdt:
    // -- OP_lidt:
    // -- OP_smsw:
    // -- OP_lmsw:
    // -- OP_invlpg:
    // -- OP_cmpxchg8b:
    // -- OP_fxsave32:
    // -- OP_fxrstor32:
    // -- OP_ldmxcsr:
    // -- OP_stmxcsr:
    // -- OP_lfence:
    // -- OP_mfence:

    // -- OP_clflush:
    ib_hook_skip(tb_ctx->tool_info, OP_clflush);

    // -- OP_sfence:

    // -- OP_prefetchnta:
    ib_hook_skip(tb_ctx->tool_info, OP_prefetchnta);

    // -- OP_prefetcht0:
    ib_hook_skip(tb_ctx->tool_info, OP_prefetcht0);

    // -- OP_prefetcht1:
    ib_hook_skip(tb_ctx->tool_info, OP_prefetcht1);

    // -- OP_prefetcht2:
    ib_hook_skip(tb_ctx->tool_info, OP_prefetcht2);

    // -- OP_prefetch:
    ib_hook_skip(tb_ctx->tool_info, OP_prefetch);

    // -- OP_prefetchw:
    ib_hook_skip(tb_ctx->tool_info, OP_prefetchw);

    // -- OP_movups:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movups,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVUPS_DREG_16_SMEM_16]),
            init_option, ub_is_mov_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movups,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVUPS_DREG_16_SREG_16]),
            init_option, ub_is_mov_dreg_16_sreg_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movups,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVUPS_DMEM_16_SREG_16]),
            init_option, ub_is_mov_dmem_16_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_movss:

    // -- OP_movupd:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movupd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVUPD_DREG_16_SMEM_16]),
            init_option, ub_is_mov_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movupd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVUPD_DREG_16_SREG_16]),
            init_option, ub_is_mov_dreg_16_sreg_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movupd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVUPD_DMEM_16_SREG_16]),
            init_option, ub_is_mov_dmem_16_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_movsd:

    // -- OP_movlps:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movlps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVLPS_DREG_16_SMEM_8]),
            init_option, ub_is_mov_dreg_16_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movlps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVLPS_DMEM_8_SREG_16]),
            init_option, ub_is_mov_dmem_8_sreg_16_instr, IB_GUARD_HOOK);


    // -- OP_movlpd:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movlpd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVLPD_DREG_16_SMEM_8]),
            init_option, ub_is_mov_dreg_16_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movlpd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVLPD_DMEM_8_SREG_16]),
            init_option, ub_is_mov_dmem_8_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_unpcklps:
    // -- OP_unpcklpd:
    // -- OP_unpckhps:
    // -- OP_unpckhpd:
    // -- OP_movhps:
    // -- OP_movhpd:

    // -- OP_movaps:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movaps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVAPS_DREG_16_SMEM_16]),
            init_option, ub_is_mov_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movaps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVAPS_DREG_16_SREG_16]),
            init_option, ub_is_mov_dreg_16_sreg_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movaps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVAPS_DMEM_16_SREG_16]),
            init_option, ub_is_mov_dmem_16_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_movapd:
    // -- OP_cvtpi2ps:
    // -- OP_cvtsi2ss:
    // -- OP_cvtpi2pd:
    // -- OP_cvtsi2sd:
    // -- OP_cvttps2pi:
    // -- OP_cvttss2si:
    // -- OP_cvttpd2pi:
    // -- OP_cvttsd2si:
    // -- OP_cvtps2pi:
    // -- OP_cvtss2si:
    // -- OP_cvtpd2pi:
    // -- OP_cvtsd2si:
    // -- OP_ucomiss:
    // -- OP_ucomisd:
    // -- OP_comiss:
    // -- OP_comisd:
    // -- OP_movmskps:
    // -- OP_movmskpd:
    // -- OP_sqrtps:
    // -- OP_sqrtss:
    // -- OP_sqrtpd:
    // -- OP_sqrtsd:
    // -- OP_rsqrtps:
    // -- OP_rsqrtss:
    // -- OP_rcpps:
    // -- OP_rcpss:

    // -- OP_andps:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_andps, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDPS_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDPS_DREG_16_SREG_16]));

    // -- OP_andpd:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_andpd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDPD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDPD_DREG_16_SREG_16]));

    // -- OP_andnps:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_andnps, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDNPS_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDNPS_DREG_16_SREG_16]));

    // -- OP_andnpd:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_andnpd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDNPD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ANDNPD_DREG_16_SREG_16]));

    // -- OP_orps:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_orps, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ORPS_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ORPS_DREG_16_SREG_16]));

    // -- OP_orpd:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_orpd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ORPD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_ORPD_DREG_16_SREG_16]));

    // -- OP_xorps:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xorps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XORPS_DREG_16_SMEM_16]),
            init_option, ub_is_srcdst_src_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xorps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XORPS_DREG_16_SREG_16]),
            init_option, ub_is_srcdst_src_diff_dreg_16_sreg_16_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xorps,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_16]),
            init_option, ub_is_srcdst_src_same_dreg_16_sreg_16_instr,
            IB_GUARD_HOOK);

    // -- OP_xorpd:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xorpd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XORPD_DREG_16_SMEM_16]),
            init_option, ub_is_srcdst_src_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xorpd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_XORPD_DREG_16_SREG_16]),
            init_option, ub_is_srcdst_src_diff_dreg_16_sreg_16_instr,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xorpd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_DREG_16]),
            init_option, ub_is_srcdst_src_same_dreg_16_sreg_16_instr,
            IB_GUARD_HOOK);

    // -- OP_addps:
    // -- OP_addss:
    // -- OP_addpd:
    // -- OP_addsd:
    // -- OP_mulps:
    // -- OP_mulss:
    // -- OP_mulpd:
    // -- OP_mulsd:
    // -- OP_cvtps2pd:
    // -- OP_cvtss2sd:
    // -- OP_cvtpd2ps:
    // -- OP_cvtsd2ss:
    // -- OP_cvtdq2ps:
    // -- OP_cvttps2dq:
    // -- OP_cvtps2dq:
    // -- OP_subps:
    // -- OP_subss:
    // -- OP_subpd:
    // -- OP_subsd:
    // -- OP_minps:
    // -- OP_minss:
    // -- OP_minpd:
    // -- OP_minsd:
    // -- OP_divps:
    // -- OP_divss:
    // -- OP_divpd:
    // -- OP_divsd:
    // -- OP_maxps:
    // -- OP_maxss:
    // -- OP_maxpd:
    // -- OP_maxsd:
    // -- OP_cmpps:
    // -- OP_cmpss:
    // -- OP_cmppd:
    // -- OP_cmpsd:
    // -- OP_shufps:
    // -- OP_shufpd:
    // -- OP_cvtdq2pd:
    // -- OP_cvttpd2dq:
    // -- OP_cvtpd2dq:

    // -- OP_nop:
    ib_hook_skip(tb_ctx->tool_info, OP_nop);

    // -- OP_pause:

    // -- OP_ins:
    // -- OP_rep_ins:
    // -- OP_outs:
    // -- OP_rep_outs:

    // -- OP_movs:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVS_DMEM_1_SMEM_1]),
            init_option, ub_is_mov_dmem_1_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVS_DMEM_2_SMEM_2]),
            init_option, ub_is_mov_dmem_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVS_DMEM_4_SMEM_4]),
            init_option, ub_is_mov_dmem_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVS_DMEM_8_SMEM_8]),
            init_option, ub_is_mov_dmem_8_smem_8_instr, IB_GUARD_HOOK);

    // -- OP_rep_movs:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_MOVSB]), init_option,
            ub_is_rep_movsb_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_MOVSW]), init_option,
            ub_is_rep_movsw_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_MOVSD]), init_option,
            ub_is_rep_movsd_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_movs,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_MOVSQ]), init_option,
            ub_is_rep_movsq_instr, IB_GUARD_HOOK);

    // -- OP_stos:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_STOS_DMEM_1_SREG_1]),
            init_option, ub_is_mov_dmem_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_STOS_DMEM_2_SREG_2]),
            init_option, ub_is_mov_dmem_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_STOS_DMEM_4_SREG_4]),
            init_option, ub_is_mov_dmem_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_STOS_DMEM_8_SREG_8]),
            init_option, ub_is_mov_dmem_8_sreg_8_instr, IB_GUARD_HOOK);

    // -- OP_rep_stos:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_STOSB]), init_option,
            ub_is_rep_stosb_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_STOSW]), init_option,
            ub_is_rep_stosw_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_STOSD]), init_option,
            ub_is_rep_stosd_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_rep_stos,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_REP_STOSQ]), init_option,
            ub_is_rep_stosq_instr, IB_GUARD_HOOK);

    // -- OP_lods:
    // -- OP_rep_lods:
    // -- OP_cmps:
    ib_hook_skip(tb_ctx->tool_info, OP_cmps);

    // -- OP_rep_cmps:
    ib_hook_skip(tb_ctx->tool_info, OP_rep_cmps);

    // -- OP_repne_cmps:
    ib_hook_skip(tb_ctx->tool_info, OP_repne_cmps);

    // -- OP_scas:
    ib_hook_skip(tb_ctx->tool_info, OP_scas);

    // -- OP_rep_scas:
    ib_hook_skip(tb_ctx->tool_info, OP_rep_scas);

    // -- OP_repne_scas:
    ib_hook_skip(tb_ctx->tool_info, OP_repne_scas);

    // -- OP_fadd:
    // -- OP_fmul:
    // -- OP_fcom:
    // -- OP_fcomp:
    // -- OP_fsub:
    // -- OP_fsubr:
    // -- OP_fdiv:
    // -- OP_fdivr:
    // -- OP_fld:
    // -- OP_fst:
    // -- OP_fstp:
    // -- OP_fldenv:
    // -- OP_fldcw:
    // -- OP_fnstenv:
    // -- OP_fnstcw:
    // -- OP_fiadd:
    // -- OP_fimul:
    // -- OP_ficom:
    // -- OP_ficomp:
    // -- OP_fisub:
    // -- OP_fisubr:
    // -- OP_fidiv:
    // -- OP_fidivr:
    // -- OP_fild:
    // -- OP_fist:
    // -- OP_fistp:
    // -- OP_frstor:
    // -- OP_fnsave:
    // -- OP_fnstsw:

    // -- OP_fbld:
    // -- OP_fbstp:

    // -- OP_fxch:
    // -- OP_fnop:
    ib_hook_skip(tb_ctx->tool_info, OP_fnop);

    // -- OP_fchs:
    // -- OP_fabs:
    // -- OP_ftst:
    // -- OP_fxam:
    // -- OP_fld1:
    // -- OP_fldl2t:
    // -- OP_fldl2e:
    // -- OP_fldpi:
    // -- OP_fldlg2:
    // -- OP_fldln2:
    // -- OP_fldz:
    // -- OP_f2xm1:
    // -- OP_fyl2x:
    // -- OP_fptan:
    // -- OP_fpatan:
    // -- OP_fxtract:
    // -- OP_fprem1:
    // -- OP_fdecstp:
    // -- OP_fincstp:
    // -- OP_fprem:
    // -- OP_fyl2xp1:
    // -- OP_fsqrt:
    // -- OP_fsincos:
    // -- OP_frndint:
    // -- OP_fscale:
    // -- OP_fsin:
    // -- OP_fcos:
    // -- OP_fcmovb:
    // -- OP_fcmove:
    // -- OP_fcmovbe:
    // -- OP_fcmovu:
    // -- OP_fucompp:
    // -- OP_fcmovnb:
    // -- OP_fcmovne:
    // -- OP_fcmovnbe:
    // -- OP_fcmovnu:
    // -- OP_fnclex:
    // -- OP_fninit:
    // -- OP_fucomi:
    // -- OP_fcomi:
    // -- OP_ffree:
    // -- OP_fucom:
    // -- OP_fucomp:
    // -- OP_faddp:
    // -- OP_fmulp:
    // -- OP_fcompp:
    // -- OP_fsubrp:
    // -- OP_fsubp:
    // -- OP_fdivrp:
    // -- OP_fdivp:
    // -- OP_fucomip:
    // -- OP_fcomip:
    // -- OP_fisttp:
    // -- OP_haddpd:
    // -- OP_haddps:
    // -- OP_hsubpd:
    // -- OP_hsubps:
    // -- OP_addsubpd:
    // -- OP_addsubps:

    // -- OP_lddqu:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lddqu,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LDDQU_DREG_16_SMEM_16]),
            init_option, ub_is_mov_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    // -- OP_monitor:
    // -- OP_mwait:
    // -- OP_movsldup:
    // -- OP_movshdup:
    // -- OP_movddup:

    // -- OP_femms:
    // -- OP_unknown_3dnow:
    // -- OP_pavgusb:
    // -- OP_pfadd:
    // -- OP_pfacc:
    // -- OP_pfcmpge:
    // -- OP_pfcmpgt:
    // -- OP_pfcmpeq:
    // -- OP_pfmin:
    // -- OP_pfmax:
    // -- OP_pfmul:
    // -- OP_pfrcp:
    // -- OP_pfrcpit1:
    // -- OP_pfrcpit2:
    // -- OP_pfrsqrt:
    // -- OP_pfrsqit1:
    // -- OP_pmulhrw:
    // -- OP_pfsub:
    // -- OP_pfsubr:
    // -- OP_pi2fd:
    // -- OP_pf2id:
    // -- OP_pi2fw:
    // -- OP_pf2iw:
    // -- OP_pfnacc:
    // -- OP_pfpnacc:
    // -- OP_pswapd:

    // -- OP_pshufb:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshufb, &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFB_DREG_8_SMEM_8]),
            init_option, ub_is_srcdst_src_dreg_8_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshufb, &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFB_DREG_8_SREG_8]),
            init_option, ub_is_srcdst_src_dreg_8_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshufb, &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFB_DREG_16_SMEM_16]),
            init_option, ub_is_srcdst_src_dreg_16_smem_16_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pshufb, &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PSHUFB_DREG_16_SREG_16]),
            init_option, ub_is_srcdst_src_dreg_16_sreg_16_instr, IB_GUARD_HOOK);


    // -- OP_phaddw:
    // -- OP_phaddd:
    // -- OP_phaddsw:
    // -- OP_pmaddubsw:
    // -- OP_phsubw:
    // -- OP_phsubd:
    // -- OP_phsubsw:
    // -- OP_psignb:
    // -- OP_psignw:
    // -- OP_psignd:
    // -- OP_pmulhrsw:
    // -- OP_pabsb:
     // -- OP_pabsw:
    // -- OP_pabsd:

    // -- OP_palignr:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_palignr,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PALIGNR_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PALIGNR_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PALIGNR_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PALIGNR_DREG_16_SREG_16]));

    // -- OP_popcnt:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_popcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POPCNT_DREG_2_SREG_2]),
            init_option, ub_is_mov_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_popcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POPCNT_DREG_2_SMEM_2]),
            init_option, ub_is_mov_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_popcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POPCNT_DREG_4_SREG_4]),
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_popcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POPCNT_DREG_4_SMEM_4]),
            init_option, ub_is_mov_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_popcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POPCNT_DREG_8_SREG_8]),
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_popcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_POPCNT_DREG_8_SMEM_8]),
            init_option, ub_is_mov_dreg_8_smem_8_instr, IB_GUARD_HOOK);

    // -- OP_movntss:
    // -- OP_movntsd:
    // -- OP_extrq:
    // -- OP_insertq:

    // -- OP_lzcnt:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LZCNT_DREG_2_SMEM_2]),
            init_option, ub_is_mov_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LZCNT_DREG_4_SMEM_4]),
            init_option, ub_is_mov_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LZCNT_DREG_8_SMEM_8]),
            init_option, ub_is_mov_dreg_8_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LZCNT_DREG_2_SREG_2]),
            init_option, ub_is_mov_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LZCNT_DREG_4_SREG_4]),
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_lzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_LZCNT_DREG_8_SREG_8]),
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);

    // -- OP_pblendvb:
    // -- OP_blendvps:
    // -- OP_blendvpd:

    // -- OP_ptest:
    ib_hook_skip(tb_ctx->tool_info, OP_ptest);

    // -- OP_pmovsxbw:
    // -- OP_pmovsxbd:
    // -- OP_pmovsxbq:
    // -- OP_pmovsxwd:
    // -- OP_pmovsxwq:
    // -- OP_pmovsxdq:
    // -- OP_pmuldq:

    // -- OP_pcmpeqq:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpeqq,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQQ_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQQ_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQQ_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPEQQ_DREG_16_SREG_16]));

    // -- OP_movntdqa:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movntdqa,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQU_DREG_16_SMEM_16]),
            init_option, ub_is_mov_dreg_16_smem_16_instr, IB_GUARD_HOOK);

    // -- OP_packusdw:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_packusdw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKUSDW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PACKUSDW_DREG_16_SREG_16]));

    // -- OP_pmovzxbw:
    // -- OP_pmovzxbd:
    // -- OP_pmovzxbq:
    // -- OP_pmovzxwd:
    // -- OP_pmovzxwq:
    // -- OP_pmovzxdq:

    // -- OP_pcmpgtq:
    tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_ctx, OP_pcmpgtq,
            init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTQ_DREG_8_SMEM_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTQ_DREG_8_SREG_8]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTQ_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PCMPGTQ_DREG_16_SREG_16]));

    // -- OP_pminsb:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pminsb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSB_DREG_16_SREG_16]));

    // -- OP_pminsd:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pminsd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINSD_DREG_16_SREG_16]));

    // -- OP_pminuw:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pminuw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUW_DREG_16_SREG_16]));

    // -- OP_pminud:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pminud, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMINUD_DREG_16_SREG_16]));

    // -- OP_pmaxsb:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pmaxsb, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSB_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSB_DREG_16_SREG_16]));

    // -- OP_pmaxsd:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pmaxsd, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXSD_DREG_16_SREG_16]));

    // -- OP_pmaxuw:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pmaxuw, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUW_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUW_DREG_16_SREG_16]));

    // -- OP_pmaxud:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pmaxud, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMAXUD_DREG_16_SREG_16]));

    // -- OP_pmulld:
    tb_register_pinstr_dreg_sreg_or_smem_16(tb_ctx, OP_pmulld, init_option,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULLD_DREG_16_SMEM_16]),
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PMULLD_DREG_16_SREG_16]));

    // -- OP_phminposuw:
    // -- OP_crc32:
    // -- OP_pextrb:

    tb_register_hook_instrum_hndlr(tb_ctx, OP_pextrb,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXTRB_DREG_4]),
            init_option, ub_is_pextr_dreg_4_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pextrb,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXTRB_DMEM_4]),
            init_option, ub_is_pextr_dmem_1_sreg_16, IB_GUARD_HOOK);

    // -- OP_pextrd:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pextrd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXTRD_DREG_4]),
            init_option, ub_is_pextr_dreg_4_sreg_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pextrd,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXTRD_DMEM_4]),
            init_option, ub_is_pextr_dmem_4_sreg_16, IB_GUARD_HOOK);

    // -- OP_extractps:
    // -- OP_roundps:
    // -- OP_roundpd:
    // -- OP_roundss:
    // -- OP_roundsd:
    // -- OP_blendps:
    // -- OP_blendpd:
    // -- OP_pblendw:
    // -- OP_pinsrb:
    // -- OP_insertps:
    // -- OP_pinsrd:
    // -- OP_dpps:
    // -- OP_dppd:
    // -- OP_mpsadbw:
    // -- OP_pcmpestrm:
    // -- OP_pcmpestri:
    // -- OP_pcmpistrm:
    // -- OP_pcmpistri:

    // -- OP_movsxd:
    // -- OP_swapgs:

    // -- OP_vmcall:
    // -- OP_vmlaunch:
    // -- OP_vmresume:
    // -- OP_vmxoff:
    // -- OP_vmptrst:
    // -- OP_vmptrld:
    // -- OP_vmxon:
    // -- OP_vmclear:
    // -- OP_vmread:
    // -- OP_vmwrite:

    // -- OP_int1:
    // -- OP_salc:
    // -- OP_ffreep:

    // -- OP_vmrun:
    // -- OP_vmmcall:
    // -- OP_vmload:
    // -- OP_vmsave:
    // -- OP_stgi:
    // -- OP_clgi:
    // -- OP_skinit:
    // -- OP_invlpga:

    // -- OP_rdtscp:

    // -- OP_invept:
    // -- OP_invvpid:

    // -- OP_pclmulqdq:
    // -- OP_aesimc:
    // -- OP_aesenc:
    // -- OP_aesenclast:
    // -- OP_aesdec:
    // -- OP_aesdeclast:
    // -- OP_aeskeygenassist:

    // -- OP_movbe:

    // -- OP_xgetbv:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_xgetbv,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_UNTAINT_FIRST_2_DREGS_4]),
            init_option, NULL, IB_GUARD_HOOK);

    // -- OP_xsetbv:
    // -- OP_xsave32:
    // -- OP_xrstor32:
    // -- OP_xsave// OPt32:

    // -- OP_vmovss:
    // -- OP_vmovsd:
    // -- OP_vmovups:
    // -- OP_vmovupd:
    // -- OP_vmovlps:
    // -- OP_vmovsldup:
    // -- OP_vmovlpd:
    // -- OP_vmovddup:
    // -- OP_vunpcklps:
    // -- OP_vunpcklpd:
    // -- OP_vunpckhps:
    // -- OP_vunpckhpd:
    // -- OP_vmovhps:
    // -- OP_vmovshdup:
    // -- OP_vmovhpd:
    // -- OP_vmovaps:
    // -- OP_vmovapd:
    // -- OP_vcvtsi2ss:
    // -- OP_vcvtsi2sd:
    // -- OP_vmovntps:
    // -- OP_vmovntpd:
    // -- OP_vcvttss2si:
    // -- OP_vcvttsd2si:
    // -- OP_vcvtss2si:
    // -- OP_vcvtsd2si:
    // -- OP_vucomiss:
    // -- OP_vucomisd:
    // -- OP_vcomiss:
    // -- OP_vcomisd:
    // -- OP_vmovmskps:
    // -- OP_vmovmskpd:
    // -- OP_vsqrtps:
    // -- OP_vsqrtss:
    // -- OP_vsqrtpd:
    // -- OP_vsqrtsd:
    // -- OP_vrsqrtps:
    // -- OP_vrsqrtss:
    // -- OP_vrcpps:
    // -- OP_vrcpss:
    // -- OP_vandps:
    // -- OP_vandpd:
    // -- OP_vandnps:
    // -- OP_vandnpd:
    // -- OP_vorps:
    // -- OP_vorpd:
    // -- OP_vxorps:
    // -- OP_vxorpd:
    // -- OP_vaddps:
    // -- OP_vaddss:
    // -- OP_vaddpd:
    // -- OP_vaddsd:
    // -- OP_vmulps:
    // -- OP_vmulss:
    // -- OP_vmulpd:
    // -- OP_vmulsd:
    // -- OP_vcvtps2pd:
    // -- OP_vcvtss2sd:
    // -- OP_vcvtpd2ps:
    // -- OP_vcvtsd2ss:
    // -- OP_vcvtdq2ps:
    // -- OP_vcvttps2dq:
    // -- OP_vcvtps2dq:
    // -- OP_vsubps:
    // -- OP_vsubss:
    // -- OP_vsubpd:
    // -- OP_vsubsd:
    // -- OP_vminps:
    // -- OP_vminss:
    // -- OP_vminpd:
    // -- OP_vminsd:
    // -- OP_vdivps:
    // -- OP_vdivss:
    // -- OP_vdivpd:
    // -- OP_vdivsd:
    // -- OP_vmaxps:
    // -- OP_vmaxss:
    // -- OP_vmaxpd:
    // -- OP_vmaxsd:
    // -- OP_vpunpcklbw:
    // -- OP_vpunpcklwd:
    // -- OP_vpunpckldq:
    // -- OP_vpacksswb:
    // -- OP_vpcmpgtb:
    // -- OP_vpcmpgtw:
    // -- OP_vpcmpgtd:
    // -- OP_vpackuswb:
    // -- OP_vpunpckhbw:
    // -- OP_vpunpckhwd:
    // -- OP_vpunpckhdq:
    // -- OP_vpackssdw:
    // -- OP_vpunpcklqdq:
    // -- OP_vpunpckhqdq:
    // -- OP_vmovd:
    // -- OP_vpshufhw:
    // -- OP_vpshufd:
    // -- OP_vpshuflw:
    // -- OP_vpcmpeqb:
    // -- OP_vpcmpeqw:
    // -- OP_vpcmpeqd:
    // -- OP_vmovq:
    // -- OP_vcmpps:
    // -- OP_vcmpss:
    // -- OP_vcmppd:
    // -- OP_vcmpsd:
    // -- OP_vpinsrw:
    // -- OP_vpextrw:
    // -- OP_vshufps:
    // -- OP_vshufpd:
    // -- OP_vpsrlw:
    // -- OP_vpsrld:
    // -- OP_vpsrlq:
    // -- OP_vpaddq:
    // -- OP_vpmullw:
    // -- OP_vpmovmskb:
    // -- OP_vpsubusb:
    // -- OP_vpsubusw:
    // -- OP_vpminub:
    // -- OP_vpand:
    // -- OP_vpaddusb:
    // -- OP_vpaddusw:
    // -- OP_vpmaxub:
    // -- OP_vpandn:
    // -- OP_vpavgb:
    // -- OP_vpsraw:
    // -- OP_vpsrad:
    // -- OP_vpavgw:
    // -- OP_vpmulhuw:
    // -- OP_vpmulhw:
    // -- OP_vcvtdq2pd:
    // -- OP_vcvttpd2dq:
    // -- OP_vcvtpd2dq:
    // -- OP_vmovntdq:
    // -- OP_vpsubsb:
    // -- OP_vpsubsw:
    // -- OP_vpminsw:
    // -- OP_vpor:
    // -- OP_vpaddsb:
    // -- OP_vpaddsw:
    // -- OP_vpmaxsw:
    // -- OP_vpxor:
    // -- OP_vpsllw:
    // -- OP_vpslld:
    // -- OP_vpsllq:
    // -- OP_vpmuludq:
    // -- OP_vpmaddwd:
    // -- OP_vpsadbw:
    // -- OP_vmaskmovdqu:
    // -- OP_vpsubb:
    // -- OP_vpsubw:
    // -- OP_vpsubd:
    // -- OP_vpsubq:
    // -- OP_vpaddb:
    // -- OP_vpaddw:
    // -- OP_vpaddd:
    // -- OP_vpsrldq:
    // -- OP_vpslldq:
    // -- OP_vmovdqu:
    // -- OP_vmovdqa:
    // -- OP_vhaddpd:
    // -- OP_vhaddps:
    // -- OP_vhsubpd:
    // -- OP_vhsubps:
    // -- OP_vaddsubpd:
    // -- OP_vaddsubps:
    // -- OP_vlddqu:
    // -- OP_vpshufb:
    // -- OP_vphaddw:
    // -- OP_vphaddd:
    // -- OP_vphaddsw:
    // -- OP_vpmaddubsw:
    // -- OP_vphsubw:
    // -- OP_vphsubd:
    // -- OP_vphsubsw:
    // -- OP_vpsignb:
    // -- OP_vpsignw:
    // -- OP_vpsignd:
    // -- OP_vpmulhrsw:
    // -- OP_vpabsb:
    // -- OP_vpabsw:
    // -- OP_vpabsd:
    // -- OP_vpalignr:
    // -- OP_vpblendvb:
    // -- OP_vblendvps:
    // -- OP_vblendvpd:
    // -- OP_vptest:
    // -- OP_vpmovsxbw:
    // -- OP_vpmovsxbd:
    // -- OP_vpmovsxbq:
    // -- OP_vpmovsxwd:
    // -- OP_vpmovsxwq:
    // -- OP_vpmovsxdq:
    // -- OP_vpmuldq:
    // -- OP_vpcmpeqq:
    // -- OP_vmovntdqa:
    // -- OP_vpackusdw:
    // -- OP_vpmovzxbw:
    // -- OP_vpmovzxbd:
    // -- OP_vpmovzxbq:
    // -- OP_vpmovzxwd:
    // -- OP_vpmovzxwq:
    // -- OP_vpmovzxdq:
    // -- OP_vpcmpgtq:
    // -- OP_vpminsb:
    // -- OP_vpminsd:
    // -- OP_vpminuw:
    // -- OP_vpminud:
    // -- OP_vpmaxsb:
    // -- OP_vpmaxsd:
    // -- OP_vpmaxuw:
    // -- OP_vpmaxud:
    // -- OP_vpmulld:
    // -- OP_vphminposuw:
    // -- OP_vaesimc:
    // -- OP_vaesenc:
    // -- OP_vaesenclast:
    // -- OP_vaesdec:
    // -- OP_vaesdeclast:
    // -- OP_vpextrb:
    // -- OP_vpextrd:
    // -- OP_vextractps:
    // -- OP_vroundps:
    // -- OP_vroundpd:
    // -- OP_vroundss:
    // -- OP_vroundsd:
    // -- OP_vblendps:
    // -- OP_vblendpd:
    // -- OP_vpblendw:
    // -- OP_vpinsrb:
    // -- OP_vinsertps:
    // -- OP_vpinsrd:
    // -- OP_vdpps:
    // -- OP_vdppd:
    // -- OP_vmpsadbw:
    // -- OP_vpcmpestrm:
    // -- OP_vpcmpestri:
    // -- OP_vpcmpistrm:
    // -- OP_vpcmpistri:
    // -- OP_vpclmulqdq:
    // -- OP_vaeskeygenassist:
    // -- OP_vtestps:
    // -- OP_vtestpd:
    // -- OP_vzeroupper:
    // -- OP_vzeroall:
    // -- OP_vldmxcsr:
    // -- OP_vstmxcsr:
    // -- OP_vbroadcastss:
    // -- OP_vbroadcastsd:
    // -- OP_vbroadcastf128:
    // -- OP_vmaskmovps:
    // -- OP_vmaskmovpd:
    // -- OP_vpermilps:
    // -- OP_vpermilpd:
    // -- OP_vperm2f128:
    // -- OP_vinsertf128:
    // -- OP_vextractf128:

    // -- OP_vcvtph2ps:
    // -- OP_vcvtps2ph:

    // -- OP_vfmadd132ps:
    // -- OP_vfmadd132pd:
    // -- OP_vfmadd213ps:
    // -- OP_vfmadd213pd:
    // -- OP_vfmadd231ps:
    // -- OP_vfmadd231pd:
    // -- OP_vfmadd132ss:
    // -- OP_vfmadd132sd:
    // -- OP_vfmadd213ss:
    // -- OP_vfmadd213sd:
    // -- OP_vfmadd231ss:
    // -- OP_vfmadd231sd:
    // -- OP_vfmaddsub132ps:
    // -- OP_vfmaddsub132pd:
    // -- OP_vfmaddsub213ps:
    // -- OP_vfmaddsub213pd:
    // -- OP_vfmaddsub231ps:
    // -- OP_vfmaddsub231pd:
    // -- OP_vfmsubadd132ps:
    // -- OP_vfmsubadd132pd:
    // -- OP_vfmsubadd213ps:
    // -- OP_vfmsubadd213pd:
    // -- OP_vfmsubadd231ps:
    // -- OP_vfmsubadd231pd:
    // -- OP_vfmsub132ps:
    // -- OP_vfmsub132pd:
    // -- OP_vfmsub213ps:
    // -- OP_vfmsub213pd:
    // -- OP_vfmsub231ps:
    // -- OP_vfmsub231pd:
    // -- OP_vfmsub132ss:
    // -- OP_vfmsub132sd:
    // -- OP_vfmsub213ss:
    // -- OP_vfmsub213sd:
    // -- OP_vfmsub231ss:
    // -- OP_vfmsub231sd:
    // -- OP_vfnmadd132ps:
    // -- OP_vfnmadd132pd:
    // -- OP_vfnmadd213ps:
    // -- OP_vfnmadd213pd:
    // -- OP_vfnmadd231ps:
    // -- OP_vfnmadd231pd:
    // -- OP_vfnmadd132ss:
    // -- OP_vfnmadd132sd:
    // -- OP_vfnmadd213ss:
    // -- OP_vfnmadd213sd:
    // -- OP_vfnmadd231ss:
    // -- OP_vfnmadd231sd:
    // -- OP_vfnmsub132ps:
    // -- OP_vfnmsub132pd:
    // -- OP_vfnmsub213ps:
    // -- OP_vfnmsub213pd:
    // -- OP_vfnmsub231ps:
    // -- OP_vfnmsub231pd:
    // -- OP_vfnmsub132ss:
    // -- OP_vfnmsub132sd:
    // -- OP_vfnmsub213ss:
    // -- OP_vfnmsub213sd:
    // -- OP_vfnmsub231ss:
    // -- OP_vfnmsub231sd:

    // -- OP_movq2dq:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movq2dq,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVQ2DQ_DREG_16_SREG_8]),
            init_option, ub_is_mov_dreg_16_sreg_8_instr, IB_GUARD_HOOK);

    // -- OP_movdq2q:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_movdq2q,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_MOVDQ2Q_DREG_8_SREG_16]),
            init_option, ub_is_mov_dreg_8_sreg_16_instr, IB_GUARD_HOOK);

    // -- OP_fxsave64:
    // -- OP_fxrstor64:
    // -- OP_xsave64:
    // -- OP_xrstor64:
    // -- OP_xsave// OPt64:

    // -- OP_rdrand:
    // -- OP_rdfsbase:
    // -- OP_rdgsbase:
    // -- OP_wrfsbase:
    // -- OP_wrgsbase:

    // -- OP_rdseed:

    // -- OP_vfmaddsubps:
    // -- OP_vfmaddsubpd:
    // -- OP_vfmsubaddps:
    // -- OP_vfmsubaddpd:
    // -- OP_vfmaddps:
    // -- OP_vfmaddpd:
    // -- OP_vfmaddss:
    // -- OP_vfmaddsd:
    // -- OP_vfmsubps:
    // -- OP_vfmsubpd:
    // -- OP_vfmsubss:
    // -- OP_vfmsubsd:
    // -- OP_vfnmaddps:
    // -- OP_vfnmaddpd:
    // -- OP_vfnmaddss:
    // -- OP_vfnmaddsd:
    // -- OP_vfnmsubps:
    // -- OP_vfnmsubpd:
    // -- OP_vfnmsubss:
    // -- OP_vfnmsubsd:

    // -- OP_vfrczps:
    // -- OP_vfrczpd:
    // -- OP_vfrczss:
    // -- OP_vfrczsd:
    // -- OP_vpcmov:
    // -- OP_vpcomb:
    // -- OP_vpcomw:
    // -- OP_vpcomd:
    // -- OP_vpcomq:
    // -- OP_vpcomub:
    // -- OP_vpcomuw:
    // -- OP_vpcomud:
    // -- OP_vpcomuq:
    // -- OP_vpermil2pd:
    // -- OP_vpermil2ps:
    // -- OP_vphaddbw:
    // -- OP_vphaddbd:
    // -- OP_vphaddbq:
    // -- OP_vphaddwd:
    // -- OP_vphaddwq:
    // -- OP_vphadddq:
    // -- OP_vphaddubw:
    // -- OP_vphaddubd:
    // -- OP_vphaddubq:
    // -- OP_vphadduwd:
    // -- OP_vphadduwq:
    // -- OP_vphaddudq:
    // -- OP_vphsubbw:
    // -- OP_vphsubwd:
    // -- OP_vphsubdq:
    // -- OP_vpmacssww:
    // -- OP_vpmacsswd:
    // -- OP_vpmacssdql:
    // -- OP_vpmacssdd:
    // -- OP_vpmacssdqh:
    // -- OP_vpmacsww:
    // -- OP_vpmacswd:
    // -- OP_vpmacsdql:
    // -- OP_vpmacsdd:
    // -- OP_vpmacsdqh:
    // -- OP_vpmadcsswd:
    // -- OP_vpmadcswd:
    // -- OP_vpperm:
    // -- OP_vprotb:
    // -- OP_vprotw:
    // -- OP_vprotd:
    // -- OP_vprotq:
    // -- OP_vpshlb:
    // -- OP_vpshlw:
    // -- OP_vpshld:
    // -- OP_vpshlq:
    // -- OP_vpshab:
    // -- OP_vpshaw:
    // -- OP_vpshad:
    // -- OP_vpshaq:

    // -- OP_bextr:
    // -- OP_blcfill:
    // -- OP_blci:
    // -- OP_blcic:
    // -- OP_blcmsk:
    // -- OP_blcs:
    // -- OP_blsfill:
    // -- OP_blsic:
    // -- OP_t1mskc:
    // -- OP_tzmsk:

    // -- OP_llwpcb:
    // -- OP_slwpcb:
    // -- OP_lwpins:
    // -- OP_lwpval:

    // -- OP_andn:
    // -- OP_blsr:
    // -- OP_blsmsk:
    // -- OP_blsi:

    // -- OP_tzcnt:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_tzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_TZCNT_DREG_2_SMEM_2]),
            init_option, ub_is_mov_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_tzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_TZCNT_DREG_4_SMEM_4]),
            init_option, ub_is_mov_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_tzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_TZCNT_DREG_8_SMEM_8]),
            init_option, ub_is_mov_dreg_8_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_tzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_TZCNT_DREG_2_SREG_2]),
            init_option, ub_is_mov_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_tzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_TZCNT_DREG_4_SREG_4]),
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_tzcnt,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_TZCNT_DREG_8_SREG_8]),
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);

    // -- OP_bzhi:

    // -- OP_pext:
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pext,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXT_DREG_4_SREG_4_SREG_4]),
            init_option, ub_is_pext_dreg_4_sreg_4_sreg_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pext,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXT_DREG_8_SREG_8_SREG_8]),
            init_option, ub_is_pext_dreg_8_sreg_8_sreg_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pext,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXT_DREG_4_SREG_4_SMEM_4]),
            init_option, ub_is_pext_dreg_4_sreg_4_smem_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, OP_pext,
            &(taint_engine->instr_hndlrs[TB_INSTRUM_ID_PEXT_DREG_8_SREG_8_SMEM_8]),
            init_option, ub_is_pext_dreg_8_sreg_8_smem_8, IB_GUARD_HOOK);

    // -- OP_pdep:
    // -- OP_sarx:
    // -- OP_shlx:
    // -- OP_shrx:
    // -- OP_rorx:
    // -- OP_mulx:

    // -- OP_getsec:

    // -- OP_vmfunc:
    // -- OP_invpcid:

    // -- OP_xabort:
    // -- OP_xbegin:
    // -- OP_xend:
    // -- OP_xtest:

    // -- OP_vpgatherdd:
    // -- OP_vpgatherdq:
    // -- OP_vpgatherqd:
    // -- OP_vpgatherqq:
    // -- OP_vgatherdps:
    // -- OP_vgatherdpd:
    // -- OP_vgatherqps:
    // -- OP_vgatherqpd:
    // -- OP_vbroadcasti128:
    // -- OP_vinserti128:
    // -- OP_vextracti128:
    // -- OP_vpmaskmovd:
    // -- OP_vpmaskmovq:
    // -- OP_vperm2i128:
    // -- OP_vpermd:
    // -- OP_vpermps:
    // -- OP_vpermq:
    // -- OP_vpermpd:
    // -- OP_vpblendd:
    // -- OP_vpsllvd:
    // -- OP_vpsllvq:
    // -- OP_vpsravd:
    // -- OP_vpsrlvd:
    // -- OP_vpsrlvq:
    // -- OP_vpbroadcastb:
    // -- OP_vpbroadcastw:
    // -- OP_vpbroadcastd:
    // -- OP_vpbroadcastq:

    // -- OP_xsavec32:
    // -- OP_xsavec64:

    // -- OP_adox:
    // -- OP_adcx:

    tb_register_default_hooks(tb_ctx);
}
