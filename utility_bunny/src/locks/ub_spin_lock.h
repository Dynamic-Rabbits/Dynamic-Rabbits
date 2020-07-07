/*
 * ub_spin_lock.h
 *
 *  Created on: 20 Mar 2019
 *      Author: john
 */

#ifndef LOCKS_UB_SPIN_LOCK_H_
#define LOCKS_UB_SPIN_LOCK_H_

#include "dr_api.h"
#include "drmgr.h"

void ub_sl_try_and_lock(volatile int *spin_lock);

void ub_sl_unlock(volatile int *spin_lock);

void ub_sl_insert_try_and_lock(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t xax_scratch, reg_id_t reg_scratch,
        int *spin_lock);

void ub_sl_insert_unlock(void *drcontext, instrlist_t *ilist, instr_t *where,
        int *spin_lock);

#endif /* LOCKS_UB_SPIN_LOCK_H_ */
