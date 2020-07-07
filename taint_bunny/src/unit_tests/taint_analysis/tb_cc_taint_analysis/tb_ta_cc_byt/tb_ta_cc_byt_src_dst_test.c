/*
 * tb_ta_cc_byt_src_dst_test.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_src_dst_test.h"
#include "../../../../taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_dst.h"
#include "../../../../taint_bunny.h"

void tb_test_src_dst_dmem_smem(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    tb_taint_mem_block((void *) tb_ctx, 71110, 17, (void *) 1);
    tb_taint_mem_block((void *) tb_ctx, 91110, 1, (void *) 1);

    tb_cc_byt_handle_src_dst_dmem_1_smem_1(&info, 81110, 71110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 17));
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_2_smem_2(&info, 81110, 91110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_2_smem_2(&info, 81110, 71110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 17));
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 3));
    tb_untaint_mem_block(tb_ctx, 81110, 2);

    tb_cc_byt_handle_src_dst_dmem_4_smem_4(&info, 81110, 91110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_4_smem_4(&info, 81110, 71110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 17));
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 4));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 5));
    tb_untaint_mem_block(tb_ctx, 81110, 4);

    tb_cc_byt_handle_src_dst_dmem_8_smem_8(&info, 81110, 91110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_8_smem_8(&info, 81110, 71110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 17));
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 8));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 9));
    tb_untaint_mem_block(tb_ctx, 81110, 8);

    tb_cc_byt_handle_src_dst_dmem_16_smem_16(&info, 81110, 91110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_16_smem_16(&info, 81110, 71110);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71110, 17));
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 16));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 17));
    tb_untaint_mem_block(tb_ctx, 81110, 16);

    // Clean Up
    tb_untaint_mem_block(tb_ctx, 71110, 17);
    tb_untaint_mem_block(tb_ctx, 91110, 1);

}

void tb_test_src_dst_dmem_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id2 = ub_get_byte_id(DR_REG_XMM2, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_src_dst_dmem_1_sreg_1(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_2_sreg_2(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_2_sreg_2(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 3));
    tb_untaint_mem_block(tb_ctx, 81110, 2);

    tb_cc_byt_handle_src_dst_dmem_4_sreg_4(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_4_sreg_4(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 4));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 5));
    tb_untaint_mem_block(tb_ctx, 81110, 4);

    tb_cc_byt_handle_src_dst_dmem_8_sreg_8(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_8_sreg_8(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 8));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 9));
    tb_untaint_mem_block(tb_ctx, 81110, 8);

    tb_cc_byt_handle_src_dst_dmem_16_sreg_16(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_16_sreg_16(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 16));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 17));
    tb_untaint_mem_block(tb_ctx, 81110, 16);

    // Clean Up
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM2);
}

void tb_test_src_dst_dreg_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id2 = ub_get_byte_id(DR_REG_XMM2, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_src_dst_dreg_1_sreg_1(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_2_sreg_2(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_2_sreg_2(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_4_sreg_4(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_4_sreg_4(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_8_sreg_8(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_8_sreg_8(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_16_sreg_16(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_16_sreg_16(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    // Clean Up
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM2);
}

void tb_test_src_dst_dreg_smem(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_mem_block((void *) tb_ctx, 71110, 17, (void *) 1);
    tb_taint_mem_block((void *) tb_ctx, 91110, 1, (void *) 1);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_src_dst_dreg_1_smem_1(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_1_smem_1(&info, xmm_id3, 91110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_2_smem_2(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_2_smem_2(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_4_smem_4(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_4_smem_4(&info, xmm_id3, 91110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_8_smem_8(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_8_smem_8(&info, xmm_id3, 91110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_dreg_16_smem_16(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    // Clean Up
    tb_untaint_mem_block(tb_ctx, 71110, 17);
    tb_untaint_mem_block(tb_ctx, 91110, 1);
}

void tb_test_src_dst_reg_extension(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int reg_id1 = ub_get_byte_id(DR_REG_XAX, 0);
    unsigned int reg_id2 = ub_get_byte_id(DR_REG_XBX, 0);
    unsigned int reg_id3 = ub_get_byte_id(DR_REG_XCX, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XBX, (void *) 1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XCX);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_1(&info, reg_id1, reg_id3);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1, 4));
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);

    tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_1(&info, reg_id1, reg_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, reg_id1,
                    1));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1 + 1, 3));

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_2(&info, reg_id1, reg_id3);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1, 4));

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_2(&info, reg_id1, reg_id2);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, reg_id1,
                    2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1 + 2, 2));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XBX);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XAX);

}

void tb_test_src_dst_mem_extension(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int reg_id1 = ub_get_byte_id(DR_REG_XAX, 0);

    tb_taint_mem_block((void *) tb_ctx, 71110, 17, (void *) 1);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_EBX, 0, (void *) 1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_ECX);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_src_dst_extension_dreg_4_smem_1(&info, reg_id1, 91110);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1, 4));
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_src_dst_extension_dreg_4_smem_1(&info, reg_id1, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, reg_id1,
                    1));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1 + 1, 3));

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_src_dst_extension_dreg_4_smem_2(&info, reg_id1, 91110);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1, 4));
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_src_dst_extension_dreg_4_smem_2(&info, reg_id1, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, reg_id1,
                    2));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    reg_id1 + 2, 2));
}

void tb_test_src_dst_whole_dreg_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id2 = ub_get_byte_id(DR_REG_XMM2, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_1(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_2(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_2(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_4(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_4(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_8(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_8(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_16_sreg_16(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_16_sreg_16(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    // Clean Up
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM2);
}

void tb_test_src_dst_whole_dreg_smem(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_mem_block((void *) tb_ctx, 71110, 17, (void *) 1);
    tb_taint_mem_block((void *) tb_ctx, 91110, 1, (void *) 1);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_src_dst_whole_dreg_1_smem_1(&info, xmm_id3, 91110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_1_smem_1(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_2_smem_2(&info, xmm_id3, 91110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    3));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_2_smem_2(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    1));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    2));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_4_smem_4(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_4_smem_4(&info, xmm_id3, 91110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    4));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    5));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_8_smem_8(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_8_smem_8(&info, xmm_id3, 91110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    9));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_src_dst_whole_dreg_16_smem_16(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    // Clean Up
    tb_untaint_mem_block(tb_ctx, 71110, 17);
    tb_untaint_mem_block(tb_ctx, 91110, 1);
}

void tb_test_src_dst_whole_dmem_sreg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id2 = ub_get_byte_id(DR_REG_XMM2, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_src_dst_whole_dmem_1_sreg_1(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 1));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_whole_dmem_2_sreg_2(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 2));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 3));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_4(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 4));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 5));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_4(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 4));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 5));
    tb_untaint_mem_block(tb_ctx, 81110, 4);

    tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_8(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 8));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 9));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_8(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 8));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 9));
    tb_untaint_mem_block(tb_ctx, 81110, 8);

    tb_cc_byt_handle_src_dst_whole_dmem_16_sreg_16(&info, 81110, xmm_id2);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 16));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 17));
    tb_untaint_mem_block(tb_ctx, 81110, 1);

    tb_cc_byt_handle_src_dst_dmem_16_sreg_16(&info, 81110, xmm_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 81110, 16));
    DR_ASSERT(!tb_is_mem_all_tainted(tb_ctx, 81110, 17));
    tb_untaint_mem_block(tb_ctx, 81110, 16);

    // Clean Up
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM2);
}

void tb_test_src_dst_high_src_dst_mem(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_mem_block((void *) tb_ctx, 71110, 17, (void *) 1);
    tb_taint_mem_block((void *) tb_ctx, 91110, 1, (void *) 1);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_high_src_dst_dreg_16_smem_16(&info, xmm_id3, 71110);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    17));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_high_src_dst_dreg_16_smem_16(&info, xmm_id3, 91110);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    16));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    // Clean Up
    tb_untaint_mem_block(tb_ctx, 71110, 17);
    tb_untaint_mem_block(tb_ctx, 91110, 1);
}

void tb_test_src_dst_high_src_dst_reg(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int xmm_id = ub_get_byte_id(DR_REG_XMM1, 0);
    unsigned int xmm_id2 = ub_get_byte_id(DR_REG_XMM2, 0);
    unsigned int xmm_id3 = ub_get_byte_id(DR_REG_XMM3, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XMM1, (void *) 1);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XMM2, 0, (void *) 1);

    tb_cc_byt_handle_high_src_dst_dreg_16_sreg_16(&info, xmm_id3, xmm_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3, 8));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 8));

    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    tb_cc_byt_handle_high_src_dst_dreg_16_sreg_16(&info, xmm_id3, xmm_id2);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    xmm_id3 + 8, 8));
    DR_ASSERT(
            !tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, xmm_id3,
                    8));
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM3);

    // Clean Up
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM1);
    tb_untaint_reg(tb_ctx, drcontext, DR_REG_XMM2);
}
