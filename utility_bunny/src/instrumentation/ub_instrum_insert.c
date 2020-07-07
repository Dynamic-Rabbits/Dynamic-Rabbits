/**
 *  @file ub_instrum_insert.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_instrum_insert.h"
#include "../location/ub_loc.h"

DR_EXPORT void ub_instrum_mov_ld_mem_to_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, app_pc pc, const reg_id_t base_reg,
        const unsigned int disp, const reg_id_t dest_reg) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = OPND_CREATE_MEMPTR(base_reg, disp);
    opnd2 = opnd_create_reg(dest_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, opnd2, opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_mov_ld_mem_opnd_to_reg(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *mem_opnd,
        const reg_id_t dest_reg) {

    opnd_t opnd;
    instr_t *instr;

    opnd = opnd_create_reg(dest_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, opnd, *mem_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_xchg_reg_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, reg_id_t addr_reg) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = OPND_CREATE_MEMPTR(addr_reg, 0);
    opnd2 = opnd_create_reg(reg);
    instr = INSTR_CREATE_xchg(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_xchg_reg_mem_opnd(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, opnd_t *mem_opnd) {

    dr_fprintf(STDERR,
            "WARNING XCHG mem, reg is dangerous due to implicit lock!\n");

    DR_ASSERT(opnd_is_memory_reference(*mem_opnd));

    opnd_t opnd;
    instr_t *instr;

    opnd = opnd_create_reg(reg);
    instr = INSTR_CREATE_xchg(drcontext, *mem_opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

}

DR_EXPORT void ub_instrum_xchg_reg_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, const reg_id_t reg2) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = opnd_create_reg(reg);
    opnd2 = opnd_create_reg(reg2);
    instr = INSTR_CREATE_xchg(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_mov_ld_mem_to_reg_via_base_disp_index(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const reg_id_t index_reg, const unsigned int disp,
        const reg_id_t dest_reg) {

    ub_instrum_lea_base_disp_index(drcontext, ilist, where, base_reg, index_reg,
            disp, 1, dest_reg);

    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, dest_reg, 0,
            dest_reg);
}

DR_EXPORT void ub_instrum_mov_st_reg_to_mem_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        opnd_t *dst_opnd) {

    opnd_t opnd = opnd_create_reg(src_reg);
    instr_t *instr = INSTR_CREATE_mov_st(drcontext, *dst_opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

}

DR_EXPORT void ub_instrum_mov_st_reg_to_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t src_reg, const reg_id_t dst_base_reg,
        const unsigned int dst_disp) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = opnd_create_reg(src_reg);
    opnd2 = OPND_CREATE_MEMPTR(dst_base_reg, dst_disp);
    instr = INSTR_CREATE_mov_st(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_mov_st_immed_to_mem_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const int immed_val,
		opnd_t *dst_opnd) {

    opnd_t opnd;
    instr_t *instr;

    opnd = opnd_create_immed_int(immed_val, OPSZ_PTR);
    instr = INSTR_CREATE_mov_imm(drcontext, *dst_opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_mov_st_immed_to_reg(void *drcontext,
        instrlist_t *ilist, instr_t * where, const int immed_val,
        const reg_id_t dst_reg) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = opnd_create_immed_int(immed_val, OPSZ_PTR);
    opnd2 = opnd_create_reg(dst_reg);
    instr = INSTR_CREATE_mov_imm(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_mov_st_reg_to_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t src_reg, const reg_id_t dest_reg) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = opnd_create_reg(src_reg);
    opnd2 = opnd_create_reg(dest_reg);

    opnd_size_t size_opnd = opnd_get_size(opnd);
    uint opnd_size = opnd_size_in_bytes(size_opnd);

    size_opnd = opnd_get_size(opnd2);
    uint opnd_size2 = opnd_size_in_bytes(size_opnd);

    instr = INSTR_CREATE_mov_st(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_lea_base_disp(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t base_reg, const int disp,
        const reg_id_t dest_reg) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = OPND_CREATE_MEM_lea(base_reg, DR_REG_NULL, 0, disp);
    opnd2 = opnd_create_reg(dest_reg);
    instr = INSTR_CREATE_lea(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_lea_base_disp_index(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const reg_id_t index_reg, const int disp, const int scale,
        const reg_id_t dest_reg) {

    opnd_t opnd, opnd2;
    instr_t *instr;

    opnd = OPND_CREATE_MEM_lea(base_reg, index_reg, scale, disp);
    opnd2 = opnd_create_reg(dest_reg);
    instr = INSTR_CREATE_lea(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_inc_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t base_reg, const unsigned int disp) {

    opnd_t opnd;
    opnd_t opnd2;
    instr_t *instr;

    // Dont use inc but add to destroy dependency chain.
    opnd_t mem_ptr = OPND_CREATE_MEMPTR(base_reg, disp);
    opnd2 = opnd_create_immed_int(1, OPSZ_4);
    instr = INSTR_CREATE_add(drcontext, mem_ptr, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_inc_mem_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const unsigned int disp, reg_id_t scratch) {

    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, base_reg, disp,
            scratch);
    ub_instrum_inc_reg_no_eflag_corrupt(drcontext, ilist, where, scratch);
    ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, scratch, base_reg,
            disp);
}

DR_EXPORT void ub_instrum_dec_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t base_reg, const unsigned int disp) {

    opnd_t opnd;
    opnd_t opnd2;
    instr_t *instr;

    // Dont use inc but add to destroy dependency chain.
    opnd_t mem_ptr = OPND_CREATE_MEMPTR(base_reg, disp);
    opnd2 = opnd_create_immed_int(1, OPSZ_4);
    instr = INSTR_CREATE_sub(drcontext, mem_ptr, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_dec_mem_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const unsigned int disp, reg_id_t scratch) {

    ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, base_reg, disp,
            scratch);
    ub_instrum_dec_reg_no_eflag_corrupt(drcontext, ilist, where, scratch);
    ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, scratch, base_reg,
            disp);
}

DR_EXPORT void ub_instrum_inc_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg) {

    opnd_t opnd;
    opnd_t opnd2;
    instr_t *instr;

    // Dont use inc but add to destroy dependency chain.
    opnd = opnd_create_reg(reg);
    opnd2 = opnd_create_immed_int(1, OPSZ_4);
    instr = INSTR_CREATE_add(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_inc_reg_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t reg) {

    ub_instrum_lea_base_disp(drcontext, ilist, where, reg, 1, reg);
}

DR_EXPORT void ub_instrum_dec_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg) {

    opnd_t opnd;
    opnd_t opnd2;
    instr_t *instr;

    // Dont use dec but sub to destroy dependency chain.
    opnd = opnd_create_reg(reg);
    opnd2 = opnd_create_immed_int(1, OPSZ_4);
    instr = INSTR_CREATE_sub(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_dec_reg_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t reg) {

    ub_instrum_lea_base_disp(drcontext, ilist, where, reg, -1, reg);
}

DR_EXPORT void ub_instrum_arith_reg_immed_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t reg, int immed_val) {

    ub_instrum_lea_base_disp(drcontext, ilist, where, reg, immed_val, reg);
}

DR_EXPORT void ub_instrum_add_reg_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, int immed_val) {

    opnd_t opnd;
    opnd_t opnd2;
    instr_t *instr;

    opnd = opnd_create_reg(reg);
    opnd2 = opnd_create_immed_int(immed_val, OPSZ_PTR);
    instr = INSTR_CREATE_add(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_sub_reg_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, int immed_val) {

    opnd_t opnd;
    opnd_t opnd2;
    instr_t *instr;

    // Dont use dec but sub to destroy dependency chain.
    opnd = opnd_create_reg(reg);
    opnd2 = opnd_create_immed_int(immed_val, OPSZ_PTR);
    instr = INSTR_CREATE_sub(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_clear_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t clear_reg) {

    opnd_t opnd = opnd_create_reg(clear_reg);
    instr_t *instr = INSTR_CREATE_xor(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_clear_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t base_reg, int disp) {

    opnd_t opnd = OPND_CREATE_MEMPTR(base_reg, disp);
    instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, opnd, ilist,
            where, NULL, NULL);
}

DR_EXPORT void ub_instrum_clear_mem_opnd(void *drcontext, instrlist_t *ilist,
        instr_t * where, opnd_t *mem_opnd) {

    instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, *mem_opnd,
            ilist, where, NULL, NULL);
}

DR_EXPORT void ub_instrum_clear_reg_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t clear_reg) {

    opnd_t opnd = opnd_create_reg(clear_reg);
    instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, opnd, ilist,
            where, NULL, NULL);
}

DR_EXPORT void ub_instrum_shift_right(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t shift_reg, int shift_size) {

    opnd_t opnd = opnd_create_reg(shift_reg);
    opnd_t opnd_immed = opnd_create_immed_int((ptr_int_t) shift_size, OPSZ_PTR);
    instr_t *instr = INSTR_CREATE_shr(drcontext, opnd, opnd_immed);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_shift_left(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t shift_reg, int shift_size) {

    opnd_t opnd = opnd_create_reg(shift_reg);
    opnd_t opnd_immed = opnd_create_immed_int((ptr_int_t) shift_size, OPSZ_1);
    instr_t *instr = INSTR_CREATE_shl(drcontext, opnd, opnd_immed);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_and_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t value_reg, int immed_value) {

    opnd_t opnd = opnd_create_reg(value_reg);
    opnd_t opnd_immed = opnd_create_immed_int((ptr_int_t) immed_value,
    OPSZ_PTR);
    instr_t *instr = INSTR_CREATE_and(drcontext, opnd, opnd_immed);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_or_reg_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t srcdst_reg, reg_id_t src_reg) {

    opnd_t opnd = opnd_create_reg(src_reg);
    opnd_t opnd2 = opnd_create_reg(srcdst_reg);
    instr_t *instr = INSTR_CREATE_or(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_or_reg_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t value_reg, int immed_value) {

    opnd_t opnd = opnd_create_reg(value_reg);
    opnd_t opnd_immed = opnd_create_immed_int((ptr_int_t) immed_value,
    OPSZ_PTR);
    instr_t *instr = INSTR_CREATE_or(drcontext, opnd, opnd_immed);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_or_mem_and_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, opnd_t *mem_opnd, reg_id_t src_reg) {

    opnd_t src_reg_opnd = opnd_create_reg(src_reg);
    instr_t *instr = INSTR_CREATE_or(drcontext, *mem_opnd, src_reg_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_or_reg_and_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t dst_reg, opnd_t *mem_opnd) {

    opnd_t dst_reg_opnd = opnd_create_reg(dst_reg);
    instr_t *instr = INSTR_CREATE_or(drcontext, dst_reg_opnd, *mem_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_or_mem_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, opnd_t *mem_opnd, int immed_value) {

    opnd_t opnd_immed = opnd_create_immed_int((ptr_int_t) immed_value,
    OPSZ_PTR);
    instr_t *instr = INSTR_CREATE_or(drcontext, *mem_opnd, opnd_immed);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_clear_mem_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t base_reg, int disp) {

    opnd_t opnd = OPND_CREATE_MEMPTR(base_reg, disp);
    instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, opnd, ilist,
            where, NULL, NULL);
}

DR_EXPORT void ub_instrum_clear_mem_opnd_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *opnd) {

    instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, *opnd, ilist,
            where, NULL, NULL);
}

DR_EXPORT void ub_instrum_direct_jmp(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t* label) {

    instr_t *instr;
    opnd_t label_opnd = opnd_create_instr(label);
    instr = INSTR_CREATE_jmp(drcontext, label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_null(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t check_reg, instr_t* true_label,
        instr_t* false_label) {

    instr_t *instr;
    opnd_t opnd = opnd_create_reg(check_reg);
    instr = INSTR_CREATE_test(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t true_label_opnd = opnd_create_instr(true_label);
    opnd_t false_label_opnd = opnd_create_instr(false_label);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    // fall through. Lets jump to the false!

    instr = INSTR_CREATE_jmp(drcontext, false_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

}

DR_EXPORT void ub_instrum_check_simd_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_reg,
        instr_t* true_label) {

    DR_ASSERT(reg_is_xmm(vector_reg));

    opnd_t true_label_opnd = opnd_create_instr(true_label);
    opnd_t reg_opnd = opnd_create_reg(vector_reg);

    instr_t *instr = INSTR_CREATE_ptest(drcontext, reg_opnd, reg_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_simd_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_reg,
        instr_t* true_label) {

    DR_ASSERT(reg_is_xmm(vector_reg));

    opnd_t true_label_opnd = opnd_create_instr(true_label);
    opnd_t reg_opnd = opnd_create_reg(vector_reg);

    instr_t *instr = INSTR_CREATE_ptest(drcontext, reg_opnd, reg_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jcc(drcontext, OP_jnz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_mem_immed_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation,
        opnd_t *check_mem_opnd, int immed_val, instr_t* true_label) {

    instr_t *instr;
    opnd_t opnd = opnd_create_immed_int(immed_val, OPSZ_4);
    instr = INSTR_CREATE_cmp(drcontext, *check_mem_opnd, opnd);
    instr_set_translation(instr, translation);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t true_label_opnd = opnd_create_instr(true_label);
    instr = INSTR_CREATE_jcc(drcontext, OP_jz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_mem_immed_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation,
        opnd_t *check_mem_opnd, int immed_val, instr_t* false_label) {

    instr_t *instr;
    opnd_t opnd = opnd_create_immed_int(immed_val, OPSZ_4);
    instr = INSTR_CREATE_cmp(drcontext, *check_mem_opnd, opnd);
    instr_set_translation(instr, translation);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t true_label_opnd = opnd_create_instr(false_label);

    instr = INSTR_CREATE_jcc(drcontext, OP_jnz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_mem_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation,
        opnd_t *check_mem_opnd, instr_t* true_label) {

    ub_instrum_check_mem_immed_true_case(drcontext, ilist, where, translation,
            check_mem_opnd, 0, true_label);
}

DR_EXPORT void ub_instrum_check_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t check_reg,
        instr_t* true_label) {

    instr_t *instr;
    opnd_t opnd = opnd_create_reg(check_reg);

    instr = INSTR_CREATE_test(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t true_label_opnd = opnd_create_instr(true_label);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_mem_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation,
        opnd_t *check_mem_opnd, instr_t* false_label) {

    ub_instrum_check_mem_immed_false_case(drcontext, ilist, where, translation,
            check_mem_opnd, 0, false_label);
}

DR_EXPORT void ub_instrum_check_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t check_reg,
        instr_t* false_label) {

    instr_t *instr;
    opnd_t opnd = opnd_create_reg(check_reg);

    instr = INSTR_CREATE_test(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t true_label_opnd = opnd_create_instr(false_label);

    instr = INSTR_CREATE_jcc(drcontext, OP_jnz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_null_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t check_reg,
        instr_t* true_label, instr_t* false_label) {

    DR_ASSERT(check_reg == DR_REG_XCX);

    instr_t *instr;
    opnd_t true_label_opnd = opnd_create_instr(true_label);
    opnd_t false_label_opnd = opnd_create_instr(false_label);

    instr = INSTR_CREATE_jcxz(drcontext, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    // fall through. Lets jump to the false!

    instr = INSTR_CREATE_jmp(drcontext, false_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_check_null_no_eflag_corrupt_true_case(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t check_reg,
        instr_t* true_label) {

    DR_ASSERT(check_reg == DR_REG_XCX);

    instr_t *instr;
    opnd_t true_label_opnd = opnd_create_instr(true_label);

    instr = INSTR_CREATE_jcxz(drcontext, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_store_eflags(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t dst_base_reg, int offset) {

    ub_instrum_lea_base_disp(drcontext, ilist, where, dst_base_reg, offset + 4,
    DR_REG_XSP);

    instr_t *instr = INSTR_CREATE_pushf(drcontext);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_load_eflags(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t src_base_reg, int offset) {

    ub_instrum_lea_base_disp(drcontext, ilist, where, src_base_reg, offset,
    DR_REG_XSP);

    instr_t *instr = INSTR_CREATE_popf(drcontext);
    instrlist_meta_preinsert(ilist, where, instr);
}

void ib_insert_load_flags(void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t flag_addr_reg, reg_id_t scratch_reg_id) {

    DR_ASSERT(flag_addr_reg == DR_REG_XSP);

    instr_t *instr = INSTR_CREATE_popf(drcontext);
    instrlist_meta_preinsert(ilist, where, instr);
}

/*********************************************************************************
 * SIMD INSTRs
 */

