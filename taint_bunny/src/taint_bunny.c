/*
 *  @author John F.X. Galea
 */

#include "taint_bunny.h"

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include "umbra.h"
#include  <stdint.h>
#include "utility_bunny.h"
#include "instrumentation_bunny.h"

#include "taint_engines/taint_analysis/taint_checks/tb_ta_cc_check/tb_ta_cc_check.h"
#include "taint_engines/taint_analysis/taint_checks/tb_ta_raw_check/tb_ta_raw_check.h"
#include "taint_engines/taint_analysis/taint_checks/tb_ta_simd_check/tb_ta_simd_check.h"

#include "syscall_handlers/tb_syscall_handlers.h"
#include "instrumentation/tb_instrum_register.h"
#include "optimisations/fast_path_generator/tb_fp_optimisation.h"
#include "tls_access/tb_tls_access.h"
#include "taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt_functionality.h"

#include "taint_engines/instr_handlers/tb_raw_instruction_handler_driver.h"
#include "taint_engines/instr_handlers/tb_cc_instruction_handler_driver.h"
#include "taint_engines/instr_handlers/tb_simd_instruction_handler_driver.h"

#include "taint_annotations/tb_annotation_handler.h"

/***************************************************************************
 *  Prototypes
 */

static tb_context_t *tb_init(client_id_t client_id, IB_INSTRUM_OPT options,
		tb_options_t *te_options, tb_fp_settings_t *fp_settings);
static void tb_exit(tb_context_t *tb_ctx);
static void tb_thread_init(void *drcontext, void *tb_ctx_opaque);
static void tb_thread_exit(void *drcontext, void *tb_ctx_opaque);
static void tb_set_default_opts(tb_options_t *te_options);
static void tb_set_default_fp_settings(tb_fp_settings_t *fp_settings);

/***************************************************************************
 * DEFAULT Initialisation Functions
 */

DR_EXPORT void *tb_cc_init_default(client_id_t client_id,
		tb_cc_taint_policy_t *taint_policy) {

	tb_options_t te_options;
	tb_fp_settings_t fp_settings;
	tb_set_default_opts(&te_options);
	tb_set_default_fp_settings(&fp_settings);
	return tb_cc_init(client_id, IB_OPT_BARE, &te_options, &fp_settings,
			taint_policy);
}

DR_EXPORT void *tb_raw_init_default(client_id_t client_id,
		tb_raw_taint_policy_t *taint_policy) {

	tb_options_t te_options;
	tb_fp_settings_t fp_settings;
	tb_set_default_opts(&te_options);
	tb_set_default_fp_settings(&fp_settings);
	return tb_raw_init(client_id, IB_OPT_BARE, &te_options, &fp_settings,
			taint_policy);
}

DR_EXPORT void *tb_simd_init_default(client_id_t client_id,
		tb_raw_taint_policy_t *taint_policy) {

	tb_options_t te_options;
	tb_fp_settings_t fp_settings;
	tb_set_default_opts(&te_options);
	tb_set_default_fp_settings(&fp_settings);
	return tb_simd_init(client_id, IB_OPT_BARE, &te_options, &fp_settings,
			taint_policy);
}

static void tb_set_default_opts(tb_options_t *te_options) {

	te_options->enable_inline = false;
	te_options->enable_taint_off = false;
	te_options->enable_fp = true;
}

static void tb_set_default_fp_settings(tb_fp_settings_t *fp_settings) {

	fp_settings->required_size = 2;
	fp_settings->pop_limit = 3;
	fp_settings->dynamic_path_hit_threshold = (uint) 2000; /*Due to collision, we set this high */
	fp_settings->dups_limit = 2;
	fp_settings->bb_in_out_threshold = 0;
}

/***************************************************************************
 * Initialisation Functions
 */

