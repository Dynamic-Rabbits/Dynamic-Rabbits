/**
 *  @file ub_event_file_input_test8.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

void *socket_input_ctx;
int count = 0;
bool read1 = false;
bool read2 = false;

int fd1;

static void got_read(ub_fd_input_data_t *input_data) {

	count++;

	DR_ASSERT_MSG(input_data->buf_list != NULL,
			"ub_file_input_option_test8 - 0 failed...");

	DR_ASSERT_MSG(ub_list_get_size(input_data->buf_list) == 1,
			"ub_file_input_option_test8 - 1 failed...");

	ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 0);

	if (input_data->offset == 0) {

		fd1 = input_data->fd;

		read1 = true;

		DR_ASSERT_MSG(memcmp(input_buf->buf, "H", input_buf->size) == 0,
				"ub_file_input_option_test8 - 2 failed...");

		DR_ASSERT_MSG(input_buf->size == 1,
				"ub_file_input_option_test8 - 3 failed...");
	} else if (input_data->offset == 1) {

		read2 = true;

		DR_ASSERT_MSG(read1 == true,
				"ub_env_var_input_option_test8 - test2 - 0 failed...");

		DR_ASSERT_MSG(memcmp(input_buf->buf, "e", input_buf->size) == 0,
				"ub_env_var_input_option_test7 - test2 - 1 failed...");
	}
}

static void event_exit() {

	DR_ASSERT_MSG(count >= 1,
			"ub_event_file_input_test8 - test3 - 0 failed...");

	DR_ASSERT_MSG(read2 == true,
			"ub_event_file_input_test8 - test3 - 1 failed...");

	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_read, false,
			UB_EV_FD_INPUT_OPT_FILE | UB_EV_FD_INPUT_OPT_SOURCE_INFO
					| UB_EV_FD_INPUT_OPT_OFFSET, id);

	ub_ev_fd_input_register_file(socket_input_ctx, "ub_file_input_test1.txt");

	dr_register_exit_event(event_exit);
}