DR_EXPORT void ub_instrum_simd_mov_ld_mem_opnd_to_reg(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *mem_opnd,
        const reg_id_t dest_reg) {

    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where, mem_opnd,
            dest_reg, NULL);
}

DR_EXPORT void ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *mem_opnd,
        const reg_id_t dest_reg, app_pc translation) {

    opnd_t opnd;
    instr_t *instr;
    ub_loc_info_t loc_info;

    DR_ASSERT(mem_opnd!= NULL);
    DR_ASSERT(reg_is_xmm(dest_reg));

    opnd = opnd_create_reg(dest_reg);
    ub_get_loc_info(&loc_info, mem_opnd);

    switch (loc_info.size) {

    case 4:
        instr = INSTR_CREATE_movd(drcontext, opnd, *mem_opnd);
        break;

    case 8:
        instr = INSTR_CREATE_movq(drcontext, opnd, *mem_opnd);
        break;

    case 16:
        instr = INSTR_CREATE_movdqu(drcontext, opnd, *mem_opnd);
        break;

    default:
        dr_fprintf(STDERR, "The size is %u\n", loc_info.size);
        DR_ASSERT_MSG(false,
                "Couldn't find appropriate instruction for given size.");
    }

    instr_set_translation(instr, translation);
    instrlist_meta_preinsert(ilist, where, instr);

}

