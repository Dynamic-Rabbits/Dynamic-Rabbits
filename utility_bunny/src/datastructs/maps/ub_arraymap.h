/**
 *  @file map.h
 *  @brief A data structure that maps keys to values
 *  @author John F.X. Galea
 */

#ifndef MAPS_TB_MAP_H_
#define MAPS_TB_MAP_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"
#include <stddef.h>

/***************************************************************************
 *  Map operations
 */

/**
 *  Creates and initialises a map.
 *
 *  @param destroy_value A function pointer that safely destroys a value. Can be set to NULL.
 *  @param size Size of the array map. if collisions occur, buckets are then employed.
 *	@return A pointer to the map or null if unsuccessful.
 */
DR_EXPORT void *ub_arraymap_create_map(size_t size);

/**
 *  Safely destroys a map
 *
 *  @param type The map to destroy
 */
DR_EXPORT void ub_arraymap_destroy_map(void *map_opaque,
		ub_destroy_value_func_t detroy_func);

/**
 *  Inserts value with given key in map.
 *
 *  @param map The map to insert the new key-value pair
 *  @param key_val_pair The key and value to map
 *  @return Returns the old value if the key was already mapped. Otherwise, returns NULL.
 */
DR_EXPORT void* ub_arraymap_insert_entry(void *map, ub_key_value_pair_t *key_val_pair);

/**
 *  Performs a lookup operation on the map.
 *
 *  @param map The map to perform lookup operation on.
 *  @param key The key to lookup.
 *  @return The found value, or null if lookup finds no entry.
 */
DR_EXPORT void *ub_arraymap_lookup_entry(void *map, uintptr_t key);

/**
 *  Removes entry from map.
 *
 *  @param map The map to perform remove operation on
 *  @param key The key to lookup and remove mapping
 *  @return Returns the value of the removed entry. Returns NULL if the
 *  key is not mapped.
 */
DR_EXPORT void * ub_arraymap_remove_entry(void *map, uintptr_t key);


void drarraymap_symb_insert_new_node(reg_id_t opnd_reg, reg_id_t map_reg);

void ub_arraymap_insert_lookup_entry(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t key_reg, reg_id_t map_reg,
		reg_id_t scratch_reg);

void ub_arraymap_insert_lookup_check(void *drcontext, instrlist_t *ilist, instr_t *where,
		instr_t* not_valid_opnd_label, reg_id_t looked_node, reg_id_t scratch_reg);

void ub_arraymap_insert_map_entry(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t opnd_reg, reg_id_t map_reg,
		reg_id_t scratch_reg);

void ub_arraymap_insert_inline_map_remove(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t opnd_reg, reg_id_t map_reg,
		reg_id_t scratch_reg);


#endif /* MAPS_TB_MAP_H_ */
