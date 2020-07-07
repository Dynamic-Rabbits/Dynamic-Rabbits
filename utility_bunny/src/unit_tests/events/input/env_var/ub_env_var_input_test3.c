/**
 *  @file ub_env_var_input_test3.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../events/input/env_var/ub_event_env_var_input.h"
#include <string.h>

int count = 0;

void got_env_var_data(ub_ev_env_var_data_t *data) {

	count++;
}

static void event_exit() {

	DR_ASSERT_MSG(count == 0,
			"ub_env_var_input_option_test - test1 - 2 failed...");

	ub_ev_env_var_input_destroy_ctx();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	ub_ev_env_var_input_init_ctx(got_env_var_data,
			false, UB_EV_ENV_VAR_INPUT_OPT_BARE);

	ub_ev_env_var_input_register_env_var("NO_NO_NO");

	dr_register_exit_event(event_exit);
}
