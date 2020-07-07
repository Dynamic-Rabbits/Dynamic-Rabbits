/**
 *  @file ub_event_dealloc.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_HEAP_DEALLOC_UB_EVENT_DEALLOC_H_
#define EVENTS_HEAP_DEALLOC_UB_EVENT_DEALLOC_H_

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"

/**
 *  @struct ub_dealloc_data_t
 *
 *  @var ub_dealloc_data_t::addr The addr of the deallocated block.
 */
typedef struct {
	void *addr;
    void *pc;
    void *return_pc;
} ub_ev_dealloc_data_t;

/**
 *  Callback function which is triggered upon the successful deallocation of
 *  heap memory.
 */
typedef void (*ub_ev_handle_heap_dealloc_event_t)(ub_ev_dealloc_data_t *dealloc_data);

/**
 *  Initialises the context responsible for hooking heap deallocation
 *  functions.
 */
void ub_ev_heap_dealloc_init_ctx(ub_ev_handle_heap_dealloc_event_t pre_dealloc_hndlr,
		ub_ev_handle_heap_dealloc_event_t post_dealloc_hndlr);

/**
 *  Destroys the heap deallocation context.
 */
void ub_ev_heap_dealloc_destroy_ctx();


#endif /* EVENTS_HEAP_DEALLOC_UB_EVENT_DEALLOC_H_ */
