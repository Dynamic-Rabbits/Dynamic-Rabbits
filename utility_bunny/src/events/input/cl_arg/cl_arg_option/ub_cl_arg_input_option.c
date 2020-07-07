/**
 *  @file ub_cl_arg_input_option.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_cl_arg_input_option.h"
#include "../../../../byte/ub_bit_checker.h"

// Indexes of options
#define HANDLE_0TH_ARG_BIT 0

bool ub_cl_arg_options_is_handle_0th_arg_enabled(
		UB_EV_CL_ARG_INPUT_OPT options) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, HANDLE_0TH_ARG_BIT, true);

	return ub_byte_are_all_bit_set(options, 1, bit_check);
}