DR_EXPORT void *tb_cc_init(client_id_t client_id, IB_INSTRUM_OPT options,
		tb_options_t *te_options, tb_fp_settings_t *fp_settings,
		tb_cc_taint_policy_t *taint_policy) {
	DR_ASSERT(te_options);
	tb_context_t *tb_ctx = tb_init(client_id, options, te_options, fp_settings);

	dr_raw_tls_calloc(&(tb_ctx->tls_raw_reg), &(tb_ctx->tls_raw_base), 4, 0);

	// IH Initialisation
	tb_ctx->instr_hndlrs = tb_ih_cc_init_instr_handlers(tb_ctx,
			taint_policy->pre_propagate_funcs,
			taint_policy->post_propagate_funcs);

	// MAP Initialisation
	tb_map_init_maps_drivers_from_cc_mode(&(tb_ctx->mem_map_driver),
			&(tb_ctx->reg_map_driver));

	if (tb_ctx->instr_hndlrs->init_instr_hndlrs)
		tb_ctx->instr_hndlrs->init_instr_hndlrs();

	// Initialise taint policy
	tb_ctx->policy_init = taint_policy->init_func;
	tb_ctx->policy_destroy = taint_policy->destroy_func;

	if (tb_ctx->policy_init)
		tb_ctx->policy_init();

	tb_ctx->get_taint_label = taint_policy->get_default_label;

	tb_ctx->intro_taint_reg_func = taint_policy->intro_taint_reg_func;
	tb_ctx->intro_taint_mem_func = taint_policy->intro_taint_mem_func;

	tb_ctx->meet_func = taint_policy->meet_func;

	tb_ctx->new_ref_func = taint_policy->new_ref_tl_func;
	tb_ctx->delete_ref_func = taint_policy->delete_ref_tl_func;

	tb_ctx->propogate_func_1dst_1src = taint_policy->propagate_1dst_1src_func;
	tb_ctx->propogate_func_1dst_2src = taint_policy->propagate_1dst_2src_func;

	tb_ctx->untaint_mem_func = taint_policy->untaint_mem_func;
	tb_ctx->untaint_reg_func = taint_policy->untaint_reg_func;

	// Initialise maps
	if (tb_ctx->mem_map_driver.init_map_func)
		tb_ctx->mem_map_driver.init_map_func(client_id);

	if (tb_ctx->reg_map_driver.init_map_func)
		tb_ctx->reg_map_driver.init_map_func(client_id);

	tb_ctx->mem_map = tb_ctx->mem_map_driver.create_map_func(tb_ctx, NULL);

	if (te_options->enable_fp) {

		tb_ctx->is_fast_path_mode = true;

		tb_fp_settings_t default_fp_settings;

		if (fp_settings == NULL) {
			tb_set_default_fp_settings(&default_fp_settings);
			fp_settings = &default_fp_settings;
		}

		tb_ctx->tool_info = tb_fast_path_init(client_id, tb_ctx, fp_settings);
	} else {
		tb_ctx->is_fast_path_mode = false;
		tb_ctx->tool_info = ib_register_instrum_tool();
	}

	return (void *) tb_ctx;
}

