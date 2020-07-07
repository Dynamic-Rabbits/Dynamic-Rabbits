/*
 * ub_allocator.c
 *
 *      Author: john
 */

#include "ub_allocator.h"

#include "../instrumentation/ub_instrum_insert.h"

#include <stddef.h> /* offsetof */
#include <signal.h>

#define NUM_ALLOC 25 /* Number of nodes to create when requesting memory */

/**
 * The basic idea is to reuse already allocated nodes, which are maintained in a list.
 *
 * We could have used the ub_list data structure but that has quite a lot
 * of additional information which our allocator does not need.
 *
 * Java folks, this is kinda similar to hydration.
 */

typedef struct free_node_opaque_t {

    void *val;
    struct free_node_opaque_t *next;
    struct free_node_opaque_t *prev;

} free_node_t;

typedef struct {

    void *faulty_page; /* Indicates when to allocate more data */
    size_t elem_size; /* The size of the elements allocated */

    /**
     * TODO: We could perhaps remove the dummy and in the fault
     * just simply go to next instr.
     */

    free_node_t *dummy_to_base; /* Dummy node to go to base from faulty page */
    free_node_t *base;
    free_node_t *curr;
} ub_allocator_ctx_t;

static void ub_allocate_more_memory(ub_allocator_ctx_t *allocator_ctx) {

    /**
     * Called when to allocate more memory.
     * Set up the pointers stored in allocator context correctly.
     */

    for (int i = 0; i < NUM_ALLOC; i++) {

        free_node_t *node = dr_global_alloc(sizeof(free_node_t));
        node->val = dr_global_alloc(allocator_ctx->elem_size);
        node->next = allocator_ctx->base;
        allocator_ctx->base->prev = node;
        node->prev = (free_node_t *) allocator_ctx->faulty_page;
        allocator_ctx->dummy_to_base->next = node;
        allocator_ctx->base = node;

        if (i == 0)
            allocator_ctx->curr = node;
    }
}

static dr_signal_action_t ub_allocator_event_signal(void *drcontext,
        dr_siginfo_t *info, void *user_data) {

    ub_allocator_ctx_t *allocator_ctx = (ub_allocator_ctx_t *) user_data;

    if (info->sig == SIGSEGV || info->sig == SIGBUS) {

        int next_offset = offsetof(free_node_t, next);
        int val_offset = offsetof(free_node_t, val);

        if ((allocator_ctx->faulty_page + val_offset == info->access_address)
                || (allocator_ctx->faulty_page + next_offset
                        == info->access_address)) {

            instr_t * fault_inst = instr_create(drcontext);
            decode(drcontext, info->raw_mcontext->pc, fault_inst);
            DR_ASSERT(instr_get_opcode(fault_inst) == OP_mov_ld);
            DR_ASSERT(opnd_is_memory_reference(instr_get_src(fault_inst, 0)));

            int disp = opnd_get_disp(instr_get_src(fault_inst, 0));
            reg_id_t base_reg = opnd_get_base(instr_get_src(fault_inst, 0));

            // Check that the fault concerns the faulty page.
            if (disp == val_offset) {

                ub_allocate_more_memory(allocator_ctx);

                // Get the instruction that faulted. This must be a load instruction.
                reg_set_value(base_reg, info->raw_mcontext,
                        (reg_t) (intptr_t) allocator_ctx->curr);

            } else if (disp == next_offset) {

                // Get the instruction that faulted. This must be a load instruction.
                reg_set_value(base_reg, info->raw_mcontext,
                        (reg_t) (intptr_t) allocator_ctx->dummy_to_base);

            } else {
                DR_ASSERT(false);
            }

            instr_destroy(drcontext, fault_inst);

            return DR_SIGNAL_SUPPRESS;
        }
    }

    return DR_SIGNAL_DELIVER;
}

static void init_free_list(ub_allocator_ctx_t *allocator_ctx,
        size_t init_pool_size) {

    allocator_ctx->base = dr_global_alloc(sizeof(free_node_t));
    allocator_ctx->base->val = dr_global_alloc(allocator_ctx->elem_size);
    allocator_ctx->base->next = NULL;
    allocator_ctx->base->prev = (free_node_t *) allocator_ctx->faulty_page;
    allocator_ctx->dummy_to_base = dr_global_alloc(sizeof(free_node_t));
    allocator_ctx->dummy_to_base->next = allocator_ctx->base;
    free_node_t *prev = allocator_ctx->base;
    free_node_t *temp = allocator_ctx->base;

    for (size_t i = 1; i < init_pool_size; i++) {

        temp = dr_global_alloc(sizeof(free_node_t));
        temp->val = dr_global_alloc(allocator_ctx->elem_size);
        temp->next = NULL;
        temp->prev = prev;
        prev->next = temp;
        prev = temp;
    }

    allocator_ctx->curr = prev;
}

/**
 * For now we create an allocator which can only provide data slots of fixed size.
 */
