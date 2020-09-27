/*
 * tb_fp_helper.h
 *
 *  Created on: 26 Jul 2019
 *      Author: john
 */

#ifndef OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_HELPER_H_
#define OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_HELPER_H_

#include "utility_bunny.h"

#define ALIGN_FORWARD(x, alignment) \
    ((((ptr_uint_t)x) + ((alignment)-1)) & (~((alignment)-1)))

typedef struct {
    ub_in_out_set_t in_out_set;
    ub_in_out_set_t out_reg_set;
    bool contains_rep;
} tb_fp_in_out_data_t;

void tb_fp_init_index_map();

uint32_t tb_fp_internal_get_reg_mask(reg_id_t reg_id);

void *tb_fp_analyse_set_up_taint_state(uint case_val,
        ub_in_out_set_t *in_out_set);

uint32_t tb_fp_get_default_val(ub_in_out_set_t *in_out_set);

void tb_fp_fetch_tainted_out_regs(void *drcontext, void *taint_state,
		void *reg_list, void **tainted_out_list);

void ub_destroy_thread_alloc_opnd(void *del_opnd);

#endif /* OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_HELPER_H_ */
