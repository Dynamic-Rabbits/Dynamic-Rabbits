/*
 * tb_instrum_rep_guard.c
 *
 *      Author: john
 */

#include "ub_rep_instr.h"
#include "../register/ub_register.h"

static bool ub_is_rep_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return (opnd_size_in_bytes(opnd_get_size(src)) == size)
            && (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

DR_EXPORT bool ub_is_rep_movs_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_rep_movsb_instr(instr_t *instr) {

    return ub_is_rep_movs_instr(instr) && ub_is_rep_size(instr, 1);
}

DR_EXPORT bool ub_is_rep_movsw_instr(instr_t *instr) {

    return ub_is_rep_movs_instr(instr) && ub_is_rep_size(instr, 2);
}

DR_EXPORT bool ub_is_rep_movsd_instr(instr_t *instr) {

    return ub_is_rep_movs_instr(instr) && ub_is_rep_size(instr, 4);
}

DR_EXPORT bool ub_is_rep_movsq_instr(instr_t *instr) {

    return ub_is_rep_movs_instr(instr) && ub_is_rep_size(instr, 8);
}

DR_EXPORT bool ub_is_rep_stos_instr(instr_t *instr) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t src = instr_get_src(instr, 0);

    return opnd_is_memory_reference(dst) && ub_opnd_is_reg(&src);
}

DR_EXPORT bool ub_is_rep_stosb_instr(instr_t *instr) {

    return ub_is_rep_stos_instr(instr) && ub_is_rep_size(instr, 1);
}

DR_EXPORT bool ub_is_rep_stosw_instr(instr_t *instr) {

    return ub_is_rep_stos_instr(instr) && ub_is_rep_size(instr, 2);
}

DR_EXPORT bool ub_is_rep_stosd_instr(instr_t *instr) {

    return ub_is_rep_stos_instr(instr) && ub_is_rep_size(instr, 4);
}

DR_EXPORT bool ub_is_rep_stosq_instr(instr_t *instr) {

    return ub_is_rep_stos_instr(instr) && ub_is_rep_size(instr, 8);
}
