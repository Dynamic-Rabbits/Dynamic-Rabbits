/*
 * tb_ih_cc_instrum.c
 *
 *      Author: john
 */

#include "tb_ih_cc_instrum.h"
#include "../../../tb_defines.h"
#include "instr_hndlrs/tb_cc_byte_ih_info.h"
#include "instr_hndlrs/tb_cc_byt_instr_hndlrs.h"

static void tb_ih_cc_insert_clean_call(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    tb_cc_instr_hndlr_info_t *hndlr_info =
            (tb_cc_instr_hndlr_info_t *) user_data;

    dr_insert_clean_call(drcontext, ilist, where, hndlr_info->execute_function,
    false, 1,
    OPND_CREATE_INTPTR(hndlr_info));
}

static void tb_ih_cc_init_helper(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        tb_instr_hndlr_t (*set_instr_hndlr)(
                ib_insert_hndle_func_t instr_handler_func, void *user_data,
                IB_INSTRUM_OPT options, ib_spill_regs_func_t spill_reg_func,
                ib_restore_regs_func_t restore_reg_func, void *spill_data),
        void *tb_ctx_opaque) {

    // Init to 0
    memset(instr_hndlrs, 0, sizeof(tb_te_instr_hndlrs_t));

    instr_hndlrs->init_instr_hndlrs = NULL;
    instr_hndlrs->destroy_instr_hndlrs = NULL;

    tb_ih_cc_init_hndle_info(instr_hndlrs, pre_info, post_info, tb_ctx_opaque);

    for (int i = 0; i < TB_INSTRUM_ID_END; i++) {

        tb_cc_instr_hndlr_info_t *hndlr_info =
                &(instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[i]);

        IB_INSTRUM_OPT opt = hndlr_info->opt;
        hndlr_info->opt = opt | IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO;
        instr_hndlrs->instr_hndlrs[i] = set_instr_hndlr(
                tb_ih_cc_insert_clean_call, (void *) hndlr_info,
                hndlr_info->opt, NULL, NULL, NULL);
    }
}

void tb_ih_cc_cache_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque) {

    tb_ih_cc_init_helper(instr_hndlrs, pre_info, post_info,
            tb_ih_set_cache_instr_hndlr, tb_ctx_opaque);
}

void tb_ih_cc_in_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque) {

    tb_ih_cc_init_helper(instr_hndlrs, pre_info, post_info,
            tb_ih_set_inline_instr_hndlr, tb_ctx_opaque);
}

static bool tb_ih_is_supported_dst_modified(instr_t *app_instr) {

    int dst_num = instr_num_dsts(app_instr);

    for (int i = 0; i < dst_num; i++) {
        opnd_t dst = instr_get_dst(app_instr, i);

        if (ub_opnd_is_reg(&dst) || opnd_is_memory_reference(dst))
            return true;
    }

    return false;
}

void tb_ih_cc_insert_unsupported_handle(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    if (tb_ih_is_supported_dst_modified(app_instr)) {
        dr_insert_clean_call(drcontext, ilist, where,
                tb_cc_byt_execute_unsupported_instr,
                false, 1, OPND_CREATE_INTPTR(user_data));
    }
}
