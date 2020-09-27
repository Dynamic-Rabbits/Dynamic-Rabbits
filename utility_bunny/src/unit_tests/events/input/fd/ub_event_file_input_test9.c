/**
 *  @file ub_event_file_input_test9.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

void *socket_input_ctx;
int count = 0;

static void got_readv(ub_fd_input_data_t *input_data) {

	count++;

	DR_ASSERT_MSG(input_data->buf_list != NULL,
			"ub_file_input_option_test9 - 0 failed...");

	DR_ASSERT_MSG(ub_list_get_size(input_data->buf_list) == 3,
			"ub_file_input_option_test9 - 1 failed...");

	ub_input_buf_t *input_buf1 = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 0);

	DR_ASSERT_MSG(memcmp(input_buf1->buf, "H", input_buf1->size) == 0,
			"ub_file_input_option_test9 - 2 failed...");

	DR_ASSERT_MSG(input_buf1->size == 1,
			"ub_file_input_option_test9 - 3 failed...");

	ub_input_buf_t *input_buf2 = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 1);

	DR_ASSERT_MSG(memcmp(input_buf2->buf, "e", input_buf1->size) == 0,
			"ub_file_input_option_test9 - 4 failed...");

	DR_ASSERT_MSG(input_buf2->size == 1,
			"ub_file_input_option_test9 - 5 failed...");

	ub_input_buf_t *input_buf3 = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 2);

	DR_ASSERT_MSG(memcmp(input_buf3->buf, "l", input_buf3->size) == 0,
			"ub_file_input_option_test9 - 6 failed...");

	DR_ASSERT_MSG(input_buf3->size == 1,
			"ub_file_input_option_test9 - 7 failed...");

	DR_ASSERT_MSG( input_data->offset == 0,
			"ub_file_input_option_test9 - 8 failed...");
}

static void event_exit() {

	DR_ASSERT_MSG(count == 1,
			"ub_event_file_input_test9 - 9 failed...");

	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_readv, false,
			UB_EV_FD_INPUT_OPT_SOURCE_INFO
					| UB_EV_FD_INPUT_OPT_OFFSET, id);

	ub_ev_fd_input_register_file(socket_input_ctx, "ub_file_input_test1.txt");

	dr_register_exit_event(event_exit);
}

