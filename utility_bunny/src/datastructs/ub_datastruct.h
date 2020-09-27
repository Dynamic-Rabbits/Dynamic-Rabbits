/*
 *  @file datastruct.h
 *  @brief Definitions and struct declarations pertaining to data
 *  structures
 *  @author John F.X. Galea
 */

#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#include <stdint.h>
#include "dr_api.h"

/**
 * @var destroy_value_function_t Safely destroys a value
 */
typedef void (*ub_destroy_value_func_t)(void *);

/**
 * @var compare_func_t Comparison function to check equality between values in the list
 */
typedef bool (*ub_compare_func_t)(const void *, const void *);


/**
 *  @struct key_value_pair_t
 *
 *  A pair of keys and values
 *
 *  @var key_value_pair_t::key
 *  The key associated with the value
 *
 *  @var key_value_pair_t::value
 *  A pointer to the value
 */
typedef struct key_value_pair {
	uintptr_t key;
	void *value;
} ub_key_value_pair_t;

typedef struct two_key_value_pair {
    uintptr_t key1;
    uintptr_t key2;
    void *value;
} ub_two_key_value_pair_t;

#endif /* DATASTRUCT_H_ */
