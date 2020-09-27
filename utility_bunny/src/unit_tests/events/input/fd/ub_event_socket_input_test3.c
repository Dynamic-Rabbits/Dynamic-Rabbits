/**
 *  @file ub_event_socket_input_test4.c
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
			"ub_socket_input_test1 - 0 failed...");

	DR_ASSERT_MSG(input_data->type == UB_FD_LOCAL_SOCKET,
			"ub_socket_input_test1 - 1 failed...");

	DR_ASSERT_MSG(ub_list_get_size(input_data->buf_list) == 3,
			"ub_socket_input_test1 - 2 failed...");

	ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 0);

	DR_ASSERT_MSG(input_buf->size == 1, "ub_socket_input_test1 - 3 failed...");

	char *char_buf = (char *) input_buf->buf;
	DR_ASSERT_MSG(char_buf[0] == 'H',
			"ub_socket_input_test1 - 4 failed...");

	DR_ASSERT_MSG(input_data->source_info.local_socket_info.port == 7717,
			"ub_socket_input_test1 - 5 failed...");

	input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 1);

	DR_ASSERT_MSG(input_buf->size == 1, "ub_socket_input_test1 - 6 failed...");

	char_buf = (char *) input_buf->buf;
	DR_ASSERT_MSG(char_buf[0] == 'E',
			"ub_socket_input_test1 - 6 failed...");

	DR_ASSERT_MSG(input_data->source_info.local_socket_info.port == 7717,
			"ub_socket_input_test1 - 7 failed...");

	input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 2);

	DR_ASSERT_MSG(input_buf->size == 1, "ub_socket_input_test1 - 8 failed...");


	char_buf = (char *) input_buf->buf;
	DR_ASSERT_MSG(char_buf[0] == 'L',
			"ub_socket_input_test1 - 9 failed...");

	DR_ASSERT_MSG(input_data->source_info.local_socket_info.port == 7717,
			"ub_socket_input_test1 - 10 failed...");

}

static void event_exit() {

	dr_fprintf(STDERR, "The count isn %d", count);
	DR_ASSERT_MSG(count == 1, "ub_socket_input_test1 - 11 failed...");
	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_read, true,
			UB_EV_FD_INPUT_OPT_SOURCE_INFO | UB_EV_FD_INPUT_OPT_OFFSET
					| UB_EV_FD_INPUT_OPT_LOCAL_SOCKET, id);

	dr_register_exit_event(event_exit);
}
