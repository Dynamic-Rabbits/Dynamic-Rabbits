/*
 * tb_fp_helper.c
 *
 *      Author: john
 */

#include "tb_fp_helper.h"

#include "../../taint_engines/taint_analysis/taint_checks/tb_ta_cc_check/tb_ta_cc_check.h"
#include "../../taint_engines/taint_analysis/taint_checks/tb_ta_raw_check/tb_ta_raw_check.h"
#include "../../taint_engines/taint_analysis/taint_checks/tb_ta_simd_check/tb_ta_simd_check.h"

/* Initialised once, used multiple times */
static uint32_t reg_id_to_mask_index[REG_MAX_VAL];

void tb_fp_init_index_map() {

	int index_counter = 0;
	size_t register_size = ub_get_reg_size(DR_REG_START_GPR);
	for (reg_id_t gpr = DR_REG_START_GPR; gpr <= DR_REG_STOP_GPR; gpr++) {

		unsigned int ub_reg_id = ub_get_byte_id(gpr, 0);
		for (size_t i = 0; i < register_size; i++) {
			reg_id_to_mask_index[ub_reg_id + i] = index_counter;
		}
		index_counter++;
	}

	register_size = ub_get_reg_size(DR_REG_START_XMM);
	for (int j = 0; j < MCXT_NUM_SIMD_SLOTS; j++) {

		unsigned int ub_reg_id = ub_get_byte_id(DR_REG_START_XMM + j, 0);
		for (size_t i = 0; i < register_size; i++) {
			reg_id_to_mask_index[ub_reg_id + i] = index_counter;
		}
		index_counter++;
	}

	DR_ASSERT(index_counter < 32);
}

/* Returns the mask of the specific register. */
uint32_t tb_fp_internal_get_reg_mask(reg_id_t reg_id) {

	unsigned int ub_reg_id = ub_get_byte_id(reg_id, 0);
	uint32_t index = reg_id_to_mask_index[ub_reg_id];
	uint32_t mask = 1;
	return mask << index;
}

void *tb_fp_analyse_set_up_taint_state(uint case_val,
		ub_in_out_set_t *in_out_set) {

	void *taint_state = ub_create_dataflow_analysis();

	int total_in_outs = (int) ub_size_in_out_set(in_out_set);

#ifndef __BMI2__

	for (void * it = ub_list_get_start_it(in_out_set->reg_list); it; it =
			ub_list_get_next_it(it)) {

		opnd_t *reg_opnd = ub_list_get_it_value(it);

		total_in_outs--;
		DR_ASSERT(total_in_outs >= 0);
		unsigned int mask = 1;
		mask = mask << total_in_outs;

		if (mask & case_val) {
			// This opnd is therefore tainted. We need to update the taint state.
			ub_dataflow_mark_opnd_tainted(reg_opnd, taint_state, true);
		} else {
			ub_dataflow_mark_opnd_tainted(reg_opnd, taint_state, false);
		}
	}
#else
	/* When BMI2 is enabled, bit order is reversed! */
	int reg_counter = (int) ub_list_get_size(in_out_set->mem_list)
	+ ub_list_get_size(in_out_set->mem_base_list);

	for (void * it = ub_list_get_start_it(in_out_set->reg_list); it; it =
			ub_list_get_next_it(it)) {

		opnd_t *reg_opnd = ub_list_get_it_value(it);
		DR_ASSERT(ub_opnd_is_reg(reg_opnd));
		DR_ASSERT(reg_counter < total_in_outs);

		unsigned int mask = 1;
		mask = mask << reg_counter;

		if (mask & case_val) {
			// This opnd is therefore tainted. We need to update the taint state.
			ub_dataflow_mark_opnd_tainted(reg_opnd, taint_state, true);
		} else {
			ub_dataflow_mark_opnd_tainted(reg_opnd, taint_state, false);
		}
		reg_counter++;
	}
#endif

	total_in_outs = (int) ub_list_get_size(in_out_set->mem_list)
			+ ub_list_get_size(in_out_set->mem_base_list);

	for (void * it = ub_list_get_start_it(in_out_set->mem_base_list); it; it =
			ub_list_get_next_it(it)) {

		opnd_t *mem_base_opmd = ub_list_get_it_value(it);

		total_in_outs--;
		DR_ASSERT(total_in_outs >= 0);
		unsigned int mask = 1;
		mask = mask << total_in_outs;

		if (mask & case_val) {
			// This opnd is therefore tainted. We need to update the taint state.
			ub_dataflow_mark_opnd_tainted(mem_base_opmd, taint_state, true);
		} else {
			ub_dataflow_mark_opnd_tainted(mem_base_opmd, taint_state, false);
		}
	}

	for (void * it = ub_list_get_start_it(in_out_set->mem_list); it; it =
			ub_list_get_next_it(it)) {

		opnd_t *mem_opnd = ub_list_get_it_value(it);

		total_in_outs--;
		DR_ASSERT(total_in_outs >= 0);
		unsigned int mask = 1;
		mask = mask << total_in_outs;

		if (mask & case_val) {
			// This opnd is therefore tainted. We need to update the taint state.
			ub_dataflow_mark_opnd_tainted(mem_opnd, taint_state, true);
		} else {
			ub_dataflow_mark_opnd_tainted(mem_opnd, taint_state, false);
		}
	}

	DR_ASSERT(total_in_outs == 0);

	return taint_state;
}

/**
 * Responsible for deriving the default case value. Essentially, the default case
 * represents the occurrance of all in/out operands being tainted.
 *
 * Therefore, from UB's in out analysis, we get the count of opnds, and create a
 * mask of 1s.
 *
 */
uint32_t tb_fp_get_default_val(ub_in_out_set_t *in_out_set) {

	size_t total_in_outs = ub_size_in_out_set(in_out_set);

	unsigned int default_val = 0;
	for (size_t i = 0; i < total_in_outs; i++) {
		// Shift and or with 1
		default_val = default_val << 1;
		default_val |= 1;
	}

	return default_val;
}

void tb_fp_fetch_tainted_out_regs(void *drcontext, void *taint_state,
		void *reg_list, void **tainted_out_list) {

	void *tainted_out_regs = ub_list_create();
	*tainted_out_list = tainted_out_regs;

	for (void *it = ub_list_get_start_it(reg_list); it;
			it = ub_list_get_next_it(it)) {

		opnd_t *reg_opnd = ub_list_get_it_value(it);
		DR_ASSERT(reg_opnd);

		if (ub_dataflow_is_opnd_tainted(reg_opnd, taint_state)) {
			opnd_t *copy_opnd = dr_thread_alloc(drcontext, sizeof(opnd_t));
			*copy_opnd = *reg_opnd;
			ub_list_insert(tainted_out_regs, copy_opnd);
		}
	}

}

void ub_destroy_thread_alloc_opnd(void *del_opnd){

	void *drcontext = dr_get_current_drcontext();
	dr_thread_free(drcontext, del_opnd, sizeof(opnd_t));
}


