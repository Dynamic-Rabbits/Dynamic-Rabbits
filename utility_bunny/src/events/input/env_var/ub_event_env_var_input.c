/**
 *  @file ub_env_var_input.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_event_env_var_input.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drwrap.h"
#include "env_var_option/ub_env_var_input_option.h"
#include "../../../datastructs/sets/ub_str_hashset.h"
#include <string.h>

/***************************************************************************
 *  Structs
 */

/**
 *  @struct ub_env_var_input_ctx_t
 *
 *  The env var input context. It stores overall info on
 *  hooks to get environment variables.
 *
 *  @var ub_env_var_input_ctx_t::options Options for hooking.
 *  @var ub_env_var_input_ctx_t::env_var_hndlr A function pointer
 *  to the callback.
 *  @var variable_set A set of containing the variables names to
 *  hook.
 */
typedef struct {
	bool consider_all;
	UB_EV_ENV_VAR_INPUT_OPT options;
	ub_ev_handle_env_var_event_t env_var_hndlr;
	void *variable_set;
} ub_env_var_input_ctx_t;

/**
 *  @struct ub_env_var_passing_data_t
 *
 *  Data to be passed from the prior cb hook to the post cb hook.
 *
 *  @var ub_env_var_passing_data_t::variable_name The name of the environment
 *  variable. Not set if option in UB_EV_ENV_VAR_INPUT_OPT is not set.
 *  @var ub_env_var_passing_data_t::ctx_data The env var input ctx.
 */
typedef struct {
	char *variable_name;
} ub_env_var_passing_data_t;

ub_env_var_input_ctx_t *env_var_input_ctx;

/***************************************************************************
 *  Prototypes
 */
static void ub_env_var_input_module_load_event(void *drcontext,
		const module_data_t *mod, bool loaded);
static void ub_env_var_wrap_getenv_pre(void *wrapcxt, void **user_data);
static void ub_env_var_wrap_getenv_post(void *wrapcxt, void *user_data);

/***************************************************************************
 *  Implementation
 */

DR_EXPORT void ub_ev_env_var_input_init_ctx(
		ub_ev_handle_env_var_event_t env_var_hndlr, bool consider_all,
		UB_EV_ENV_VAR_INPUT_OPT options) {

	drmgr_init();

	if (!drwrap_init())
		DR_ASSERT_MSG(false, "DrWrap not initialised.");

	env_var_input_ctx = dr_global_alloc(sizeof(ub_env_var_input_ctx_t));

	env_var_input_ctx->consider_all = consider_all;
	env_var_input_ctx->env_var_hndlr = env_var_hndlr;

	if (!env_var_input_ctx->consider_all)
		env_var_input_ctx->variable_set = ub_str_hashset_create();
	else
		env_var_input_ctx->variable_set = NULL;

	env_var_input_ctx->options = options;

	drmgr_register_module_load_event(ub_env_var_input_module_load_event);
}

DR_EXPORT void ub_ev_env_var_input_destroy_ctx() {


	if (!env_var_input_ctx->consider_all)
		ub_str_hashset_destroy(env_var_input_ctx->variable_set);

	dr_global_free(env_var_input_ctx, sizeof(ub_env_var_input_ctx_t));

	drwrap_exit();
	drmgr_exit();
}

DR_EXPORT void ub_ev_env_var_input_register_env_var(char *env_variable) {

	DR_ASSERT_MSG(!env_var_input_ctx->consider_all,
			"The consider_all option not passed!");

	ub_str_hashset_insert(env_var_input_ctx->variable_set, env_variable);
}

/**
 *  Should be called upon the loading of a module. It is responsible
 *  for getting the proc address of getenv, and hooking it with the
 *  callback supplied via \p ub_ev_env_var_input_init_ctx.
 *
 *  @param env_var_ctx The env var input ctx.
 */
static void ub_env_var_input_module_load_event(void *drcontext,
		const module_data_t *mod, bool loaded) {

	app_pc towrap = (app_pc) dr_get_proc_address(mod->handle, "getenv");
	if (towrap != NULL) {

		bool is_succ = drwrap_wrap_ex(towrap, ub_env_var_wrap_getenv_pre,
				ub_env_var_wrap_getenv_post, NULL,
				DRWRAP_CALLCONV_DEFAULT);

		DR_ASSERT(is_succ);
	}
}

/**
 *  Called upon the execution of getenv. This is a prior call-back, and is used to get
 *  the variable name of the environment.
 *
 *  @param user_data A pointer to a pointer referring to env var input ctx.
 */
static void ub_env_var_wrap_getenv_pre(void *wrapcxt, void **user_data) {

	char *path = (char*) drwrap_get_arg(wrapcxt, 0);

	if (!env_var_input_ctx->consider_all
			&& !ub_str_hashset_is_included(env_var_input_ctx->variable_set,
					path)) {
		// We are skipping this variable as it is not included in the set
		*user_data = NULL;
		return;
	}

	ub_env_var_passing_data_t *env_var_passing_data =
			(ub_env_var_passing_data_t *) dr_global_alloc(
					sizeof(ub_env_var_passing_data_t));

	bool get_var_name = ub_env_var_options_is_var_name_enabled(
			env_var_input_ctx->options);

	if (get_var_name) {
		env_var_passing_data->variable_name = dr_global_alloc(
				(strlen(path) + 1) * sizeof(char));
		memcpy(env_var_passing_data->variable_name, path,
				(strlen(path) + 1) * sizeof(char));
	} else
		env_var_passing_data->variable_name = NULL;

	*user_data = env_var_passing_data;
}

/**
 *  Called upon the execution of getenv. This is a post call-back, and is used to get
 *  the variable value of the environment. The handler provided by the user is also called.
 *
 *  @param user_data A pointer to a pointer referring to env var input ctx.
 */
static void ub_env_var_wrap_getenv_post(void *wrapcxt, void *user_data) {

	ub_env_var_passing_data_t *passing_data =
			(ub_env_var_passing_data_t *) user_data;

	if (passing_data != NULL) {

		ub_ev_env_var_data_t env_var_data;

		env_var_data.value = (char *) (ptr_int_t) drwrap_get_retval(wrapcxt);

		if (env_var_data.value != NULL)
			env_var_data.variable_name = passing_data->variable_name;

		env_var_input_ctx->env_var_hndlr(&env_var_data);

		if (passing_data->variable_name != NULL) {
			dr_global_free(passing_data->variable_name,
					sizeof(char) * (strlen(passing_data->variable_name) + 1));
		}

		dr_global_free(passing_data, sizeof(ub_env_var_passing_data_t));
	}
}
