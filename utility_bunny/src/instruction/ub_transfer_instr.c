/*
 * ib_instrum_transfer_guard.c
 *
 *      Author: john
 */

#include "ub_transfer_instr.h"
#include "../register/ub_register.h"

static bool ub_is_mov_d_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src)) == size);
}

static bool ub_is_mov_d_s_dsize_ssize(instr_t *instr, size_t dsize,
        size_t ssize) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == dsize)
            && (opnd_size_in_bytes(opnd_get_size(src)) == ssize);
}

DR_EXPORT bool ub_is_mov_dreg_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_mov_dreg_1_sreg_1_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 1);
}

DR_EXPORT bool ub_is_mov_dreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_mov_dreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_mov_dreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_mov_dreg_16_sreg_16_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 16);
}

DR_EXPORT bool ub_is_mov_dreg_smem_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_mov_dreg_1_smem_1_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_mov_d_s_size(instr, 1);
}

DR_EXPORT bool ub_is_mov_dreg_2_smem_2_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_mov_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_mov_dreg_4_smem_4_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_mov_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_mov_dreg_8_smem_8_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_mov_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_mov_dreg_16_smem_16_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_mov_d_s_size(instr, 16);
}

/* MOVD */

DR_EXPORT bool ub_is_mov_dreg_16_smem_4_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 16, 4);
}

DR_EXPORT bool ub_is_mov_dreg_16_sreg_4_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 16, 4);
}

DR_EXPORT bool ub_is_mov_dmem_4_sreg_16_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 4, 16);
}

DR_EXPORT bool ub_is_mov_dreg_4_sreg_16_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 4, 16);
}

DR_EXPORT bool ub_is_mov_dreg_8_smem_4_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 8, 4);
}

DR_EXPORT bool ub_is_mov_dreg_8_sreg_4_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 8, 4);
}

DR_EXPORT bool ub_is_mov_dmem_4_sreg_8_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 4, 8);
}

DR_EXPORT bool ub_is_mov_dreg_4_sreg_8_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 4, 8);
}

/* MOVQ */

DR_EXPORT bool ub_is_mov_dreg_8_sreg_16_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 8, 16);
}

DR_EXPORT bool ub_is_mov_dmem_8_sreg_16_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 8, 16);
}

DR_EXPORT bool ub_is_mov_dreg_16_smem_8_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 16, 8);
}

DR_EXPORT bool ub_is_mov_dreg_16_sreg_8_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr)
            && ub_is_mov_d_s_dsize_ssize(instr, 16, 8);
}


DR_EXPORT bool ub_is_mov_dmem_smem_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_mov_dmem_1_smem_1_instr(instr_t *instr) {

    return ub_is_mov_dmem_smem_instr(instr) && ub_is_mov_d_s_size(instr, 1);
}

DR_EXPORT bool ub_is_mov_dmem_2_smem_2_instr(instr_t *instr) {

    return ub_is_mov_dmem_smem_instr(instr) && ub_is_mov_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_mov_dmem_4_smem_4_instr(instr_t *instr) {

    return ub_is_mov_dmem_smem_instr(instr) && ub_is_mov_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_mov_dmem_8_smem_8_instr(instr_t *instr) {

    return ub_is_mov_dmem_smem_instr(instr) && ub_is_mov_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_mov_dmem_16_smem_16_instr(instr_t *instr) {

    return ub_is_mov_dmem_smem_instr(instr) && ub_is_mov_d_s_size(instr, 16);
}

DR_EXPORT bool ub_is_mov_dmem_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_mov_dmem_1_sreg_1_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 1);
}

DR_EXPORT bool ub_is_mov_dmem_2_sreg_2_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_mov_dmem_4_sreg_4_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_mov_dmem_8_sreg_8_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_mov_dmem_16_sreg_16_instr(instr_t *instr) {

    return ub_is_mov_dmem_sreg_instr(instr) && ub_is_mov_d_s_size(instr, 16);
}

static bool ub_is_mov_d_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

DR_EXPORT bool ub_is_mov_dmem_simm_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_immed(src);
}

DR_EXPORT bool ub_is_mov_dmem_1_simm_1_instr(instr_t *instr) {

    return ub_is_mov_dmem_simm_instr(instr) && ub_is_mov_d_size(instr, 1);
}

DR_EXPORT bool ub_is_mov_dmem_2_simm_2_instr(instr_t *instr) {

    return ub_is_mov_dmem_simm_instr(instr) && ub_is_mov_d_size(instr, 2);
}

DR_EXPORT bool ub_is_mov_dmem_4_simm_4_instr(instr_t *instr) {

    return ub_is_mov_dmem_simm_instr(instr) && ub_is_mov_d_size(instr, 4);
}

DR_EXPORT bool ub_is_mov_dmem_8_simm_8_instr(instr_t *instr) {

    return ub_is_mov_dmem_simm_instr(instr) && ub_is_mov_d_size(instr, 8);
}

DR_EXPORT bool ub_is_mov_dreg_simm_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return ub_opnd_is_reg(&dst) && opnd_is_immed(src);
}

DR_EXPORT bool ub_is_mov_dreg_1_simm_1_instr(instr_t *instr) {

    return ub_is_mov_dreg_simm_instr(instr) && ub_is_mov_d_size(instr, 1);
}