DR_EXPORT void *tb_raw_init(client_id_t client_id, IB_INSTRUM_OPT options,
		tb_options_t *te_options, tb_fp_settings_t *fp_settings,
		tb_raw_taint_policy_t *taint_policy) {

	DR_ASSERT(te_options);
	tb_context_t *tb_ctx = tb_init(client_id, options, te_options, fp_settings);

	// Initialise slots
	dr_raw_tls_calloc(&(tb_ctx->tls_raw_reg), &(tb_ctx->tls_raw_base), 6, 0);

	tb_ctx->instr_hndlrs = tb_ih_raw_init_instr_handlers(tb_ctx,
			taint_policy->pre_propagate_funcs,
			taint_policy->post_propagate_funcs);

	if (tb_ctx->instr_hndlrs->init_instr_hndlrs)
		tb_ctx->instr_hndlrs->init_instr_hndlrs();

	tb_map_init_maps_drivers_from_raw_mode(&(tb_ctx->mem_map_driver),
			&(tb_ctx->reg_map_driver));

	// Initialising User taint policy.
	tb_ctx->policy_init = taint_policy->init_func;
	tb_ctx->policy_destroy = taint_policy->destroy_func;

	if (tb_ctx->policy_init)
		tb_ctx->policy_init();

	tb_ctx->get_taint_label = taint_policy->get_default_label;

	tb_ctx->intro_taint_reg_func = taint_policy->intro_taint_reg_func;
	tb_ctx->intro_taint_mem_func = taint_policy->intro_taint_mem_func;

	tb_ctx->new_ref_func = taint_policy->new_ref_tl_func;
	tb_ctx->insert_new_ref_func = taint_policy->insert_raw_new_ref_tl;

	tb_ctx->delete_ref_func = taint_policy->delete_ref_tl_func;
	tb_ctx->insert_delete_ref_func = taint_policy->insert_raw_delete_ref_tl;

	tb_ctx->insert_raw_meet = taint_policy->insert_raw_meet;

	tb_ctx->insert_propogate_func_1dst_1src =
			taint_policy->insert_raw_propogate_1dst_1src;
	tb_ctx->insert_propogate_func_1dst_2src =
			taint_policy->insert_raw_propogate_1dst_2src;

	tb_ctx->untaint_mem_func = taint_policy->untaint_mem_func;
	tb_ctx->insert_untaint_mem_func = taint_policy->insert_raw_untaint_mem;

	tb_ctx->untaint_reg_func = taint_policy->untaint_reg_func;
	tb_ctx->insert_untaint_reg_func = taint_policy->insert_raw_untaint_reg;

	tb_ctx->insert_spill_regs = taint_policy->insert_raw_spill_additional_regs;
	tb_ctx->insert_restore_regs =
			taint_policy->insert_raw_restore_additional_regs;

	// Initialise maps
	if (tb_ctx->mem_map_driver.init_map_func)
		tb_ctx->mem_map_driver.init_map_func(client_id);

	if (tb_ctx->reg_map_driver.init_map_func)
		tb_ctx->reg_map_driver.init_map_func(client_id);

	tb_ctx->mem_map = tb_ctx->mem_map_driver.create_map_func(tb_ctx, NULL);

	if (te_options->enable_fp) {

		tb_ctx->is_fast_path_mode = true;

		tb_fp_settings_t default_fp_settings;

		if (fp_settings == NULL) {
			tb_set_default_fp_settings(&default_fp_settings);
			fp_settings = &default_fp_settings;
		}

		tb_ctx->tool_info = tb_fast_path_init(client_id, tb_ctx, fp_settings);
	} else {
		tb_ctx->is_fast_path_mode = false;
		tb_ctx->tool_info = ib_register_instrum_tool();
	}

	return (void *) tb_ctx;
}

