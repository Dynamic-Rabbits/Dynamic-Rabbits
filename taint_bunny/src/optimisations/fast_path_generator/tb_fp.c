/*
 * tb_fp_stage_one.c
 *
 *      Author: john
 */

#include "tb_fp.h"
#include "tb_fp_stat.h"
#include "tb_fp_helper.h"
#include "utility_bunny.h"
#include "../../tls_access/tb_tls_access.h"
#include "../../taint_engines/taint_analysis/taint_checks/tb_ta_cc_check/tb_ta_cc_check.h"
#include "../../taint_engines/taint_analysis/taint_checks/tb_ta_raw_check/tb_ta_raw_check.h"
#include "../../taint_engines/taint_analysis/taint_checks/tb_ta_simd_check/tb_ta_simd_check.h"

#include "umbra.h"
#include "drbbdup.h"
#include "drhit.h"

#include "drwrap.h"
#include "drreg.h"
#include "dr_api.h"
#include "drmgr.h"
#include "hashtable.h"
#include "drvector.h"

/************************************************************
 * Structs
 */
unsigned long inc_false_fp;
unsigned long total_default;
unsigned long total_elided;
unsigned long total_gen_fp_count;

/* Returns the mask of the specific register. */
static bool tb_fp_bb_contains_rep(instrlist_t *bb) {

	/* Instrument according to analysis */
	instr_t *instr = instrlist_first_app(bb);
	while (instr != NULL) {

		if (instr_is_rep_string_op(instr))
			return true;

		instr = instr_get_next_app(instr);
	}
	return false;
}

/*
 * Creates default instrumentation paths. Initially, we consider 2 namely:
 *  1) All tainted - this is also the default case. Note the default path is lazily created.
 *  2) All untainted - very useful, especially in for execution where tainted data
 *     has yet to be introduced.
 */
bool tb_fp_set_starting_cases(void *drbbdup_ctx, void *drcontext,
		instrlist_t *bb, bool *enable_dynamic_fp, uint *default_case_value,
		size_t required_size, float bb_in_out_threshold, size_t pop_limit) {

	/* Firstly check if we are going to even generate fp for the bb */
	instr_t *first;
	size_t cur_size = 0;
	for (first = instrlist_first_app(bb); first != NULL; first =
			instr_get_next_app(first))
		cur_size++;

	first = instrlist_first_app(bb);
	DR_ASSERT(!drwrap_is_post_wrap(instr_get_app_pc(first)));

	ub_in_out_set_t in_out_set;
	ub_init_in_out_set(&in_out_set);
	ub_get_in_out_set(&in_out_set, bb);
	size_t in_out_size = ub_size_in_out_set(&in_out_set);

	size_t in_out_mem_size = ub_list_get_size(in_out_set.mem_list);
	in_out_mem_size += ub_list_get_size(in_out_set.mem_base_list);

	if (in_out_size <= 0) {
		ub_delete_in_out_set(&in_out_set);
		return false;
	}

	*enable_dynamic_fp = true;

	DR_ASSERT(required_size > 1);
	if (cur_size < required_size)
		*enable_dynamic_fp = false;

	if (*enable_dynamic_fp) {

		/* Secondly, check if we are going to enable dynamic fp */
		float threshold = (float) in_out_size / (float) cur_size;
		/* Enable dynamic fast path generation for bbs of 3 or greater */
		if (threshold < bb_in_out_threshold)
			*enable_dynamic_fp = false;

	}

	/* ADD ALL TAINTED CASE (DEFAULT CASE) */
	*default_case_value = tb_fp_get_default_val(&in_out_set);

	/* ADD ALL UNTAINTED CASE */
	ib_register_case_value(drbbdup_ctx, 0);

	ub_delete_in_out_set(&in_out_set);

	return true;
}

/***
 * Analysis stage
 */
void* tb_fp_initial_analysis(void *drcontext, instrlist_t *bb) {

	tb_fp_in_out_data_t *in_out_data = (tb_fp_in_out_data_t *) dr_global_alloc(
			sizeof(tb_fp_in_out_data_t));

	ub_init_in_out_set(&(in_out_data->in_out_set));
	ub_get_in_out_set(&(in_out_data->in_out_set), bb);

	ub_init_in_out_set(&(in_out_data->out_reg_set));
	ub_get_out_set_of_regs(&(in_out_data->out_reg_set), bb);

	return (void *) in_out_data;
}

