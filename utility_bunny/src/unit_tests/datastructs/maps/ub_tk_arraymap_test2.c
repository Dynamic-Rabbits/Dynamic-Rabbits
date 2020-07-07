/*
 * ub_tk_arraymap_test2.c
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
#include "../../../utility_bunny.h"

void *tk_array;

static void event_exit();
static dr_emit_flags_t event_bb_insert(void *drcontext, void *tag,
        instrlist_t *bb, instr_t *instr, bool for_trace, bool translating,
        void *user_data);

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    drutil_init();

    tk_array = ub_tk_arraymap_create_map();

    drreg_options_t ops = { sizeof(ops), 4, false };

    drmgr_priority_t priority = { sizeof(priority), "array", NULL, NULL, 0 };
    dr_register_exit_event(event_exit);

    if (!drmgr_register_bb_instrumentation_event(NULL, event_bb_insert,
            &priority) || drreg_init(&ops) != DRREG_SUCCESS) {
        /* something is wrong: can't continue */
        DR_ASSERT(false);
        return;
    }
}

static void event_exit() {

    ub_tk_arraymap_destroy_map(tk_array, NULL);

    if (!drmgr_unregister_bb_insertion_event(event_bb_insert)
            || drreg_exit() != DRREG_SUCCESS)
        DR_ASSERT(false);

    drutil_exit();
    drmgr_exit();
}

void test_null(reg_id_t reg) {

    void* drcontext = dr_get_current_drcontext();

    // Initialise machine context so that reg values may be retrieved.
    dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
    dr_get_mcontext(drcontext, &mcontext);

    uintptr_t val = (uintptr_t) reg_get_value(reg, &mcontext);
    DR_ASSERT((void *)val == NULL);

    val = (uintptr_t) ub_tk_arraymap_lookup_entry(tk_array, 6, 89);
    DR_ASSERT((void *)val == NULL);
}

void test_insert() {

    uintptr_t val = (uintptr_t) ub_tk_arraymap_lookup_entry(tk_array, 6, 89);
    DR_ASSERT(val == 6);
}

void test_check(reg_id_t reg) {

    void* drcontext = dr_get_current_drcontext();

    // Initialise machine context so that reg values may be retrieved.
    dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
    dr_get_mcontext(drcontext, &mcontext);

    uintptr_t val = (uintptr_t) reg_get_value(reg, &mcontext);
    DR_ASSERT(val == 6);

    val = (uintptr_t) ub_tk_arraymap_lookup_entry(tk_array, 6, 89);
    DR_ASSERT(val == 6);
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

    ub_instrum_mov_st_immed_to_reg(drcontext, bb, instr, 6, reg1);
    ub_instrum_mov_st_immed_to_reg(drcontext, bb, instr, 89, reg2);

    ub_tk_arraymap_insert_lookup(tk_array, drcontext, bb, instr, reg1, reg2,
            reg3);

    dr_insert_clean_call(drcontext, bb, instr, test_null, false, 1,
    OPND_CREATE_INTPTR(reg3));

    ub_tk_arraymap_insert_map_entry(tk_array, drcontext, bb, instr, reg1, reg2,
            reg3, reg4);

    opnd_t value_opnd = ub_tk_arraymap_get_val_opnd(reg3);
    opnd_t immed_opnd = opnd_create_immed_int(6, OPSZ_4);
    instr_t *instr2 = INSTR_CREATE_mov_imm(drcontext, value_opnd, immed_opnd);
    instrlist_meta_preinsert(bb, instr, instr2);

    dr_insert_clean_call(drcontext, bb, instr, test_insert, false, 0);

    ub_tk_arraymap_insert_lookup(tk_array, drcontext, bb, instr, reg1, reg2,
            reg3);

    dr_insert_clean_call(drcontext, bb, instr, test_check, false, 1,
    OPND_CREATE_INTPTR(reg3));

    ub_tk_arraymap_insert_inline_map_remove(tk_array, drcontext, bb, instr,
            reg1, reg2, reg3);

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

