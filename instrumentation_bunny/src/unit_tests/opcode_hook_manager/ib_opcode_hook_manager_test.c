/**
 *  @file ib_opcode_hook_manager_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "instrumentation_bunny.h"
#include "../../opcode_hook_manager/ib_opcode_hook_manager.h"
#include <string.h>

void ib_code_cache_insert_hndle_func_test(void *h, instrlist_t *f, instr_t *a,
		void *user_data) {

	dr_fprintf(STDERR, "Nothing!");
}

static void test1() {

	ib_code_cache_manager_init();
	void *opcode_hook_mngr = ib_opcode_hook_mngr_create();

	DR_ASSERT_MSG(opcode_hook_mngr,
			"ib_opcode_hook_manager_test - test1 failed...");

	ib_opcode_hook_mngr_destroy(opcode_hook_mngr);
	ib_code_cache_manager_destroy();

}

static void test2() {

	ib_code_cache_manager_init();
	void *opcode_hook_mngr = ib_opcode_hook_mngr_create();

	ib_opcode_hook_mngr_register_instrum_tool(opcode_hook_mngr, 7);

	bool value = ib_opcode_hook_mngr_unregister_instrum_tool(opcode_hook_mngr,
			7);
	DR_ASSERT_MSG(value, "ib_opcode_hook_manager_test - test2 failed...");

	ib_opcode_hook_mngr_destroy(opcode_hook_mngr);
	ib_code_cache_manager_destroy();

}

static void test3() {

	ib_code_cache_manager_init();
	void *opcode_hook_mngr = ib_opcode_hook_mngr_create();

	ib_opcode_hook_mngr_register_instrum_tool(opcode_hook_mngr, 7);

	bool value = ib_opcode_hook_mngr_unregister_instrum_tool(opcode_hook_mngr,
			7);
	DR_ASSERT_MSG(value, "ib_opcode_hook_manager_test - test3 failed...");

	ib_opcode_hook_mngr_destroy(opcode_hook_mngr);
	ib_code_cache_manager_destroy();

}


DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
}