void tb_fp_destroy_initial_analysis(void *drcontext, void *pre_analysis_data) {

	tb_fp_in_out_data_t *in_out_data = (tb_fp_in_out_data_t *) pre_analysis_data;

	/* No longer needed */
	ub_delete_in_out_set(&(in_out_data->in_out_set));
	ub_delete_in_out_set(&(in_out_data->out_reg_set));

	dr_global_free(in_out_data, sizeof(tb_fp_in_out_data_t));
}

size_t tb_fp_analyse_for_fast_path(void *drcontext, instrlist_t *bb,
		uint case_val, drvector_t *action, void *pre_analysis_data,
		void **post_data) {

	tb_fp_in_out_data_t *in_out_data = (tb_fp_in_out_data_t *) pre_analysis_data;
	ub_in_out_set_t *in_out_set = &(in_out_data->in_out_set);
	ub_in_out_set_t *out_reg_set = &(in_out_data->out_reg_set);

	size_t index = 0;

	in_out_data->contains_rep = tb_fp_bb_contains_rep(bb);

	uint default_case = tb_fp_get_default_val(in_out_set);

	if (case_val == 0 && !in_out_data->contains_rep) {
		/* Instrument according to analysis */
		instr_t *instr = instrlist_first_app(bb);
		while (instr != NULL) {

			drvector_set_entry(action, index, (void *) IB_INSTRUM_ACTION_SKIP);
			index++;
			instr = instr_get_next_app(instr);
		}
	} else {

		/* Reconstruct the initial taint state. */
		void *taint_state = tb_fp_analyse_set_up_taint_state(case_val,
				in_out_set);

		/* Instrument according to analysis */
		instr_t *instr = instrlist_first_app(bb);
		while (instr != NULL) {

			// If instr deals with tainted data, apply instrumentation.
			if (ub_dataflow_is_instr_tainted(instr, taint_state)) {
				drvector_set_entry(action, index,
						(void *) IB_INSTRUM_ACTION_APPLY);
			} else {
				// If instr deals with untainted data, skip instrumentation.
				drvector_set_entry(action, index,
						(void *) IB_INSTRUM_ACTION_SKIP);
			}

			ub_dataflow_propagate(instr, taint_state);

			index++;
			instr = instr_get_next_app(instr);
		}

		tb_fp_fetch_tainted_out_regs(drcontext, taint_state,
				out_reg_set->reg_list, post_data);

		ub_destroy_dataflow_analysis(taint_state);
	}

	return index;
}

bool tb_fp_allow_generation(void *drbbdup_ctx, void *drcontext, void *tag,
		instrlist_t *bb, uint dynamic_case, bool *enable_dynamic_fp,
		void *user_data) {

	bool allow = true;

	ub_in_out_set_t in_out_set;

	ub_init_in_out_set(&in_out_set);
	ub_get_in_out_set(&in_out_set, bb);

	DR_ASSERT(dynamic_case);
	DR_ASSERT(dynamic_case != tb_fp_get_default_val(&in_out_set));

#ifdef ENABLE_STATS
	tb_fp_stat_inc_fp_gen();
#endif

	uint total_count = tb_fp_analyse_count_instrumented(drcontext, bb,
			tb_fp_get_default_val(&in_out_set), &in_out_set);
	uint instrum_count = tb_fp_analyse_count_instrumented(drcontext, bb,
			dynamic_case, &in_out_set);

	if (total_count < instrum_count) {

		dr_fprintf(STDERR, "CASES: %p %p\n", tb_fp_get_default_val(&in_out_set),
				dynamic_case);

		  instr_t *instr = instrlist_first_app(bb);
		    while (instr != NULL) {

		        instr_disassemble(drcontext, instr, STDERR);
		    	instr = instr_get_next_app(instr);
		    }


		DR_ASSERT(false);
	}

#ifdef ENABLE_STATS
	tb_fp_stat_add_total(total_count);
#endif

	if (total_count == instrum_count) {

#ifdef ENABLE_STATS
		tb_fp_stat_inc_false_fp();
#endif

		*enable_dynamic_fp = false;
		allow = false;
	} else {
		DR_ASSERT(total_count > instrum_count);

#ifdef ENABLE_STATS
		tb_fp_stat_add_elided(total_count - instrum_count);
#endif
		allow = true;
	}

	ub_delete_in_out_set(&in_out_set);

	return allow;
}

