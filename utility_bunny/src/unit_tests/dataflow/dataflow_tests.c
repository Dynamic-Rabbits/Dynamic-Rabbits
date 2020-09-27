#include "dr_api.h"
#include "drmgr.h"
#include "../../utility_bunny.h"

static void test_aaa() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr = INSTR_CREATE_aaa(drcontext);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(!ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == instr_num_dsts(instr));

    instr_destroy(drcontext, instr);
}

static void test_label() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t dst_opnd = opnd_create_reg(DR_REG_XAX);
    opnd_t src_opnd = opnd_create_reg(DR_REG_XDX);

    instr_t *instr = INSTR_CREATE_label(drcontext);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 0);

    instr_destroy(drcontext, instr);

}

static void test_pop() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t dst_opnd = opnd_create_reg(DR_REG_XAX);

    instr_t *instr = INSTR_CREATE_pop(drcontext, dst_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 1);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, dst_opnd));

    instr_destroy(drcontext, instr);

}

static void test_push() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t src_opnd = opnd_create_reg(DR_REG_XAX);

    instr_t *instr = INSTR_CREATE_push(drcontext, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 1);

    opnd_t src_opnd_test = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test, src_opnd));

    instr_destroy(drcontext, instr);
}

static void test_mov() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t dst_opnd = opnd_create_reg(DR_REG_XAX);
    opnd_t src_opnd = opnd_create_reg(DR_REG_XDX);

    instr_t *instr = INSTR_CREATE_mov_st(drcontext, dst_opnd, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 1);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, dst_opnd));

    opnd_t src_opnd_test = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test, src_opnd));

    instr_destroy(drcontext, instr);
}

static void test_add() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t srcdst_opnd = opnd_create_reg(DR_REG_XAX);
    opnd_t src_opnd = opnd_create_reg(DR_REG_XDX);

    instr_t *instr = INSTR_CREATE_add(drcontext, srcdst_opnd, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 2);

    opnd_t srcdst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(srcdst_opnd_test, srcdst_opnd));

    opnd_t src_opnd_test = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(
            opnd_same(src_opnd_test, src_opnd)
                    || opnd_same(src_opnd_test, srcdst_opnd_test));

    opnd_t src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 1);
    DR_ASSERT(
            opnd_same(src_opnd_test2, src_opnd)
                    || opnd_same(src_opnd_test2, srcdst_opnd));

    DR_ASSERT(!opnd_same(src_opnd_test2, src_opnd_test));

    instr_destroy(drcontext, instr);
}

static void test_bswap() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t src_opnd = opnd_create_reg(DR_REG_XDX);

    instr_t *instr = INSTR_CREATE_bswap(drcontext, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 1);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, src_opnd));

    opnd_t src_opnd_test = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test, src_opnd));

    instr_destroy(drcontext, instr);
}

static void test_xchg() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t srcdst_opnd = opnd_create_reg(DR_REG_XAX);
    opnd_t srcdst2_opnd = opnd_create_reg(DR_REG_XDX);

    instr_t *instr = INSTR_CREATE_xchg(drcontext, srcdst_opnd, srcdst2_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 2);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 1);
    DR_ASSERT(size == 1);

    opnd_t srcdst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(srcdst_opnd_test, srcdst_opnd));

    opnd_t srcdst_opnd_test2 = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 1);
    DR_ASSERT(opnd_same(srcdst_opnd_test2, srcdst2_opnd));

    opnd_t src_opnd_test = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test, srcdst2_opnd));

    opnd_t src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 0);
    DR_ASSERT(opnd_same(src_opnd_test2, srcdst_opnd));

    instr_destroy(drcontext, instr);
}

static void test_lea() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t dst_opnd = opnd_create_reg(DR_REG_XAX);
    opnd_t src_opnd = OPND_CREATE_MEM_lea(DR_REG_XAX, DR_REG_XDI, 1, 0);

    instr_t *instr = INSTR_CREATE_lea(drcontext, dst_opnd, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 2);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, dst_opnd));

    opnd_t src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, opnd_create_reg(DR_REG_XAX)));

    opnd_t src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 1);
    DR_ASSERT(opnd_same(src_opnd_test2, opnd_create_reg(DR_REG_XDI)));

    instr_destroy(drcontext, instr);
}

static void test_lea_base() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t dst_opnd = opnd_create_reg(DR_REG_XAX);
    opnd_t src_opnd = OPND_CREATE_MEM_lea(DR_REG_XAX, DR_REG_NULL, 1, 0);

    instr_t *instr = INSTR_CREATE_lea(drcontext, dst_opnd, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 1);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, dst_opnd));

    opnd_t src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, opnd_create_reg(DR_REG_XAX)));

    instr_destroy(drcontext, instr);
}

