/*
 * @file ub_dr_hashmap.h
 * @brief A data structure that maps keys to values making use of
 * dynamorio's hash_table functionality
 * @author John F.X. Galea
 */

#ifndef DATASTRUCTS_MAPS_UB_DR_HASHMAP_H_
#define DATASTRUCTS_MAPS_UB_DR_HASHMAP_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"
#include <stdint.h>
#include "hashtable.h"

/**
 *  Safely destroys a map
 *
 *  @param map_opaque The map to destroy
 *  @param detroy_val_func A function pointer that safely destroys a value. Can be set to NULL.
 */
void ub_hashmap_destroy_map(void *map_opaque, ub_destroy_value_func_t detroy_val_func);

/**
 *  Calls apply_func to all values in the map.
 */
void ub_hashmap_apply_all_values(void *map, void (*apply_func)(void *value));


/**
 *  Calls apply_func to all values in the map passing also user data.
 */
void ub_hashmap_apply_all_values_ex(void *map_opaque,
		void (*apply_func)(void *value, void *user_data), void *user_data);

/**
 *  Inserts value with given key in map.
 *
 *  @param map The map to insert the new key-value pair
 *  @param key_val_pair The key and value to map
 *  @return Returns the old value if the key was already mapped. Otherwise, returns NULL.
 */
void* ub_hashmap_insert_entry(void *map, ub_key_value_pair_t *key_val_pair);

/**
 *  Performs a lookup operation on the map.
 *
 *  @param map The map to perform lookup operation on.
 *  @param key The key to lookup.
 *  @return The found value, or null if lookup finds no entry.
 */
void *ub_hashmap_lookup_entry(void *map, uintptr_t key);

/**
 *  Removes entry from map.
 *
 *  @param map The map to perform remove operation on
 *  @param key The key to lookup and remove mapping
 *  @return Returns the value of the removed entry. Returns NULL if the
 *  key was not in the map
 */
void * ub_hashmap_remove_entry(void *map, uintptr_t key);

void ub_hashmap_lock(void *map);

void ub_hashmap_unlock(void *map);

#endif /* DATASTRUCTS_MAPS_UB_DR_HASHMAP_H_ */
