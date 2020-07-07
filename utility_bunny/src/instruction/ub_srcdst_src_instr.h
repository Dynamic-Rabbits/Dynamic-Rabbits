/*
 * tb_instrum_srcdst_src_instr_guard.c
 *
 *  Created on: 11 May 2018
 *      Author: john
 */

#ifndef INSTRUCTION_UB_SRCDST_SRC_INSTR_C_
#define INSTRUCTION_UB_SRCDST_SRC_INSTR_C_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_srcdst_src_dreg_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dreg_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_8_smem_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_16_smem_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dreg_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_16_sreg_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dmem_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dmem_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_16_sreg_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dreg_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dreg_1_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_8_simm_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dmem_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dmem_1_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_8_simm_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dreg_2_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_4_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dreg_8_simm_1_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_dmem_2_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_4_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_dmem_8_simm_1_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_diff_dreg_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_same_dreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_srcdst_src_same_dreg_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_same_dreg_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr_t *instr);

#endif /* INSTRUMENTATION_GUARDS_TB_INSTRUM_srcdst_src_INSTR_GUARD_C_ */
