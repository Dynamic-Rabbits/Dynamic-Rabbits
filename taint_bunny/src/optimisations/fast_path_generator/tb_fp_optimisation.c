/*
 * tb_fast_path_optimisation.c
 *
 *      Author: john
 */

#include "tb_fp_optimisation.h"

#include "tb_fp_stat.h"
#include "tb_fp_helper.h"

#include "drbbdup.h"
#include "drhit.h"

#include "drwrap.h"
#include "dr_api.h"
#include "drmgr.h"
#include "utility_bunny.h"
#include "tb_fp.h"

/*************************************************
 * Structs
 */

/*************************************************
 * Globals
 */

static float bb_in_out_threshold;
static float pop_limit;
static size_t required_size;

/* To be removed once we add passing of user data */
static tb_context_t *tb_ctx;

/*
 * Creates default instrumentation paths. Initially, we consider 2 namely:
 *  1) All tainted - this is also the default case. Note the default path is lazily created.
 *  2) All untainted - very useful, especially in for execution where tainted data
 *     has yet to be introduced.
 */
static bool tb_fp_init_cases(void *drbbdup_ctx, void *drcontext, void *tag,
		instrlist_t *bb, bool *enable_dynamic_fp, uint *default_case_value,
		void *user_data) {

	/* We use fp ops so we have to save fp state */
	byte fp_raw[DR_FPSTATE_BUF_SIZE + DR_FPSTATE_ALIGN];
	byte *fp_align = (byte *) ALIGN_FORWARD(fp_raw, DR_FPSTATE_ALIGN);

	proc_save_fpstate(fp_align);

	app_pc pc = instr_get_app_pc(instrlist_first_app(bb));

	bool consider = false;

	if (drwrap_is_post_wrap(pc)) {
		size_t cur_size = 0;
		for (instr_t * first = instrlist_first_app(bb); first != NULL; first =
				instr_get_next_app(first))
			cur_size++;
		DR_ASSERT(cur_size == 1);
	} else {
		consider = tb_fp_set_starting_cases(drbbdup_ctx, drcontext, bb,
				enable_dynamic_fp, default_case_value, required_size,
				bb_in_out_threshold, pop_limit);
	}

	proc_restore_fpstate(fp_align);

	return consider;
}

void *tb_fp_do_initial_analysis(void *drcontext, instrlist_t *bb,
		void *user_data) {

	return tb_fp_initial_analysis(drcontext, bb);
}

void tb_fp_destroy_init_analysis(void *drcontext, void *user_data,
		void *pre_analysis_data) {

	tb_fp_destroy_initial_analysis(drcontext, pre_analysis_data);
}

static size_t tb_fp_analyse_for_instrum(void *drcontext, instrlist_t *bb,
		uint case_val, void *user_data, drvector_t *action,
		void *pre_analysis_data, void **post_data) {

	return tb_fp_analyse_for_fast_path(drcontext, bb, case_val, action,
			pre_analysis_data, post_data);
}

/**
 * Responsible for inserting inline code that determines
 * which instrumented bb to execute.
 */
static void tb_fp_get_comparator(void *drcontext, instrlist_t *bb,
		instr_t *where, void *user_data, void *pre_analysis_data) {

	tb_fp_check_inouts((tb_context_t *) user_data, drcontext, bb, where,
			pre_analysis_data);
}

static void tb_fp_set_post_instrum(void *drcontext, instrlist_t *bb,
		instr_t *where, uint case_val, void *user_data, void *pre_analysis_data,
		void *post_data) {

	tb_fp_in_out_data_t *reg_out_data =
			(tb_fp_in_out_data_t *) pre_analysis_data;

	if ((case_val != 0) || (case_val == 0 && reg_out_data->contains_rep)) {
		DR_ASSERT(post_data != NULL);

		tb_fp_update_reg_map_with_taint_data(tb_ctx, drcontext, bb, where,
				reg_out_data->out_reg_set.reg_list, post_data);

		ub_list_destroy(post_data, ub_destroy_thread_alloc_opnd);
	}
}

static bool tb_allow_fp(void *drbbdup_ctx, void *drcontext, void *tag,
		instrlist_t *ilist, uint dynamic_case, bool *enable_dynamic_fp,
		void *user_data) {

	ub_addr_const_reg_truncate(drcontext, ilist);
	ub_opnd_truncate(drcontext, ilist);

	return tb_fp_allow_generation(drbbdup_ctx, drcontext, tag, ilist,
			dynamic_case, enable_dynamic_fp, user_data);
}

/********************************************************************
 * Init Functions
 */

void *tb_fast_path_init(client_id_t client_id, tb_context_t *tb_ctx_in,
		tb_fp_settings_t *fp_settings) {

	DR_ASSERT(fp_settings);
	DR_ASSERT(fp_settings->dups_limit > 0);
	DR_ASSERT(fp_settings->pop_limit > 0);

	tb_ctx = tb_ctx_in;
	pop_limit = fp_settings->pop_limit;
	bb_in_out_threshold = fp_settings->bb_in_out_threshold;
	required_size = fp_settings->required_size;

	drwrap_init();
	ub_opnd_trunc_init();
	ub_addr_const_reg_trunc_init();
	ub_wrap_post_point_trunc_init();

	tb_fp_init_index_map();

	ib_dup_opts_t dup_opts =
			{ tb_fp_init_cases, tb_fp_do_initial_analysis,
					tb_fp_destroy_init_analysis, tb_fp_analyse_for_instrum,
					tb_fp_get_comparator, tb_allow_fp, tb_fp_set_post_instrum,
					tb_ctx_in };

	ib_dup_fp_settings_t ib_settings;
	ib_settings.dup_limit = fp_settings->dups_limit;
	ib_settings.required_size = 0;
	ib_settings.hit_threshold = fp_settings->dynamic_path_hit_threshold;

#ifdef ENABLE_STATS
	tb_fp_stat_init();
#endif

	return ib_register_instrum_tool_ex(&dup_opts, &ib_settings);
}

void tb_fast_path_exit() {

	ub_opnd_trunc_exit();
	ub_addr_const_reg_trunc_exit();
	ub_wrap_post_point_trunc_exit();

	drwrap_exit();

#ifdef ENABLE_STATS
	tb_fp_stat_exit();
#endif
}

uint32_t tb_fast_path_get_reg_mask(reg_id_t reg_id) {

	return tb_fp_internal_get_reg_mask(reg_id);
}
