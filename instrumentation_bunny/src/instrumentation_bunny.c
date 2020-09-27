/*
 * instrumentation_bunny.c
 *
 *      Author: john
 */

#include "instrumentation_bunny.h"

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include "utility_bunny.h"
#include "slicer_bunny.h"

#include "ib_data.h"
#include "options/ib_option.h"
#include "instrumentation/ib_instrumenter.h"
#include "tls_access/ib_tls_access.h"
#include "bbdup_instrum/ib_bbdup_instrum.h"

#include <stddef.h>

#include <signal.h>

/********************************************************************
 * Structs and Definitions
 */

ib_ctx_t *ib_ctx = NULL;

/********************************************************************
 * Prototypes
 */

static void ib_thread_init(void *drcontext);
static void ib_thread_exit(void *drcontext);

static unsigned int *ib_get_next_tool_id();
static void ib_destroy_tool_id(unsigned int *tool_id);

static dr_emit_flags_t ib_app_instruction(void *drcontext, void *tag,
		instrlist_t *bb, instr_t *instr, bool for_trace, bool translating,
		void *user_data);

static dr_signal_action_t ib_raw_conc_invalid_event_signal(void *drcontext,
		dr_siginfo_t *info);

/********************************************************************
 * Implementation
 */

ib_skip_check_t check = NULL;
void *check_data = NULL;

DR_EXPORT void ib_init_debug(void *slicer, ib_skip_check_t c, void *d) {

	check = c;
	check_data = d;

	ib_init(slicer);
}

DR_EXPORT void ib_init(void *slicer) {

	if (ib_ctx == NULL) {

		// Initialise DR manager
		drmgr_init();
		drutil_init();

		ib_ctx = dr_global_alloc(sizeof(ib_ctx_t));

		dr_raw_tls_calloc(&(ib_ctx->tls_raw_reg), &(ib_ctx->tls_raw_base), 9,
				0);

		ib_ctx->opcode_hook_mngr = ib_opcode_hook_mngr_create();
		ib_ctx->tool_id_counter = 1;
		ib_ctx->ref_counter = 1;

		ib_code_cache_manager_init();

		ib_ctx->slicer = slicer;

		ib_ctx->tls_data_idx = drmgr_register_tls_field();
		ib_ctx->dup_tool_info = NULL;

		drmgr_priority_t priority = { sizeof(drmgr_priority_t),
		DRMGR_PRIORITY_NAME_IB,
		NULL, NULL, DRMGR_PRIORITY_INSERT_INSTRUMENTATION_BUNNY };

		// Register hooks.
		if (!drmgr_register_thread_init_event(ib_thread_init)
				|| !drmgr_register_thread_exit_event(ib_thread_exit)
				|| !drmgr_register_bb_instrumentation_event(NULL,
						ib_app_instruction, &priority)) {

			DR_ASSERT(false);
			dr_global_free(ib_ctx, sizeof(ib_ctx_t));
			ib_ctx = NULL;
		}

		ib_instrumenter_init();

		drmgr_register_signal_event(ib_raw_conc_invalid_event_signal);

	} else {
		ib_ctx->ref_counter++;
	}
}

DR_EXPORT void ib_exit() {

	DR_ASSERT(ib_ctx);

	if (ib_ctx->ref_counter == 1) {

		if (!drmgr_unregister_thread_init_event(ib_thread_init)
				|| !drmgr_unregister_thread_exit_event(ib_thread_exit))
			DR_ASSERT(false);

		if (!ib_ctx->dup_tool_info) {

			if (!drmgr_unregister_bb_insertion_event(ib_app_instruction))
				DR_ASSERT(false);

		} else {
			drbbdup_exit();
		}
		drmgr_unregister_tls_field(ib_ctx->tls_data_idx);

		dr_raw_tls_cfree(ib_ctx->tls_raw_base, 9);

		ib_opcode_hook_mngr_destroy(ib_ctx->opcode_hook_mngr);

		drmgr_unregister_signal_event(ib_raw_conc_invalid_event_signal);

		ib_instrumenter_exit();

		ib_code_cache_manager_destroy();

		dr_global_free(ib_ctx, sizeof(ib_ctx_t));

		drutil_exit();
		drmgr_exit();

		ib_ctx = NULL;

	} else {
		ib_ctx->ref_counter--;
	}
}

