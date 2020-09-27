/*
 * @author John F.X. Galea
 */

#include "../maps/ub_hashmap.h"
#include "ub_hashset.h"

void ub_hashset_destroy(void* set) {

	ub_hashmap_destroy_map(set, NULL);
}

bool ub_hashset_is_included(void* set, const uintptr_t elem) {

	return ub_hashmap_lookup_entry(set, elem) != NULL;
}

void ub_hashset_apply_to_elements(void *set, void (*apply_func)(void * elem)) {

	ub_hashmap_apply_all_values(set, apply_func);

}

void ub_hashset_apply_to_elements_ex(void *set,
		void (*apply_func)(void * elem, void *user_data), void *user_data) {

	ub_hashmap_apply_all_values_ex(set, apply_func, user_data);
}

static void ub_hashset_count(void *elem_data, void *count_opaque) {

	size_t *count = (size_t *) count_opaque;
	*count = *count + 1;
}

size_t ub_hashset_get_size(void *set) {

	size_t count = 0;

	if (set)
		ub_hashmap_apply_all_values_ex(set, ub_hashset_count, &count);

	return count;
}

static void ub_hashset_include(void *elem_data, void *dest_src) {

	ub_hashset_insert(dest_src, (uintptr_t) elem_data);
}

void ub_hashset_union(void *dest_set, void *src_set) {

	if (src_set)
		ub_hashmap_apply_all_values_ex(src_set, ub_hashset_include, dest_set);
}

bool ub_hashset_insert(void* set, uintptr_t elem) {

	DR_ASSERT_MSG(elem != 0, "We do not support the inclusion of 0");

	ub_key_value_pair_t key_val_pair;
	key_val_pair.key = elem;
	key_val_pair.value = (void*) elem;

	if (ub_hashmap_lookup_entry(set, elem) != NULL)
		return false;
	else {

		ub_hashmap_insert_entry(set, &key_val_pair);
	}

	return true;
}

bool ub_hashset_remove(void* set, const uintptr_t elem) {

	return ub_hashmap_remove_entry(set, elem) != NULL;
}
