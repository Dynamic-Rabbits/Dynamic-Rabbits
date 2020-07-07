/**
 *  @file ub_bit_checker.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_bit_checker.h"
#include "../instrumentation/ub_instrum_insert.h"
#include "../register/ub_eflags.h"

static void ub_byte_hp_set_bit(unsigned int *value, ub_bit_check_t *bit_check) {

    if (bit_check->is_set) {
        *value |= (1 << bit_check->check_index);

    } else {
        *value |= (0 << bit_check->check_index);
    }
}

static void ub_byte_hp_set_mask_bit(unsigned int *cmp_value,
        ub_bit_check_t *bit_check) {

    *cmp_value |= (1 << bit_check->check_index);

}

DR_EXPORT void ub_byte_populate_check(ub_bit_check_t *bit_check,
        unsigned int check_index, bool is_set) {

    bit_check->check_index = check_index;
    bit_check->is_set = is_set;
}

DR_EXPORT void ub_byte_set_bit(unsigned int *value, int set_count, ...) {

    va_list index_va_list;
    va_start(index_va_list, set_count);

    for (int i = 0; i < set_count; i++) {

        ub_bit_check_t bit_check = va_arg(index_va_list, ub_bit_check_t);
        ub_byte_hp_set_bit(value, &bit_check);
    }
    va_end(index_va_list);
}

DR_EXPORT bool ub_byte_are_all_bit_set(unsigned int value, int index_num, ...) {

    va_list index_va_list;
    va_start(index_va_list, index_num);

    unsigned int cmp_value = 0;
    unsigned int mask_value = 0;

    // Construct mask
    for (int i = 0; i < index_num; i++) {

        ub_bit_check_t bit_check = va_arg(index_va_list, ub_bit_check_t);
        ub_byte_hp_set_bit(&cmp_value, &bit_check);
        ub_byte_hp_set_mask_bit(&mask_value, &bit_check);
    }
    va_end(index_va_list);

    unsigned int result = value & mask_value;

    return result == cmp_value;
}

DR_EXPORT bool ub_byte_is_any_bit_set(unsigned int value, int index_num, ...) {

    va_list index_va_list;
    va_start(index_va_list, index_num);

    unsigned int mask_value = 0;

    // Construct mask
    for (int i = 0; i < index_num; i++) {

        ub_bit_check_t bit_check = va_arg(index_va_list, ub_bit_check_t);
        ub_byte_hp_set_mask_bit(&mask_value, &bit_check);
    }

    va_end(index_va_list);

    unsigned int result = value & mask_value;

    return result != 0;
}

DR_EXPORT void ub_byte_insert_test_bit(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *val_opnd, ub_bit_check_t bit_check) {

    unsigned int mask_value = 0;

    ub_byte_hp_set_mask_bit(&mask_value, &bit_check);

#ifdef X86_32
    opnd_t opnd_immed = opnd_create_immed_uint(mask_value, OPSZ_4);
#else
    opnd_t opnd_immed = opnd_create_immed_uint(mask_value, OPSZ_8);
#endif
    instr_t *instr = INSTR_CREATE_test(drcontext, *val_opnd, opnd_immed);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_byte_insert_are_all_bit_set(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *val_opnd,
        opnd_t *is_set_label, reg_id_t scratch_reg, int index_num, ...) {

    // Set up VA
    va_list index_va_list;
    va_start(index_va_list, index_num);

    if (index_num == 1) {

        // If index size is just 1, then we simply use test

        ub_bit_check_t bit_check = va_arg(index_va_list, ub_bit_check_t);

        ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, bit_check);

        instr_t *instr;
        if (bit_check.is_set) {
            instr = INSTR_CREATE_jcc(drcontext, OP_jnz, *is_set_label);
        } else {
            instr = INSTR_CREATE_jcc(drcontext, OP_jz, *is_set_label);

        }

        instrlist_meta_preinsert(ilist, where, instr);

    } else {

        unsigned int mask_value = 0;
        unsigned int cmp_value = 0;

        for (int i = 0; i < index_num; i++) {

            ub_bit_check_t bit_check = va_arg(index_va_list, ub_bit_check_t);
            ub_byte_hp_set_bit(&cmp_value, &bit_check);
            ub_byte_hp_set_mask_bit(&mask_value, &bit_check);
        }

#ifdef X86_32

        opnd_t mask_opnd_immed = opnd_create_immed_uint(mask_value, OPSZ_4);
#else
        opnd_t mask_opnd_immed = opnd_create_immed_uint(mask_value, OPSZ_8);
#endif

        // Load value data to scratch register.
        opnd_t val_in_reg_opnd = opnd_create_reg(scratch_reg);
        instr_t *instr = INSTR_CREATE_mov_ld(drcontext, val_in_reg_opnd,
                *val_opnd);
        instrlist_meta_preinsert(ilist, where, instr);

        // Perform AND instruction
        instr = INSTR_CREATE_and(drcontext, val_in_reg_opnd, mask_opnd_immed);
        instrlist_meta_preinsert(ilist, where, instr);

#ifdef X86_32
        opnd_t cmp_opnd_immed = opnd_create_immed_uint(cmp_value, OPSZ_4);
#else
        opnd_t cmp_opnd_immed = opnd_create_immed_uint(cmp_value, OPSZ_8);
#endif

        instr = INSTR_CREATE_cmp(drcontext, val_in_reg_opnd, cmp_opnd_immed);
        instrlist_meta_preinsert(ilist, where, instr);

        instr = INSTR_CREATE_jcc(drcontext, OP_je, *is_set_label);
        instrlist_meta_preinsert(ilist, where, instr);
    }

    va_end(index_va_list);
}

DR_EXPORT void ub_byte_insert_is_any_bit_set(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *val_opnd,
        opnd_t *is_set_label, int index_num, ...) {

    // Set up VA
    va_list index_va_list;
    va_start(index_va_list, index_num);

    unsigned int mask_value = 0;

    for (int i = 0; i < index_num; i++) {

        ub_bit_check_t bit_check = va_arg(index_va_list, ub_bit_check_t);
        DR_ASSERT(bit_check.is_set);

        ub_byte_hp_set_mask_bit(&mask_value, &bit_check);
    }

#ifdef X86_32

    opnd_t opnd_immed = opnd_create_immed_uint(mask_value, OPSZ_4);
#else
    opnd_t opnd_immed = opnd_create_immed_uint(mask_value, OPSZ_8);
#endif

    instr_t *instr = INSTR_CREATE_test(drcontext, *val_opnd, opnd_immed);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jcc(drcontext, OP_jnz, *is_set_label);
    instrlist_meta_preinsert(ilist, where, instr);

    va_end(index_va_list);
}

