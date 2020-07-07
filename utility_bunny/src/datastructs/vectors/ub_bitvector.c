/*
 * bit_vector.c
 *
 *      Author: john
 */

#include "ub_bitvector.h"
#include "../../instrumentation/ub_instrum_insert.h"
#include <stddef.h>
#include "string.h"

static void ub_bitvect_init(ub_bitvect_t *bit_vect, size_t bit_size) {

    bit_vect->bit_size = bit_size;
    bit_vect->byte_size = bit_size / UB_BYTE_SIZE;

    bit_vect->value = NULL;

    if (bit_size % UB_BYTE_SIZE > 0)
        bit_vect->byte_size++;

    if (bit_size != 0) {
        bit_vect->value = dr_global_alloc(bit_vect->byte_size);
        ub_bitvect_basic_init(bit_vect->value, bit_vect->byte_size);
    }
}

DR_EXPORT ub_bitvect_t* ub_bitvect_create(size_t bit_size) {

    ub_bitvect_t *bit_vect = dr_global_alloc(sizeof(ub_bitvect_t));
    ub_bitvect_init(bit_vect, bit_size);
    return bit_vect;
}

static void ub_bitvector_destroy_value(byte *value, size_t byte_size) {

    if (value)
        dr_global_free(value, byte_size);

}

DR_EXPORT void ub_bitvect_destroy(ub_bitvect_t *bit_vector) {

    ub_bitvector_destroy_value(bit_vector->value, bit_vector->byte_size);
    dr_global_free(bit_vector, sizeof(ub_bitvect_t));
}

DR_EXPORT size_t ub_bitvect_get_num_of_bit_sets(ub_bitvect_t *bit_vector) {

    size_t count = 0;

    byte mask = 1;
    for (size_t i = 0; i < bit_vector->byte_size; i++) {

        byte val = bit_vector->value[i];
        size_t size = UB_BYTE_SIZE;

        if ((i + 1) * UB_BYTE_SIZE > bit_vector->bit_size)
            size = bit_vector->bit_size - (i * UB_BYTE_SIZE);

        for (size_t j = 0; j < size; j++) {

            if (val & mask)
                count++;

            val = val >> 1;
        }
    }

    return count;
}

DR_EXPORT size_t ub_bitvect_get_size(ub_bitvect_t *bit_vector) {

    return bit_vector->bit_size;
}

DR_EXPORT void ub_bitvect_set_bit(ub_bitvect_t *bit_vector, size_t index,
        bool is_set) {

    ub_bitvect_basic_set_bit(bit_vector->value, index, is_set);
}

DR_EXPORT bool ub_bitvect_get_bit(ub_bitvect_t *bit_vector, size_t index) {

    return ub_bitvect_basic_get_bit(bit_vector->value, index);
}

DR_EXPORT size_t ub_bitvect_get_start_trailing_zero(ub_bitvect_t *bit_vector) {

    DR_ASSERT(bit_vector);

    int j;
    int i;

    for (i = (int) bit_vector->byte_size - 1; i >= 0; i--) {

        bool set = false;
        byte val = bit_vector->value[i];
        size_t size = UB_BYTE_SIZE;

        if ((i + 1) * UB_BYTE_SIZE > (int) bit_vector->bit_size)
            size = bit_vector->bit_size - (i * UB_BYTE_SIZE);

        byte mask = 0x80;
        mask = mask >> (UB_BYTE_SIZE - size);

        for (j = (int) size - 1; j >= 0; j--) {

            if (val & mask) {
                set = true;
                break;
            }

            mask = mask >> 1;
        }

        if (set)
            break;
    }

    if (i < 0)
        return 0;
    else {
        return (i * UB_BYTE_SIZE) + j + 1;
    }
}

DR_EXPORT void ub_bitvect_trim(ub_bitvect_t *bitvect1) {

    DR_ASSERT(bitvect1);

    size_t max = bitvect1->bit_size;
    size_t max_trim = ub_bitvect_get_start_trailing_zero(bitvect1);

    byte *old_value = bitvect1->value;
    size_t old_size = bitvect1->byte_size;

    if (max_trim < max) {

        ub_bitvect_init(bitvect1, max_trim);
        memcpy(bitvect1->value, old_value, bitvect1->byte_size);

        ub_bitvector_destroy_value(old_value, old_size);
    }
}

static size_t ub_bitvect_get_max_size(ub_bitvect_t *bitvect1,
        ub_bitvect_t *bitvect2) {

    if (bitvect1->bit_size < bitvect2->bit_size)
        return bitvect2->bit_size;

    return bitvect1->bit_size;
}

