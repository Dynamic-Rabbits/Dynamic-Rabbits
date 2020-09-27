/**
 *  @file ub_env_var_input.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_ENV_VAR_UB_ENV_VAR_INPUT_H_
#define EVENTS_INPUT_ENV_VAR_UB_ENV_VAR_INPUT_H_

#include "dr_api.h"

/**
 * Defines flags that specify what information to be available
 * upon the calling of the callback for parsing ci args.
 */
typedef unsigned int UB_EV_ENV_VAR_INPUT_OPT;
#define UB_EV_ENV_VAR_INPUT_OPT_BARE 0
#define UB_EV_ENV_VAR_INPUT_OPT_VAR 1 // Include variable name

/**
 *  @struct ub_env_var_data_t
 *  Information on the obtain value of the environment variable.
 *
 *  The pointer \p value directs to memory used by the application,
 *  not an external copy. Hence, you can mark that pointer
 *  as tainted if one likes.
 *
 *  @var ub_env_var_data_t::variable_name The name of the variable.
 *  @var ub_env_var_data_t::value The value of the environment.
 */
typedef struct {
	char *variable_name;
	char *value;
} ub_ev_env_var_data_t;

/**
 *  Call-back function when obtaining a value of an env var.
 *
 *  @param env_var_data Contains data of the variable, such as its name and value.
 */
typedef void (*ub_ev_handle_env_var_event_t)(ub_ev_env_var_data_t *env_var_data);

/**
 *  Creates an env var input ctx used to hook getenv.
 *
 *  @param env_var_hndlr A function pointer to the callback.
 *  @param consider_all
 *  @param options Options specifying what information is available for the callback.
 */
DR_EXPORT void ub_ev_env_var_input_init_ctx(ub_ev_handle_env_var_event_t env_var_hndlr,
		bool consider_all, UB_EV_ENV_VAR_INPUT_OPT options);

/**
 *  Destroys an env var input ctx.
 */
DR_EXPORT void ub_ev_env_var_input_destroy_ctx();

/**
 *  Registers the hook supplied to a specific env variable. This may be called
 *  multiple times. However, should the consider_all option be specified, this
 *  function should never be called.
 *
 *  @param env_variable The variable to hook.
 */
DR_EXPORT void ub_ev_env_var_input_register_env_var(char *env_variable);

#endif /* EVENTS_INPUT_ENV_VAR_UB_ENV_VAR_INPUT_H_ */
