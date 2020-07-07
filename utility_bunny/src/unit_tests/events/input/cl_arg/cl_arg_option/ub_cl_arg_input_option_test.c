/**
 *  @file ub_cl_arg_input_option_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../../events/input/cl_arg/cl_arg_option/ub_cl_arg_input_option.h"

static void test1() {

	DR_ASSERT_MSG(
			ub_cl_arg_options_is_handle_0th_arg_enabled(UB_EV_CL_ARG_INPUT_OPT_BARE) == false,
			"ub_cl_arg_input_option_test - 0 failed...");

	DR_ASSERT_MSG(
			ub_cl_arg_options_is_handle_0th_arg_enabled(UB_EV_CL_ARG_INPUT_OPT_HANDLE_0TH) == true,
			"ub_cl_arg_input_option_test - 1 failed...");

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
}
