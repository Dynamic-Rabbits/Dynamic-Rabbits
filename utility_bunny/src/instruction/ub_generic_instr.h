/*
 * ub_generic_instr.h
 *
 *  Created on: 7 Jan 2019
 *      Author: john
 */

#ifndef INSTRUCTION_UB_GENERIC_INSTR_H_
#define INSTRUCTION_UB_GENERIC_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_dreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_dmem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_dreg_2nd_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_2nd_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_2nd_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_2nd_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_dreg_2nd_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_dmem_2nd_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_2nd_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_2nd_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_2nd_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_dmem_2nd_16_instr(instr_t *instr);


#endif /* INSTRUCTION_UB_GENERIC_INSTR_H_ */
