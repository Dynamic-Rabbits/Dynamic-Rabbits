/*
 * tb_instrum_register_healper.c
 *
 *      Author: john
 */

#include "tb_instrum_register_helper.h"

void tb_register_hook_instrum_hndlr(tb_context_t *tb_ctx, int opcode,
        tb_instr_hndlr_t * instr_hndlr, IB_INSTRUM_OPT options,
        ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result) {

    if (instr_hndlr->is_cached) {

        ib_hook_cache_to_instr_ex(tb_ctx->tool_info, opcode,
                &(instr_hndlr->instr_handler_data),
                options | instr_hndlr->options,
                IB_INSTRUM_BEFORE, check_hook_guard, action_result);
    } else {

        ib_hook_to_instr_ex(tb_ctx->tool_info, opcode,
                &(instr_hndlr->instr_handler_data),
                options | instr_hndlr->options,
                IB_INSTRUM_BEFORE, check_hook_guard, action_result);
    }
}

void tb_register_bs(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *dreg_2_smem_2_hndlr,
        tb_instr_hndlr_t *dreg_4_smem_4_hndlr,
        tb_instr_hndlr_t *dreg_8_smem_8_hndlr,
        tb_instr_hndlr_t *dreg_2_sreg_2_hndlr,
        tb_instr_hndlr_t *dreg_4_sreg_4_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_smem_2_hndlr,
            init_option, ub_is_mov_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_smem_4_hndlr,
            init_option, ub_is_mov_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_smem_8_hndlr,
            init_option, ub_is_mov_dreg_8_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_sreg_2_hndlr,
            init_option, ub_is_mov_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_sreg_4_hndlr,
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_hndlr,
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);

}

void tb_register_pshift(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option,
        tb_instr_hndlr_t *dreg_8_sreg_8_sreg_8_hndlr,
        tb_instr_hndlr_t *dreg_16_sreg_16_sreg_16_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_smem_8_hndlr,
        tb_instr_hndlr_t *dreg_16_sreg_16_smem_16_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_16_sreg_16_simm_1_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_sreg_8_hndlr,
            init_option, ub_is_reg_pshift_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode,
            dreg_16_sreg_16_sreg_16_hndlr, init_option, ub_is_reg_pshift_16,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_smem_8_hndlr,
            init_option, ub_is_mem_pshift_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode,
            dreg_16_sreg_16_smem_16_hndlr, init_option, ub_is_mem_pshift_16,
            IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_simm_1_hndlr,
            init_option, ub_is_immed_reg_shift_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_16_sreg_16_simm_1_hndlr,
            init_option, ub_is_immed_reg_shift_16, IB_GUARD_HOOK);

}

void tb_register_pshiftd(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option,
        tb_instr_hndlr_t *dmem_2_sreg_2_simm_1_hndlr,
        tb_instr_hndlr_t *dmem_4_sreg_4_simm_1_hndlr,
        tb_instr_hndlr_t *dmem_8_sreg_8_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_2_sreg_2_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_4_sreg_4_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_simm_1_hndlr,
        tb_instr_hndlr_t *dmem_2_sreg_2_sreg_1_hndlr,
        tb_instr_hndlr_t *dmem_4_sreg_4_sreg_1_hndlr,
        tb_instr_hndlr_t *dmem_8_sreg_8_sreg_1_hndlr,
        tb_instr_hndlr_t *dreg_2_sreg_2_sreg_1_hndlr,
        tb_instr_hndlr_t *dreg_4_sreg_4_sreg_1_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_sreg_1_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_2_sreg_2_simm_1_hndlr,
            init_option, ub_is_shiftd_dmem_2_sreg_2_simm_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_4_sreg_4_simm_1_hndlr,
            init_option, ub_is_shiftd_dmem_4_sreg_4_simm_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_8_sreg_8_simm_1_hndlr,
            init_option, ub_is_shiftd_dmem_8_sreg_8_simm_1, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_sreg_2_simm_1_hndlr,
            init_option, ub_is_shiftd_dreg_2_sreg_2_simm_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_sreg_4_simm_1_hndlr,
            init_option, ub_is_shiftd_dreg_4_sreg_4_simm_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_simm_1_hndlr,
            init_option, ub_is_shiftd_dreg_8_sreg_8_simm_1, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_2_sreg_2_sreg_1_hndlr,
            init_option, ub_is_shiftd_dmem_2_sreg_2_sreg_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_4_sreg_4_sreg_1_hndlr,
            init_option, ub_is_shiftd_dmem_4_sreg_4_sreg_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_8_sreg_8_sreg_1_hndlr,
            init_option, ub_is_shiftd_dmem_8_sreg_8_sreg_1, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_sreg_2_sreg_1_hndlr,
            init_option, ub_is_shiftd_dreg_2_sreg_2_sreg_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_sreg_4_sreg_1_hndlr,
            init_option, ub_is_shiftd_dreg_4_sreg_4_sreg_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_sreg_1_hndlr,
            init_option, ub_is_shiftd_dreg_8_sreg_8_sreg_1, IB_GUARD_HOOK);
}

