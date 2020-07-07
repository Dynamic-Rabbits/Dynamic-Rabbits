/**
 *  @file ub_event_realloc.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_event_realloc.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drwrap.h"
#include "../routine_entry_checker.h"
#include "../../../datastructs/sets/ub_str_hashset.h"
#include <string.h>
#include <stdint.h>

typedef struct {

    ub_ev_handle_heap_realloc_event_t pre_realloc_hndlr;
    ub_ev_handle_heap_realloc_event_t post_realloc_hndlr;
} heap_realloc_ctx_t;

static void ub_ev_heap_realloc_module_load_event(void *drcontext,
        const module_data_t *mod, bool loaded);
static void ub_ev_heap_realloc_wrap_realloc_pre(void *wrapcxt, void **user_data);
static void ub_ev_heap_realloc_wrap_realloc_post(void *wrapcxt, void *user_data);

/*
 *  Since DrWrap only allows us to insert the same function cb once, we only
 *  support one instantiation.
 */
heap_realloc_ctx_t *realloc_ctx;

void ub_ev_heap_realloc_init_ctx(
        ub_ev_handle_heap_realloc_event_t pre_realloc_hndlr,
        ub_ev_handle_heap_realloc_event_t post_realloc_hndlr) {

    drmgr_init();
    drwrap_init();

    ub_ev_heap_routine_entry_checker_init();

    realloc_ctx = dr_global_alloc(sizeof(heap_realloc_ctx_t));
    realloc_ctx->pre_realloc_hndlr = pre_realloc_hndlr;
    realloc_ctx->post_realloc_hndlr = post_realloc_hndlr;

    drmgr_register_module_load_event(ub_ev_heap_realloc_module_load_event);
}

void ub_ev_heap_realloc_destroy_ctx() {

    ub_ev_heap_routine_entry_checker_destroy();
    dr_global_free(realloc_ctx, sizeof(heap_realloc_ctx_t));

    drmgr_unregister_module_load_event(ub_ev_heap_realloc_module_load_event);

    drwrap_exit();
    drmgr_exit();
}

static void ub_ev_heap_realloc_module_load_event(void *drcontext,
        const module_data_t *mod, bool loaded) {

    ub_ev_heap_wrap_helper(mod, "realloc", NULL,
            ub_ev_heap_realloc_wrap_realloc_pre,
            ub_ev_heap_realloc_wrap_realloc_post);

    ub_ev_heap_wrap_helper(mod, "__libc_realloc", NULL,
            ub_ev_heap_realloc_wrap_realloc_pre,
            ub_ev_heap_realloc_wrap_realloc_post);

    //TODO Wrap more allocation functions!
}

static void ub_ev_heap_realloc_wrap_realloc_pre(void *wrapcxt, void **user_data) {

    void *drcontext = dr_get_current_drcontext();

    if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

        ub_ev_realloc_data_t *realloc_data = dr_global_alloc(
                sizeof(ub_ev_realloc_data_t));

        void *passed_addr = (void *) drwrap_get_arg(wrapcxt, 0);
        size_t size = (size_t) drwrap_get_arg(wrapcxt, 1);

        realloc_data->passed_addr = passed_addr;
        realloc_data->pc = drwrap_get_func(wrapcxt);
        realloc_data->size = size;

        if (realloc_ctx->pre_realloc_hndlr) {
            realloc_data->addr = NULL;
            realloc_data->return_pc = NULL;
            realloc_ctx->pre_realloc_hndlr(realloc_data);
        }

        // Send the alloc_data to post function.
        *user_data = realloc_data;
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
static void ub_ev_heap_realloc_wrap_realloc_post(void *wrapcxt, void *user_data) {

    ub_ev_realloc_data_t *realloc_data = (ub_ev_realloc_data_t *) user_data;

    if (realloc_data != NULL) {

        void *drcontext = dr_get_current_drcontext();
        DR_ASSERT(ub_ev_heap_routine_entry_checker_is_set(drcontext));
        ub_ev_heap_routine_entry_checker_unset(drcontext);
        DR_ASSERT(!ub_ev_heap_routine_entry_checker_is_set(drcontext));

        if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

            if (realloc_ctx->post_realloc_hndlr) {
                realloc_data->addr = (void *) drwrap_get_retval(wrapcxt);

                DR_TRY_EXCEPT(drcontext, {
                    realloc_data->return_pc = drwrap_get_retaddr(wrapcxt)
                    ;
                },
                { dr_fprintf(STDERR, "Warning: Failed to retrieve retaddr"); });

                realloc_ctx->post_realloc_hndlr(realloc_data);
            }
        }

        dr_global_free(realloc_data, sizeof(ub_ev_realloc_data_t));

    }
}
