/*
 * @file ub_str_hashmap.h
 * @brief A data structure that maps keys to values (referred to via a ptr)
 *  making use of dynamorio's hash_table functionality
 * @author John F.X. Galea
 */

#ifndef DATASTRUCTS_MAPS_UB_STR_HASHMAP_H_
#define DATASTRUCTS_MAPS_UB_STR_HASHMAP_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"
#include <stddef.h>

/**
 *  Creates and initialises a map.
 *
 *
 *	@return A pointer to the map or null if unsuccessful
 */
DR_EXPORT void *ub_str_hashmap_create_map();

/**
 *  Safely destroys a map
 *
 *  @param type The map to destroy
 */
DR_EXPORT void ub_str_hashmap_destroy_map(void *map, ub_destroy_value_func_t detroy_val_func);

/**
 *  Calls a function for each value in the map.
 *
 *  @param map The map containing the values of interest
 *  @param apply_func Function called to each value in the map
 */
DR_EXPORT void ub_str_hashmap_apply_all_values(void *map, void (*apply_func)(void *value));

/**
 *  Inserts value with given key in map.
 *
 *  @param map The map to insert the new key-value pair
 *  @param key_val_pair The key and value to map
 *  @return Returns the old value if the key was already mapped. Otherwise, returns NULL.
 */
DR_EXPORT void* ub_str_hashmap_insert_entry(void *map, ub_key_value_pair_t *key_val_pair);

/**
 *  Performs a lookup operation on the map.
 *
 *  @param map The map to perform lookup operation on.
 *  @param key The key to lookup.
 *  @return The found value, or null if lookup finds no entry.
 */
DR_EXPORT void *ub_str_hashmap_lookup_entry(void *map, char *key);

/**
 *  Removes entry from map.
 *
 *  @param map The map to perform remove operation on
 *  @param key The key to lookup and remove mapping
 *  @return Returns the value of the removed entry. Returns NULL if the
 *  key was not in the map
 */
DR_EXPORT void * ub_str_hashmap_remove_entry(void *map, char *key);

DR_EXPORT void ub_str_hashmap_lock(void *map);

DR_EXPORT void ub_str_hashmap_unlock(void *map);

#endif /* DATASTRUCTS_MAPS_UB_STR_HASHMAP_H_ */
