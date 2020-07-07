/*
 * ub_shift_instr.c
 *
 *      Author: john
 */

#include "ub_shift_instr.h"
#include "../register/ub_register.h"

static bool ub_is_shift_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

DR_EXPORT bool ub_is_sole_mem_shift(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_immed(src)
            && opnd_get_size(src) == OPSZ_0;
}

DR_EXPORT bool ub_is_sole_mem_shift_1(instr_t *instr) {

    return ub_is_sole_mem_shift(instr) && ub_is_shift_size(instr, 1);
}

DR_EXPORT bool ub_is_sole_mem_shift_2(instr_t *instr) {

    return ub_is_sole_mem_shift(instr) && ub_is_shift_size(instr, 2);
}

DR_EXPORT bool ub_is_sole_mem_shift_4(instr_t *instr) {

    return ub_is_sole_mem_shift(instr) && ub_is_shift_size(instr, 4);
}

DR_EXPORT bool ub_is_sole_mem_shift_8(instr_t *instr) {

    return ub_is_sole_mem_shift(instr) && ub_is_shift_size(instr, 8);
}

DR_EXPORT bool ub_is_sole_reg_shift(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_immed(src)
            && opnd_get_size(src) == OPSZ_0;
}

DR_EXPORT bool ub_is_sole_reg_shift_1(instr_t *instr) {

    return ub_is_sole_reg_shift(instr) && ub_is_shift_size(instr, 1);
}

DR_EXPORT bool ub_is_sole_reg_shift_2(instr_t *instr) {

    return ub_is_sole_reg_shift(instr) && ub_is_shift_size(instr, 2);
}

DR_EXPORT bool ub_is_sole_reg_shift_4(instr_t *instr) {

    return ub_is_sole_reg_shift(instr) && ub_is_shift_size(instr, 4);
}

DR_EXPORT bool ub_is_sole_reg_shift_8(instr_t *instr) {

    return ub_is_sole_reg_shift(instr) && ub_is_shift_size(instr, 8);
}

DR_EXPORT bool ub_is_immed_mem_shift(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_immed(src)
            && opnd_get_size(src) == OPSZ_1;
}

DR_EXPORT bool ub_is_immed_mem_shift_1(instr_t *instr) {

    return ub_is_immed_mem_shift(instr) && ub_is_shift_size(instr, 1);
}

DR_EXPORT bool ub_is_immed_mem_shift_2(instr_t *instr) {

    return ub_is_immed_mem_shift(instr) && ub_is_shift_size(instr, 2);
}

DR_EXPORT bool ub_is_immed_mem_shift_4(instr_t *instr) {

    return ub_is_immed_mem_shift(instr) && ub_is_shift_size(instr, 4);
}

DR_EXPORT bool ub_is_immed_mem_shift_8(instr_t *instr) {

    return ub_is_immed_mem_shift(instr) && ub_is_shift_size(instr, 8);
}

DR_EXPORT bool ub_is_immed_mem_shift_16(instr_t *instr) {

    return ub_is_immed_mem_shift(instr) && ub_is_shift_size(instr, 16);
}

DR_EXPORT bool ub_is_immed_reg_shift(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_immed(src) && opnd_get_size(src) == OPSZ_1;
}

DR_EXPORT bool ub_is_immed_reg_shift_1(instr_t *instr) {

    return ub_is_immed_reg_shift(instr) && ub_is_shift_size(instr, 1);
}

DR_EXPORT bool ub_is_immed_reg_shift_2(instr_t *instr) {

    return ub_is_immed_reg_shift(instr) && ub_is_shift_size(instr, 2);
}

DR_EXPORT bool ub_is_immed_reg_shift_4(instr_t *instr) {

    return ub_is_immed_reg_shift(instr) && ub_is_shift_size(instr, 4);
}

DR_EXPORT bool ub_is_immed_reg_shift_8(instr_t *instr) {

    return ub_is_immed_reg_shift(instr) && ub_is_shift_size(instr, 8);
}

DR_EXPORT bool ub_is_immed_reg_shift_16(instr_t *instr) {

    return ub_is_immed_reg_shift(instr) && ub_is_shift_size(instr, 16);
}

DR_EXPORT bool ub_is_mem_reg_shift(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src)
            && opnd_get_size(src) == OPSZ_1;
}

DR_EXPORT bool ub_is_mem_reg_shift_1(instr_t *instr) {

    return ub_is_mem_reg_shift(instr) && ub_is_shift_size(instr, 1);
}

DR_EXPORT bool ub_is_mem_reg_shift_2(instr_t *instr) {

    return ub_is_mem_reg_shift(instr) && ub_is_shift_size(instr, 2);
}

DR_EXPORT bool ub_is_mem_reg_shift_4(instr_t *instr) {

    return ub_is_mem_reg_shift(instr) && ub_is_shift_size(instr, 4);
}

DR_EXPORT bool ub_is_mem_reg_shift_8(instr_t *instr) {

    return ub_is_mem_reg_shift(instr) && ub_is_shift_size(instr, 8);
}

