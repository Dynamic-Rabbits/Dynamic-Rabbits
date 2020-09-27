/*
 * taint_dummy_helper.c
 *
 *      Author: john
 */

#include "taint_dummy_helper.h"

#include "dr_defines.h"
#include <string.h>
#include "taint_bunny.h"
#include "taint_bunny.h"

#define MAX_SAMPLE_RANGE 4

extern void *taint_bunny;
static tb_cc_get_default_label_t get_default_label;
static bool enable_random_sampling;

void *fd_input_ctx;
void *cl_arg_input_ctx;

uint32_t num_taint_srcs;
uint32_t num_samples;

static bool is_sampled() {
        
        if (enable_random_sampling)
            return dr_get_random_value(MAX_SAMPLE_RANGE) == 0;

	return true;
}

static void got_cl_arg_read(ub_ev_cl_arg_data_t *cl_arg_data) {

	num_taint_srcs++;
	if (!is_sampled())
		return;
	num_samples++;

	tb_taint_mem_block(taint_bunny, (uintptr_t) cl_arg_data->arg,
			strlen(cl_arg_data->arg), get_default_label());
}

static void got_env_var_read(ub_ev_env_var_data_t *env_var_data) {

	num_taint_srcs++;
	if (!is_sampled())
		return;
	num_samples++;

	if (env_var_data->value) {
		tb_taint_mem_block(taint_bunny, (uintptr_t) env_var_data->value,
				strlen(env_var_data->value), get_default_label());
	}
}

static void got_fd_read(ub_fd_input_data_t *input_data) {

	num_taint_srcs++;
	if (!is_sampled())
		return;
	num_samples++;

	ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
			input_data->buf_list, 0);

	if (input_data->type == UB_FD_FILE) {

		if (strstr(input_data->source_info.file_info.base_name, ".so") == NULL) {

			tb_taint_mem_block(taint_bunny, (uintptr_t) input_buf->buf,
					input_buf->size, get_default_label());
		}
	} else {

		tb_taint_mem_block(taint_bunny, (uintptr_t) input_buf->buf,
				input_buf->size, get_default_label());
	}
}

void taint_dummy_intro_init(client_id_t client_id,
		tb_cc_get_default_label_t in_get_default_label, bool is_random_samp) {

	DR_ASSERT(in_get_default_label);
	get_default_label = in_get_default_label;

	enable_random_sampling = is_random_samp;

	if (enable_random_sampling) {
		num_taint_srcs = 0;
		num_samples = 0;

		/* Keep it fixed for repeatable experiments */
		dr_set_random_seed(99999);
	}

	cl_arg_input_ctx = ub_ev_cl_arg_input_init_ctx(got_cl_arg_read, true,
	UB_EV_CL_ARG_INPUT_OPT_BARE);
	ub_ev_cl_arg_input_parse(cl_arg_input_ctx);

	ub_ev_env_var_input_init_ctx(got_env_var_read, true,
	UB_EV_ENV_VAR_INPUT_OPT_BARE);

	fd_input_ctx =
			ub_ev_fd_input_init_ctx(got_fd_read, true,
					UB_EV_FD_INPUT_OPT_LOCAL_SOCKET
							| UB_EV_FD_INPUT_OPT_SOURCE_INFO
							| UB_EV_FD_INPUT_OPT_REMOTE_SOCKET
							| UB_EV_FD_INPUT_OPT_FILE, client_id);
}

void taint_dummy_exit() {



	ub_ev_cl_arg_input_destroy_ctx(cl_arg_input_ctx);
	ub_ev_env_var_input_destroy_ctx();
	ub_ev_fd_input_destroy_ctx(fd_input_ctx);
}
