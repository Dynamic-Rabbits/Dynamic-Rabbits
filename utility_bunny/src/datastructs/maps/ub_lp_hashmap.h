/*
 * ub_linear_probing_map.h
 *
 *  Created on: 26 Sep 2019
 *      Author: john
 */

#ifndef DATASTRUCTS_MAPS_UB_LP_HASHMAP_H_
#define DATASTRUCTS_MAPS_UB_LP_HASHMAP_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"
#include <stddef.h>

/**
 * TODO
 */
DR_EXPORT void *ub_lp_map_create();

/**
 * TODO
 */
DR_EXPORT void ub_lp_map_destroy(void *map_opaque,
		ub_destroy_value_func_t detroy_func);

/**
 * TODO
 */
DR_EXPORT void* ub_lp_map_insert_entry(void *map_opaque,
		ub_key_value_pair_t *key_val_pair);

/**
 * TODO
 */
DR_EXPORT void* ub_lp_map_lookup_entry(void *map_opaque, void *key);

/**
 * TODO
 */
DR_EXPORT bool ub_lp_map_remove(void *map_opaque, void *key, void **old_val);

/**
 * TODO
 */
void ub_lp_hashmap_insert_lookup_entry(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_reg, reg_id_t key_reg, reg_id_t map_reg,
		reg_id_t scratch_reg);
/**
 * TODO
 */
void ub_lp_hashmap_insert_lookup_entry_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_reg, reg_id_t key_reg, reg_id_t map_reg,
		reg_id_t scratch_reg, bool check_map);

#endif /* DATASTRUCTS_MAPS_UB_LP_HASHMAP_H_ */
