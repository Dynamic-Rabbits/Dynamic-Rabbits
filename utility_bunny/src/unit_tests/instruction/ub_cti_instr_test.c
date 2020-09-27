/*
 * ub_cti_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_cti_instr.h"

static void ub_is_ret_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_ret(drcontext);
    DR_ASSERT(ub_is_ret_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_ret_imm(drcontext,
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(!ub_is_ret_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_ret_imm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_ret(drcontext);
    DR_ASSERT(!ub_is_ret_imm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_ret_imm(drcontext,
            opnd_create_immed_int(1, OPSZ_1));
    DR_ASSERT(ub_is_ret_imm_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_cti_mem_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_jmp_ind(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_cti_mem_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_jmp_ind(drcontext,
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cti_mem_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_call(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(ub_is_cti_mem_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_call(drcontext, opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(!ub_is_cti_mem_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

static void ub_is_cti_reg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_jmp_ind(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cti_reg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_jmp_ind(drcontext,
            opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(ub_is_cti_reg_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_call(drcontext,
            OPND_CREATE_MEMPTR(DR_REG_XAX, 2));
    DR_ASSERT(!ub_is_cti_reg_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_call(drcontext, opnd_create_reg(DR_REG_XAX));
    DR_ASSERT(ub_is_cti_reg_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_ret_instr_test();
    ub_is_ret_imm_instr_test();
    ub_is_cti_mem_instr_test();
    ub_is_cti_reg_instr_test();
}
