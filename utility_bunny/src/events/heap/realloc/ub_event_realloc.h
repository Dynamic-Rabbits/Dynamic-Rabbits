/**
 *  @file ub_event_realloc.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_HEAP_REALLOC_UB_EVENT_REALLOC_H_
#define EVENTS_HEAP_REALLOC_UB_EVENT_REALLOC_H_

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"

/**
 *  @struct ub_realloc_data_t
 *
 *  @var ub_realloc_data_t::addr The addr of the reallocated block.
 *  @var ub_realloc_data_t::passed_addr The passed addr.
 *  @var ub_realloc_data_t::size The size of the reallocated block.
 */
typedef struct {
	void *addr;
	void *passed_addr;
    void *pc;
    void *return_pc;
	size_t size;
} ub_ev_realloc_data_t;

/**
 *  Callback function which is triggered upon the successful allocation of
 *  heap memory.
 */
typedef void (*ub_ev_handle_heap_realloc_event_t)(ub_ev_realloc_data_t *realloc_data);

/**
 *  Initialises the context responsible for hooking heap reallocation
 *  functions.
 */
void ub_ev_heap_realloc_init_ctx(
		ub_ev_handle_heap_realloc_event_t pre_realloc_hndlr,
		ub_ev_handle_heap_realloc_event_t post_realloc_hndlr);
/**
 *  Destroys the heap reallocation context.
 */
void ub_ev_heap_realloc_destroy_ctx();

#endif /* EVENTS_HEAP_REALLOC_UB_EVENT_REALLOC_H_ */