DR_EXPORT void *tb_simd_init(client_id_t client_id, IB_INSTRUM_OPT options,
		tb_options_t *te_options, tb_fp_settings_t *fp_settings,
		tb_raw_taint_policy_t *taint_policy) {

	DR_ASSERT(te_options);
	tb_context_t *tb_ctx = tb_init(client_id, options, te_options, fp_settings);

	// Initialise slots
	dr_raw_tls_calloc(&(tb_ctx->tls_raw_reg), &(tb_ctx->tls_raw_base), 6, 0);

	tb_ctx->instr_hndlrs = tb_ih_simd_init_instr_handlers(tb_ctx,
			taint_policy->pre_propagate_funcs,
			taint_policy->post_propagate_funcs);

	if (tb_ctx->instr_hndlrs->init_instr_hndlrs)
		tb_ctx->instr_hndlrs->init_instr_hndlrs();

	tb_map_init_maps_drivers_from_raw_mode(&(tb_ctx->mem_map_driver),
			&(tb_ctx->reg_map_driver));

	/**
	 *  Initialising User taint policy
	 */

	tb_ctx->policy_init = taint_policy->init_func;
	tb_ctx->policy_destroy = taint_policy->destroy_func;

	if (tb_ctx->policy_init)
		tb_ctx->policy_init();

	tb_ctx->get_taint_label = taint_policy->get_default_label;

	tb_ctx->intro_taint_reg_func = taint_policy->intro_taint_reg_func;
	tb_ctx->intro_taint_mem_func = taint_policy->intro_taint_mem_func;

	// Reference Management
	tb_ctx->new_ref_func = taint_policy->new_ref_tl_func;
	tb_ctx->insert_new_ref_func = taint_policy->insert_raw_new_ref_tl;
	tb_ctx->insert_simd_new_ref_func = taint_policy->insert_simd_new_ref_tl;

	tb_ctx->delete_ref_func = taint_policy->delete_ref_tl_func;
	tb_ctx->insert_delete_ref_func = taint_policy->insert_raw_delete_ref_tl;
	tb_ctx->insert_simd_delete_ref_func =
			taint_policy->insert_simd_delete_ref_tl;

	// Taint Primitives
	tb_ctx->insert_raw_meet = taint_policy->insert_raw_meet;
	tb_ctx->insert_simd_meet = taint_policy->insert_simd_meet;

	tb_ctx->insert_propogate_func_1dst_1src =
			taint_policy->insert_raw_propogate_1dst_1src;
	tb_ctx->insert_propogate_func_1dst_2src =
			taint_policy->insert_raw_propogate_1dst_2src;

	tb_ctx->insert_simd_propogate_func_1dst_1src =
			taint_policy->insert_simd_propogate_1dst_1src;
	tb_ctx->insert_simd_propogate_func_1dst_2src =
			taint_policy->insert_simd_propogate_1dst_2src;

	// Event Handlers
	tb_ctx->untaint_mem_func = taint_policy->untaint_mem_func;
	tb_ctx->insert_untaint_mem_func = taint_policy->insert_raw_untaint_mem;
	tb_ctx->insert_simd_untaint_mem_func =
			taint_policy->insert_simd_untaint_mem;

	tb_ctx->untaint_reg_func = taint_policy->untaint_reg_func;
	tb_ctx->insert_untaint_reg_func = taint_policy->insert_raw_untaint_reg;
	tb_ctx->insert_simd_untaint_reg_func =
			taint_policy->insert_simd_untaint_reg;

	tb_ctx->insert_spill_regs = taint_policy->insert_raw_spill_additional_regs;
	tb_ctx->insert_restore_regs =
			taint_policy->insert_raw_restore_additional_regs;

	// Initialise maps
	if (tb_ctx->mem_map_driver.init_map_func)
		tb_ctx->mem_map_driver.init_map_func(client_id);

	if (tb_ctx->reg_map_driver.init_map_func)
		tb_ctx->reg_map_driver.init_map_func(client_id);

	tb_ctx->mem_map = tb_ctx->mem_map_driver.create_map_func(tb_ctx, NULL);

	if (te_options->enable_fp) {

		tb_fp_settings_t default_fp_settings;

		if (fp_settings == NULL) {
			tb_set_default_fp_settings(&default_fp_settings);
			fp_settings = &default_fp_settings;
		}

		tb_ctx->tool_info = tb_fast_path_init(client_id, tb_ctx, fp_settings);
	} else {
		tb_ctx->is_fast_path_mode = false;
		tb_ctx->tool_info = ib_register_instrum_tool();
	}

	return (void *) tb_ctx;
}

static tb_context_t *tb_init(client_id_t client_id, IB_INSTRUM_OPT options,
		tb_options_t *te_options, tb_fp_settings_t *fp_settings) {

	// Initialise DR manager
	drmgr_init();
	drutil_init();

	DR_ASSERT(ib_is_initialised());

	tb_context_t *tb_ctx = dr_global_alloc(sizeof(tb_context_t));
	memset(tb_ctx, 0, sizeof(tb_context_t));

	DR_ASSERT(tb_ctx);

	tb_syscall_handlers_init(client_id, tb_ctx);

	tb_ctx->tls_id = drmgr_register_tls_field();
	tb_ctx->instrum_options = options;

	// Register thread hooks.
	if (!drmgr_register_thread_init_event_user_data(tb_thread_init, NULL,
			tb_ctx)
			|| !drmgr_register_thread_exit_event_user_data(tb_thread_exit, NULL,
					tb_ctx)) {
		DR_ASSERT(false);
		return NULL;
	}

	tb_ctx->is_inline = te_options->enable_inline;
	tb_ctx->is_taint_switch_enabled = te_options->enable_taint_off;
	tb_ctx->is_fast_path_mode = te_options->enable_fp;

	tb_init_annotation_handler(tb_ctx);

	return tb_ctx;
}

DR_EXPORT void tb_register_hooks(void *tb_ctx_opaque) {

	DR_ASSERT(tb_ctx_opaque);
	tb_register_instrumentation_hooks((tb_context_t *) tb_ctx_opaque);
}

DR_EXPORT void tb_cc_exit(void *tb_ctx_opaque) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	DR_ASSERT(tb_ctx);

	if (tb_ctx->is_fast_path_mode) {
		tb_fast_path_exit();
	}

	dr_raw_tls_cfree(tb_ctx->tls_raw_base, 4);

	tb_exit(tb_ctx);
}

