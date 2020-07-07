/**
 *  @file ub_env_var_input_test.c
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

	DR_ASSERT_MSG(strcmp(data->value, "THIS IS THE TEST!") == 0,
			"ub_env_var_input_option_test - test1 - 0 failed...");

	DR_ASSERT_MSG(strcmp(data->variable_name, "HELLO_TEST") == 0,
			"ub_env_var_input_option_test - test1 - 1 failed...");
}

static void event_exit() {

	DR_ASSERT_MSG(count == 1,
			"ub_env_var_input_option_test - test1 - 2 failed...");

	ub_ev_env_var_input_destroy_ctx();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	ub_ev_env_var_input_init_ctx(got_env_var_data,
	true, UB_EV_ENV_VAR_INPUT_OPT_VAR);

	dr_register_exit_event(event_exit);

}
