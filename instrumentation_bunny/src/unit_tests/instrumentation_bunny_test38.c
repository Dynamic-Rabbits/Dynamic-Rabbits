#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "instrumentation_bunny.h"
#include "drvector.h"
#include <string.h>

void* instrum_tool = NULL;

static void event_exit() {

	ib_unregister_instrum_tool(instrum_tool);
	ib_exit();
	drmgr_exit();
}

/** DUMMIES */

static bool create_default_manager(void *drbbdup_ctx, void *drcontext,
		void *tag, instrlist_t *bb, bool *enable_dynamic_fp,
		uint *default_case_value, void *user_data) {

	*default_case_value = 0;

	ib_register_case_value(drbbdup_ctx, 1);

	return true;
}

static size_t analyse_bb(void *drcontext, instrlist_t *bb, uint case_val,
		void *user_data, drvector_t *action, void *pre_analysis_data,
		void **post_data) {


	if (case_val == 0){
		*post_data = (void *) 7;
	}else{
		*post_data = (void *) 8238;
	}
	size_t index = 0;

	if (case_val == 0) {

		instr_t *instr = instrlist_first(bb);
		while (instr != NULL) {
			bool succ = drvector_set_entry(action, index,
					(void *) IB_INSTRUM_ACTION_SKIP);
			DR_ASSERT(succ);

			index++;
			instr = instr_get_next(instr);
		}
	} else if (case_val == 1) {

		instr_t *instr = instrlist_first(bb);
		while (instr != NULL) {

			bool succ = drvector_set_entry(action, index,
					(void *) IB_INSTRUM_ACTION_APPLY);
			DR_ASSERT(succ);

			index++;
			instr = instr_get_next(instr);
		}
	}

	return index;
}

static void get_comparator(void *drcontext, instrlist_t *bb, instr_t *where,
		void *user_data, void *pre_analysis_data) {

	opnd_t cmp_opnd = drbbdup_get_comparator_opnd();
	ub_instrum_clear_mem_opnd(drcontext, bb, where, &cmp_opnd);
}

int cc = 0;

void ib_clean_call() {

	cc++;
}

static void ib_fail() {

	DR_ASSERT(false);
}

void ib_code_cache_insert_hndle_func_test(void *drcontext, instrlist_t *bb,
		instr_t *where, instr_t *app, void *user_data, void *spilling_data) {

	dr_insert_clean_call(drcontext, bb, where, ib_clean_call, false, 0);
}

void ib_post_handling_test(void *drcontext, instrlist_t *bb, instr_t *where,
		uint case_val, void *user_data, void *pre_analysis_data, void *post_data) {

	if (case_val != 0) {
		DR_ASSERT(post_data == (void *) 8238);
		DR_ASSERT(user_data == (void *) 7);
		dr_insert_clean_call(drcontext, bb, where, ib_fail, false, 0);
	}else{
		DR_ASSERT(post_data == (void *) 7);

	}
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();
	ib_init(NULL);

	ib_dup_opts_t dup_opts = { create_default_manager, NULL, NULL, analyse_bb,
			get_comparator, NULL, ib_post_handling_test, (void *) 7 };
	instrum_tool = ib_register_instrum_tool_ex(&dup_opts, NULL);

	ib_insert_hndle_data_t inline_data;
	inline_data.user_data = (void *) 8;
	inline_data.user_instrum_func = ib_code_cache_insert_hndle_func_test;
	inline_data.spill_reg_func = NULL;
	inline_data.restore_reg_func = NULL;
	inline_data.spilling_user_data = NULL;

	ib_hook_to_default(instrum_tool, &inline_data,
			IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO | IB_OPT_OPCODE_INFO
					| IB_OPT_FULL_OPND_INFO | IB_OPT_OPND_COUNT_INFO);

	dr_register_exit_event(event_exit);
}
