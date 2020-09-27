/*
 * ub_bitvector_raw.h
 *
 *  Created on: 28 Mar 2019
 *      Author: john
 */

#ifndef DATASTRUCTS_VECTORS_UB_BITVECTOR_BASIC_H_
#define DATASTRUCTS_VECTORS_UB_BITVECTOR_BASIC_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drutil.h"

/**
 * This API is considered to be at a lower level than ub_bitvector.
 *
 * In fact, ub_bitvector internally makes use of this API.
 */

#define UB_BYTE_SIZE 8

DR_EXPORT void ub_bitvect_basic_init(byte *value, size_t size);

DR_EXPORT void ub_bitvect_basic_set_bit(byte *value, size_t index, bool is_set);

DR_EXPORT bool ub_bitvect_basic_get_bit(byte *value, size_t index);

DR_EXPORT void ub_bitvect_basic_union(byte *dst_value, byte *src_value1,
        byte *src_value2, size_t size);

DR_EXPORT bool ub_bitvect_basic_equal(byte *value1, byte *value2,
        size_t size);

/***********************************************************************************
 * Insert function
 */

DR_EXPORT void ub_bitvect_basic_insert_copy(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect1_reg, reg_id_t bit_vect2_reg,
        reg_id_t size_reg, reg_id_t scratch_reg);

DR_EXPORT void ub_bitvect_basic_insert_union(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t bit_vect1_reg,
        reg_id_t bit_vect2_reg, reg_id_t size_reg, reg_id_t scratch_reg);

#endif /* DATASTRUCTS_VECTORS_UB_BITVECTOR_BASIC_H_ */
