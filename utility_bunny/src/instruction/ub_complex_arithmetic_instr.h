/*
 * tb_instrum_register_arithmetic.h
 *
 *  Created on: 11 May 2018
 *      Author: john
 */

#ifndef INSTRUCTION_UB_ARITHMETIC_INSTR_H_
#define INSTRUCTION_UB_ARITHMETIC_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

/*********************************************************
 * MUL 4 Instruction
 */

DR_EXPORT bool ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr_t *instr);

/*********************************************************
 * MUL 1 Instruction
 */

DR_EXPORT bool ub_is_mult_dreg_2_sreg_1_sreg_1(instr_t *instr);
DR_EXPORT bool ub_is_mult_dreg_2_smem_1_sreg_1(instr_t *instr);

/*********************************************************
 * IMUL Instruction
 */

DR_EXPORT bool ub_is_mult_dreg_sreg_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mult_dreg_8_sreg_8_simm_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_mult_dreg_smem_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_mult_dreg_2_smem_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mult_dreg_4_smem_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mult_dreg_8_smem_8_simm_8_instr(instr_t *instr);

/*********************************************************
 * DIV 4 Instruction
 */

DR_EXPORT bool ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr(
        instr_t *instr);
DR_EXPORT bool ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(
        instr_t *instr);

/*********************************************************
 * DIV 1 Instruction
 */

DR_EXPORT bool ub_is_div_dreg_dreg_smem_sreg_instr(instr_t *instr);
DR_EXPORT bool ub_is_div_dreg_dreg_sreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr(instr_t *instr);

#endif /* INSTRUMENTATION_GUARDS_TB_INSTRUM_REGISTER_ARITHMETIC_H_ */
