/*
 * shadow_mem_map_inline.c
 *
 *      Author: john
 */

#include "tb_raw_umbra_mem_map.h"

#include "../../../../shdw_fault_handlers/tb_umbra_fault_handlers.h"

#include "../../tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../../../../../tls_access/tb_tls_access.h"
#include "umbra.h"
#include "instrumentation_bunny.h"
#include "utility_bunny.h"
#include <signal.h>

/***********************************************************************************
 * Prototypes
 */

static dr_signal_action_t tb_raw_umbra_event_signal(void *drcontext,
        dr_siginfo_t *info, void *user_data);
static void tb_raw_umbra_taint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t label_reg, reg_id_t old_reg, bool get_old);
static void tb_raw_umbra_untaint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t old_reg, bool get_old);
static void tb_raw_umbra_low_on_memory(void *drcontext, void *user_data);

typedef struct {
    void *shdw_addr;
    void * data[4];
} cache_info_t;

/****************************************************************************************
 * RAW UBMRA CREATION
 */

void *tb_raw_umbra_create_mem_map(void *user_data, void **start) {

    umbra_map_t *map = tb_cc_umbra_create_mem_map(user_data, start);
    drmgr_register_signal_event_user_data(tb_raw_umbra_event_signal, 0,
            user_data);
    drmgr_register_low_on_memory_event_user_data(tb_raw_umbra_low_on_memory,
    NULL, (void *) map);

    return map;
}

void tb_raw_umbra_destroy_mem_map(void *map,
        ub_destroy_value_func_t detroy_func, void *user_data) {

    tb_cc_umbra_destroy_mem_map(map, detroy_func, user_data);
    drmgr_unregister_signal_event_user_data(tb_raw_umbra_event_signal);
    drmgr_unregister_low_on_memory_event_user_data(tb_raw_umbra_low_on_memory);
}

/***********************************************************************************
 * Lazy Approach (Init on Fault, just like DR Memory)
 */

/**
 *  On 32-bit, UMBRA points translated addresses which are unmapped, to a single special block.
 *  When the taint bunny accesses such the special block, UMBRA faults. We
 *  implement lazy initialisation, by handling the fault, so that the translated address now
 *  refers to allocated data.
 *
 *  A similar approach is taken by DrMemory.
 *
 *  We perform the following steps.
 *    1) Catch the fault, and determine whether it was caused due to an access of a special block.
 *    2) Get the app address, which is unmapped in UMBRA
 *    3) Create a normal (allocated) block and map it to the app address.
 *    4) Suppress the signal, so that the faulted instruction is executed again.
 *
 *    Much of this functionality is in tb_umbra_event_signal_handler
 */
static dr_signal_action_t tb_raw_umbra_event_signal(void *drcontext,
        dr_siginfo_t *info, void *user_data) {

    tb_context_t *tb_ctx = (tb_context_t *) user_data;
    return tb_umbra_event_signal_handler(drcontext, info, tb_ctx,
            tb_ctx->mem_map);
}

/***********************************************************************************
 * Address Translation
 */

void tb_umbra_insert_translate_address(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t scratch_reg) {

    umbra_map_t *map = (umbra_map_t *) tb_ctx->mem_map;

    int num_regs;
    umbra_num_scratch_regs_for_translation(&num_regs);
    DR_ASSERT(num_regs == 1);

// Translate address to shadow address. X86_32 requires 1 scratch.
    drmf_status_t status = umbra_insert_app_to_shadow(drcontext, map, ilist,
            where, addr_reg, &scratch_reg, 1);
    DR_ASSERT(status == DRMF_SUCCESS);
}

/***********************************************************************************
 * Map Operations - Set taint and get old
 */

