/*
 * addr_constant_reg_truncator.c
 *
 *      Author: john
 */

#include "ub_addr_constant_reg_truncator.h"

#include "dr_api.h"
#include "../dataflow/ub_constant_analysis.h"

#define UB_PRIORITY_NAME_INSERT_CONSTANT_REG_TRUNC "ub_bb_const_addr_reg_trunc"

app_pc ub_addr_const_reg_truncate(void *drcontext, instrlist_t *bb) {

    app_pc next_pc = NULL;

    uint index_mark;
    bool found = ub_constant_analysis_get_index_at_modified(bb, &index_mark);

    if (!found)
        return next_pc;

    bool remove = false;

    uint index = 0;
    instr_t *next;
    instr_t *instr = instrlist_first_app(bb);

    while (instr) {

        next = instr_get_next_app(instr);

        if (remove) {
            // The flag has been set. We remove all remaining instrs.
            instrlist_remove(bb, instr);
            instr_destroy(drcontext, instr);
        } else if (index_mark == index) {
            next_pc = instr_get_app_pc(instr);
            remove = true;
            instrlist_remove(bb, instr);
            instr_destroy(drcontext, instr);
        }

        instr = next;
        index++;
    }

    return next_pc;
}

static dr_emit_flags_t ub_trancute_phase(void *drcontext, void *tag,
        instrlist_t *bb, bool for_trace, bool translating) {

    ub_addr_const_reg_truncate(drcontext, bb);
    return DR_EMIT_DEFAULT;
}

void ub_addr_const_reg_trunc_init() {

    drmgr_priority_t app2app_priority = { sizeof(app2app_priority),
    UB_PRIORITY_NAME_INSERT_CONSTANT_REG_TRUNC,
    NULL, NULL, UB_PRIORITY_APP2APP_CONSTANT_TRUNCATOR };

    if (!drmgr_register_bb_app2app_event(ub_trancute_phase, &app2app_priority))
        DR_ASSERT(false);
}

void ub_addr_const_reg_trunc_exit() {

    if (!drmgr_unregister_bb_app2app_event(ub_trancute_phase))
        DR_ASSERT(false);
}
