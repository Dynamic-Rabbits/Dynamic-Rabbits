/*
 * tb_ta_cc_byt_src_srcdst_test.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_src_srcdst_test.h"
#include "../../../../taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_srcdst.h"
#include "../../../../taint_bunny.h"

void tb_test_src_srcdst_whole_dreg_sreg_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 0, (void *) 1);

    tb_cc_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_4(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_8(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_1_sreg_1_sreg_1(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_2_sreg_2_sreg_2(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_4_sreg_4_sreg_4(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_8_sreg_8_sreg_8(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_16_sreg_16_sreg_16(&info, xmm_id3,
            xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
}

void tb_test_src_srcdst_whole_dreg_smem_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);
    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);

    tb_cc_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_4_smem_4_sreg_4(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_8_smem_8_sreg_8(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_whole_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_mem_block(tb_ctx, 71110, 1);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_1_smem_1_sreg_1(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_2_smem_2_sreg_2(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_4_smem_4_sreg_4(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_8_smem_8_sreg_8(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dreg_16_smem_16_sreg_16(&info, xmm_id3,
            71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
}

void tb_test_src_srcdst_whole_dmem_sreg_smem(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);

    tb_cc_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 1);

    tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 3));
    tb_untaint_mem_block(tb_ctx, 71110, 2);

    tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_4_smem_4(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 4));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 5));
    tb_untaint_mem_block(tb_ctx, 71110, 4);

    tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_8_smem_8(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 8));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 9));
    tb_untaint_mem_block(tb_ctx, 71110, 8);

    tb_cc_byt_handle_src_srcdst_whole_dmem_16_sreg_16_smem_16(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 16));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 17));
    tb_untaint_mem_block(tb_ctx, 71110, 16);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dmem_1_sreg_1_smem_1(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 1);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dmem_2_sreg_2_smem_2(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 3));
    tb_untaint_mem_block(tb_ctx, 71110, 2);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dmem_4_sreg_4_smem_4(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 4));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 5));
    tb_untaint_mem_block(tb_ctx, 71110, 4);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dmem_8_sreg_8_smem_8(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 8));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 9));
    tb_untaint_mem_block(tb_ctx, 71110, 8);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_whole_dmem_16_sreg_16_smem_16(&info, 71110,
            xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 16));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 17));
    tb_untaint_mem_block(tb_ctx, 71110, 16);
}

void tb_test_src_srcdst_dreg_sreg_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM1, 0, (void *) 1);

    tb_cc_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_4_sreg_4_sreg_4(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_1_sreg_1_sreg_1(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_2_sreg_2_sreg_2(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_4_sreg_4_sreg_4(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_8_sreg_8_sreg_8(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_16_sreg_16_sreg_16(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
}

void tb_test_src_srcdst_dreg_smem_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);
    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);

    tb_cc_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_4_smem_4_sreg_4(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_untaint_mem_block(tb_ctx, 71110, 1);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_1_smem_1_sreg_1(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_2_smem_2_sreg_2(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_4_smem_4_sreg_4(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_8_smem_8_sreg_8(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dreg_16_smem_16_sreg_16(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);
}

void tb_test_src_srcdst_dmem_sreg_smem(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM3, 0, (void *) 1);

    tb_cc_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 1);

    tb_cc_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 2);

    tb_cc_byt_handle_src_srcdst_dmem_4_sreg_4_smem_4(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 4);

    tb_cc_byt_handle_src_srcdst_dmem_8_sreg_8_smem_8(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 8);

    tb_cc_byt_handle_src_srcdst_dmem_16_sreg_16_smem_16(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 16);

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dmem_1_sreg_1_smem_1(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 1);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dmem_2_sreg_2_smem_2(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 2);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dmem_4_sreg_4_smem_4(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 4));
    tb_untaint_mem_block(tb_ctx, 71110, 4);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dmem_8_sreg_8_smem_8(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 8);

    tb_taint_mem_block((void *) tb_ctx, 71110, 1, (void *) 1);
    tb_cc_byt_handle_src_srcdst_dmem_16_sreg_16_smem_16(&info, 71110, xmm_id3);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 71110, 2));
    tb_untaint_mem_block(tb_ctx, 71110, 16);
}
