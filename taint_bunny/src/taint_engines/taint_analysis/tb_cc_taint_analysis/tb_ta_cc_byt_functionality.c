/*
 *  @file tb_tracker_helper.c
 *
 *  @author John F.X. Galea
 */

#include "tb_ta_cc_byt_functionality.h"
#include "../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#define MAX_TAINT_SIZE 4092

/**********************************************************************************
 * Taint Introduction (Clean Call)
 ***********************************************************************************/

void tb_ta_cc_intro_taint_mem(tb_context_t *tb_ctx, uintptr_t addr,
        void *taint_label) {

    if (!taint_label)
        return;

    bool succ = false;

    // increment the taint label
    if (tb_ctx->new_ref_func)
        tb_ctx->new_ref_func(taint_label);

    void *old_taint_label = tb_umbra_set_taint_mem_and_get_old(tb_ctx->mem_map,
            addr, taint_label, &succ);

    if (succ) {

        if (tb_ctx->intro_taint_mem_func)
            tb_ctx->intro_taint_mem_func(addr, taint_label);

        if (old_taint_label) {

            if (tb_ctx->untaint_mem_func)
                tb_ctx->untaint_mem_func(addr, old_taint_label);

            if (tb_ctx->delete_ref_func)
                tb_ctx->delete_ref_func(old_taint_label);
        }
    } else {

        // WARNING! Missed taint at intro. We need to delete the ref!
        if (tb_ctx->delete_ref_func) {
            tb_ctx->delete_ref_func(taint_label);
        }
    }
}

void tb_ta_cc_intro_taint_mem_block(tb_context_t *tb_ctx, uintptr_t start_addr,
        int block_sz, void *taint_label) {

    if (!taint_label)
        return;

    int size = 0;

    void *new_buff[MAX_TAINT_SIZE];

    /**
     * TODO Try using asm code (rep stosd)
     * Was hitting constraint errors though.
     */

    for (size_t i = 0; i < MAX_TAINT_SIZE; i++) {
        new_buff[i] = taint_label;
    }

    void *old_buff[MAX_TAINT_SIZE];

    while (block_sz > 0) {

        size = (block_sz > MAX_TAINT_SIZE) ? MAX_TAINT_SIZE : block_sz;
        block_sz -= size;
        DR_ASSERT(block_sz >= 0);

        for (int i = 0; i < size; i++) {
            // increment the taint label
            if (tb_ctx->new_ref_func)
                tb_ctx->new_ref_func(taint_label);
        }

        tb_umbra_set_taint_mem_block_and_get_old(tb_ctx->mem_map,
                start_addr + block_sz, size, new_buff, old_buff, size);

        DR_ASSERT(size > 0);
        for (int i = 0; i < size; i++) {

            void *label = old_buff[i];
            if (label) {

                if (tb_ctx->untaint_mem_func)
                    tb_ctx->untaint_mem_func(start_addr + block_sz + i, label);

                if (tb_ctx->delete_ref_func)
                    tb_ctx->delete_ref_func(label);
            }
        }
    }
}

void tb_ta_cc_intro_taint_reg(tb_context_t *tb_ctx, void *map_opaque,
        unsigned int reg_byte_id, void *taint_label) {

    DR_ASSERT(taint_label);

    if (tb_ctx->new_ref_func)
        tb_ctx->new_ref_func(taint_label);

    bool succ = false;
    void *old_taint_label = tb_cc_arraymap_set_taint_reg_and_get_old(map_opaque,
            reg_byte_id, taint_label, &succ);

    if (tb_ctx->intro_taint_reg_func)
        tb_ctx->intro_taint_reg_func(reg_byte_id, taint_label);

    if (old_taint_label) {

        if (tb_ctx->untaint_reg_func)
            tb_ctx->untaint_reg_func(reg_byte_id, old_taint_label);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label);
    }
}

/**********************************************************************************
 * Taint Propagation (Clean Call)
 ***********************************************************************************/

void tb_ta_cc_set_untaint_mem(tb_context_t *tb_ctx, uintptr_t addr) {

    bool succ = false;
    void *old_taint_label = tb_umbra_set_untaint_mem_and_get_old(
            tb_ctx->mem_map, addr, &succ);

    if (old_taint_label && succ) {

        if (tb_ctx->untaint_mem_func)
            tb_ctx->untaint_mem_func(addr, old_taint_label);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label);
    }
}

