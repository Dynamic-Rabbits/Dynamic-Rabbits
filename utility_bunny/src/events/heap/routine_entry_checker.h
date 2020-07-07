/**
 *  @file RoutineEntryChecker.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_ROUTINEENTRYCHECKER_H_
#define EVENTS_ROUTINEENTRYCHECKER_H_

#include "dr_api.h"
#include "drmgr.h"

void ub_ev_heap_routine_entry_checker_init();

void ub_ev_heap_routine_entry_checker_destroy();

bool ub_ev_heap_routine_entry_checker_is_set(void *drcontext);

void ub_ev_heap_routine_entry_checker_set(void *drcontext);

void ub_ev_heap_routine_entry_checker_unset();

void ub_ev_heap_wrap_helper(const module_data_t *mod,
        char *func_name, void *user_data,
        void (*pre_func_cb)(void *wrapcxt, INOUT void **user_data),
        void (*post_func_cb)(void *wrapcxt, void *user_data));

#endif /* EVENTS_ROUTINEENTRYCHECKER_H_ */