/***************************************************
 * Comparator Stage
 */

/*****************************************************
 * Register CHECKS
 */

#ifndef __BMI2__
static void tb_fp_get_mask_helper_reg(tb_context_t *tb_ctx, void *drcontext,
		instrlist_t *bb, instr_t *where, reg_id_t reg_id,
		reg_id_t comparator_reg, reg_id_t opnd_mask, reg_id_t scratch_reg) {

	opnd_t comparator_opnd = opnd_create_reg(comparator_reg);
	instr_t *instr = INSTR_CREATE_add(drcontext, comparator_opnd,
			comparator_opnd);
	instrlist_meta_preinsert(bb, where, instr);

	uint32_t reg_mask = tb_fp_internal_get_reg_mask(reg_id);
	opnd_t reg_mask_opnd = opnd_create_immed_uint((ptr_uint_t) reg_mask,
	OPSZ_PTR);
	instr = INSTR_CREATE_test(drcontext, opnd_create_reg(opnd_mask),
			reg_mask_opnd);
	instrlist_meta_preinsert(bb, where, instr);

	ub_instrum_lea_base_disp(drcontext, bb, where, comparator_reg, 1,
			scratch_reg);

	instr = INSTR_CREATE_cmovcc(drcontext, OP_cmovnz,
			opnd_create_reg(comparator_reg), opnd_create_reg(scratch_reg));
	instrlist_meta_preinsert(bb, where, instr);
}
#endif

/*****************************************************
 * Memory Checks
 */

static void tb_fp_update_map_mem_comparator(void *drcontext, instrlist_t *ilist,
		instr_t *where, size_t block_size, reg_id_t addr_reg, int shift,
		int disp, reg_id_t comparator_reg, reg_id_t vector_reg,
		reg_id_t scratch_reg) {

	DR_ASSERT(reg_is_xmm(vector_reg));
	DR_ASSERT(reg_is_gpr(addr_reg));
	DR_ASSERT(reg_is_gpr(comparator_reg));
	DR_ASSERT(reg_is_gpr(scratch_reg));

	instr_t *instr;

	ub_instrum_lea_base_disp(drcontext, ilist, where, comparator_reg, shift,
			scratch_reg);

	int partial_size;
	for (size_t i = 0; i < block_size; i += sizeof(void *)) {

		partial_size = tb_simd_calculate_partial_size(block_size, i)
				* sizeof(void *);

		/** Load the label from memory **/
		opnd_t src_opnd = opnd_create_base_disp(addr_reg, DR_REG_NULL, 1,
				(i * sizeof(void *)) + (disp * sizeof(void *)),
				opnd_size_from_bytes(partial_size));

		ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
				&src_opnd, vector_reg,
				instr_get_app_pc(instr_get_next_app(where)));

		opnd_t reg_opnd = opnd_create_reg(vector_reg);
		instr = INSTR_CREATE_ptest(drcontext, reg_opnd, reg_opnd);
		instrlist_meta_preinsert(ilist, where, instr);

		instr = INSTR_CREATE_cmovcc(drcontext, OP_cmovnz,
				opnd_create_reg(comparator_reg), opnd_create_reg(scratch_reg));
		instrlist_meta_preinsert(ilist, where, instr);
	}
}

static void tb_fp_get_mem_addr(tb_context_t *tb_ctx, void *drcontext,
		instrlist_t *bb, instr_t *where, opnd_t *opnd, reg_id_t comparator_reg,
		reg_id_t res_reg, reg_id_t scratch_reg) {

	DR_ASSERT(opnd_is_memory_reference(*opnd));

	bool uses_mask = opnd_uses_reg(*opnd, comparator_reg);

	/* We might need to spill the mask because it may be restored! */
	if (uses_mask) {
		opnd_t comparator_opnd = drbbdup_get_comparator_opnd();
		ub_instrum_mov_st_reg_to_mem_opnd(drcontext, bb, where, comparator_reg,
				&comparator_opnd);
	}

	drreg_restore_app_values(drcontext, bb, where, *opnd, DR_REG_NULL);
	bool succ = drutil_insert_get_mem_addr(drcontext, bb, where, *opnd, res_reg,
			scratch_reg);
	DR_ASSERT(succ);

	if (uses_mask) {
		opnd_t comparator_opnd = drbbdup_get_comparator_opnd();
		ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, bb, where,
				&comparator_opnd, comparator_reg);
	}

	opnd_t fp_addr_opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx, TB_FP_SLOT_ADDR);
	ub_instrum_mov_st_reg_to_mem_opnd(drcontext, bb, where, res_reg,
			&fp_addr_opnd);
}

