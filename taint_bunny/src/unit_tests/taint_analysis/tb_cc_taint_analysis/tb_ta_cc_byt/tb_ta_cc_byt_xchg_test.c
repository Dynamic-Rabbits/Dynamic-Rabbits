/*
 * tb_ta_cc_byt_xchg_test.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_xchg_test.h"
#include "../../../../taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_xchg.h"
#include "../../../../taint_bunny.h"

void tb_cc_byt_handle_xchg_reg_4_reg_4_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int eax_id = ub_get_byte_id(DR_REG_XAX, 0);
    unsigned int ebx_id = ub_get_byte_id(DR_REG_XBX, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XBX);

    tb_cc_byt_handle_xchg_reg_4_reg_4(&info, eax_id, ebx_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX);
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XBX, (void *) 1);

    tb_cc_byt_handle_xchg_reg_4_reg_4(&info, eax_id, ebx_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    4));
}

void tb_cc_byt_handle_xchg_reg_4_mem_4_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int eax_id = ub_get_byte_id(DR_REG_XAX, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_untaint_mem_block((void *) tb_ctx, 71125, 16);

    tb_cc_byt_handle_xchg_reg_4_mem_4(&info, eax_id, 71125);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71125, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX);
    tb_taint_mem_block((void *) tb_ctx, 71125, 4, (void *) 1);

    tb_cc_byt_handle_xchg_reg_4_mem_4(&info, eax_id, 71125);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71125, 4));

}

void tb_cc_byt_handle_xchg_mem_4_reg_4_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int eax_id = ub_get_byte_id(DR_REG_XAX, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_untaint_mem_block((void *) tb_ctx, 71125, 16);

    tb_cc_byt_handle_xchg_mem_4_reg_4(&info, 71125, eax_id);
    DR_ASSERT(tb_is_mem_all_tainted(tb_ctx, 71125, 4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX);
    tb_taint_mem_block((void *) tb_ctx, 71125, 4, (void *) 1);

    tb_cc_byt_handle_xchg_mem_4_reg_4(&info, 71125, eax_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71125, 4));

    tb_untaint_mem_block((void *) tb_ctx, 71125, 16);
}

void tb_cc_handle_bswap_dsreg_4_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int eax_id = ub_get_byte_id(DR_REG_XAX, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_cc_byt_handle_bswap_dsreg_4(&info, eax_id);
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XAX, 0, (void *) 1);
    tb_cc_byt_handle_bswap_dsreg_4(&info, eax_id);
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    3));
    DR_ASSERT(
            tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    eax_id + 3, 1));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX);
    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XAX, 3, (void *) 1);
    tb_cc_byt_handle_bswap_dsreg_4(&info, eax_id);
    DR_ASSERT(
            tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    1));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext,
                    eax_id + 1, 3));

    tb_untaint_mem_block((void *) tb_ctx, 71125, 16);

}

void tb_cc_handle_bswap_dsmem_4_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    tb_untaint_mem_block((void *) tb_ctx, 71125, 4);
    tb_taint_mem((void *) tb_ctx, 71125, (void *) 1);
    tb_cc_byt_handle_bswap_dsmem_4(&info, 71125);

    DR_ASSERT(tb_is_some_mem_tainted(tb_ctx, 71125 + 3, 1));
    DR_ASSERT(!tb_is_some_mem_tainted(tb_ctx, 71125, 3));
}

void tb_cc_byt_handle_xadd_reg_4_reg_4_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int eax_id = ub_get_byte_id(DR_REG_XAX, 0);
    unsigned int ebx_id = ub_get_byte_id(DR_REG_XBX, 0);

    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XAX, (void *) 1);
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XBX);

    tb_cc_byt_handle_xadd_reg_4_reg_4(&info, eax_id, ebx_id);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    4));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX);
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XBX, (void *) 1);

    tb_cc_byt_handle_xadd_reg_4_reg_4(&info, eax_id, ebx_id);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    4));

    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XAX);
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XBX);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XBX, 0, (void *) 1);

    tb_cc_byt_handle_xadd_reg_4_reg_4(&info, eax_id, ebx_id);

    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, eax_id,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    4));

}

void tb_cc_byt_handle_xadd_mem_4_reg_4_test(void *tb_ctx_opaque) {

    tb_context_t *tb_ctx = (tb_context_t *) tb_ctx_opaque;

    void *drcontext = dr_get_current_drcontext();

    tb_cc_instr_hndlr_info_t info;
    memset(&info, 0, sizeof(tb_cc_instr_hndlr_info_t));
    info.tb_ctx = tb_ctx;

    unsigned int ebx_id = ub_get_byte_id(DR_REG_XBX, 0);
    tb_untaint_mem_block((void *) tb_ctx, 71125, 16);

    tb_taint_mem(tb_ctx, 71125, (void *) 1);
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XBX);

    tb_cc_byt_handle_xadd_mem_4_reg_4(&info, 71125, ebx_id);

    DR_ASSERT(
            tb_is_mem_all_tainted(tb_ctx, 71125,
                    4));
    DR_ASSERT(
            tb_is_all_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    1));

    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id + 1,
                    3));

    tb_untaint_mem_block((void *) tb_ctx, 71125, 16);
    tb_taint_reg((void *) tb_ctx, drcontext, DR_REG_XBX, (void *) 1);

    tb_cc_byt_handle_xadd_mem_4_reg_4(&info, 71125, ebx_id);

    DR_ASSERT(
            tb_is_mem_all_tainted(tb_ctx, 71125,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    4));

    tb_untaint_mem_block((void *) tb_ctx, 71125, 16);
    tb_untaint_reg((void *) tb_ctx, drcontext, DR_REG_XBX);

    tb_taint_reg_byte((void *) tb_ctx, drcontext, DR_REG_XBX, 0, (void *) 1);

    tb_cc_byt_handle_xadd_mem_4_reg_4(&info, 71125, ebx_id);

    DR_ASSERT(
            tb_is_mem_all_tainted(tb_ctx, 71125,
                    4));
    DR_ASSERT(
            !tb_is_some_reg_block_tainted_via_byte_id(tb_ctx, drcontext, ebx_id,
                    4));
}