void tb_register_shift(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *sole_dreg_1_hndlr,
        tb_instr_hndlr_t *sole_dreg_2_hndlr,
        tb_instr_hndlr_t *sole_dreg_4_hndlr,
        tb_instr_hndlr_t *sole_dreg_8_hndlr,
        tb_instr_hndlr_t *dreg_1_imm_1_hndlr,
        tb_instr_hndlr_t *dreg_2_imm_1_hndlr,
        tb_instr_hndlr_t *dreg_4_imm_1_hndlr,
        tb_instr_hndlr_t *dreg_8_imm_1_hndlr,
        tb_instr_hndlr_t *dreg_1_reg_1_hndlr,
        tb_instr_hndlr_t *dreg_2_reg_1_hndlr,
        tb_instr_hndlr_t *dreg_4_reg_1_hndlr,
        tb_instr_hndlr_t *dreg_8_reg_1_hndlr,
        tb_instr_hndlr_t *sole_dmem_1_hndlr,
        tb_instr_hndlr_t *sole_dmem_2_hndlr,
        tb_instr_hndlr_t *sole_dmem_4_hndlr,
        tb_instr_hndlr_t *sole_dmem_8_hndlr,
        tb_instr_hndlr_t *dmem_1_imm_1_hndlr,
        tb_instr_hndlr_t *dmem_2_imm_1_hndlr,
        tb_instr_hndlr_t *dmem_4_imm_1_hndlr,
        tb_instr_hndlr_t *dmem_8_imm_1_hndlr,
        tb_instr_hndlr_t *dmem_1_reg_1_hndlr,
        tb_instr_hndlr_t *dmem_2_reg_1_hndlr,
        tb_instr_hndlr_t *dmem_4_reg_1_hndlr,
        tb_instr_hndlr_t *dmem_8_reg_1_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dreg_1_hndlr,
            init_option, ub_is_sole_reg_shift_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dreg_2_hndlr,
            init_option, ub_is_sole_reg_shift_2, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dreg_4_hndlr,
            init_option, ub_is_sole_reg_shift_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dreg_8_hndlr,
            init_option, ub_is_sole_reg_shift_8, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_1_imm_1_hndlr,
            init_option, ub_is_immed_reg_shift_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_imm_1_hndlr,
            init_option, ub_is_immed_reg_shift_2, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_imm_1_hndlr,
            init_option, ub_is_immed_reg_shift_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_imm_1_hndlr,
            init_option, ub_is_immed_reg_shift_8, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_1_reg_1_hndlr,
            init_option, ub_is_reg_reg_shift_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_reg_1_hndlr,
            init_option, ub_is_reg_reg_shift_2, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_reg_1_hndlr,
            init_option, ub_is_reg_reg_shift_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_reg_1_hndlr,
            init_option, ub_is_reg_reg_shift_8, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dmem_1_hndlr,
            init_option, ub_is_sole_mem_shift_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dmem_2_hndlr,
            init_option, ub_is_sole_mem_shift_2, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dmem_4_hndlr,
            init_option, ub_is_sole_mem_shift_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, sole_dmem_8_hndlr,
            init_option, ub_is_sole_mem_shift_8, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_1_imm_1_hndlr,
            init_option, ub_is_immed_mem_shift_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_2_imm_1_hndlr,
            init_option, ub_is_immed_mem_shift_2, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_4_imm_1_hndlr,
            init_option, ub_is_immed_mem_shift_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_8_imm_1_hndlr,
            init_option, ub_is_immed_mem_shift_8, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_1_reg_1_hndlr,
            init_option, ub_is_mem_reg_shift_1, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_2_reg_1_hndlr,
            init_option, ub_is_mem_reg_shift_2, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_4_reg_1_hndlr,
            init_option, ub_is_mem_reg_shift_4, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_8_reg_1_hndlr,
            init_option, ub_is_mem_reg_shift_8, IB_GUARD_HOOK);
}