DR_EXPORT void ub_bitvect_fixed_union(ub_bitvect_t *bitvect1,
        ub_bitvect_t *bitvect2) {

    DR_ASSERT(bitvect1);
    DR_ASSERT(bitvect2);
    DR_ASSERT(bitvect1->byte_size == bitvect2->byte_size);

    ub_bitvect_basic_union(bitvect1->value, bitvect1->value, bitvect2->value,
            bitvect1->byte_size);
}

DR_EXPORT ub_bitvect_t *ub_bitvect_union(ub_bitvect_t *bitvect1,
        ub_bitvect_t *bitvect2) {

    DR_ASSERT(bitvect1);
    DR_ASSERT(bitvect2);

    size_t max = ub_bitvect_get_max_size(bitvect1, bitvect2);

    ub_bitvect_t *union_vect = ub_bitvect_create(max);
    memcpy((void *) union_vect->value, (void *) bitvect1->value,
            bitvect1->byte_size);

    for (size_t i = 0; i < bitvect2->byte_size; i++)
        union_vect->value[i] |= bitvect2->value[i];

    return union_vect;
}

DR_EXPORT void ub_bitvect_println(ub_bitvect_t *bit_vector) {

    DR_ASSERT(bit_vector);

    byte mask = 0x01;
    for (size_t i = 0; i < bit_vector->byte_size; i++) {

        byte val = bit_vector->value[i];
        size_t size = UB_BYTE_SIZE;

        if ((i + 1) * UB_BYTE_SIZE > bit_vector->bit_size)
            size = bit_vector->bit_size - (i * UB_BYTE_SIZE);

        for (size_t j = 0; j < size; j++) {

            if (val & mask)
                dr_fprintf(STDERR, "1");
            else
                dr_fprintf(STDERR, "0");

            val = val >> 1;
        }
    }

    dr_fprintf(STDERR, "\n");
}

DR_EXPORT bool ub_bitvect_equal(ub_bitvect_t *bitvect1, ub_bitvect_t *bitvect2) {

    size_t bitvect1_size = ub_bitvect_get_start_trailing_zero(bitvect1);
    size_t bitvect2_size = ub_bitvect_get_start_trailing_zero(bitvect2);

    if (bitvect1_size == bitvect2_size) {

        return ub_bitvect_basic_equal(bitvect1->value, bitvect2->value,
                bitvect1_size);
    }

    return false;
}

/***********************************************************************************
 * Insert function
 */

static void ub_bitvect_load_register_values(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect1_reg, reg_id_t bit_vect2_reg,
        reg_id_t size_reg) {

    /* Load the size. We assume that both vectors have the same size, thus loading one suffices. */
    opnd_t size_ref_opnd =
    OPND_CREATE_MEMPTR(bit_vect1_reg, offsetof(ub_bitvect_t, byte_size));
    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &size_ref_opnd,
            size_reg);

    /* Load bit vector */
    opnd_t bitvector_ref_opnd =
    OPND_CREATE_MEMPTR(bit_vect1_reg, offsetof(ub_bitvect_t, value));
    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where,
            &bitvector_ref_opnd, bit_vect1_reg);

    /* Load second bit vector */
    opnd_t bitvector_ref_opnd2 =
    OPND_CREATE_MEMPTR(bit_vect2_reg, offsetof(ub_bitvect_t, value));
    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where,
            &bitvector_ref_opnd2, bit_vect2_reg);

}

DR_EXPORT void ub_bitvect_insert_copy(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect1_reg, reg_id_t bit_vect2_reg,
        reg_id_t size_reg, reg_id_t scratch_reg) {

    ub_bitvect_load_register_values(drcontext, ilist, where, bit_vect1_reg,
            bit_vect2_reg, size_reg);

    ub_bitvect_basic_insert_copy(drcontext, ilist, where, bit_vect1_reg,
            bit_vect2_reg, size_reg, scratch_reg);
}

DR_EXPORT void ub_bitvect_insert_union(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect1_reg, reg_id_t bit_vect2_reg,
        reg_id_t size_reg, reg_id_t scratch_reg) {

    ub_bitvect_load_register_values(drcontext, ilist, where, bit_vect1_reg,
            bit_vect2_reg, size_reg);

    ub_bitvect_insert_union(drcontext, ilist, where, bit_vect1_reg,
            bit_vect2_reg, size_reg, scratch_reg);
}