DR_EXPORT bool ib_is_initialised() {

	return ib_ctx != NULL;
}

/**
 *  Creates instrumentation data structure used to store information
 *  about the instruction being instrumented.
 */
static void ib_thread_init(void *drcontext) {

	ib_per_thread_t *thread_data = (ib_per_thread_t *) dr_thread_alloc(
			drcontext, sizeof(ib_per_thread_t));

	if (thread_data != NULL) {
		ib_tls_set_thread_data(thread_data);

		// We also store it in drcontext tls storage so that other threads may access it.
		drmgr_set_tls_field(drcontext, ib_ctx->tls_data_idx, thread_data);
	}
}

/**
 *  Called upon thread exit. Destroys thread data
 */
static void ib_thread_exit(void *drcontext) {

	ib_per_thread_t *thread_data = (ib_per_thread_t *) drmgr_get_tls_field(
			drcontext, ib_ctx->tls_data_idx);

	dr_thread_free(drcontext, thread_data, sizeof(ib_per_thread_t));
}

static dr_emit_flags_t ib_app_instruction(void *drcontext, void *tag,
		instrlist_t *bb, instr_t *instr, bool for_trace, bool translating,
		void *user_data) {

	ib_dispatch_instr(drcontext, bb, instr, instr, NULL);

	return DR_EMIT_DEFAULT;
}

/********************************************************************
 * Registration
 */

static size_t* ib_get_next_tool_id() {

	size_t *id = dr_global_alloc(sizeof(size_t));
	*id = ib_ctx->tool_id_counter;

	ib_ctx->tool_id_counter++;

	return id;
}

static void ib_destroy_tool_id(size_t *tool_id) {

	dr_global_free(tool_id, sizeof(size_t));
}

DR_EXPORT void* ib_register_instrum_tool() {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(ib_ctx->opcode_hook_mngr);

	size_t *tool_id = ib_get_next_tool_id();

	ib_opcode_hook_mngr_register_instrum_tool(ib_ctx->opcode_hook_mngr,
			*tool_id);

	DR_ASSERT(tool_id);

	return (void *) tool_id;
}

DR_EXPORT void* ib_register_instrum_tool_ex(ib_dup_opts_t *dup_opts,
		ib_dup_fp_settings_t *fp_settings) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(ib_ctx->opcode_hook_mngr);
	DR_ASSERT(dup_opts);

	if (ib_ctx->dup_tool_info) {
		DR_ASSERT_MSG(false,
				"Cannot register an additional ex tool for now!. The Taint Bunny needs this!");
		return NULL;
	}

	size_t *tool_id = ib_get_next_tool_id();

	ib_opcode_hook_mngr_register_instrum_tool(ib_ctx->opcode_hook_mngr,
			*tool_id);

	/* We need to unregister the conventional instrumentation routine. */
	if (!drmgr_unregister_bb_insertion_event(ib_app_instruction))
		DR_ASSERT(false);

	drmgr_priority_t priority = { sizeof(drmgr_priority_t),
	DRMGR_PRIORITY_NAME_IB,
	NULL, NULL, DRMGR_PRIORITY_INSERT_INSTRUMENTATION_BUNNY };

	ib_ctx->dup_tool_info = dr_global_alloc(sizeof(ib_dup_tool_t));
	ib_ctx->dup_tool_info->tool_id = *tool_id;

	memcpy(&(ib_ctx->dup_tool_info->dup_opts), dup_opts, sizeof(ib_dup_opts_t));

	drbbdup_options_t bbdup_opts = { ib_create_default_manager,
			ib_pre_analyse_bb, ib_destroy_pre_analysis, ib_analyse_bb,
			ib_destroy_analysis, ib_instrument_bb, ib_nan_instrument_bb,
			ib_get_comparator, ib_allow_dynamic_fast_generation,
			dup_opts->user_data };

	drbbdup_init_ex(&bbdup_opts, fp_settings, &priority);

	DR_ASSERT(tool_id);

	return (void *) tool_id;
}

