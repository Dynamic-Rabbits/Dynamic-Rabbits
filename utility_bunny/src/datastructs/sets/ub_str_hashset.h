/*
 * ub_str_hashset.h
 *
 *  Created on: 30 Nov 2017
 *      Author: john
 */

#ifndef DATASTRUCTS_SETS_UB_STR_HASHSET_H_
#define DATASTRUCTS_SETS_UB_STR_HASHSET_H_

#include "dr_api.h"

DR_EXPORT void * ub_str_hashset_create();

DR_EXPORT void ub_str_hashset_destroy(void* set);

DR_EXPORT bool ub_str_hashset_is_included(void* set, char* key);

DR_EXPORT void ub_str_hashset_union(void *dest_set , void *src_set);

DR_EXPORT bool ub_str_hashset_insert(void* set, char* key);

DR_EXPORT bool ub_str_hashset_remove(void* set, char* key);

#endif /* DATASTRUCTS_SETS_UB_STR_HASHSET_H_ */
