/**
 *  @file ub_cl_arg_input_test4.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../events/input/cl_arg/ub_event_cl_arg_input.h"
#include "../../../../readers/ub_file_reader.h"
#include <string.h>

int count = 0;
bool seen1 = false;
bool seen2 = false;
void *cl_arg_input_ctx;

void got_cl_data(ub_ev_cl_arg_data_t *data) {

	count++;

	if (data->index == 1) {

		dr_fprintf(STDERR, "The value is %s\n", data->arg);

		DR_ASSERT_MSG(strcmp(data->arg, "Test1") == 0,
				"ub_cl_arg_input_option_tes4 - 1 failed...");

		seen1 = true;

	} else if (data->index == 2) {

		DR_ASSERT_MSG(strcmp(data->arg, "Test2") == 0,
				"ub_cl_arg_input_option_tes4 - 2 failed...");

		seen2 = true;
	}
}

static void event_exit() {

	DR_ASSERT_MSG(seen1, "ub_cl_arg_input_option_test4 - 3 failed...");
	DR_ASSERT_MSG(seen2, "ub_cl_arg_input_option_test4 - 4 failed...");
	DR_ASSERT_MSG(count == 2, "ub_cl_arg_input_option_test4 - 5 failed...");

	ub_ev_cl_arg_input_destroy_ctx(cl_arg_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	cl_arg_input_ctx = ub_ev_cl_arg_input_init_ctx(got_cl_data, true,
			UB_EV_CL_ARG_INPUT_OPT_BARE);

	ub_ev_cl_arg_input_parse(cl_arg_input_ctx);

	dr_register_exit_event(event_exit);
}