void tb_ta_cc_set_untaint_mem_block(tb_context_t *tb_ctx, uintptr_t start_addr,
        size_t block_sz) {

    /* We buffer this functionality */

    size_t size = 0;

    void *shadow_buff[MAX_TAINT_SIZE];

    while (block_sz > 0) {

        size = (block_sz > MAX_TAINT_SIZE) ? MAX_TAINT_SIZE : block_sz;
        block_sz -= size;

        tb_umbra_set_untaint_mem_block_and_get_old(tb_ctx->mem_map,
                start_addr + block_sz, size, shadow_buff, size);

        for (size_t i = 0; i < size; i++) {

            void *label = shadow_buff[i];
            if (label) {

                if (tb_ctx->untaint_mem_func)
                    tb_ctx->untaint_mem_func(start_addr + block_sz + i, label);

                if (tb_ctx->delete_ref_func)
                    tb_ctx->delete_ref_func(label);
            }
        }
    }
}

void tb_ta_cc_set_untaint_reg(tb_context_t *tb_ctx, void *map_opaque,
        unsigned int reg_byte_id) {

    bool succ = false;
    void *old_taint_label = tb_cc_arraymap_set_untaint_reg_and_get_old(
            map_opaque, reg_byte_id, &succ);

    if (old_taint_label && succ) {
        if (tb_ctx->untaint_reg_func)
            tb_ctx->untaint_reg_func(reg_byte_id, old_taint_label);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label);
    }
}

bool tb_ta_cc_prop_mem(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        uintptr_t dst_addr, void *result_label, bool perform_call) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (perform_call && result_label && instr_hndlr_info->pre_prop_func) {
        tb_cc_pre_propagate_func_t pre_prop_func =
                (tb_cc_pre_propagate_func_t) instr_hndlr_info->pre_prop_func;
        pre_prop_func(instr_hndlr_info->tb_ctx);
    }

    bool succ;
    void *old_taint_label = tb_umbra_set_taint_mem_and_get_old(tb_ctx->mem_map,
            dst_addr, result_label, &succ);

    if (succ) {
        if (tb_ctx->new_ref_func && result_label)
            tb_ctx->new_ref_func(result_label);

        if (old_taint_label) {
            if (tb_ctx->untaint_mem_func)
                tb_ctx->untaint_mem_func(dst_addr, old_taint_label);

            if (tb_ctx->delete_ref_func)
                tb_ctx->delete_ref_func(old_taint_label);
        }
    }

    return result_label != NULL && succ;
}

bool tb_ta_cc_prop_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, unsigned int dst_reg, void * result_label,
        bool perform_call) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (perform_call && result_label && instr_hndlr_info->pre_prop_func) {
        tb_cc_pre_propagate_func_t pre_prop_func =
                (tb_cc_pre_propagate_func_t) instr_hndlr_info->pre_prop_func;
        pre_prop_func(instr_hndlr_info->tb_ctx);
    }

    if (tb_ctx->new_ref_func && result_label)
        tb_ctx->new_ref_func(result_label);

    bool succ = false;
    void *old_taint_label = tb_cc_arraymap_set_taint_reg_and_get_old(
            reg_taint_map, dst_reg, result_label, &succ);

    if (old_taint_label) {
        if (tb_ctx->untaint_reg_func)
            tb_ctx->untaint_reg_func(dst_reg, old_taint_label);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label);
    }

    return result_label != NULL;
}

