/*
 * ub_transfer_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_transfer_instr.h"

static void ub_is_mov_dreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(ub_is_mov_dreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_mov_dreg_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_mov_dreg_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_mov_dreg_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AL),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_mov_dreg_1_sreg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_mov_dreg_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_mov_dreg_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(ub_is_mov_dreg_2_sreg_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_mov_dreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(ub_is_mov_dreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_EAX), OPND_CREATE_MEMPTR(DR_REG_ECX, 1));
    DR_ASSERT(!ub_is_mov_dreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AL),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mov_dreg_4_sreg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_mov_dreg_16_sreg_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_16_sreg_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_EAX), OPND_CREATE_MEMPTR(DR_REG_ECX, 1));
    DR_ASSERT(!ub_is_mov_dreg_16_sreg_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AL),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mov_dreg_16_sreg_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_reg(DR_REG_XMM0), opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(ub_is_mov_dreg_16_sreg_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_reg(DR_REG_XMM0),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 0, OPSZ_16));
    DR_ASSERT(!ub_is_mov_dreg_16_sreg_16_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_mov_dreg_smem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_mov_dreg_smem_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_reg(DR_REG_XMM0),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 0, OPSZ_16));
    DR_ASSERT(ub_is_mov_dreg_smem_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_mov_dreg_1_smem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_1_smem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_mov_dreg_1_smem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AL),
            OPND_CREATE_MEM8(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_mov_dreg_1_smem_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_mov_dreg_2_smem_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_2_smem_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_mov_dreg_2_smem_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_mov_dreg_2_smem_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_mov_dreg_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_EAX), OPND_CREATE_MEMPTR(DR_REG_ECX, 1));
    DR_ASSERT(ub_is_mov_dreg_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_mov_dreg_4_smem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_mov_dreg_16_smem_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_16_smem_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_EAX), OPND_CREATE_MEMPTR(DR_REG_ECX, 1));
    DR_ASSERT(!ub_is_mov_dreg_16_smem_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_mov_dreg_16_smem_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_reg(DR_REG_XMM0),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 0, OPSZ_16));
    DR_ASSERT(ub_is_mov_dreg_16_smem_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_reg(DR_REG_XMM0), opnd_create_reg(DR_REG_XMM0));
    DR_ASSERT(!ub_is_mov_dreg_16_smem_16_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_mov_dreg_16_smem_8_instr_test() {

}

static void ub_is_mov_dmem_smem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_smem_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(ub_is_mov_dmem_smem_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_mov_dmem_1_smem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_1_smem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_1_smem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(ub_is_mov_dmem_1_smem_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_movs_4(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_1_smem_1_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_mov_dmem_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_4_smem_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_movs_4(drcontext);
    DR_ASSERT(ub_is_mov_dmem_4_smem_4_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_mov_dmem_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(ub_is_mov_dmem_sreg_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_sreg_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_mov_dmem_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_1_sreg_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM8(DR_REG_XCX, 1), opnd_create_reg(DR_REG_AL));
    DR_ASSERT(ub_is_mov_dmem_1_sreg_1_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_mov_dmem_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_2_sreg_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_reg(DR_REG_AX));
    DR_ASSERT(ub_is_mov_dmem_2_sreg_2_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_mov_dmem_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM32(DR_REG_ECX, 1), opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_mov_dmem_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_reg(DR_REG_AX));
    DR_ASSERT(!ub_is_mov_dmem_4_sreg_4_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_mov_dmem_16_sreg_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_16_sreg_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM32(DR_REG_ECX, 1), opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_mov_dmem_16_sreg_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_sreg_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_reg(DR_REG_AX));
    DR_ASSERT(!ub_is_mov_dmem_16_sreg_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 0, OPSZ_16),
            opnd_create_reg(DR_REG_XMM0));
    DR_ASSERT(ub_is_mov_dmem_16_sreg_16_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_reg(DR_REG_XMM0), opnd_create_reg(DR_REG_XMM0));
    DR_ASSERT(!ub_is_mov_dmem_16_sreg_16_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);

}

static void ub_is_mov_dmem_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_simm_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_mov_dmem_simm_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            opnd_create_reg(DR_REG_XCX), opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dmem_simm_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_mov_dmem_1_simm_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_1_simm_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_1_simm_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_1_simm_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dmem_1_simm_1_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM8(DR_REG_XCX, 1), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_mov_dmem_1_simm_1_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_mov_dmem_2_simm_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_2_simm_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dmem_2_simm_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(ub_is_mov_dmem_2_simm_2_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_mov_dmem_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dmem_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dmem_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dmem_4_simm_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_mov_dmem_4_simm_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(!ub_is_mov_dmem_4_simm_4_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_mov_dreg_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dreg_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dreg_simm_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dreg_simm_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            opnd_create_reg(DR_REG_XCX), opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_mov_dreg_simm_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_mov_dreg_1_simm_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_1_simm_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dreg_1_simm_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dreg_1_simm_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dreg_1_simm_1_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dreg_1_simm_1_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CL),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_mov_dreg_1_simm_1_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_mov_dreg_2_simm_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dreg_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dreg_2_simm_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dreg_2_simm_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dreg_2_simm_2_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CX),
            opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(ub_is_mov_dreg_2_simm_2_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_mov_dreg_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_mov_dreg_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_mov_dreg_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movs_1(drcontext);
    DR_ASSERT(!ub_is_mov_dreg_4_simm_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_mov_dreg_4_simm_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_mov_dreg_4_simm_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CX),
            opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(!ub_is_mov_dreg_4_simm_4_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);

}

static void ub_is_push_dmem_smem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_push_dmem_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 2));
    DR_ASSERT(ub_is_push_dmem_smem_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_push_dmem_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_push_dmem_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 2));
    DR_ASSERT(ub_is_push_dmem_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_push_dmem_4_smem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_push_dmem_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(ub_is_push_dmem_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_push_dmem_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_push_dmem_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(ub_is_push_dmem_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_push_dmem_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_push_dmem_4_sreg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_push_dmem_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_push_imm(drcontext,
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_push_dmem_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_push_dmem_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_push_dmem_simm_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_instrum_push_dmem_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_push_imm(drcontext,
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_push_dmem_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_push(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_push_dmem_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_push_dmem_4_simm_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_push(drcontext,
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_push_dmem_4_simm_4_instr(instr1));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_pop_dreg_smem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(ub_is_pop_dreg_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_pop(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_pop_dreg_smem_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_pop_dreg_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(ub_is_pop_dreg_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_pop_dreg_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_pop(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 2));
    DR_ASSERT(!ub_is_pop_dreg_4_smem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_movzx_dreg_4_dreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_movzx_dreg_4_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_movzx_dreg_4_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEM8(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_movzx_dreg_4_sreg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_movzx_dreg_4_dreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_movzx_dreg_4_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(ub_is_movzx_dreg_4_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_movzx_dreg_4_sreg_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_movzx_dreg_4_smem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_movzx_dreg_4_smem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_movzx_dreg_4_smem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEM8(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_movzx_dreg_4_smem_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_movzx_dreg_4_smem_1_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_movzx_dreg_4_smem_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_movzx_dreg_4_smem_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_movzx_dreg_4_smem_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEM8(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_movzx_dreg_4_smem_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_movzx(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_movzx_dreg_4_smem_2_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_mov_dreg_sreg_instr_test();
    ub_is_mov_dreg_1_sreg_1_instr_test();
    ub_is_mov_dreg_2_sreg_2_instr_test();
    ub_is_mov_dreg_4_sreg_4_instr_test();
    ub_is_mov_dreg_16_sreg_16_instr_test();

    ub_is_mov_dreg_smem_instr_test();
    ub_is_mov_dreg_1_smem_1_instr_test();
    ub_is_mov_dreg_2_smem_2_instr_test();
    ub_is_mov_dreg_4_smem_4_instr_test();
    ub_is_mov_dreg_16_smem_16_instr_test();
    ub_is_mov_dreg_16_smem_8_instr_test();

    ub_is_mov_dmem_smem_instr_test();
    ub_is_mov_dmem_1_smem_1_instr_test();
    ub_is_mov_dmem_4_smem_4_instr_test();

    ub_is_mov_dmem_sreg_instr_test();
    ub_is_mov_dmem_1_sreg_1_instr_test();
    ub_is_mov_dmem_2_sreg_2_instr_test();
    ub_is_mov_dmem_4_sreg_4_instr_test();
    ub_is_mov_dmem_16_sreg_16_instr_test();

    ub_is_mov_dmem_simm_instr_test();
    ub_is_mov_dmem_1_simm_1_instr_test();
    ub_is_mov_dmem_2_simm_2_instr_test();
    ub_is_mov_dmem_4_simm_4_instr_test();

    ub_is_mov_dreg_simm_instr_test();
    ub_is_mov_dreg_1_simm_1_instr_test();
    ub_is_mov_dreg_2_simm_2_instr_test();
    ub_is_mov_dreg_4_simm_4_instr_test();

    ub_is_push_dmem_smem_instr_test();
    ub_is_push_dmem_4_smem_4_instr_test();

    ub_is_push_dmem_sreg_instr_test();
    ub_is_push_dmem_4_sreg_4_instr_test();

    ub_is_push_dmem_simm_instr_test();
    ub_instrum_push_dmem_4_simm_4_instr_test();

    ub_is_pop_dreg_smem_instr_test();
    ub_is_pop_dreg_4_smem_4_instr_test();

    ub_is_movzx_dreg_4_dreg_1_instr_test();
    ub_is_movzx_dreg_4_dreg_2_instr_test();
    ub_is_movzx_dreg_4_smem_1_instr_test();
    ub_is_movzx_dreg_4_smem_2_instr_test();
}