static void tb_raw_umbra_taint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t label_reg, reg_id_t old_reg, bool get_old) {

    if (get_old)
        DR_ASSERT(reg_is_gpr(old_reg));

    DR_ASSERT(reg_is_gpr(label_reg));

    opnd_t opnd;
    instr_t *instr;

    /**
     * Many may not know that I created many taint engines before the current state of the Taint Bunny.
     * One involved using the xchg instruction in order to swap between the old and new label in
     * shadow memory. However, this was a mistake in terms of performance, as xchg with memory and a reg
     * involves an implicit lock!!!! This slow downed speed dramatically.
     */

    if (get_old) {
        // Load the old label
        opnd = opnd_create_reg(old_reg);
        instr = INSTR_CREATE_mov_ld(drcontext, opnd, *tl_opnd);
        instr_set_translation(instr, translation_pc);
        instrlist_meta_preinsert(ilist, where, instr);
    }

    /**
     * Don't write if equal so that we can better preserve umbra shadow optimisation!
     *
     * TODO make this a compile option allowing the user to select better memory
     * performance over computation performance.
     *
     * Keep calm, it's a prototype!
     */

// Store the new label
    opnd = opnd_create_reg(label_reg);
    instr = INSTR_CREATE_mov_st(drcontext, *tl_opnd, opnd);
    instr_set_translation(instr, translation_pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

#ifdef TB_MEM_CONSERVATIVE
static void tb_raw_umbra_conservative_taint_helper(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation_pc,
        opnd_t *tl_opnd, reg_id_t label_reg, reg_id_t old_reg) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    instr_t* skip_label = INSTR_CREATE_label(drcontext);

    // Load the old label
    opnd = opnd_create_reg(old_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, opnd, *tl_opnd);
    instr_set_translation(instr, translation_pc);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd = opnd_create_reg(old_reg);
    opnd2 = opnd_create_reg(label_reg);
    instr = INSTR_CREATE_cmp(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd_create_instr(skip_label));
    instrlist_meta_preinsert(ilist, where, instr);

    tb_raw_umbra_taint_helper(drcontext, ilist, where, translation_pc, tl_opnd,
            label_reg, old_reg, false /*Already loaded*/);

    instrlist_meta_preinsert(ilist, where, skip_label);
}
#endif

void tb_raw_umbra_insert_set_taint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t label_reg, reg_id_t old_reg, bool get_old) {

// Assumes that the address has already been translated. If a fault occurs, we
// will retrieve the machine context, and recompute the app address. This
// saves us a register because we do not need to store the addr.

#ifdef TB_MEM_CONSERVATIVE
    tb_raw_umbra_conservative_taint_helper(drcontext, ilist, where, pc, tl_opnd,
            label_reg, old_reg);
#else
    tb_raw_umbra_taint_helper(drcontext, ilist, where, pc, tl_opnd, label_reg,
            old_reg, get_old);
#endif

}

static void tb_simd_umbra_taint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t vector_label_reg, reg_id_t vector_old_reg, bool get_old) {

    if (get_old)
        DR_ASSERT(reg_is_xmm(vector_old_reg));

    DR_ASSERT(reg_is_xmm(vector_label_reg));
    DR_ASSERT(tl_opnd != NULL);

    if (get_old)
        ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
                tl_opnd, vector_old_reg, translation_pc);

// Set to memory
    ub_instrum_simd_mov_st_reg_to_mem_opnd_ex(drcontext, ilist, where,
            vector_label_reg, tl_opnd, translation_pc);
}

#ifdef TB_MEM_CONSERVATIVE
static void tb_simd_umbra_conservative_taint_helper(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation_pc,
        opnd_t *tl_opnd, reg_id_t vector_label_reg, reg_id_t vector_old_reg,
        bool get_old) {

    instr_t* skip_label = INSTR_CREATE_label(drcontext);

    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where, tl_opnd,
            vector_old_reg, translation_pc);

    opnd_t opnd = opnd_create_reg(vector_old_reg);
    opnd_t opnd2 = opnd_create_reg(vector_label_reg);
    instr_t *instr = INSTR_CREATE_por(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd = opnd_create_reg(vector_old_reg);
    instr = INSTR_CREATE_ptest(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd_create_instr(skip_label));
    instrlist_meta_preinsert(ilist, where, instr);

    tb_simd_umbra_taint_helper(drcontext, ilist, where, translation_pc, tl_opnd,
            vector_label_reg, vector_old_reg, get_old);

    instrlist_meta_preinsert(ilist, where, skip_label);
}
#endif

