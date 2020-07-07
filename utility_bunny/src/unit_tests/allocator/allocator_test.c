/*
 * allocator_test.c
 *
 *      Author: john
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "dr_api.h"
#include "drmgr.h"
#include "drreg.h"
#include "drutil.h"
#include "../../utility_bunny.h"

static void event_exit();
static dr_emit_flags_t event_bb_insert(void *drcontext, void *tag,
        instrlist_t *bb, instr_t *instr, bool for_trace, bool translating,
        void *user_data);

void *allocation_ctx;

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    drutil_init();

    drreg_options_t ops = { sizeof(ops), 4, false };

    drmgr_priority_t priority = { sizeof(priority), "spinlock", NULL, NULL, 0 };
    dr_register_exit_event(event_exit);

    if (!drmgr_register_bb_instrumentation_event(NULL, event_bb_insert,
            &priority) || drreg_init(&ops) != DRREG_SUCCESS) {
        /* something is wrong: can't continue */
        DR_ASSERT(false);
        return;
    }

    allocation_ctx = ub_create_fixed_allocator(1, 1000);
}

static void event_exit() {

    ub_destroy_fixed_allocator(allocation_ctx);

    if (!drmgr_unregister_bb_insertion_event(event_bb_insert)
            || drreg_exit() != DRREG_SUCCESS)
        DR_ASSERT(false);

    drutil_exit();
    drmgr_exit();
}

/* event_bb_insert calls instrument_mem to instrument every
 * application memory reference.
 */
static dr_emit_flags_t event_bb_insert(void *drcontext, void *tag,
        instrlist_t *bb, instr_t *instr, bool for_trace, bool translating,
        void *user_data) {

    opnd_t ref, opnd1, opnd2;
    reg_id_t reg1, reg2, reg3, reg4;
    drvector_t allowed;

    drreg_init_and_fill_vector(&allowed, false);
    drreg_set_vector_entry(&allowed, DR_REG_XAX, true);
    if (drreg_reserve_register(drcontext, bb, instr, &allowed, &reg2)
            != DRREG_SUCCESS
            || drreg_reserve_register(drcontext, bb, instr, NULL, &reg1)
                    != DRREG_SUCCESS
            || drreg_reserve_register(drcontext, bb, instr, NULL, &reg3)
                    != DRREG_SUCCESS
            || drreg_reserve_register(drcontext, bb, instr, NULL, &reg4)
                    != DRREG_SUCCESS
            || drreg_reserve_aflags(drcontext, bb, instr) != DRREG_SUCCESS) {
        DR_ASSERT(false); /* cannot recover */
        drvector_delete(&allowed);
        return DR_EMIT_DEFAULT;
    }
    drvector_delete(&allowed);

    ub_insert_allocation(allocation_ctx, drcontext, bb, instr, reg1, reg2);
    ub_insert_allocation(allocation_ctx, drcontext, bb, instr, reg4, reg2);
    ub_insert_dealloation(allocation_ctx, drcontext, bb, instr, reg1, reg2,
            reg3);
    ub_insert_dealloation(allocation_ctx, drcontext, bb, instr, reg4, reg2,
            reg3);


    ub_insert_allocation(allocation_ctx, drcontext, bb, instr, reg1, reg2);
    ub_insert_allocation(allocation_ctx, drcontext, bb, instr, reg4, reg2);
    ub_insert_dealloation(allocation_ctx, drcontext, bb, instr, reg4, reg2,
            reg3);

    ub_insert_dealloation(allocation_ctx, drcontext, bb, instr, reg1, reg2,
            reg3);

    if (drreg_unreserve_register(drcontext, bb, instr, reg1) != DRREG_SUCCESS
            || drreg_unreserve_register(drcontext, bb, instr, reg2)
                    != DRREG_SUCCESS
            || drreg_unreserve_register(drcontext, bb, instr, reg3)
                    != DRREG_SUCCESS
            || drreg_unreserve_register(drcontext, bb, instr, reg4)
                    != DRREG_SUCCESS
            || drreg_unreserve_aflags(drcontext, bb, instr) != DRREG_SUCCESS)
        DR_ASSERT(false);

    return DR_EMIT_DEFAULT;

}

