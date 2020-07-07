/**
 *  @file ub_env_var_input_option_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../../events/input/env_var/env_var_option/ub_env_var_input_option.h"

static void test1() {

	DR_ASSERT_MSG(
			ub_env_var_options_is_var_name_enabled(UB_EV_ENV_VAR_INPUT_OPT_BARE) == false,
			"ub_env_var_input_option_test - test1 - 0 failed...");

	DR_ASSERT_MSG(
			ub_env_var_options_is_var_name_enabled(UB_EV_ENV_VAR_INPUT_OPT_VAR) == true,
			"ub_env_var_input_option_test - test1 - 1 failed...");

	DR_ASSERT_MSG(
			ub_env_var_options_is_var_name_enabled(UB_EV_ENV_VAR_INPUT_OPT_BARE | UB_EV_ENV_VAR_INPUT_OPT_VAR) == true,
			"ub_env_var_input_option_test - test1 - 0 failed...");

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
}

