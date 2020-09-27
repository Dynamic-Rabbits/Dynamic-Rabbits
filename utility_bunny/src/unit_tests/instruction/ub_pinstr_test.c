/*
 * ub_pinstr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_pinstr.h"

/**
 * PEXT
 */

static void ub_is_pext_dreg_sreg_sreg_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XBX));
    DR_ASSERT(ub_is_pext_dreg_sreg_sreg(instr1));

    instr_t *instr2 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XBX, 1));
    DR_ASSERT(!ub_is_pext_dreg_sreg_sreg(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_pext_dreg_4_sreg_4_sreg_4_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX), opnd_create_reg(DR_REG_EBX));
    DR_ASSERT(ub_is_pext_dreg_4_sreg_4_sreg_4(instr1));

    instr_t *instr2 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX), OPND_CREATE_MEM32(DR_REG_XBX, 1));
    DR_ASSERT(!ub_is_pext_dreg_4_sreg_4_sreg_4(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_pext_dreg_sreg_smem_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX), opnd_create_reg(DR_REG_XBX));
    DR_ASSERT(!ub_is_pext_dreg_sreg_smem(instr1));

    instr_t *instr2 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX), OPND_CREATE_MEMPTR(DR_REG_XBX, 1));
    DR_ASSERT(ub_is_pext_dreg_sreg_smem(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_pext_dreg_4_sreg_4_smem_4_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX), opnd_create_reg(DR_REG_EBX));
    DR_ASSERT(!ub_is_pext_dreg_4_sreg_4_smem_4(instr1));

    instr_t *instr2 = INSTR_CREATE_pext(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX), OPND_CREATE_MEM32(DR_REG_XBX, 1));
    DR_ASSERT(ub_is_pext_dreg_4_sreg_4_smem_4(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_pextr_dmem_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pextrb(drcontext,
            OPND_CREATE_MEM8(DR_REG_XBX, 1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_pextr_dmem_1_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_pextrb(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_reg(DR_REG_XMM2), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pextr_dmem_1_sreg_16(instr2));

    instr_t *instr3 = INSTR_CREATE_pextrw(drcontext,
            OPND_CREATE_MEM16(DR_REG_XBX, 1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pextr_dmem_1_sreg_16(instr3));

    instr_t *instr4 = INSTR_CREATE_pextrw(drcontext, opnd_create_reg(DR_REG_BX),
            opnd_create_reg(DR_REG_XMM2), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pextr_dmem_1_sreg_16(instr4));

    instr_t *instr5 = INSTR_CREATE_pextrd(drcontext,
            OPND_CREATE_MEM32(DR_REG_XBX, 1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_pextr_dmem_4_sreg_16(instr5));

    instr_t *instr6 = INSTR_CREATE_pextrd(drcontext,
            opnd_create_reg(DR_REG_EBX), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pextr_dmem_4_sreg_16(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_pextr_dreg_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pextrb(drcontext,
            OPND_CREATE_MEM8(DR_REG_XBX, 1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pextr_dreg_4_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_pextrb(drcontext, opnd_create_reg(DR_REG_EBX),
            opnd_create_reg(DR_REG_XMM2), opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_pextr_dreg_4_sreg_16(instr2));

    instr_t *instr3 = INSTR_CREATE_pextrw(drcontext,
            OPND_CREATE_MEM16(DR_REG_XBX, 1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pextr_dreg_4_sreg_16(instr3));

    instr_t *instr4 = INSTR_CREATE_pextrd(drcontext,
            OPND_CREATE_MEM32(DR_REG_XBX, 1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pextr_dreg_4_sreg_16(instr4));


    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

/**
 * PMINMAXU
 */

static void ub_is_pminmax_dreg_smem_sreg_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_smem(instr1));

    instr_t *instr2 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_pminmax_dreg_smem(instr2));

    instr_t *instr3 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_smem(instr3));

    instr_t *instr4 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_pminmax_dreg_smem(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_pminmax_dreg_sreg_sreg_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_pminmax_dreg_sreg(instr1));

    instr_t *instr2 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_sreg(instr2));

    instr_t *instr3 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_pminmax_dreg_sreg(instr3));

    instr_t *instr4 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_sreg(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_pminmax_dreg_8_sreg_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_8_sreg_8(instr1));

    instr_t *instr2 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_8_sreg_8(instr2));

    instr_t *instr3 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_8_sreg_8(instr3));

    instr_t *instr4 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_8_sreg_8(instr4));

    instr_t *instr5 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_MM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_pminmax_dreg_8_sreg_8(instr5));

    instr_t *instr6 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_MM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_pminmax_dreg_8_sreg_8(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_pminmax_dreg_8_smem_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_8_smem_8(instr1));

    instr_t *instr2 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_8_smem_8(instr2));

    instr_t *instr3 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_8_smem_8(instr3));

    instr_t *instr4 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_8_smem_8(instr4));

    instr_t *instr5 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pminmax_dreg_8_smem_8(instr5));

    instr_t *instr6 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pminmax_dreg_8_smem_8(instr6));

    instr_t *instr7 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_MM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_pminmax_dreg_8_smem_8(instr7));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);

}

