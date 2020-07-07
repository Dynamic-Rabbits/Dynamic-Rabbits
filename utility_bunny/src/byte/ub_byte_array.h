/**
 *  @file ub_byte_array.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef UB_BYTE_ARRAY_H_
#define UB_BYTE_ARRAY_H_

#include "dr_defines.h"
#include "dr_api.h"
#include <stdint.h>

/**
 *  Gets an integer from raw bytes.
 *
 *  @param bytes An array of bytes.
 *  @param size The number of bytes to consider. It cannot be greater
 *  than the size of uint32_t.
 */
DR_EXPORT uint32_t ub_get_uint32_from_byte_array(byte *bytes, size_t size);

//TODO support get_uint64_from_byte_array

/**
 *  Modifies a byte at a given index of a value.
 *
 *  @param main_value The main value, where one of its bytes is changed.
 *  @param size The size of the value (number of bytes).
 *  @param value The byte value to inject.
 *  @param byte_index The index of the byte to change.
 */
DR_EXPORT uintptr_t ub_modify_byte_of_value(uintptr_t main_value, size_t size, byte value,
		unsigned int byte_index);

#endif /* SRC_BYTE_ARRAY_UB_BYTE_ARRAY_H_ */
