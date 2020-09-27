/*
 * tb_ta_raw_check.h
 *
 *  Created on: 25 Nov 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_RAW_CHECK_TB_TA_RAW_CHECK_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_RAW_CHECK_TB_TA_RAW_CHECK_H_

#include "../../../../tb_bunny_private.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"

#include <stdint.h>
#include "utility_bunny.h"

void tb_ta_raw_insert_get_mem_label(tb_context_t *tb_ctx, void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t label_reg, reg_id_t scratch_reg);

void tb_ta_raw_insert_get_reg_label(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
         reg_id_t label_reg);

void tb_ta_raw_insert_is_some_reg_tainted_via_reg(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t id_reg, size_t block_size,
        instr_t *true_case);

void tb_ta_raw_insert_is_some_reg_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t scratch_reg, size_t block_size,
        instr_t *true_case);

void tb_ta_raw_insert_is_some_mem_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, reg_id_t addr_reg,
        reg_id_t scratch_reg2, size_t block_size, instr_t *true_case);

void tb_ta_raw_is_all_reg_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t scratch_reg, size_t block_size,
        instr_t *false_case);

void tb_ta_raw_is_all_mem_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, reg_id_t addr_reg,
        reg_id_t scratch_reg2, size_t block_size, instr_t *false_case);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_RAW_CHECK_TB_TA_RAW_CHECK_H_ */
