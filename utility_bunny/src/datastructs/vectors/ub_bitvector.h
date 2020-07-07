/*
 * bit_vector.h
 *
 *  Created on: 1 Jul 2018
 *      Author: john
 */

#ifndef DATASTRUCTS_VECTORS_BIT_VECTOR_H_
#define DATASTRUCTS_VECTORS_BIT_VECTOR_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drutil.h"
#include "ub_bitvector_basic.h"

/**
 * Insert instrum
 */

typedef struct {

    size_t byte_size;
    byte *value;
    size_t bit_size;
} ub_bitvect_t;

DR_EXPORT ub_bitvect_t* ub_bitvect_create(size_t bit_size);

DR_EXPORT void ub_bitvect_destroy(ub_bitvect_t *bit_vector);

DR_EXPORT size_t ub_bitvect_get_size(ub_bitvect_t *bit_vector);

DR_EXPORT size_t ub_bitvect_get_num_of_bit_sets(ub_bitvect_t *bit_vector);

DR_EXPORT void ub_bitvect_set_bit(ub_bitvect_t *bit_vector, size_t index,
        bool is_set);

DR_EXPORT bool ub_bitvect_get_bit(ub_bitvect_t *bit_vector, size_t index);

DR_EXPORT size_t ub_bitvect_get_start_trailing_zero(ub_bitvect_t *bit_vector);

DR_EXPORT void ub_bitvect_trim(ub_bitvect_t *bitvect1);

DR_EXPORT void ub_bitvect_fixed_union(ub_bitvect_t *bitvect1,
        ub_bitvect_t *bitvect2);

DR_EXPORT ub_bitvect_t *ub_bitvect_union(ub_bitvect_t *bitvect1,
        ub_bitvect_t *bitvect2);

DR_EXPORT void ub_bitvect_println(ub_bitvect_t *bit_vector);

DR_EXPORT bool ub_bitvect_equal(ub_bitvect_t *bitvect1, ub_bitvect_t *bitvect2);

/***********************************************************************************
 * Insert function
 */

DR_EXPORT void ub_bitvect_insert_copy(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect1_reg, reg_id_t bit_vect2_reg,
        reg_id_t size_reg, reg_id_t scratch_reg);

DR_EXPORT void ub_bitvect_insert_union(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect1_reg, reg_id_t bit_vect2_reg,
        reg_id_t size_reg, reg_id_t scratch_reg);


#endif /* DATASTRUCTS_VECTORS_BIT_VECTOR_H_ */
