/*
 * ub_opnd_limit_trancator.c
 *
 *      Author: john
 */

#include "ub_opnd_limit_truncator.h"

#include "dr_api.h"
#include "../dataflow/ub_in_out_analysis.h"

#define UB_PRIORITY_NAME_INSERT_OPND_TRUNC "ub_bb_opnd_trunc"

void ub_opnd_truncate(void *drcontext, instrlist_t *bb) {

    ub_in_out_opnds_t in_out_opnds;
    ub_init_in_out_opnds(&in_out_opnds);
    ub_get_in_out_opnds(&in_out_opnds, bb);

    size_t in_out_size = ub_size_in_out_opnds(&in_out_opnds);
    ub_delete_in_out_opnds(&in_out_opnds);

    // Do we need to truncate?
    if (in_out_size > (sizeof(unsigned int) * 8)) {

        // Get size of block:
        size_t cur_size = 0;
        instr_t *first;
        for (first = instrlist_first_app(bb); first != NULL; first =
                instr_get_next_app(first))
            cur_size++;

        int max_size = cur_size - (cur_size / 2);

        bool remove = false;

        uint index = 0;
        instr_t *next;
        instr_t *instr = instrlist_first_app(bb);
        while (instr) {

            next = instr_get_next(instr);

            if (remove) {

                // The flag has been set. We remove all remaining instrs.
                instrlist_remove(bb, instr);
                instr_destroy(drcontext, instr);

            } else if (index >= max_size) {

                remove = true;
                instrlist_remove(bb, instr);
                instr_destroy(drcontext, instr);
            }

            instr = next;
            index++;
        }
    }
}

static dr_emit_flags_t ub_truncate_phase(void *drcontext, void *tag,
        instrlist_t *bb, bool for_trace, bool translating) {

    ub_opnd_truncate(drcontext, bb);
    return DR_EMIT_DEFAULT;
}

void ub_opnd_trunc_init() {

    drmgr_priority_t app2app_priority = { sizeof(app2app_priority),
            UB_PRIORITY_NAME_INSERT_OPND_TRUNC,
    NULL, NULL, UB_PRIORITY_APP2APP_OPND_TRUNCATOR };

    if (!drmgr_register_bb_app2app_event(ub_truncate_phase, &app2app_priority))
        DR_ASSERT(false);
}

void ub_opnd_trunc_exit() {

    if (!drmgr_unregister_bb_app2app_event(ub_truncate_phase))
        DR_ASSERT(false);
}

