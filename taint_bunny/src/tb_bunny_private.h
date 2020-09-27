/*
 * tb_bunny_private.h
 *
 *  Created on: 26 Jul 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_TB_BUNNY_PRIVATE_H_
#define TAINT_ENGINES_TB_BUNNY_PRIVATE_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "tb_defines.h"
#include "drext.h"
#include <stdint.h>
#include "tb_defines.h"

#include "taint_engines/instr_handlers/tb_instruction_handler.h"
#include "taint_engines/taint_analysis/taint_maps/tb_cc_map_driver.h"

#include "taint_policies/tb_cc_taint_policy.h"
#include "taint_policies/tb_raw_taint_policy.h"

#include "utility_bunny.h"
#include "instrumentation_bunny.h"

/***************************************************************************
 *  Structs and Definitions
 */

/**
 *  @struct prop_comp_info_t
 *  Contains information of an operand for taint propagation
 *  purposes. The information is retreived from opnd and comp slots.
 *
 *  @param size The size of the operand.
 *  @param opnd The starting opnd identifier.
 *  @param taint_map The appropriate taint map for the opnd.
 *  @oaram approx The appropriate approximation for the opnd.
 */
typedef struct {
	size_t size;
	uintptr_t opnd;
	byte conc[16];
	loc_t type;
	void *taint_map;
	bool increment_in_rep;
} taint_opnd_info_t;

/**
 *  @struct tb_context_t
 *
 *  A struct containing Containing a variety of structures to
 *  perform taint tracking.
 *
 */
typedef struct {

	void *mem_map;

	/* TODO fix this to use the union of structs. Don't know what I was thinking here: */
	tb_cc_intro_taint_reg_func_t intro_taint_reg_func;
	tb_cc_intro_taint_mem_func_t intro_taint_mem_func;

	tb_cc_new_ref_tl_func_t new_ref_func;
	tb_raw_insert_new_ref_tl_func_t insert_new_ref_func;
	tb_simd_insert_new_ref_tl_func_t insert_simd_new_ref_func;

	tb_cc_delete_ref_tl_func_t delete_ref_func;
	tb_raw_insert_delete_ref_tl_func_t insert_delete_ref_func;
	tb_simd_insert_delete_ref_tl_func_t insert_simd_delete_ref_func;

	tb_cc_meet_srcs_func_t meet_func;
    tb_raw_insert_meet_func_t insert_raw_meet;
    tb_simd_insert_meet_func_t insert_simd_meet;

    tb_cc_init_func_t policy_init;
    tb_cc_destroy_func_t policy_destroy;

    tb_cc_propogate_1dst_1src_func_t propogate_func_1dst_1src;
    tb_raw_insert_propogate_1dst_1src_func_t insert_propogate_func_1dst_1src;
    tb_simd_insert_propogate_1dst_1src_func_t insert_simd_propogate_func_1dst_1src;

    tb_cc_propogate_1dst_2src_func_t propogate_func_1dst_2src;
    tb_raw_insert_propogate_1dst_2src_func_t insert_propogate_func_1dst_2src;
	tb_simd_insert_propogate_1dst_2src_func_t insert_simd_propogate_func_1dst_2src;

	tb_cc_untaint_mem_func_t untaint_mem_func;
	tb_raw_insert_untaint_mem_func_t insert_untaint_mem_func;
	tb_simd_insert_untaint_mem_func_t insert_simd_untaint_mem_func;

	tb_cc_untaint_reg_func_t untaint_reg_func;
	tb_raw_insert_untaint_reg_func_t insert_untaint_reg_func;
	tb_simd_insert_untaint_reg_func_t insert_simd_untaint_reg_func;

	tb_raw_insert_spill_regs_func_t insert_spill_regs;
	tb_raw_insert_restore_regs_func_t insert_restore_regs;

	tb_cc_get_default_label_t get_taint_label;

	tb_te_instr_hndlrs_t *instr_hndlrs;

	// These are drivers that enable the access of map functionality.
	tb_map_driver_t reg_map_driver;
	tb_map_driver_t mem_map_driver;

	void *tool_info;
	bool is_inline;
    bool is_taint_switch_enabled;

	bool is_fast_path_mode;
	IB_INSTRUM_OPT instrum_options;

	reg_id_t tls_raw_reg;
	uint tls_raw_base;
	int tls_id;

	void *bit_mem_tracker_ctx;
} tb_context_t;

typedef struct{

    void *reg_map; /*aligned */
    void *reg_map_start;
    bool analysis_switch;
}tb_per_thrd_t;


typedef struct{

    tb_cc_pre_propagate_func_t pre_propagation_func;
    tb_cc_post_propagate_func_t post_propagation_func;
}tb_cc_instr_info_t;



#endif /* TAINT_ENGINES_TB_BUNNY_PRIVATE_H_ */
