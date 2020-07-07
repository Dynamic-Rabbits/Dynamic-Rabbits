/*
 * tb_cc_taint_policy.h
 *
 *  Created on: 19 Jul 2018
 *      Author: john
 */

#ifndef TAINT_POLICIES_TB_CC_TAINT_POLICY_H_
#define TAINT_POLICIES_TB_CC_TAINT_POLICY_H_

#include <stddef.h>
#include "utility_bunny.h"
#include "instrumentation_bunny.h"
#include "tb_cc_prepost.h"

typedef void (*tb_cc_init_func_t)();
typedef void (*tb_cc_destroy_func_t)();

typedef void (*tb_cc_intro_taint_mem_func_t)(uintptr_t, void *);
typedef void (*tb_cc_intro_taint_reg_func_t)(unsigned int, void *);

typedef bool (*tb_cc_meet_srcs_func_t)(void **, void *);
typedef void * (*tb_cc_propogate_1dst_1src_func_t)(void *);
typedef void * (*tb_cc_propogate_1dst_2src_func_t)(void *, void *);
typedef void * (*tb_cc_propogate_1dst_3src_func_t)(void *, void *, void *);
typedef void * (*tb_cc_propogate_1dst_4src_func_t)(void *, void *, void *, void *);

typedef void (*tb_cc_new_ref_tl_func_t)(void *);
typedef void (*tb_cc_delete_ref_tl_func_t)(void *);

typedef void (*tb_cc_untaint_mem_func_t)(uintptr_t addr, void *);
typedef void (*tb_cc_untaint_reg_func_t)(unsigned int reg_byte_id, void *);

typedef void (*tb_cc_handle_unsup_instr_func_t)(instr_t *, bool is_dsr_tainted,
		bool is_src_tainted);

typedef void * (*tb_cc_get_default_label_t)();

typedef struct {

    tb_cc_init_func_t init_func;
    tb_cc_destroy_func_t destroy_func;

	tb_cc_intro_taint_mem_func_t intro_taint_mem_func;
	tb_cc_intro_taint_reg_func_t intro_taint_reg_func;

	// Taint Primitives
	tb_cc_meet_srcs_func_t meet_func;

    tb_cc_propogate_1dst_1src_func_t propagate_1dst_1src_func;
	tb_cc_propogate_1dst_2src_func_t propagate_1dst_2src_func;

	tb_cc_new_ref_tl_func_t new_ref_tl_func;
	tb_cc_delete_ref_tl_func_t delete_ref_tl_func;

	tb_taint_prepost_info_t *pre_propagate_funcs;
	tb_taint_prepost_info_t *post_propagate_funcs;

	tb_cc_untaint_mem_func_t untaint_mem_func;
	tb_cc_untaint_reg_func_t untaint_reg_func;

	tb_cc_get_default_label_t get_default_label;

} tb_cc_taint_policy_t;

#endif /* TAINT_POLICIES_TB_CC_TAINT_POLICY_H_ */
