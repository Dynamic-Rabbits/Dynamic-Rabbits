/*
 * tb_raw_dst_id_policy.c
 *
 *      Author: john
 */

#include "tb_raw_dst_id_policy.h"
#include <limits.h>
#include <string.h>

static void * get_default_label();

/****
 * For now, this policy is not thread-safe!
 *
 * Keep calm, it's just a prototype!
 *
 * Future work will make use of the allocator provided
 * by the UB!
 *
 * Note the allocator is done and used by the
 * bitvect policy as an example.
 */

static unsigned int id_counter = 0;

static unsigned int *add_template = NULL;
static unsigned int *add_template_aligned = NULL;

static unsigned int *zero_template = NULL;
static unsigned int *zero_template_aligned = NULL;

static void tb_create_id_taint_ploicy() {

    add_template = dr_global_alloc((sizeof(unsigned int) * 4) + 15);
    add_template_aligned = (void *) (((uintptr_t) add_template + 15)
            & ~(uintptr_t) 0x0F);

    for (int i = 1; i < 5; i++) {
        add_template_aligned[i - 1] = i;
    }

    zero_template = dr_global_alloc((sizeof(unsigned int) * 4) + 15);
    zero_template_aligned = (void *) (((uintptr_t) zero_template + 15)
            & ~(uintptr_t) 0x0F);
    memset(zero_template_aligned, 0, sizeof(unsigned int) * 4);

}

static void tb_delete_id_taint_ploicy() {

    dr_global_free(add_template, (sizeof(unsigned int) * 4) + 15);
    dr_global_free(zero_template, (sizeof(unsigned int) * 4) + 15);

    zero_template = NULL;
    zero_template_aligned = NULL;
    add_template = NULL;
    add_template_aligned = NULL;

    id_counter = 0;
}

static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg);
static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        reg_id_t scratch_reg);
static void insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc app_instr, reg_id_t meet_reg,
        opnd_t *label_lowest_opnd, opnd_t *src1_opnd, reg_id_t scratch_reg);

static void tb_simd_insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t meet_reg, opnd_t *label_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

static void tb_simd_insert_propogate_1dst_1src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc app_instr,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg);

static void tb_simd_insert_propogate_1dst_2src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        opnd_t *src2_vectorised_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_reg);

void tb_raw_initialise_id_taint_policy(tb_raw_taint_policy_t *taint_policy) {

    memset(taint_policy, 0, sizeof(tb_raw_taint_policy_t));

    taint_policy->init_func = tb_create_id_taint_ploicy;
    taint_policy->destroy_func = tb_delete_id_taint_ploicy;

    taint_policy->insert_raw_meet = insert_meet_func;
    taint_policy->insert_raw_propogate_1dst_1src =
            insert_propogate_func_1dst_1src;
    taint_policy->insert_raw_propogate_1dst_2src =
            insert_propogate_func_1dst_2src;

    taint_policy->insert_simd_meet = tb_simd_insert_meet_func;
    taint_policy->insert_simd_propogate_1dst_1src =
            tb_simd_insert_propogate_1dst_1src_func;
    taint_policy->insert_simd_propogate_1dst_2src =
            tb_simd_insert_propogate_1dst_2src_func;

    taint_policy->get_default_label = get_default_label;
}

static void *get_result() {

    // Check
    if (id_counter == UINT32_MAX) {
        id_counter = 0;
    }

    // If src is tainted inc counter and return.
    id_counter++;

    return (void *) (uintptr_t) id_counter;
}

static void * get_default_label() {

    return get_result();

}

static void insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t meet_reg, opnd_t *label_lowest_opnd,
        opnd_t *src1_opnd, reg_id_t scratch_reg) {

    DR_ASSERT(opnd_is_reg(*label_lowest_opnd));
    instr_t *instr;

    instr = INSTR_CREATE_or(drcontext, *label_lowest_opnd, *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

}

static void insert_propagate_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, reg_id_t scratch_reg) {

    /* Get the ID counter */
    opnd_t counter_opnd = opnd_create_abs_addr(&id_counter, OPSZ_4);
    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &counter_opnd,
            dst_reg);

    /** Load 1 to dst reg. We need to take into account overflow because 0 means untainted! **/
    ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, 1, scratch_reg);

    ub_instrum_inc_reg(drcontext, ilist, where, dst_reg);

    instr_t *instr = INSTR_CREATE_cmovcc(drcontext, OP_cmovo,
            opnd_create_reg(dst_reg), opnd_create_reg(scratch_reg));
    instrlist_meta_preinsert(ilist, where, instr);

    // Store new counter
    ub_instrum_mov_st_reg_to_mem_opnd(drcontext, ilist, where, dst_reg,
            &counter_opnd);
}