static void ub_is_pminmax_dreg_16_sreg_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_pminmax_dreg_16_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_16_sreg_16(instr2));

    instr_t *instr3 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_pminmax_dreg_16_sreg_16(instr3));

    instr_t *instr4 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_pminmax_dreg_16_sreg_16(instr4));

    instr_t *instr5 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pminmax_dreg_16_sreg_16(instr5));

    instr_t *instr6 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pminmax_dreg_16_sreg_16(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

static void ub_is_pminmax_dreg_16_smem_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_16_smem_16(instr1));

    instr_t *instr2 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_pminmax_dreg_16_smem_16(instr2));

    instr_t *instr3 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pminmax_dreg_16_smem_16(instr3));

    instr_t *instr4 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_XMM2),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_pminmax_dreg_16_smem_16(instr4));

    instr_t *instr5 = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pminmax_dreg_16_smem_16(instr5));

    instr_t *instr6 = INSTR_CREATE_pminsw(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pminmax_dreg_16_smem_16(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
}

/**
 * PMOVMSK
 */

static void ub_is_pmovmsk_dreg_4_sreg_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pmovmskb(drcontext,
            opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_pmovmsk_dreg_4_sreg_8(instr1));

    instr_t *instr2 = INSTR_CREATE_pmovmskb(drcontext,
            opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pmovmsk_dreg_4_sreg_8(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_pmovmsk_dreg_4_sreg_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pmovmskb(drcontext,
            opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_pmovmsk_dreg_4_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_pmovmskb(drcontext,
            opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_pmovmsk_dreg_4_sreg_16(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

/**
 * PACKSS
 */

static void ub_is_packss_dreg_8_sreg_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_packss_dreg_8_sreg_8(instr1));

    instr_t *instr2 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_packss_dreg_8_sreg_8(instr2));

    instr_t *instr3 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_packss_dreg_8_sreg_8(instr3));

    instr_t *instr4 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_packss_dreg_8_sreg_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_packss_dreg_16_sreg_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_packss_dreg_16_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_packss_dreg_16_sreg_16(instr2));

    instr_t *instr3 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_packss_dreg_16_sreg_16(instr3));

    instr_t *instr4 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_packss_dreg_16_sreg_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_packss_dreg_8_smem_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_packss_dreg_8_smem_8(instr1));

    instr_t *instr2 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_packss_dreg_8_smem_8(instr2));

    instr_t *instr3 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_packss_dreg_8_smem_8(instr3));

    instr_t *instr4 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_packss_dreg_8_smem_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_packss_dreg_16_smem_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_packss_dreg_16_smem_16(instr1));

    instr_t *instr2 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_packss_dreg_16_smem_16(instr2));

    instr_t *instr3 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_packss_dreg_16_smem_16(instr3));

    instr_t *instr4 = INSTR_CREATE_packssdw(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_packss_dreg_16_smem_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

/**
 * PALIGNR
 */

static void ub_is_palignr_dreg_8_sreg_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_sreg_8(instr1));

    instr_t *instr2 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_sreg_8(instr2));

    instr_t *instr3 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_sreg_8(instr3));

    instr_t *instr4 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_sreg_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_palignr_dreg_8_smem_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_smem_8(instr1));

    instr_t *instr2 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_smem_8(instr2));

    instr_t *instr3 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_smem_8(instr3));

    instr_t *instr4 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_8_smem_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_palignr_dreg_16_sreg_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_16_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_16_sreg_16(instr2));

    instr_t *instr3 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_palignr_dreg_16_sreg_16(instr3));

    instr_t *instr4 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_16_sreg_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_palignr_dreg_16_smem_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_palignr_dreg_16_smem_16(instr1));

    instr_t *instr2 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_16_smem_16(instr2));

    instr_t *instr3 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_16_smem_16(instr3));

    instr_t *instr4 = INSTR_CREATE_palignr(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_palignr_dreg_16_smem_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

/**
 * PSHUFH/D
 */

static void ub_is_pshuf_dreg_8_sreg_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_sreg_8(instr1));

    instr_t *instr2 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_sreg_8(instr2));

    instr_t *instr3 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_sreg_8(instr3));

    instr_t *instr4 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_sreg_8(instr4));

    instr_t *instr5 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_sreg_16(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_pshuf_dreg_16_sreg_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(ub_is_pshuf_dreg_16_sreg_16(instr2));

    instr_t *instr3 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_sreg_16(instr3));

    instr_t *instr4 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_pshuf_dreg_16_sreg_16(instr4));

    instr_t *instr5 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_sreg_16(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_is_pshuf_dreg_8_smem_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_smem_8(instr1));

    instr_t *instr2 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_smem_8(instr2));

    instr_t *instr3 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_smem_8(instr3));

    instr_t *instr4 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_smem_8(instr4));

    instr_t *instr5 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_8_smem_8(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

static void ub_is_pshuf_dreg_16_smem_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_pshuf_dreg_16_smem_16(instr1));

    instr_t *instr2 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_smem_16(instr2));

    instr_t *instr3 = INSTR_CREATE_pshufb(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_smem_16(instr3));

    instr_t *instr4 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM1),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_smem_16(instr4));

    instr_t *instr5 = INSTR_CREATE_pshufd(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8),
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_pshuf_dreg_16_smem_16(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
}

