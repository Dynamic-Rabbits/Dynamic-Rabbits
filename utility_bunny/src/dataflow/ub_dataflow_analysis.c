/*
 * ub_dataflow_analysis.c
 *
 *      Author: john
 */

#include "ub_dataflow_analysis.h"
#include "ub_instr_flows.h"
#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include  <stdint.h>
#include "drvector.h"
#include "ub_constant_analysis.h"
#include <string.h>
#include "../datastructs/lists/ub_list.h"
#include "../register/ub_register.h"

/**
 * TODO: Re-implement data-flow analysis for clarity.
 */

#define UB_DF_MAX_REG DR_REG_YMM15 + 1

typedef struct {
	bool tainted;
	bool was_untainted;
	int start;
	int end;
} ub_dataflow_mem_range_t;

typedef struct {
	reg_id_t base_reg;
	void *range_list;
} ub_dataflow_mem_base_state_t;

typedef struct {
	ub_dataflow_mem_range_t mem_range;
	opnd_t mem_opnd;
} ub_dataflow_mem_non_base_state_t;

typedef struct {

	/* Determines of operand state */
	bool is_base_type;
	union {
		ub_dataflow_mem_base_state_t base_opnd_state;
		ub_dataflow_mem_non_base_state_t non_base_opnd_state;
	} mem_opnd_state;
} ub_dataflow_mem_opnd_state_t;

typedef struct {
	/* Flags per register */
	bool reg_taint[UB_DF_MAX_REG];
	/* Flags for memory */
	void *mem_opnd_list;
	/* To follow disp values */
	ub_constant_state_t constant_state;
} ub_dataflow_state_t;

/***************************************************************
 * Helper Function
 */

/**
 * Returns whether or not the operand is strictly a base + disp
 * operand
 *
 * The base register is sent out.
 *
 * It is useful, to identify whether memory access ranges can be compared.
 */
static bool ub_dataflow_is_opnd_strictly_base_disp(opnd_t *opnd,
		reg_id_t *base_reg) {

	DR_ASSERT(opnd_is_memory_reference(*opnd));
	DR_ASSERT(base_reg != NULL);

	reg_id_t reg = opnd_get_base(*opnd);

	/* Index register must be NULL because we are concerned with base and disp only */
	if (reg != DR_REG_NULL && opnd_get_index(*opnd) == DR_REG_NULL) {
		*base_reg = reg;
		return true;
	}

	*base_reg = DR_REG_NULL;
	return false;
}

/**
 * Returns whether a register is tainted.
 */
static bool ub_dataflow_is_reg_tainted(ub_dataflow_state_t *taint_state,
		reg_id_t reg_id) {

	DR_ASSERT((reg_id < UB_DF_MAX_REG));

	if (reg_is_gpr(reg_id)) {
		reg_id_t reg_id_ptr = reg_resize_to_opsz(reg_id, OPSZ_PTR);
		DR_ASSERT(reg_id_ptr != DR_REG_NULL);
		reg_id = reg_id_ptr;
	}

	return taint_state->reg_taint[reg_id];
}

static bool ub_dataflow_is_range_intersected(ub_dataflow_mem_range_t *range,
		int start, int end) {

	return ((range->start <= start && start < range->end)
			|| (range->start <= end - 1 && end - 1 < range->end));
}

static void ub_dataflow_insert_new_range(void *range_list, int start, int end,
		bool is_tainted) {

	ub_dataflow_mem_range_t *new_range = dr_global_alloc(
			sizeof(ub_dataflow_mem_range_t));
	new_range->start = start;
	new_range->end = end;
	new_range->tainted = is_tainted;
	new_range->was_untainted = false;
	ub_list_insert(range_list, new_range);
}

