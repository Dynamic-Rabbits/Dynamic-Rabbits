/*
 *  @author John F.X. Galea
 */

#include "ib_code_cache.h"
#include "../ib_data.h"
#include "../tls_access/ib_tls_access.h"

#include "utility_bunny.h"
#include <stddef.h>

void *code_cache_manager = NULL;

/**
 *  @struct ib_code_cache_t
 *
 *  A code cache that contains code for instrumenting an instruction.
 *  Instrumentation the need to insert the same instrumentation code after each
 *  app instruction but insteads make a simple jump to the cache (thus reducing size).
 *
 *  @param pc The starting pc to the code cache.
 *  @param The register used to save the return address once the code in the cache is
 *  executed.
 */
typedef struct {

    app_pc pc;
    size_t size;
    ib_insert_hndle_func_t insert_code;

    void *user_data;
    void *spilling_user_data;
    ib_spill_regs_func_t spill_reg_func;
    ib_restore_regs_func_t restore_reg_func;

} ib_code_cache_t;

void ib_code_cache_manager_init() {

    code_cache_manager = ub_list_create();
}

static void ib_destroy_code_cache(void *code_cache_opaque) {

    ib_code_cache_t *code_cache = (ib_code_cache_t *) code_cache_opaque;

    DR_ASSERT(code_cache);
    DR_ASSERT(code_cache->pc);
    DR_ASSERT(code_cache->insert_code);
    DR_ASSERT(code_cache->size > 0);

    dr_nonheap_free(code_cache->pc, code_cache->size);

    dr_global_free(code_cache, sizeof(ib_code_cache_t));
}

void ib_code_cache_manager_destroy() {

    ub_list_destroy(code_cache_manager, ib_destroy_code_cache);
}

static void ib_code_cache_fill(void *drcontext, instrlist_t *ilist,
        ib_insert_hndle_func_t insert_code, void *user_data, void *spill_data) {

    instr_t * where;

    /**
     *  The jmp instr jumps back to the DR's code cache. More specifically,
     *  the next instruction to be executed by the app.
     */
    opnd_t return_data_opnd = ib_tls_get_raw_slot_opnd(
    IB_RAW_SLOT_RET_DATA);
    where = INSTR_CREATE_jmp_ind(drcontext, return_data_opnd);
    instrlist_meta_append(ilist, where);

    // Call function responsible inserting the main code to the cache.
    insert_code(drcontext, ilist, where, NULL, user_data, spill_data);
}

static size_t ib_code_cache_get_size(void *drcontext, void *ilist) {

    app_pc cache_pc;

    /**
     *  Allocate code cache, and set Read-Write-Execute permissions.
     *  The dr_nonheap_alloc function allows you to set permissions.
     */
    cache_pc = (app_pc) dr_nonheap_alloc(dr_page_size() * 4,
    DR_MEMPROT_READ | DR_MEMPROT_WRITE | DR_MEMPROT_EXEC);

    byte *end = instrlist_encode(drcontext, ilist, cache_pc, true);

    size_t size = end - cache_pc;
    DR_ASSERT(0 < size && size < dr_page_size() * 4);
    dr_nonheap_free((void *) cache_pc, dr_page_size() * 4);

    return size;
}

/**
 * Fills code cache with code. It is a helper function for \p ib_code_cache_init
 */