static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        reg_id_t scratch_reg) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);

    ub_instrum_clear_reg(drcontext, ilist, where, dst_reg);

    opnd_t opnd = opnd_create_immed_int(0, OPSZ_4);
    instr_t *instr = INSTR_CREATE_cmp(drcontext, *src1_opnd, opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t true_label_opnd = opnd_create_instr(exit_label);
    instr = INSTR_CREATE_jcc(drcontext, OP_jz, true_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    insert_propagate_helper(drcontext, ilist, where, pc, dst_reg, scratch_reg);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg) {

    instr_t *instr;

    ub_instrum_clear_reg(drcontext, ilist, where, dst_reg);

    opnd_t dst_opnd = opnd_create_reg(scratch_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, dst_opnd, *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_or(drcontext, dst_opnd, *src2_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    instr_t* exit_label = INSTR_CREATE_label(drcontext);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd_create_instr(exit_label));
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    insert_propagate_helper(drcontext, ilist, where, pc, dst_reg, scratch_reg);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

static void tb_simd_insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t meet_reg, opnd_t *label_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg) {

    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_scaler_reg));

    opnd_t taint = opnd_create_reg(scratch_scaler_reg);

    instr_t *instr;
    opnd_t opnd = opnd_create_immed_int(1, OPSZ_4);
    instr = INSTR_CREATE_mov_imm(drcontext, taint, opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t reg_opnd;

    if (opnd_is_memory_reference(*label_opnd)) {
        ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
                label_opnd, scratch_vectorised_reg, pc);
        reg_opnd = opnd_create_reg(scratch_vectorised_reg);
    } else {
        reg_opnd = *label_opnd;
    }

    instr = INSTR_CREATE_ptest(drcontext, reg_opnd, reg_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t meet_opnd = opnd_create_reg(meet_reg);
    instr = INSTR_CREATE_cmovcc(drcontext, OP_cmovnz, meet_opnd, taint);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

static void tb_simd_insert_propagate_helper(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg) {

    instr_t* no_overflow_label = INSTR_CREATE_label(drcontext);

    // Check that the registers are xmm registers.
    DR_ASSERT(reg_is_xmm(dst_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg));

    // Load counter
    opnd_t counter_opnd = opnd_create_abs_addr(&id_counter, OPSZ_4);
    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &counter_opnd,
            scratch_reg);

    // Check if counter is about to overflow

    // Start from 4
    ub_instrum_add_reg_immed(drcontext, ilist, where, scratch_reg, 4);

    instr_t *instr = INSTR_CREATE_jcc(drcontext, OP_jno,
            opnd_create_instr(no_overflow_label));
    instrlist_meta_preinsert(ilist, where, instr);

    ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, 1, scratch_reg);

    instrlist_meta_preinsert(ilist, where, no_overflow_label);

    // Load the value of the counter and place it in each slot.
    opnd_t src_opnd = opnd_create_reg(scratch_reg);
    opnd_t dst_opnd = opnd_create_reg(scratch_vectorised_reg);
    instr = INSTR_CREATE_movd(drcontext, dst_opnd, src_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd_t imm_opnd = opnd_create_immed_uint(0, opnd_size_from_bytes(1));
    instr = INSTR_CREATE_pshufd(drcontext, dst_opnd, dst_opnd, imm_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_paddd(drcontext,
            opnd_create_reg(scratch_vectorised_reg),
            opnd_create_abs_addr(add_template_aligned, OPSZ_16));
    instrlist_meta_preinsert(ilist, where, instr);

    // Create mask with pcmpeqd
    instr = INSTR_CREATE_pcmpeqd(drcontext, opnd_create_reg(dst_vectorised_reg),
            opnd_create_abs_addr(zero_template_aligned, OPSZ_16));
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_pandn(drcontext, opnd_create_reg(dst_vectorised_reg),
            opnd_create_reg(scratch_vectorised_reg));
    instrlist_meta_preinsert(ilist, where, instr);

    // Store new counter
    ub_instrum_mov_st_reg_to_mem_opnd(drcontext, ilist, where, scratch_reg,
            &counter_opnd);
}

static void tb_simd_insert_propogate_1dst_1src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);

    ub_instrum_simd_clear_reg(drcontext, ilist, where, dst_vectorised_reg);

    // First move src1 to dst.
    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
            src1_vectorised_opnd, scratch_vectorised_reg, pc);

    ub_instrum_check_simd_null_true_case(drcontext, ilist, where,
            scratch_vectorised_reg, exit_label);

    ub_instrum_simd_mov_st_reg_to_reg_opnd(drcontext, ilist, where,
            scratch_vectorised_reg, dst_vectorised_reg);

    tb_simd_insert_propagate_helper(drcontext, ilist, where, pc,
            dst_vectorised_reg, scratch_vectorised_reg, scratch_reg);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

static void tb_simd_insert_propogate_1dst_2src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        opnd_t *src2_vectorised_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_reg) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);

    ub_instrum_simd_clear_reg(drcontext, ilist, where, dst_vectorised_reg);

    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
            src1_vectorised_opnd, scratch_vectorised_reg, pc);

    instr_t * instr = INSTR_CREATE_por(drcontext,
            opnd_create_reg(scratch_vectorised_reg), *src2_vectorised_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    ub_instrum_check_simd_null_true_case(drcontext, ilist, where,
            scratch_vectorised_reg, exit_label);

    ub_instrum_simd_mov_st_reg_to_reg_opnd(drcontext, ilist, where,
            scratch_vectorised_reg, dst_vectorised_reg);

    tb_simd_insert_propagate_helper(drcontext, ilist, where, pc,
            dst_vectorised_reg, scratch_vectorised_reg, scratch_reg);

    instrlist_meta_preinsert(ilist, where, exit_label);

}
