/*
 * tb_instrum_ptr_arith.h
 *
 *  Created on: 11 May 2018
 *      Author: john
 */

#ifndef INSTRUCTION_UB_PTR_ARITH_INSTR_H_
#define INSTRUCTION_UB_PTR_ARITH_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_lea_dreg_sreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_lea_dreg_2_sreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_dreg_4_sreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_dreg_8_sreg_8_sreg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_lea_base_dreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_lea_base_dreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_base_dreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_base_dreg_8_sreg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_lea_index_dreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_lea_index_dreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_index_dreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_index_dreg_8_sreg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_lea_dreg_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_lea_dreg_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_dreg_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_lea_dreg_8_simm_8_instr(instr_t *instr);



#endif /* INSTRUMENTATION_GUARDS_TB_INSTRUM_PTR_ARITH_H_ */