DR_EXPORT void tb_raw_exit(void *tb_ctx_opaque) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	DR_ASSERT(tb_ctx);

	if (tb_ctx->is_fast_path_mode) {
		tb_fast_path_exit();
	}

	dr_raw_tls_cfree(tb_ctx->tls_raw_base, 6);

	tb_exit(tb_ctx);
}

DR_EXPORT void tb_simd_exit(void *tb_ctx_opaque) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	DR_ASSERT(tb_ctx);

	if (tb_ctx->is_fast_path_mode) {
		tb_fast_path_exit();
	}

	dr_raw_tls_cfree(tb_ctx->tls_raw_base, 6);

	tb_exit(tb_ctx);
}

static void tb_exit(tb_context_t *tb_ctx) {

	DR_ASSERT(tb_ctx != NULL);

	if (tb_ctx->instr_hndlrs->destroy_instr_hndlrs)
		tb_ctx->instr_hndlrs->destroy_instr_hndlrs();

	tb_ih_cc_destroy_instr_hndlrs(tb_ctx->instr_hndlrs);

	tb_ctx->mem_map_driver.destroy_map_func(tb_ctx->mem_map,
			tb_ctx->delete_ref_func, tb_ctx);

	if (tb_ctx->policy_destroy)
		tb_ctx->policy_destroy();

	if (tb_ctx->mem_map_driver.exit_map_func)
		tb_ctx->mem_map_driver.exit_map_func();

	if (tb_ctx->reg_map_driver.exit_map_func)
		tb_ctx->reg_map_driver.exit_map_func();

	if (!drmgr_unregister_thread_init_event_user_data(tb_thread_init)
			|| !drmgr_unregister_thread_exit_event_user_data(tb_thread_exit))
		DR_ASSERT(false);

	drmgr_unregister_tls_field(tb_ctx->tls_id);

	tb_syscall_handlers_destroy();

	ib_unregister_instrum_tool(tb_ctx->tool_info);

	dr_global_free(tb_ctx, sizeof(tb_context_t));

	drutil_exit();
	drmgr_exit();
}

static void tb_thread_init(void *drcontext, void *tb_ctx_opaque) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	tb_per_thrd_t *per_thrd = (tb_per_thrd_t *) dr_thread_alloc(drcontext,
			sizeof(tb_per_thrd_t));

	per_thrd->reg_map = tb_ctx->reg_map_driver.create_map_func(tb_ctx,
			&(per_thrd->reg_map_start));
	tb_set_reg_map(tb_ctx, per_thrd->reg_map);
	per_thrd->analysis_switch = true;
	tb_set_reg_analysis_switch(tb_ctx, true);

	drmgr_set_tls_field(drcontext, tb_ctx->tls_id, per_thrd);
}

/**
 *  Called upon thread exit. Destroys thread data
 */
static void tb_thread_exit(void *drcontext, void *tb_ctx_opaque) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

// We use drmgr tls field to access reg map, because the current drcontext could
// be of another thread.

	tb_per_thrd_t *per_thrd = (tb_per_thrd_t *) drmgr_get_tls_field(drcontext,
			tb_ctx->tls_id);

	tb_ctx->reg_map_driver.destroy_map_func(per_thrd->reg_map_start,
			tb_ctx->delete_ref_func, tb_ctx);

	dr_thread_free(drcontext, per_thrd, sizeof(tb_per_thrd_t));
}

/***************************************************************************
 *  Introducing Taint Data
 */

DR_EXPORT void tb_taint_mem_block(void *tb_ctx_opaque, uintptr_t start_addr,
		size_t size, void *taint_label) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	if (tb_ctx->new_ref_func)
		tb_ctx->new_ref_func(taint_label);

	tb_ta_cc_intro_taint_mem_block(tb_ctx, start_addr, (int) size, taint_label);

	if (tb_ctx->delete_ref_func)
		tb_ctx->delete_ref_func(taint_label);
}

DR_EXPORT void tb_taint_mem(void *tb_ctx_opaque, uintptr_t addr,
		void *taint_label) {
	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	tb_ta_cc_intro_taint_mem(tb_ctx, addr, taint_label);
}

