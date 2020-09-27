/*
 * ub_comparison_instr.h
 *
 *  Created on: 2 Jan 2019
 *      Author: john
 */

#ifndef INSTRUCTION_UB_COMPARISON_INSTR_H_
#define INSTRUCTION_UB_COMPARISON_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_comparison_smem_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmp_smem_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_8_smem_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_16_smem_16_instr(instr_t *instr);

/**
 * MEM VS REG
 */

DR_EXPORT bool ub_is_comparison_smem_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmp_smem_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_16_sreg_16_instr(instr_t *instr);

/**
 * REG VS MEM
 */

DR_EXPORT bool ub_is_comparison_sreg_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmp_sreg_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_8_smem_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_16_smem_16_instr(instr_t *instr);

/**
 * REG VS REG
 */

DR_EXPORT bool ub_is_comparison_sreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmp_sreg_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_16_sreg_16_instr(instr_t *instr);

/**
 * REG VS IMM
 */

DR_EXPORT bool ub_is_comparison_sreg_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmp_sreg_1_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_sreg_4_simm_4_instr(instr_t *instr);

/**
 * MEM VS IMM
 */

DR_EXPORT bool ub_is_comparison_smem_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmp_smem_1_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmp_smem_4_simm_4_instr(instr_t *instr);

#endif /* INSTRUCTION_UB_COMPARISON_INSTR_H_ */