DR_EXPORT bool ub_is_reg_reg_shift(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && opnd_get_size(src) == OPSZ_1;
}

DR_EXPORT bool ub_is_reg_reg_shift_1(instr_t *instr) {

    return ub_is_reg_reg_shift(instr) && ub_is_shift_size(instr, 1);
}

DR_EXPORT bool ub_is_reg_reg_shift_2(instr_t *instr) {

    return ub_is_reg_reg_shift(instr) && ub_is_shift_size(instr, 2);
}

DR_EXPORT bool ub_is_reg_reg_shift_4(instr_t *instr) {

    return ub_is_reg_reg_shift(instr) && ub_is_shift_size(instr, 4);
}

DR_EXPORT bool ub_is_reg_reg_shift_8(instr_t *instr) {

    return ub_is_reg_reg_shift(instr) && ub_is_shift_size(instr, 8);
}

/******
 * SHIFTD
 */

static bool ub_is_shiftd_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src2)) == 1);
}

DR_EXPORT bool ub_is_shiftd_dreg_sreg_simm(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && opnd_is_immed(src2);
}

DR_EXPORT bool ub_is_shiftd_dreg_2_sreg_2_simm_1(instr_t *instr) {

    return ub_is_shiftd_dreg_sreg_simm(instr) && ub_is_shiftd_size(instr, 2);
}

DR_EXPORT bool ub_is_shiftd_dreg_4_sreg_4_simm_1(instr_t *instr) {

    return ub_is_shiftd_dreg_sreg_simm(instr) && ub_is_shiftd_size(instr, 4);
}

DR_EXPORT bool ub_is_shiftd_dreg_8_sreg_8_simm_1(instr_t *instr) {

    return ub_is_shiftd_dreg_sreg_simm(instr) && ub_is_shiftd_size(instr, 8);
}

DR_EXPORT bool ub_is_shiftd_dmem_sreg_simm(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src)
            && opnd_is_immed(src2);
}

DR_EXPORT bool ub_is_shiftd_dmem_2_sreg_2_simm_1(instr_t *instr) {

    return ub_is_shiftd_dmem_sreg_simm(instr) && ub_is_shiftd_size(instr, 2);
}

DR_EXPORT bool ub_is_shiftd_dmem_4_sreg_4_simm_1(instr_t *instr) {

    return ub_is_shiftd_dmem_sreg_simm(instr) && ub_is_shiftd_size(instr, 4);
}

DR_EXPORT bool ub_is_shiftd_dmem_8_sreg_8_simm_1(instr_t *instr) {

    return ub_is_shiftd_dmem_sreg_simm(instr) && ub_is_shiftd_size(instr, 8);
}

DR_EXPORT bool ub_is_shiftd_dreg_sreg_sreg(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_shiftd_dreg_2_sreg_2_sreg_1(instr_t *instr) {

    return ub_is_shiftd_dreg_sreg_sreg(instr) && ub_is_shiftd_size(instr, 2);
}

DR_EXPORT bool ub_is_shiftd_dreg_4_sreg_4_sreg_1(instr_t *instr) {

    return ub_is_shiftd_dreg_sreg_sreg(instr) && ub_is_shiftd_size(instr, 4);
}

DR_EXPORT bool ub_is_shiftd_dreg_8_sreg_8_sreg_1(instr_t *instr) {

    return ub_is_shiftd_dreg_sreg_sreg(instr) && ub_is_shiftd_size(instr, 8);
}

DR_EXPORT bool ub_is_shiftd_dmem_sreg_sreg(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src)
            && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_shiftd_dmem_2_sreg_2_sreg_1(instr_t *instr) {

    return ub_is_shiftd_dmem_sreg_sreg(instr) && ub_is_shiftd_size(instr, 2);
}

DR_EXPORT bool ub_is_shiftd_dmem_4_sreg_4_sreg_1(instr_t *instr) {

    return ub_is_shiftd_dmem_sreg_sreg(instr) && ub_is_shiftd_size(instr, 4);
}

DR_EXPORT bool ub_is_shiftd_dmem_8_sreg_8_sreg_1(instr_t *instr) {

    return ub_is_shiftd_dmem_sreg_sreg(instr) && ub_is_shiftd_size(instr, 8);
}

/******
 * PSHIFT
 */

static bool ub_is_pshift_d_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(src)) == size)
            && (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

static bool ub_is_pshift_reg(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&src);
}

static bool ub_is_pshift_mem(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);

    return opnd_is_memory_reference(src) && ub_opnd_is_reg(&dst);
}

DR_EXPORT bool ub_is_reg_pshift_8(instr_t *instr) {

    return ub_is_pshift_reg(instr) && ub_is_pshift_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_reg_pshift_16(instr_t *instr) {

    return ub_is_pshift_reg(instr) && ub_is_pshift_d_s_size(instr, 16);
}

DR_EXPORT bool ub_is_mem_pshift_8(instr_t *instr) {

    return ub_is_pshift_mem(instr) && ub_is_pshift_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_mem_pshift_16(instr_t *instr) {

    return ub_is_pshift_mem(instr) && ub_is_pshift_d_s_size(instr, 16);
}

