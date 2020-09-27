/*
 * tb_ta_cc_byt_punpck.c
 *
 *      Author: john
 */

#include "../../../../taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_punpck.h"
#include "tb_ta_cc_byt_punpck_test.h"

#include "../../../../taint_bunny.h"

void tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16_test(
        void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);

    tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 2, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 6, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 10, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 14, 2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 0, (void *) 1);

    tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);

    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 2, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 6, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 10, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 14, 2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    for (int i = 8; i < 16; i++) {
        tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, i,
                (void *) 1);
    }

    tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    for (int i = 8; i < 16; i++) {
        tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, i,
                (void *) 1);
    }

    tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

}

void tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16_test(
        void *tb_ctx_opaque) {


    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

       void *drcontext = dr_get_current_drcontext();

       tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

       tb_cc_instr_hndlr_info_t info;
       memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
       info.tb_ctx = tb_ctx;

       unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

       tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

       tb_taint_mem_block((void *) tb_ctx, 71110, 16, (void *) 1);

       tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
               71110);

       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 2, 2));
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 4, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 6, 2));
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 8, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 10, 2));
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 12, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 14, 2));

       tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

       tb_untaint_mem_block((void *) tb_ctx, 71110, 16);
       tb_taint_mem_block((void *) tb_ctx, 71110, 8, (void *) 1);


       tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
               71110);

       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 2, 2));
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 4, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 6, 2));
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 8, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 10, 2));
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 12, 2));
       DR_ASSERT(
               tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3 + 14, 2));

       tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
       tb_untaint_mem_block((void *) tb_ctx, 71110, 16);

       for (int i = 8; i < 16; i++) {

           tb_taint_mem((void *) tb_ctx, 71110 +i, (void *)1);
       }

       tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
               71110);
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3, 8));

       tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
       tb_untaint_mem_block((void *) tb_ctx, 71110, 16);

       tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
               71110);
       DR_ASSERT(
               !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                       xmm_id3, 8));

}

void tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16_test(
        void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);


    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);

    tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);

    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 2, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 6, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 10, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 14, 2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 8, (void *) 1);

    tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);

    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 2, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 6, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 10, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 14, 2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    for (int i = 0; i < 8; i++) {
        tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, i,
                (void *) 1);
    }

    tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    for (int i = 0; i < 8; i++) {
        tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, i,
                (void *) 1);
    }

    tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);

    tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));
}

void tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16_test(
        void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_mem_block((void *) tb_ctx, 71110, 16, (void *) 1);

    tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);

    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 2, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 6, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 10, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 14, 2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_mem_block((void *) tb_ctx, 71110, 16);
    tb_taint_mem_block((void *) tb_ctx, 71110 + 8, 8, (void *) 1);


    tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);

    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 2, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 4, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 6, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 10, 2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 12, 2));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 14, 2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_mem_block((void *) tb_ctx, 71110, 16);


    for (int i = 0; i < 8; i++) {

        tb_taint_mem((void *) tb_ctx, 71110 +i, (void *)1);

    }

    tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
    tb_untaint_mem_block((void *) tb_ctx, 71110, 16);

    tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));
}
