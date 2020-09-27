/*
 * ub_tk_lp_hashmap.h
 *
 *  Created on: 26 Sep 2019
 *      Author: john
 */

#ifndef DATASTRUCTS_MAPS_UB_TK_LP_HASHMAP_H_
#define DATASTRUCTS_MAPS_UB_TK_LP_HASHMAP_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"
#include <stddef.h>

/**
 * TODO:
 */
DR_EXPORT void *ub_tk_lp_hashmap_create();

/**
 * TODO:
 */
DR_EXPORT void ub_tk_lp_hashmap_destroy(void *map_opaque,
		ub_destroy_value_func_t detroy_func);

/**
 * TODO:
 */
DR_EXPORT void* ub_tk_lp_hashmap_insert_entry(void *map_opaque,
		ub_two_key_value_pair_t *two_key_val_pair);

/**
 * TODO:
 */
DR_EXPORT void *ub_tk_lp_hashmap_lookup_entry(void *map_opaque, uintptr_t key1,
		uintptr_t key2);

/**
 * TODO:
 */
DR_EXPORT bool ub_tk_lp_hashmap_remove_entry(void *map_opaque, uintptr_t key1,
		uintptr_t key2, void **old_val);

/**
 * TODO:
 */
DR_EXPORT void ub_tk_lp_hashmap_insert_lookup_entry(void *map_opaque, void *drcontext,
		instrlist_t *ilist, instr_t *where, reg_id_t result_reg,
		reg_id_t key_reg, reg_id_t key2_reg, reg_id_t scratch_reg);

#endif /* DATASTRUCTS_MAPS_UB_TK_LP_HASHMAP_H_ */