void tb_register_srcdst_src_reg(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *dreg_1_smem_1_hndlr,
        tb_instr_hndlr_t *dreg_2_smem_2_hndlr,
        tb_instr_hndlr_t *dreg_4_smem_4_hndlr,
        tb_instr_hndlr_t *dreg_8_smem_8_hndlr,
        tb_instr_hndlr_t *dreg_1_sreg_1_hndlr,
        tb_instr_hndlr_t *dreg_2_sreg_2_hndlr,
        tb_instr_hndlr_t *dreg_4_sreg_4_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_hndlr,
        tb_instr_hndlr_t *dreg_1_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_2_simm_2_hndlr,
        tb_instr_hndlr_t *dreg_4_simm_4_hndlr,
        tb_instr_hndlr_t *dmem_1_sreg_1_hndlr,
        tb_instr_hndlr_t *dmem_2_sreg_2_hndlr,
        tb_instr_hndlr_t *dmem_4_sreg_4_hndlr,
        tb_instr_hndlr_t *dmem_8_sreg_8_hndlr,
        tb_instr_hndlr_t *dmem_1_simm_1_hndlr,
        tb_instr_hndlr_t *dmem_2_simm_2_hndlr,
        tb_instr_hndlr_t *dmem_4_simm_4_hndlr,
        tb_instr_hndlr_t *dreg_2_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_4_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_8_simm_1_hndlr,
        tb_instr_hndlr_t *dmem_2_simm_1_hndlr,
        tb_instr_hndlr_t *dmem_4_simm_1_hndlr,
        tb_instr_hndlr_t *dmem_8_simm_1_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_1_smem_1_hndlr,
            init_option, ub_is_srcdst_src_dreg_1_smem_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_smem_2_hndlr,
            init_option, ub_is_srcdst_src_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_smem_4_hndlr,
            init_option, ub_is_srcdst_src_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_smem_8_hndlr,
            init_option, ub_is_srcdst_src_dreg_8_smem_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_1_sreg_1_hndlr,
            init_option, ub_is_srcdst_src_dreg_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_sreg_2_hndlr,
            init_option, ub_is_srcdst_src_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_sreg_4_hndlr,
            init_option, ub_is_srcdst_src_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_hndlr,
            init_option, ub_is_srcdst_src_dreg_8_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_1_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dreg_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_simm_2_hndlr,
            init_option, ub_is_srcdst_src_dreg_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_simm_4_hndlr,
            init_option, ub_is_srcdst_src_dreg_4_simm_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_1_sreg_1_hndlr,
            init_option, ub_is_srcdst_src_dmem_1_sreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_2_sreg_2_hndlr,
            init_option, ub_is_srcdst_src_dmem_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_4_sreg_4_hndlr,
            init_option, ub_is_srcdst_src_dmem_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_8_sreg_8_hndlr,
            init_option, ub_is_srcdst_src_dmem_8_sreg_8_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_1_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dmem_1_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_2_simm_2_hndlr,
            init_option, ub_is_srcdst_src_dmem_2_simm_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_4_simm_4_hndlr,
            init_option, ub_is_srcdst_src_dmem_4_simm_4_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dreg_2_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dreg_4_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dreg_8_simm_1_instr, IB_GUARD_HOOK);

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_2_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dmem_2_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_4_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dmem_4_simm_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dmem_8_simm_1_hndlr,
            init_option, ub_is_srcdst_src_dmem_8_simm_1_instr, IB_GUARD_HOOK);
}

