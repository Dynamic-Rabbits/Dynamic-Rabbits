/*
 * ub_dataflow_analysis.h
 *
 *  Created on: 13 Dec 2018
 *      Author: john
 */

#ifndef DATAFLOW_UB_DATAFLOW_ANALYSIS_H_
#define DATAFLOW_UB_DATAFLOW_ANALYSIS_H_

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include  <stdint.h>

void *ub_create_dataflow_analysis();

void ub_destroy_dataflow_analysis(void *taint_state_opaque);

bool ub_dataflow_is_opnd_tainted(opnd_t *patched_opnd, void *taint_state);

void ub_dataflow_mark_reg_tainted(reg_id_t reg_id, void *taint_state,
		bool is_tainted);

bool ub_dataflow_mark_mem_tainted(opnd_t *patched_ref_opnd, void *taint_state,
		bool is_tainted);

void ub_dataflow_mark_opnd_tainted(opnd_t *patched_opnd, void *taint_state,
		bool is_tainted);

bool ub_dataflow_is_any_instr_src_tainted(instr_t *instr, void *taint_state);

bool ub_dataflow_is_all_instr_src_tainted(instr_t *instr, void *taint_state);

bool ub_dataflow_is_any_instr_dst_tainted(instr_t *instr, void *taint_state);

bool ub_dataflow_is_all_instr_dst_tainted(instr_t *instr, void *taint_state);

bool ub_dataflow_is_instr_tainted(instr_t *instr, void *taint_state);

void ub_dataflow_propagate(instr_t *instr, void *taint_state);

#endif /* DATAFLOW_UB_DATAFLOW_ANALYSIS_H_ */
