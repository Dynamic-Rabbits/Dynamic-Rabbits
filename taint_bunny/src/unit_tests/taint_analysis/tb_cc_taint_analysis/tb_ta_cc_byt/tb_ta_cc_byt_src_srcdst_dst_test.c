/*
 * tb_ta_cc_byt_src_srcdst_dst_test.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_src_srcdst_dst_test.h"
#include "../../../../taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_srcdst_dst.h"
#include "../../../../taint_bunny.h"

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4_test(
        void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int src_reg = ub_get_byte_id(DR_REG_XBX, 0);
    unsigned int srcdst_id = ub_get_byte_id(DR_REG_XAX, 0);
    unsigned int dst_id = ub_get_byte_id(DR_REG_XDX, 0);

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XBX );
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX );
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XDX );

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XBX, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4(&info,
            dst_id, srcdst_id, src_reg);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    srcdst_id, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, dst_id,
                    4));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XBX );
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX );
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XDX );

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XAX, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4(&info,
            dst_id, srcdst_id, src_reg);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    srcdst_id, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, dst_id,
                    4));
}

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4_test(
        void *tb_ctx_opaque) {


    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int srcdst_id = ub_get_byte_id(DR_REG_XAX, 0);
    unsigned int dst_id = ub_get_byte_id(DR_REG_XDX, 0);

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX );
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XDX );

    tb_taint_mem_block((void *) tb_ctx, 71110, 4, (void *) 1);


    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XBX, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4(&info,
            dst_id, srcdst_id, 71110);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    srcdst_id, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, dst_id,
                    4));

    tb_untaint_mem_block(tb_ctx_opaque, 71110, 10);
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX );
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XDX );

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XAX, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4(&info,
            dst_id, srcdst_id, 71110);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    srcdst_id, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, dst_id,
                    4));

    tb_untaint_mem_block(tb_ctx_opaque, 71110, 10);
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX );
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XDX );}