static void tb_fp_get_comparator_mask_translated_base(tb_context_t *tb_ctx,
		void *drcontext, instrlist_t *bb, instr_t *where, size_t block_size,
		bool perform_translation, reg_id_t mask_reg, reg_id_t base_addr_reg,
		int shift, int disp, reg_id_t vector_reg, reg_id_t scratch_reg) {

	if (perform_translation) {

		/* Translate */
		tb_umbra_insert_translate_address(tb_ctx, drcontext, bb, where,
				base_addr_reg, scratch_reg);
	}

	tb_fp_update_map_mem_comparator(drcontext, bb, where, block_size,
			base_addr_reg, shift, disp, mask_reg, vector_reg, scratch_reg);
}

static void tb_fp_update_comparator_mask_mem_translated_base(
		tb_context_t *tb_ctx, void *drcontext, instrlist_t *bb, instr_t *where,
		opnd_t *opnd, size_t block_size, int shift, reg_id_t *cur_base,
		reg_id_t mask_reg, reg_id_t vector_reg, reg_id_t scratch_reg,
		reg_id_t scratch_reg2) {

	reg_id_t base_reg = opnd_get_base(*opnd);

	DR_ASSERT(base_reg != DR_REG_NULL);

	if (*cur_base == base_reg) {

		tb_fp_get_comparator_mask_translated_base(tb_ctx, drcontext, bb, where,
				block_size, false, mask_reg, scratch_reg, shift,
				opnd_get_disp(*opnd), vector_reg, scratch_reg2);
	} else {

		*cur_base = base_reg;
		opnd_t base_opnd = OPND_CREATE_MEMPTR(base_reg, 0);

		tb_fp_get_mem_addr(tb_ctx, drcontext, bb, where, &base_opnd, mask_reg,
				scratch_reg, scratch_reg2);

		tb_fp_get_comparator_mask_translated_base(tb_ctx, drcontext, bb, where,
				block_size, true, mask_reg, scratch_reg, shift,
				opnd_get_disp(*opnd), vector_reg, scratch_reg2);
	}
}

static void tb_fp_update_comparator_mask_mem(tb_context_t *tb_ctx,
		void *drcontext, instrlist_t *bb, instr_t *where, opnd_t *opnd,
		size_t block_size, int shift, reg_id_t mask_reg, reg_id_t vector_reg,
		reg_id_t scratch_reg, reg_id_t scratch_reg2) {

	tb_fp_get_mem_addr(tb_ctx, drcontext, bb, where, opnd, mask_reg,
			scratch_reg, scratch_reg2);

	tb_fp_get_comparator_mask_translated_base(tb_ctx, drcontext, bb, where,
			block_size, true, mask_reg, scratch_reg, shift, 0, vector_reg,
			scratch_reg2);
}

static void tb_fp_spill(void *drcontext, instrlist_t *bb, instr_t *where,
		bool does_reg_exist, bool does_mem_exist, reg_id_t *comparator_reg,
		reg_id_t *vector_reg, reg_id_t * scratch_reg, reg_id_t * scratch_reg2) {

	*comparator_reg = DR_REG_NULL;
	*vector_reg = DR_REG_NULL;
	*scratch_reg = DR_REG_NULL;
	*scratch_reg2 = DR_REG_NULL;

	if (drreg_reserve_register(drcontext, bb, where, NULL, comparator_reg)
			!= DRREG_SUCCESS)
		DR_ASSERT(false);

	if (does_mem_exist) {
		if (drreg_reserve_xmm_register(drcontext, bb, where, NULL, vector_reg)
				!= DRREG_SUCCESS
				|| drreg_reserve_register(drcontext, bb, where, NULL,
						scratch_reg) != DRREG_SUCCESS
				|| drreg_reserve_register(drcontext, bb, where, NULL,
						scratch_reg2) != DRREG_SUCCESS) {
			DR_ASSERT(false);
		}
	} else if (does_reg_exist) {
#ifdef __BMI2__
		if (drreg_reserve_register(drcontext, bb, where, NULL, scratch_reg)
				!= DRREG_SUCCESS) {
			DR_ASSERT(false);
		}
#else
		if (drreg_reserve_register(drcontext, bb, where, NULL, scratch_reg)
				!= DRREG_SUCCESS
				|| drreg_reserve_register(drcontext, bb, where, NULL,
						scratch_reg2) != DRREG_SUCCESS) {
			DR_ASSERT(false);
		}
#endif
	}
}

