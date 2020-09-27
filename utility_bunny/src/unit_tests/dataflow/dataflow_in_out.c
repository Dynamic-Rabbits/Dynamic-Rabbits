/*
 * dataflow_in_out.c
 *
 *      Author: john
 */

#include "../../dataflow/ub_in_out_analysis.h"
#include "../../datastructs/lists/ub_list.h"

static void test1() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 0);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test2() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    for (void * it = ub_list_get_start_it(in_out_opnds.in_set.reg_list); it;
            it = ub_list_get_next_it(it)) {

        opnd_t *in = ub_list_get_it_value(it);

        DR_ASSERT(opnd_same(*in, opnd_create_reg(DR_REG_XDX)));
    }

    for (void * it = ub_list_get_start_it(in_out_opnds.out_set.reg_list); it;
            it = ub_list_get_next_it(it)) {

        opnd_t *out = ub_list_get_it_value(it);

        DR_ASSERT(opnd_same(*out, opnd_create_reg(DR_REG_XAX)));
    }

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 2);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test3() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    opnd_t * opnd = ub_list_get_ith_value(in_out_opnds.in_set.reg_list, 0);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XDX)));
    DR_ASSERT(ub_list_get_size(in_out_opnds.in_set.reg_list) == 1);

    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 0);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XAX)));
    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 1);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XDX)));
    DR_ASSERT(ub_list_get_size(in_out_opnds.out_set.reg_list) == 2);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 3);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test4() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XDX),
            opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_add(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    opnd_t * opnd = ub_list_get_ith_value(in_out_opnds.in_set.reg_list, 0);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XDX)));
    opnd = ub_list_get_ith_value(in_out_opnds.in_set.reg_list, 1);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XBX)));
    DR_ASSERT(ub_list_get_size(in_out_opnds.in_set.reg_list) == 2);

    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 0);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XAX)));
    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 1);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XDX)));
    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 2);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XBX)));
    DR_ASSERT(ub_list_get_size(in_out_opnds.out_set.reg_list) == 3);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 5);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test5() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_pop(drcontext, opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 2);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test6() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);

    DR_ASSERT(total == 2);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test7() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    opnd_t dst = instr_get_dst(instr, 1);

    instr = INSTR_CREATE_lea(drcontext, opnd_create_reg(DR_REG_XAX),
            OPND_CREATE_MEM_lea(DR_REG_XCX, DR_REG_NULL, 1, 0));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_xchg(drcontext, opnd_create_reg(DR_REG_XCX),
            opnd_create_reg(DR_REG_XDX));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    opnd_t * opnd = ub_list_get_ith_value(in_out_opnds.in_set.reg_list, 0);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XAX)));

    opnd = ub_list_get_ith_value(in_out_opnds.in_set.reg_list, 1);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XCX)));
    opnd = ub_list_get_ith_value(in_out_opnds.in_set.reg_list, 2);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XDX)));
    DR_ASSERT(ub_list_get_size(in_out_opnds.in_set.reg_list) == 3);

    opnd = ub_list_get_ith_value(in_out_opnds.out_set.mem_base_list, 0);
    DR_ASSERT(opnd_same(*opnd, dst) || opnd_same_address(*opnd, dst));
    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 0);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XAX)));
    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 1);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XCX)));
    opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 2);
    DR_ASSERT(opnd_same(*opnd, opnd_create_reg(DR_REG_XDX)));
    DR_ASSERT(ub_size_in_out_set(&(in_out_opnds.out_set)) == 4);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 7);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test8() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XBX));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XBP),
            opnd_create_reg(DR_REG_XSP));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XDI));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_push(drcontext, opnd_create_reg(DR_REG_XSI));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 8);

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test9() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_BL),
            opnd_create_reg(DR_REG_AL));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XBX),
            opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    size_t total = ub_size_in_out_opnds(&in_out_opnds);
    DR_ASSERT(total == 2);

    opnd_t *xax_opnd = ub_list_get_ith_value(in_out_opnds.in_set.reg_list, 0);
    DR_ASSERT(DR_REG_XAX == opnd_get_reg(*xax_opnd));

    opnd_t *xbx_opnd = ub_list_get_ith_value(in_out_opnds.out_set.reg_list, 0);
    DR_ASSERT(DR_REG_XBX == opnd_get_reg(*xbx_opnd));

    ub_delete_in_out_opnds(&in_out_opnds);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test10() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_movq(drcontext,
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 2,OPSZ_8),
            opnd_create_reg(DR_REG_XMM0));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_movq(drcontext, opnd_create_reg(DR_REG_XMM0),
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 2,OPSZ_8));
    instrlist_append(bb, instr);

    ub_in_out_set_t in_out_set;
    ub_init_in_out_set(&in_out_set);
    ub_get_in_out_set(&in_out_set, bb);

    size_t total = ub_size_in_out_set(&in_out_set);
    DR_ASSERT(total == 2);

    opnd_t *xmm_opnd = ub_list_get_ith_value(in_out_set.reg_list, 0);
    DR_ASSERT(DR_REG_XMM0 == opnd_get_reg(*xmm_opnd));

    total = ub_list_get_size(in_out_set.reg_list);
    DR_ASSERT(total == 1);

    ub_delete_in_out_set(&in_out_set);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test11() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext,
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 2,OPSZ_1),
            opnd_create_reg(DR_REG_AH));
    instrlist_append(bb, instr);

    opnd_t main_mem_opnd = opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 2,
    OPSZ_PTR);

    instr = INSTR_CREATE_mov_st(drcontext, main_mem_opnd,
            opnd_create_reg(DR_REG_XAX));
    instrlist_append(bb, instr);

    ub_in_out_set_t in_out_set;
    ub_init_in_out_set(&in_out_set);
    ub_get_in_out_set(&in_out_set, bb);

    size_t total = ub_size_in_out_set(&in_out_set);
    DR_ASSERT(total == 2);

    total = ub_list_get_size(in_out_set.reg_list);
    DR_ASSERT(total == 1);

    total = ub_list_get_size(in_out_set.mem_base_list);
    DR_ASSERT(total == 1);

    opnd_t *xax_opnd = ub_list_get_ith_value(in_out_set.reg_list, 0);
    DR_ASSERT(DR_REG_XAX == opnd_get_reg(*xax_opnd));

    opnd_t *base_opnd = ub_list_get_ith_value(in_out_set.mem_base_list, 0);
    DR_ASSERT(opnd_same_address(main_mem_opnd, *base_opnd));
    DR_ASSERT(opnd_get_size(main_mem_opnd) == opnd_get_size(*base_opnd));

    ub_delete_in_out_set(&in_out_set);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test12() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext,
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 2,OPSZ_1),
            opnd_create_reg(DR_REG_AH));
    instrlist_append(bb, instr);

    ub_in_out_set_t in_out_set;
    ub_init_in_out_set(&in_out_set);
    ub_get_in_out_set(&in_out_set, bb);

    size_t total = ub_size_in_out_set(&in_out_set);
    DR_ASSERT(total == 2);

    total = ub_list_get_size(in_out_set.reg_list);
    DR_ASSERT(total == 1);

    total = ub_list_get_size(in_out_set.mem_base_list);
    DR_ASSERT(total == 1);

    opnd_t *xax_opnd = ub_list_get_ith_value(in_out_set.reg_list, 0);
    DR_ASSERT(DR_REG_XAX == opnd_get_reg(*xax_opnd));

    opnd_t *base_opnd = ub_list_get_ith_value(in_out_set.mem_base_list, 0);
    DR_ASSERT(OPSZ_1 == opnd_get_size(*base_opnd));

    ub_delete_in_out_set(&in_out_set);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test13() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext,
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 2 ,OPSZ_1),
            opnd_create_reg(DR_REG_AH));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_mov_st(drcontext,
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, 8 ,OPSZ_1),
            opnd_create_reg(DR_REG_AH));
    instrlist_append(bb, instr);

    instr = INSTR_CREATE_mov_st(drcontext,
            opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 0, -2 ,OPSZ_1),
            opnd_create_reg(DR_REG_AH));
    instrlist_append(bb, instr);

    ub_in_out_set_t in_out_set;
    ub_init_in_out_set(&in_out_set);
    ub_get_in_out_set(&in_out_set, bb);

    size_t total = ub_size_in_out_set(&in_out_set);
    DR_ASSERT(total == 4);

    total = ub_list_get_size(in_out_set.reg_list);
    DR_ASSERT(total == 1);

    total = ub_list_get_size(in_out_set.mem_base_list);
    DR_ASSERT(total == 3);

    opnd_t *base_opnd = ub_list_get_ith_value(in_out_set.mem_base_list, 0);
    DR_ASSERT(-2 == opnd_get_disp(*base_opnd));

    base_opnd = ub_list_get_ith_value(in_out_set.mem_base_list, 1);
    DR_ASSERT(2 == opnd_get_disp(*base_opnd));

    base_opnd = ub_list_get_ith_value(in_out_set.mem_base_list, 2);
    DR_ASSERT(8 == opnd_get_disp(*base_opnd));

    ub_delete_in_out_set(&in_out_set);
    instrlist_clear_and_destroy(drcontext, bb);
}

static void test14() {

    void *drcontext = dr_get_current_drcontext();
    instrlist_t *bb = instrlist_create(drcontext);
    instrlist_init(bb);

    instr_t *instr = INSTR_CREATE_pminud(drcontext,
            opnd_create_reg(DR_REG_MM1), opnd_create_reg(DR_REG_MM2));
    instrlist_append(bb, instr);

    ub_in_out_set_t in_out_set;
    ub_init_in_out_set(&in_out_set);
    ub_get_in_out_set(&in_out_set, bb);

    size_t total = ub_size_in_out_set(&in_out_set);
    DR_ASSERT(total == 0);

    ub_delete_in_out_set(&in_out_set);
    instrlist_clear_and_destroy(drcontext, bb);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
}