void tb_simd_umbra_insert_set_taint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t vector_label_reg, reg_id_t vector_old_reg, bool get_old) {

#ifdef TB_MEM_CONSERVATIVE
    tb_simd_umbra_conservative_taint_helper(drcontext, ilist, where, pc,
            tl_opnd, vector_label_reg, vector_old_reg, get_old);
#else
    tb_simd_umbra_taint_helper(drcontext, ilist, where, pc, tl_opnd,
            vector_label_reg, vector_old_reg, get_old);

#endif
}

/***********************************************************************************
 * Map Operations - Set UNtaint and get old
 */

static void tb_raw_umbra_untaint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t old_reg, bool get_old) {

    opnd_t opnd;
    instr_t *instr;

// Load the old label
    if (get_old) {
        opnd = opnd_create_reg(old_reg);
        instr = INSTR_CREATE_mov_ld(drcontext, opnd, *tl_opnd);
        instr_set_translation(instr, translation_pc);
        instrlist_meta_preinsert(ilist, where, instr);
    }

// Simply NULL it!
// TODO use instrlist_insert_mov_immed_ptrsz but you will need to modify it to take translation.
    opnd = opnd_create_immed_uint((ptr_uint_t) NULL, OPSZ_4);
    instr = INSTR_CREATE_mov_st(drcontext, *tl_opnd, opnd);
    instr_set_translation(instr, translation_pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

#ifdef TB_MEM_CONSERVATIVE

static void tb_raw_umbra_conservative_untaint_helper(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation_pc,
        opnd_t *tl_opnd, reg_id_t old_reg) {

    opnd_t opnd;
    instr_t *instr;

// Load the old label
    opnd = opnd_create_reg(old_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, opnd, *tl_opnd);
    instr_set_translation(instr, translation_pc);
    instrlist_meta_preinsert(ilist, where, instr);

    instr_t* skip_label = INSTR_CREATE_label(drcontext);

    /**
     * Don't write if equal so that we can better preserve umbra shadow optimisation!
     */

    opnd = opnd_create_reg(old_reg);
    instr = INSTR_CREATE_test(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd_create_instr(skip_label));
    instrlist_meta_preinsert(ilist, where, instr);

    tb_raw_umbra_untaint_helper(drcontext, ilist, where, translation_pc,
            tl_opnd, old_reg, false /* Already loaded */);

    instrlist_meta_preinsert(ilist, where, skip_label);
}
#endif

void tb_raw_umbra_insert_set_untaint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t old_reg, bool get_old) {

#ifdef TB_MEM_CONSERVATIVE
    tb_raw_umbra_conservative_untaint_helper(drcontext, ilist, where, pc,
            tl_opnd, old_reg);
#else
    tb_raw_umbra_untaint_helper(drcontext, ilist, where, pc, tl_opnd, old_reg,
            get_old);

#endif

}

static void tb_simd_umbra_untaint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t vector_old_reg, reg_id_t vector_scratch_reg, bool get_old) {

    if (get_old)
        DR_ASSERT(reg_is_xmm(vector_old_reg));

    DR_ASSERT(reg_is_xmm(vector_scratch_reg));
    DR_ASSERT(tl_opnd != NULL);

    if (get_old) {
        // Load the old label
        ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
                tl_opnd, vector_old_reg, translation_pc);
    }

    ub_instrum_simd_clear_reg(drcontext, ilist, where, vector_scratch_reg);

// Set to memory
    ub_instrum_simd_mov_st_reg_to_mem_opnd_ex(drcontext, ilist, where,
            vector_scratch_reg, tl_opnd, translation_pc);
}

#ifdef TB_MEM_CONSERVATIVE

