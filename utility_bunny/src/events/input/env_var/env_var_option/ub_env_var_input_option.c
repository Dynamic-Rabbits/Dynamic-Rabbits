/**
 *  @file ub_env_var_option.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_env_var_input_option.h"
#include "../../../../byte/ub_bit_checker.h"

// Indexes of options
#define VAR_NAME_BIT 0

bool ub_env_var_options_is_var_name_enabled(UB_EV_ENV_VAR_INPUT_OPT options){

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, VAR_NAME_BIT, true);

	return ub_byte_are_all_bit_set(options, 1, bit_check);
}
