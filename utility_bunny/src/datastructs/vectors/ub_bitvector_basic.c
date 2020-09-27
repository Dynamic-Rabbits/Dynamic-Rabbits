/*
 * ub_bitvector_raw.c
 *
 *      Author: john
 */

#include "ub_bitvector_basic.h"
#include "../../instrumentation/ub_instrum_insert.h"
#include "string.h"

DR_EXPORT void ub_bitvect_basic_init(byte *value, size_t size) {

    memset((void *) value, 0, size);
}

DR_EXPORT void ub_bitvect_basic_set_bit(byte *value, size_t index, bool is_set) {

    size_t byte_index = index / UB_BYTE_SIZE;
    size_t bit_index = index % UB_BYTE_SIZE;

    unsigned int mask = 1;
    mask = mask << bit_index;

    if (!is_set) {

        mask = ~mask;
        value[byte_index] = value[byte_index] & mask;

    } else {
        value[byte_index] = value[byte_index] | mask;
    }
}

DR_EXPORT bool ub_bitvect_basic_get_bit(byte *value, size_t index) {

    size_t byte_index = index / UB_BYTE_SIZE;
    size_t bit_index = index % UB_BYTE_SIZE;

    unsigned int mask = 1;
    mask = mask << bit_index;
    return (value[byte_index] & mask) != 0;
}

DR_EXPORT void ub_bitvect_basic_union(byte *dst_value, byte *src_value1,
        byte *src_value2, size_t size) {

    DR_ASSERT(dst_value);
    DR_ASSERT(src_value1);
    DR_ASSERT(src_value2);
    DR_ASSERT(dst_value != src_value2);

    if (dst_value != src_value1)
        memcpy((void *) dst_value, (void *) src_value1, size);

    for (size_t i = 0; i < size; i++)
        dst_value[i] |= src_value2[i];
}

DR_EXPORT bool ub_bitvect_basic_equal(byte *value1, byte *value2, size_t size) {

    for (size_t i = 0; i < size; i++) {

        if (ub_bitvect_basic_get_bit(value1, i) != ub_bitvect_basic_get_bit(value2, i)) {
            return false;
        }
    }

    return true;
}

/***********************************************************************************
 * Insert function
 */

static void ub_bitvect_basic_insert_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect2_reg, reg_id_t size_reg,
        reg_id_t scratch_reg, instr_t *principle_instr) {

    DR_ASSERT(reg_32_to_8(scratch_reg) != DR_REG_NULL);

    instr_t* done_label = INSTR_CREATE_label(drcontext);

    instr_t *instr;
    opnd_t opnd = opnd_create_reg(size_reg);
    instr = INSTR_CREATE_test(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd = opnd_create_instr(done_label);
    instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr_t* loop_label = INSTR_CREATE_label(drcontext);
    instrlist_meta_preinsert(ilist, where, loop_label);

    ub_instrum_sub_reg_immed(drcontext, ilist, where, size_reg, 1);

    // Load the value
    instr = INSTR_CREATE_movzx(drcontext,
            opnd_create_reg(scratch_reg),
            opnd_create_base_disp(bit_vect2_reg, size_reg, 1, 0, OPSZ_1));
    instrlist_meta_preinsert(ilist, where, instr);

    // Add principle instruction
    instrlist_meta_preinsert(ilist, where, principle_instr);

    // Loop again?
    ub_instrum_check_null_false_case(drcontext, ilist, where, size_reg,
            loop_label);

    instrlist_meta_preinsert(ilist, where, done_label);
}

DR_EXPORT void ub_bitvect_basic_insert_copy(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t bit_vect1_reg, reg_id_t bit_vect2_reg,
        reg_id_t size_reg, reg_id_t scratch_reg) {

    // Principle Instruction: Copy the value
    instr_t *principle_instr = INSTR_CREATE_mov_st(drcontext,
            opnd_create_base_disp(bit_vect1_reg, size_reg, 1, 0, OPSZ_1),
            opnd_create_reg(reg_32_to_8(scratch_reg)));

    ub_bitvect_basic_insert_helper(drcontext, ilist, where, bit_vect2_reg,
            size_reg, scratch_reg, principle_instr);
}

DR_EXPORT void ub_bitvect_basic_insert_union(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t bit_vect1_reg,
        reg_id_t bit_vect2_reg, reg_id_t size_reg, reg_id_t scratch_reg) {

    // Principle Instruction: Or the value
    instr_t *principle_instr = INSTR_CREATE_or(drcontext,
            opnd_create_base_disp(bit_vect1_reg, size_reg, 1, 0, OPSZ_1),
            opnd_create_reg(reg_32_to_8(scratch_reg)));

    ub_bitvect_basic_insert_helper(drcontext, ilist, where, bit_vect2_reg,
            size_reg, scratch_reg, principle_instr);
}