DR_EXPORT bool ib_unregister_instrum_tool(void *tool_info) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	bool is_removed = ib_opcode_hook_mngr_unregister_instrum_tool(
			ib_ctx->opcode_hook_mngr, *tool_id);
	DR_ASSERT(is_removed);

	if (ib_ctx->dup_tool_info) {

		if (ib_ctx->dup_tool_info->tool_id == *tool_id) {

			drbbdup_exit();
			dr_global_free(ib_ctx->dup_tool_info, sizeof(ib_dup_tool_t));
			ib_ctx->dup_tool_info = NULL;

			if (!drmgr_register_bb_instrumentation_event(NULL,
					ib_app_instruction, NULL))
				DR_ASSERT(false);
		}
	}

	ib_destroy_tool_id(tool_id);
	return is_removed;
}

void ib_hook_skip(void *tool_info, int opcode) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t skip_hook_info;
	ib_hook_info_init_skip(&skip_hook_info);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &skip_hook_info);
}

void ib_hook_to_instr(void *tool_info, int opcode,
		ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);
	DR_ASSERT(user_instrum_data);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t hook_instr_info;
	ib_hook_info_init_instrum_instr(&hook_instr_info, user_instrum_data,
			options);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &hook_instr_info);
}

void ib_hook_to_instr_ex(void *tool_info, int opcode,
		ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options,
		IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
		ib_guard_result_t action_result) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);
	DR_ASSERT(user_instrum_data);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t hook_instr_info;
	ib_hook_info_init_instrum_instr_ex(&hook_instr_info, user_instrum_data,
			options, pos, check_hook_guard, action_result);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &hook_instr_info);
}

void ib_hook_cache_to_instr(void *tool_info, int opcode,
		ib_insert_hndle_data_t *cache_data, IB_INSTRUM_OPT options) {

//TODO: WAY TO MANY ARGS. I don't like especially since the function is exported.

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t instr_hook_info;

	ib_hook_cache_info_init_instrum_instr(&instr_hook_info, cache_data,
			options);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &instr_hook_info);
}

void ib_hook_cache_to_instr_ex(void *tool_info, int opcode,
		ib_insert_hndle_data_t *cache_data, IB_INSTRUM_OPT options,
		IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
		ib_guard_result_t action_result) {

//TODO: WAY TO MANY ARGS. I don't like especially since the function is exported.

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t instr_hook_info;
	ib_hook_cache_info_init_instrum_instr_ex(&instr_hook_info, cache_data,
			options, pos, check_hook_guard, action_result);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &instr_hook_info);
}

void ib_hook_to_branch_instr(void *tool_info, int opcode,
		ib_insert_hndle_data_t *user_instrum_data,
		ib_insert_hndle_data_t * target_instrum_data,
		ib_insert_hndle_data_t * fall_instrum_data, IB_INSTRUM_OPT options) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t branch_hook_info;
	ib_hook_info_init_instrum_branch_instr(&branch_hook_info, user_instrum_data,
			target_instrum_data, fall_instrum_data, options);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &branch_hook_info);
}

void ib_hook_to_branch_instr_ex(void *tool_info, int opcode,
		ib_insert_hndle_data_t * user_instrum_data,
		ib_insert_hndle_data_t *target_instrum_data,
		ib_insert_hndle_data_t * fall_instrum_data, IB_INSTRUM_OPT options,
		IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
		ib_guard_result_t action_result) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t branch_hook_info;
	ib_hook_info_init_instrum_branch_instr_ex(&branch_hook_info,
			user_instrum_data, target_instrum_data, fall_instrum_data, options,
			pos, check_hook_guard, action_result);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &branch_hook_info);
}

void ib_hook_cache_to_branch_instr(void *tool_info, int opcode,
		ib_insert_hndle_data_t *cache_data,
		ib_insert_hndle_data_t *target_cache_data,
		ib_insert_hndle_data_t *fall_through_code_cache, IB_INSTRUM_OPT options) {

//TODO: WAY TO MANY ARGS. I don't like especially since the function is exported.

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t branch_hook_info;
	ib_hook_cache_info_init_instrum_branch_instr(&branch_hook_info, cache_data,
			target_cache_data, fall_through_code_cache, options);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &branch_hook_info);
}