bool ub_dataflow_is_opnd_tainted(opnd_t *patched_opnd, void *taint_state_opaque) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	if (ub_opnd_is_reg(patched_opnd)) {

		/* Simply get register id and check if it is tainted */
		reg_id_t reg_id = opnd_get_reg(*patched_opnd);
		return ub_dataflow_is_reg_tainted(taint_state, reg_id);

	} else if (opnd_is_memory_reference(*patched_opnd)) {

		reg_id_t base_reg = DR_REG_NULL;
		int start = 0;
		int end = 0;

		/* Check if operand is base + disp and fetch base register */
		bool is_base = ub_dataflow_is_opnd_strictly_base_disp(patched_opnd,
				&base_reg);

		start = opnd_get_disp(*patched_opnd);
		opnd_size_t opsize = opnd_get_size(*patched_opnd);
		end = start + opnd_size_in_bytes(opsize);

		for (void * it = ub_list_get_start_it(taint_state->mem_opnd_list); it;
				it = ub_list_get_next_it(it)) {

			ub_dataflow_mem_opnd_state_t *mem_opnd_state =
					(ub_dataflow_mem_opnd_state_t *) ub_list_get_it_value(it);

			if (mem_opnd_state->is_base_type && is_base) {

				ub_dataflow_mem_base_state_t *base_state =
						&(mem_opnd_state->mem_opnd_state.base_opnd_state);

				/* Check if the base is the same */
				if (base_reg == base_state->base_reg) {

					for (void * range_it = ub_list_get_start_it(
							base_state->range_list); range_it; range_it =
							ub_list_get_next_it(range_it)) {

						ub_dataflow_mem_range_t *range =
								(ub_dataflow_mem_range_t *) ub_list_get_it_value(
										range_it);

						/**
						 * Check if the range intersect, and if it does, return the range's taint
						 * status
						 */
						if (ub_dataflow_is_range_intersected(range, start, end))
							return range->tainted;
					}
				}
			} else if (!is_base) {

				ub_dataflow_mem_non_base_state_t non_base_state =
						mem_opnd_state->mem_opnd_state.non_base_opnd_state;

				if (opnd_same_address(*patched_opnd, non_base_state.mem_opnd)) {

					ub_dataflow_mem_range_t *range = &non_base_state.mem_range;

					/**
					 * Check if the range intersect, and if it does, return the range's taint
					 * status
					 */
					if (ub_dataflow_is_range_intersected(range, start, end))
						return range->tainted;

				}
			}
		}
	}

	return false;
}

static void ub_dataflow_mark_reg_tainted_priv(reg_id_t reg_id,
		void *taint_state_opaque, bool is_tainted, bool is_xmm_partial) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	/* We are only partially untainting a register, we ignore the marking. */
	if (!is_tainted
			&& ((reg_is_gpr(reg_id) && !reg_is_pointer_sized(reg_id))
					|| is_xmm_partial))
		return;

	if ((reg_id < UB_DF_MAX_REG))
		taint_state->reg_taint[reg_id] = is_tainted;
}

void ub_dataflow_mark_reg_tainted(reg_id_t reg_id, void *taint_state_opaque,
		bool is_tainted) {

	/* TODO: need to be more precise in the future when we consider ymm and ZMM */
	ub_dataflow_mark_reg_tainted_priv(reg_id, taint_state_opaque, is_tainted,
	false);
}

static bool ub_taint_range(ub_dataflow_mem_range_t *range, int start, int end,
		bool is_tainted, bool *taint_changed) {

	if (ub_dataflow_is_range_intersected(range, start, end)) {

		bool encapsulates_entire_range = (range->start == start)
				&& (range->end == end);

		if (taint_changed != NULL)
			*taint_changed = is_tainted && !range->tainted;

		range->was_untainted = !is_tainted && range->tainted;

		if (!encapsulates_entire_range) {
			if (range->start > start)
				range->start = start;

			if (range->end < end)
				range->end = end;

			range->tainted |= is_tainted;
		} else {
			range->tainted = is_tainted;
		}

		return true;
	}

	return false;
}

