/*
 * tb_instrum_xchg_guard.h
 *
 *  Created on: 13 May 2018
 *      Author: john
 */

#ifndef INSTRUCTION_UB_XCHG_INSTR_H_
#define INSTRUCTION_UB_XCHG_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_xchg_reg_reg_instr(instr_t *instr);

DR_EXPORT bool ub_is_xchg_reg_1_reg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_reg_2_reg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_reg_4_reg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_reg_8_reg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_xchg_mem_reg_instr(instr_t *instr);

DR_EXPORT bool ub_is_xchg_mem_1_reg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_mem_2_reg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_mem_4_reg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_mem_8_reg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_xchg_reg_mem_instr(instr_t *instr);

DR_EXPORT bool ub_is_xchg_reg_1_mem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_reg_2_mem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_reg_4_mem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_xchg_reg_8_mem_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmpxchg_sreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmpxchg_sreg_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmpxchg_sreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmpxchg_sreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_instr_cmpxchg_sreg_8_sreg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmpxchg_sreg_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_cmpxchg_sreg_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmpxchg_sreg_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmpxchg_sreg_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_cmpxchg_sreg_8_smem_8_instr(instr_t *instr);



#endif /* INSTRUMENTATION_GUARDS_TB_INSTRUM_XCHG_GUARD_H_ */
