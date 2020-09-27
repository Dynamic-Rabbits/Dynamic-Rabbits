/**
 *  @file ub_file_input_option.c
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_FILE_FILE_INPUT_OPTION_UB_FILE_INPUT_OPTION_C_
#define EVENTS_INPUT_FILE_FILE_INPUT_OPTION_UB_FILE_INPUT_OPTION_C_

#include "dr_defines.h"
#include "dr_api.h"
#include "../ub_event_fd_input.h"

bool ub_fd_options_is_source_info_enabled(UB_EV_FD_INPUT_OPT options);

bool ub_fd_options_is_read_offset_enabled(UB_EV_FD_INPUT_OPT options);

bool ub_fd_options_is_file_enabled(UB_EV_FD_INPUT_OPT options);

bool ub_fd_options_is_local_socket_enabled(UB_EV_FD_INPUT_OPT options);

bool ub_fd_options_is_remote_socket_enabled(UB_EV_FD_INPUT_OPT options);

bool ub_fd_options_is_socket_enabled(UB_EV_FD_INPUT_OPT options);

#endif /* EVENTS_INPUT_FILE_FILE_INPUT_OPTION_UB_FILE_INPUT_OPTION_C_ */