static void tb_fp_restore(void *drcontext, instrlist_t *bb, instr_t *where,
		bool does_reg_exist, bool does_mem_exist, reg_id_t comparator_reg,
		reg_id_t vector_reg, reg_id_t scratch_reg, reg_id_t scratch_reg2) {

	drreg_unreserve_register(drcontext, bb, where, comparator_reg);

	if (does_mem_exist) {
		drreg_unreserve_xmm_register(drcontext, bb, where, vector_reg);
		drreg_unreserve_register(drcontext, bb, where, scratch_reg);
		drreg_unreserve_register(drcontext, bb, where, scratch_reg2);

	} else if (does_reg_exist) {
#ifdef __BMI2__
		drreg_unreserve_register(drcontext, bb, where, scratch_reg);
#else
		drreg_unreserve_register(drcontext, bb, where, scratch_reg);
		drreg_unreserve_register(drcontext, bb, where, scratch_reg2);
#endif
	}
}

/**
 * Responsible for inserting inline code that determines
 * which instrumented bb to execute.
 */
void tb_fp_check_inouts(tb_context_t *tb_ctx, void *drcontext, instrlist_t *bb,
		instr_t *where, void *pre_analysis_data) {

	reg_id_t comparator_reg, vector_reg, scratch_reg, scratch_reg2;

	tb_fp_in_out_data_t *in_out_data = (tb_fp_in_out_data_t *) pre_analysis_data;
	ub_in_out_set_t *in_out_set = &(in_out_data->in_out_set);

	bool is_checking_reg = ub_list_get_size(in_out_set->reg_list) > 0;
	int mem_opnd_count = (int) ub_list_get_size(in_out_set->mem_list)
			+ ub_list_get_size(in_out_set->mem_base_list);
	bool is_checking_mem = mem_opnd_count > 0;

	tb_fp_spill(drcontext, bb, where, is_checking_reg, is_checking_mem,
			&comparator_reg, &vector_reg, &scratch_reg, &scratch_reg2);

	DR_ASSERT(comparator_reg != DR_REG_NULL);

#ifdef __BMI2__
	if (is_checking_reg) {
		opnd_t reg_state_opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx,
				TB_FP_SLOT_REG_STATE);
		ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, bb, where, &reg_state_opnd,
				scratch_reg);

		uint32_t bit_mask = 0;
		for (void * it = ub_list_get_start_it(in_out_set->reg_list); it; it =
				ub_list_get_next_it(it)) {
			opnd_t *reg_opnd = ub_list_get_it_value(it);
			DR_ASSERT(ub_opnd_is_reg(reg_opnd));
			bit_mask |= tb_fp_internal_get_reg_mask(opnd_get_reg(*reg_opnd));
		}

		ub_instrum_mov_st_immed_to_reg(drcontext, bb, where, bit_mask, comparator_reg);

		opnd_t msk_opnd = opnd_create_reg(comparator_reg);
		opnd_t src_opnd = opnd_create_reg(scratch_reg);
		opnd_t dst_opnd = opnd_create_reg(comparator_reg);

		/* Does not follow intel operand ordering - mask before source. */
		instr_t *instr = INSTR_CREATE_pext(drcontext, dst_opnd, msk_opnd, src_opnd);
		instrlist_meta_preinsert(bb, where, instr);

	} else {
		ub_instrum_clear_reg(drcontext, bb, where, comparator_reg);
	}

#else
	DR_ASSERT(scratch_reg2 != DR_REG_NULL);
	ub_instrum_clear_reg(drcontext, bb, where, comparator_reg);

	if (is_checking_reg) {

		/* Load register bit statuses. */
		opnd_t reg_state_opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx,
		TB_FP_SLOT_REG_STATE);
		ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, bb, where, &reg_state_opnd,
				scratch_reg2);

		reg_id_t prev_debug = DR_REG_NULL;

		for (void *it = ub_list_get_start_it(in_out_set->reg_list); it; it =
				ub_list_get_next_it(it)) {

			opnd_t *reg_opnd = ub_list_get_it_value(it);
			DR_ASSERT(ub_opnd_is_reg(reg_opnd));
			reg_id_t reg = opnd_get_reg(*reg_opnd);

			DR_ASSERT(prev_debug < reg);
			prev_debug = reg;

			tb_fp_get_mask_helper_reg(tb_ctx, drcontext, bb, where, reg,
					comparator_reg, scratch_reg2, scratch_reg);
		}
	}
