/*
 * te_in_raw_shadow_reg_map.h
 *
 *  Created on: 9 Jul 2018
 *      Author: john
 */

#ifndef TAINT_MAPS_REGISTER_MAP_TB_IN_raw_REG_MAPS_TE_IN_raw_SHADOW_REG_MAP_TB_IN_raw_SHADOW_REG_MAP_H_
#define TAINT_MAPS_REGISTER_MAP_TB_IN_raw_REG_MAPS_TE_IN_raw_SHADOW_REG_MAP_TB_IN_raw_SHADOW_REG_MAP_H_

#include "utility_bunny.h"
#include "../../tb_cc_reg_maps/tb_cc_array_reg_maps/tb_array_reg_map_definitions.h"
#include "../../../../../../tb_bunny_private.h"

void tb_raw_arraymap_insert_load_reg_map(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg);

/****************************************************************************
 * SET Reg Label
 */
void tb_raw_arraymap_insert_set_taint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd, reg_id_t label_reg,
        reg_id_t old_reg, bool get_old);

void tb_simd_arraymap_insert_set_taint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t vector_label_reg, reg_id_t vector_old_reg, bool get_old);

/****************************************************************************
 * SET UNTAINT Reg Label
 */

void tb_raw_arraymap_insert_set_untaint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t old_translated_reg, bool get_old);

void tb_simd_arraymap_insert_set_untaint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t old_vectorised_reg, reg_id_t scratch_vectorised_reg, bool get_old);

/****************************************************************************
 * Translation Functions
 */

void tb_raw_arraymap_insert_translate_address(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t addr_reg);

void tb_raw_arraymap_insert_translate_address_via_id(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        uintptr_t reg_byte_id, reg_id_t dst_reg);

opnd_t tb_raw_arraymap_get_opnd(void *drcontext, reg_id_t map_reg,
        reg_id_t reg_id, uintptr_t reg_byte_id, int disp, opnd_size_t data_size);

opnd_t tb_raw_arraymap_get_opnd_via_id(void *drcontext, reg_id_t map_reg,
        uintptr_t reg_byte_id, int disp, opnd_size_t data_size);

/****************************************************************************
 * Get Reg Label
 */

opnd_t tb_raw_arraymap_insert_reg_get_taint_label_opnd(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t tranlated_addr_reg);

opnd_t tb_raw_arraymap_insert_reg_get_taint_label_opnd_ex(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t reg_id_reg, size_t size);

#endif /* TAINT_MAPS_REGISTER_MAP_TB_IN_raw_REG_MAPS_TE_IN_raw_SHADOW_REG_MAP_TB_IN_raw_SHADOW_REG_MAP_H_ */
