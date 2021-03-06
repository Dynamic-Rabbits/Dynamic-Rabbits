#include "dr_defines.h"
#include "taint_dummy_helper.h"
#include "taint_bunny.h"
#include <inttypes.h>
#include <string.h>

void *taint_bunny;
int policy_case = 0;

static void event_exit() {

    taint_dummy_exit();
    tb_cc_exit(taint_bunny);
    ib_exit();

    /* Clean up taint policy */
    if (policy_case == 3) {
        tb_cc_destroy_bitvector_tree_taint_policy();
    }

    drmgr_exit();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    ib_init(NULL);

    DR_ASSERT(argc == 3);

    tb_cc_taint_policy_t taint_policy;
    if (strcmp(argv[1], "bitwise") == 0) {
        policy_case = 0;
        tb_cc_initialise_bitwise_taint_policy(&taint_policy);
    } else if (strcmp(argv[1], "set") == 0) {
        policy_case = 1;
        tb_cc_initialise_set_taint_policy(&taint_policy);
    } else if (strcmp(argv[1], "id") == 0) {
        policy_case = 2;
        tb_cc_initialise_id_taint_policy(&taint_policy);
    } else if (strcmp(argv[1], "bitvect") == 0) {
        policy_case = 3;
        tb_cc_initialise_bitvector_tree_taint_policy(&taint_policy);
    } else if (strcmp(argv[1], "dummy") == 0) {
        policy_case = 4;
        tb_cc_initialise_dummy_taint_policy(&taint_policy);
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

    taint_bunny = tb_cc_init(id, IB_OPT_BARE, &te_options, NULL, &taint_policy);
    tb_register_hooks(taint_bunny);

	if (policy_case == 3) {
		taint_dummy_intro_init(id, tb_cc_tree_get_inc_default_label, false);
	} else {
		taint_dummy_intro_init(id, taint_policy.get_default_label, false);
	}

    dr_register_exit_event(event_exit);
}