bool tb_ta_cc_prop_xchg_reg_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t reg_id1, void *result_label1,
        uintptr_t reg_id2, void *result_label2, bool perform_call) {

    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (perform_call && (result_label1 || result_label2)
            && instr_hndlr_info->pre_prop_func) {

        tb_cc_pre_propagate_func_t pre_prop_func =
                (tb_cc_pre_propagate_func_t) instr_hndlr_info->pre_prop_func;
        pre_prop_func(instr_hndlr_info->tb_ctx);
    }

    if (tb_ctx->new_ref_func) {
        if (result_label1)
            tb_ctx->new_ref_func(result_label1);

        if (result_label2)
            tb_ctx->new_ref_func(result_label2);
    }

    bool succ = false;
    void *old_taint_label1 = tb_cc_arraymap_set_taint_reg_and_get_old(
            reg_taint_map, reg_id1, result_label2, &succ);

    if (old_taint_label1) {
        if (tb_ctx->untaint_reg_func)
            tb_ctx->untaint_reg_func(reg_id1, old_taint_label1);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label1);
    }

    void *old_taint_label2 = tb_cc_arraymap_set_taint_reg_and_get_old(
            reg_taint_map, reg_id2, result_label1, &succ);

    if (old_taint_label2) {
        if (tb_ctx->untaint_reg_func)
            tb_ctx->untaint_reg_func(reg_id2, old_taint_label2);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label2);
    }

    return result_label1 != NULL || result_label2 != NULL;

}

bool tb_ta_cc_prop_xchg_mem_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t addr_id1, void *result_label1,
        uintptr_t reg_id2, void *result_label2, bool perform_call) {

    bool succ = false;
    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (perform_call && (result_label1 || result_label2)
            && instr_hndlr_info->pre_prop_func) {
        tb_cc_pre_propagate_func_t pre_prop_func =
                (tb_cc_pre_propagate_func_t) instr_hndlr_info->pre_prop_func;
        pre_prop_func(instr_hndlr_info->tb_ctx);
    }

    if (tb_ctx->new_ref_func && result_label1)
        tb_ctx->new_ref_func(result_label1);

    void *old_taint_label1 = tb_umbra_set_taint_mem_and_get_old(tb_ctx->mem_map,
            addr_id1, result_label2, &succ);

    if (succ) {

        if (tb_ctx->new_ref_func) {

            if (result_label2)
                tb_ctx->new_ref_func(result_label2);
        }

        if (old_taint_label1) {
            if (tb_ctx->untaint_mem_func)
                tb_ctx->untaint_mem_func(addr_id1, old_taint_label1);

            if (tb_ctx->delete_ref_func)
                tb_ctx->delete_ref_func(old_taint_label1);
        }
    }

    void *old_taint_label2 = tb_cc_arraymap_set_taint_reg_and_get_old(
            reg_taint_map, reg_id2, result_label1, &succ);

    if (old_taint_label2) {
        if (tb_ctx->untaint_reg_func)
            tb_ctx->untaint_reg_func(reg_id2, old_taint_label2);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label2);
    }

    return succ && (result_label1 != NULL || result_label2 != NULL);

}

bool tb_ta_cc_prop_xchg_mem_mem(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t addr_id1, void *result_label1,
        uintptr_t addr_id2, void *result_label2, bool perform_call) {

    bool succ = false;
    tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

    if (perform_call && (result_label1 || result_label2)
            && instr_hndlr_info->pre_prop_func) {
        tb_cc_pre_propagate_func_t pre_prop_func =
                (tb_cc_pre_propagate_func_t) instr_hndlr_info->pre_prop_func;
        pre_prop_func(instr_hndlr_info->tb_ctx);
    }

    if (tb_ctx->new_ref_func && result_label1)
        tb_ctx->new_ref_func(result_label1);

    void *old_taint_label1 = tb_umbra_set_taint_mem_and_get_old(tb_ctx->mem_map,
            addr_id1, result_label2, &succ);

    if (succ) {

        if (tb_ctx->new_ref_func) {

            if (result_label2)
                tb_ctx->new_ref_func(result_label2);
        }

        if (old_taint_label1) {
            if (tb_ctx->untaint_mem_func)
                tb_ctx->untaint_mem_func(addr_id1, old_taint_label1);

            if (tb_ctx->delete_ref_func)
                tb_ctx->delete_ref_func(old_taint_label1);
        }
    }

    void *old_taint_label2 = tb_umbra_set_taint_mem_and_get_old(tb_ctx->mem_map,
            addr_id2, result_label1, &succ);

    if (old_taint_label2) {
        if (tb_ctx->untaint_reg_func)
            tb_ctx->untaint_reg_func(addr_id2, old_taint_label2);

        if (tb_ctx->delete_ref_func)
            tb_ctx->delete_ref_func(old_taint_label2);
    }

    return succ && (result_label1 != NULL || result_label2 != NULL);
}
