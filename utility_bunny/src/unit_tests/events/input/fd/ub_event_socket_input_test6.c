/**
 *  @file ub_event_socket_input_test6.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

void *socket_input_ctx;
int count = 0;
bool saw_first = false;
bool saw_second = false;

static void got_read(ub_fd_input_data_t *input_data) {

	count++;

	if (!saw_first) {

		DR_ASSERT_MSG(input_data->buf_list != NULL,
				"ub_socket_input_test1 - 0 failed...");

		DR_ASSERT_MSG(input_data->type == UB_FD_REMOTE_SOCKET,
				"ub_socket_input_test1 - 1 failed...");

		DR_ASSERT_MSG(ub_list_get_size(input_data->buf_list) == 1,
				"ub_socket_input_test1 - 2 failed...");

		ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
				input_data->buf_list, 0);

		DR_ASSERT_MSG(input_buf->size == 5,
				"ub_socket_input_test1 - 3 failed...");

		DR_ASSERT_MSG(memcmp(input_buf->buf, "HELLO", input_buf->size) == 0,
				"ub_socket_input_test1 - 4 failed...");

		DR_ASSERT_MSG(memcmp(input_data->source_info.remote_socket_info.ip, "127.0.0.1", 9) == 0,
				"ub_socket_input_test1 - 4 failed...");

		DR_ASSERT_MSG(input_data->source_info.remote_socket_info.port == 7717,
				"ub_socket_input_test1 - 5 failed...");

		DR_ASSERT_MSG(input_data->offset == 0,
				"ub_socket_input_test1 - 12 failed...");

		saw_first = true;

	} else {

		DR_ASSERT_MSG(input_data->buf_list != NULL,
				"ub_socket_input_test1 - 6 failed...");

		DR_ASSERT_MSG(input_data->type == UB_FD_REMOTE_SOCKET,
				"ub_socket_input_test1 - 7 failed...");

		DR_ASSERT_MSG(ub_list_get_size(input_data->buf_list) == 1,
				"ub_socket_input_test1 - 8 failed...");

		ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
				input_data->buf_list, 0);

		DR_ASSERT_MSG(input_buf->size == 3,
				"ub_socket_input_test1 - 2 failed...");

		DR_ASSERT_MSG(memcmp(input_buf->buf, "END", input_buf->size) == 0,
				"ub_socket_input_test1 - 10 failed...");

		DR_ASSERT_MSG(memcmp(input_data->source_info.remote_socket_info.ip, "127.0.0.1", 9) == 0,
				"ub_socket_input_test1 - 4 failed...");

		DR_ASSERT_MSG(input_data->source_info.remote_socket_info.port == 7717,
				"ub_socket_input_test1 - 11 failed...");

		DR_ASSERT_MSG(input_data->offset == 5,
				"ub_socket_input_test1 - 12 failed...");

		saw_second = true;
	}
}

static void event_exit() {

	DR_ASSERT_MSG(saw_first, "ub_socket_input_test1 - 13 failed...");
	DR_ASSERT_MSG(saw_second, "ub_socket_input_test1 - 14 failed...");

	DR_ASSERT_MSG(count == 2, "ub_socket_input_test1 - 15 failed...");
	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_read, true,
			UB_EV_FD_INPUT_OPT_SOURCE_INFO | UB_EV_FD_INPUT_OPT_OFFSET
					| UB_EV_FD_INPUT_OPT_REMOTE_SOCKET, id);

	dr_register_exit_event(event_exit);
}


