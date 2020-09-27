#include "ub_comparison_instr.h"
#include "../register/ub_register.h"

static bool ub_is_comparison_s_s_size(instr_t *instr, size_t size) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(src)) == size
            && opnd_size_in_bytes(opnd_get_size(src2)) == size);
}

/**
 * MEM VS MEM
 */

DR_EXPORT bool ub_is_comparison_smem_smem_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return opnd_is_memory_reference(src) && opnd_is_memory_reference(src2);
}

DR_EXPORT bool ub_is_cmp_smem_1_smem_1_instr(instr_t *instr) {

    return ub_is_comparison_smem_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmp_smem_2_smem_2_instr(instr_t *instr) {

    return ub_is_comparison_smem_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmp_smem_4_smem_4_instr(instr_t *instr) {

    return ub_is_comparison_smem_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_cmp_smem_8_smem_8_instr(instr_t *instr) {

    return ub_is_comparison_smem_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_cmp_smem_16_smem_16_instr(instr_t *instr) {

    return ub_is_comparison_smem_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 16);
}

/**
 * MEM VS REG
 */

DR_EXPORT bool ub_is_comparison_smem_sreg_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return opnd_is_memory_reference(src) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_cmp_smem_1_sreg_1_instr(instr_t *instr) {

    return ub_is_comparison_smem_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmp_smem_2_sreg_2_instr(instr_t *instr) {

    return ub_is_comparison_smem_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmp_smem_4_sreg_4_instr(instr_t *instr) {

    return ub_is_comparison_smem_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_cmp_smem_8_sreg_8_instr(instr_t *instr) {

    return ub_is_comparison_smem_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_cmp_smem_16_sreg_16_instr(instr_t *instr) {

    return ub_is_comparison_smem_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 16);
}

/**
 * REG VS MEM
 */

DR_EXPORT bool ub_is_comparison_sreg_smem_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&src) && opnd_is_memory_reference(src2);
}

DR_EXPORT bool ub_is_cmp_sreg_1_smem_1_instr(instr_t *instr) {

    return ub_is_comparison_sreg_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmp_sreg_2_smem_2_instr(instr_t *instr) {

    return ub_is_comparison_sreg_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmp_sreg_4_smem_4_instr(instr_t *instr) {

    return ub_is_comparison_sreg_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_cmp_sreg_8_smem_8_instr(instr_t *instr) {

    return ub_is_comparison_sreg_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_cmp_sreg_16_smem_16_instr(instr_t *instr) {

    return ub_is_comparison_sreg_smem_instr(instr)
            && ub_is_comparison_s_s_size(instr, 16);
}

/**
 * REG VS REG
 */

DR_EXPORT bool ub_is_comparison_sreg_sreg_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&src) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_cmp_sreg_1_sreg_1_instr(instr_t *instr) {

    return ub_is_comparison_sreg_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmp_sreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_comparison_sreg_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmp_sreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_comparison_sreg_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_cmp_sreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_comparison_sreg_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_cmp_sreg_16_sreg_16_instr(instr_t *instr) {

    return ub_is_comparison_sreg_sreg_instr(instr)
            && ub_is_comparison_s_s_size(instr, 16);
}

/**
 * REG VS IMM
 */

DR_EXPORT bool ub_is_comparison_sreg_simm_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&src) && opnd_is_immed(src2);
}

DR_EXPORT bool ub_is_cmp_sreg_1_simm_1_instr(instr_t *instr) {

    return ub_is_comparison_sreg_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmp_sreg_2_simm_2_instr(instr_t *instr) {

    return ub_is_comparison_sreg_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmp_sreg_4_simm_4_instr(instr_t *instr) {

    return ub_is_comparison_sreg_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_cmp_sreg_8_simm_8_instr(instr_t *instr) {

    return ub_is_comparison_sreg_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 8);
}

/**
 * MEM VS IMM
 */

DR_EXPORT bool ub_is_comparison_smem_simm_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return opnd_is_memory_reference(src) && opnd_is_immed(src2);
}

DR_EXPORT bool ub_is_cmp_smem_1_simm_1_instr(instr_t *instr) {

    return ub_is_comparison_smem_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmp_smem_2_simm_2_instr(instr_t *instr) {

    return ub_is_comparison_smem_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmp_smem_4_simm_4_instr(instr_t *instr) {

    return ub_is_comparison_smem_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_cmp_guard_smem_8_simm_8_instr(instr_t *instr) {

    return ub_is_comparison_smem_simm_instr(instr)
            && ub_is_comparison_s_s_size(instr, 8);
}
