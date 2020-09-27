/**
 *  @file ub_file_input_option.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_fd_input_option.h"
#include "../../../../byte/ub_bit_checker.h"

// Indexes of options
#define SOURCE_INFO_BIT 0
#define OFFSET_BIT 1
#define FILE_BIT 2
#define LOCAL_SOCKET_BIT 3
#define REMOTE_SOCKET_BIT 4

bool ub_fd_options_is_source_info_enabled(UB_EV_FD_INPUT_OPT options) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, SOURCE_INFO_BIT, true);

	return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ub_fd_options_is_read_offset_enabled(UB_EV_FD_INPUT_OPT options) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, OFFSET_BIT, true);

	return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ub_fd_options_is_file_enabled(UB_EV_FD_INPUT_OPT options) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, FILE_BIT, true);

	return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT options) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, LOCAL_SOCKET_BIT, true);

	return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT options) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, REMOTE_SOCKET_BIT, true);

	return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ub_fd_options_is_socket_enabled(UB_EV_FD_INPUT_OPT options) {

	return ub_fd_options_is_local_socket_enabled(options)
			|| ub_fd_options_is_remote_socket_enabled(options);
}

