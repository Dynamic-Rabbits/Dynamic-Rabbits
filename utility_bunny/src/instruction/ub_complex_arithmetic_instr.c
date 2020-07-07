/*
 * tb_instrum_register_arithmetic.c
 *
 *      Author: john
 */

#include "ub_complex_arithmetic_instr.h"
#include "../register/ub_register.h"

/*********************************************************
 * MUL 4 Instruction
 */

static bool ub_is_mult_d_d_s_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src2)) == size);
}

static bool ub_is_mult_4_dreg_dreg_sreg_sreg_instr(instr_t *instr) {

    // This will map imul_4 and mul_4

    if (instr_num_dsts(instr) != 2 || instr_num_srcs(instr) != 2) {
        return false;
    }

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_mult_4_dreg_dreg_sreg_sreg_instr(instr)
            && ub_is_mult_d_d_s_s_size(instr, 4);
}

static DR_EXPORT bool ub_is_mult_dreg_dreg_smem_sreg_instr(instr_t *instr) {

    if (instr_num_dsts(instr) != 2 || instr_num_srcs(instr) != 2)
        return false;

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_is_memory_reference(src)) && ub_opnd_is_reg(&dst)
            && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr_t *instr) {

    return ub_is_mult_dreg_dreg_smem_sreg_instr(instr)
            && ub_is_mult_d_d_s_s_size(instr, 4);
}

/*********************************************************
 * MUL 1 Instruction
 */

static bool ub_is_mult_d_s_s_size(instr_t *instr, size_t dsize, size_t ssize) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == dsize)
            && (opnd_size_in_bytes(opnd_get_size(src)) == ssize)
            && (opnd_size_in_bytes(opnd_get_size(src2)) == ssize);
}

static bool ub_is_mult_dreg_sreg_sreg_instr(instr_t *instr) {

    if (instr_num_dsts(instr) != 1 || instr_num_srcs(instr) != 2) {
        return false;
    }

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_mult_dreg_2_sreg_1_sreg_1(instr_t *instr) {

    return ub_is_mult_dreg_sreg_sreg_instr(instr)
            && ub_is_mult_d_s_s_size(instr, 2, 1);
}


static bool ub_is_mult_dreg_smem_sreg(instr_t *instr) {

    if (instr_num_dsts(instr) != 1 || instr_num_srcs(instr) != 2) {
        return false;
    }

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src)
            && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_mult_dreg_2_smem_1_sreg_1(instr_t *instr) {

    return ub_is_mult_dreg_smem_sreg(instr)
            && ub_is_mult_d_s_s_size(instr, 2, 1);
}

/*********************************************************
 * IMUL IMM Instruction
 */

static bool ub_is_mult_d_s_size(instr_t *instr, size_t dsize, size_t ssize) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == dsize)
            && (opnd_size_in_bytes(opnd_get_size(src)) == ssize);
}


DR_EXPORT bool ub_is_mult_dreg_sreg_simm_instr(instr_t *instr) {

    if (instr_num_dsts(instr) != 1 || instr_num_srcs(instr) != 2) {
        return false;
    }

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && opnd_is_immed(src2);
}

DR_EXPORT bool ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr_t *instr) {

    return ub_is_mult_dreg_sreg_simm_instr(instr)
            && ub_is_mult_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr_t *instr) {

    return ub_is_mult_dreg_sreg_simm_instr(instr)
            && ub_is_mult_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_mult_dreg_8_sreg_8_simm_8_instr(instr_t *instr) {

    return ub_is_mult_dreg_sreg_simm_instr(instr)
            && ub_is_mult_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_mult_dreg_smem_simm_instr(instr_t *instr) {

    if (instr_num_dsts(instr) != 1 || instr_num_srcs(instr) != 2)
        return false;

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src)
            && opnd_is_immed(src2);
}

DR_EXPORT bool ub_is_mult_dreg_2_smem_2_simm_2_instr(instr_t *instr) {

    return ub_is_mult_dreg_smem_simm_instr(instr)
            && ub_is_mult_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_mult_dreg_4_smem_4_simm_4_instr(instr_t *instr) {

    return ub_is_mult_dreg_smem_simm_instr(instr)
            && ub_is_mult_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_mult_dreg_8_smem_8_simm_8_instr(instr_t *instr) {

    return ub_is_mult_dreg_smem_simm_instr(instr)
            && ub_is_mult_d_s_size(instr, 8, 8);
}

/*********************************************************
 * DIV 4 Instruction
 */

static bool ub_is_div_d_d_s_s_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_dst(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src2)) == size);
}

DR_EXPORT bool ub_is_div_dreg_dreg_smem_sreg_sreg_instr(instr_t *instr) {

    if (instr_num_dsts(instr) != 2 || instr_num_srcs(instr) != 3)
        return false;

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_dst(instr, 1);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src)
            && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr(
        instr_t *instr) {

    return ub_is_div_dreg_dreg_smem_sreg_sreg_instr(instr)
            && ub_is_div_d_d_s_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_div_dreg_8_dreg_8_smem_8_sreg_8_sreg_8_instr(
        instr_t *instr) {

    return ub_is_div_dreg_dreg_smem_sreg_sreg_instr(instr)
            && ub_is_div_d_d_s_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_div_dreg_dreg_sreg_sreg_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_dst(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(
        instr_t *instr) {

    return ub_is_div_dreg_dreg_sreg_sreg_sreg_instr(instr)
            && ub_is_div_d_d_s_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_div_dreg_8_dreg_8_sreg_8_sreg_8_sreg_8_instr(
        instr_t *instr) {

    return ub_is_div_dreg_dreg_sreg_sreg_sreg_instr(instr)
            && ub_is_div_d_d_s_s_s_size(instr, 8);
}

/*********************************************************
 * DIV 1 Instruction
 */

static bool ub_is_div_d_d_s_s_size(instr_t *instr, size_t size) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t dst2 = instr_get_dst(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(dst2)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src)) == size);
}

DR_EXPORT bool ub_is_div_dreg_dreg_smem_sreg_instr(instr_t *instr) {

    if (instr_num_dsts(instr) != 2 || instr_num_srcs(instr) != 2)
        return false;

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t dst2 = instr_get_dst(instr, 1);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src)
            && ub_opnd_is_reg(&dst2);
}

DR_EXPORT bool ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr(instr_t *instr) {


    return ub_is_div_dreg_dreg_smem_sreg_instr(instr)
            && ub_is_div_d_d_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_div_dreg_dreg_sreg_sreg_instr(instr_t *instr) {

    if (instr_num_dsts(instr) != 2 || instr_num_srcs(instr) != 2)
        return false;

    opnd_t src = instr_get_src(instr, 0);
    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t dst2 = instr_get_dst(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && ub_opnd_is_reg(&dst2);
}

DR_EXPORT bool ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr(instr_t *instr) {

    return ub_is_div_dreg_dreg_sreg_sreg_instr(instr)
            && ub_is_div_d_d_s_s_size(instr, 1);
}
