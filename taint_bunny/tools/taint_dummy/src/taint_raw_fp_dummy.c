/*
 * taint_raw_fp_dummy.c
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

    DR_ASSERT(argc == 6);

    tb_raw_taint_policy_t taint_policy;
    tb_raw_initialise_tree_taint_policy(&taint_policy);

    tb_options_t te_options;
    te_options.enable_taint_off = false;
    te_options.enable_inline = false;
    te_options.enable_fp = true;

    tb_fp_settings_t settings;
    // Arg 1 - dups
    settings.dups_limit = (int)  strtol(argv[1], NULL, 10);
    // Arg 2 - size
    settings.required_size = (int)  strtol(argv[2], NULL, 10);
    // Arg 3 - Dynamic hit-count
    settings.dynamic_path_hit_threshold = (ushort) strtol(argv[3], NULL, 10);
    // Arg 4 - bb_in_out_threshold. TODO: switch to strtod
    settings.bb_in_out_threshold = (float)  atof(argv[4]);
    // Arg 5 - pop
    settings.pop_limit = (int)  strtol(argv[5], NULL, 10);

    taint_bunny = tb_raw_init(id, IB_OPT_BARE, &te_options, &settings,
            &taint_policy);
    tb_register_hooks(taint_bunny);

    taint_dummy_intro_init(id, tb_raw_tree_get_inc_default_label, false);

    dr_register_exit_event(event_exit);
}