#endif

	if (is_checking_mem) {
		reg_id_t cur_base = DR_REG_NULL;

		ub_instrum_shift_left(drcontext, bb, where, comparator_reg,
				mem_opnd_count);

		int shift;

		/* Check whether memory, that share common base, is tainted */
		for (void * it = ub_list_get_start_it(in_out_set->mem_base_list); it;
				it = ub_list_get_next_it(it)) {

			mem_opnd_count--;
			DR_ASSERT(mem_opnd_count >= 0);
			shift = 1 << mem_opnd_count;

			opnd_t *base_mem_opnd = ub_list_get_it_value(it);

			opnd_size_t size_opnd = opnd_get_size(*base_mem_opnd);
			size_t size = opnd_size_in_bytes(size_opnd);

			tb_fp_update_comparator_mask_mem_translated_base(tb_ctx, drcontext,
					bb, where, base_mem_opnd, size, shift, &cur_base,
					comparator_reg, vector_reg, scratch_reg2, scratch_reg);
		}

		/* Check whether memory, that don't share common base, is tainted */
		for (void * it = ub_list_get_start_it(in_out_set->mem_list); it; it =
				ub_list_get_next_it(it)) {

			mem_opnd_count--;
			DR_ASSERT(mem_opnd_count >= 0);
			shift = 1 << mem_opnd_count;

			opnd_t *mem_opnd = ub_list_get_it_value(it);

			opnd_size_t size_opnd = opnd_get_size(*mem_opnd);
			size_t size = opnd_size_in_bytes(size_opnd);

			tb_fp_update_comparator_mask_mem(tb_ctx, drcontext, bb, where,
					mem_opnd, size, shift, comparator_reg, vector_reg,
					scratch_reg2, scratch_reg);
		}

		/* Clear the stored memory address */
		opnd_t fp_addr_opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx,
		TB_FP_SLOT_ADDR);
		ub_instrum_clear_mem_opnd(drcontext, bb, where, &fp_addr_opnd);
	}

	/* Store the mask to memory */
	opnd_t comparator_opnd = drbbdup_get_comparator_opnd();
	ub_instrum_mov_st_reg_to_mem_opnd(drcontext, bb, where, comparator_reg,
			&comparator_opnd);

	tb_fp_restore(drcontext, bb, where, is_checking_reg, is_checking_mem,
			comparator_reg, vector_reg, scratch_reg, scratch_reg2);
}