DR_EXPORT bool ub_is_mov_dreg_2_simm_2_instr(instr_t *instr) {

    return ub_is_mov_dreg_simm_instr(instr) && ub_is_mov_d_size(instr, 2);
}

DR_EXPORT bool ub_is_mov_dreg_4_simm_4_instr(instr_t *instr) {

    return ub_is_mov_dreg_simm_instr(instr) && ub_is_mov_d_size(instr, 4);
}

DR_EXPORT bool ub_is_mov_dreg_8_simm_8_instr(instr_t *instr) {

    return ub_is_mov_dreg_simm_instr(instr) && ub_is_mov_d_size(instr, 8);
}

static bool ub_is_push_d_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size
            && opnd_size_in_bytes(opnd_get_size(src)) == size);
}

DR_EXPORT bool ub_is_push_dmem_smem_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_push_dmem_1_smem_1_instr(instr_t *instr) {

    return ub_is_push_dmem_smem_instr(instr) && ub_is_push_d_s_size(instr, 1);
}

DR_EXPORT bool ub_is_push_dmem_2_smem_2_instr(instr_t *instr) {

    return ub_is_push_dmem_smem_instr(instr) && ub_is_push_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_push_dmem_4_smem_4_instr(instr_t *instr) {

    return ub_is_push_dmem_smem_instr(instr) && ub_is_push_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_push_dmem_8_smem_8_instr(instr_t *instr) {

    return ub_is_push_dmem_smem_instr(instr) && ub_is_push_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_push_dmem_sreg_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_push_dmem_1_sreg_1_instr(instr_t *instr) {

    return ub_is_push_dmem_sreg_instr(instr) && ub_is_push_d_s_size(instr, 1);
}

DR_EXPORT bool ub_is_push_dmem_2_sreg_2_instr(instr_t *instr) {

    return ub_is_push_dmem_sreg_instr(instr) && ub_is_push_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_push_dmem_4_sreg_4_instr(instr_t *instr) {

    return ub_is_push_dmem_sreg_instr(instr) && ub_is_push_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_push_dmem_8_sreg_8_instr(instr_t *instr) {

    return ub_is_push_dmem_sreg_instr(instr) && ub_is_push_d_s_size(instr, 8);
}

static bool ub_is_push_d_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

DR_EXPORT bool ub_is_push_dmem_simm_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 1);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_immed(src);
}

DR_EXPORT bool ub_is_push_dmem_1_simm_1_instr(instr_t *instr) {

    return ub_is_push_dmem_simm_instr(instr) && ub_is_push_d_size(instr, 1);
}

DR_EXPORT bool ub_is_push_dmem_2_simm_2_instr(instr_t *instr) {

    return ub_is_push_dmem_simm_instr(instr) && ub_is_push_d_size(instr, 2);
}

DR_EXPORT bool ub_is_push_dmem_4_simm_4_instr(instr_t *instr) {

    return ub_is_push_dmem_simm_instr(instr) && ub_is_push_d_size(instr, 4);
}

DR_EXPORT bool ub_is_push_dmem_8_simm_8_instr(instr_t *instr) {

    return ub_is_push_dmem_simm_instr(instr) && ub_is_push_d_size(instr, 8);
}

static bool ub_is_pop_d_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 1);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size
            && opnd_size_in_bytes(opnd_get_size(src)) == size);
}

DR_EXPORT bool ub_is_pop_dreg_smem_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 1);

    return ub_opnd_is_reg(&dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_pop_dreg_1_smem_1_instr(instr_t *instr) {

    return ub_is_pop_dreg_smem_instr(instr) && ub_is_pop_d_s_size(instr, 1);
}

DR_EXPORT bool ub_is_pop_dreg_2_smem_2_instr(instr_t *instr) {

    return ub_is_pop_dreg_smem_instr(instr) && ub_is_pop_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_pop_dreg_4_smem_4_instr(instr_t *instr) {

    return ub_is_pop_dreg_smem_instr(instr) && ub_is_pop_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_pop_dreg_8_smem_8_instr(instr_t *instr) {

    return ub_is_pop_dreg_smem_instr(instr) && ub_is_pop_d_s_size(instr, 8);
}

static bool ub_is_movzx_d_2_d_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == 2
            && opnd_size_in_bytes(opnd_get_size(src)) == size);
}

DR_EXPORT bool ub_is_movzx_dreg_2_sreg_1_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_movzx_d_2_d_size(instr, 1);
}


static bool ub_is_movzx_d_4_d_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == 4
            && opnd_size_in_bytes(opnd_get_size(src)) == size);
}

DR_EXPORT bool ub_is_movzx_dreg_4_sreg_1_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_movzx_d_4_d_size(instr, 1);
}

DR_EXPORT bool ub_is_movzx_dreg_4_sreg_2_instr(instr_t *instr) {

    return ub_is_mov_dreg_sreg_instr(instr) && ub_is_movzx_d_4_d_size(instr, 2);
}

DR_EXPORT bool ub_is_movzx_dreg_2_smem_1_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_movzx_d_2_d_size(instr, 1);
}

DR_EXPORT bool ub_is_movzx_dreg_4_smem_1_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_movzx_d_4_d_size(instr, 1);
}

DR_EXPORT bool ub_is_movzx_dreg_4_smem_2_instr(instr_t *instr) {

    return ub_is_mov_dreg_smem_instr(instr) && ub_is_movzx_d_4_d_size(instr, 2);
}
