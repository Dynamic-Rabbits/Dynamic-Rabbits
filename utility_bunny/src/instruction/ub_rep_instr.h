/*
 * tb_instrum_rep_guard.h
 *
 *  Created on: 11 May 2018
 *      Author: john
 */

#ifndef INSTRUCTION_UB_REP_INSTR_H_
#define INSTRUCTION_UB_REP_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_rep_movs_instr(instr_t *instr);

DR_EXPORT bool ub_is_rep_movsb_instr(instr_t *instr);
DR_EXPORT bool ub_is_rep_movsw_instr(instr_t *instr);
DR_EXPORT bool ub_is_rep_movsd_instr(instr_t *instr);
DR_EXPORT bool ub_is_rep_movsq_instr(instr_t *instr);

DR_EXPORT bool ub_is_rep_stos_instr(instr_t *instr);

DR_EXPORT bool ub_is_rep_stosb_instr(instr_t *instr);
DR_EXPORT bool ub_is_rep_stosw_instr(instr_t *instr);
DR_EXPORT bool ub_is_rep_stosd_instr(instr_t *instr);
DR_EXPORT bool ub_is_rep_stosq_instr(instr_t *instr);

#endif /* INSTRUMENTATION_GUARDS_TB_INSTRUM_REP_GUARD_H_ */