void ib_hook_cache_to_branch_instr_ex(void *tool_info, int opcode,
		ib_insert_hndle_data_t *cache_data,
		ib_insert_hndle_data_t *target_cache_data,
		ib_insert_hndle_data_t *fall_through_code_cache, IB_INSTRUM_OPT options,
		IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
		ib_guard_result_t action_result) {

//TODO: WAY TO MANY ARGS. I don't like especially since the function is exported.

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t branch_hook_info;

	ib_hook_cache_info_init_instrum_branch_instr_ex(&branch_hook_info,
			cache_data, target_cache_data, fall_through_code_cache, pos,
			options, check_hook_guard, action_result);

	ib_opcode_hook_mngr_hook_opcode_for_tool(ib_ctx->opcode_hook_mngr, *tool_id,
			opcode, &branch_hook_info);
}

DR_EXPORT void ib_remove_hook_via_opcode(void *tool_info, int opcode) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_opcode_hook_mngr_unhook_opcode_for_tool(ib_ctx->opcode_hook_mngr,
			*tool_id, opcode);
}

void ib_hook_to_default(void *tool_info,
		ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t default_hook_info;
	ib_hook_info_init_instrum_instr(&default_hook_info, user_instrum_data,
			options);

	ib_opcode_hook_mngr_hook_default_for_tool(ib_ctx->opcode_hook_mngr,
			*tool_id, &default_hook_info);

}

DR_EXPORT void ib_hook_cache_to_default(void *tool_info,
		ib_insert_hndle_data_t *cache_data, IB_INSTRUM_OPT options) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_hook_info_t default_hook_info;
	ib_hook_cache_info_init_instrum_instr(&default_hook_info, cache_data,
			options);

	ib_opcode_hook_mngr_hook_default_for_tool(ib_ctx->opcode_hook_mngr,
			*tool_id, &default_hook_info);
}

DR_EXPORT void ib_remove_default_hook(void *tool_info) {

	DR_ASSERT(ib_is_initialised());
	DR_ASSERT(tool_info);

	size_t *tool_id = (size_t *) tool_info;

	ib_opcode_hook_mngr_unhook_default_for_tool(ib_ctx->opcode_hook_mngr,
			*tool_id);
}

/********************************************************************
 * Information Retrieval
 */

DR_EXPORT void ib_insert_load_per_thread_data(void *drcontext,
		instrlist_t *ilist, instr_t *where, reg_id_t data_reg) {

	opnd_t thread_data_opnd = ib_tls_get_raw_slot_opnd(
	IB_RAW_SLOT_THRD_DATA);
	opnd_t opnd = opnd_create_reg(data_reg);
	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, opnd, thread_data_opnd);
	instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT size_t ib_get_num_srcs(void *drcontext) {

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return (size_t) instrum_data->instr_src_count;
}

DR_EXPORT void ib_insert_get_num_srcs(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg) {

	ib_insert_load_per_thread_data(drcontext, ilist, where, reg);

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, reg,
			offsetof(ib_per_thread_t, instr_src_count), reg);
}

DR_EXPORT void ib_insert_get_num_srcs_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg) {

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, data_reg,
			offsetof(ib_per_thread_t, instr_src_count), res_reg);
}

DR_EXPORT size_t ib_get_num_dsts(void *drcontext) {

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return (size_t) instrum_data->instr_dst_count;
}

DR_EXPORT void ib_insert_get_num_dsts(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg) {

	ib_insert_load_per_thread_data(drcontext, ilist, where, reg);

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, reg,
			offsetof(ib_per_thread_t, instr_dst_count), reg);
}

DR_EXPORT void ib_insert_get_num_dsts_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg) {

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, data_reg,
			offsetof(ib_per_thread_t, instr_dst_count), res_reg);
}

DR_EXPORT app_pc ib_get_pc(void *drcontext) {

	return (app_pc) ib_tls_get_pc_data();
}

DR_EXPORT void ib_insert_get_pc(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg) {

	opnd_t pc_opnd = ib_tls_get_raw_slot_opnd(IB_RAW_SLOT_PC_DATA);
	ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &pc_opnd, reg);
}

DR_EXPORT int ib_get_opcode(void *drcontext) {

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return instrum_data->instr_opcode;
}

DR_EXPORT void ib_insert_get_opcode(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg) {

	ib_insert_load_per_thread_data(drcontext, ilist, where, reg);

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, reg,
			offsetof(ib_per_thread_t, instr_opcode), reg);
}

DR_EXPORT void ib_insert_get_opcode_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg) {

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, data_reg,
			offsetof(ib_per_thread_t, instr_opcode), res_reg);
}

DR_EXPORT uintptr_t ib_get_flags(void *drcontext) {

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return instrum_data->flag_value;
}

