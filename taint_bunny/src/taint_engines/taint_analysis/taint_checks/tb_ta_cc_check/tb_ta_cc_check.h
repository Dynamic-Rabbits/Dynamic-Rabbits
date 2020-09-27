/*
 * tb_ta_cc_check.h
 *
 *  Created on: 25 Nov 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_CC_CHECK_TB_TA_CC_CHECK_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_CC_CHECK_TB_TA_CC_CHECK_H_

#include "../../../../tb_bunny_private.h"

#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"


#include <stdint.h>
#include "utility_bunny.h"

void* tb_ta_cc_get_mem_label(tb_context_t *tb_ctx, uintptr_t addr);

void tb_ta_cc_get_mem_labels_from_block(tb_context_t *tb_ctx, uintptr_t addr,
        size_t block_size, size_t label_buf_size, void **label_buf);

void* tb_ta_cc_get_reg_label(tb_context_t *tb_ctx, void *taint_map,
        unsigned byte_id);

bool tb_ta_cc_is_some_reg_tainted(tb_context_t *tb_ctx, void *taint_map,
        uintptr_t start_id, size_t block_size);

bool tb_ta_cc_is_some_mem_tainted(tb_context_t *tb_ctx, uintptr_t start_id,
        size_t block_size);

bool tb_ta_cc_is_some_reg_tainted(tb_context_t *tb_ctx, void *taint_map,
        uintptr_t start_id, size_t block_size);

bool tb_ta_cc_is_all_mem_tainted(tb_context_t *tb_ctx, uintptr_t start_id,
        size_t block_size);

bool tb_ta_cc_is_all_reg_tainted(tb_context_t *tb_ctx, void *taint_map,
        uintptr_t start_id, size_t block_size);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_CC_CHECK_TB_TA_CC_CHECK_H_ */
