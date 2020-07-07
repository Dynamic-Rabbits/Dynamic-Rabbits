/*
 * ub_ptr_arith_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_ptr_arith_instr.h"

static void ub_is_lea_dreg_sreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(ub_is_lea_dreg_sreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_dreg_sreg_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_lea_dreg_4_sreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(ub_is_lea_dreg_4_sreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_dreg_4_sreg_4_sreg_4_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_lea_base_dreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_base_dreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(ub_is_lea_base_dreg_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_instrum_lea_base_dreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_base_dreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_base_dreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_base_disp(DR_REG_EDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(ub_is_lea_base_dreg_4_sreg_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

static void ub_is_lea_index_dreg_sreg_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_index_dreg_sreg_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_index_dreg_sreg_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_lea_index_dreg_4_sreg_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_index_dreg_4_sreg_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_index_dreg_4_sreg_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_NULL, DR_REG_XDX, 1, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_index_dreg_4_sreg_4_instr(instr3));

    instr_t *instr4 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_base_disp(DR_REG_NULL, DR_REG_XDX, 1, 1, OPSZ_lea));
    DR_ASSERT(ub_is_lea_index_dreg_4_sreg_4_instr(instr4));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
    instr_destroy(drcontext, instr4);
}

static void ub_is_lea_index_dreg_simm_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_dreg_simm_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_dreg_simm_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_NULL, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(ub_is_lea_dreg_simm_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);
}

static void ub_is_lea_index_dreg_4_simm_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_XCX, 1, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_dreg_4_simm_4_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_DX),
            opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(!ub_is_lea_dreg_4_simm_4_instr(instr2));

    instr_t *instr3 = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_EDX),
            opnd_create_base_disp(DR_REG_NULL, DR_REG_NULL, 0, 1, OPSZ_lea));
    DR_ASSERT(ub_is_lea_dreg_4_simm_4_instr(instr3));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
    instr_destroy(drcontext, instr3);

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_lea_dreg_sreg_sreg_instr_test();
    ub_is_lea_dreg_4_sreg_4_sreg_4_instr_test();

    ub_is_lea_base_dreg_sreg_instr_test();
    ub_instrum_lea_base_dreg_4_sreg_4_instr_test();

    ub_is_lea_index_dreg_sreg_instr_test();
    ub_is_lea_index_dreg_4_sreg_4_instr_test();

    ub_is_lea_index_dreg_simm_instr_test();
    ub_is_lea_index_dreg_4_simm_4_instr_test();
}
