/**
 *  @file RoutineEntryChecker.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "routine_entry_checker.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drwrap.h"
#include <string.h>
#include <stdint.h>

/***************************************************************************
 *  Structs
 */

int instant_count = 0;
int tls_field = -1;

/***************************************************************************
 *  Prototypes
 */

static void ub_ev_heap_routine_entry_checker_thread_init(void *drcontext);

/***************************************************************************
 *  Implementation
 */

void ub_ev_heap_routine_entry_checker_init() {

    if (instant_count == 0) {
        tls_field = drmgr_register_tls_field();

        drmgr_register_thread_init_event(
                ub_ev_heap_routine_entry_checker_thread_init);
    }

    instant_count++;
}

void ub_ev_heap_routine_entry_checker_destroy() {


    instant_count--;

    DR_ASSERT(instant_count >=0);

    if (instant_count == 0) {
        drmgr_unregister_tls_field(tls_field);
        drmgr_unregister_thread_init_event(
                ub_ev_heap_routine_entry_checker_thread_init);
    }
}

static void ub_ev_heap_routine_entry_checker_thread_init(void *drcontext) {

    drmgr_set_tls_field(drcontext, tls_field, ((void *) (intptr_t) 0));
}

bool ub_ev_heap_routine_entry_checker_is_set(void *drcontext) {

    return drmgr_get_tls_field(drcontext, tls_field) != 0;
}

void ub_ev_heap_routine_entry_checker_set(void *drcontext) {

    DR_ASSERT(tls_field > -1);

    drmgr_set_tls_field(drcontext, tls_field, (void *) 1);
}

void ub_ev_heap_routine_entry_checker_unset() {
    void *drcontext = dr_get_current_drcontext();

    int val = (intptr_t) drmgr_get_tls_field(drcontext, tls_field);

    if (val > 0)
        drmgr_set_tls_field(drcontext, tls_field, (void *) 0);
}

void ub_ev_heap_wrap_helper(const module_data_t *mod,
        char *func_name, void *user_data,
        void (*pre_func_cb)(void *wrapcxt, INOUT void **user_data),
        void (*post_func_cb)(void *wrapcxt, void *user_data)) {

    app_pc towrap = (app_pc) dr_get_proc_address(mod->handle, func_name);

    if (towrap != NULL) {

        bool is_succ = drwrap_wrap_ex(towrap, pre_func_cb, post_func_cb, user_data,
                DRWRAP_CALLCONV_DEFAULT);
        DR_ASSERT(is_succ);
    }
}