static void tb_fp_update_reg_map_via_cmov(tb_context_t *tb_ctx, void *drcontext,
		instrlist_t *bb, instr_t *where, void *out_taint_regs,
		reg_id_t bit_mask_reg) {

	reg_id_t vector_reg, map_reg, scratch_reg;
	int partial_size;
	uint32_t reg_mask = 0;
	instr_t *instr;

	if (drreg_reserve_xmm_register(drcontext, bb, where, NULL, &vector_reg)
			!= DRREG_SUCCESS
			|| drreg_reserve_register(drcontext, bb, where, NULL, &scratch_reg)
					!= DRREG_SUCCESS
			|| drreg_reserve_register(drcontext, bb, where, NULL, &map_reg)
					!= DRREG_SUCCESS) {
		DR_ASSERT(false);
	}

	tb_raw_arraymap_insert_load_reg_map(tb_ctx, drcontext, bb, where, map_reg);

	/* Set vector to all 1s. */
	opnd_t vector_opnd = opnd_create_reg(vector_reg);
	instr = INSTR_CREATE_pcmpeqd(drcontext, vector_opnd, vector_opnd);
	instrlist_meta_preinsert(bb, where, instr);

	for (void * it = ub_list_get_start_it(out_taint_regs); it; it =
			ub_list_get_next_it(it)) {

		opnd_t *reg_opnd = ub_list_get_it_value(it);
		reg_id_t reg_id = opnd_get_reg(*reg_opnd);
		reg_id_t reg_byte_id = ub_get_byte_id(reg_id, 0);
		reg_mask = tb_fp_internal_get_reg_mask(reg_id);

		size_t reg_size = ub_get_reg_size(reg_id);
		DR_ASSERT(reg_size >= sizeof(void *));

		ub_instrum_mov_st_reg_to_reg(drcontext, bb, where, bit_mask_reg,
				scratch_reg);

		instr = INSTR_CREATE_or(drcontext, opnd_create_reg(scratch_reg),
				opnd_create_immed_uint(reg_mask, OPSZ_4));
		instrlist_meta_preinsert(bb, where, instr);

		if (reg_size == sizeof(void *)) {

			opnd_t src_opnd = tb_raw_arraymap_get_opnd_via_id(drcontext,
					map_reg, reg_byte_id, 0,
					opnd_size_from_bytes(sizeof(void *) * sizeof(void *)));

			instr = INSTR_CREATE_ptest(drcontext, vector_opnd, src_opnd);
			instrlist_meta_preinsert(bb, where, instr);

		} else {
			ub_instrum_simd_clear_reg(drcontext, bb, where, vector_reg);

			for (size_t i = 0; i < reg_size; i += sizeof(void *)) {

				partial_size = tb_simd_calculate_partial_size(reg_size, i)
						* sizeof(void *);

				opnd_t src_opnd = tb_raw_arraymap_get_opnd_via_id(drcontext,
						map_reg, reg_byte_id, i * sizeof(void *),
						opnd_size_from_bytes(partial_size));
				instr = INSTR_CREATE_por(drcontext, vector_opnd, src_opnd);
				instrlist_meta_preinsert(bb, where, instr);
			}

			instr = INSTR_CREATE_ptest(drcontext, vector_opnd, vector_opnd);
			instrlist_meta_preinsert(bb, where, instr);

			instr = INSTR_CREATE_pcmpeqd(drcontext, vector_opnd, vector_opnd);
			instrlist_meta_preinsert(bb, where, instr);

		}

		/* Eflags have been set*/
		instr = INSTR_CREATE_cmovcc(drcontext, OP_cmovnz,
				opnd_create_reg(bit_mask_reg), opnd_create_reg(scratch_reg));
		instrlist_meta_preinsert(bb, where, instr);
	}

	drreg_unreserve_register(drcontext, bb, where, scratch_reg);
	drreg_unreserve_register(drcontext, bb, where, map_reg);
	drreg_unreserve_xmm_register(drcontext, bb, where, vector_reg);
}

void tb_fp_update_reg_map_with_taint_data(tb_context_t *tb_ctx, void *drcontext,
		instrlist_t *bb, instr_t *where, void *out_reg_list,
		void *out_taint_regs) {

	instr_t *instr;
	reg_id_t bit_mask_reg;

	bool is_checking_reg = ub_list_get_size(out_reg_list) > 0;
	size_t is_taint_reg = ub_list_get_size(out_taint_regs) > 0;

	if (is_checking_reg) {
		if (drreg_reserve_aflags(drcontext, bb, where)

				|| drreg_reserve_register(drcontext, bb, where, NULL,
						&bit_mask_reg) != DRREG_SUCCESS) {
			DR_ASSERT(false);
		}

		/* Load current mask */
		opnd_t reg_state_opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx,
		TB_FP_SLOT_REG_STATE);
		ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, bb, where, &reg_state_opnd,
				bit_mask_reg);

		uint32_t reg_mask = 0;

		for (void * it = ub_list_get_start_it(out_reg_list); it; it =
				ub_list_get_next_it(it)) {
			opnd_t *reg_opnd = ub_list_get_it_value(it);
			reg_id_t reg_id = opnd_get_reg(*reg_opnd);
			reg_mask |= tb_fp_internal_get_reg_mask(reg_id);
		}

		/* Set untainted regs directly to zero, and check possible tainted regs */
		instr = INSTR_CREATE_and(drcontext, opnd_create_reg(bit_mask_reg),
				opnd_create_immed_uint(~reg_mask, OPSZ_4));
		instrlist_meta_preinsert(bb, where, instr);

		if (is_taint_reg) {
			tb_fp_update_reg_map_via_cmov(tb_ctx, drcontext, bb, where,
					out_taint_regs, bit_mask_reg);
		}

		ub_instrum_mov_st_reg_to_mem_opnd(drcontext, bb, where, bit_mask_reg,
				&reg_state_opnd);

		drreg_unreserve_aflags(drcontext, bb, where);
		drreg_unreserve_register(drcontext, bb, where, bit_mask_reg);
	}
}

