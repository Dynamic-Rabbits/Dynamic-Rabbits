/*
 * tb_instrum_xchg_guard.c
 *
 *      Author: john
 */

#include "ub_xinstr_instr.h"
#include "../register/ub_register.h"

static bool ub_is_xchg_d_d_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(src)) == size)
            && (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

DR_EXPORT bool ub_is_xchg_reg_reg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_xchg_reg_1_reg_1_instr(instr_t *instr) {

    return ub_is_xchg_reg_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 1);
}

DR_EXPORT bool ub_is_xchg_reg_2_reg_2_instr(instr_t *instr) {

    return ub_is_xchg_reg_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 2);
}

DR_EXPORT bool ub_is_xchg_reg_4_reg_4_instr(instr_t *instr) {

    return ub_is_xchg_reg_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 4);
}

DR_EXPORT bool ub_is_xchg_reg_8_reg_8_instr(instr_t *instr) {

    return ub_is_xchg_reg_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 8);
}

DR_EXPORT bool ub_is_xchg_mem_reg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 1);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_xchg_mem_1_reg_1_instr(instr_t *instr) {

    return ub_is_xchg_mem_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 1);
}

DR_EXPORT bool ub_is_xchg_mem_2_reg_2_instr(instr_t *instr) {

    return ub_is_xchg_mem_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 2);
}

DR_EXPORT bool ub_is_xchg_mem_4_reg_4_instr(instr_t *instr) {

    return ub_is_xchg_mem_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 4);
}

DR_EXPORT bool ub_is_xchg_mem_8_reg_8_instr(instr_t *instr) {

    return ub_is_xchg_mem_reg_instr(instr) && ub_is_xchg_d_d_size(instr, 8);
}

DR_EXPORT bool ub_is_xchg_reg_mem_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_xchg_reg_1_mem_1_instr(instr_t *instr) {

    return ub_is_xchg_reg_mem_instr(instr) && ub_is_xchg_d_d_size(instr, 1);
}

DR_EXPORT bool ub_is_xchg_reg_2_mem_2_instr(instr_t *instr) {

    return ub_is_xchg_reg_mem_instr(instr) && ub_is_xchg_d_d_size(instr, 2);
}

DR_EXPORT bool ub_is_xchg_reg_4_mem_4_instr(instr_t *instr) {

    return ub_is_xchg_reg_mem_instr(instr) && ub_is_xchg_d_d_size(instr, 4);
}

DR_EXPORT bool ub_is_xchg_reg_8_mem_8_instr(instr_t *instr) {

    return ub_is_xchg_reg_mem_instr(instr) && ub_is_xchg_d_d_size(instr, 8);
}

static bool ub_is_cmpxchg_s_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src1 = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size
            && opnd_size_in_bytes(opnd_get_size(src1)) == size
            && opnd_size_in_bytes(opnd_get_size(src2)) == size);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src1 = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src1) && ub_opnd_is_reg(&src2);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_1_sreg_1_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_sreg_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_sreg_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_sreg_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 4);
}

DR_EXPORT bool ub_instr_cmpxchg_sreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_sreg_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 8);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_smem_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src1 = instr_get_src(instr, 0);
    opnd_t src2 = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src1)
            && opnd_is_memory_reference(src2);

}

DR_EXPORT bool ub_is_cmpxchg_sreg_1_smem_1_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_smem_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 1);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_2_smem_2_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_smem_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 2);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_4_smem_4_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_smem_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_cmpxchg_sreg_8_smem_8_instr(instr_t *instr) {

    return ub_is_cmpxchg_sreg_smem_instr(instr)
            && ub_is_cmpxchg_s_s_size(instr, 8);
}
