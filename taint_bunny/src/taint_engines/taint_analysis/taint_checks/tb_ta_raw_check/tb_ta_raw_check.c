/*
 * tb_ta_cc_check.c
 *
 *      Author: john
 */

#include "tb_ta_raw_check.h"

/**********************************************************************************
 * Taint Check
 ***********************************************************************************/

void tb_ta_raw_insert_get_mem_label(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t label_reg,
        reg_id_t scratch_reg) {

    tb_umbra_insert_translate_address(tb_ctx, drcontext, ilist, where,
            label_reg, scratch_reg);

    opnd_t tl_opnd = OPND_CREATE_MEMPTR(label_reg, 0);

    tb_raw_umbra_insert_get_mem(drcontext, ilist, where, NULL, &tl_opnd,
            label_reg);
}

void tb_ta_raw_insert_get_reg_label(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t label_reg) {

    opnd_t src_opnd = tb_raw_arraymap_insert_reg_get_taint_label_opnd(drcontext,
            ilist, where, map_reg, label_reg);

    opnd_t dst_opnd = opnd_create_reg(label_reg);
    instr_t *instr = INSTR_CREATE_mov_ld(drcontext, dst_opnd, src_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

void tb_ta_raw_insert_is_some_reg_tainted_via_reg(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t id_reg, size_t block_size,
        instr_t *true_case) {

    // Translation:
    tb_raw_arraymap_insert_translate_address(tb_ctx,
            drcontext, ilist, where, map_reg, id_reg);

    for (size_t i = 0; i < block_size; i++) {

        opnd_t src_opnd = OPND_CREATE_MEMPTR(id_reg, i * sizeof(void *));

        ub_instrum_check_mem_null_false_case(drcontext, ilist, where, NULL,
                &src_opnd, true_case);
    }
}

void tb_ta_raw_insert_is_some_reg_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t scratch_reg, size_t block_size,
        instr_t *true_case) {

    // Translation:
    tb_raw_arraymap_insert_translate_address_via_id(tb_ctx, drcontext, ilist,
            where, map_reg, reg_byte_id, scratch_reg);

    for (size_t i = 0; i < block_size; i++) {

        opnd_t src_opnd = OPND_CREATE_MEMPTR(scratch_reg, i* sizeof(void *));

        ub_instrum_check_mem_null_false_case(drcontext, ilist, where, NULL,
                &src_opnd, true_case);
    }
}

void tb_ta_raw_insert_is_some_mem_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, reg_id_t addr_reg,
        reg_id_t scratch_reg2, size_t block_size, instr_t *true_case) {

    tb_umbra_insert_translate_address(tb_ctx, drcontext, ilist, where, addr_reg,
            scratch_reg2);

    for (size_t i = 0; i < block_size; i++) {

        // Create dereference operand that access the src taint label
        opnd_t src_label_opnd = OPND_CREATE_MEMPTR(addr_reg, i * sizeof(void *));

        ub_instrum_check_mem_null_false_case(drcontext, ilist, where,
                translation, &src_label_opnd, true_case);
    }
}

void tb_ta_raw_is_all_reg_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t scratch_reg, size_t block_size,
        instr_t *false_case) {

    // Translation:
    tb_raw_arraymap_insert_translate_address_via_id(tb_ctx, drcontext, ilist,
            where, map_reg, reg_byte_id, scratch_reg);


    for (size_t i = 0; i < block_size; i++) {

        opnd_t src_opnd = OPND_CREATE_MEMPTR(scratch_reg, i * sizeof(void *));
        ub_instrum_check_mem_null_true_case(drcontext, ilist, where, NULL, &src_opnd,
                false_case);
    }
}

void tb_ta_raw_is_all_mem_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, reg_id_t addr_reg,
        reg_id_t scratch_reg2, size_t block_size, instr_t *false_case) {

    tb_umbra_insert_translate_address(tb_ctx, drcontext, ilist, where, addr_reg,
            scratch_reg2);

    for (size_t i = 0; i < block_size; i++) {

        // Create dereference operand that access the src taint label
        opnd_t src_label_opnd = OPND_CREATE_MEMPTR(addr_reg, i * sizeof(void *));

        ub_instrum_check_mem_null_true_case(drcontext, ilist, where, translation,
                &src_label_opnd, false_case);
    }
}
