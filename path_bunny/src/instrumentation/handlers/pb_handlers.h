/*
 * pb_handlers.h
 *
 *  Created on: 5 Aug 2018
 *      Author: john
 */

#ifndef SRC_INSTRUMENTATION_HANDLERS_PB_HANDLERS_H_
#define SRC_INSTRUMENTATION_HANDLERS_PB_HANDLERS_H_

#include "dr_defines.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"

/**
 * REG VS IMM
 */

void pb_instrument_sreg_1_simm_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_2_simm_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_4_simm_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_8_simm_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);


/**
 * MEM VS IMM
 */

void pb_instrument_smem_1_simm_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_2_simm_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_4_simm_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_8_simm_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);

/**
 * REG VS REG
 */

void pb_instrument_sreg_1_sreg_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_2_sreg_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_4_sreg_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_8_sreg_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_16_sreg_16_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);

/**
 * REP
 */

void pb_instrument_rep_cmp_smem_1_smem_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_rep_cmp_smem_2_smem_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_rep_cmp_smem_4_smem_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_rep_cmp_smem_8_smem_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);

void pb_instrument_rep_scas_smem_1_smem_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_rep_scas_smem_2_smem_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_rep_scas_smem_4_smem_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_rep_scas_smem_8_smem_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);

/**
 * MEM VS MEM
 */

void pb_instrument_smem_1_smem_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_2_smem_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_4_smem_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_8_smem_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);

/**
 * MEM VS REG
 */

void pb_instrument_smem_1_sreg_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_2_sreg_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_4_sreg_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_8_sreg_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_smem_16_sreg_16_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);

/**
 * REG VS MEM
 */

void pb_instrument_sreg_1_smem_1_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_2_smem_2_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_4_smem_4_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_8_smem_8_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);
void pb_instrument_sreg_16_smem_16_check(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *user_data, void *spill_data);

#endif /* SRC_INSTRUMENTATION_HANDLERS_PB_HANDLERS_H_ */
