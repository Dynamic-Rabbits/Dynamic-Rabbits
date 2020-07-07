/**
 *  @file ub_event_alloc.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_event_alloc.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drwrap.h"
#include "../routine_entry_checker.h"
#include "../../../datastructs/sets/ub_str_hashset.h"
#include <string.h>
#include <stdint.h>

/***************************************************************************
 *  Structs
 */

/**
 *  @struct heap_alloc_ctx_t Context for hooking allocations.
 *
 *  @var heap_alloc_ctx_t::alloc_hndlr The cb to be triggered upon an allocation.
 */
typedef struct {

    ub_ev_handle_heap_alloc_event_t pre_alloc_hndlr;
    ub_ev_handle_heap_alloc_event_t post_alloc_hndlr;
} heap_alloc_ctx_t;

typedef struct {

    void **addr_loc;
    ub_ev_alloc_data_t alloc_data;
} posix_memalign_data_t;

/*
 *  Since DrWrap only allows us to insert the same function cb once, we only
 *  support one instantiation.
 */
heap_alloc_ctx_t *alloc_ctx = NULL;

/***************************************************************************
 *  Prototypes
 */

static void ub_ev_heap_alloc_module_load_event(void *drcontext,
        const module_data_t *mod, bool loaded);
static void ub_ev_heap_alloc_wrap_malloc_pre(void *wrapcxt, void **user_data);
static void ub_ev_heap_alloc_wrap_calloc_pre(void *wrapcxt, void **user_data);
static void ub_ev_heap_alloc_wrap_memalign_pre(void *wrapcxt, void **user_data);
static void ub_ev_heap_alloc_wrap_malloc_post(void *wrapcxt, void *user_data);

static void ub_ev_heap_alloc_wrap_posix_memalign_pre(void *wrapcxt,
        void **user_data);
static void ub_ev_heap_alloc_wrap_posix_memalign_post(void *wrapcxt,
        void *user_data);

/***************************************************************************
 *  Implementation
 */

void ub_ev_heap_alloc_init_ctx(ub_ev_handle_heap_alloc_event_t pre_alloc_hndlr,
        ub_ev_handle_heap_alloc_event_t post_alloc_hndlr) {

    drmgr_init();
    drwrap_init();

    ub_ev_heap_routine_entry_checker_init();

    alloc_ctx = dr_global_alloc(sizeof(heap_alloc_ctx_t));
    alloc_ctx->pre_alloc_hndlr = pre_alloc_hndlr;
    alloc_ctx->post_alloc_hndlr = post_alloc_hndlr;

    drmgr_register_module_load_event(ub_ev_heap_alloc_module_load_event);
}

void ub_ev_heap_alloc_destroy_ctx() {

    ub_ev_heap_routine_entry_checker_destroy();
    dr_global_free(alloc_ctx, sizeof(heap_alloc_ctx_t));

    drmgr_unregister_module_load_event(ub_ev_heap_alloc_module_load_event);

    drwrap_exit();
    drmgr_exit();
}

/**
 *  Called upon the loading of a module. Used to wrap malloc.
 */
static void ub_ev_heap_alloc_module_load_event(void *drcontext,
        const module_data_t *mod, bool loaded) {

    ub_ev_heap_wrap_helper(mod, "malloc", NULL,
            ub_ev_heap_alloc_wrap_malloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "calloc", NULL,
            ub_ev_heap_alloc_wrap_calloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "valloc", NULL,
            ub_ev_heap_alloc_wrap_malloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "pvalloc", NULL,
            ub_ev_heap_alloc_wrap_malloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "__libc_malloc", NULL,
            ub_ev_heap_alloc_wrap_malloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "__libc_calloc", NULL,
            ub_ev_heap_alloc_wrap_calloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "__libc_valloc", NULL,
            ub_ev_heap_alloc_wrap_malloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "__libc_pvalloc", NULL,
            ub_ev_heap_alloc_wrap_malloc_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "memalign", NULL,
            ub_ev_heap_alloc_wrap_memalign_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "__libc_memalign", NULL,
            ub_ev_heap_alloc_wrap_memalign_pre,
            ub_ev_heap_alloc_wrap_malloc_post);

    ub_ev_heap_wrap_helper(mod, "posix_memalign", NULL,
            ub_ev_heap_alloc_wrap_posix_memalign_pre,
            ub_ev_heap_alloc_wrap_posix_memalign_post);

    //TODO Wrap more allocation functions! Maybe TCMalloc?

    /* TODO: A long time ago, I implemented a very simply taint engine called SUDUTA.
     * It was crap compared to the DBs. However, one feature of SUDUTA was its ability
     * to discover custom memory allocators.
     *
     * Maybe re-implement?
     *
     */
}

/**
 *  Called prior malloc. Used to obtain the size of the requested allocation.
 */
static void ub_ev_heap_alloc_wrap_malloc_pre(void *wrapcxt, void **user_data) {

    void *drcontext = dr_get_current_drcontext();

    if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

        ub_ev_alloc_data_t *alloc_data = dr_global_alloc(
                sizeof(ub_ev_alloc_data_t));

        size_t size = (size_t) drwrap_get_arg(wrapcxt, 0);
        alloc_data->size = size;
        alloc_data->pc = drwrap_get_func(wrapcxt);

        // Send the alloc_data to post function.
        // Send the alloc_data to post function.
        *user_data = alloc_data;

        if (alloc_ctx->pre_alloc_hndlr != NULL) {
            alloc_data->addr = NULL;
            alloc_ctx->pre_alloc_hndlr(alloc_data);
        }

        ub_ev_heap_routine_entry_checker_set(drcontext);
        return;
    }

    *user_data = NULL;
}

/**
 *  Called prior calloc. Used to obtain the size of the requested allocation.
 */