DR_EXPORT void tb_taint_reg(void *tb_ctx_opaque, void *drcontext,
		reg_id_t reg_id, void *taint_label) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	size_t reg_size = ub_get_reg_size(reg_id);
	unsigned int reg_byte = ub_get_byte_id(reg_id, 0);
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = reg_byte; i < reg_byte + reg_size; i++)
		tb_ta_cc_intro_taint_reg(tb_ctx, reg_map, i, taint_label);

	if (tb_ctx->is_fast_path_mode) {
		uint32_t reg_id_mask = tb_fast_path_get_reg_mask(reg_id);
		uint32_t reg_state = tb_get_fp_reg_state(tb_ctx);
		reg_state |= reg_id_mask;
		tb_set_fp_reg_state(tb_ctx, reg_state);
	}
}

DR_EXPORT void tb_taint_reg_byte(void *tb_ctx_opaque, void *drcontext,
		reg_id_t reg_id, unsigned int byte_index, void *taint_label) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	unsigned int reg_byte_id = ub_get_byte_id(reg_id, byte_index);
	void *reg_map = tb_get_reg_map(tb_ctx);
	tb_ta_cc_intro_taint_reg(tb_ctx, reg_map, reg_byte_id, taint_label);

	if (tb_ctx->is_fast_path_mode) {
		uint32_t reg_id_mask = tb_fast_path_get_reg_mask(reg_id);
		uint32_t reg_state = tb_get_fp_reg_state(tb_ctx);
		reg_state |= reg_id_mask;
		tb_set_fp_reg_state(tb_ctx, reg_state);
	}
}

DR_EXPORT void tb_untaint_mem_block(void *tb_ctx_opaque, uintptr_t start_addr,
		size_t size) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	tb_ta_cc_set_untaint_mem_block(tb_ctx, start_addr, size);
}

DR_EXPORT void tb_untaint_mem(void *tb_ctx_opaque, uintptr_t addr) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	tb_ta_cc_set_untaint_mem(tb_ctx, addr);
}

DR_EXPORT void tb_untaint_reg(void *tb_ctx_opaque, void *drcontext,
		reg_id_t reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	unsigned int reg_byte_id = ub_get_byte_id(reg_id, 0);
	void *reg_map = tb_get_reg_map(tb_ctx);
	size_t reg_size = ub_get_reg_size(reg_id);

	for (size_t i = reg_byte_id; i < reg_byte_id + reg_size; i++)
		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, i);

	if (tb_ctx->is_fast_path_mode) {
		uint32_t reg_id_mask = tb_fast_path_get_reg_mask(reg_id);
		uint32_t reg_state = tb_get_fp_reg_state(tb_ctx);
		reg_state &= ~reg_id_mask;
		tb_set_fp_reg_state(tb_ctx, reg_state);
	}
}

DR_EXPORT void tb_untaint_reg_byte(void *tb_ctx_opaque, void *drcontext,
		reg_id_t reg_id, unsigned int byte_index) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	unsigned int reg_byte_id = ub_get_byte_id(reg_id, byte_index);
	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, reg_byte_id);

	if (tb_ctx->is_fast_path_mode) {

		if (!tb_is_some_reg_byte_tainted(tb_ctx, drcontext, reg_id)) {
			uint32_t reg_id_mask = tb_fast_path_get_reg_mask(reg_id);
			uint32_t reg_state = tb_get_fp_reg_state(tb_ctx);
			reg_state &= ~reg_id_mask;
			tb_set_fp_reg_state(tb_ctx, reg_state);
		}
	}

}

/****************************************************************************************
 *  Retrieving Taint Information
 */

DR_EXPORT bool tb_is_mem_tainted(void *tb_ctx_opaque, uintptr_t addr) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	return tb_ta_cc_is_all_mem_tainted(tb_ctx, addr, 1);
}

DR_EXPORT bool tb_is_some_mem_tainted(void *tb_ctx_opaque, uintptr_t start_addr,
		size_t block_size) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	return tb_ta_cc_is_some_mem_tainted(tb_ctx, start_addr, block_size);
}

DR_EXPORT bool tb_is_mem_all_tainted(void *tb_ctx_opaque, uintptr_t start_addr,
		size_t block_size) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	return tb_ta_cc_is_all_mem_tainted(tb_ctx, start_addr, block_size);
}

DR_EXPORT bool tb_is_some_reg_byte_tainted(void *tb_ctx_opaque, void* drcontext,
		reg_id_t reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	return tb_ta_cc_is_some_reg_tainted(tb_ctx, reg_map,
			ub_get_byte_id(reg_id, 0), ub_get_reg_size(reg_id));
}

