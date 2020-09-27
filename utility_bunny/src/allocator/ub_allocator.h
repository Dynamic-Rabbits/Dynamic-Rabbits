/*
 * ub_allocator.h
 *
 *  Created on: 20 Mar 2019
 *      Author: john
 */

#ifndef ALLOCATOR_UB_ALLOCATOR_H_
#define ALLOCATOR_UB_ALLOCATOR_H_

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include  <stdint.h>

void * ub_create_fixed_allocator(size_t init_pool_size, size_t elem_size);

void ub_destroy_fixed_allocator(void *allocator_ctx_opaque);

void *ub_allocate(void *allocator_ctx_opaque);

void ub_deallocate(void *allocator_ctx_opaque, void *free_val);

void ub_insert_allocation(void *allocator_ctx_opaque, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t dest_reg,
        reg_id_t scratch_reg);

void ub_insert_dealloation(void *allocator_ctx_opaque, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t free_reg,
        reg_id_t scratch_reg, reg_id_t scratch_reg2);

#endif /* ALLOCATOR_UB_ALLOCATOR_H_ */
