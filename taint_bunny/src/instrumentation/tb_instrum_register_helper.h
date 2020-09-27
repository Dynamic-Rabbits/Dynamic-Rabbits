/*
 * tb_instrum_register_healper.h
 *
 *  Created on: 27 Jul 2018
 *      Author: john
 */

#ifndef INSTRUMENTATION_TB_INSTRUM_REGISTER_HEALPER_H_
#define INSTRUMENTATION_TB_INSTRUM_REGISTER_HEALPER_H_

#include "dr_api.h"
#include "drmgr.h"
#include "../tb_bunny_private.h"

void tb_register_hook_instrum_hndlr(tb_context_t *tb_ctx, int opcode,
        tb_instr_hndlr_t * instr_hndlr, IB_INSTRUM_OPT options,
        ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

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
        tb_instr_hndlr_t *dmem_8_reg_1_hndlr);

void tb_register_bs(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *dreg_2_smem_2_hndlr,
        tb_instr_hndlr_t *dreg_4_smem_4_hndlr,
        tb_instr_hndlr_t *dreg_8_smem_8_hndlr,
        tb_instr_hndlr_t *dreg_2_sreg_2_hndlr,
        tb_instr_hndlr_t *dreg_4_sreg_4_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_hndlr);

void tb_register_pshift(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option,
        tb_instr_hndlr_t *dreg_8_sreg_8_sreg_8_hndlr,
        tb_instr_hndlr_t *dreg_16_sreg_16_sreg_16_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_smem_8_hndlr,
        tb_instr_hndlr_t *dreg_16_sreg_16_smem_16_hndlr,
        tb_instr_hndlr_t *dreg_8_sreg_8_simm_1_hndlr,
        tb_instr_hndlr_t *dreg_16_sreg_16_simm_1_hndlr);

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
        tb_instr_hndlr_t *dreg_8_sreg_8_sreg_1_hndlr);

//TODO I never created a function with such a high number of args.. until today. FIX THIS!
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
        tb_instr_hndlr_t *dmem_8_simm_1_hndlr);

void tb_register_call(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *untaint_dmem_4_hndlr,
        tb_instr_hndlr_t *untaint_dmem_8_hndlr);

void tb_register_set(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *untaint_dreg_1_hndlr,
        tb_instr_hndlr_t *untaint_dmem_1_hndlr);

void tb_register_cmov(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t *dreg_2_smem_2_hndlr,
        tb_instr_hndlr_t *dreg_4_smem_4_hndlr,
        tb_instr_hndlr_t *dreg_8_smem_8_hndlr,
        tb_instr_hndlr_t * dreg_2_sreg_2_hndlr,
        tb_instr_hndlr_t * dreg_4_sreg_4_hndlr,
        tb_instr_hndlr_t * dreg_8_sreg_8_hndlr);

void tb_register_pinstr_dreg_sreg_or_smem_8_or_16(tb_context_t *tb_ctx,
        int opcode, IB_INSTRUM_OPT init_option,
        tb_instr_hndlr_t * dreg_8_smem_8_hndlr,
        tb_instr_hndlr_t * dreg_8_sreg_8_hndlr,
        tb_instr_hndlr_t * dreg_16_smem_16_hndlr,
        tb_instr_hndlr_t * dreg_16_sreg_16_hndlr);

void tb_register_pinstr_dreg_sreg_or_smem_16(tb_context_t *tb_ctx, int opcode,
        IB_INSTRUM_OPT init_option, tb_instr_hndlr_t * dreg_16_smem_16_hndlr,
        tb_instr_hndlr_t * dreg_16_sreg_16_hndlr);

#endif /* INSTRUMENTATION_TB_INSTRUM_REGISTER_HEALPER_H_ */