DR_EXPORT bool tb_is_all_reg_tainted(void *tb_ctx_opaque, void* drcontext,
		reg_id_t reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);

	return tb_ta_cc_is_all_reg_tainted(tb_ctx, reg_map,
			ub_get_byte_id(reg_id, 0), ub_get_reg_size(reg_id));
}

DR_EXPORT bool tb_is_reg_byte_tainted(void *tb_ctx_opaque, void* drcontext,
		reg_id_t reg_id, unsigned long byte_index) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	return tb_ta_cc_is_all_reg_tainted(tb_ctx, reg_map,
			ub_get_byte_id(reg_id, 0), 1);
}

DR_EXPORT bool tb_is_reg_byte_tainted_via_byte_id(void *tb_ctx_opaque,
		void* drcontext, uintptr_t reg_byte_id) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	return tb_ta_cc_is_all_reg_tainted(tb_ctx, reg_map, reg_byte_id, 1);
}

DR_EXPORT bool tb_is_all_reg_block_tainted_via_byte_id(void *tb_ctx_opaque,
		void* drcontext, uintptr_t reg_byte_id, size_t block_size) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	return tb_ta_cc_is_all_reg_tainted(tb_ctx, reg_map, reg_byte_id, block_size);
}

DR_EXPORT bool tb_is_some_reg_block_tainted_via_byte_id(void *tb_ctx_opaque,
		void* drcontext, uintptr_t reg_byte_id, size_t block_size) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	return tb_ta_cc_is_some_reg_tainted(tb_ctx, reg_map, reg_byte_id,
			block_size);
}

DR_EXPORT void * tb_mem_get_taint_label(void *tb_ctx_opaque, uintptr_t addr) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	return tb_ta_cc_get_mem_label(tb_ctx, addr);
}

DR_EXPORT void *tb_get_reg_byte_taint_label(void *tb_ctx_opaque,
		void* drcontext, reg_id_t reg_id, unsigned long byte_index) {
	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	return tb_ta_cc_get_reg_label(tb_ctx, reg_map,
			ub_get_byte_id(reg_id, byte_index));
}

DR_EXPORT void *tb_get_reg_byte_taint_label_via_byte_id(void *tb_ctx_opaque,
		void* drcontext, uintptr_t reg_byte_id) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	void *reg_map = tb_get_reg_map(tb_ctx);
	return tb_ta_cc_get_reg_label(tb_ctx, reg_map, reg_byte_id);
}

/**
 * Retrieval via insert
 */

DR_EXPORT void tb_insert_get_mem_label(void *tb_ctx_opaque, void *drcontext,
		instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
		reg_id_t scratch_reg) {

	tb_ta_raw_insert_get_mem_label(tb_ctx_opaque, drcontext, ilist, where,
			addr_reg, scratch_reg);
}

DR_EXPORT void tb_insert_get_reg_label(void *tb_ctx_opaque, void *drcontext,
		instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
		reg_id_t label_reg) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	tb_raw_arraymap_insert_load_reg_map(tb_ctx, drcontext, ilist, where,
			map_reg);
	tb_ta_raw_insert_get_reg_label(tb_ctx, drcontext, ilist, where, map_reg,
			label_reg);
}

DR_EXPORT void tb_insert_is_some_reg_tainted_via_reg(void *tb_ctx_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t id_reg,
		reg_id_t map_reg, reg_id_t vector_reg, size_t block_size,
		instr_t *true_case) {

	DR_ASSERT(reg_is_gpr(id_reg));
	DR_ASSERT(reg_is_gpr(map_reg));
	DR_ASSERT(reg_is_xmm(vector_reg));

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	tb_raw_arraymap_insert_load_reg_map(tb_ctx, drcontext, ilist, where,
			map_reg);

	tb_ta_simd_insert_is_some_reg_tainted_via_reg(tb_ctx, drcontext, ilist,
			where, map_reg, id_reg, vector_reg, block_size, true_case);
}

DR_EXPORT void tb_insert_is_some_reg_tainted(void *tb_ctx_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
		unsigned int reg_byte_id, reg_id_t vector_reg,
		reg_id_t scaler_scratch_reg, size_t block_size, instr_t *true_case) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	tb_raw_arraymap_insert_load_reg_map(tb_ctx, drcontext, ilist, where,
			map_reg);

	tb_ta_simd_insert_is_some_reg_tainted(tb_ctx, drcontext, ilist, where,
			map_reg, reg_byte_id, vector_reg, scaler_scratch_reg, block_size,
			true_case);
}

