/*
 * ub_generic_instr.c
 *
 *      Author: john
 */

#include "ub_generic_instr.h"
#include "../register/ub_register.h"

static bool ub_is_dst_d_size(instr_t *instr, int index, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    return (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

static bool ub_is_dreg(instr_t *instr, int index) {

    opnd_t dst = instr_get_dst(instr, index);
    return ub_opnd_is_reg(&dst);
}

DR_EXPORT bool ub_is_dreg_1_instr(instr_t *instr) {

    return ub_is_dreg(instr, 0) && ub_is_dst_d_size(instr, 0, 1);
}

DR_EXPORT bool ub_is_dreg_2_instr(instr_t *instr) {

    return ub_is_dreg(instr, 0) && ub_is_dst_d_size(instr, 0, 2);
}

DR_EXPORT bool ub_is_dreg_4_instr(instr_t *instr) {

    return ub_is_dreg(instr, 0) && ub_is_dst_d_size(instr, 0, 4);
}

DR_EXPORT bool ub_is_dreg_8_instr(instr_t *instr) {

    return ub_is_dreg(instr, 0) && ub_is_dst_d_size(instr, 0, 8);
}

DR_EXPORT bool ub_is_dreg_16_instr(instr_t *instr) {

    return ub_is_dreg(instr, 0) && ub_is_dst_d_size(instr, 0, 16);
}

static bool ub_is_dmem(instr_t *instr, int index) {

    opnd_t dst = instr_get_dst(instr, index);
    return opnd_is_memory_reference(dst);
}

DR_EXPORT bool ub_is_dmem_1_instr(instr_t *instr) {

    return ub_is_dmem(instr, 0) && ub_is_dst_d_size(instr, 0, 1);
}

DR_EXPORT bool ub_is_dmem_2_instr(instr_t *instr) {

    return ub_is_dmem(instr, 0) && ub_is_dst_d_size(instr, 0, 2);
}


DR_EXPORT bool ub_is_dmem_4_instr(instr_t *instr) {

    return ub_is_dmem(instr, 0) && ub_is_dst_d_size(instr, 0, 4);
}

DR_EXPORT bool ub_is_dmem_8_instr(instr_t *instr) {

    return ub_is_dmem(instr, 0) && ub_is_dst_d_size(instr, 0, 8);
}

DR_EXPORT bool ub_is_dmem_16_instr(instr_t *instr) {

    return ub_is_dmem(instr, 0) && ub_is_dst_d_size(instr, 0, 16);
}


/****
 * SECOND Dst
 */

DR_EXPORT bool ub_is_dreg_2nd_1_instr(instr_t *instr) {

    return ub_is_dreg(instr, 1) && ub_is_dst_d_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_dreg_2nd_2_instr(instr_t *instr) {

    return ub_is_dreg(instr, 1) && ub_is_dst_d_size(instr, 1, 2);
}

DR_EXPORT bool ub_is_dreg_2nd_4_instr(instr_t *instr) {

    return ub_is_dreg(instr, 1) && ub_is_dst_d_size(instr, 1, 4);
}

DR_EXPORT bool ub_is_dreg_2nd_8_instr(instr_t *instr) {

    return ub_is_dreg(instr, 1) && ub_is_dst_d_size(instr, 1, 8);
}

DR_EXPORT bool ub_is_dreg_2nd_16_instr(instr_t *instr) {

    return ub_is_dreg(instr, 1) && ub_is_dst_d_size(instr, 1, 16);
}


DR_EXPORT bool ub_is_dmem_2nd_1_instr(instr_t *instr) {

    return ub_is_dmem(instr, 1) && ub_is_dst_d_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_dmem_2nd_2_instr(instr_t *instr) {

    return ub_is_dmem(instr, 1) && ub_is_dst_d_size(instr, 1, 2);
}


DR_EXPORT bool ub_is_dmem_2nd_4_instr(instr_t *instr) {

    return ub_is_dmem(instr, 1) && ub_is_dst_d_size(instr, 1, 4);
}

DR_EXPORT bool ub_is_dmem_2nd_8_instr(instr_t *instr) {

    return ub_is_dmem(instr, 1) && ub_is_dst_d_size(instr, 1, 8);
}

DR_EXPORT bool ub_is_dmem_2nd_16_instr(instr_t *instr) {

    return ub_is_dmem(instr, 1) && ub_is_dst_d_size(instr, 1, 16);
}
