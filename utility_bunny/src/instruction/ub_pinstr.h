/*
 * ub_pinstr.h
 *
 *  Created on: 8 Jan 2019
 *      Author: john
 */

#ifndef INSTRUCTION_UB_PINSTR_H_
#define INSTRUCTION_UB_PINSTR_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

/**
 * PEXT
 */

DR_EXPORT bool ub_is_pext_dreg_sreg_sreg(instr_t *instr);
DR_EXPORT bool ub_is_pext_dreg_4_sreg_4_sreg_4(instr_t *instr);
DR_EXPORT bool ub_is_pext_dreg_8_sreg_8_sreg_8(instr_t *instr);

DR_EXPORT bool ub_is_pext_dreg_sreg_smem(instr_t *instr);
DR_EXPORT bool ub_is_pext_dreg_4_sreg_4_smem_4(instr_t *instr);
DR_EXPORT bool ub_is_pext_dreg_8_sreg_8_smem_8(instr_t *instr);

DR_EXPORT bool ub_is_pextr_dmem_1_sreg_16(instr_t *instr);
DR_EXPORT bool ub_is_pextr_dmem_2_sreg_16(instr_t *instr);
DR_EXPORT bool ub_is_pextr_dmem_4_sreg_16(instr_t *instr);

DR_EXPORT bool ub_is_pextr_dreg_4_sreg_16(instr_t *instr);
DR_EXPORT bool ub_is_pextr_dreg_4_sreg_8(instr_t *instr);

/**
 * PMINMAXU
 */

DR_EXPORT bool ub_is_pminmax_dreg_smem(instr_t *instr);
DR_EXPORT bool ub_is_pminmax_dreg_sreg(instr_t *instr);

DR_EXPORT bool ub_is_pminmax_dreg_8_sreg_8(instr_t *instr);
DR_EXPORT bool ub_is_pminmax_dreg_8_smem_8(instr_t *instr);

DR_EXPORT bool ub_is_pminmax_dreg_16_sreg_16(instr_t *instr);
DR_EXPORT bool ub_is_pminmax_dreg_16_smem_16(instr_t *instr);

/**
 * PMOVMSK
 */

DR_EXPORT bool ub_is_pmovmsk_dreg_4_sreg_8(instr_t *instr);
DR_EXPORT bool ub_is_pmovmsk_dreg_4_sreg_16(instr_t *instr);

DR_EXPORT bool ub_is_pmovmsk_dreg_8_sreg_8(instr_t *instr);
DR_EXPORT bool ub_is_pmovmsk_dreg_8_sreg_16(instr_t *instr);

/**
 * PACKSS
 */

DR_EXPORT bool ub_is_packss_dreg_8_sreg_8(instr_t *instr);

DR_EXPORT bool ub_is_packss_dreg_16_sreg_16(instr_t *instr);

DR_EXPORT bool ub_is_packss_dreg_8_smem_8(instr_t *instr);

DR_EXPORT bool ub_is_packss_dreg_16_smem_16(instr_t *instr);

/**
 * PALIGNR
 */

DR_EXPORT bool ub_is_palignr_dreg_8_sreg_8(instr_t *instr);
DR_EXPORT bool ub_is_palignr_dreg_8_smem_8(instr_t *instr);

DR_EXPORT bool ub_is_palignr_dreg_16_sreg_16(instr_t *instr);
DR_EXPORT bool ub_is_palignr_dreg_16_smem_16(instr_t *instr);

/**
 * PSHUFH/D
 */

DR_EXPORT bool ub_is_pshuf_dreg_8_sreg_8(instr_t *instr);
DR_EXPORT bool ub_is_pshuf_dreg_16_sreg_16(instr_t *instr);

DR_EXPORT bool ub_is_pshuf_dreg_8_smem_8(instr_t *instr);
DR_EXPORT bool ub_is_pshuf_dreg_16_smem_16(instr_t *instr);

/**
 * PUNPCK
 */

DR_EXPORT bool ub_is_punpck_dreg_8_sreg_8(instr_t *instr);
DR_EXPORT bool ub_is_punpck_dreg_16_sreg_16(instr_t *instr);

DR_EXPORT bool ub_is_punpck_dreg_8_smem_8(instr_t *instr);
DR_EXPORT bool ub_is_punpck_dreg_16_smem_16(instr_t *instr);

/**
 * PCMP
 */

DR_EXPORT bool ub_is_pcmp_dreg_8_sreg_8(instr_t *instr);
DR_EXPORT bool ub_is_pcmp_dreg_16_sreg_16(instr_t *instr);

DR_EXPORT bool ub_is_pcmp_dreg_8_smem_8(instr_t *instr);
DR_EXPORT bool ub_is_pcmp_dreg_16_smem_16(instr_t *instr);

#endif /* INSTRUCTION_UB_PINSTR_H_ */
