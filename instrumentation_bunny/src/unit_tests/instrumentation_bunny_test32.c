#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "instrumentation_bunny.h"
#include "drvector.h"
#include <string.h>

int count = 0;

void *instrum_tool;

bool clean_called_1 = false;
bool spilled = false;
bool restored = false;

void ib_spill_regs_func_test(void *drcontext, instrlist_t *ilist,
		instr_t *where, void *user_data, void **spill_user_data) {

	spilled = true;

	dr_save_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_restore_regs_func_test(void *drcontext, instrlist_t *ilist,
		instr_t *where, void *user_data, void *spill_user_data) {

	restored = true;
	dr_restore_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_clean_call(int value) {

	clean_called_1 = true;
	DR_ASSERT_MSG(value == 4, "ub_code_cache_test - test3 failed...");

	DR_ASSERT_MSG(ib_get_opcode(dr_get_current_drcontext()) == OP_mov_st,
			"ub_code_cache_test - test3 failed...");
	DR_ASSERT_MSG(ib_get_num_dsts(dr_get_current_drcontext()) == 1,
			"ub_code_cache_test - test3 failed...");
	DR_ASSERT_MSG(ib_get_num_srcs(dr_get_current_drcontext()) == 1,
			"ub_code_cache_test - test3 failed...");
}

void ib_code_cache_insert_hndle_func_test(void *drcontext, instrlist_t *bb,
		instr_t *where, instr_t *app, void *user_data, void *spilling_data) {

	DR_ASSERT_MSG(user_data == (void *) 8,
			"ub_code_cache_test - test2 failed...");

	count++;
	dr_insert_clean_call(drcontext, bb, where, ib_clean_call, false, 1,
			OPND_CREATE_INTPTR(4));
}

static void event_exit() {

	DR_ASSERT_MSG(count > 0, "ub_code_cache_test - test32 failed...");
	DR_ASSERT_MSG(clean_called_1 == true,
			"ub_code_cache_test - test4 failed...");
	DR_ASSERT_MSG(spilled == true, "ub_code_cache_test - test32 failed...");
	DR_ASSERT_MSG(restored == true, "ub_code_cache_test - test32 failed...");

	ib_unregister_instrum_tool(instrum_tool);
	ib_exit();
	drmgr_exit();
}

/** DUMMIES */

bool create_default_manager(void *drbbdup_ctx, void *drcontext, void *tag,
		instrlist_t *bb, bool *enable_dynamic_fp,
		uint *default_case_value, void *user_data) {

	*default_case_value = 0;
	ib_register_case_value(drbbdup_ctx, 1);
	return true;
}

size_t analyse_bb(void *drcontext, instrlist_t *bb, uint case_val,
		void *user_data, drvector_t *action, void *pre_analysis_data,
		void **post_data) {

	DR_ASSERT(pre_analysis_data == NULL);

	size_t index = 0;

	instr_t *instr = instrlist_first(bb);

	while (instr) {
		DR_ASSERT(instr_is_app(instr));

		if (instr_get_opcode(instr) != OP_mov_st) {
			bool succ = drvector_set_entry(action, index,
					(void *) IB_INSTRUM_ACTION_SKIP);
			DR_ASSERT(succ);
		} else {

			bool succ = drvector_set_entry(action, index,
					(void *) IB_INSTRUM_ACTION_APPLY);
			DR_ASSERT(succ);
		}

		index++;
		instr = instr_get_next(instr);
	}

	return index;
}

void get_comparator(void *drcontext, instrlist_t *bb, instr_t *where,
		void *user_data, void *pre_analysis_data) {

	DR_ASSERT(pre_analysis_data == NULL);

	opnd_t comparator_opnd = drbbdup_get_comparator_opnd();
	ub_instrum_clear_mem_opnd(drcontext, bb, where, &comparator_opnd);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();
	ib_init(NULL);

	ib_dup_opts_t dup_opts = { create_default_manager, NULL, NULL, analyse_bb,
			get_comparator, NULL, NULL, NULL };
	instrum_tool = ib_register_instrum_tool_ex(&dup_opts, NULL);

	ib_insert_hndle_data_t cc_data;
	cc_data.user_data = (void *) 8;
	cc_data.user_instrum_func = ib_code_cache_insert_hndle_func_test;
	cc_data.spill_reg_func = ib_spill_regs_func_test;
	cc_data.restore_reg_func = ib_restore_regs_func_test;
	cc_data.spilling_user_data = NULL;

	ib_hook_cache_to_instr(instrum_tool, OP_mov_st, &cc_data,
			IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO | IB_OPT_OPCODE_INFO
					| IB_OPT_FULL_OPND_INFO | IB_OPT_OPND_COUNT_INFO
					| IB_OPT_OPCODE_INFO);

	dr_register_exit_event(event_exit);
}
