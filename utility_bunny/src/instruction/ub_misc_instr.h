/*
 * ub_misc_instr.h
 *
 *  Created on: 8 Jan 2019
 *      Author: john
 */

#ifndef INSTRUCTION_UB_MISC_INSTR_H_
#define INSTRUCTION_UB_MISC_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_leave_dreg_4_dreg_4_sreg_4_smem_4_instr(instr_t *instr);

DR_EXPORT bool ub_is_leave_dreg_8_dreg_8_sreg_8_smem_8_instr(instr_t *instr);

#endif /* INSTRUCTION_UB_MISC_INSTR_H_ */
