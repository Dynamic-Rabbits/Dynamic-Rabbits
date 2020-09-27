/*
 * tb_fp_stage_one.h
 *
 *  Created on: 24 Jul 2019
 *      Author: john
 */

#ifndef OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_H_
#define OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_H_

#include "../../tb_bunny_private.h"

bool tb_fp_set_starting_cases(void *drbbdup_ctx, void *drcontext,
		instrlist_t *bb, bool *options,
		uint *default_case_value, size_t required_size,
		float bb_in_out_threshold, size_t pop_limit);

void* tb_fp_initial_analysis(void *drcontext, instrlist_t *bb);

void tb_fp_destroy_initial_analysis(void *drcontext, void *pre_analysis_data);

size_t tb_fp_analyse_for_fast_path(void *drcontext, instrlist_t *bb,
		uint case_val, drvector_t *action, void *pre_analysis_data,
		void **post_data);

bool tb_fp_allow_generation(void *drbbdup_ctx, void *drcontext, void *tag,
		instrlist_t *bb, uint dynamic_case, bool *enable_dynamic_fp,
		void *user_data);

void tb_fp_check_inouts(tb_context_t *tb_ctx, void *drcontext, instrlist_t *bb,
		instr_t *where, void *pre_analysis_data);

void tb_fp_update_reg_map_with_taint_data(tb_context_t *tb_ctx, void *drcontext,
		instrlist_t *bb, instr_t *where, void *out_reg_list,
		void *out_taint_regs);

#endif /* OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_H_ */
