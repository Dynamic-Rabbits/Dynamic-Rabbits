/*
 * ub_comparison_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_comparison_instr.h"

static void ub_is_comparison_smem_smem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_comparison_smem_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_comparison_smem_smem_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_cmp_guard_smem_1_smem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_1_smem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_smem_1_smem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 2), OPND_CREATE_MEM8(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_cmp_smem_1_smem_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_smem_2_smem_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_2_smem_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_smem_2_smem_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 2), OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_cmp_smem_2_smem_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);


}

static void ub_is_cmp_guard_smem_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2),
            OPND_CREATE_MEMPTR(DR_REG_EAX, 2));
    DR_ASSERT(ub_is_cmp_smem_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 2), OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_smem_4_smem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

/**
 * MEM VS REG
 */

static void ub_is_comparison_smem_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_comparison_smem_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(ub_is_comparison_smem_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_cmp_guard_smem_1_sreg_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 2), opnd_create_reg(DR_REG_AL));
    DR_ASSERT(ub_is_cmp_smem_1_sreg_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_smem_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 2), opnd_create_reg(DR_REG_AX));
    DR_ASSERT(ub_is_cmp_smem_2_sreg_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);


}

static void ub_is_cmp_guard_smem_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2), opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_cmp_smem_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 2), opnd_create_reg(DR_REG_AL));
    DR_ASSERT(!ub_is_cmp_smem_4_sreg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

/**
 * REG VS MEM
 */

static void ub_is_comparison_sreg_smem_instr_test() {
    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_comparison_sreg_smem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_comparison_sreg_smem_instr(instr2));

    instr_t *instr3 =
    INSTR_CREATE_ptest(drcontext, opnd_create_reg(DR_REG_XMM0),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_comparison_sreg_smem_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_sreg_1_smem_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_sreg_1_smem_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_1_smem_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AL),
            OPND_CREATE_MEM8(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_cmp_sreg_1_smem_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_sreg_2_smem_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_sreg_2_smem_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_2_smem_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_cmp_sreg_2_smem_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_sreg_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_sreg_4_smem_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_cmp_sreg_4_smem_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_4_smem_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_sreg_16_smem_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_sreg_16_smem_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_16_smem_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_16_smem_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_ptest(drcontext,
            opnd_create_reg(DR_REG_XMM0),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 2, 0, OPSZ_128));
    DR_ASSERT(!ub_is_cmp_sreg_16_smem_16_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

/**
 * REG VS REG
 */

static void ub_is_comparison_sreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(ub_is_comparison_sreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_comparison_sreg_sreg_instr(instr2));

    instr_t *instr3 =
    INSTR_CREATE_ptest(drcontext, opnd_create_reg(DR_REG_XMM0),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_comparison_sreg_sreg_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_sreg_1_sreg_1_instr_test() {
    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AL),
            opnd_create_reg(DR_REG_AL));
    DR_ASSERT(ub_is_cmp_sreg_1_sreg_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_1_sreg_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_1_sreg_1_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_ptest(drcontext,
            opnd_create_reg(DR_REG_XMM0), OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_1_sreg_1_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_cmp_guard_sreg_2_sreg_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            opnd_create_reg(DR_REG_AX));
    DR_ASSERT(ub_is_cmp_sreg_2_sreg_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_2_sreg_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_2_sreg_2_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_ptest(drcontext,
            opnd_create_reg(DR_REG_XMM0), opnd_create_reg(DR_REG_XMM0));
    DR_ASSERT(!ub_is_cmp_sreg_2_sreg_2_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_cmp_guard_sreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(ub_is_cmp_sreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_ptest(drcontext,
            opnd_create_reg(DR_REG_XMM0), opnd_create_reg(DR_REG_XMM0));
    DR_ASSERT(!ub_is_cmp_sreg_4_sreg_4_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_cmp_guard_sreg_16_sreg_16_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            opnd_create_reg(DR_REG_EAX));
    DR_ASSERT(!ub_is_cmp_sreg_16_sreg_16_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_EAX),
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_16_sreg_16_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            OPND_CREATE_MEM16(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cmp_sreg_16_sreg_16_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_ptest(drcontext,
            opnd_create_reg(DR_REG_XMM0), opnd_create_reg(DR_REG_XMM0));
    DR_ASSERT(ub_is_cmp_sreg_16_sreg_16_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

/**
 * REG VS IMM
 */

static void ub_is_comparison_sreg_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_comparison_sreg_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_immed_int(3, OPSZ_4));
    DR_ASSERT(ub_is_comparison_sreg_simm_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_cmp_guard_sreg_1_simm_1_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_sreg_1_simm_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_immed_int(3, OPSZ_4));
    DR_ASSERT(!ub_is_cmp_sreg_1_simm_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AL),
            opnd_create_immed_int(3, OPSZ_1));
    DR_ASSERT(ub_is_cmp_sreg_1_simm_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_cmp_guard_sreg_2_simm_2_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_sreg_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_immed_int(3, OPSZ_4));
    DR_ASSERT(!ub_is_cmp_sreg_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AX),
            opnd_create_immed_int(3, OPSZ_2));
    DR_ASSERT(ub_is_cmp_sreg_2_simm_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_cmp_guard_sreg_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_sreg_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_immed_int(3, OPSZ_4));
    DR_ASSERT(ub_is_cmp_sreg_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_AL),
            opnd_create_immed_int(3, OPSZ_1));
    DR_ASSERT(!ub_is_cmp_sreg_4_simm_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

/**
 * MEM VS IMM
 */

static void ub_is_comparison_smem_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_comparison_smem_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_immed_int(3, OPSZ_4));
    DR_ASSERT(!ub_is_comparison_smem_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 9), opnd_create_immed_int(3, OPSZ_2));
    DR_ASSERT(ub_is_comparison_smem_simm_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_smem_1_simm_1_instr_test() {



    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_1_simm_1_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 9), opnd_create_immed_int(3, OPSZ_2));
    DR_ASSERT(!ub_is_cmp_smem_1_simm_1_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 9), opnd_create_immed_int(3, OPSZ_1));
    DR_ASSERT(ub_is_cmp_smem_1_simm_1_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_smem_2_simm_2_instr_test() {
    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_2_simm_2_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM16(DR_REG_XAX, 9), opnd_create_immed_int(3, OPSZ_2));
    DR_ASSERT(ub_is_cmp_smem_2_simm_2_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 9), opnd_create_immed_int(3, OPSZ_1));
    DR_ASSERT(!ub_is_cmp_smem_2_simm_2_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_cmp_guard_smem_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_cmp(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cmp_smem_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM32(DR_REG_XAX, 9), opnd_create_immed_int(3, OPSZ_4));
    DR_ASSERT(ub_is_cmp_smem_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_cmp(drcontext,
            OPND_CREATE_MEM8(DR_REG_XAX, 9), opnd_create_immed_int(3, OPSZ_1));
    DR_ASSERT(!ub_is_cmp_smem_4_simm_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}


DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_comparison_smem_smem_instr_test();
    ub_is_cmp_guard_smem_1_smem_1_instr_test();
    ub_is_cmp_guard_smem_2_smem_2_instr_test();
    ub_is_cmp_guard_smem_4_smem_4_instr_test();

    /**
     * MEM VS REG
     */

    ub_is_comparison_smem_sreg_instr_test();
    ub_is_cmp_guard_smem_1_sreg_1_instr_test();
    ub_is_cmp_guard_smem_2_sreg_2_instr_test();
    ub_is_cmp_guard_smem_4_sreg_4_instr_test();
    /**
     * REG VS MEM
     */

    ub_is_comparison_sreg_smem_instr_test();
    ub_is_cmp_guard_sreg_1_smem_1_instr_test();
    ub_is_cmp_guard_sreg_2_smem_2_instr_test();
    ub_is_cmp_guard_sreg_4_smem_4_instr_test();
    ub_is_cmp_guard_sreg_16_smem_16_instr_test();

    /**
     * REG VS REG
     */

    ub_is_comparison_sreg_sreg_instr_test();
    ub_is_cmp_guard_sreg_1_sreg_1_instr_test();
    ub_is_cmp_guard_sreg_2_sreg_2_instr_test();
    ub_is_cmp_guard_sreg_4_sreg_4_instr_test();
    ub_is_cmp_guard_sreg_16_sreg_16_instr_test();
    /**
     * REG VS IMM
     */

    ub_is_comparison_sreg_simm_instr_test();
    ub_is_cmp_guard_sreg_1_simm_1_instr_test();
    ub_is_cmp_guard_sreg_2_simm_2_instr_test();
    ub_is_cmp_guard_sreg_4_simm_4_instr_test();
    /**
     * MEM VS IMM
     */

    ub_is_comparison_smem_simm_instr_test();
    ub_is_cmp_guard_smem_1_simm_1_instr_test();
    ub_is_cmp_guard_smem_2_simm_2_instr_test();
    ub_is_cmp_guard_smem_4_simm_4_instr_test();
}
