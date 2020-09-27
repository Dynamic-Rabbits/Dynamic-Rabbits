/*
 * tb_ta_cc_byt_unsupport.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_untainted_test.h"
#include "../../../../taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_untaint.h"
#include "../../../../taint_bunny.h"

void tb_test_untaint_mem(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_taint_mem_block((void *) tb_ctx, 71110, 10, (void *) 17);
    tb_cc_byt_handle_untaint_mem_1(tb_ctx, 71110);
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(tb_is_some_mem_tainted(tb_ctx, 71110, 2));

    tb_taint_mem_block((void *) tb_ctx, 71110, 10, (void *) 17);
    tb_cc_byt_handle_untaint_mem_2(tb_ctx, 71110);
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71110, 2));
    DR_ASSERT(tb_is_some_mem_tainted(tb_ctx, 71110, 3));

    tb_taint_mem_block((void *) tb_ctx, 71110, 10, (void *) 17);
    tb_cc_byt_handle_untaint_mem_4(tb_ctx, 71110);
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71110, 4));
    DR_ASSERT(tb_is_some_mem_tainted(tb_ctx, 71110, 5));

    tb_taint_mem_block((void *) tb_ctx, 71110, 10, (void *) 17);
    tb_cc_byt_handle_untaint_mem_8(tb_ctx, 71110);
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71110, 8));
    DR_ASSERT(tb_is_some_mem_tainted(tb_ctx, 71110, 9));

    tb_taint_mem_block((void *) tb_ctx, 71110, 17, (void *) 17);
    tb_cc_byt_handle_untaint_mem_16(tb_ctx, 71110);
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71110, 16));
    DR_ASSERT(tb_is_some_mem_tainted(tb_ctx, 71110, 17));

    // Clean up
    tb_cc_byt_handle_untaint_mem_1(tb_ctx, 71110 + 16);

}

void tb_test_untaint_reg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_cc_byt_handle_untaint_reg_1(tb_ctx, xmm_id);
    DR_ASSERT(tb_is_some_reg_byte_tainted(tb_ctx, drcontext, DR_REG_XMM1));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id,
                    1));

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 2);
    tb_cc_byt_handle_untaint_reg_2(tb_ctx, xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id,
                    2));
    DR_ASSERT(tb_is_some_reg_byte_tainted(tb_ctx, drcontext, DR_REG_XMM1));

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 2);
    tb_cc_byt_handle_untaint_reg_4(tb_ctx, xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id,
                    4));
    DR_ASSERT(tb_is_some_reg_byte_tainted(tb_ctx, drcontext, DR_REG_XMM1));

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_cc_byt_handle_untaint_reg_8(tb_ctx, xmm_id);
DR_ASSERT(!tb_is_some_reg_block_tainted_via_byte_id(tb_ctx,
                    drcontext, xmm_id,  8));
        DR_ASSERT(tb_is_some_reg_byte_tainted(tb_ctx, drcontext, DR_REG_XMM1));

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_cc_byt_handle_untaint_reg_16(tb_ctx, xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id,
                    16));
    DR_ASSERT(!tb_is_some_reg_byte_tainted(tb_ctx, drcontext, DR_REG_XMM1));
}