DR_EXPORT void ib_insert_get_flags(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg) {

	ib_insert_load_per_thread_data(drcontext, ilist, where, reg);

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, reg,
			offsetof(ib_per_thread_t, flag_value), reg);
}

DR_EXPORT void ib_insert_get_flags_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg) {

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, data_reg,
			offsetof(ib_per_thread_t, flag_value), res_reg);
}

DR_EXPORT opnd_t ib_insert_get_flags_opnd_ex(reg_id_t data_reg) {

	return OPND_CREATE_MEMPTR(data_reg,
			offsetof(ib_per_thread_t, flag_value));
}

DR_EXPORT void ib_load_flags(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t scratch_reg_xsp) {

	DR_ASSERT(scratch_reg_xsp == DR_REG_XSP);

	ib_insert_load_per_thread_data(drcontext, ilist, where, scratch_reg_xsp);

	ub_instrum_load_eflags(drcontext, ilist, where, scratch_reg_xsp,
			offsetof(ib_per_thread_t, flag_value));
}

static void ib_hp_insert_get_comp_x(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg,
		ub_opnd_access_t *comp_access_slot,
		opnd_t (*ib_get_comp_slot_x)(reg_id_t data_reg,
				ub_opnd_access_t *comp_access_slot)) {

	opnd_t access_opnd, opnd2;
	instr_t *instr;

	access_opnd = ib_get_comp_slot_x(data_reg, comp_access_slot);
	opnd2 = opnd_create_reg(res_reg);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd2, access_opnd);
	instrlist_meta_preinsert(ilist, where, instr);
}

static int ib_calculate_component_index(ub_opnd_access_t *opnd_access) {

	return (opnd_access->opnd_field * 5) + opnd_access->comp_field;
}

#ifdef DEBUG_CHECK_ASSESS
/** NEED TO CHECK IF PRESENT */

static void check_access(void *drcontext, ub_opnd_access_t *comp_access_slot) {

	app_pc pc = ib_get_pc(drcontext);
	instr_t instr;
	instr_init(drcontext, &instr);
	decode(drcontext, pc, &instr);

	if (ib_is_full_opnd_storage_enabled_for_instr(&instr)) {
		instr_free(drcontext, &instr);
		return;
	}

	ub_instr_dataflow_t instr_dataflow;
	ub_dataflow_get_info(&instr, &instr_dataflow);

	bool found = false;

	size_t num_opnds = instr_dataflow.num_opnds;

	for (uint i = 0; i < num_opnds; i++) {

		ub_opnd_access_t opnd_access = instr_dataflow.opnd_access[i];

		if (opnd_access.opnd_field == comp_access_slot->opnd_field
				&& opnd_access.comp_field == comp_access_slot->comp_field)
		found = true;
	}

	int u = 0;
	if (!found) {
		instr_disassemble(drcontext, &instr, STDERR);
		dr_fprintf(STDERR, "\n (%u %u)\n", comp_access_slot->opnd_field,
				comp_access_slot->comp_field);
		u = 8 / 0;

		DR_ASSERT(false);
	}

	instr_free(drcontext, &instr);
}

static void clean_entry_check(int opnd_field, int comp_field) {

	ub_opnd_access_t comp_access_slot;
	comp_access_slot.opnd_field = opnd_field;
	comp_access_slot.comp_field = comp_field;
	check_access(dr_get_current_drcontext(), &comp_access_slot);

}

#endif

