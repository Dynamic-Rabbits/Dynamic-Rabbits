/*
 * shadow_reg_map_inline.c
 *
 *      Author: john
 */

#include "tb_raw_array_reg_map.h"
#include "../../../../../../tls_access/tb_tls_access.h"
#include "../../tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#include <stddef.h>

void tb_raw_arraymap_insert_load_reg_map(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg) {

    opnd_t opnd = tb_raw_get_tls_raw_slot_opnd(tb_ctx, TB_RAW_SLOT_IDX_MAP);
    opnd_t opnd2 = opnd_create_reg(map_reg);
    instr_t *instr = INSTR_CREATE_mov_ld(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

/*********************************************************************
 * Set taint operator
 */

static void tb_raw_arraymap_taint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *tl_opnd, reg_id_t label_reg, reg_id_t old_reg,
        bool get_old) {

    // Load the old label
    if (get_old) {
        ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, tl_opnd,
                old_reg);
    }

    ub_instrum_mov_st_reg_to_mem_opnd(drcontext, ilist, where, label_reg,
            tl_opnd);
}

void tb_raw_arraymap_insert_set_taint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd, reg_id_t label_reg,
        reg_id_t old_reg, bool get_old) {

    tb_raw_arraymap_taint_helper(drcontext, ilist, where, tl_opnd, label_reg,
            old_reg, get_old);
}

static void tb_simd_arraymap_insert_set_taint_reg_and_get_old_helper(
        void *drcontext, instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t vector_label_reg, reg_id_t vector_old_reg, bool get_old) {

    if (get_old)
        DR_ASSERT(reg_is_xmm(vector_old_reg));

    DR_ASSERT(reg_is_xmm(vector_label_reg));

    // Load old Taint Labels in old reg
    if (get_old) {
        ub_instrum_simd_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, tl_opnd,
                vector_old_reg);
    }

    // Store new taint label in memory!
    ub_instrum_simd_mov_st_reg_to_mem_opnd(drcontext, ilist, where,
            vector_label_reg, tl_opnd);
}

void tb_simd_arraymap_insert_set_taint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t vector_label_reg, reg_id_t vector_old_reg, bool get_old) {

    tb_simd_arraymap_insert_set_taint_reg_and_get_old_helper(drcontext, ilist,
            where, tl_opnd, vector_label_reg, vector_old_reg, get_old);
}

/*********************************************************************
 * Set untaint operator
 */

static void tb_raw_arraymap_untaint_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *tl_opnd, reg_id_t old_reg, bool get_old) {

    if (get_old) {
        ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, tl_opnd,
                old_reg);
    }

    instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, *tl_opnd,
            ilist, where, NULL, NULL);
}

void tb_raw_arraymap_insert_set_untaint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd, reg_id_t old_reg,
        bool get_old) {

    tb_raw_arraymap_untaint_helper(drcontext, ilist, where, tl_opnd, old_reg,
            get_old);
}

static void tb_simd_arraymap_insert_set_untaint_reg_and_get_old_helper(
        void *drcontext, instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t vector_scratch_reg, reg_id_t vector_scratch_reg2, bool get_old) {

    DR_ASSERT(reg_is_xmm(vector_scratch_reg));

    // Load Taint Labels in old reg
    if (get_old) {
        ub_instrum_simd_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, tl_opnd,
                vector_scratch_reg);
    }

    // Clear scratch register
    ub_instrum_simd_clear_reg(drcontext, ilist, where, vector_scratch_reg2);

    // Untaint memory
    ub_instrum_simd_mov_st_reg_to_mem_opnd(drcontext, ilist, where,
            vector_scratch_reg2, tl_opnd);
}

void tb_simd_arraymap_insert_set_untaint_reg_and_get_old(void *drcontext,
        instrlist_t *ilist, instr_t *where, opnd_t *tl_opnd,
        reg_id_t old_vectorised_reg, reg_id_t scratch_vectorised_reg, bool get_old) {

    tb_simd_arraymap_insert_set_untaint_reg_and_get_old_helper(drcontext, ilist,
            where, tl_opnd, old_vectorised_reg, scratch_vectorised_reg, get_old);
}

/*********************************************************************
 * Translation Functions
 */

void tb_raw_arraymap_insert_translate_address(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t reg_id) {

    // Load map
    ub_instrum_lea_base_disp_index(drcontext, ilist, where, map_reg, reg_id,
            offsetof(tb_map_reg_map_t, reg_map), sizeof(void *), reg_id);
}

void tb_raw_arraymap_insert_translate_address_via_id(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        uintptr_t reg_byte_id, reg_id_t dst_reg) {

    DR_ASSERT(reg_byte_id < REG_MAX_VAL);

    // Load map
    ub_instrum_lea_base_disp(drcontext, ilist, where, map_reg,
    offsetof(tb_map_reg_map_t, reg_map) + (sizeof(void *) * reg_byte_id),
            dst_reg);
}

opnd_t tb_raw_arraymap_get_opnd(void *drcontext, reg_id_t map_reg,
        reg_id_t reg_id, uintptr_t reg_byte_id, int disp, opnd_size_t data_size) {

    if (reg_id == DR_REG_NULL) {

        return tb_raw_arraymap_get_opnd_via_id(drcontext, map_reg, reg_byte_id,
                disp, data_size);
    } else {

        return opnd_create_base_disp(map_reg, reg_id, sizeof(void *),
                offsetof(tb_map_reg_map_t, reg_map), data_size);
    }
}

opnd_t tb_raw_arraymap_get_opnd_via_id(void *drcontext, reg_id_t map_reg,
        uintptr_t reg_byte_id, int disp, opnd_size_t data_size) {

    return opnd_create_base_disp(map_reg, DR_REG_NULL, 0,
    offsetof(tb_map_reg_map_t, reg_map) + (sizeof(void *) * reg_byte_id) + disp,
            data_size);
}

/*********************************************************************
 * Get operator
 */

opnd_t tb_raw_arraymap_insert_reg_get_taint_label_opnd(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t reg_id_reg) {

#ifdef X64
    /** Create a base+disp pointer-sized operand. */
    opnd_t mem_opnd = opnd_create_base_disp(map_reg, reg_id_reg, sizeof(void *),
            offsetof(tb_map_reg_map_t, reg_map), OPSZ_8);
#else
    /** Create a base+disp pointer-sized operand. */
    opnd_t mem_opnd = opnd_create_base_disp(map_reg, reg_id_reg, sizeof(void *),
            offsetof(tb_map_reg_map_t, reg_map), OPSZ_4);
#endif

    return mem_opnd;
}

opnd_t tb_raw_arraymap_insert_reg_get_taint_label_opnd_ex(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t reg_id_reg, size_t size) {

    opnd_t mem_opnd = opnd_create_base_disp(map_reg, reg_id_reg, sizeof(void *),
            offsetof(tb_map_reg_map_t, reg_map),
            opnd_size_from_bytes(size * sizeof(void *)));

    return mem_opnd;
}
