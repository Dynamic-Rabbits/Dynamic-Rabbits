/*
 * tb_bitwise_policy.c
 *
 *      Author: john
 */

#include "tb_raw_bitwise_policy.h"
#include "../cc_taint_policies/tb_cc_bitwise_policy.h"

static void *tb_raw_bitwise_get_default_label();
static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg_xcx);
static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        reg_id_t scratch_reg);
static void insert_meet_func(void *drcontext, instrlist_t *ilist, instr_t *where,
        app_pc app_instr, reg_id_t meet_reg, opnd_t *label_lowest_opnd,
        opnd_t *src1_opnd, reg_id_t scratch_reg);

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

void tb_raw_initialise_bitwise_taint_policy(tb_raw_taint_policy_t *taint_policy) {

    memset(taint_policy, 0, sizeof(tb_raw_taint_policy_t));

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

    taint_policy->get_default_label = tb_raw_bitwise_get_default_label;
}

static void *tb_raw_bitwise_get_default_label(){

    return (void *) 1;
}

static void insert_meet_func(void *drcontext, instrlist_t *ilist, instr_t *where,
        app_pc pc, reg_id_t meet_reg, opnd_t *label_lowest_opnd,
        opnd_t *src1_opnd, reg_id_t scratch_reg) {

    DR_ASSERT(opnd_is_reg(*label_lowest_opnd));
    instr_t *instr;

    instr = INSTR_CREATE_or(drcontext, *label_lowest_opnd, *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        reg_id_t scratch_reg) {

    instr_t *instr;

    opnd_t dst_opnd = opnd_create_reg(dst_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, dst_opnd, *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg_xcx) {

    instr_t *instr;

    opnd_t dst_opnd = opnd_create_reg(dst_reg);
    instr = INSTR_CREATE_mov_ld(drcontext, dst_opnd, *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_or(drcontext, dst_opnd, *src2_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);
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

static void tb_simd_insert_propogate_1dst_1src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg) {

    // Check that the registers are xmm registers.
    DR_ASSERT(reg_is_xmm(dst_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg));

    // First move src1 to dst.
    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
            src1_vectorised_opnd, dst_vectorised_reg, pc);
}

static void tb_simd_insert_propogate_1dst_2src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        opnd_t *src2_vectorised_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_reg) {

    // Check that the registers are xmm registers.
    DR_ASSERT(reg_is_xmm(dst_vectorised_reg));
    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
    DR_ASSERT(reg_is_gpr(scratch_reg));

    // First move src1 to dst.
    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
            src1_vectorised_opnd, dst_vectorised_reg, pc);

    ub_instrum_simd_mov_ld_mem_opnd_to_reg(drcontext, ilist, where,
            src2_vectorised_opnd, scratch_vectorised_reg);

    opnd_t src_opnd = opnd_create_reg(scratch_vectorised_reg);
    opnd_t dst_opnd = opnd_create_reg(dst_vectorised_reg);

    instr_t * instr = INSTR_CREATE_por(drcontext, dst_opnd, src_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

