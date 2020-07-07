/*
 * ub_srcdst_src_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_srcdst_src_instr.h"

static void ub_is_srcdst_src_dreg_smem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_srcdst_src_dreg_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_smem_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_pand(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XCX,DR_REG_NULL, 0, 1, OPSZ_128));
    DR_ASSERT(ub_is_srcdst_src_dreg_smem_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_1_smem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_smem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_smem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_CL),
            OPND_CREATE_MEM8(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_srcdst_src_dreg_1_smem_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_2_smem_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_smem_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_smem_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_CX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_srcdst_src_dreg_2_smem_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(ub_is_srcdst_src_dreg_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_CX),
            OPND_CREATE_MEM16(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_smem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_16_smem_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_16_smem_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_16_smem_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_pand(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XCX,DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_srcdst_src_dreg_16_smem_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_paddb(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XCX,DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_srcdst_src_dreg_16_smem_16_instr(instr4));


    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_srcdst_src_dreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(ub_is_srcdst_src_dreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_srcdst_src_dreg_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_srcdst_src_dreg_1_sreg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(ub_is_srcdst_src_dreg_2_sreg_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_srcdst_src_dreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_sreg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_16_sreg_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_16_sreg_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XDX),
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1));
    DR_ASSERT(!ub_is_srcdst_src_dreg_16_sreg_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_CX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_16_sreg_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_pand(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XCX,DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_srcdst_src_dreg_16_sreg_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_pand(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(ub_is_srcdst_src_dreg_16_sreg_16_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_srcdst_src_dmem_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(ub_is_srcdst_src_dmem_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_srcdst_src_dmem_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEM8(DR_REG_XCX, 1), opnd_create_reg(DR_REG_DL));
    DR_ASSERT(ub_is_srcdst_src_dmem_1_sreg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dmem_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_reg(DR_REG_DX));
    DR_ASSERT(ub_is_srcdst_src_dmem_2_sreg_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dmem_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(ub_is_srcdst_src_dmem_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_4_sreg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dreg_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dreg_simm_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_srcdst_src_dreg_simm_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ib_is_srcdst_src_dreg_1_simm_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_simm_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_simm_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_simm_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dreg_1_simm_1_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_DH),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_srcdst_src_dreg_1_simm_1_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ib_is_srcdst_src_dreg_2_simm_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_simm_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dreg_2_simm_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(ub_is_srcdst_src_dreg_2_simm_2_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ib_is_srcdst_src_dreg_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1), opnd_create_reg(DR_REG_XDX));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_simm_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_srcdst_src_dreg_4_simm_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(!ub_is_srcdst_src_dreg_4_simm_4_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_srcdst_src_dmem_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_srcdst_src_dmem_simm_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_srcdst_src_dmem_1_simm_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_1_simm_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dmem_1_simm_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEM8(DR_REG_XCX, 1), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_srcdst_src_dmem_1_simm_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dmem_2_simm_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XCX, 1),
            opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(!ub_is_srcdst_src_dmem_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(ub_is_srcdst_src_dmem_2_simm_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_dmem_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_srcdst_src_dmem_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEM32(DR_REG_XCX, 1), opnd_create_immed_int(1, OPSZ_4));
    DR_ASSERT(ub_is_srcdst_src_dmem_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_add(drcontext,
            OPND_CREATE_MEM16(DR_REG_XCX, 1), opnd_create_immed_int(1, OPSZ_2));
    DR_ASSERT(!ub_is_srcdst_src_dmem_4_simm_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_srcdst_src_diff_dreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_sreg_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_sreg_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_srcdst_src_diff_dreg_sreg_instr(instr4));


    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_srcdst_src_diff_dreg_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_1_sreg_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(ub_is_srcdst_src_diff_dreg_1_sreg_1_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_1_sreg_1_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_srcdst_src_diff_dreg_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_AX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(ub_is_srcdst_src_diff_dreg_2_sreg_2_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_srcdst_src_diff_dreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_srcdst_src_diff_dreg_4_sreg_4_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_srcdst_src_diff_dreg_16_sreg_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_pxor(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_pxor(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(!ub_is_srcdst_src_diff_dreg_16_sreg_16_instr(instr8));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
}

static void ub_is_srcdst_src_same_dreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(ub_is_srcdst_src_same_dreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(ub_is_srcdst_src_same_dreg_sreg_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_sreg_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_sreg_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_srcdst_src_same_dreg_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_1_sreg_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_1_sreg_1_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(ub_is_srcdst_src_same_dreg_1_sreg_1_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_srcdst_src_same_dreg_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_AX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_2_sreg_2_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);

}

static void ub_is_srcdst_src_same_dreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_4_sreg_4_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_srcdst_src_same_dreg_16_sreg_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_EDX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_reg(DR_REG_DX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_EDX),
            OPND_CREATE_MEM32(DR_REG_EDX, 2));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_AH));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_xor(drcontext, opnd_create_reg(DR_REG_DL),
            opnd_create_reg(DR_REG_DL));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_pxor(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_pxor(drcontext, opnd_create_reg(DR_REG_XMM1),
            opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(ub_is_srcdst_src_same_dreg_16_sreg_16_instr(instr8));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_srcdst_src_dreg_smem_instr_test();

    ub_is_srcdst_src_dreg_1_smem_1_instr_test();
    ub_is_srcdst_src_dreg_2_smem_2_instr_test();
    ub_is_srcdst_src_dreg_4_smem_4_instr_test();
    ub_is_srcdst_src_dreg_16_smem_16_instr_test();

    ub_is_srcdst_src_dreg_sreg_instr_test();

    ub_is_srcdst_src_dreg_1_sreg_1_instr_test();
    ub_is_srcdst_src_dreg_2_sreg_2_instr_test();
    ub_is_srcdst_src_dreg_4_sreg_4_instr_test();
    ub_is_srcdst_src_dreg_16_sreg_16_instr_test();

    ub_is_srcdst_src_dmem_sreg_instr_test();

    ub_is_srcdst_src_dmem_1_sreg_1_instr_test();
    ub_is_srcdst_src_dmem_2_sreg_2_instr_test();
    ub_is_srcdst_src_dmem_4_sreg_4_instr_test();

    ub_is_srcdst_src_dreg_simm_instr_test();

    ib_is_srcdst_src_dreg_1_simm_1_instr_test();
    ib_is_srcdst_src_dreg_2_simm_2_instr_test();
    ib_is_srcdst_src_dreg_4_simm_4_instr_test();

    ub_is_srcdst_src_dmem_simm_instr_test();

    ub_is_srcdst_src_dmem_1_simm_1_instr_test();
    ub_is_srcdst_src_dmem_2_simm_2_instr_test();
    ub_is_srcdst_src_dmem_4_simm_4_instr_test();

    ub_is_srcdst_src_diff_dreg_sreg_instr_test();
    ub_is_srcdst_src_diff_dreg_1_sreg_1_instr_test();
    ub_is_srcdst_src_diff_dreg_2_sreg_2_instr_test();
    ub_is_srcdst_src_diff_dreg_4_sreg_4_instr_test();
    ub_is_srcdst_src_diff_dreg_16_sreg_16_instr_test();

    ub_is_srcdst_src_same_dreg_sreg_instr_test();
    ub_is_srcdst_src_same_dreg_1_sreg_1_instr_test();
    ub_is_srcdst_src_same_dreg_2_sreg_2_instr_test();
    ub_is_srcdst_src_same_dreg_4_sreg_4_instr_test();
    ub_is_srcdst_src_same_dreg_16_sreg_16_instr_test();

}
