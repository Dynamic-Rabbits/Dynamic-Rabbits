/*
 * ub_call_instr.c
 *
 *      Author: john
 */

#include "ub_cti_instr.h"
#include "../register/ub_register.h"

DR_EXPORT bool ub_is_ret_instr(instr_t *instr) {

    return instr_num_srcs(instr) == 2;
}

DR_EXPORT bool ub_is_ret_imm_instr(instr_t *instr) {

    return instr_num_srcs(instr) == 3;
}

DR_EXPORT bool ub_is_cti_mem_instr(instr_t *instr) {

    DR_ASSERT(instr_is_cti(instr));


    opnd_t src = instr_get_src(instr, 0);
    return opnd_is_memory_reference(src);
}

DR_EXPORT bool ub_is_cti_reg_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);
    return ub_opnd_is_reg(&src);
}






