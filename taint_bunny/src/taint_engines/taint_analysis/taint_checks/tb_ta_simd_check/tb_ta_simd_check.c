/*
 * tb_ta_simd_check.c
 *
 *      Author: john
 */

#include "tb_ta_simd_check.h"
#include "../../tb_simd_taint_analysis/tb_ta_simd_byt_functionality.h"

void tb_ta_simd_insert_get_mem_label(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *tl_opnd, reg_id_t vector_label_reg) {

    tb_simd_umbra_insert_get_mem(drcontext, ilist, where,
            instr_get_app_pc(where), tl_opnd, vector_label_reg);
}

void tb_ta_simd_insert_get_reg_label(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, size_t size, reg_id_t veclabel_reg) {

    opnd_t tl_opnd = tb_raw_arraymap_insert_reg_get_taint_label_opnd_ex(
            drcontext, ilist, where, map_reg, reg_byte_id, size);

    ub_instrum_simd_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &tl_opnd,
            veclabel_reg);
}

static void tb_ta_simd_some_reg_check_helper(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t id_reg,
        reg_id_t vector_reg, size_t block_size, instr_t *true_case) {

    int partial_size;

    for (size_t i = 0; i < block_size; i += sizeof(void *)) {

        partial_size = tb_simd_calculate_partial_size(block_size, i)
                * sizeof(void *);

        opnd_t src_opnd = opnd_create_base_disp(id_reg, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        ub_instrum_simd_mov_ld_mem_opnd_to_reg(drcontext, ilist, where,
                &src_opnd, vector_reg);

        ub_instrum_check_simd_null_false_case(drcontext, ilist, where,
                vector_reg, true_case);
    }
}

void tb_ta_simd_insert_is_some_reg_tainted_via_reg(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_id_t id_reg, reg_id_t vector_reg, size_t block_size,
        instr_t *true_case) {

    DR_ASSERT(reg_is_gpr(map_reg));
    DR_ASSERT(reg_is_gpr(id_reg));
    DR_ASSERT(reg_is_xmm(vector_reg));

    // Translation:
    tb_raw_arraymap_insert_translate_address(tb_ctx, drcontext, ilist, where,
            map_reg, id_reg);

    tb_ta_simd_some_reg_check_helper(tb_ctx, drcontext, ilist, where, id_reg,
            vector_reg, block_size, true_case);
}

void tb_ta_simd_insert_is_some_reg_tainted(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t vector_reg,
        reg_id_t scaler_scratch_reg, size_t block_size, instr_t *true_case) {

    DR_ASSERT(reg_is_gpr(map_reg));
    DR_ASSERT(reg_is_gpr(scaler_scratch_reg));
    DR_ASSERT(reg_is_xmm(vector_reg));

    // Translation:
    tb_raw_arraymap_insert_translate_address_via_id(tb_ctx, drcontext, ilist,
            where, map_reg, reg_byte_id, scaler_scratch_reg);

    tb_ta_simd_some_reg_check_helper(tb_ctx, drcontext, ilist, where,
            scaler_scratch_reg, vector_reg, block_size, true_case);
}

void tb_ta_simd_insert_is_some_mem_tainted(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
        instr_t *true_case) {

    DR_ASSERT(reg_is_xmm(vector_reg));
    DR_ASSERT(reg_is_gpr(addr_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg));

    tb_umbra_insert_translate_address(tb_ctx, drcontext, ilist, where, addr_reg,
            scratch_reg);

    int partial_size;

    for (size_t i = 0; i < block_size; i += sizeof(void *)) {

        partial_size = tb_simd_calculate_partial_size(block_size, i)
                * sizeof(void *);

        opnd_t src2_label_opnd = opnd_create_base_disp(addr_reg, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
                &src2_label_opnd, vector_reg, instr_get_app_pc(where));

        ub_instrum_check_simd_null_false_case(drcontext, ilist, where,
                vector_reg, true_case);
    }
}

static void tb_ta_simd_is_all_reg_check_helper(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t id_reg,
        reg_id_t vector_reg, size_t block_size, instr_t *false_case) {

    int partial_size;

    for (size_t i = 0; i < block_size; i += sizeof(void *)) {

        partial_size = tb_simd_calculate_partial_size(block_size, i)
                * sizeof(void *);

        opnd_t src_opnd = opnd_create_base_disp(id_reg, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        ub_instrum_simd_mov_ld_mem_opnd_to_reg(drcontext, ilist, where,
                &src_opnd, vector_reg);

        ub_instrum_check_simd_null_true_case(drcontext, ilist, where,
                vector_reg, false_case);
    }
}

void tb_ta_simd_insert_is_all_reg_tainted_via_reg(tb_context_t *tb_ctx,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        reg_t id_reg, reg_id_t vector_reg, size_t block_size,
        instr_t *false_case) {

    DR_ASSERT(reg_is_gpr(map_reg));
    DR_ASSERT(reg_is_gpr(vector_reg));

    // Translation:
    tb_raw_arraymap_insert_translate_address(tb_ctx, drcontext, ilist, where,
            map_reg, id_reg);

    tb_ta_simd_is_all_reg_check_helper(tb_ctx, drcontext, ilist, where, id_reg,
            vector_reg, block_size, false_case);
}

void tb_ta_simd_insert_is_all_reg_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t vector_reg,
        reg_id_t scaler_scratch_reg, size_t block_size, instr_t *false_case) {

    DR_ASSERT(reg_is_gpr(map_reg));
    DR_ASSERT(reg_is_gpr(vector_reg));

    // Translation:
    tb_raw_arraymap_insert_translate_address_via_id(tb_ctx, drcontext, ilist,
            where, map_reg, reg_byte_id, scaler_scratch_reg);

    tb_ta_simd_is_all_reg_check_helper(tb_ctx, drcontext, ilist, where,
            scaler_scratch_reg, vector_reg, block_size, false_case);

}

void tb_ta_simd_insert_is_all_mem_tainted(tb_context_t *tb_ctx, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
        instr_t *false_case) {

    DR_ASSERT(reg_is_xmm(vector_reg));
    DR_ASSERT(reg_is_gpr(addr_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg));

    tb_umbra_insert_translate_address(tb_ctx, drcontext, ilist, where, addr_reg,
            scratch_reg);

    int partial_size;

    for (size_t i = 0; i < block_size; i += sizeof(void *)) {

        partial_size = tb_simd_calculate_partial_size(block_size, i)
                * sizeof(void *);

        opnd_t src2_label_opnd = opnd_create_base_disp(addr_reg, DR_REG_NULL, 1,
                sizeof(void *) * i, opnd_size_from_bytes(partial_size));

        ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
                &src2_label_opnd, vector_reg, instr_get_app_pc(where));

        ub_instrum_check_simd_null_true_case(drcontext, ilist, where,
                vector_reg, false_case);
    }
}
