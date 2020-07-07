/**
 *  @file ub_cl_arg_input.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_CL_ARG_UB_EVENT_CL_ARG_INPUT_H_
#define EVENTS_INPUT_CL_ARG_UB_EVENT_CL_ARG_INPUT_H_

#include "dr_api.h"

/**
 * Defines flags that specify what information to be available
 * upon the calling of the callback for parsing command-line
 * arguments.
 */
typedef unsigned int UB_EV_CL_ARG_INPUT_OPT;
// No additional information
#define UB_EV_CL_ARG_INPUT_OPT_BARE 0
// Call CB for the 0th ARG
#define UB_EV_CL_ARG_INPUT_OPT_HANDLE_0TH 1

/**
 *  @struct ub_env_var_data_t
 *  Information on the obtain value of the command-line arg.
 *
 *  The pointer \p arg directs to memory used by the application,
 *  not an external copy. Hence, you can mark that pointer
 *  as tainted if one likes.
 *
 *  @var ub_ev_cl_arg_data_t::index The index of the arg.
 *  @var ub_ev_cl_arg_data_t::arg The value of the command-line arg.
 */
typedef struct {
	size_t index;
	char *arg;
} ub_ev_cl_arg_data_t;

/**
 *  Call-back function when obtaining a value of an cl arg.
 *
 *  @param cl_data Contains data of a cl arg, such as its name and value.
 */
typedef void (*ub_ev_handle_cl_arg_event_t)(ub_ev_cl_arg_data_t *cl_arg_data);

/**
 *  Creates an cl arg input ctx used to gather cl args
 *
 *  @param env_var_hndlr A function pointer to the callback.
 *  @param consider_all
 *  @param options Options specifying what information is available for the callback.
 *  @return Returns the newly created cl arg input manager.
 */
DR_EXPORT void *ub_ev_cl_arg_input_init_ctx(ub_ev_handle_cl_arg_event_t cl_arg_hndlr,
		bool consider_all, UB_EV_CL_ARG_INPUT_OPT options);

/**
 *  Destroys an cl arg input ctx.
 *
 *  @param cl_arg_input_ctx The cl arg input ctx to destroy.
 */
DR_EXPORT void ub_ev_cl_arg_input_destroy_ctx(void *cl_arg_input_ctx);

/**
 *  Registers the hook supplied to a specific cl arg index. This may be called
 *  multiple times. However, should the consider_all option be specified, this
 *  function should never be called.
 *
 *  @param cl_arg_ctx The cl arg input ctx.
 *  @param cl_arg_variable The variable to hook.
 */
DR_EXPORT void ub_ev_cl_arg_input_register_cl_args_index(void *cl_arg_input_ctx, size_t cl_arg_index);

/**
 *  Parse command-line args.
 *
 *  @param cl_arg_input_ctx The cl arg input ctx to destroy.
 */
DR_EXPORT void ub_ev_cl_arg_input_parse(void *cl_arg_input_ctx);

#endif /* EVENTS_INPUT_CL_ARG_UB_EVENT_CL_ARG_INPUT_H_ */
