/*
 * ib_instrum_ptr_arith.c
 *
 *      Author: john
 */

#include "ub_ptr_arith_instr.h"
#include "../register/ub_register.h"

static bool ub_is_lea_d_s_size(instr_t *instr, size_t size) {

    opnd_t dst = instr_get_dst(instr, 0);
    opnd_t main_src = instr_get_src(instr, 0);

    return (opnd_get_size(main_src) == OPSZ_lea)
            && (opnd_size_in_bytes(opnd_get_size(dst)) == size);
}

DR_EXPORT bool ub_is_lea_dreg_sreg_sreg_instr(instr_t *instr) {

    opnd_t main_src = instr_get_src(instr, 0);
    reg_id_t base = opnd_get_base(main_src);
    reg_id_t index = opnd_get_index(main_src);

    return base != DR_REG_NULL && index != DR_REG_NULL;
}

DR_EXPORT bool ub_is_lea_dreg_2_sreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_lea_dreg_sreg_sreg_instr(instr) && ub_is_lea_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_lea_dreg_4_sreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_lea_dreg_sreg_sreg_instr(instr) && ub_is_lea_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_lea_dreg_8_sreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_lea_dreg_sreg_sreg_instr(instr) && ub_is_lea_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_lea_base_dreg_sreg_instr(instr_t *instr) {

    opnd_t main_src = instr_get_src(instr, 0);

    reg_id_t base = opnd_get_base(main_src);
    reg_id_t index = opnd_get_index(main_src);

    return base != DR_REG_NULL && index == DR_REG_NULL;
}

DR_EXPORT bool ub_is_lea_base_dreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_lea_base_dreg_sreg_instr(instr) && ub_is_lea_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_lea_base_dreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_lea_base_dreg_sreg_instr(instr) && ub_is_lea_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_lea_base_dreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_lea_base_dreg_sreg_instr(instr) && ub_is_lea_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_lea_index_dreg_sreg_instr(instr_t *instr) {

    opnd_t main_src = instr_get_src(instr, 0);

    reg_id_t base = opnd_get_base(main_src);
    reg_id_t index = opnd_get_index(main_src);

    return base == DR_REG_NULL && index != DR_REG_NULL;

}

DR_EXPORT bool ub_is_lea_index_dreg_2_sreg_2_instr(instr_t *instr) {

    return ub_is_lea_index_dreg_sreg_instr(instr)
            && ub_is_lea_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_lea_index_dreg_4_sreg_4_instr(instr_t *instr) {

    return ub_is_lea_index_dreg_sreg_instr(instr)
            && ub_is_lea_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_lea_index_dreg_8_sreg_8_instr(instr_t *instr) {

    return ub_is_lea_index_dreg_sreg_instr(instr)
            && ub_is_lea_d_s_size(instr, 8);
}

DR_EXPORT bool ub_is_lea_dreg_simm_instr(instr_t *instr) {

    opnd_t src = instr_get_src(instr, 0);

    reg_id_t base = opnd_get_base(src);
    reg_id_t index = opnd_get_index(src);

    return base == DR_REG_NULL && index == DR_REG_NULL;
}

DR_EXPORT bool ub_is_lea_dreg_2_simm_2_instr(instr_t *instr) {

    return ub_is_lea_dreg_simm_instr(instr)
            && ub_is_lea_d_s_size(instr, 2);
}

DR_EXPORT bool ub_is_lea_dreg_4_simm_4_instr(instr_t *instr) {

    return ub_is_lea_dreg_simm_instr(instr)
            && ub_is_lea_d_s_size(instr, 4);
}

DR_EXPORT bool ub_is_lea_dreg_8_simm_8_instr(instr_t *instr) {

    return ub_is_lea_dreg_simm_instr(instr)
            && ub_is_lea_d_s_size(instr, 8);
}
