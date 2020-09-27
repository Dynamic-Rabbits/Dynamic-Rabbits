/**
 *  @file ub_event_file_input_test2.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

void *socket_input_ctx;
int count = 0;

static void got_read(ub_fd_input_data_t *input_data) {

	count++;

	DR_ASSERT_MSG(input_data->buf_list != NULL,
			"ub_file_input_option_test8 - test1 - 0 failed...");

	DR_ASSERT_MSG(ub_list_get_size(input_data->buf_list) == 1,
			"ub_file_input_option_test8 - test1 - 1 failed...");

	ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 0);

	DR_ASSERT_MSG(memcmp(input_buf->buf, "Hello there!", input_buf->size) == 0,
			"ub_env_var_input_option_test - test1 - 2 failed...");

	DR_ASSERT_MSG(input_data->offset == 0,
			"ub_env_var_input_option_test - test1 - 3 failed...");

	DR_ASSERT_MSG(input_buf->size == 12,
			"ub_env_var_input_option_test - test1 - 4 failed...");

	DR_ASSERT_MSG(strcmp(input_data->source_info.file_info.base_name, "ub_file_input_test1.txt") == 0,
			"ub_env_var_input_option_test - test1 - 5 failed...");
}

static void event_exit() {

	DR_ASSERT_MSG(count == 1,
			"ub_event_file_input_test2 - test2 - 1 failed...");
	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_read, false,
	UB_EV_FD_INPUT_OPT_FILE | UB_EV_FD_INPUT_OPT_OFFSET | UB_EV_FD_INPUT_OPT_SOURCE_INFO, id);

	ub_ev_fd_input_register_file(socket_input_ctx, "ub_file_input_test1.txt");

	dr_register_exit_event(event_exit);
}