static void *ib_code_cache_create(void *code_cache_manager,
        ib_insert_hndle_data_t *code_cache_data) {

    /* New handler found. Need to create a new code cache. */

    app_pc cache_pc;
    instrlist_t *ilist;
    size_t size;

    void *drcontext = dr_get_current_drcontext();
    if (drcontext == NULL)
        return NULL;

    ilist = instrlist_create(drcontext);

    ib_code_cache_fill(drcontext, ilist, code_cache_data->user_instrum_func,
            code_cache_data->user_data, code_cache_data->spilling_user_data);

	size = ib_code_cache_get_size(drcontext, ilist);

    /*
     *  Allocate code cache, and set Read-Write-Execute permissions.
     *  The dr_nonheap_alloc function allows you to set permissions.
     */
    cache_pc = (app_pc) dr_nonheap_alloc(size,
    DR_MEMPROT_READ | DR_MEMPROT_WRITE | DR_MEMPROT_EXEC);

    byte *end = instrlist_encode(drcontext, ilist, cache_pc, true);

    instrlist_clear_and_destroy(drcontext, ilist);

    DR_ASSERT(end - cache_pc <= (int ) size);

    /**
     * Change the permission Read-Write-Execute permissions.
     * In particular, we do not need to write the the private cache.
     */
    dr_memory_protect(cache_pc, size, DR_MEMPROT_READ | DR_MEMPROT_EXEC);

    ib_code_cache_t *code_cache = dr_global_alloc(sizeof(ib_code_cache_t));
    code_cache->pc = cache_pc;
    code_cache->insert_code = code_cache_data->user_instrum_func;
    code_cache->user_data = code_cache_data->user_data;
    code_cache->spilling_user_data = code_cache_data->spilling_user_data;
    code_cache->spill_reg_func = code_cache_data->spill_reg_func;
    code_cache->restore_reg_func = code_cache_data->restore_reg_func;

    code_cache->size = size;

    return code_cache;
}

void *ib_code_cache_init(ib_insert_hndle_data_t *code_cache_data) {

    DR_ASSERT(code_cache_manager);

    /* Create code cache from provided data */
    ib_code_cache_t * code_cache = (ib_code_cache_t *) ib_code_cache_create(
            code_cache_manager, code_cache_data);
    ub_list_insert(code_cache_manager, code_cache);

    return (void *) code_cache;
}

static bool ib_code_cache_exit_comparator(const void *code_cache1_opaque,
        const void *code_cache2_opaque) {

    ib_code_cache_t *code_cache = (ib_code_cache_t *) code_cache1_opaque;
    ib_code_cache_t *code_cache2 = (ib_code_cache_t *) code_cache2_opaque;

    if (code_cache == code_cache2) {

        DR_ASSERT(code_cache->insert_code == code_cache2->insert_code);
        return true;
    }

    return false;
}

void ib_code_cache_exit(void *code_cache_opaque) {

    ib_code_cache_t *code_cache = (ib_code_cache_t *) code_cache_opaque;

    void *code_cache_rem = ub_list_remove(code_cache_manager, code_cache,
            ib_code_cache_exit_comparator);

    DR_ASSERT(code_cache_rem == code_cache_opaque);

    ib_destroy_code_cache(code_cache_opaque);
}

void ib_code_cache_insert_jmp_cache_instr(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *code_cache_opaque) {

    ib_code_cache_t *code_cache = (ib_code_cache_t *) code_cache_opaque;

    void *spill_data = code_cache->spilling_user_data;

    if (code_cache->spill_reg_func)
        code_cache->spill_reg_func(drcontext, ilist, where,
                code_cache->user_data, &spill_data);

    opnd_t opnd;
    instr_t *instr;

    /* Jump to restore label after returning from private code cache. */
    instr_t *return_label = INSTR_CREATE_label(drcontext);

    /* This is the return address for jumping back from lean procedure. */
    opnd_t return_data_opnd = ib_tls_get_raw_slot_opnd(
    IB_RAW_SLOT_RET_DATA);
    instrlist_insert_mov_instr_addr(drcontext, return_label, NULL,
            return_data_opnd, ilist, where, NULL, NULL);

    /* Jump to code cache */
    opnd = opnd_create_pc(code_cache->pc);
    instr = INSTR_CREATE_jmp(drcontext, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    /* Insert restore label. This is obviously placed at the end. */
    instrlist_meta_preinsert(ilist, where, return_label);

    if (code_cache->restore_reg_func)
        code_cache->restore_reg_func(drcontext, ilist, where,
                code_cache->user_data, spill_data);
}

