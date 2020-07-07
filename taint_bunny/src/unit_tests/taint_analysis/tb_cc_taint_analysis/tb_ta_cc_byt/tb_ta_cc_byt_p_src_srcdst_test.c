/*
 * tb_ta_cc_byt_p_src_srcdst_test.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_p_src_srcdst_test.h"
#include "../../../../taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_p_src_srcdst.h"
#include "../../../../taint_bunny.h"

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16_test(
        void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 0, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 15, (void *) 1);

    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 0, (void *) 1);

    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 16));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

}

void tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16_test(
        void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_taint_mem_block((void *) tb_ctx, 71125, 1, (void *) 1);

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_mem_block(tb_ctx, 71110, 16);

    tb_taint_mem_block((void *) tb_ctx, 71125, 1, (void *) 1);

    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_mem_block(tb_ctx, 71110, 16);
}

void tb_cc_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 0, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 15, (void *) 1);

    tb_cc_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3, xmm_id);

    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 14, (void *) 1);

    tb_cc_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3, xmm_id);

    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);


}

void tb_cc_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_taint_mem_block((void *) tb_ctx, 71125, 1, (void *) 1);

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_cc_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_mem_block(tb_ctx, 71110, 16);

    tb_taint_mem_block((void *) tb_ctx, 71125, 1, (void *) 1);

    tb_cc_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 4));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_mem_block(tb_ctx, 71110, 16);

}