DR_EXPORT void tb_insert_is_some_mem_tainted(void *tb_ctx_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
		reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
		instr_t *true_case) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	tb_ta_simd_insert_is_some_mem_tainted(tb_ctx, drcontext, ilist, where,
			addr_reg, vector_reg, scratch_reg, block_size, true_case);
}

DR_EXPORT void tb_insert_is_all_reg_tainted_via_reg(void *tb_ctx_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t id_reg,
		reg_id_t map_reg, reg_id_t vector_reg, size_t block_size,
		instr_t *false_case) {

	DR_ASSERT(reg_is_gpr(id_reg));
	DR_ASSERT(reg_is_gpr(map_reg));
	DR_ASSERT(reg_is_xmm(vector_reg));

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	tb_raw_arraymap_insert_load_reg_map(tb_ctx, drcontext, ilist, where,
			map_reg);

	tb_ta_simd_insert_is_all_reg_tainted_via_reg(tb_ctx, drcontext, ilist,
			where, map_reg, id_reg, vector_reg, block_size, false_case);
}

DR_EXPORT void tb_insert_is_all_reg_tainted(void *tb_ctx_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
		unsigned int reg_byte_id, reg_id_t vector_reg,
		reg_id_t scaler_scratch_reg, size_t block_size, instr_t *false_case) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	tb_raw_arraymap_insert_load_reg_map(tb_ctx, drcontext, ilist, where,
			map_reg);

	tb_ta_simd_insert_is_all_reg_tainted(tb_ctx, drcontext, ilist, where,
			map_reg, reg_byte_id, vector_reg, scaler_scratch_reg, block_size,
			false_case);
}

DR_EXPORT void tb_insert_is_all_mem_tainted(void *tb_ctx_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
		reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
		instr_t *false_case) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;
	tb_ta_simd_insert_is_all_mem_tainted(tb_ctx, drcontext, ilist, where,
			addr_reg, vector_reg, scratch_reg, block_size, false_case);
}

/****************************************************************************************
 *  Analysis Switch
 */

DR_EXPORT void tb_turn_on_analysis(void *tb_ctx_opaque, void *drcontext) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	DR_ASSERT_MSG(tb_ctx->is_taint_switch_enabled,
			"Taint Switch is not enabled. I set this off by"
					"default to avoid performing runtime checks.");

	tb_per_thrd_t *per_thrd = (tb_per_thrd_t *) drmgr_get_tls_field(drcontext,
			tb_ctx->tls_id);
	per_thrd->analysis_switch = true;
	tb_set_reg_analysis_switch(tb_ctx, true);
}

DR_EXPORT void tb_turn_off_analysis(void *tb_ctx_opaque, void *drcontext) {

// Not yet implemented
	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	DR_ASSERT_MSG(tb_ctx->is_taint_switch_enabled,
			"Taint Switch is not enabled. I set this off by"
					"default to avoid performing runtime checks.");

	tb_per_thrd_t *per_thrd = (tb_per_thrd_t *) drmgr_get_tls_field(drcontext,
			tb_ctx->tls_id);
	per_thrd->analysis_switch = false;
	tb_set_reg_analysis_switch(tb_ctx, false);
}

DR_EXPORT bool tb_is_analysis_on(void *tb_ctx_opaque, void *drcontext) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	if (!tb_ctx->is_taint_switch_enabled)
		return true;

	tb_per_thrd_t *per_thrd = (tb_per_thrd_t *) drmgr_get_tls_field(drcontext,
			tb_ctx->tls_id);
	return per_thrd->analysis_switch;
}

DR_EXPORT void tb_insert_is_analysis_on(void *drcontext, instrlist_t *ilist,
		instr_t *where, void *tb_ctx_opaque, instr_t* false_label) {

	tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

	if (tb_ctx->is_taint_switch_enabled) {

		opnd_t switch_analysis_opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx,
		TB_RAW_SLOT_IDX_ANALYSIS_SWITCH);

		ub_instrum_check_mem_null_true_case(drcontext, ilist, where, NULL,
				&switch_analysis_opnd, false_label);
	}
}
