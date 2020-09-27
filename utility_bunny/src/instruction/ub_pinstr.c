/*
 * ub_pinstr.c
 *
 *      Author: john
 */

#include "ub_pinstr.h"
#include "../register/ub_register.h"

static bool ub_is_p_d_s_size(instr_t *instr, size_t dsize, size_t ssize) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == dsize)
            && (opnd_size_in_bytes(opnd_get_size(src)) == ssize);
}

static bool ub_is_p_dreg_sreg(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src);
}

static bool ub_is_p_dreg_smem(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src);
}

/****
 * PEXT
 */

static bool ub_is_pext_d_s_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src2)) == size);
}

DR_EXPORT bool ub_is_pext_dreg_sreg_sreg(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_pext_dreg_4_sreg_4_sreg_4(instr_t *instr) {

    return ub_is_pext_dreg_sreg_sreg(instr) && ub_is_pext_d_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_pext_dreg_8_sreg_8_sreg_8(instr_t *instr) {

    return ub_is_pext_dreg_sreg_sreg(instr) && ub_is_pext_d_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_pext_dreg_sreg_smem(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src)
            && opnd_is_memory_reference(src2);
}

DR_EXPORT bool ub_is_pext_dreg_4_sreg_4_smem_4(instr_t *instr) {

    return ub_is_pext_dreg_sreg_smem(instr) && ub_is_pext_d_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_pext_dreg_8_sreg_8_smem_8(instr_t *instr) {

    return ub_is_pext_dreg_sreg_smem(instr) && ub_is_pext_d_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_pextr_dmem_1_sreg_16(instr_t *instr) {


    opnd_t dst = instr_get_dst(instr, 0);
    return opnd_is_memory_reference(dst)  && ub_is_p_d_s_size(instr, 1, 16);
}


DR_EXPORT bool ub_is_pextr_dmem_2_sreg_16(instr_t *instr) {


    opnd_t dst = instr_get_dst(instr, 0);
    return opnd_is_memory_reference(dst)  && ub_is_p_d_s_size(instr, 2, 16);
}


DR_EXPORT bool ub_is_pextr_dmem_4_sreg_16(instr_t *instr) {


    opnd_t dst = instr_get_dst(instr, 0);
    return opnd_is_memory_reference(dst)  && ub_is_p_d_s_size(instr, 4, 16);
}

DR_EXPORT bool ub_is_pextr_dreg_4_sreg_16(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);

    return ub_opnd_is_reg(&dst) && ub_is_p_d_s_size(instr, 4, 16);
}

DR_EXPORT bool ub_is_pextr_dreg_4_sreg_8(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    return ub_opnd_is_reg(&dst)  && ub_is_p_d_s_size(instr, 4, 8);
}


/**
 * PMINU
 */

static bool ub_is_pminmax_d_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src)) == size);
}

DR_EXPORT bool ub_is_pminmax_dreg_smem(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_pminmax_dreg_sreg(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_pminmax_dreg_8_sreg_8(instr_t *instr) {

    return ub_is_pminmax_dreg_sreg(instr) && ub_is_pminmax_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_pminmax_dreg_8_smem_8(instr_t *instr) {

    return ub_is_pminmax_dreg_smem(instr) && ub_is_pminmax_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_pminmax_dreg_16_sreg_16(instr_t *instr) {

    return ub_is_pminmax_dreg_sreg(instr) && ub_is_pminmax_d_s_size(instr, 16);
}

DR_EXPORT bool ub_is_pminmax_dreg_16_smem_16(instr_t *instr) {

    return ub_is_pminmax_dreg_smem(instr) && ub_is_pminmax_d_s_size(instr, 16);
}

/**
 * PMOVMSK
 */

DR_EXPORT bool ub_is_pmovmsk_dreg_4_sreg_8(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 4, 8);
}

DR_EXPORT bool ub_is_pmovmsk_dreg_4_sreg_16(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 4, 16);
}

DR_EXPORT bool ub_is_pmovmsk_dreg_8_sreg_8(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_pmovmsk_dreg_8_sreg_16(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 8, 16);
}

/**
 * PACKSS
 */

DR_EXPORT bool ub_is_packss_dreg_8_sreg_8(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_packss_dreg_16_sreg_16(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_packss_dreg_8_smem_8(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_packss_dreg_16_smem_16(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

/**
 * PALIGN
 */

DR_EXPORT bool ub_is_palignr_dreg_8_sreg_8(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_palignr_dreg_8_smem_8(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_palignr_dreg_16_sreg_16(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_palignr_dreg_16_smem_16(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

/**
 * PSHUF
 */

DR_EXPORT bool ub_is_pshuf_dreg_8_sreg_8(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_pshuf_dreg_16_sreg_16(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_pshuf_dreg_8_smem_8(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_pshuf_dreg_16_smem_16(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

/**
 * PUNPCK
 */

DR_EXPORT bool ub_is_punpck_dreg_8_sreg_8(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_punpck_dreg_16_sreg_16(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_punpck_dreg_8_smem_8(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_punpck_dreg_16_smem_16(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

/**
 * PCMP
 */

DR_EXPORT bool ub_is_pcmp_dreg_8_sreg_8(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_pcmp_dreg_16_sreg_16(instr_t *instr) {

    return ub_is_p_dreg_sreg(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_pcmp_dreg_8_smem_8(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_pcmp_dreg_16_smem_16(instr_t *instr) {

    return ub_is_p_dreg_smem(instr) && ub_is_p_d_s_size(instr, 16, 16);
}

