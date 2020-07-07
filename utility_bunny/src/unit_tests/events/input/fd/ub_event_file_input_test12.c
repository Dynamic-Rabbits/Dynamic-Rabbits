/**
 *  @file ub_event_file_input_test12.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

void *socket_input_ctx;
int count = 0;
bool pread_seen = false;
bool read_seen = false;

static void got_preadv(ub_fd_input_data_t *input_data) {

	count++;

	DR_ASSERT_MSG(input_data->buf_list != NULL,
			"ub_file_input_option_test12 - 0 failed...");

	if (ub_list_get_size(input_data->buf_list) == 3) {

		ub_input_buf_t *input_buf1 = (ub_input_buf_t *) ub_list_get_ith_value(
				input_data->buf_list, 0);

		char *charic = (char *) input_buf1->buf;
		dr_fprintf(STDERR, "THE valus is %c\n", *charic);

		DR_ASSERT_MSG(memcmp(input_buf1->buf, "o", input_buf1->size) == 0,
				"ub_file_input_option_test12 - 2 failed...");

		DR_ASSERT_MSG(input_buf1->size == 1,
				"ub_file_input_option_test12 - 3 failed...");

		ub_input_buf_t *input_buf2 = (ub_input_buf_t *) ub_list_get_ith_value(
				input_data->buf_list, 1);

		charic = (char *) input_buf2->buf;
		dr_fprintf(STDERR, "THE valus is %c\n", *charic);

		DR_ASSERT_MSG(memcmp(input_buf2->buf, " ", input_buf1->size) == 0,
				"ub_file_input_option_test12 - 4 failed...");

		DR_ASSERT_MSG(input_buf2->size == 1,
				"ub_file_input_option_test12 - 5 failed...");

		ub_input_buf_t *input_buf3 = (ub_input_buf_t *) ub_list_get_ith_value(
				input_data->buf_list, 2);

		charic = (char *) input_buf3->buf;
		dr_fprintf(STDERR, "THE valus is %c\n", *charic);

		DR_ASSERT_MSG(memcmp(input_buf3->buf, "t", input_buf3->size) == 0,
				"ub_file_input_option_test12 - 6 failed...");

		DR_ASSERT_MSG(input_buf3->size == 1,
				"ub_file_input_option_test12 - 7 failed...");

		DR_ASSERT_MSG(input_data->offset == 4,
				"ub_file_input_option_test12 - 8 failed...");

		pread_seen = true;

	} else if (ub_list_get_size(input_data->buf_list) == 1){

		ub_input_buf_t *input_buf1 = (ub_input_buf_t *) ub_list_get_ith_value(
				input_data->buf_list, 0);

		dr_fprintf(STDERR, "The offset attaINED IS %d", input_data->offset);

		DR_ASSERT_MSG(input_data->offset == (int64_t ) 0,
				"ub_env_var_input_option_test11 - test1 - 5 failed...");

		DR_ASSERT_MSG(memcmp(input_buf1->buf, "Hello ", input_buf1->size) == 0,
				"ub_env_var_input_option_test - test11 - 3 failed...");

		DR_ASSERT_MSG(pread_seen,
				"ub_env_var_input_option_test11 - test1 - 6 failed...");

		read_seen = true;
	}

}

static void event_exit() {

	DR_ASSERT_MSG(read_seen,
			"ub_env_var_input_option_test11 - test1 - 6 failed...");

	DR_ASSERT_MSG(count == 2, "ub_event_file_input_test12 - 9 failed...");

	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_preadv, false,
	UB_EV_FD_INPUT_OPT_SOURCE_INFO | UB_EV_FD_INPUT_OPT_OFFSET, id);

	ub_ev_fd_input_register_file(socket_input_ctx, "ub_file_input_test1.txt");

	dr_register_exit_event(event_exit);
}

