/*
 * te_in_max6_shadow_mem_maps.h
 *
 *  Created on: 8 Jul 2018
 *      Author: john
 */

#ifndef TAINT_MAPS_MEMORY_MAPS_TB_IN_MAX6_MEM_MAPS_TE_IN_MAX6_SHADOW_MEM_MAPS_TE_IN_MAX6_SHADOW_MEM_MAPS_H_
#define TAINT_MAPS_MEMORY_MAPS_TB_IN_MAX6_MEM_MAPS_TE_IN_MAX6_SHADOW_MEM_MAPS_TE_IN_MAX6_SHADOW_MEM_MAPS_H_

#include "../../../../../../tb_bunny_private.h"
#include "instrumentation_bunny.h"

/**************************************************
 * Creation Functions
 */

void *tb_raw_umbra_create_mem_map(void *user_data, void **start);
void tb_raw_umbra_destroy_mem_map(void *map,
        ub_destroy_value_func_t detroy_func, void *user_data);

/**************************************************
 * Translation Function
 */

void tb_umbra_insert_translate_address(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t scratch_reg);

/**************************************************
 * Setters
 */

void tb_raw_umbra_insert_set_taint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t label_reg, reg_id_t old_reg, bool get_old);

void tb_simd_umbra_insert_set_taint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t vector_label_reg, reg_id_t vector_old_reg, bool get_old);

/**************************************************
 * Unsetters
 */

void tb_raw_umbra_insert_set_untaint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t old_reg, bool get_old);

void tb_simd_umbra_insert_set_untaint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t vector_old_reg, reg_id_t vector_scratch_reg, bool get_old);

/****************************************************************************
 * Getters
 */

void tb_raw_umbra_insert_get_mem(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t label_reg);

void tb_simd_umbra_insert_get_mem(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t vector_scratch_reg);

#endif /* TAINT_MAPS_MEMORY_MAPS_TB_IN_MAX6_MEM_MAPS_TE_IN_MAX6_SHADOW_MEM_MAPS_TE_IN_MAX6_SHADOW_MEM_MAPS_H_ */