static void test_lea_index() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t dst_opnd = opnd_create_reg(DR_REG_XAX);
    opnd_t src_opnd = OPND_CREATE_MEM_lea(DR_REG_NULL, DR_REG_XAX, 1, 0);

    instr_t *instr = INSTR_CREATE_lea(drcontext, dst_opnd, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 1);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 1);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, dst_opnd));

    opnd_t src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, opnd_create_reg(DR_REG_XAX)));

    instr_destroy(drcontext, instr);
}

static void test_div() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t src_opnd = opnd_create_reg(DR_REG_XDI);

    instr_t *instr = INSTR_CREATE_div_4(drcontext, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);

    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 2);

    size = ub_dataflow_flow_num_srcs(&dataflow_instr, 0);
    DR_ASSERT(size == 3);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, opnd_create_reg(DR_REG_XDX)));

    opnd_t src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, src_opnd));
    opnd_t src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 1);
    DR_ASSERT(opnd_same(src_opnd_test2, opnd_create_reg(DR_REG_XDX)));
    opnd_t src_opnd_test3 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 2);
    DR_ASSERT(opnd_same(src_opnd_test3, opnd_create_reg(DR_REG_XAX)));

    opnd_t dst_opnd_test2 = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 1);
    DR_ASSERT(opnd_same(dst_opnd_test2, opnd_create_reg(DR_REG_XAX)));

    src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, src_opnd));
    src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 1);
    DR_ASSERT(opnd_same(src_opnd_test2, opnd_create_reg(DR_REG_XDX)));
    src_opnd_test3 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 2);
    DR_ASSERT(opnd_same(src_opnd_test3, opnd_create_reg(DR_REG_XAX)));

    instr_destroy(drcontext, instr);
}

static void test_mul() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t src_opnd = opnd_create_reg(DR_REG_XDI);
    instr_t *instr = INSTR_CREATE_mul_4(drcontext, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);
    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 2);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 1);
    DR_ASSERT(opnd_same(dst_opnd_test, opnd_create_reg(DR_REG_XAX)));

    opnd_t src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, src_opnd));

    opnd_t src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 1);
    DR_ASSERT(opnd_same(src_opnd_test2, opnd_create_reg(DR_REG_XAX)));

    dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, opnd_create_reg(DR_REG_XDX)));

    src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, src_opnd));
    src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 1);
    DR_ASSERT(opnd_same(src_opnd_test2, opnd_create_reg(DR_REG_XAX)));

    instr_destroy(drcontext, instr);

}

static void test_imul() {

    void *drcontext = dr_get_current_drcontext();

    opnd_t src_opnd = opnd_create_reg(DR_REG_XDI);
    instr_t *instr = INSTR_CREATE_imul_4(drcontext, src_opnd);
    ub_instr_dataflow_t dataflow_instr;
    ub_dataflow_get_info(instr, &dataflow_instr);
    DR_ASSERT(ub_dataflow_is_supported(&dataflow_instr));

    size_t size = ub_dataflow_num_flows(&dataflow_instr);
    DR_ASSERT(size == 2);

    opnd_t dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 1);
    DR_ASSERT(opnd_same(dst_opnd_test, opnd_create_reg(DR_REG_XAX)));
    opnd_t src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, src_opnd));
    opnd_t src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 0, 1);
    DR_ASSERT(opnd_same(src_opnd_test2, opnd_create_reg(DR_REG_XAX)));

    dst_opnd_test = ub_dataflow_get_flow_dst(instr, &dataflow_instr, 0);
    DR_ASSERT(opnd_same(dst_opnd_test, opnd_create_reg(DR_REG_XDX)));

    src_opnd_test1 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 0);
    DR_ASSERT(opnd_same(src_opnd_test1, src_opnd));
    src_opnd_test2 = ub_dataflow_get_flow_src(instr, &dataflow_instr, 1, 1);
    DR_ASSERT(opnd_same(src_opnd_test2, opnd_create_reg(DR_REG_XAX)));

    instr_destroy(drcontext, instr);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    test_aaa();
    test_mov();
    test_add();
    test_label();
    test_xchg();
    test_pop();
    test_push();
    test_bswap();
    test_lea();
    test_lea_base();
    test_lea_index();
    test_div();
    test_mul();
    test_imul();
}