DR_EXPORT uintptr_t ib_get_comp_opnd(void *drcontext,
		ub_opnd_access_t *comp_access_slot) {

#ifdef DEBUG_CHECK_ASSESS
	/** NEED TO CHECK IF PRESENT */

	check_access(drcontext, comp_access_slot);

#endif

	if (comp_access_slot->comp_field == UB_COMP_1) {

		if (comp_access_slot->opnd_field <= UB_SRC_OPND_3) {

			// TODO: Not sure about this assert. If it fails please contact me!
			DR_ASSERT(drcontext == dr_get_current_drcontext());

			int index = IB_RAW_SLOT_SRC_OPND_DATA_1
					+ comp_access_slot->opnd_field;
			DR_ASSERT(
					index >= IB_RAW_SLOT_SRC_OPND_DATA_1 && index <= IB_RAW_SLOT_SRC_OPND_DATA_3);

			return ib_tls_get_opnd_data(index);
		}

		if (comp_access_slot->opnd_field >= UB_DST_OPND_1
				&& comp_access_slot->opnd_field <= UB_DST_OPND_3) {

			// TODO: Not sure about this assert. If it fails please contact me!
			DR_ASSERT(drcontext == dr_get_current_drcontext());

			int offset = comp_access_slot->opnd_field - UB_DST_OPND_1;
			DR_ASSERT(offset >= 0);

			int index = IB_RAW_SLOT_DST_OPND_DATA_1 + offset;
			DR_ASSERT(
					index >= IB_RAW_SLOT_DST_OPND_DATA_1 && index <= IB_RAW_SLOT_DST_OPND_DATA_3);
			return ib_tls_get_opnd_data(index);

		}
	}

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return instrum_data->components[ib_calculate_component_index(
			comp_access_slot)].opnd;

}

DR_EXPORT void ib_insert_get_comp_opnd(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg, ub_opnd_access_t *comp_access_slot) {

	opnd_t access_opnd, opnd2;
	instr_t *instr;

#ifdef DEBUG_CHECK_ASSESS
	/** NEED TO CHECK IF PRESENT */

	dr_insert_clean_call(drcontext, ilist, where, clean_entry_check, false, 2,
			OPND_CREATE_INTPTR(comp_access_slot->opnd_field),
			OPND_CREATE_INTPTR(comp_access_slot->comp_field));
#endif

	if (!ib_get_fast_slot(comp_access_slot, &access_opnd)) {
		ib_insert_load_per_thread_data(drcontext, ilist, where, reg);
		access_opnd = ib_get_slow_comp_slot_opnd(reg, comp_access_slot);
	}

	opnd2 = opnd_create_reg(reg);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd2, access_opnd);
	instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT bool ib_insert_get_direct_opnd_to_comp_opnd(void *drcontext,
		ub_opnd_access_t *comp_access_slot, opnd_t *out_opnd) {

	if (!ib_get_fast_slot(comp_access_slot, out_opnd)) {
		return false;
	}

	return true;
}

DR_EXPORT void ib_insert_get_comp_opnd_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_data,
		ub_opnd_access_t *comp_access_slot) {

	/* TODO: FIX to map ib_insert_get_comp_opnd */
	DR_ASSERT(false);

	ib_hp_insert_get_comp_x(drcontext, ilist, where, data_reg, res_data,
			comp_access_slot, ib_get_slow_comp_slot_opnd);
}

DR_EXPORT uintptr_t ib_get_comp_size(void *drcontext,
		ub_opnd_access_t *comp_access_slot) {

#ifdef DEBUG_CHECK_ASSESS
	/** NEED TO CHECK IF PRESENT */

	check_access(drcontext, comp_access_slot);

#endif

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return instrum_data->components[ib_calculate_component_index(
			comp_access_slot)].size;
}

DR_EXPORT void ib_insert_get_comp_size(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg, ub_opnd_access_t *comp_access_slot) {

#ifdef DEBUG_CHECK_ASSESS
	/** NEED TO CHECK IF PRESENT */

	check_access(drcontext, comp_access_slot);

#endif

	ib_insert_load_per_thread_data(drcontext, ilist, where, reg);
	ib_hp_insert_get_comp_x(drcontext, ilist, where, reg, reg, comp_access_slot,
			ib_get_comp_slot_size);
}

DR_EXPORT void ib_insert_get_comp_size_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg,
		ub_opnd_access_t *comp_access_slot) {

	ib_hp_insert_get_comp_x(drcontext, ilist, where, data_reg, res_reg,
			comp_access_slot, ib_get_comp_slot_size);
}

DR_EXPORT byte *ib_get_comp_conc(void *drcontext,
		ub_opnd_access_t *comp_access_slot) {

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return instrum_data->components[ib_calculate_component_index(
			comp_access_slot)].conc;
}