static bool ub_dataflow_mark_mem_tainted_priv(opnd_t *patched_mem_ref_opnd,
		void *taint_state_opaque, bool is_tainted, bool *taint_changed) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	reg_id_t base_reg = DR_REG_NULL;
	int start = 0;
	int end = 0;

	/* Check if memory operand is strictly base + disp */
	bool is_base = ub_dataflow_is_opnd_strictly_base_disp(patched_mem_ref_opnd,
			&base_reg);

	start = opnd_get_disp(*patched_mem_ref_opnd);
	opnd_size_t opsize = opnd_get_size(*patched_mem_ref_opnd);
	end = start + opnd_size_in_bytes(opsize);

	if (is_base) {
		for (void * it = ub_list_get_start_it(taint_state->mem_opnd_list); it;
				it = ub_list_get_next_it(it)) {

			ub_dataflow_mem_opnd_state_t *mem_opnd_state =
					(ub_dataflow_mem_opnd_state_t *) ub_list_get_it_value(it);

			if (mem_opnd_state->is_base_type) {

				ub_dataflow_mem_base_state_t *base_state =
						&(mem_opnd_state->mem_opnd_state.base_opnd_state);

				if (base_state->base_reg == base_reg) {

					for (void * range_it = ub_list_get_start_it(
							base_state->range_list); range_it; range_it =
							ub_list_get_next_it(range_it)) {

						ub_dataflow_mem_range_t *range =
								(ub_dataflow_mem_range_t *) ub_list_get_it_value(
										range_it);

						if (ub_taint_range(range, start, end, is_tainted,
								taint_changed))
							return false;

					}

					if (taint_changed != NULL)
						*taint_changed = is_tainted;

					ub_dataflow_insert_new_range(base_state->range_list, start,
							end, is_tainted);
					return true;
				}
			}
		}

		if (taint_changed != NULL)
			*taint_changed = is_tainted;

		void *new_range_list = ub_list_create();
		ub_dataflow_insert_new_range(new_range_list, start, end, is_tainted);

		ub_dataflow_mem_opnd_state_t *mem_opnd_state = dr_global_alloc(
				sizeof(ub_dataflow_mem_opnd_state_t));
		mem_opnd_state->is_base_type = true;
		mem_opnd_state->mem_opnd_state.base_opnd_state.base_reg = base_reg;
		mem_opnd_state->mem_opnd_state.base_opnd_state.range_list =
				new_range_list;
		ub_list_insert(taint_state->mem_opnd_list, mem_opnd_state);
		return true;

	} else {
		for (void * it = ub_list_get_start_it(taint_state->mem_opnd_list); it;
				it = ub_list_get_next_it(it)) {

			ub_dataflow_mem_opnd_state_t *mem_opnd_state =
					(ub_dataflow_mem_opnd_state_t *) ub_list_get_it_value(it);

			if (!mem_opnd_state->is_base_type) {

				ub_dataflow_mem_non_base_state_t *non_base_state;
				non_base_state =
						&mem_opnd_state->mem_opnd_state.non_base_opnd_state;

				if (opnd_same_address(non_base_state->mem_opnd,
						*patched_mem_ref_opnd)) {

					if (ub_taint_range(&(non_base_state->mem_range), start, end,
							is_tainted, taint_changed))
						return false;
				}
			}
		}

		ub_dataflow_mem_opnd_state_t *mem_opnd_state = dr_global_alloc(
				sizeof(ub_dataflow_mem_opnd_state_t));
		mem_opnd_state->is_base_type = false;
		mem_opnd_state->mem_opnd_state.non_base_opnd_state.mem_opnd =
				*patched_mem_ref_opnd;
		mem_opnd_state->mem_opnd_state.non_base_opnd_state.mem_range.start =
				start;
		mem_opnd_state->mem_opnd_state.non_base_opnd_state.mem_range.end = end;
		mem_opnd_state->mem_opnd_state.non_base_opnd_state.mem_range.tainted =
				is_tainted;
		mem_opnd_state->mem_opnd_state.non_base_opnd_state.mem_range.was_untainted =
		false;
		ub_list_insert(taint_state->mem_opnd_list, mem_opnd_state);

		if (taint_changed != NULL)
			*taint_changed = is_tainted;

		return true;
	}
}

bool ub_dataflow_mark_mem_tainted(opnd_t *patched_mem_ref_opnd,
		void *taint_state_opaque, bool is_tainted) {

	return ub_dataflow_mark_mem_tainted_priv(patched_mem_ref_opnd,
			taint_state_opaque, is_tainted, NULL);
}

void ub_dataflow_mark_opnd_tainted(opnd_t *patched_opnd,
		void *taint_state_opaque, bool is_tainted) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	if (ub_opnd_is_reg(patched_opnd)) {
		reg_id_t reg_id = opnd_get_reg(*patched_opnd);
		ub_dataflow_mark_reg_tainted(reg_id, taint_state, is_tainted);

	} else if (opnd_is_memory_reference(*patched_opnd)) {
		/* Assumed opnd is patched */
		ub_dataflow_mark_mem_tainted(patched_opnd, taint_state, is_tainted);
	}
}

