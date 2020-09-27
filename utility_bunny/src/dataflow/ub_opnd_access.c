/*
 * ub_opnd_access.c
 *
 *      Author: john
 */

#include "ub_opnd_access.h"

opnd_t ub_opnd_access_get_opnd(instr_t *instr, ub_opnd_access_t *opnd_access){

    DR_ASSERT(instr);
    DR_ASSERT(opnd_access);

    opnd_t opnd = opnd_create_null();

    if (UB_SRC_OPND_1 <= opnd_access->opnd_field && opnd_access->opnd_field <= UB_SRC_OPND_8){
        opnd = instr_get_src(instr, opnd_access->opnd_field);

    }else if (UB_DST_OPND_1 <= opnd_access->opnd_field && opnd_access->opnd_field <= UB_DST_OPND_8){
        opnd = instr_get_dst(instr, opnd_access->opnd_field - UB_DST_OPND_1);

    }else{
        DR_ASSERT(false);
    }

    if (opnd_access->comp_field != UB_COMP_1)
        DR_ASSERT(opnd_is_memory_reference(opnd));

    reg_id_t inner_reg = DR_REG_NULL;
    int inner_int = 0;

    switch (opnd_access->comp_field){

    case UB_COMP_1:
        return opnd;

    case UB_COMP_2:
        inner_reg = opnd_get_base(opnd);
        DR_ASSERT(inner_reg != DR_REG_NULL);
        return opnd_create_reg(inner_reg);

    case UB_COMP_3:
        inner_reg = opnd_get_index(opnd);
        DR_ASSERT(inner_reg != DR_REG_NULL);
        return opnd_create_reg(inner_reg);

    case UB_COMP_4:
        inner_int = opnd_get_scale(opnd);
        return opnd_create_immed_int(inner_int, OPSZ_4);

    case UB_COMP_5:
        inner_int = opnd_get_disp(opnd);
        return opnd_create_immed_int(inner_int, OPSZ_4);

    default:
        DR_ASSERT(false);
    }

    return opnd;
}

