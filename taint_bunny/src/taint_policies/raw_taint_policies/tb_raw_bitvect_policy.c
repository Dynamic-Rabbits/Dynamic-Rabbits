/*
 * tb_raw_bitvect_policy.c
 *
 *      Author: john
 */

#include "tb_raw_bitvect_policy.h"
#include "../cc_taint_policies/tb_cc_bitvector_policy.h"
#include "utility_bunny.h"
#include "drreg.h"

/*********************************************************************
 * Prototypes
 */

static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg_xcx);
static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        reg_id_t scratch_reg);
static void insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc app_instr, reg_id_t meet_reg,
        opnd_t *label_lowest_opnd, opnd_t *src1_opnd, reg_id_t scratch_reg);

static void *tb_raw_bitvector_get_default_label();

static void insert_raw_spill_additional_regs(void *drcontext,
        instrlist_t *ilist, instr_t *where, bool is_inline);
static void insert_raw_restore_additional_regs(void *drcontext,
        instrlist_t *ilist, instr_t *where, bool is_inline);

static void tb_new_ref_tl(void *val);
static void tb_delete_ref_tl(void *val);

static void tb_raw_insert_new_ref_tl(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t taint_label, reg_id_t scratch_reg);
static void tb_raw_insert_delete_ref_tl(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t taint_label, reg_id_t scratch_reg);

/*********************************************************************
 * Global variables
 */

static void *tb_label_allocator = NULL;

/** This register must be XAX for spin-lock. TB guarantees that XAX is not used!**/
static reg_id_t additional_spill_reg_xax = DR_REG_XAX;

reg_id_t tls_raw_reg;
uint tls_raw_base;

static int spinlock = 0;

/*********************************************************************
 * Implementation
 */

void tb_raw_initialise_bitvector_taint_policy(
        tb_raw_taint_policy_t *taint_policy) {

    drreg_options_t ops = { sizeof(ops), 2, false, NULL, false };
    if (drreg_init(&ops) != DRREG_SUCCESS)
        DR_ASSERT(false);

    // Create allocator responsible for memory management of labels
    tb_label_allocator = ub_create_fixed_allocator(3,
            sizeof(tb_bitvector_tl_t));

    dr_raw_tls_calloc(&(tls_raw_reg), &(tls_raw_base), 1, 0);

    memset(taint_policy, 0, sizeof(tb_raw_taint_policy_t));

    taint_policy->insert_raw_meet = insert_meet_func;
    taint_policy->insert_raw_propogate_1dst_1src =
            insert_propogate_func_1dst_1src;
    taint_policy->insert_raw_propogate_1dst_2src =
            insert_propogate_func_1dst_2src;

    taint_policy->new_ref_tl_func = tb_new_ref_tl;
    taint_policy->delete_ref_tl_func = tb_delete_ref_tl;

    taint_policy->insert_raw_new_ref_tl = tb_raw_insert_new_ref_tl;
    taint_policy->insert_raw_delete_ref_tl = tb_raw_insert_delete_ref_tl;

    taint_policy->get_default_label = tb_raw_bitvector_get_default_label;

    taint_policy->insert_raw_spill_additional_regs =
            insert_raw_spill_additional_regs;
    taint_policy->insert_raw_restore_additional_regs =
            insert_raw_restore_additional_regs;
}

void tb_raw_destroy_bitvector_taint_policy() {

    dr_raw_tls_cfree(tls_raw_base, 1);
    ub_destroy_fixed_allocator(tb_label_allocator);
    tb_label_allocator = NULL;
    drreg_exit();
}

static void *tb_raw_bitvector_get_default_label() {

    ub_sl_try_and_lock(&spinlock);
    tb_bitvector_tl_t *bitvect = ub_allocate(tb_label_allocator);
    ub_sl_unlock(&spinlock);

    // Clear the vector
    memset(bitvect->bitvect, 0, TB_BITVECT_SIZE);
    bitvect->count = 0;

    return bitvect;
}

