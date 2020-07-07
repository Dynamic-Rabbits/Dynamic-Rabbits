/*
 * ub_call_instr.h
 *
 *  Created on: 2 Jan 2019
 *      Author: john
 */

#ifndef INSTRUCTION_UB_CALL_INSTR_H_
#define INSTRUCTION_UB_CALL_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_ret_instr(instr_t *instr);
DR_EXPORT bool ub_is_ret_imm_instr(instr_t *instr);

DR_EXPORT bool ub_is_cti_mem_instr(instr_t *instr);
DR_EXPORT bool ub_is_cti_reg_instr(instr_t *instr);

#endif /* INSTRUCTION_UB_CALL_INSTR_H_ */