static void ub_dataflow_taint_others(opnd_t *opnd,
		ub_dataflow_state_t *taint_state, bool only_marked) {

	reg_id_t base_reg = DR_REG_NULL;
	bool is_base = ub_dataflow_is_opnd_strictly_base_disp(opnd, &base_reg);

	for (void * it = ub_list_get_start_it(taint_state->mem_opnd_list); it; it =
			ub_list_get_next_it(it)) {

		ub_dataflow_mem_opnd_state_t *mem_opnd_state =
				(ub_dataflow_mem_opnd_state_t *) ub_list_get_it_value(it);

		if (mem_opnd_state->is_base_type) {

			ub_dataflow_mem_base_state_t *base_state =
					&(mem_opnd_state->mem_opnd_state.base_opnd_state);

			if (is_base && base_state->base_reg == base_reg)
				continue;

			for (void * range_it = ub_list_get_start_it(base_state->range_list);
					range_it; range_it = ub_list_get_next_it(range_it)) {

				ub_dataflow_mem_range_t *range =
						(ub_dataflow_mem_range_t *) ub_list_get_it_value(
								range_it);

				if (!only_marked || (only_marked && range->was_untainted))
					range->tainted = true;
			}

		} else {
			ub_dataflow_mem_non_base_state_t *non_base_state =
					&(mem_opnd_state->mem_opnd_state.non_base_opnd_state);

			if (opnd_same_address(non_base_state->mem_opnd, *opnd))
				continue;

			if (!only_marked || (only_marked && non_base_state->mem_range.was_untainted))
				non_base_state->mem_range.tainted = true;
		}
	}
}

static void ub_dataflow_taint_all_mem(ub_dataflow_state_t *taint_state) {

	for (void * it = ub_list_get_start_it(taint_state->mem_opnd_list); it; it =
			ub_list_get_next_it(it)) {

		ub_dataflow_mem_opnd_state_t *mem_opnd_state =
				(ub_dataflow_mem_opnd_state_t *) ub_list_get_it_value(it);

		if (mem_opnd_state->is_base_type) {

			ub_dataflow_mem_base_state_t *base_state =
					&(mem_opnd_state->mem_opnd_state.base_opnd_state);

			for (void * range_it = ub_list_get_start_it(base_state->range_list);
					range_it; range_it = ub_list_get_next_it(range_it)) {

				ub_dataflow_mem_range_t *range =
						(ub_dataflow_mem_range_t *) ub_list_get_it_value(
								range_it);

				range->tainted = true;
			}

		} else {
			ub_dataflow_mem_non_base_state_t *non_base_state =
					&(mem_opnd_state->mem_opnd_state.non_base_opnd_state);

			non_base_state->mem_range.tainted = true;
		}
	}
}

static void ub_dataflow_handle_propagation(instr_t * instr, opnd_t *opnd,
		ub_dataflow_state_t *taint_state, bool is_tainted,
		bool is_xmm_partial_reg) {

	if (ub_opnd_is_reg(opnd)) {
		reg_id_t reg_id = opnd_get_reg(*opnd);
		ub_dataflow_mark_reg_tainted_priv(reg_id, taint_state, is_tainted,
				is_xmm_partial_reg);

	} else if (opnd_is_memory_reference(*opnd)) {
		bool taint_change = false;

		bool new_abstract = ub_dataflow_mark_mem_tainted_priv(opnd, taint_state,
				is_tainted, &taint_change);

//      Debug:
//        if (new_abstract) {
//            instr_disassemble(dr_get_current_drcontext(), instr, STDERR);
//            dr_fprintf(STDERR, "\n");
//
//            opnd_disassemble(dr_get_current_drcontext(), *opnd, STDERR);
//            dr_fprintf(STDERR, "\n");
//
//            dr_fprintf(STDERR, "List: \n");
//
//            for (void * it = ub_list_get_start_it(taint_state->mem_opnd_list);
//                    it; it = ub_list_get_next_it(it)) {
//
//                ub_dataflow_mem_opnd_state_t *mem_opnd_state =
//                        (ub_dataflow_mem_opnd_state_t *) ub_list_get_it_value(
//                                it);
//
//                if (!mem_opnd_state->is_base_type) {
//
//                    opnd_disassemble(dr_get_current_drcontext(),
//                            mem_opnd_state->mem_opnd_state.non_base_opnd_state.mem_opnd,
//                            STDERR);
//                    dr_fprintf(STDERR, "\n");
//                }
//            }
//        }

		DR_ASSERT(!new_abstract);

		if (taint_change) {
			ub_dataflow_taint_others(opnd, taint_state, false);
		} else if (is_tainted) {
			ub_dataflow_taint_others(opnd, taint_state, true);
		}
	}
}

