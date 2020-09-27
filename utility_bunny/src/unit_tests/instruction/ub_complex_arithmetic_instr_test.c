/*
 * ub_complex_arithmetic_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_complex_arithmetic_instr.h"

/*********************************************************
 * MUL 4 Instruction
 */

static void ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr(instr7));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
}

static void ub_instrum_mult_dreg_4_dreg_4_smem_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_mult_dreg_4_dreg_4_smem_4_sreg_4_instr(instr8));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
}

/*********************************************************
 * MUL 1 Instruction
 */

static void ub_is_mult_dreg_2_sreg_1_sreg_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_1_sreg_1(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_mult_dreg_2_sreg_1_sreg_1(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_1_sreg_1(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_1_sreg_1(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(ub_is_mult_dreg_2_sreg_1_sreg_1(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_1_sreg_1(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_1_sreg_1(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_1_sreg_1(instr8));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);

}

static void ub_is_mult_dreg_2_smem_1_sreg_1_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_1_sreg_1(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_1_sreg_1(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_1_sreg_1(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_1_sreg_1(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_1_sreg_1(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_1_sreg_1(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_mult_dreg_2_smem_1_sreg_1(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_mult_dreg_2_smem_1_sreg_1(instr8));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
}

/*********************************************************
 * IMUL DST SRC Instruction
 */

static void ub_is_mult_dreg_sreg_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(ub_is_mult_dreg_sreg_simm_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr8));

    instr_t *instr9 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEMPTR(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_sreg_simm_instr(instr9));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
    instr_destroy(drcontext, instr9);
}

static void ub_is_mult_dreg_2_sreg_2_simm_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr8));

    instr_t *instr9 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEMPTR(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr9));

    instr_t *instr10 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_CX), opnd_create_reg(DR_REG_AX),
            opnd_create_immed_int(8, OPSZ_2));
    DR_ASSERT(ub_is_mult_dreg_2_sreg_2_simm_2_instr(instr10));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
    instr_destroy(drcontext, instr9);
    instr_destroy(drcontext, instr10);
}

static void ub_is_mult_dreg_4_sreg_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr8));

    instr_t *instr9 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEMPTR(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr9));

    instr_t *instr10 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_CX), opnd_create_reg(DR_REG_AX),
            opnd_create_immed_int(8, OPSZ_2));
    DR_ASSERT(!ub_is_mult_dreg_4_sreg_4_simm_4_instr(instr10));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
    instr_destroy(drcontext, instr9);
    instr_destroy(drcontext, instr10);

}

static void ub_is_mult_dreg_smem_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_smem_simm_instr(instr8));

    instr_t *instr9 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEMPTR(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(ub_is_mult_dreg_smem_simm_instr(instr9));

    instr_t *instr10 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_CX), OPND_CREATE_MEM16(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_2));
    DR_ASSERT(ub_is_mult_dreg_smem_simm_instr(instr10));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
    instr_destroy(drcontext, instr9);
    instr_destroy(drcontext, instr10);
}

static void ub_is_mult_dreg_2_smem_2_simm_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr8));

    instr_t *instr9 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEMPTR(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_2_smem_2_simm_2_instr(instr9));

    instr_t *instr10 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_CX), OPND_CREATE_MEM16(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_2));
    DR_ASSERT(ub_is_mult_dreg_2_smem_2_simm_2_instr(instr10));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
    instr_destroy(drcontext, instr9);
    instr_destroy(drcontext, instr10);

}

static void ub_is_mult_dreg_4_smem_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_imul(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_imul_1(drcontext,
            opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_imul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), opnd_create_reg(DR_REG_EAX),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_mul_1(drcontext, opnd_create_reg(DR_REG_CL));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_mul_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr6));

    instr_t *instr7 = INSTR_CREATE_mul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr7));

    instr_t *instr8 = INSTR_CREATE_imul_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_mult_dreg_4_smem_4_simm_4_instr(instr8));

    instr_t *instr9 = INSTR_CREATE_imul_imm(drcontext,
            opnd_create_reg(DR_REG_ECX), OPND_CREATE_MEMPTR(DR_REG_EAX, 1),
            opnd_create_immed_int(8, OPSZ_4));
    DR_ASSERT(ub_is_mult_dreg_4_smem_4_simm_4_instr(instr9));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);
    instr_destroy(drcontext, instr7);
    instr_destroy(drcontext, instr8);
    instr_destroy(drcontext, instr9);
}

/*********************************************************
 * DIV 4 Instruction
 */

static void ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_div_1(drcontext, opnd_create_reg(DR_REG_CH));
    DR_ASSERT(!ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_div_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_div_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_idiv_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_idiv_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(instr5));

    instr_t *instr6 = INSTR_CREATE_div_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr(instr6));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);
    instr_destroy(drcontext, instr6);

}

static void ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_div_1(drcontext, opnd_create_reg(DR_REG_CH));
    DR_ASSERT(!ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_div_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_div_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_idiv_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_idiv_4(drcontext,
            opnd_create_reg(DR_REG_ECX));
    DR_ASSERT(!ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr(instr5));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

/*********************************************************
 * DIV 1 Instruction
 */

static void ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_div_1(drcontext, opnd_create_reg(DR_REG_CH));
    DR_ASSERT(!ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_div_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_div_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_idiv_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr(instr4));

    instr_t *instr5 = INSTR_CREATE_idiv_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr(instr5));


    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
    instr_destroy(drcontext, instr5);

}

static void ub_div_dreg_1_dreg_1_sreg_1_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_div_1(drcontext, opnd_create_reg(DR_REG_CH));
    DR_ASSERT(ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_div_1(drcontext,
            OPND_CREATE_MEM8(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_div_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_div_4(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_ECX, 2));
    DR_ASSERT(!ub_is_div_dreg_1_dreg_1_sreg_1_sreg_2_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_mult_dreg_4_dreg_4_sreg_4_sreg_4_instr_test();
    ub_instrum_mult_dreg_4_dreg_4_smem_4_sreg_4_instr_test();

    ub_is_mult_dreg_2_sreg_1_sreg_1_test();
    ub_is_mult_dreg_2_smem_1_sreg_1_test();

    ub_is_mult_dreg_sreg_simm_instr_test();
    ub_is_mult_dreg_2_sreg_2_simm_2_instr_test();
    ub_is_mult_dreg_4_sreg_4_simm_4_instr_test();

    ub_is_mult_dreg_smem_simm_instr_test();
    ub_is_mult_dreg_2_smem_2_simm_2_instr_test();
    ub_is_mult_dreg_4_smem_4_simm_4_instr_test();

    ub_is_div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_instr_test();
    ub_is_div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_instr_test();

    ub_is_div_dreg_1_dreg_1_smem_1_sreg_2_instr_test();
    ub_div_dreg_1_dreg_1_sreg_1_sreg_2_instr_test();
}
