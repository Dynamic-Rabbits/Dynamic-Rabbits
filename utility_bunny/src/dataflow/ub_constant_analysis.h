/*
 * ub_mod_analysis.h
 *
 *  Created on: 9 Dec 2018
 *      Author: john
 */

#ifndef DATAFLOW_UB_CONSTANT_ANALYSIS_H_
#define DATAFLOW_UB_CONSTANT_ANALYSIS_H_

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include  <stdint.h>

typedef struct {

    bool modified;
    int emulated_disp; /* Calculated via simple constant folding */
} ub_constant_info_t;

typedef struct {

    ub_constant_info_t reg_constant_data[DR_NUM_GPR_REGS];
} ub_constant_state_t;

/**
 * Via result
 */

typedef void * ub_constant_analysis_t;

ub_constant_analysis_t ub_constant_analysis_result(instrlist_t *bb);

void ub_constant_analysis_destroy_result(
        ub_constant_analysis_t constant_analysis);

bool ub_constant_analysis_instr_uses_mod_addr_regs_via_result(
        ub_constant_analysis_t constant_analysis, instr_t *instr,
        uint instr_index);

bool ub_constant_analysis_is_reg_constant_via_result(ub_constant_analysis_t constant_analysis,
        uint instr_index, reg_id_t reg_id, int *disp);

bool ub_constant_analysis_patch_addr_via_result(ub_constant_analysis_t constant_analysis,
        opnd_t *mem_opnd, uint instr_index);

/**
 * On point
 *
 * Useful to avoid heavy mem allocs.
 */

void ub_constant_analysis_init(ub_constant_state_t *state);

void ub_constant_analysis_update(ub_constant_state_t *state, instr_t *instr);

bool ub_constant_analysis_instr_uses_mod_addr_regs(
        ub_constant_state_t *state, instr_t *instr);

bool ub_constant_analysis_is_reg_constant(ub_constant_state_t *state,
        reg_id_t reg_id, int *disp);

bool ub_constant_analysis_patch_addr(ub_constant_state_t *state, opnd_t *mem_opnd);

/**
 * Other helpers
 */

bool ub_constant_analysis_get_index_at_modified(instrlist_t *bb, uint *index);

#endif /* DATAFLOW_UB_CONSTANT_ANALYSIS_H_ */