// Call
void tb_register_call(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *untaint_dmem_4_hndlr,
        tb_instr_hndlr_t *untaint_dmem_8_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, untaint_dmem_4_hndlr,
            init_option, ub_is_dmem_2nd_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, untaint_dmem_8_hndlr,
            init_option, ub_is_dmem_2nd_8_instr, IB_GUARD_HOOK);
}

//Set

void tb_register_set(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *untaint_dreg_1_hndlr,
        tb_instr_hndlr_t *untaint_dmem_1_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, untaint_dreg_1_hndlr,
            init_option, ub_is_dreg_1_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, untaint_dmem_1_hndlr,
            init_option, ub_is_dmem_1_instr, IB_GUARD_HOOK);
}

// CMOV

void tb_register_cmov(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *dreg_2_smem_2_hndlr,
        tb_instr_hndlr_t *dreg_4_smem_4_hndlr,
        tb_instr_hndlr_t *dreg_8_smem_8_hndlr,
        tb_instr_hndlr_t * dreg_2_sreg_2_hndlr,
        tb_instr_hndlr_t * dreg_4_sreg_4_hndlr,
        tb_instr_hndlr_t * dreg_8_sreg_8_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_smem_2_hndlr,
            init_option, ub_is_mov_dreg_2_smem_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_smem_4_hndlr,
            init_option, ub_is_mov_dreg_4_smem_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_smem_8_hndlr,
            init_option, ub_is_mov_dreg_8_smem_8_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_2_sreg_2_hndlr,
            init_option, ub_is_mov_dreg_2_sreg_2_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_4_sreg_4_hndlr,
            init_option, ub_is_mov_dreg_4_sreg_4_instr, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_hndlr,
            init_option, ub_is_mov_dreg_8_sreg_8_instr, IB_GUARD_HOOK);
}

// Instrument SIMD instructions with certain templates.

void tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_context_t *tb_ctx,
        int opcode, IB_INSTRUM_OPT init_option,
        tb_instr_hndlr_t * dreg_8_smem_8_hndlr,
        tb_instr_hndlr_t * dreg_8_sreg_8_hndlr,
        tb_instr_hndlr_t * dreg_16_smem_16_hndlr,
        tb_instr_hndlr_t * dreg_16_sreg_16_hndlr) {


    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_smem_8_hndlr,
            init_option, ub_is_pminmax_dreg_8_smem_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_8_sreg_8_hndlr,
            init_option, ub_is_pminmax_dreg_8_sreg_8, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_16_smem_16_hndlr,
            init_option, ub_is_pminmax_dreg_16_smem_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_16_sreg_16_hndlr,
            init_option, ub_is_pminmax_dreg_16_sreg_16, IB_GUARD_HOOK);
}

void tb_register_pinstr_dreg_sreg_or_smem_16(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t * dreg_16_smem_16_hndlr,
        tb_instr_hndlr_t * dreg_16_sreg_16_hndlr) {

    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_16_smem_16_hndlr,
            init_option, ub_is_pminmax_dreg_16_smem_16, IB_GUARD_HOOK);
    tb_register_hook_instrum_hndlr(tb_ctx, opcode, dreg_16_sreg_16_hndlr,
            init_option, ub_is_pminmax_dreg_16_sreg_16, IB_GUARD_HOOK);
}
