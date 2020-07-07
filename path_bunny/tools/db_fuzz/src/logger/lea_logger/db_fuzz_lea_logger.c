/*
 * lea_logger.c
 *
 *      Author: john
 */

#include "db_fuzz_lea_logger.h"

#include "../db_fuzz_print.h"
#include "dr_defines.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"
#include "string.h"
#include <stdio.h>
#include "db_fuzz_lea_spill.h"

FILE *lea_log_file;

static void lea_index_log(void *taint_bunny) {

    bool is_tainted = false;

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t index_slot;
    index_slot.opnd_field = UB_SRC_OPND_1;
    index_slot.comp_field = UB_COMP_3;

    // A data record is composed of 13 entries.
    char data[6][200];

    for (size_t i = 0; i < 6; i++) {
        strncpy(data[i], "{}", 200);
    }

    strncpy(data[0], "32", 200);
    db_fuzz_store_pc(drcontext, data[1], 200);

    uintptr_t index_opnd = ib_get_comp_opnd(drcontext, &index_slot);

    for (int data_index = 2; data_index < 4 + 2; data_index++, index_opnd++) {

        void *tb_label = tb_get_reg_byte_taint_label_via_byte_id(taint_bunny,
                drcontext, index_opnd);

        if (tb_label) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index],
                    200);
            is_tainted = is_tainted | succ;
        }
    }

    if (is_tainted) {

        for (int i = 0; i < 5; i++) {

            // We use fprint because it is buffered. it *should* be okay to use
            // as opposed to dr_fprintf ... hopefully.

            fprintf(lea_log_file, "%s ", data[i]);
        }

        fprintf(lea_log_file, "%s\n", data[5]);
    }
}

static void instrument_lea_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *taint_bunny, void *spill_data) {

    instr_t *done_label = INSTR_CREATE_label(drcontext);
    instr_t *reg_tainted_label = INSTR_CREATE_label(drcontext);

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_3;

    ib_insert_get_comp_opnd(drcontext, ilist, where, db_fuzz_lea_reg1,
            &comp_access_slot);

    tb_insert_is_some_reg_tainted_via_reg(taint_bunny, drcontext, ilist, where,
    db_fuzz_lea_reg1, db_fuzz_lea_reg2, db_fuzz_lea_reg3, 4, reg_tainted_label);

    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, reg_tainted_label);

    dr_insert_clean_call(drcontext, ilist, where, lea_index_log, false, 1,
    OPND_CREATE_INTPTR(taint_bunny));

    instrlist_meta_preinsert(ilist, where, done_label);

}

void db_fuzz_register_lea_checks(void *tool_info, void *taint_bunny) {

	/* Dont need to use IB_OPT_FULL_OPND_INFO */
    IB_INSTRUM_OPT option = IB_OPT_ADDR_GEN_INFO | IB_OPT_PC_INFO |
    IB_OPT_REG_OPND_INFO;

    ib_insert_hndle_data_t cc_data;
    cc_data.user_data = taint_bunny;
    cc_data.spill_reg_func = db_fuzz_lea_spill_three_regs;
    cc_data.restore_reg_func = db_fuzz_lea_restore_three_regs;
    cc_data.user_instrum_func = instrument_lea_check;

    ib_hook_cache_to_instr_ex(tool_info, OP_lea, &cc_data, option,
    IB_INSTRUM_BEFORE, ub_is_lea_index_dreg_4_sreg_4_instr, IB_GUARD_HOOK);

    ib_hook_cache_to_instr_ex(tool_info, OP_lea, &cc_data, option,
    IB_INSTRUM_BEFORE, ub_is_lea_dreg_4_sreg_4_sreg_4_instr, IB_GUARD_HOOK);

}

