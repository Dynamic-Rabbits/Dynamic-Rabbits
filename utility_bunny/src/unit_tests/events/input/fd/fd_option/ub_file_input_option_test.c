/**
 *  @file ub_file_input_option_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../../events/input/fd/fd_option/ub_fd_input_option.h"

static void test1() {

	DR_ASSERT_MSG(
			ub_fd_options_is_source_info_enabled(UB_EV_FD_INPUT_OPT_BARE) == false,
			"ub_file_input_option_test - test1 - 0 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_source_info_enabled(UB_EV_FD_INPUT_OPT_OFFSET) == false,
			"ub_file_input_option_test - test1 - 1 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_source_info_enabled(UB_EV_FD_INPUT_OPT_SOURCE_INFO) == true,
			"ub_file_input_option_test - test1 - 2 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_read_offset_enabled(UB_EV_FD_INPUT_OPT_BARE) == false,
			"ub_file_input_option_test - test1 - 3 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_read_offset_enabled(UB_EV_FD_INPUT_OPT_LOCAL_SOCKET) == false,
			"ub_file_input_option_test - test1 - 4 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_read_offset_enabled(UB_EV_FD_INPUT_OPT_FILE) == false,
			"ub_file_input_option_test - test1 - 5 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_read_offset_enabled(UB_EV_FD_INPUT_OPT_SOURCE_INFO) == false,
			"ub_file_input_option_test - test1 - 6 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_read_offset_enabled(UB_EV_FD_INPUT_OPT_OFFSET) == true,
			"ub_file_input_option_test - test1 - 7 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT_OFFSET) == false,
			"ub_file_input_option_test - test1 - 8 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT_FILE) == false,
			"ub_file_input_option_test - test1 - 9 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT_BARE) == false,
			"ub_file_input_option_test - test1 - 10 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT_SOURCE_INFO) == false,
			"ub_file_input_option_test - test1 - 11 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT_LOCAL_SOCKET) == false,
			"ub_file_input_option_test - test1 - 12 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT_REMOTE_SOCKET) == true,
				"ub_file_input_option_test - test1 - 13 failed...");

	DR_ASSERT_MSG(
				ub_fd_options_is_file_enabled(UB_EV_FD_INPUT_OPT_LOCAL_SOCKET) == false,
				"ub_file_input_option_test - test1 - 14 failed...");

	DR_ASSERT_MSG(
				ub_fd_options_is_file_enabled(UB_EV_FD_INPUT_OPT_BARE) == false,
				"ub_file_input_option_test - test1 - 15 failed...");
	DR_ASSERT_MSG(
				ub_fd_options_is_file_enabled(UB_EV_FD_INPUT_OPT_OFFSET) == false,
				"ub_file_input_option_test - test1 - 17 failed...");

	DR_ASSERT_MSG(
				ub_fd_options_is_file_enabled(UB_EV_FD_INPUT_OPT_SOURCE_INFO) == false,
				"ub_file_input_option_test - test1 - 18 failed...");

	DR_ASSERT_MSG(
				ub_fd_options_is_file_enabled(UB_EV_FD_INPUT_OPT_FILE) == true,
				"ub_file_input_option_test - test1 - 19 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT_OFFSET) == false,
			"ub_file_input_option_test - test1 - 8 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT_FILE) == false,
			"ub_file_input_option_test - test1 - 9 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT_BARE) == false,
			"ub_file_input_option_test - test1 - 10 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT_SOURCE_INFO) == false,
			"ub_file_input_option_test - test1 - 11 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT_LOCAL_SOCKET) == true,
			"ub_file_input_option_test - test1 - 12 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT_REMOTE_SOCKET) == false,
				"ub_file_input_option_test - test1 - 13 failed...");


	DR_ASSERT_MSG(
			ub_fd_options_is_socket_enabled(UB_EV_FD_INPUT_OPT_SOURCE_INFO) == false,
			"ub_file_input_option_test - test1 - 11 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_socket_enabled(UB_EV_FD_INPUT_OPT_LOCAL_SOCKET) == true,
			"ub_file_input_option_test - test1 - 12 failed...");

	DR_ASSERT_MSG(
			ub_fd_options_is_socket_enabled(UB_EV_FD_INPUT_OPT_REMOTE_SOCKET) == true,
				"ub_file_input_option_test - test1 - 13 failed...");

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
}
