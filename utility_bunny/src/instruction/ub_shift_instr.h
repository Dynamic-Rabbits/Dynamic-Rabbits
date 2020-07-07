/*
 * ub_shift_instr.h
 *
 *  Created on: 8 Jan 2019
 *      Author: john
 */

#ifndef INSTRUCTION_UB_SHIFT_INSTR_H_
#define INSTRUCTION_UB_SHIFT_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_sole_mem_shift(instr_t *instr);
DR_EXPORT bool ub_is_sole_mem_shift_1(instr_t *instr);
DR_EXPORT bool ub_is_sole_mem_shift_2(instr_t *instr);
DR_EXPORT bool ub_is_sole_mem_shift_4(instr_t *instr);
DR_EXPORT bool ub_is_sole_mem_shift_8(instr_t *instr);

DR_EXPORT bool ub_is_sole_reg_shift(instr_t *instr);
DR_EXPORT bool ub_is_sole_reg_shift_1(instr_t *instr);
DR_EXPORT bool ub_is_sole_reg_shift_2(instr_t *instr);
DR_EXPORT bool ub_is_sole_reg_shift_4(instr_t *instr);
DR_EXPORT bool ub_is_sole_reg_shift_8(instr_t *instr);

DR_EXPORT bool ub_is_immed_mem_shift(instr_t *instr);
DR_EXPORT bool ub_is_immed_mem_shift_1(instr_t *instr);
DR_EXPORT bool ub_is_immed_mem_shift_2(instr_t *instr);
DR_EXPORT bool ub_is_immed_mem_shift_4(instr_t *instr);
DR_EXPORT bool ub_is_immed_mem_shift_8(instr_t *instr);
DR_EXPORT bool ub_is_immed_mem_shift_16(instr_t *instr);

DR_EXPORT bool ub_is_immed_reg_shift(instr_t *instr);
DR_EXPORT bool ub_is_immed_reg_shift_1(instr_t *instr);
DR_EXPORT bool ub_is_immed_reg_shift_2(instr_t *instr);
DR_EXPORT bool ub_is_immed_reg_shift_4(instr_t *instr);
DR_EXPORT bool ub_is_immed_reg_shift_8(instr_t *instr);
DR_EXPORT bool ub_is_immed_reg_shift_16(instr_t *instr);

DR_EXPORT bool ub_is_mem_reg_shift(instr_t *instr);
DR_EXPORT bool ub_is_mem_reg_shift_1(instr_t *instr);
DR_EXPORT bool ub_is_mem_reg_shift_2(instr_t *instr);
DR_EXPORT bool ub_is_mem_reg_shift_4(instr_t *instr);
DR_EXPORT bool ub_is_mem_reg_shift_8(instr_t *instr);

DR_EXPORT bool ub_is_reg_reg_shift(instr_t *instr);
DR_EXPORT bool ub_is_reg_reg_shift_1(instr_t *instr);
DR_EXPORT bool ub_is_reg_reg_shift_2(instr_t *instr);
DR_EXPORT bool ub_is_reg_reg_shift_4(instr_t *instr);
DR_EXPORT bool ub_is_reg_reg_shift_8(instr_t *instr);

DR_EXPORT bool ub_is_shiftd_dreg_sreg_simm(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dreg_2_sreg_2_simm_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dreg_4_sreg_4_simm_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dreg_8_sreg_8_simm_1(instr_t *instr);

DR_EXPORT bool ub_is_shiftd_dmem_sreg_simm(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dmem_2_sreg_2_simm_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dmem_4_sreg_4_simm_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dmem_8_sreg_8_simm_1(instr_t *instr);

DR_EXPORT bool ub_is_shiftd_dreg_sreg_sreg(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dreg_2_sreg_2_sreg_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dreg_4_sreg_4_sreg_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dreg_8_sreg_8_sreg_1(instr_t *instr);

DR_EXPORT bool ub_is_shiftd_dmem_sreg_sreg(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dmem_2_sreg_2_sreg_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dmem_4_sreg_4_sreg_1(instr_t *instr);
DR_EXPORT bool ub_is_shiftd_dmem_8_sreg_8_sreg_1(instr_t *instr);

DR_EXPORT bool ub_is_reg_pshift_8(instr_t *instr);
DR_EXPORT bool ub_is_reg_pshift_16(instr_t *instr);

DR_EXPORT bool ub_is_mem_pshift_8(instr_t *instr);
DR_EXPORT bool ub_is_mem_pshift_16(instr_t *instr);


#endif /* INSTRUCTION_UB_SHIFT_INSTR_H_ */
