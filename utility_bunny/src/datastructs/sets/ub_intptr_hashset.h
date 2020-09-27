/*
 * ub_intptr_hashset.h
 *
 *  Created on: 30 Nov 2017
 *      Author: john
 */

#ifndef DATASTRUCTS_SETS_UB_INTPTR_HASHSET_H_
#define DATASTRUCTS_SETS_UB_INTPTR_HASHSET_H_

#include <stddef.h>

#include "dr_defines.h"
#include "dr_api.h"
#include <stddef.h>
#include <stdint.h>

/**
 *  Creates an intptr hashset. The set takes unsigned int pointers.
 *  @return Returns the newly created hashset.
 */
DR_EXPORT void * ub_intptr_hashset_create();


DR_EXPORT void ub_intptr_hashset_apply_to_elements(void *set,
		void (*apply_func)(void * elem));


DR_EXPORT void ub_intptr_hashset_apply_to_elements_ex(void *set,
		void (*apply_func)(void * elem, void *user_data), void *user_data);

/**
 *  Destroys a given hashset.
 *
 *  @param set The hashset to destroy.
 */
DR_EXPORT void ub_intptr_hashset_destroy(void* set);

/**
 *  Indicates whether an element is in the hashset.
 *
 *  @param set The hashset.
 *  @param element The element to check for inclusion.
 *  @return Returns a boolean indicating whether the element is in the set.
 */
DR_EXPORT bool ub_intptr_hashset_is_included(void* set, uintptr_t element);

/**
 *
 */
DR_EXPORT void ub_intptr_hashset_union(void *dest_set , void *src_set);

/**
 *
 */
DR_EXPORT size_t ub_intptr_hashset_get_size(void *set);

/**
 * Inserts an element to the set.
 *
 * @param set The set to perform inclusion.
 * @param element The element to include in the set.
 * @return Returns true if the element was not already in the set.
 */
DR_EXPORT bool ub_intptr_hashset_insert(void* set, uintptr_t element);

/**
 *  Removes an element from the hashset.
 *
 *  @param set The hashset.
 *  @param element The element to removed.
 *  @return Returns true if the element has been successfully removed.
 */
DR_EXPORT bool ub_intptr_hashset_remove(void* set, uintptr_t element);

#endif /* DATASTRUCTS_SETS_UB_INTPTR_HASHSET_H_ */