static void insert_raw_spill_additional_regs(void *drcontext,
        instrlist_t *ilist, instr_t *where, bool is_inline) {

    drvector_t allowed;
    drreg_init_and_fill_vector(&allowed, false);
    drreg_set_vector_entry(&allowed, DR_REG_XAX, true);
    if (drreg_reserve_register(drcontext, ilist, where, &allowed,
            &additional_spill_reg_xax) != DRREG_SUCCESS)
        DR_ASSERT(false); /* cannot recover */

    DR_ASSERT(additional_spill_reg_xax == DR_REG_XAX);
    drvector_delete(&allowed);
}

static void insert_raw_restore_additional_regs(void *drcontext,
        instrlist_t *ilist, instr_t *where, bool is_inline) {

    if (drreg_unreserve_register(drcontext, ilist, where,
            additional_spill_reg_xax) != DRREG_SUCCESS)
        DR_ASSERT(false);
}

static void tb_new_ref_tl(void *val) {

    if (!val)
        return;

    ub_sl_try_and_lock(&spinlock);

    tb_bitvector_tl_t *bitvect = val;
    bitvect->count++;

    ub_sl_unlock(&spinlock);
}

static void tb_delete_ref_tl(void *val) {

    if (!val)
        return;

    ub_sl_try_and_lock(&spinlock);

    tb_bitvector_tl_t *bitvect = val;
    DR_ASSERT(bitvect->count > 0);

    bitvect->count--;

    // if the counter has reached 0, we perform a deallocation.
    if (bitvect->count <= 0)
        ub_deallocate(tb_label_allocator, bitvect);

    ub_sl_unlock(&spinlock);
}

static void tb_raw_insert_new_ref_tl(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t taint_label, reg_id_t scratch_reg) {

    ub_sl_insert_try_and_lock(drcontext, ilist, where, additional_spill_reg_xax,
            scratch_reg, &spinlock);

    // Increment reference counter.
    ub_instrum_inc_mem(drcontext, ilist, where, taint_label,
            offsetof(tb_bitvector_tl_t, count));

    ub_sl_insert_unlock(drcontext, ilist, where, &spinlock);
}

static void tb_raw_insert_delete_ref_tl(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t taint_label, reg_id_t scratch_reg) {

    ub_sl_insert_try_and_lock(drcontext, ilist, where, additional_spill_reg_xax,
            scratch_reg, &spinlock);

    ub_instrum_dec_mem(drcontext, ilist, where, taint_label,
            offsetof(tb_bitvector_tl_t, count));

    instr_t *not_zero_label = INSTR_CREATE_label(drcontext);

    instr_t *jmp_instr = INSTR_CREATE_jcc(drcontext, OP_jnz,
            opnd_create_instr(not_zero_label));
    instrlist_meta_preinsert(ilist, where, jmp_instr);

    // We have reached the zero count. We need to deallocate!
    ub_insert_dealloation(tb_label_allocator, drcontext, ilist, where,
            taint_label, additional_spill_reg_xax, scratch_reg);

    instrlist_meta_preinsert(ilist, where, not_zero_label);

    ub_sl_insert_unlock(drcontext, ilist, where, &spinlock);
}

static void insert_create_copy(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t new_reg, reg_id_t src_reg, reg_id_t size_reg,
        reg_id_t scratch_xax) {

    DR_ASSERT(scratch_xax == DR_REG_XAX);

    /* Allocate new vector */
    ub_sl_insert_try_and_lock(drcontext, ilist, where, scratch_xax, new_reg,
            &spinlock);
    ub_insert_allocation(tb_label_allocator, drcontext, ilist, where, new_reg,
            scratch_xax);
    ub_sl_insert_unlock(drcontext, ilist, where, &spinlock);

    // Set the ref counter to 0.
    ub_instrum_clear_mem(drcontext, ilist, where, new_reg,
            offsetof(tb_bitvector_tl_t, count));

    DR_ASSERT(offsetof(tb_bitvector_tl_t, bitvect) == 0);

    ub_bitvect_basic_insert_copy(drcontext, ilist, where, new_reg, src_reg,
            size_reg, scratch_xax);
}

static reg_id_t get_spill_reg(opnd_t src_opnd) {

    if (opnd_is_reg(src_opnd))
        return opnd_get_reg(src_opnd);
    else if (opnd_is_memory_reference(src_opnd))
        return opnd_get_base(src_opnd);
    else
        DR_ASSERT(false);

    return DR_REG_NULL;
}

