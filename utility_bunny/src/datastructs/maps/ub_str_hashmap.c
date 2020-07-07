/*
 * ub_str_hashmap.c
 *
 *      Author: john
 */

#include "ub_str_hashmap.h"
#include "ub_hashmap.h"

DR_EXPORT void *ub_str_hashmap_create_map() {

	hashtable_t *hash_table = dr_global_alloc(sizeof(hashtable_t));

    hashtable_init_ex(hash_table, 8, HASH_STRING, true, false, NULL, NULL,
            NULL);


	return hash_table;
}

DR_EXPORT void ub_str_hashmap_destroy_map(void *map_opaque,
		ub_destroy_value_func_t detroy_val_func) {

	return ub_hashmap_destroy_map(map_opaque, detroy_val_func);
}

DR_EXPORT void ub_str_hashmap_apply_all_values(void *map_opaque,
		void (*apply_func)(void *value)) {
	ub_hashmap_apply_all_values(map_opaque, apply_func);
}

DR_EXPORT void* ub_str_hashmap_insert_entry(void *map,
		ub_key_value_pair_t *key_val_pair) {


	return ub_hashmap_insert_entry(map, key_val_pair);
}

DR_EXPORT void *ub_str_hashmap_lookup_entry(void *map_opaque, char *key) {

	return ub_hashmap_lookup_entry(map_opaque, (uintptr_t) key);
}

DR_EXPORT void *ub_str_hashmap_remove_entry(void *map, char *key) {

	return ub_hashmap_remove_entry(map, (uintptr_t) key);
}

DR_EXPORT void ub_str_hashmap_lock(void *map) {

    ub_hashmap_lock(map);
}

DR_EXPORT void ub_str_hashmap_unlock(void *map) {

    ub_hashmap_unlock(map);
}
