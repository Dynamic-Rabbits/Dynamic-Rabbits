/**
 *  @file ub_env_var_option.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_ENV_VAR_ENV_VAR_OPTION_UB_ENV_VAR_OPTION_H_
#define EVENTS_INPUT_ENV_VAR_ENV_VAR_OPTION_UB_ENV_VAR_OPTION_H_

#include "../ub_event_env_var_input.h"
#include "dr_defines.h"
#include "dr_api.h"

/**
 *  Determines whether the var name retrieval is set.
 *
 *  @param options The options value set by the user.
 *  @return Returns a bool indicating whether the UB_EV_ENV_VAR_INPUT_OPT_VAR
 *  option is set.
 */
bool ub_env_var_options_is_var_name_enabled(UB_EV_ENV_VAR_INPUT_OPT options);

#endif /* EVENTS_INPUT_ENV_VAR_ENV_VAR_OPTION_UB_ENV_VAR_OPTION_H_ */
