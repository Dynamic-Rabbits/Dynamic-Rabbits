/*
 * ub_drwrap_post_point_truncator.c
 *
 *      Author: john
 */

#include "ub_drwrap_post_point_truncator.h"

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include "drwrap.h"

#define UB_PRIORITY_NAME_INSERT_WRAP_POST_POINT_TRUNC "ub_bb_wrap_post_point_trunc"

static dr_emit_flags_t ub_trancute_phase(void *drcontext, void *tag,
        instrlist_t *bb, bool for_trace, bool translating) {

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

        } else if (drwrap_is_post_wrap(instr_get_app_pc(instr))) {

            if (index == 0) {

                remove = true;
            } else {

                remove = true;
                instrlist_remove(bb, instr);
                instr_destroy(drcontext, instr);
            }
        }

        instr = next;
        index++;
    }

    return DR_EMIT_DEFAULT;
}

void ub_wrap_post_point_trunc_init() {

    drmgr_init();
    drutil_init();

    drwrap_init();

    drmgr_priority_t app2app_priority = { sizeof(app2app_priority),
    UB_PRIORITY_NAME_INSERT_WRAP_POST_POINT_TRUNC, NULL, NULL,
            UB_PRIORITY_APP2APP_WRAP_POST_POINT_TRUNCATOR };

    if (!drmgr_register_bb_app2app_event(ub_trancute_phase, &app2app_priority))
        DR_ASSERT(false);
}

void ub_wrap_post_point_trunc_exit() {

    if (!drmgr_unregister_bb_app2app_event(ub_trancute_phase))
        DR_ASSERT(false);

    drwrap_exit();
    drutil_exit();
    drmgr_exit();
}

