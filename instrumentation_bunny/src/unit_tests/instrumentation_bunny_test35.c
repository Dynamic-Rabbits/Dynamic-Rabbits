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

static int tls_idx = -1;

static void ib_test_thread_init(void *drcontext) {

	drmgr_set_tls_field(drcontext, tls_idx, (void *) (uintptr_t) 0);
}

static void ib_test_thread_exit(void *drcontext) {

}

void ib_spill_regs_func_test(void *drcontext, instrlist_t *ilist,
		instr_t *where, void *user_data, void **spill_user_data) {

	spilled = true;

	DR_ASSERT_MSG(*spill_user_data == (void *) 87879,
			"ub_code_cache_test - test2 failed...");

	dr_save_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_restore_regs_func_test(void *drcontext, instrlist_t *ilist,
		instr_t *where, void *user_data, void *spill_user_data) {

	DR_ASSERT_MSG(spill_user_data == (void *) 87879,
			"ub_code_cache_test - test2 failed...");

	restored = true;
	dr_restore_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_clean_call(app_pc value) {

	clean_called_1 = true;

	int i = (intptr_t) (void *) drmgr_get_tls_field(dr_get_current_drcontext(),
			tls_idx);

	DR_ASSERT_MSG(i == 1, "ub_code_cache_test - test3 failed...");

	DR_ASSERT_MSG(ib_get_opcode(dr_get_current_drcontext()) == OP_mov_st,
			"ub_code_cache_test - test3 failed...");
	DR_ASSERT_MSG(ib_get_num_dsts(dr_get_current_drcontext()) == 1,
			"ub_code_cache_test - test3 failed...");
	DR_ASSERT_MSG(ib_get_num_srcs(dr_get_current_drcontext()) == 1,
			"ub_code_cache_test - test3 failed...");
}

void ib_code_cache_insert_hndle_func_test(void *drcontext, instrlist_t *bb,
		instr_t *where, instr_t *app, void *user_data, void *spill_data) {

	DR_ASSERT_MSG(user_data == (void *) 8,
			"ub_code_cache_test - test2 failed...");

	DR_ASSERT_MSG(spill_data == (void *) 87879,
			"ub_code_cache_test - test2 failed...");

	count++;
	dr_insert_clean_call(drcontext, bb, where, ib_clean_call, false, 1,
			OPND_CREATE_INTPTR(instr_get_app_pc(where)));
}

static void event_exit() {

	DR_ASSERT_MSG(count > 0, "ub_code_cache_test - test34 failed...");
	DR_ASSERT_MSG(clean_called_1 == true,
			"ub_code_cache_test - test34 failed...");
	DR_ASSERT_MSG(spilled == true, "ub_code_cache_test - test34 failed...");
	DR_ASSERT_MSG(restored == true, "ub_code_cache_test - test34 failed...");

	if (!drmgr_unregister_thread_init_event(ib_test_thread_init)
			|| !drmgr_unregister_thread_exit_event(ib_test_thread_exit))
		DR_ASSERT(false);
	drmgr_unregister_tls_field(tls_idx);

	ib_unregister_instrum_tool(instrum_tool);
	ib_exit();
	drmgr_exit();
}

/** DUMMIES */

bool create_default_manager(void *drbbdup_ctx, void *drcontext, void *tag,
		instrlist_t *bb, bool *enable_dynamic_fp,
		uint *default_case_value, void *user_data) {

	DR_ASSERT(user_data == (void *) 888);
	*default_case_value = 0;
	ib_register_case_value(drbbdup_ctx, 1);

	return true;
}

size_t analyse_bb(void *drcontext, instrlist_t *bb, uint case_val,
		void *user_data, drvector_t *action, void *pre_analysis_data,
		void **post_data) {

	DR_ASSERT(user_data == (void *) 888);
	DR_ASSERT(pre_analysis_data == NULL);

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

void ib_clean_call_comparator(reg_id_t reg) {

	dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
	dr_get_mcontext(dr_get_current_drcontext(), &mcontext);

	int i = (intptr_t) (void *) drmgr_get_tls_field(dr_get_current_drcontext(),
			tls_idx);

	i++;
	if (i > 1) {
		i = 0;
	}

	drmgr_set_tls_field(dr_get_current_drcontext(), tls_idx, (void *) i);

	drbbdup_set_comparator((void *) (intptr_t) i);
}

void get_comparator(void *drcontext, instrlist_t *bb, instr_t *where,
		void *user_data, void *pre_analysis_data) {

	DR_ASSERT(user_data == (void *) 888);

	dr_insert_clean_call(drcontext, bb, where, ib_clean_call_comparator, false,
			0);
}

void destroy_manager_data_dummy(void *user_data) {

	DR_ASSERT(user_data == (void *) 888);
}

void destroy_case_data_dummy(void *user_data) {

	DR_ASSERT(user_data == (void *) 771);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();
	ib_init(NULL);

	ib_dup_opts_t dup_opts = { create_default_manager, NULL, NULL, analyse_bb,
			get_comparator, NULL, NULL, (void *) 888 };
	instrum_tool = ib_register_instrum_tool_ex(&dup_opts, NULL);

	ib_insert_hndle_data_t cc_data;
	cc_data.user_data = (void *) 8;
	cc_data.user_instrum_func = ib_code_cache_insert_hndle_func_test;
	cc_data.spill_reg_func = ib_spill_regs_func_test;
	cc_data.restore_reg_func = ib_restore_regs_func_test;
	cc_data.spilling_user_data = (void *) 87879;

	if (!drmgr_register_thread_init_event(ib_test_thread_init)
			|| !drmgr_register_thread_exit_event(ib_test_thread_exit))
		DR_ASSERT(false);
	tls_idx = drmgr_register_tls_field();
	if (tls_idx == -1)
		DR_ASSERT(false);

	ib_hook_cache_to_instr(instrum_tool, OP_mov_st, &cc_data,
			IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO | IB_OPT_OPCODE_INFO
					| IB_OPT_FULL_OPND_INFO | IB_OPT_OPND_COUNT_INFO
					| IB_OPT_OPCODE_INFO);

	dr_register_exit_event(event_exit);
}
