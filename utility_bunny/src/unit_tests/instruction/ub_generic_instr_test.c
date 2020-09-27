/*
 * ub_generic_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_generic_instr.h"

static void ub_is_dreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CL),
            opnd_create_reg(DR_REG_AL));
    DR_ASSERT(ub_is_dreg_1_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_1_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_dreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CX),
            opnd_create_reg(DR_REG_AX));
    DR_ASSERT(ub_is_dreg_2_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_dreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_dreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_EAX), opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_dreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CX),
            opnd_create_reg(DR_REG_AX));
    DR_ASSERT(!ub_is_dreg_4_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_dreg_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_dreg_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_EAX), opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_dreg_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dreg_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CX),
            opnd_create_reg(DR_REG_AX));
    DR_ASSERT(!ub_is_dreg_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_pand(drcontext, opnd_create_reg(DR_REG_XMM2),
            opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(ub_is_dreg_16_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_dmem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CL),
            opnd_create_reg(DR_REG_AL));
    DR_ASSERT(!ub_is_dmem_1_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 2), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_dmem_1_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_dmem_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CL),
            opnd_create_reg(DR_REG_AL));
    DR_ASSERT(!ub_is_dmem_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 2), opnd_create_reg(DR_REG_CX));
    DR_ASSERT(ub_is_dmem_2_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_dmem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_dmem_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CL),
            opnd_create_reg(DR_REG_AL));
    DR_ASSERT(!ub_is_dmem_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 2), opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_dmem_4_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_dmem_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_dmem_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_dmem_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_CL),
            opnd_create_reg(DR_REG_AL));
    DR_ASSERT(!ub_is_dmem_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mov_st(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 2), opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_dmem_16_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_movdqu(drcontext,
            opnd_create_base_disp(DR_REG_XAX,DR_REG_XCX, 2, 0, OPSZ_16), opnd_create_reg(DR_REG_XMM0));
    DR_ASSERT(ub_is_dmem_16_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_dreg_1_instr_test();
    ub_is_dreg_2_instr_test();
    ub_is_dreg_4_instr_test();
    ub_is_dreg_16_instr_test();

    ub_is_dmem_1_instr_test();
    ub_is_dmem_2_instr_test();
    ub_is_dmem_4_instr_test();
    ub_is_dmem_16_instr_test();
}
