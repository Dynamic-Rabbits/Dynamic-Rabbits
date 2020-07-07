/**
 * @author John F.X. Galea
 */

#include "ub_str_hashset.h"
#include "ub_hashset.h"
#include "../maps/ub_str_hashmap.h"


DR_EXPORT void * ub_str_hashset_create() {

	return ub_str_hashmap_create_map();
}

DR_EXPORT void ub_str_hashset_destroy(void* set) {

	ub_hashset_destroy(set);
}

DR_EXPORT bool ub_str_hashset_is_included(void* set, char* elem) {

	return ub_hashset_is_included(set, (uintptr_t) elem);
}

DR_EXPORT void ub_str_hashset_union(void *dest_set , void *src_set){

	ub_hashset_union(dest_set, src_set);
}

DR_EXPORT bool ub_str_hashset_insert(void* set, char* key) {

	return ub_hashset_insert(set, (uintptr_t) key);
}

DR_EXPORT bool ub_str_hashset_remove(void* set, char* key){

	return ub_hashset_remove(set, (uintptr_t) key);
}
