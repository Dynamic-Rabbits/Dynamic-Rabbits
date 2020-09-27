/*
 * ub_shift_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_shift_instr.h"

static void ub_is_sole_shift_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(ub_is_sole_reg_shift(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_sole_reg_shift(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_sole_shift_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(ub_is_sole_reg_shift_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_sole_reg_shift_1(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_sole_shift_2_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(ub_is_sole_reg_shift_2(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_sole_reg_shift_2(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_sole_shift_4_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(ub_is_sole_reg_shift_4(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_sole_reg_shift_4(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_immed_shift_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_immed_reg_shift(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_immed_reg_shift(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_immed_reg_shift(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_immed_shift_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_immed_reg_shift_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_immed_reg_shift_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_immed_reg_shift_1(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_immed_shift_2_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_immed_reg_shift_2(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_immed_reg_shift_2(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_immed_reg_shift_2(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_immed_shift_4_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_immed_reg_shift_4(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_immed_reg_shift_4(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_immed_reg_shift_4(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_immed_shift_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_immed_reg_shift_16(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_immed_reg_shift_16(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_immed_reg_shift_16(instr3));

    instr_t *instr4 = INSTR_CREATE_psraw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_immed_reg_shift_16(instr4));

    instr_t *instr5 = INSTR_CREATE_psraw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_immed_reg_shift_16(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_reg_shift_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_reg_reg_shift(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_reg_reg_shift(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_reg_reg_shift(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_reg_shift_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_reg_reg_shift_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_reg_reg_shift_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_reg_reg_shift_1(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_reg_shift_2_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_reg_reg_shift_2(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_reg_reg_shift_2(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_reg_reg_shift_2(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_reg_shift_4_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_0));
    DR_ASSERT(!ub_is_reg_reg_shift_4(instr1));

    instr_t *instr2 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_reg_reg_shift_4(instr2));

    instr_t *instr3 = INSTR_CREATE_shr(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_reg_reg_shift_4(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_shiftd_dreg_reg_imm_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_shiftd_dreg_sreg_simm(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dreg_sreg_simm(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dreg_sreg_simm(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_shiftd_dreg_2_reg_2_imm_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_shiftd_dreg_2_sreg_2_simm_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dreg_2_sreg_2_simm_1(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_shiftd_dreg_4_reg_4_imm_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_shiftd_dreg_4_sreg_4_simm_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dreg_4_sreg_4_simm_1(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_shiftd_dmem_reg_imm_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_sreg_simm(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_sreg_simm(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_sreg_simm(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_shiftd_dmem_sreg_simm(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_shiftd_dmem_2_reg_2_imm_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_2_sreg_2_simm_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_2_sreg_2_simm_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            OPND_CREATE_MEM16(DR_REG_EDX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_2_sreg_2_simm_1(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEM16(DR_REG_EDX, 2), opnd_create_reg(DR_REG_DX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_shiftd_dmem_2_sreg_2_simm_1(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_shiftd_dmem_4_reg_4_imm_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_4_sreg_4_simm_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_4_sreg_4_simm_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_4_sreg_4_simm_1(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_shiftd_dmem_4_sreg_4_simm_1(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_shiftd_dreg_reg_reg_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dreg_sreg_sreg(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_shiftd_dreg_sreg_sreg(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dreg_sreg_sreg(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dreg_sreg_sreg(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_shiftd_dreg_2_reg_2_reg_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dreg_2_sreg_2_sreg_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_shiftd_dreg_2_sreg_2_sreg_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            OPND_CREATE_MEM16(DR_REG_EDX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dreg_2_sreg_2_sreg_1(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            OPND_CREATE_MEM16(DR_REG_EDX, 2), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dreg_2_sreg_2_sreg_1(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_shiftd_dreg_4_reg_4_reg_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dreg_4_sreg_4_sreg_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_shiftd_dreg_4_sreg_4_sreg_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dreg_4_sreg_4_sreg_1(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dreg_4_sreg_4_sreg_1(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_shiftd_dmem_reg_reg_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_sreg_sreg(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_sreg_sreg(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_shiftd_dmem_sreg_sreg(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_EDX, 2), opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_sreg_sreg(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_shiftd_dmem_2_reg_2_reg_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_2_sreg_2_sreg_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_2_sreg_2_sreg_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEM16(DR_REG_EDX, 2), opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_shiftd_dmem_2_sreg_2_sreg_1(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEM16(DR_REG_EDX, 2), opnd_create_reg(DR_REG_DX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_2_sreg_2_sreg_1(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_shiftd_dmem_4_reg_4_reg_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_4_sreg_4_sreg_1(instr1));

    instr_t *instr2 = INSTR_CREATE_shrd(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_shiftd_dmem_4_sreg_4_sreg_1(instr2));

    instr_t *instr3 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEM32(DR_REG_EDX, 2), opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_shiftd_dmem_4_sreg_4_sreg_1(instr3));

    instr_t *instr4 = INSTR_CREATE_shrd(drcontext,
            OPND_CREATE_MEM32(DR_REG_EDX, 2), opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_shiftd_dmem_4_sreg_4_sreg_1(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_reg_pshift_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_reg_pshift_8(instr1));

    instr_t *instr2 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            OPND_CREATE_MEM64(DR_REG_EBX, 1));
    DR_ASSERT(!ub_is_reg_pshift_8(instr2));

    instr_t *instr3 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_reg_pshift_8(instr3));

    instr_t *instr4 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_EBX, DR_REG_NULL, 1, 1, OPSZ_16));
    DR_ASSERT(!ub_is_reg_pshift_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_reg_pshift_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_reg_pshift_16(instr1));

    instr_t *instr2 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            OPND_CREATE_MEM64(DR_REG_EBX, 1));
    DR_ASSERT(!ub_is_reg_pshift_16(instr2));

    instr_t *instr3 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_reg_pshift_16(instr3));

    instr_t *instr4 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_EBX, DR_REG_NULL, 1, 1, OPSZ_16));
    DR_ASSERT(!ub_is_reg_pshift_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_mem_pshift_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_mem_pshift_8(instr1));

    instr_t *instr2 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            OPND_CREATE_MEM64(DR_REG_EBX, 1));
    DR_ASSERT(!ub_is_mem_pshift_8(instr2));

    instr_t *instr3 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_mem_pshift_8(instr3));

    instr_t *instr4 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_EBX, DR_REG_NULL, 1, 1, OPSZ_16));
    DR_ASSERT(!ub_is_mem_pshift_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_mem_pshift_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_mem_pshift_16(instr1));

    instr_t *instr2 = INSTR_CREATE_psrad(drcontext, opnd_create_reg(DR_REG_MM1),
            OPND_CREATE_MEM64(DR_REG_EBX, 1));
    DR_ASSERT(!ub_is_mem_pshift_16(instr2));

    instr_t *instr3 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_mem_pshift_16(instr3));

    instr_t *instr4 = INSTR_CREATE_psrad(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_EBX, DR_REG_NULL, 1, 1, OPSZ_16));
    DR_ASSERT(ub_is_mem_pshift_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_sole_shift_test();

    ub_is_sole_shift_1_test();
    ub_is_sole_shift_2_test();
    ub_is_sole_shift_4_test();

    ub_is_immed_shift_test();

    ub_is_immed_shift_1_test();
    ub_is_immed_shift_2_test();
    ub_is_immed_shift_4_test();
    ub_is_immed_shift_16_test();

    ub_is_reg_shift_test();

    ub_is_reg_shift_1_test();
    ub_is_reg_shift_2_test();
    ub_is_reg_shift_4_test();

    ub_is_shiftd_dreg_reg_imm_test();
    ub_is_shiftd_dreg_2_reg_2_imm_1_test();
    ub_is_shiftd_dreg_4_reg_4_imm_1_test();

    ub_is_shiftd_dmem_reg_imm_test();

    ub_is_shiftd_dmem_2_reg_2_imm_1_test();
    ub_is_shiftd_dmem_4_reg_4_imm_1_test();

    ub_is_shiftd_dreg_reg_reg_test();
    ub_is_shiftd_dreg_2_reg_2_reg_1_test();
    ub_is_shiftd_dreg_4_reg_4_reg_1_test();

    ub_is_shiftd_dmem_reg_reg_test();
    ub_is_shiftd_dmem_2_reg_2_reg_1_test();
    ub_is_shiftd_dmem_4_reg_4_reg_1_test();

    ub_is_reg_pshift_8_test();
    ub_is_reg_pshift_16_test();

    ub_is_mem_pshift_8_test();
    ub_is_mem_pshift_16_test();
}