static void ub_ev_heap_alloc_wrap_calloc_pre(void *wrapcxt, void **user_data) {

    void *drcontext = dr_get_current_drcontext();

    if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

        ub_ev_alloc_data_t *alloc_data = dr_global_alloc(
                sizeof(ub_ev_alloc_data_t));

        size_t number = (size_t) drwrap_get_arg(wrapcxt, 0);
        size_t elem_size = (size_t) drwrap_get_arg(wrapcxt, 1);

        alloc_data->size = number * elem_size;
        dr_mcontext_t * ctx = drwrap_get_mcontext(wrapcxt);
        alloc_data->pc = ctx->pc;

        // Send the alloc_data to post function.
        *user_data = alloc_data;

        if (alloc_ctx->pre_alloc_hndlr != NULL) {
            alloc_data->addr = NULL;
            alloc_ctx->pre_alloc_hndlr(alloc_data);
        }

        ub_ev_heap_routine_entry_checker_set(drcontext);
        return;
    }

    *user_data = NULL;
}

/**
 *  Called prior memalign. Used to obtain the size of the requested allocation.
 */
static void ub_ev_heap_alloc_wrap_memalign_pre(void *wrapcxt, void **user_data) {

    void *drcontext = dr_get_current_drcontext();

    if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

        ub_ev_alloc_data_t *alloc_data = dr_global_alloc(
                sizeof(ub_ev_alloc_data_t));

        /* Select second index because first stores the alignment */
        size_t size = (size_t) drwrap_get_arg(wrapcxt, 1);
        alloc_data->size = size;
        alloc_data->pc = drwrap_get_func(wrapcxt);

        // Send the alloc_data to post function.
        // Send the alloc_data to post function.
        *user_data = alloc_data;

        if (alloc_ctx->pre_alloc_hndlr != NULL) {
            alloc_data->addr = NULL;
            alloc_ctx->pre_alloc_hndlr(alloc_data);
        }

        ub_ev_heap_routine_entry_checker_set(drcontext);
        return;
    }

    *user_data = NULL;
}

static void ub_ev_heap_alloc_wrap_posix_memalign_pre(void *wrapcxt,
        void **user_data) {

    void *drcontext = dr_get_current_drcontext();

    if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

        posix_memalign_data_t *memalign_data = dr_global_alloc(
                sizeof(posix_memalign_data_t));

        void **alloc_addr = (void **) drwrap_get_arg(wrapcxt, 0);
        memalign_data->addr_loc = alloc_addr;

        size_t size = (size_t) drwrap_get_arg(wrapcxt, 2);
        memalign_data->alloc_data.size = size;
        memalign_data->alloc_data.pc = drwrap_get_func(wrapcxt);

        // Send the alloc_data to post function.
        *user_data = memalign_data;

        if (alloc_ctx->pre_alloc_hndlr != NULL) {
            memalign_data->alloc_data.addr = NULL;
            alloc_ctx->pre_alloc_hndlr(&(memalign_data->alloc_data));
        }

        ub_ev_heap_routine_entry_checker_set(drcontext);
        return;
    }

    *user_data = NULL;
}

/**
 *  Called after malloc/calloc. Used to obtain the addr and call the cb.
 *
 *  @param user_data The alloc_data containing the size of the allocation.
 */
static void ub_ev_heap_alloc_wrap_malloc_post(void *wrapcxt, void *user_data) {

    ub_ev_alloc_data_t *alloc_data = (ub_ev_alloc_data_t *) user_data;

    if (alloc_data != NULL) {

        void *drcontext = dr_get_current_drcontext();

        DR_ASSERT(ub_ev_heap_routine_entry_checker_is_set(drcontext));
        ub_ev_heap_routine_entry_checker_unset(drcontext);

        DR_ASSERT(!ub_ev_heap_routine_entry_checker_is_set(drcontext));

        if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

            void *addr = (void *) drwrap_get_retval(wrapcxt);

            if (addr != NULL && alloc_ctx->post_alloc_hndlr) {

                DR_TRY_EXCEPT(drcontext, {
                    alloc_data->return_pc = drwrap_get_retaddr(wrapcxt)
                    ;
                },
                { dr_fprintf(STDERR, "Warning: Failed to retrieve retaddr"); });

                alloc_data->addr = addr;
                alloc_ctx->post_alloc_hndlr(alloc_data);
            }
        }

        dr_global_free(alloc_data, sizeof(ub_ev_alloc_data_t));
    }
}

static void ub_ev_heap_alloc_wrap_posix_memalign_post(void *wrapcxt,
        void *user_data) {

    posix_memalign_data_t *memalign_data = (posix_memalign_data_t *) user_data;

    if (memalign_data != NULL) {

        void *drcontext = dr_get_current_drcontext();

        DR_ASSERT(ub_ev_heap_routine_entry_checker_is_set(drcontext));
        ub_ev_heap_routine_entry_checker_unset(drcontext);
        DR_ASSERT(!ub_ev_heap_routine_entry_checker_is_set(drcontext));

        if (!ub_ev_heap_routine_entry_checker_is_set(drcontext)) {

            void *addr = *(memalign_data->addr_loc);

            if (addr != NULL && alloc_ctx->post_alloc_hndlr) {

                DR_TRY_EXCEPT(drcontext,
                        {
                            memalign_data->alloc_data.return_pc =
                                    drwrap_get_retaddr(wrapcxt)
                            ;
                        }
                        ,
                        { dr_fprintf(STDERR, "Warning: Failed to retrieve retaddr"); });

                memalign_data->alloc_data.addr = addr;
                alloc_ctx->post_alloc_hndlr(&(memalign_data->alloc_data));
            }
        }

        dr_global_free(memalign_data, sizeof(posix_memalign_data_t));
    }
}
