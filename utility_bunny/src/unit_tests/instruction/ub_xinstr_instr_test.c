/*
 * ub_xinstr_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_xinstr_instr.h"

static void ub_is_xchg_reg_reg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(ub_is_xchg_reg_reg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1));
    DR_ASSERT(!ub_is_xchg_reg_reg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_xchg_reg_1_reg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_reg_1_reg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_CL),
            opnd_create_reg(DR_REG_AL));
    DR_ASSERT(ub_is_xchg_reg_1_reg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1));
    DR_ASSERT(!ub_is_xchg_reg_1_reg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_xchg_reg_2_reg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_reg_2_reg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_CX),
            opnd_create_reg(DR_REG_AX));
    DR_ASSERT(ub_is_xchg_reg_2_reg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1));
    DR_ASSERT(!ub_is_xchg_reg_2_reg_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_xchg_reg_4_reg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_CX),
            opnd_create_reg(DR_REG_AX));
    DR_ASSERT(!ub_is_xchg_reg_4_reg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_ECX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_xchg_reg_4_reg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1));
    DR_ASSERT(!ub_is_xchg_reg_4_reg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_xchg_mem_reg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_mem_reg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(ub_is_xchg_mem_reg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_xchg_mem_1_reg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_mem_1_reg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_xchg_mem_1_reg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 1), opnd_create_reg(DR_REG_CH));
    DR_ASSERT(ub_is_xchg_mem_1_reg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_xchg_mem_2_reg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_mem_2_reg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1), opnd_create_reg(DR_REG_XCX));
    DR_ASSERT(!ub_is_xchg_mem_2_reg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 1), opnd_create_reg(DR_REG_CX));
    DR_ASSERT(ub_is_xchg_mem_2_reg_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_xchg_mem_4_reg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_mem_4_reg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext,
            OPND_CREATE_MEM32(DR_REG_EAX, 1), opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_xchg_mem_4_reg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 1), opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_xchg_mem_4_reg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_xchg_reg_mem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_reg_mem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1));
    DR_ASSERT(ub_is_xchg_reg_mem_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_xchg_reg_1_mem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_reg_1_mem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1));
    DR_ASSERT(!ub_is_xchg_reg_1_mem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_CL),
            OPND_CREATE_MEM8(DR_REG_XAX, 1));
    DR_ASSERT(ub_is_xchg_reg_1_mem_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_xchg_reg_2_mem_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_reg_2_mem_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 1));
    DR_ASSERT(!ub_is_xchg_reg_2_mem_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_CX),
            OPND_CREATE_MEM16(DR_REG_XAX, 1));
    DR_ASSERT(ub_is_xchg_reg_2_mem_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_xchg_reg_4_mem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_xchg_reg_4_mem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            OPND_CREATE_MEM32(DR_REG_XAX, 1));
    DR_ASSERT(ub_is_xchg_reg_4_mem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_CX),
            OPND_CREATE_MEM16(DR_REG_XAX, 1));
    DR_ASSERT(!ub_is_xchg_reg_4_mem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmpxchg_sreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmpxchg_1(drcontext,
            opnd_create_reg(DR_REG_CL), opnd_create_reg(DR_REG_DL));
    DR_ASSERT(ub_is_cmpxchg_sreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmpxchg_1(drcontext,
            opnd_create_reg(DR_REG_CL), OPND_CREATE_MEM8(DR_REG_EDX, 1));
    DR_ASSERT(!ub_is_cmpxchg_sreg_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_cmpxchg_sreg_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmpxchg_1(drcontext,
            opnd_create_reg(DR_REG_CL), opnd_create_reg(DR_REG_DL));
    DR_ASSERT(ub_is_cmpxchg_sreg_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmpxchg_1(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEM8(DR_REG_EDX, 1));
    DR_ASSERT(!ub_is_cmpxchg_sreg_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmpxchg_4(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_cmpxchg_sreg_1_sreg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_cmpxchg_sreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmpxchg_1(drcontext,
            opnd_create_reg(DR_REG_CL), opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_cmpxchg_sreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmpxchg_4(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEM32(DR_REG_EDX, 1));
    DR_ASSERT(!ub_is_cmpxchg_sreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmpxchg_4(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(ub_is_cmpxchg_sreg_4_sreg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_cmpxchg_sreg_smem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmpxchg_1(drcontext,
            opnd_create_reg(DR_REG_DL), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_cmpxchg_sreg_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmpxchg_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_EDX, 1), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_cmpxchg_sreg_smem_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_cmpxchg_sreg_1_smem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmpxchg_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_EDX, 1), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_cmpxchg_sreg_1_smem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmpxchg_4(drcontext,
            OPND_CREATE_MEM32(DR_REG_EDX, 1), opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_cmpxchg_sreg_1_smem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmpxchg_4(drcontext,
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_cmpxchg_sreg_1_smem_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_instrum_cmpxchg_sreg_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmpxchg_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_EDX, 1), opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_cmpxchg_sreg_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmpxchg_4(drcontext,
            OPND_CREATE_MEM32(DR_REG_EDX, 1), opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_cmpxchg_sreg_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmpxchg_4(drcontext,
            opnd_create_reg(DR_REG_EDX), opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_cmpxchg_sreg_4_smem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_xchg_reg_reg_instr_test();
    ub_is_xchg_reg_1_reg_1_instr_test();
    ub_is_xchg_reg_2_reg_2_instr_test();
    ub_is_xchg_reg_4_reg_4_instr_test();

    ub_is_xchg_mem_reg_instr_test();
    ub_is_xchg_mem_1_reg_1_instr_test();
    ub_is_xchg_mem_2_reg_2_instr_test();
    ub_is_xchg_mem_4_reg_4_instr_test();

    ub_is_xchg_reg_mem_instr_test();
    ub_is_xchg_reg_1_mem_1_instr_test();
    ub_is_xchg_reg_2_mem_2_instr_test();
    ub_is_xchg_reg_4_mem_4_instr_test();

    ub_is_cmpxchg_sreg_sreg_instr_test();
    ub_is_cmpxchg_sreg_1_sreg_1_instr_test();
    ub_is_cmpxchg_sreg_4_sreg_4_instr_test();

    ub_is_cmpxchg_sreg_smem_instr_test();
    ub_is_cmpxchg_sreg_1_smem_1_instr_test();
    ub_instrum_cmpxchg_sreg_4_smem_4_instr_test();
}
