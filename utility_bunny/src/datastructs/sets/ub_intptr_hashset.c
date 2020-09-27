/**
 * @author John F.X. Galea
 */

#include "ub_hashset.h"
#include "../maps/ub_intptr_hashmap.h"
#include "ub_intptr_hashset.h"

DR_EXPORT void * ub_intptr_hashset_create() {

	return ub_intptr_hashmap_create_map();
}

DR_EXPORT void ub_intptr_hashset_destroy(void* set) {

	ub_hashset_destroy(set);
}

DR_EXPORT void ub_intptr_hashset_apply_to_elements(void *set,
		void (*apply_func)(void * elem)) {

	ub_hashset_apply_to_elements(set, apply_func);
}

DR_EXPORT void ub_intptr_hashset_apply_to_elements_ex(void *set,
		void (*apply_func)(void * elem, void *user_data), void *user_data) {

	ub_hashset_apply_to_elements_ex(set, apply_func, user_data);
}

DR_EXPORT size_t ub_intptr_hashset_get_size(void *set){

	return ub_hashset_get_size(set);
}

DR_EXPORT void ub_intptr_hashset_union(void *dest_set, void *src_set) {

	ub_hashset_union(dest_set, src_set);
}

DR_EXPORT bool ub_intptr_hashset_is_included(void* set, uintptr_t element) {

	return ub_hashset_is_included(set, element);
}

DR_EXPORT bool ub_intptr_hashset_insert(void* set, uintptr_t element) {

	return ub_hashset_insert(set, element);
}

DR_EXPORT bool ub_intptr_hashset_remove(void* set, uintptr_t element) {

	return ub_hashset_remove(set, element);
}