/**
 * TODO: dataflow_is_any and dataflow_is_all mostly make use of the same code.
 * Any ideas to reduce this code?
 */

bool ub_dataflow_is_any_instr_src_tainted(instr_t *instr,
		void *taint_state_opaque) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	/* Special case. We do not check (possibly large) memory. */
	if (instr_get_opcode(instr) == OP_rep_movs
			|| instr_get_opcode(instr) == OP_rep_stos) {
		return true;
	}

	ub_instr_dataflow_t instr_dataflow;
	ub_dataflow_get_info(instr, &instr_dataflow);

	size_t num_flows = ub_dataflow_num_flows(&instr_dataflow);
	for (size_t i = 0; i < num_flows; i++) {

		// Firstly, check srcs
		size_t num_srcs = ub_dataflow_flow_num_srcs(&instr_dataflow, i);
		for (size_t j = 0; j < num_srcs; j++) {

			opnd_t src_opnd = ub_dataflow_get_flow_src(instr, &instr_dataflow,
					i, j);
			ub_constant_analysis_patch_addr(&(taint_state->constant_state),
					&src_opnd);

			if (ub_dataflow_is_opnd_tainted(&src_opnd, taint_state))
				return true;
		}
	}

	return false;
}

bool ub_dataflow_is_all_instr_src_tainted(instr_t *instr,
		void *taint_state_opaque) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	/* Special case. We do not check (possibly large) memory. */
	if (instr_get_opcode(instr) == OP_rep_movs
			|| instr_get_opcode(instr) == OP_rep_stos) {
		return true;
	}

	ub_instr_dataflow_t instr_dataflow;
	ub_dataflow_get_info(instr, &instr_dataflow);

	size_t num_flows = ub_dataflow_num_flows(&instr_dataflow);
	for (size_t i = 0; i < num_flows; i++) {

		// Firstly, check srcs
		size_t num_srcs = ub_dataflow_flow_num_srcs(&instr_dataflow, i);
		for (size_t j = 0; j < num_srcs; j++) {

			opnd_t src_opnd = ub_dataflow_get_flow_src(instr, &instr_dataflow,
					i, j);
			ub_constant_analysis_patch_addr(&(taint_state->constant_state),
					&src_opnd);

			if (!ub_dataflow_is_opnd_tainted(&src_opnd, taint_state))
				return false;
		}
	}

	return true;
}

bool ub_dataflow_is_any_instr_dst_tainted(instr_t *instr,
		void *taint_state_opaque) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	/* Special case. We do not check (possibly large) memory. */
	if (instr_get_opcode(instr) == OP_rep_movs
			|| instr_get_opcode(instr) == OP_rep_stos) {
		return true;
	}

	ub_instr_dataflow_t instr_dataflow;
	ub_dataflow_get_info(instr, &instr_dataflow);

	size_t num_flows = ub_dataflow_num_flows(&instr_dataflow);

	for (size_t i = 0; i < num_flows; i++) {

		opnd_t dst_opnd = ub_dataflow_get_flow_dst(instr, &instr_dataflow, i);
		ub_constant_analysis_patch_addr(&(taint_state->constant_state),
				&dst_opnd);

		if (ub_dataflow_is_opnd_tainted(&dst_opnd, taint_state))
			return true;
	}

	return false;
}

bool ub_dataflow_is_all_instr_dst_tainted(instr_t *instr,
		void *taint_state_opaque) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	/* Special case. We do not check (possibly large) memory. */
	if (instr_get_opcode(instr) == OP_rep_movs
			|| instr_get_opcode(instr) == OP_rep_stos) {
		return true;
	}

	ub_instr_dataflow_t instr_dataflow;
	ub_dataflow_get_info(instr, &instr_dataflow);

	size_t num_flows = ub_dataflow_num_flows(&instr_dataflow);

	for (size_t i = 0; i < num_flows; i++) {

		opnd_t dst_opnd = ub_dataflow_get_flow_dst(instr, &instr_dataflow, i);
		ub_constant_analysis_patch_addr(&(taint_state->constant_state),
				&dst_opnd);

		if (!ub_dataflow_is_opnd_tainted(&dst_opnd, taint_state))
			return false;
	}

	return true;
}

