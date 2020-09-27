/*
 * taint_sample_dummy.c
 *
 *      Author: john
 */

#include "dr_defines.h"
#include "taint_dummy_helper.h"
#include "taint_bunny.h"
#include <inttypes.h>
#include <string.h>

void *taint_bunny;

static void event_exit() {

	taint_dummy_exit();
	tb_raw_exit(taint_bunny);
	ib_exit();

	tb_raw_destroy_tree_taint_policy();

	drmgr_exit();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();
	ib_init(NULL);

	tb_raw_taint_policy_t taint_policy;

	tb_raw_initialise_tree_taint_policy(&taint_policy);

	taint_bunny = tb_raw_init_default(id, &taint_policy);

	tb_register_hooks(taint_bunny);

	taint_dummy_intro_init(id, tb_raw_tree_get_inc_default_label, true);

	dr_register_exit_event(event_exit);
}