static void tb_simd_umbra_conservative_untaint_helper(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation_pc,
        opnd_t *tl_opnd, reg_id_t vector_old_reg, reg_id_t vector_scratch_reg) {

    opnd_t opnd;
    instr_t *instr;

    instr_t* skip_label = INSTR_CREATE_label(drcontext);

    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where, tl_opnd,
            vector_old_reg, translation_pc);

    opnd = opnd_create_reg(vector_old_reg);
    instr = INSTR_CREATE_ptest(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd_create_instr(skip_label));
    instrlist_meta_preinsert(ilist, where, instr);

    tb_simd_umbra_untaint_helper(drcontext, ilist, where, translation_pc,
            tl_opnd, vector_old_reg, vector_scratch_reg,
            false /*Already loaded */);

    instrlist_meta_preinsert(ilist, where, skip_label);
}
#endif

void tb_simd_umbra_insert_set_untaint_mem_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc, opnd_t *tl_opnd,
        reg_id_t vector_old_reg, reg_id_t vector_scratch_reg, bool get_old) {

#ifdef TB_MEM_CONSERVATIVE

    tb_simd_umbra_conservative_untaint_helper(drcontext, ilist, where, pc,
            tl_opnd, vector_old_reg, vector_scratch_reg);

#else
    tb_simd_umbra_untaint_helper(drcontext, ilist, where, pc, tl_opnd,
            vector_old_reg, vector_scratch_reg, get_old);
#endif

}

/****************************************************************************
 * Getters
 */

void tb_raw_umbra_insert_get_mem(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t label_reg) {

    instr_t *instr;
    opnd_t opnd;

    opnd = opnd_create_reg(label_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, opnd, *tl_opnd);
    instr_set_translation(instr, translation_pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

void tb_simd_umbra_insert_get_mem(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc translation_pc, opnd_t *tl_opnd,
        reg_id_t vector_scratch_reg) {

    DR_ASSERT(reg_is_xmm(vector_scratch_reg));
    DR_ASSERT(tl_opnd != NULL);

// Load the old label
    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where, tl_opnd,
            vector_scratch_reg, translation_pc);
}

typedef struct {
    int n;
    int t;
    int m;

} block_info_t;

static bool tb_map_check_data(umbra_map_t *map,
        umbra_shadow_memory_info_t *info, void *user_data) {

    if (info->shadow_type == UMBRA_SHADOW_MEMORY_TYPE_NORMAL) {

        block_info_t *block_info = (block_info_t *) user_data;

        uintptr_t base = (uintptr_t) info->shadow_base;

        bool found_non_null = false;

        for (uintptr_t addr = base; addr < base + info->shadow_size; addr +=
                sizeof(void *)) {

            // Extract the label from shadow memory
            void *label;
            memcpy(&label, (void *) addr, sizeof(void *));

            // If label is not null, destroy it!
            if (label) {
                found_non_null = true;
                break;
            }
        }

        if (!found_non_null) {
            block_info->n += 1;
        } else {
            block_info->t += 1;

        }

        block_info->m += 1;

    }

    return true;
}

void tb_cc_umbra_check_null_mem_map(void *map_opaque) {

    umbra_map_t * map = (umbra_map_t *) map_opaque;

    block_info_t block_info = { 0, 0, 0 };

// Iterate through memory and destroy shadow data.
    umbra_iterate_shadow_memory(map, (void *) &block_info, tb_map_check_data);

    dr_fprintf(STDERR, "-----------------------------------------\n");
    dr_fprintf(STDERR, "Number of all NULL blocks: %d/%d\n", block_info.n,
            block_info.m);
    dr_fprintf(STDERR, "Number of all NON NULL blocks: %d/%d\n", block_info.t,
            block_info.m);
}

void tb_raw_umbra_low_on_memory(void *drcontext, void *map_opaque) {

    dr_fprintf(STDERR, "RUNNING OUT OF MEMORY!\n");
    tb_cc_umbra_check_null_mem_map(map_opaque);

    /* Potential UAF - I'll fix later */
    umbra_collect_redundant_blocks((umbra_map_t *) map_opaque);

    tb_cc_umbra_check_null_mem_map(map_opaque);
}

