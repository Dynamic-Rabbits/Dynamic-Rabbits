/*
 * tb_ih_raw_instrum.c
 *
 *      Author: john
 */

#include "tb_ih_raw_instrum.h"
#include "../spill.h"

#include "raw_instr_hndlrs/tb_raw_byte_ih_info.h"
#include "simd_instr_hndlrs/tb_simd_byte_ih_info.h"

static void tb_ih_raw_init_helper(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        tb_instr_hndlr_t (*set_instr_hndlr)(
                ib_insert_hndle_func_t instr_handler_func, void *user_data,
                IB_INSTRUM_OPT options, ib_spill_regs_func_t spill_reg_func,
                ib_restore_regs_func_t restore_reg_func, void *spill_data),
        void *tb_ctx_opaque) {

    instr_hndlrs->init_instr_hndlrs = tb_live_regs_init;
    instr_hndlrs->destroy_instr_hndlrs = tb_live_regs_destroy;

    for (int i = 0; i < TB_INSTRUM_ID_END; i++) {

        tb_raw_instr_hndlr_info_t *hndlr_info =
                &(instr_hndlrs->tb_instr_hndlr_info.instrum_raw_infos[i]);

        instr_hndlrs->instr_hndlrs[i] = set_instr_hndlr(
                hndlr_info->execute_function, (void *) hndlr_info,
                hndlr_info->opt, tb_spill_regs, tb_restore_regs,
                hndlr_info->spill_info);

        if (hndlr_info->execute_function == 0 || hndlr_info->tb_ctx == NULL) {

            dr_fprintf(STDERR, "The missing link is %d\n", i);
            DR_ASSERT(false);
        }
    }
}

static void tb_cache_init_instr_hndlrs_helper(
        tb_te_instr_hndlrs_t *instr_hndlrs, tb_taint_prepost_info_t *pre_info,
        tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque,
        void (*tb_ih_init_hndle_info)(tb_te_instr_hndlrs_t *instr_hndlrs,
                tb_taint_prepost_info_t *pre_info,
                tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque)) {

    // Init to 0
    memset(instr_hndlrs, 0, sizeof(tb_te_instr_hndlrs_t));

    instr_hndlrs->init_instr_hndlrs = tb_live_regs_init;
    instr_hndlrs->destroy_instr_hndlrs = tb_live_regs_destroy;

    tb_ih_init_hndle_info(instr_hndlrs, pre_info, post_info, tb_ctx_opaque);

    for (int i = 0; i < TB_INSTRUM_ID_END; i++) {

        IB_INSTRUM_OPT opt =
                instr_hndlrs->tb_instr_hndlr_info.instrum_raw_infos[i].opt;

        instr_hndlrs->tb_instr_hndlr_info.instrum_raw_infos[i].opt = opt
                | IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO;
    }

    tb_ih_raw_init_helper(instr_hndlrs, pre_info, post_info,
            tb_ih_set_cache_instr_hndlr, tb_ctx_opaque);

}

void tb_ih_raw_cache_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque) {

    tb_cache_init_instr_hndlrs_helper(instr_hndlrs, pre_info, post_info,
            tb_ctx_opaque, tb_ih_raw_init_hndle_info);
}

void tb_ih_simd_cache_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque) {

    tb_cache_init_instr_hndlrs_helper(instr_hndlrs, pre_info, post_info,
            tb_ctx_opaque, tb_ih_simd_init_hndle_info);

}

static void tb_inline_init_instr_hndlrs_helper(
        tb_te_instr_hndlrs_t *instr_hndlrs, tb_taint_prepost_info_t *pre_info,
        tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque,
        void (*tb_ih_init_hndle_info)(tb_te_instr_hndlrs_t *instr_hndlrs,
                tb_taint_prepost_info_t *pre_info,
                tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque)) {

    // Init to 0
    memset(instr_hndlrs, 0, sizeof(tb_te_instr_hndlrs_t));

    tb_ih_init_hndle_info(instr_hndlrs, pre_info, post_info, tb_ctx_opaque);

    for (int i = 0; i < TB_INSTRUM_ID_END; i++) {

        IB_INSTRUM_OPT anti_pc = ~IB_OPT_PC_INFO;
        IB_INSTRUM_OPT opt =
                instr_hndlrs->tb_instr_hndlr_info.instrum_raw_infos[i].opt;

        // We set only ADDR option because reg info may be obtained from instr_t.
        // This is only possible for inlined instructions where we have access to
        // the instruction being instrumented. Cached instr handlers require storing
        // reg info as well.
        instr_hndlrs->tb_instr_hndlr_info.instrum_raw_infos[i].opt = (opt
                & anti_pc) | IB_OPT_ADDR_OPND_INFO;
    }

    tb_ih_raw_init_helper(instr_hndlrs, pre_info, post_info,
            tb_ih_set_inline_instr_hndlr, tb_ctx_opaque);
}

void tb_ih_raw_in_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque) {

    tb_inline_init_instr_hndlrs_helper(instr_hndlrs, pre_info, post_info,
            tb_ctx_opaque, tb_ih_raw_init_hndle_info);
}

void tb_ih_simd_in_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque) {

    tb_inline_init_instr_hndlrs_helper(instr_hndlrs, pre_info, post_info,
            tb_ctx_opaque, tb_ih_simd_init_hndle_info);
}
