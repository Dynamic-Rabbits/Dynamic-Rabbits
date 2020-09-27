/**
 *  @file ub_byte_array.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_byte_array.h"
#include <string.h>

DR_EXPORT uint32_t ub_get_uint32_from_byte_array(byte *bytes, size_t size){

	uint32_t value = 0;
	DR_ASSERT(sizeof(uint32_t) >= size);
	memcpy(&value, bytes, size);

	return value;
}

DR_EXPORT uintptr_t ub_modify_byte_of_value(uintptr_t main_value, size_t size, byte value, unsigned int byte_index){

	DR_ASSERT(byte_index < size);
	unsigned int shift_n = 8 * byte_index ;
	uintptr_t mask = ~(0xff << shift_n);
	uintptr_t well_sized_val = (uintptr_t) value;
	return (main_value & mask) | (well_sized_val << shift_n);
}
