#include "dr_defines.h"
#include "taint_dummy_helper.h"
#include "taint_bunny.h"
#include <inttypes.h>
#include <string.h>

void *taint_bunny;

int policy_case = 0;

static void event_exit() {

	taint_dummy_exit();
	tb_raw_exit(taint_bunny);
	ib_exit();

	if (policy_case == 3) {
		tb_raw_destroy_tree_taint_policy();
	}

	drmgr_exit();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();
	ib_init(NULL);

	DR_ASSERT(argc == 3);

	tb_raw_taint_policy_t taint_policy;

	// TODO use dr opts
	// This is buggy as hell and I am trusting the user. Fix me!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (strcmp(argv[1], "bitwise") == 0) {
		tb_raw_initialise_bitwise_taint_policy(&taint_policy);
		policy_case = 0;
	} else if (strcmp(argv[1], "id") == 0) {
		tb_raw_initialise_id_taint_policy(&taint_policy);
		policy_case = 1;
	} else if (strcmp(argv[1], "dummy") == 0) {
		tb_raw_initialise_dummy_taint_policy(&taint_policy);
		policy_case = 2;
	} else if (strcmp(argv[1], "bitvect") == 0) {
		tb_raw_initialise_tree_taint_policy(&taint_policy);
		policy_case = 3;
	} else {
		DR_ASSERT_MSG(false, "Invalid Prop Logic.\n");
	}

	tb_options_t te_options;
	te_options.enable_taint_off = false;
	te_options.enable_inline = false;

	if (strcmp(argv[2], "1") == 0) {
		te_options.enable_fp = true;
	} else if (strcmp(argv[2], "0") == 0) {
		te_options.enable_fp = false;
	} else {
		DR_ASSERT_MSG(false, "Invalid fast path option\n");
	}

	taint_bunny = tb_raw_init(id, IB_OPT_BARE, &te_options, NULL,
			&taint_policy);
	tb_register_hooks(taint_bunny);

	if (policy_case == 3) {
		taint_dummy_intro_init(id, tb_raw_tree_get_inc_default_label, false);
	} else {
		taint_dummy_intro_init(id, taint_policy.get_default_label, false);
	}

	dr_register_exit_event(event_exit);
}
