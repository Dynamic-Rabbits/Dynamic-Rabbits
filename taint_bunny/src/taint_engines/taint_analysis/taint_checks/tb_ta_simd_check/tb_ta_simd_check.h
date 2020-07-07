/*
 * tb_ta_simd_check.h
 *
 *  Created on: 20 Dec 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_SIMD_CHECK_TB_TA_SIMD_CHECK_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_SIMD_CHECK_TB_TA_SIMD_CHECK_H_

#include "../../../../tb_bunny_private.h"

#include "../../tb_simd_taint_analysis/tb_ta_simd_byt_functionality.h"
#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"

#include <stdint.h>
#include "utility_bunny.h"

void tb_ta_simd_insert_get_mem_label(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *tl_opnd, reg_id_t vector_label_reg);

void tb_ta_simd_insert_get_reg_label(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, size_t size, reg_id_t veclabel_reg);

void tb_ta_simd_insert_is_some_reg_tainted_via_reg(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t id_reg, reg_id_t vector_reg,  size_t block_size,
        instr_t *true_case);

void tb_ta_simd_insert_is_some_reg_tainted(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t vector_reg,
        reg_id_t scaler_scratch_reg, size_t block_size, instr_t *true_case);

void tb_ta_simd_insert_is_some_mem_tainted(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
        instr_t *true_case);

void tb_ta_simd_insert_is_all_reg_tainted_via_reg(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_t id_reg, reg_id_t vector_reg,
        size_t block_size, instr_t *false_case);

void tb_ta_simd_insert_is_all_reg_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t vector_reg,
        reg_id_t scaler_scratch_reg, size_t block_size, instr_t *false_case);

void tb_ta_simd_insert_is_all_mem_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
        instr_t *false_case);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TAINT_CHECKS_TB_TA_SIMD_CHECK_TB_TA_SIMD_CHECK_H_ */