DR_EXPORT void ib_insert_get_comp_conc(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg, size_t opnd_size,
		ub_opnd_access_t *comp_access_slot, size_t disp) {

#ifdef DEBUG_CHECK_ASSESS
	/** NEED TO CHECK IF PRESENT */

	dr_insert_clean_call(drcontext, ilist, where, clean_entry_check, false, 2,
			OPND_CREATE_INTPTR(comp_access_slot->opnd_field),
			OPND_CREATE_INTPTR(comp_access_slot->comp_field));
#endif

	ib_insert_load_per_thread_data(drcontext, ilist, where, reg);

	opnd_t access_opnd, opnd2;
	instr_t *instr;

	access_opnd = ib_get_comp_slot_conc(reg, opnd_size, comp_access_slot, disp);
	opnd2 = opnd_create_reg(reg);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd2, access_opnd);
	instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ib_insert_get_comp_conc_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg, size_t opnd_size,
		ub_opnd_access_t *comp_access_slot, size_t disp) {

	opnd_t access_opnd, opnd2;
	instr_t *instr;

	access_opnd = ib_get_comp_slot_conc(data_reg, opnd_size, comp_access_slot,
			disp);
	opnd2 = opnd_create_reg(res_reg);

	if (opnd_size <= 2) {

		instr = INSTR_CREATE_movzx(drcontext, opnd2, access_opnd);
	} else {
		instr = INSTR_CREATE_mov_ld(drcontext, opnd2, access_opnd);

	}
	instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT opnd_t ib_get_comp_conc_opnd_ex(reg_id_t data_reg, size_t opnd_size,
		ub_opnd_access_t *comp_access_slot, size_t disp) {

	return ib_get_comp_slot_conc(data_reg, opnd_size, comp_access_slot, disp);

}

DR_EXPORT loc_t ib_get_comp_type(void *drcontext,
		ub_opnd_access_t *comp_access_slot) {

#ifdef DEBUG_CHECK_ASSESS
	/** NEED TO CHECK IF PRESENT */

	check_access(drcontext, comp_access_slot);

#endif

	ib_per_thread_t *instrum_data = (ib_per_thread_t *) ib_get_thread_data(
			drcontext);
	return instrum_data->components[ib_calculate_component_index(
			comp_access_slot)].type;
}

DR_EXPORT void ib_insert_get_comp_type(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg, ub_opnd_access_t *comp_access_slot) {

#ifdef DEBUG_CHECK_ASSESS
	/** NEED TO CHECK IF PRESENT */

	dr_insert_clean_call(drcontext, ilist, where, clean_entry_check, false, 2,
			OPND_CREATE_INTPTR(comp_access_slot->opnd_field),
			OPND_CREATE_INTPTR(comp_access_slot->comp_field));
#endif

	ib_insert_load_per_thread_data(drcontext, ilist, where, reg);
	ib_hp_insert_get_comp_x(drcontext, ilist, where, reg, reg, comp_access_slot,
			ib_get_comp_slot_type);
}

DR_EXPORT void ib_insert_get_comp_type_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t data_reg, reg_id_t res_reg,
		ub_opnd_access_t *comp_access_slot) {

	ib_hp_insert_get_comp_x(drcontext, ilist, where, data_reg, res_reg,
			comp_access_slot, ib_get_comp_slot_type);
}

/**********************************************************************************
 * Fault handler
 */

/*
 *
 * The issue is that if the app address is faulty, such as NULL, we need
 * to handle/suppress the fault triggered when getting the conc value.
 *
 * Restoration of app regs is done by drreg so no problems there. However, the fault handler
 * needs to identify that it's an instruction for storing the conc value and simply skip the
 * instruction.
 *
 */

static dr_signal_action_t ib_raw_conc_invalid_event_signal(void *drcontext,
		dr_siginfo_t *info) {

	if (info->sig == SIGSEGV || info->sig == SIGBUS) {
		byte *target = info->access_address;

		bool is_conc_dst_operand = false;

		/* We only check sources for now */

		ub_opnd_access_t slot;

		slot.opnd_field = UB_SRC_OPND_1;
		slot.comp_field = UB_COMP_1;

		while (slot.opnd_field < UB_NUM_OF_SRC_FIELDS) {

			/* Check if the destination is the comp conc buffer addr */
			byte *conc_addr = ib_get_comp_conc(drcontext, &slot);

			if (target == conc_addr) {
				is_conc_dst_operand = true;
				break;
			}

			slot.opnd_field++;
		}

		if (is_conc_dst_operand) {
			// We skip the instruction
			return DR_SIGNAL_REDIRECT;
		}
	}

	return DR_SIGNAL_DELIVER;
}