bool ub_dataflow_is_instr_tainted(instr_t *instr, void *taint_state_opaque) {

	if (ub_dataflow_is_any_instr_src_tainted(instr, taint_state_opaque))
		return true;

	if (ub_dataflow_is_any_instr_dst_tainted(instr, taint_state_opaque))
		return true;

	return false;
}

static bool ub_dataflow_partially_uses_xmm(instr_t *instr) {

	/**
	 * A bit flaky here. We need to check if XMM is partially
	 * used  so we dont incorrectly deem is completely as tainted
	 * or untainted.
	 *
	 */

	int opcode = instr_get_opcode(instr);

	switch (opcode) {

	case OP_movlpd:
	case OP_movlps:
	case OP_movhpd:
	case OP_movhps:
		return true;
	default:
		return false;
	}
}

void ub_dataflow_propagate(instr_t *instr, void *taint_state_opaque) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	size_t num_flows;
	size_t num_srcs;
	ub_instr_dataflow_t instr_dataflow;

	ub_dataflow_get_info(instr, &instr_dataflow);

// We need to get dataflow info.
	num_flows = ub_dataflow_num_flows(&instr_dataflow);

	/**
	 * Special case for rep instructions as we cannot check the entire string due to
	 * overhead.
	 */
	if (instr_get_opcode(instr) == OP_rep_movs
			|| instr_get_opcode(instr) == OP_rep_stos) {

		opnd_t dst_opnd = ub_dataflow_get_flow_dst(instr, &instr_dataflow, 0);
		ub_constant_analysis_patch_addr(&(taint_state->constant_state),
				&dst_opnd);

		ub_dataflow_taint_all_mem(taint_state);

	} else {
		bool taint_results[num_flows];

		/* We first needs to consider the inputs. */
		for (size_t i = 0; i < num_flows; i++) {
			taint_results[i] = false;

			num_srcs = ub_dataflow_flow_num_srcs(&instr_dataflow, i);
			for (size_t j = 0; j < num_srcs; j++) {
				opnd_t src_opnd = ub_dataflow_get_flow_src(instr,
						&instr_dataflow, i, j);
				ub_constant_analysis_patch_addr(&(taint_state->constant_state),
						&src_opnd);
				taint_results[i] |= ub_dataflow_is_opnd_tainted(&src_opnd,
						taint_state);
			}
		}

		/* After inputs, we need to consider outputs now */
		for (size_t i = 0; i < num_flows; i++) {

			opnd_t dst_opnd = ub_dataflow_get_flow_dst(instr, &instr_dataflow,
					i);
			ub_constant_analysis_patch_addr(&(taint_state->constant_state),
					&dst_opnd);
			ub_dataflow_handle_propagation(instr, &dst_opnd, taint_state,
					taint_results[i], ub_dataflow_partially_uses_xmm(instr));
		}
	}

	ub_constant_analysis_update(&(taint_state->constant_state), instr);
}

void *ub_create_dataflow_analysis() {

	ub_dataflow_state_t *taint_state = dr_global_alloc(
			sizeof(ub_dataflow_state_t));

	/* Set register states to NULL */
	memset(taint_state->reg_taint, 0, sizeof(taint_state->reg_taint));

	taint_state->mem_opnd_list = ub_list_create();

	ub_constant_analysis_init(&(taint_state->constant_state));

	return taint_state;
}

static void ub_destroy_range(void *range_opaque) {

	ub_dataflow_mem_range_t *range = (ub_dataflow_mem_range_t *) range_opaque;
	dr_global_free(range, sizeof(ub_dataflow_mem_range_t));
}

static void ub_destroy_mem_opnd(void *mem_opnd_opaque) {

	ub_dataflow_mem_opnd_state_t *mem_opnd_state =
			(ub_dataflow_mem_opnd_state_t *) mem_opnd_opaque;

	if (mem_opnd_state->is_base_type) {

		void *range_list =
				mem_opnd_state->mem_opnd_state.base_opnd_state.range_list;
		ub_list_destroy(range_list, ub_destroy_range);

	}

	dr_global_free(mem_opnd_state, sizeof(ub_dataflow_mem_opnd_state_t));
}

void ub_destroy_dataflow_analysis(void *taint_state_opaque) {

	ub_dataflow_state_t *taint_state =
			(ub_dataflow_state_t *) taint_state_opaque;

	ub_list_destroy(taint_state->mem_opnd_list, ub_destroy_mem_opnd);
	dr_global_free(taint_state, sizeof(ub_dataflow_state_t));
}
