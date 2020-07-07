/*
 * dataflow_constant_analysis.c
 *
 *      Author: john
 */

#include "../../dataflow/ub_constant_analysis.h"

static void test1() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    // 0
    instr_t *instr = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    opnd_t dst = instr_get_dst(instr, 1);

    // 1
    instr = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XAX),
            OPND_CREATE_MEM_lea(DR_REG_XCX, DR_REG_NULL, 1, 0));
    instrlist_append(bb, instr);


    // 2
    instr = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    ub_constant_analysis_t analysis = ub_constant_analysis_result(bb);

    uint index = 0;
    instr = instrlist_first_app(bb);
    while (instr) {

        DR_ASSERT(!ub_constant_analysis_instr_uses_mod_addr_regs_via_result(analysis, instr, index));
        instr = instr_get_next_app(instr);
        index++;
    }


    int disp;

    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XSI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XSP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XAX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XDX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XBP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XDI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XBX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XCX, &disp));

    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XSI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XSP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XAX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XDX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XBP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XDI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XBX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XCX, &disp));

    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XSI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XSP, &disp));
    DR_ASSERT(!ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XAX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XDX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XBP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XDI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XBX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XCX, &disp));

    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XSI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XSP, &disp));
    DR_ASSERT(!ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XAX, &disp));
    DR_ASSERT(!ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XDX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XBP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XDI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XBX, &disp));
    DR_ASSERT(!ub_constant_analysis_is_reg_constant_via_result(analysis, 3, DR_REG_XCX, &disp));

    ub_constant_analysis_destroy_result(analysis);

    instrlist_clear_and_destroy(drcontext, bb);
}

static void test2() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_XBX));
    instrlist_append(bb, instr);

    ub_constant_analysis_t analysis = ub_constant_analysis_result(bb);

    int disp;

    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XSI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XSP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XAX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XDX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XBP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XDI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XBX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 0, DR_REG_XCX, &disp));

    DR_ASSERT(!ub_constant_analysis_instr_uses_mod_addr_regs_via_result(analysis, instr, 0));

    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XSI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XSP, &disp));
    DR_ASSERT(!ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XAX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XDX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XBP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XDI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XBX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 1, DR_REG_XCX, &disp));

    DR_ASSERT(!ub_constant_analysis_instr_uses_mod_addr_regs_via_result(analysis, instr, 1));

    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XSI, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XSP, &disp));
    DR_ASSERT(!ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XAX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XDX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XBP, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XDI, &disp));
    DR_ASSERT(!ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XBX, &disp));
    DR_ASSERT(ub_constant_analysis_is_reg_constant_via_result(analysis, 2, DR_REG_XCX, &disp));

    ub_constant_analysis_destroy_result(analysis);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test3() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XAX),
            OPND_CREATE_MEM_lea(DR_REG_XCX, DR_REG_NULL, 1, 0));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_XBX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_mov_ld(drcontext, OPND_CREATE_MEMPTR(DR_REG_XAX, 8),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    ub_constant_analysis_t analysis = ub_constant_analysis_result(bb);

    int index = 0;
    instr = instrlist_first_app(bb);

    while(instr){

        if (ub_constant_analysis_instr_uses_mod_addr_regs_via_result(analysis, instr, index))
            break;

        instr = instr_get_next_app(instr);
        index++;
    }

    dr_fprintf(STDERR, "%d\n", index);
    DR_ASSERT(index == 3);

    ub_constant_analysis_destroy_result(analysis);
    instrlist_clear_and_destroy(drcontext, bb);

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    test1();
    test2();
    test3();
}