/**
 * PUNPCK
 */

static void ub_is_punpck_dreg_8_sreg_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_punpck_dreg_8_sreg_8(instr1));

    instr_t *instr2 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_punpck_dreg_8_sreg_8(instr2));

    instr_t *instr3 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_punpck_dreg_8_sreg_8(instr3));

    instr_t *instr4 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_punpck_dreg_8_sreg_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_punpck_dreg_16_sreg_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_punpck_dreg_16_sreg_16(instr1));

    instr_t *instr2 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_punpck_dreg_16_sreg_16(instr2));

    instr_t *instr3 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_punpck_dreg_16_sreg_16(instr3));

    instr_t *instr4 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(ub_is_punpck_dreg_16_sreg_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_punpck_dreg_8_smem_8_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(!ub_is_punpck_dreg_8_smem_8(instr1));

    instr_t *instr2 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_punpck_dreg_8_smem_8(instr2));

    instr_t *instr3 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_punpck_dreg_8_smem_8(instr3));

    instr_t *instr4 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_punpck_dreg_8_smem_8(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_punpck_dreg_16_smem_16_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_16));
    DR_ASSERT(ub_is_punpck_dreg_16_smem_16(instr1));

    instr_t *instr2 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1),
            opnd_create_base_disp(DR_REG_XBX, DR_REG_NULL, 0, 1, OPSZ_8));
    DR_ASSERT(!ub_is_punpck_dreg_16_smem_16(instr2));

    instr_t *instr3 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    DR_ASSERT(!ub_is_punpck_dreg_16_smem_16(instr3));

    instr_t *instr4 = INSTR_CREATE_punpckhdq(drcontext,
            opnd_create_reg(DR_REG_XMM1), opnd_create_reg(DR_REG_XMM2));
    DR_ASSERT(!ub_is_punpck_dreg_16_smem_16(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    /**
     * PEXT
     */

    ub_is_pext_dreg_sreg_sreg_test();
    ub_is_pext_dreg_4_sreg_4_sreg_4_test();

    ub_is_pext_dreg_sreg_smem_test();
    ub_is_pext_dreg_4_sreg_4_smem_4_test();

    ub_is_pextr_dmem_test();
    ub_is_pextr_dreg_test();

    /**
     * PMINMAXU
     */

    ub_is_pminmax_dreg_smem_sreg_test();
    ub_is_pminmax_dreg_sreg_sreg_test();

    ub_is_pminmax_dreg_8_sreg_8_test();
    ub_is_pminmax_dreg_8_smem_8_test();

    ub_is_pminmax_dreg_16_sreg_16_test();
    ub_is_pminmax_dreg_16_smem_16_test();

    /**
     * PMOVMSK
     */

    ub_is_pmovmsk_dreg_4_sreg_8_test();
    ub_is_pmovmsk_dreg_4_sreg_16_test();

    /**
     * PACKSS
     */

    ub_is_packss_dreg_8_sreg_8_test();
    ub_is_packss_dreg_16_sreg_16_test();
    ub_is_packss_dreg_8_smem_8_test();
    ub_is_packss_dreg_16_smem_16_test();

    /**
     * PALIGNR
     */

    ub_is_palignr_dreg_8_sreg_8_test();
    ub_is_palignr_dreg_8_smem_8_test();

    ub_is_palignr_dreg_16_sreg_16_test();
    ub_is_palignr_dreg_16_smem_16_test();

    /**
     * PSHUFH/D
     */

    ub_is_pshuf_dreg_8_sreg_8_test();
    ub_is_pshuf_dreg_16_sreg_16_test();

    ub_is_pshuf_dreg_8_smem_8_test();
    ub_is_pshuf_dreg_16_smem_16_test();

    /**
     * PUNPCK
     */

    ub_is_punpck_dreg_8_sreg_8_test();
    ub_is_punpck_dreg_16_sreg_16_test();

    ub_is_punpck_dreg_8_smem_8_test();
    ub_is_punpck_dreg_16_smem_16_test();

}
