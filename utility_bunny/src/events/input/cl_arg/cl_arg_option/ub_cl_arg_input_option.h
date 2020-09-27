/**
 *  @file ub_cl_arg_input_option.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_CL_ARG_CL_ARG_OPTION_UB_CL_ARG_INPUT_OPTION_H_
#define EVENTS_INPUT_CL_ARG_CL_ARG_OPTION_UB_CL_ARG_INPUT_OPTION_H_

#include "../ub_event_cl_arg_input.h"
#include "dr_defines.h"
#include "dr_api.h"

/**
 *  Specifies whether to consider the 0th arg.
 *
 *  @param options The options value set by the user.
 *  @return Returns a bool indicating whether the UB_EV_CL_ARG_INPUT_OPT_HANDLE_0th
 *  option is set.
 */
bool ub_cl_arg_options_is_handle_0th_arg_enabled(UB_EV_CL_ARG_INPUT_OPT options);

#endif /* EVENTS_INPUT_CL_ARG_CL_ARG_OPTION_UB_CL_ARG_INPUT_OPTION_H_ */