static void insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t meet_reg, opnd_t *label_lowest_opnd,
        opnd_t *src1_opnd, reg_id_t scratch_reg) {

    /* Load pointer to bitvector. */
    instr_t * instr = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(scratch_reg), *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    instr_t *src_is_null_label = INSTR_CREATE_label(drcontext);
    ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
            src_is_null_label);

    opnd_t spill_opnd = opnd_create_far_base_disp_ex(tls_raw_reg,
    REG_NULL, REG_NULL, 1, tls_raw_base, OPSZ_4, false, true, false);

    reg_id_t additional_spill_reg2 = get_spill_reg(*src1_opnd);
    DR_ASSERT(meet_reg != additional_spill_reg2);

    ub_instrum_mov_st_reg_to_mem_opnd(drcontext, ilist, where,
            additional_spill_reg2, &spill_opnd);

    /* Load the size to register. */
    ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, TB_BITVECT_SIZE,
            additional_spill_reg2);

    instr_t *meet_is_null_label = INSTR_CREATE_label(drcontext);
    ub_instrum_check_null_false_case(drcontext, ilist, where, meet_reg,
            meet_is_null_label);

    insert_create_copy(drcontext, ilist, where, meet_reg, scratch_reg,
            additional_spill_reg2, additional_spill_reg_xax);

    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &spill_opnd,
            additional_spill_reg2);

    ub_instrum_direct_jmp(drcontext, ilist, where, src_is_null_label);

    instrlist_meta_preinsert(ilist, where, meet_is_null_label);

    /* Now perform union */
    ub_bitvect_basic_insert_union(drcontext, ilist, where, meet_reg,
            scratch_reg, additional_spill_reg2, additional_spill_reg_xax);

    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &spill_opnd,
            additional_spill_reg2);

    instrlist_meta_preinsert(ilist, where, src_is_null_label);
}

static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t *src1_opnd,
        reg_id_t scratch_reg) {

    opnd_t dst_opnd = opnd_create_reg(dst_reg);
    instr_t * instr = INSTR_CREATE_mov_ld(drcontext, dst_opnd, *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);
}

static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t *src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg) {

    instr_t *src_is_null_label = INSTR_CREATE_label(drcontext);
    instr_t *done_label = INSTR_CREATE_label(drcontext);

    opnd_t spill_opnd = opnd_create_far_base_disp_ex(tls_raw_reg,
    REG_NULL, REG_NULL, 1, tls_raw_base, OPSZ_4, false, true, false);
    reg_id_t additional_spill_reg2 = get_spill_reg(*src1_opnd);
    DR_ASSERT(dst_reg != additional_spill_reg2);

    // Load the label
    instr_t * instr = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(scratch_reg), *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    ub_instrum_mov_st_reg_to_mem_opnd(drcontext, ilist, where,
            additional_spill_reg2, &spill_opnd);

    ub_instrum_clear_reg(drcontext, ilist, where, dst_reg);

    /* Load the size to register. */
    ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, TB_BITVECT_SIZE,
            additional_spill_reg2);

    ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
            src_is_null_label);

    /* Copy first bitvector to second */
    insert_create_copy(drcontext, ilist, where, dst_reg, scratch_reg,
            additional_spill_reg2, additional_spill_reg_xax);

    // Load the label
    instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(scratch_reg),
            *src2_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
            done_label);

    /* If both sources are tainted, we perform a union! */

    /* Load the size to register again as it was corrupted when handling the first src */
    ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, TB_BITVECT_SIZE,
            additional_spill_reg2);

    ub_bitvect_basic_insert_union(drcontext, ilist, where, dst_reg, scratch_reg,
            additional_spill_reg2, additional_spill_reg_xax);

    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, src_is_null_label);

    // Load the label
    instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(scratch_reg),
            *src2_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    /* If true, both srcs are null and we can simply jump to the done label! */
    ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
            done_label);

    /* Copy second bitvector to dst */
    insert_create_copy(drcontext, ilist, where, dst_reg, scratch_reg,
            additional_spill_reg2, additional_spill_reg_xax);

    instrlist_meta_preinsert(ilist, where, done_label);

    ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &spill_opnd,
            additional_spill_reg2);
}

