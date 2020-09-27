/**
 *  @file ub_event_dealloc.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_event_dealloc.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drwrap.h"
#include "../routine_entry_checker.h"
#include "../../../datastructs/sets/ub_str_hashset.h"
#include <string.h>
#include <stdint.h>

typedef struct {

    ub_ev_handle_heap_dealloc_event_t pre_dealloc_hndlr;
    ub_ev_handle_heap_dealloc_event_t post_dealloc_hndlr;

} heap_dealloc_ctx_t;

static void ub_ev_heap_dealloc_module_load_event(void *drcontext,
        const module_data_t *mod, bool loaded);
static void ub_ev_heap_dealloc_wrap_free_pre(void *wrapcxt, void **user_data);
static void ub_ev_heap_dealloc_wrap_free_post(void *wrapcxt, void *user_data);

/*
 *  Since DrWrap only allows us to insert the same function cb once, we only
 *  support one instantiation.
 */
heap_dealloc_ctx_t *dealloc_ctx;

void ub_ev_heap_dealloc_init_ctx(
        ub_ev_handle_heap_dealloc_event_t pre_dealloc_hndlr,
        ub_ev_handle_heap_dealloc_event_t post_dealloc_hndlr) {

    drmgr_init();
    drwrap_init();

    ub_ev_heap_routine_entry_checker_init();

    dealloc_ctx = dr_global_alloc(sizeof(heap_dealloc_ctx_t));
    dealloc_ctx->pre_dealloc_hndlr = pre_dealloc_hndlr;
    dealloc_ctx->post_dealloc_hndlr = post_dealloc_hndlr;

    drmgr_register_module_load_event(ub_ev_heap_dealloc_module_load_event);
}

void ub_ev_heap_dealloc_destroy_ctx() {

    ub_ev_heap_routine_entry_checker_destroy();
    dr_global_free(dealloc_ctx, sizeof(heap_dealloc_ctx_t));

    drmgr_unregister_module_load_event(ub_ev_heap_dealloc_module_load_event);

    drwrap_exit();
    drmgr_exit();
}

/**
 *  Called upon the loading of a module. Used to wrap free.
 */
static void ub_ev_heap_dealloc_module_load_event(void *drcontext,
        const module_data_t *mod, bool loaded) {

    ub_ev_heap_wrap_helper(mod, "free", NULL,
            ub_ev_heap_dealloc_wrap_free_pre,
            ub_ev_heap_dealloc_wrap_free_post);

    ub_ev_heap_wrap_helper(mod, "cfree", NULL,
            ub_ev_heap_dealloc_wrap_free_pre,
            ub_ev_heap_dealloc_wrap_free_post);

    ub_ev_heap_wrap_helper(mod, "__libc_free", NULL,
            ub_ev_heap_dealloc_wrap_free_pre,
            ub_ev_heap_dealloc_wrap_free_post);


    //TODO Wrap more allocation functions!
}

static void ub_ev_heap_dealloc_wrap_free_pre(void *wrapcxt, void **user_data) {

    void *drcontext = dr_get_current_drcontext();

    if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

        ub_ev_dealloc_data_t *dealloc_data = dr_global_alloc(
                sizeof(ub_ev_dealloc_data_t));

        void *addr = (void *) drwrap_get_arg(wrapcxt, 0);

        dealloc_data->addr = addr;
        dealloc_data->pc = drwrap_get_func(wrapcxt);

        if (dealloc_ctx->pre_dealloc_hndlr) {
            dealloc_ctx->pre_dealloc_hndlr(dealloc_data);
        }

        // Send the alloc_data to post function.
        *user_data = dealloc_data;
        ub_ev_heap_routine_entry_checker_set(drcontext);
        return;
    }

    *user_data = NULL;
}

/**
 *  Called after free. Used to call the cb.
 *
 *  @param user_data The alloc_data containing the size of the allocation.
 */
static void ub_ev_heap_dealloc_wrap_free_post(void *wrapcxt, void *user_data) {

    ub_ev_dealloc_data_t *dealloc_data = (ub_ev_dealloc_data_t *) user_data;

    void *drcontext = dr_get_current_drcontext();

    if (dealloc_data != NULL) {

        DR_ASSERT(ub_ev_heap_routine_entry_checker_is_set(drcontext));
        ub_ev_heap_routine_entry_checker_unset(drcontext);
        DR_ASSERT(!ub_ev_heap_routine_entry_checker_is_set(drcontext));

        if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

            if (dealloc_ctx->post_dealloc_hndlr) {
                DR_TRY_EXCEPT(drcontext, {
                    dealloc_data->return_pc = drwrap_get_retaddr(wrapcxt)
                    ;
                },
                { dr_fprintf(STDERR, "Warning: Failed to retrieve retaddr"); });

                dealloc_ctx->post_dealloc_hndlr(dealloc_data);
            }
        }

        dr_global_free(dealloc_data, sizeof(ub_ev_dealloc_data_t));
    }
}
