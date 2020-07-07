/**
 *  @file map.h
 *  @brief A data structure that maps keys to values
 *  @author John F.X. Galea
 */

#ifndef MAPS_TB_TK_MAP_H_
#define MAPS_TB_TK_MAP_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"
#include <stddef.h>

typedef struct arraymap_list_node {
	uintptr_t used_flag;
    uintptr_t key;
    uintptr_t key2;
    void *value;
    struct arraymap_list_node *next;
} ub_tk_arraymap_list_node_t;

DR_EXPORT void *ub_tk_arraymap_create_map();

DR_EXPORT void ub_tk_arraymap_destroy_map(void *map_opaque,
        ub_destroy_value_func_t detroy_func);

DR_EXPORT void* ub_tk_arraymap_insert_entry(void *map_opaque,
        ub_two_key_value_pair_t *key_val_pair);

DR_EXPORT void *ub_tk_arraymap_lookup_entry(void *map_opaque, uintptr_t key1,
        uintptr_t key2);

DR_EXPORT void * ub_tk_arraymap_remove_entry(void *map_opaque, uintptr_t key1,
        uintptr_t key2);

/***********************************************************************************************
 * Inline interface
 */

DR_EXPORT void ub_tk_arraymap_insert_lookup(void *map_opaque,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t key_reg,
        reg_id_t key2_reg, reg_id_t found_reg);

DR_EXPORT void ub_tk_arraymap_insert_inline_map_remove(
        void *map, void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t key_reg, reg_id_t key2_reg,
        reg_id_t scratch_reg);

DR_EXPORT opnd_t ub_tk_arraymap_get_val_opnd(reg_id_t entry_reg);

DR_EXPORT void ub_tk_arraymap_insert_map_entry(void *map,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t key_reg,
        reg_id_t key2_reg, reg_id_t new_node_reg, reg_id_t scratch_reg2);

#endif /* MAPS_TB_TK_MAP_H_ */
