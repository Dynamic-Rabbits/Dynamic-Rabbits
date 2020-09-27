/**
 *  @file ub_event_alloc.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_HEAP_ALLOC_UB_EVENT_ALLOC_H_
#define EVENTS_HEAP_ALLOC_UB_EVENT_ALLOC_H_

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"

/**
 *  @struct ub_alloc_data_t
 *
 *  @var ub_alloc_data_t::addr The addr of the allocated block.
 *  @var ub_alloc_data_t::size The size of the allocated block.
 */
typedef struct {
	void *addr;
	size_t size;
	app_pc pc;
    app_pc return_pc;

} ub_ev_alloc_data_t;

/**
 *  Callback function which is triggered upon the successful allocation of
 *  heap memory.
 */
typedef void (*ub_ev_handle_heap_alloc_event_t)(ub_ev_alloc_data_t *alloc_data);

/**
 *  Initialises the context responsible for hooking heap allocation
 *  functions.
 */
void ub_ev_heap_alloc_init_ctx(ub_ev_handle_heap_alloc_event_t pre_alloc_hndlr,
		ub_ev_handle_heap_alloc_event_t post_alloc_hndlr);
/**
 *  Destroys the heap allocation context.
 */
void ub_ev_heap_alloc_destroy_ctx();

#endif /* EVENTS_HEAP_ALLOC_UB_EVENT_ALLOC_H_ */
