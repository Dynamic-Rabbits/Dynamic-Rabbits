/*
 * ib_instrum_srcdst_src_instr_guard.c
 *
 *      Author: john
 */

#include "ub_srcdst_src_instr.h"
#include "../register/ub_register.h"

static bool ub_is_srcdst_src_d_s_size(instr_t *instr, size_t dsize,
        size_t ssize) {

    if (!opnd_same(instr_get_dst(instr, 0), instr_get_src(instr, 1))
            || instr_num_dsts(instr) != 1 || instr_num_srcs(instr) != 2)
        return false;

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(src)) == ssize)
            && (opnd_size_in_bytes(opnd_get_size(dst)) == dsize);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_smem_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_1_smem_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_smem_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_2_smem_2_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_smem_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_4_smem_4_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_smem_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_8_smem_8_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_smem_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_16_smem_16_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_smem_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_1_sreg_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_16_sreg_16_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_1_sreg_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_2_sreg_2_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_4_sreg_4_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_8_sreg_8_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_16_sreg_16_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_simm_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_immed(src);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_1_simm_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_2_simm_2_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_4_simm_4_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_8_simm_8_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_simm_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_immed(src);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_1_simm_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_2_simm_2_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_4_simm_4_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_8_simm_8_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_2_simm_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_4_simm_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dreg_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dreg_8_simm_1_instr(instr_t *instr) {
    return ub_is_srcdst_src_dreg_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_2_simm_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_4_simm_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 1);
}

DR_EXPORT bool ub_is_srcdst_src_dmem_8_simm_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_dmem_simm_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 1);
}

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return !opnd_same(dst, src) && ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_1_sreg_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_diff_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_srcdst_src_diff_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_srcdst_src_diff_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_srcdst_src_diff_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr_t *instr) {

    return ub_is_srcdst_src_diff_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 16, 16);
}

DR_EXPORT bool ub_is_srcdst_src_same_dreg_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_same(dst, src) && ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_srcdst_src_same_dreg_1_sreg_1_instr(instr_t *instr) {

    return ub_is_srcdst_src_same_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 1, 1);
}

DR_EXPORT bool ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_srcdst_src_same_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 2, 2);
}

DR_EXPORT bool ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_srcdst_src_same_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 4, 4);
}

DR_EXPORT bool ub_is_srcdst_src_same_dreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_srcdst_src_same_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 8, 8);
}

DR_EXPORT bool ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr_t *instr) {

    return ub_is_srcdst_src_same_dreg_sreg_instr(instr)
            && ub_is_srcdst_src_d_s_size(instr, 16, 16);
}
