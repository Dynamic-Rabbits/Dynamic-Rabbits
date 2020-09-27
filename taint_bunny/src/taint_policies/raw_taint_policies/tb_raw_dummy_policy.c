/*
 * tb_raw_bitvect_policy.c
 *
 *      Author: john
 */

#include "tb_raw_dummy_policy.h"

static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg_xcx);
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
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg);
static void tb_simd_insert_propogate_1dst_2src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        opnd_t *src2_vectorised_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_reg);

static void *get_dummy_default_label();

void tb_raw_initialise_dummy_taint_policy(tb_raw_taint_policy_t *taint_policy) {

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

    taint_policy->get_default_label = get_dummy_default_label;
}

static void *get_dummy_default_label() {

    return (void *) 1;
}


static void insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t meet_reg, opnd_t *label_lowest_opnd,
        opnd_t *src1_opnd, reg_id_t scratch_reg) {

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
}

static void tb_simd_insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t meet_reg, opnd_t *label_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg) {

}

static void tb_simd_insert_propogate_1dst_1src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg) {

    // First move src1 to dst.
    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
            src1_vectorised_opnd, dst_vectorised_reg, pc);
}

static void tb_simd_insert_propogate_1dst_2src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        opnd_t *src2_vectorised_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_reg) {

    // First move src1 to dst.
    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
            src1_vectorised_opnd, dst_vectorised_reg, pc);
}