static void ub_instrum_simd_mov_st_reg_to_mem_opnd_helper(void *drcontext,
        instr_t **instr, const reg_id_t src_reg, opnd_t *mem_opnd) {

    opnd_t opnd;
    ub_loc_info_t loc_info;

    DR_ASSERT(mem_opnd!= NULL);
    DR_ASSERT(reg_is_xmm(src_reg));

    opnd = opnd_create_reg(src_reg);
    ub_get_loc_info(&loc_info, mem_opnd);

    switch (loc_info.size) {

    case 4:
        *instr = INSTR_CREATE_movd(drcontext, *mem_opnd, opnd);
        break;

    case 8:
        *instr = INSTR_CREATE_movq(drcontext, *mem_opnd, opnd);
        break;

    case 16:
        *instr = INSTR_CREATE_movdqu(drcontext, *mem_opnd, opnd);
        break;

    default:
        DR_ASSERT_MSG(false,
                "Couldn't find appropriate instruction for given size.");
    }

}

DR_EXPORT void ub_instrum_simd_mov_st_reg_to_reg_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        const reg_id_t dst_reg) {

    DR_ASSERT(reg_is_xmm(src_reg));
    DR_ASSERT(reg_is_xmm(dst_reg));

    instr_t *instr;
    instr = INSTR_CREATE_movdqu(drcontext, opnd_create_reg(dst_reg),
            opnd_create_reg(src_reg));
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_simd_mov_st_reg_to_mem_opnd_ex(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        opnd_t *mem_opnd, app_pc translation) {

    instr_t *instr;
    ub_instrum_simd_mov_st_reg_to_mem_opnd_helper(drcontext, &instr, src_reg,
            mem_opnd);
    instr_set_translation(instr, translation);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_simd_mov_st_reg_to_mem_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        opnd_t *mem_opnd) {

    instr_t *instr;
    ub_instrum_simd_mov_st_reg_to_mem_opnd_helper(drcontext, &instr, src_reg,
            mem_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_simd_clear_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t vector_src_reg) {

    DR_ASSERT(reg_is_xmm(vector_src_reg));

    opnd_t opnd;
    instr_t *instr;

    opnd = opnd_create_reg(vector_src_reg);
    instr = INSTR_CREATE_pxor(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_simd_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t vector_check_reg) {

    DR_ASSERT(reg_is_xmm(vector_check_reg));

    instr_t *instr;
    opnd_t opnd = opnd_create_reg(vector_check_reg);

    instr = INSTR_CREATE_ptest(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_simd_check_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_check_reg,
        instr_t* true_label) {

    DR_ASSERT(true_label != NULL);

    instr_t *instr;
    ub_instrum_simd_test(drcontext, ilist, where, vector_check_reg);

    opnd_t true_label_opnd = opnd_create_instr(true_label);
    instr = INSTR_CREATE_jcc(drcontext, OP_jz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_simd_check_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_check_reg,
        instr_t* false_label) {

    DR_ASSERT(false_label != NULL);

    instr_t *instr;
    ub_instrum_simd_test(drcontext, ilist, where, vector_check_reg);

    opnd_t false_label_opnd = opnd_create_instr(false_label);
    instr = INSTR_CREATE_jcc(drcontext, OP_jnz, false_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

DR_EXPORT void ub_instrum_simd_negate_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t vector_src_reg, reg_id_t vector_scratch_reg) {

    opnd_t opnd, opnd2;

    DR_ASSERT(reg_is_xmm(vector_src_reg));
    DR_ASSERT(reg_is_xmm(vector_scratch_reg));

    instr_t *instr;

    opnd = opnd_create_reg(vector_scratch_reg);
    instr = INSTR_CREATE_pcmpeqd(drcontext, opnd, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd = opnd_create_reg(vector_src_reg);
    opnd2 = opnd_create_reg(vector_scratch_reg);
    instr = INSTR_CREATE_pxor(drcontext, opnd, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

