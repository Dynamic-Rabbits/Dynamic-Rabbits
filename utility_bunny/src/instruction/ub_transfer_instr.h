/*
 * tb_instrum_transfer_guard.h
 *
 *  Created on: 11 May 2018
 *      Author: john
 */

#ifndef INSTRUCTION_UB_TRANSFER_INSTR_H_
#define INSTRUCTION_UB_TRANSFER_INSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

DR_EXPORT bool ub_is_mov_dreg_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dreg_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_16_sreg_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dreg_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dreg_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_8_smem_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_16_smem_16_instr(instr_t *instr);

/* MOVD */

DR_EXPORT bool ub_is_mov_dreg_16_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_16_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_4_sreg_16_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_4_sreg_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dreg_8_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_8_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_4_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_4_sreg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dreg_8_sreg_16_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_8_sreg_16_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_16_smem_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_16_sreg_8_instr(instr_t *instr);


DR_EXPORT bool ub_is_mov_dmem_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dmem_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_8_smem_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_16_smem_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dmem_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dmem_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_8_sreg_8_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_16_sreg_16_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dmem_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dmem_1_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dmem_8_simm_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dreg_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_mov_dreg_1_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_mov_dreg_8_simm_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_push_dmem_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_push_dmem_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_8_smem_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_push_dmem_sreg_instr(instr_t *instr);

DR_EXPORT bool ub_is_push_dmem_1_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_2_sreg_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_4_sreg_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_8_sreg_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_push_dmem_simm_instr(instr_t *instr);

DR_EXPORT bool ub_is_push_dmem_1_simm_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_2_simm_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_4_simm_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_push_dmem_8_simm_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_pop_dreg_smem_instr(instr_t *instr);

DR_EXPORT bool ub_is_pop_dreg_1_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_pop_dreg_2_smem_2_instr(instr_t *instr);
DR_EXPORT bool ub_is_pop_dreg_4_smem_4_instr(instr_t *instr);
DR_EXPORT bool ub_is_pop_dreg_8_smem_8_instr(instr_t *instr);

DR_EXPORT bool ub_is_movzx_dreg_2_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_movzx_dreg_4_sreg_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_movzx_dreg_4_sreg_2_instr(instr_t *instr);

DR_EXPORT bool ub_is_movzx_dreg_2_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_movzx_dreg_4_smem_1_instr(instr_t *instr);
DR_EXPORT bool ub_is_movzx_dreg_4_smem_2_instr(instr_t *instr);

#endif /* INSTRUMENTATION_GUARDS_TB_INSTRUM_TRANSFER_GUARD_H_ */