void * ub_create_fixed_allocator(size_t init_pool_size, size_t elem_size) {

    DR_ASSERT(init_pool_size > 0); // Init pool size must be at least of size 1.

    ub_allocator_ctx_t *allocator_ctx = (ub_allocator_ctx_t *) dr_global_alloc(
            sizeof(ub_allocator_ctx_t));

    bool succ = drmgr_register_signal_event_user_data(ub_allocator_event_signal,
            0, allocator_ctx);
    DR_ASSERT(succ);

    allocator_ctx->elem_size = elem_size;
    allocator_ctx->faulty_page = dr_nonheap_alloc(dr_page_size(),
    DR_MEMPROT_NONE);

    init_free_list(allocator_ctx, init_pool_size);

    return allocator_ctx;
}

void ub_destroy_fixed_allocator(void *allocator_ctx_opaque) {

    ub_allocator_ctx_t *allocator_ctx =
            (ub_allocator_ctx_t *) allocator_ctx_opaque;

    if (allocator_ctx->curr->next != NULL){

        free_node_t *debug_temp = allocator_ctx->curr->next;
        int count = 0;
        while (debug_temp) {

            count++;

            debug_temp = debug_temp->next;
        }

	/* Uncomment to identify leaks */
	/* TODO make this a debug option. Keep calm, it's just a prototype */
        //dr_fprintf(STDERR, "There are %d potential live objects\n", count);
        //DR_ASSERT(allocator_ctx->curr->next == NULL);
    }


    free_node_t *temp = allocator_ctx->base;
    free_node_t *temp_next = NULL;

    while (temp) {
        dr_global_free(temp->val, allocator_ctx->elem_size);
        temp_next = temp->next;

        dr_global_free(temp, sizeof(free_node_t));
        temp = temp_next;
    }

    dr_global_free(allocator_ctx->dummy_to_base, sizeof(free_node_t));

    dr_nonheap_free(allocator_ctx->faulty_page, dr_page_size());
    dr_global_free(allocator_ctx, sizeof(ub_allocator_ctx_t));
}

void *ub_allocate(void *allocator_ctx_opaque) {

    ub_allocator_ctx_t *allocator_ctx =
            (ub_allocator_ctx_t *) allocator_ctx_opaque;

    if (allocator_ctx->curr == allocator_ctx->faulty_page)
        ub_allocate_more_memory(allocator_ctx);

    DR_ASSERT(allocator_ctx->curr != allocator_ctx->faulty_page);
    free_node_t * free_node = allocator_ctx->curr;

    /* Get the val of the free node */
    void *val_ptr = free_node->val;
    allocator_ctx->curr = free_node->prev;

    return val_ptr;
}

void ub_deallocate(void *allocator_ctx_opaque, void *free_val) {

    if (free_val == NULL)
        DR_ASSERT(false);

    ub_allocator_ctx_t *allocator_ctx =
            (ub_allocator_ctx_t *) allocator_ctx_opaque;

    free_node_t * free_node;

    if (allocator_ctx->curr == allocator_ctx->faulty_page) {
        free_node = allocator_ctx->dummy_to_base->next;
    } else {
        free_node = allocator_ctx->curr->next;
    }

    DR_ASSERT(free_node);

    /* Free node */
    free_node->val = free_val;

    allocator_ctx->curr = free_node;

}

void ub_insert_allocation(void *allocator_ctx_opaque, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t dest_reg,
        reg_id_t scratch_reg) {

    ub_allocator_ctx_t *allocator_ctx =
            (ub_allocator_ctx_t *) allocator_ctx_opaque;

    /* Load current free node */
    opnd_t allocator_opnd = opnd_create_abs_addr(&(allocator_ctx->curr),
    OPSZ_PTR);
    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &allocator_opnd,
            scratch_reg);

    /* Load the val to reg */
    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where,
            instr_get_app_pc(where), scratch_reg, offsetof(free_node_t, val),
            dest_reg);

    /* Load the prev to reg */
    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, scratch_reg,
            offsetof(free_node_t, prev), scratch_reg);

    /* Set prev to curr */
    ub_instrum_mov_st_reg_to_mem_opnd(drcontext, ilist, where, scratch_reg,
            &allocator_opnd);
}

void ub_insert_dealloation(void *allocator_ctx_opaque, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t free_reg,
        reg_id_t scratch_reg, reg_id_t scratch_reg2) {

    ub_allocator_ctx_t *allocator_ctx =
            (ub_allocator_ctx_t *) allocator_ctx_opaque;

    // The user should take care not to do a double free!
    // Keep calm, it's just a prototype!

    /**
     * Load curr
     */
    opnd_t allocator_opnd = opnd_create_abs_addr(&(allocator_ctx->curr),
    OPSZ_PTR);
    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &allocator_opnd,
            scratch_reg);

    /**
     * Load next
     */
    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where,
            instr_get_app_pc(where), scratch_reg, offsetof(free_node_t, next),
            scratch_reg);

    /**
     * Set the freed val.
     */
    ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, free_reg, scratch_reg,
            offsetof(free_node_t, val));

    ub_instrum_mov_st_reg_to_mem_opnd(drcontext, ilist, where, scratch_reg,
            &allocator_opnd);
}

