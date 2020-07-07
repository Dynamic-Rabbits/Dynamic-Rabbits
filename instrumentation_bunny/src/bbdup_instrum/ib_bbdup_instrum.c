/*
 * ib_bbdup_instrum.c
 *
 *      Author: john
 */

#include "ib_bbdup_instrum.h"
#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include "../ib_data.h"
#include "../instrumentation/ib_instrumenter.h"

extern ib_ctx_t *ib_ctx;

bool ib_create_default_manager(void *drbbdup_ctx, void *drcontext, void *tag,
		instrlist_t *bb, bool *enable_fp, uint *default_case_value,
		void *user_data) {

	DR_ASSERT(ib_ctx->dup_tool_info);

	if (ib_ctx->dup_tool_info->dup_opts.create_default_manager)
		return ib_ctx->dup_tool_info->dup_opts.create_default_manager(
				drbbdup_ctx, drcontext, tag, bb, enable_fp, default_case_value,
				user_data);

	return false;
}

void ib_pre_analyse_bb(void *drcontext, instrlist_t *bb, void *user_data,
		void **pre_analysis_result) {

	DR_ASSERT(ib_ctx->dup_tool_info);

	if (ib_ctx->dup_tool_info->dup_opts.get_pre_analysis_data) {
		*pre_analysis_result =
				ib_ctx->dup_tool_info->dup_opts.get_pre_analysis_data(drcontext,
						bb, user_data);
	} else {
		*pre_analysis_result = NULL;
	}
}

void ib_destroy_pre_analysis(void *drcontext, void *user_data,
		void *pre_analysis_result) {

	DR_ASSERT(pre_analysis_result);

	if (ib_ctx->dup_tool_info->dup_opts.destroy_pre_analysis_data) {
		ib_ctx->dup_tool_info->dup_opts.destroy_pre_analysis_data(drcontext,
				user_data, pre_analysis_result);
	}
}

void ib_analyse_bb(void *drcontext, instrlist_t *bb, uint case_val,
		void *user_data, void *pre_analysis_data, void **analysis_result) {

	DR_ASSERT(ib_ctx->dup_tool_info);
	DR_ASSERT(ib_ctx->dup_tool_info->dup_opts.analyse_bb);

	ib_analyse_instrum_info_t * instrum_info = dr_thread_alloc(drcontext,
			sizeof(ib_analyse_instrum_info_t));

	drvector_init(&(instrum_info->instrum_vector), 20, false, NULL);
	instrum_info->index = 0;
	instrum_info->post_instrum_info = NULL;

	size_t size = ib_ctx->dup_tool_info->dup_opts.analyse_bb(drcontext, bb,
			case_val, user_data, &(instrum_info->instrum_vector),
			pre_analysis_data, &(instrum_info->post_instrum_info));

	instrum_info->max = size;

	*analysis_result = instrum_info;
}

void ib_destroy_analysis(void *drcontext, void *user_data,
		void *pre_analysis_data, void *delete_analysis_result) {

	DR_ASSERT(delete_analysis_result);

	ib_analyse_instrum_info_t *instrum_info =
			(ib_analyse_instrum_info_t *) delete_analysis_result;

	drvector_delete(&(instrum_info->instrum_vector));
	dr_thread_free(drcontext, instrum_info, sizeof(ib_analyse_instrum_info_t));
}

void ib_instrument_bb(void *drcontext, instrlist_t *bb, instr_t *instr,
		instr_t *where, uint case_val, void *user_data, void *pre_analysis_data,
		void *analysis_data) {

	DR_ASSERT(instr_is_app(instr));
	DR_ASSERT(ib_ctx->dup_tool_info);

	ib_analyse_instrum_info_t *instrum_info =
			(ib_analyse_instrum_info_t *) analysis_data;

	drvector_t *instrum_vector = &(instrum_info->instrum_vector);

	ib_instrum_analysis_data_t instrum_analysis_data;
	instrum_analysis_data.id = ib_ctx->dup_tool_info->tool_id;

	/* Get the instrum action at instr index */
	instrum_analysis_data.action =
			(ib_analysis_action_t) (intptr_t) drvector_get_entry(instrum_vector,
					(uint) instrum_info->index);

	DR_ASSERT(
			instrum_analysis_data.action == IB_INSTRUM_ACTION_APPLY
					|| instrum_analysis_data.action == IB_INSTRUM_ACTION_SKIP);

	ib_dispatch_instr(drcontext, bb, instr, where, &instrum_analysis_data);

	DR_ASSERT(instrum_info->index < instrum_info->max);
	instrum_info->index++;

	if (ib_ctx->dup_tool_info->dup_opts.post_handling
			&& drbbdup_is_last_instr(bb, instr)) {

		DR_ASSERT(instrum_info->index == instrum_info->max);

		ib_ctx->dup_tool_info->dup_opts.post_handling(drcontext, bb, where,
				case_val, user_data, pre_analysis_data,
				instrum_info->post_instrum_info);
		instrum_info->post_instrum_info = NULL;
	}
}

void ib_nan_instrument_bb(void *drcontext, instrlist_t *bb, instr_t *where,
		void *user_data) {

	/* We are not going to employ fast path here */
	ib_dispatch_instr(drcontext, bb, where, where, NULL);
}

void ib_get_comparator(void *drcontext, instrlist_t *bb, instr_t *where,
		void *user_data, void *pre_analysis_data) {

	DR_ASSERT(ib_ctx->dup_tool_info);
	DR_ASSERT(ib_ctx->dup_tool_info->dup_opts.get_comparator);

	ib_ctx->dup_tool_info->dup_opts.get_comparator(drcontext, bb, where,
			user_data, pre_analysis_data);
}

bool ib_allow_dynamic_fast_generation(void *drbbdup_ctx, void *drcontext,
		void *tag, instrlist_t *ilist, uint dynamic_case,
		bool *enable_dynamic_fp, void *user_data) {

	DR_ASSERT(ib_ctx->dup_tool_info);

	if (ib_ctx->dup_tool_info->dup_opts.allow_fp == NULL) {
		return true;
	} else {
		return ib_ctx->dup_tool_info->dup_opts.allow_fp(drbbdup_ctx, drcontext,
				tag, ilist, dynamic_case, enable_dynamic_fp, user_data);

	}

}
