/*
 * ub_set.h
 *
 *  Created on: 30 Nov 2017
 *      Author: john
 */

#ifndef DATASTRUCTS_SETS_UB_SET_H_
#define DATASTRUCTS_SETS_UB_SET_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "hashtable.h"

#include <stdint.h>

/**
 *  Destroys a set
 *
 *  @param set The set to destroy
 */
void ub_hashset_destroy(void* set);

/**
 *  @param set The set to consider
 *  @param elem The element to check
 *  @return Returns whether the element is in the set
 */
bool ub_hashset_is_included(void* set, uintptr_t elem);

/**
 *  Call the apply_func to all elemnts in this list.
 *  @param apply_func A pointer to a function to call for every element.
 */
void ub_hashset_apply_to_elements(void *set, void (*apply_func)(void *value));


void ub_hashset_apply_to_elements_ex(void *set,
		void (*apply_func)(void * elem, void *user_data), void *user_data);

size_t ub_hashset_get_size(void *set);

/**
 *  Include all elements in source set in destination set.
 */
void ub_hashset_union(void *dest_set, void *src_set);

/**
 *  Inserts an element to the set.
 *
 *  @return Returns true if the element inserted was not in the set already.
 */
bool ub_hashset_insert(void* set, uintptr_t elem);

/**
 *  Removes element from set.
 *
 */
bool ub_hashset_remove(void* set, uintptr_t elem);

// TODO implement Union and Intersection functions.

#endif /* DATASTRUCTS_SETS_UB_SET_H_ */
