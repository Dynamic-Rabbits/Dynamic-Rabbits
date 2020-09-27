/*
 * ib_bbdup_instrum.h
 *
 *  Created on: 6 Mar 2019
 *      Author: john
 */

#ifndef BBDUP_INSTRUM_IB_BBDUP_INSTRUM_H_
#define BBDUP_INSTRUM_IB_BBDUP_INSTRUM_H_

#include "dr_api.h"
#include "dr_defines.h"
#include <stdint.h>
#include <drbbdup.h>

bool ib_create_default_manager(void *drbbdup_ctx, void *drcontext, void *tag,
        instrlist_t *bb, bool *enable_dynamic_fp,
        uint *default_case_value, void *user_data);

void ib_pre_analyse_bb(void *drcontext, instrlist_t *bb,
        void *user_data, void **pre_analysis_result);

void ib_destroy_pre_analysis(void *drcontext, void *user_data,
        void *pre_analysis_result);

void ib_analyse_bb(void *drcontext, instrlist_t *bb,
        uint case_val, void *user_data, void *pre_analysis_data,
        void **analysis_result);

void ib_destroy_analysis(void *drcontext, void *user_data,
        void *pre_analysis_data, void *delete_analysis_result);

void ib_instrument_bb(void *drcontext, instrlist_t *bb,
		instr_t *instr, instr_t *where, uint case_val, void *user_data, void *pre_analysis_data,
        void *analysis_data);

void ib_nan_instrument_bb(void *drcontext, instrlist_t *bb,
        instr_t *where, void *user_data);

void ib_get_comparator(void *drcontext, instrlist_t *bb,
        instr_t *where, void *user_data, void *pre_analysis_data);

bool ib_allow_dynamic_fast_generation(void *drbbdup_ctx, void *drcontext,
		void *tag, instrlist_t *ilist, uint dynamic_case,
		bool *enable_dynamic_fp, void *user_data);

#endif /* BBDUP_INSTRUM_IB_BBDUP_INSTRUM_H_ */
