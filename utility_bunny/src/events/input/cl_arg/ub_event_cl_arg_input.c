/**
 *  @file ub_cl_arg_input.c
 *  @brief It parsed the command line arguments, calling a cb function
 *  for each.
 *  @author John F.X. Galea
 */

#include "ub_event_cl_arg_input.h"
#include "cl_arg_option/ub_cl_arg_input_option.h"
#include "drmgr.h"
#include "../../../datastructs/sets/ub_intptr_hashset.h"

/***************************************************************************
 *  Structs
 */

/**
 *  @struct ub_env_var_input_ctx_t
 *
 *  The cl arg input context. It stores overall info on
 *  gather cl arguments.
 *
 *  @var ub_cl_arg_input_ctx_t::options Options for hooking.
 *  @var ub_cl_arg_input_ctx_t::env_var_hndlr A function pointer
 *  to the callback.
 *  @var ub_cl_arg_input_ctx_t::index_set A set of containing arg indexes
 *  to consider.
 */
typedef struct {
	bool consider_all;
	UB_EV_CL_ARG_INPUT_OPT options;
	ub_ev_handle_cl_arg_event_t cl_arg_hndlr;
	void *index_set;
	int *argc;
	char **argv;
} ub_cl_arg_input_ctx_t;

/***************************************************************************
 *  Structs
 */

DR_EXPORT void* ub_ev_cl_arg_input_init_ctx(
		ub_ev_handle_cl_arg_event_t cl_arg_hndlr, bool consider_all,
		UB_EV_CL_ARG_INPUT_OPT options) {

	drmgr_init();

	ub_cl_arg_input_ctx_t *ub_cl_arg_input_ctx = dr_global_alloc(
			sizeof(ub_cl_arg_input_ctx_t));

	ub_cl_arg_input_ctx->consider_all = consider_all;
	ub_cl_arg_input_ctx->cl_arg_hndlr = cl_arg_hndlr;

	if (!ub_cl_arg_input_ctx->consider_all)
		ub_cl_arg_input_ctx->index_set = ub_intptr_hashset_create();
	else
		ub_cl_arg_input_ctx->index_set = NULL;

	ub_cl_arg_input_ctx->options = options;

	dr_get_application_cl_args(&(ub_cl_arg_input_ctx->argc),
			&(ub_cl_arg_input_ctx->argv));

	return ub_cl_arg_input_ctx;
}

DR_EXPORT void ub_ev_cl_arg_input_destroy_ctx(void *cl_arg_input_ctx_opaque) {

	ub_cl_arg_input_ctx_t *ub_cl_arg_input_ctx =
			(ub_cl_arg_input_ctx_t *) cl_arg_input_ctx_opaque;

	if (ub_cl_arg_input_ctx->index_set != NULL)
		ub_intptr_hashset_destroy(ub_cl_arg_input_ctx->index_set);

	dr_global_free(ub_cl_arg_input_ctx, sizeof(ub_cl_arg_input_ctx_t));

	drmgr_exit();
}

DR_EXPORT void ub_ev_cl_arg_input_register_cl_args_index(
		void *cl_arg_input_ctx_oapque, size_t cl_arg_index) {

	ub_cl_arg_input_ctx_t *ub_cl_arg_input_ctx =
			(ub_cl_arg_input_ctx_t *) cl_arg_input_ctx_oapque;

	DR_ASSERT_MSG(!ub_cl_arg_input_ctx->consider_all,
			"The consider_all option not passed!");

	if (cl_arg_index <= 0 || *(ub_cl_arg_input_ctx->argc) <= cl_arg_index)
		DR_ASSERT(false);

	ub_intptr_hashset_insert(ub_cl_arg_input_ctx->index_set,
			(uintptr_t) cl_arg_index);
}

static void ub_ev_cl_trigger_cl_arg_cb(ub_cl_arg_input_ctx_t *cl_arg_input_ctx,
		ub_ev_cl_arg_data_t *cl_arg_data, size_t index, char *arg) {

	cl_arg_data->index = index;
	cl_arg_data->arg = arg;
	cl_arg_input_ctx->cl_arg_hndlr(cl_arg_data);
}

DR_EXPORT void ub_ev_cl_arg_input_parse(void *cl_arg_input_ctx_opaque) {

	ub_cl_arg_input_ctx_t *cl_arg_input_ctx =
			(ub_cl_arg_input_ctx_t *) cl_arg_input_ctx_opaque;

	size_t argc = *(cl_arg_input_ctx->argc);

	DR_ASSERT(argc > 0);

	ub_ev_cl_arg_data_t cl_arg_data;

	if (ub_cl_arg_options_is_handle_0th_arg_enabled(
			cl_arg_input_ctx->options)) {

		ub_ev_cl_trigger_cl_arg_cb(cl_arg_input_ctx, &cl_arg_data, 0,
				cl_arg_input_ctx->argv[0]);
	}

	for (size_t i = 1; i < argc; i++) {

		if (cl_arg_input_ctx->consider_all
				|| ub_intptr_hashset_is_included(cl_arg_input_ctx->index_set,
						(uintptr_t) i))
			ub_ev_cl_trigger_cl_arg_cb(cl_arg_input_ctx, &cl_arg_data, i,
					cl_arg_input_ctx->argv[i]);
	}

}
