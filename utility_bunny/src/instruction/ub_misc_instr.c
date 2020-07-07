/*
 * ub_misc_instr.c
 *
 *      Author: john
 */

#include "ub_misc_instr.h"

static bool ub_is_leave_d_d_s_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t dst2 = instr_get_dst(instr, 1);
    opnd_t src_pop = instr_get_src(instr, 2);

    return (opnd_size_in_bytes(opnd_get_size(dst)) == size)
            && (opnd_size_in_bytes(opnd_get_size(dst2)) == size)
            && (opnd_size_in_bytes(opnd_get_size(src_pop)) == size);
}

DR_EXPORT bool ub_is_leave_dreg_4_dreg_4_sreg_4_smem_4_instr(instr_t *instr) {

    return ub_is_leave_d_d_s_s_size(instr, 4);
}

DR_EXPORT bool ub_is_leave_dreg_8_dreg_8_sreg_8_smem_8_instr(instr_t *instr) {

    return ub_is_leave_d_d_s_s_size(instr, 8);
}
