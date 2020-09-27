/*
 * tb_raw_tree.c
 *
 *      Author: john
 */

#include "tb_raw_bitvect_tree_policy.h"

#include "utility_bunny.h"
#include "drreg.h"

/*********************************************************************
 * Prototypes
 */

static void *tb_raw_tree_get_default_label();
static void insert_propogate_func_1dst_2src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        opnd_t * src2_opnd, reg_id_t scratch_reg_xcx);
static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t * src1_opnd,
        reg_id_t scratch_reg);
static void insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc app_instr, reg_id_t meet_reg,
        opnd_t *label_lowest_opnd, opnd_t *src1_opnd, reg_id_t scratch_reg);

static void insert_raw_spill_additional_regs(void *drcontext,
        instrlist_t *ilist, instr_t *where, bool is_inline);
static void insert_raw_restore_additional_regs(void *drcontext,
        instrlist_t *ilist, instr_t *where, bool is_inline);

/*********************************************************************
 * Global variables
 */

static void *tb_raw_tree_get_default_label() {

    return (void *) tb_raw_tree_get_label(0);
}

static int spinlock = 0;
static ub_bdd_node_t root_node = NULL;
static void *map;

/** This register must be XAX for spin-lock. TB guarantees that XAX is not used!**/
static reg_id_t additional_spill_reg_xax = DR_REG_XAX;

/* TODO reduce code duplication with CC imp */
#define COUNTER_MAX 32
static int counter = 0;
/*********************************************************************
 * Implementation
 */

static void *tb_raw_tree_get_label_helper(int index){

    ub_bitvect_t*bitvect = ub_bitvect_create(index + 1);
    ub_bitvect_set_bit(bitvect, index, true);

    ub_bdd_node_t node = ub_bdd_insert(root_node, bitvect);
    ub_two_key_value_pair_t key_val_pair;
    key_val_pair.value = (void *) node;
    key_val_pair.key1 = (uintptr_t) node;
    key_val_pair.key2 = (uintptr_t) node;
    ub_tk_arraymap_insert_entry(map, &key_val_pair);

	ub_bitvect_destroy(bitvect);
    return (void *) node;
}

DR_EXPORT void *tb_raw_tree_get_inc_default_label() {

	ub_sl_try_and_lock(&spinlock);

	void *new_label = (void *) tb_raw_tree_get_label_helper(counter);

	counter++;
	if (counter >= COUNTER_MAX)
		counter = 0;

	ub_sl_unlock(&spinlock);

	return new_label;
}


DR_EXPORT void tb_raw_initialise_tree_taint_policy(tb_raw_taint_policy_t *taint_policy) {

    drreg_options_t ops = { sizeof(ops), 2, false, NULL, false };
    if (drreg_init(&ops) != DRREG_SUCCESS)
        DR_ASSERT(false);

    root_node = ub_bdd_create();
    map = ub_tk_arraymap_create_map();

    memset(taint_policy, 0, sizeof(tb_raw_taint_policy_t));

    taint_policy->insert_raw_meet = insert_meet_func;
    taint_policy->insert_raw_propogate_1dst_1src =
            insert_propogate_func_1dst_1src;
    taint_policy->insert_raw_propogate_1dst_2src =
            insert_propogate_func_1dst_2src;

    taint_policy->insert_raw_spill_additional_regs =
            insert_raw_spill_additional_regs;
    taint_policy->insert_raw_restore_additional_regs =
            insert_raw_restore_additional_regs;

    taint_policy->get_default_label = tb_raw_tree_get_default_label;
}

DR_EXPORT void tb_raw_destroy_tree_taint_policy() {
    ub_bdd_destroy(root_node);
    root_node = NULL;

    ub_tk_arraymap_destroy_map(map, NULL);
    map = NULL;

    drreg_exit();
}

DR_EXPORT void * tb_raw_tree_get_label(int index){

	ub_sl_try_and_lock(&spinlock);
    void *result = tb_raw_tree_get_label_helper(index);
	ub_sl_unlock(&spinlock);

    return result;
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

static void cc_insert_new_bitvector(intptr_t key1, intptr_t key2,
        reg_id_t dst_reg) {

    void* drcontext = dr_get_current_drcontext();

    // Initialise machine context so that reg values may be retrieved.
    dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
    dr_get_mcontext(drcontext, &mcontext);

    ub_bdd_node_t res = ub_bdd_node_union(root_node, (ub_bdd_node_t) key1,
            (ub_bdd_node_t) key2);

    ub_two_key_value_pair_t key_val_pair;
    key_val_pair.value = (void *) res;

    void* old = NULL;

    /* Add the different combos to the map */
    key_val_pair.key1 = key1;
    key_val_pair.key2 = key2;
    old = ub_tk_arraymap_insert_entry(map, &key_val_pair);
    DR_ASSERT(!old);

    key_val_pair.key1 = key2;
    key_val_pair.key2 = key1;
    old = ub_tk_arraymap_insert_entry(map, &key_val_pair);
    DR_ASSERT(!old);

    key_val_pair.key1 = key1;
    key_val_pair.key2 = (uintptr_t) res;
    old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

    key_val_pair.key1 = (uintptr_t) res;
    key_val_pair.key2 = key1;
    old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

    key_val_pair.key1 = key2;
    key_val_pair.key2 = (uintptr_t) res;
    old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

    key_val_pair.key1 = (uintptr_t) res;
    key_val_pair.key2 = key2;
    old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

    key_val_pair.key1 = (uintptr_t) res;
    key_val_pair.key2 = (uintptr_t) res;
    old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

    // Set dst to refer to the new node.
    reg_set_value(dst_reg, &mcontext, (reg_t) res);

    // Don't forget to update the mcontext, as otherwise our change to dst reg won't be put to effect.
    dr_set_mcontext(drcontext, &mcontext);
}

static void insert_union(void *drcontext, instrlist_t *ilist, instr_t *where,
		app_pc pc, reg_id_t dst_key_reg, reg_id_t src1_key_reg, opnd_t *src1_opnd) {

    ub_sl_insert_try_and_lock(drcontext, ilist, where, additional_spill_reg_xax,
    		src1_key_reg, &spinlock);

	/* Load source to scratch */
    instr_t * instr = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(src1_key_reg), *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    ub_tk_arraymap_insert_lookup(map, drcontext, ilist, where, dst_key_reg,
            src1_key_reg, additional_spill_reg_xax);

    instr_t *found_label = INSTR_CREATE_label(drcontext);

    ub_instrum_check_null_false_case(drcontext, ilist, where,
            additional_spill_reg_xax, found_label);

    // We need to perform a clean call because we encountered a new bitvector combination!
    dr_insert_clean_call(drcontext, ilist, where, cc_insert_new_bitvector,
    false, 3, opnd_create_reg(dst_key_reg), opnd_create_reg(src1_key_reg),
    OPND_CREATE_INTPTR(additional_spill_reg_xax));

    instrlist_meta_preinsert(ilist, where, found_label);

    ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, additional_spill_reg_xax, dst_key_reg);

    ub_sl_insert_unlock(drcontext, ilist, where, &spinlock);
}

static void insert_meet_func(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t meet_reg, opnd_t *label_lowest_opnd,
        opnd_t *src1_opnd, reg_id_t scratch_reg) {

	/* Load source to scratch */
    instr_t * instr = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(scratch_reg), *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    /* If source is null, just jump to done label */
    instr_t *done_label = INSTR_CREATE_label(drcontext);
    ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
            done_label);

    instr_t *meet_is_not_null_label = INSTR_CREATE_label(drcontext);
    ub_instrum_check_null_false_case(drcontext, ilist, where, meet_reg,
            meet_is_not_null_label);

    /* If meet is NULL, move source to meet */
    ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, scratch_reg,
            meet_reg);
    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, meet_is_not_null_label);

    /* If both meet and source are tainted, then perform union */
    insert_union(drcontext, ilist, where, pc, meet_reg, scratch_reg, src1_opnd);

    instrlist_meta_preinsert(ilist, where, done_label);
}

static void insert_propogate_func_1dst_1src(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc pc, reg_id_t dst_reg, opnd_t *src1_opnd,
        reg_id_t scratch_reg) {

	/* Simply load source to destination reg */
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

    /* Load the label to scratch*/
    instr_t * instr = INSTR_CREATE_mov_ld(drcontext,
            opnd_create_reg(scratch_reg), *src1_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    /* Load the label to dst reg*/
    instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(dst_reg),
            *src2_opnd);
    instr_set_translation(instr, pc);
    instrlist_meta_preinsert(ilist, where, instr);

    /* If source is NULL, jump to done. The second source is already in dst */
    ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
            done_label);

    ub_instrum_check_null_true_case(drcontext, ilist, where, dst_reg,
            src_is_null_label);

    /* If both sources are tainted, we perform a union! */
    insert_union(drcontext, ilist, where, pc, dst_reg, scratch_reg, src1_opnd);

    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, src_is_null_label);

    /* Simply move label of first source in dst */
    ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, scratch_reg, dst_reg);

    instrlist_meta_preinsert(ilist, where, done_label);
}



/******
 * SIMD
 */

static void insert_simd_union(void *drcontext, instrlist_t *ilist, instr_t *where,
		app_pc pc, reg_id_t dst_key_reg, reg_id_t src1_key_reg, reg_id_t scaler_scratch) {

//    ub_sl_insert_try_and_lock(drcontext, ilist, where, additional_spill_reg_xax,
//    		scaler_scratch, &spinlock);
//
//    ub_tk_arraymap_insert_lookup(map, drcontext, ilist, where, dst_key_reg,
//            src1_key_reg, additional_spill_reg_xax);
//
//    instr_t *found_label = INSTR_CREATE_label(drcontext);
//
//    ub_instrum_check_null_false_case(drcontext, ilist, where,
//            additional_spill_reg_xax, found_label);
//
//    // We need to perform a clean call because we encountered a new bit-vector combination!
//    dr_insert_clean_call(drcontext, ilist, where, cc_insert_new_bitvector,
//    false, 3, opnd_create_reg(dst_key_reg), opnd_create_reg(src1_key_reg),
//    OPND_CREATE_INTPTR(additional_spill_reg_xax));
//
//    instrlist_meta_preinsert(ilist, where, found_label);
//
//    ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, additional_spill_reg_xax, dst_key_reg);
//
//    ub_sl_insert_unlock(drcontext, ilist, where, &spinlock);
}

static void tb_simd_insert_propogate_1dst_1src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg) {

//    // Check that the registers are xmm registers.
//    DR_ASSERT(reg_is_xmm(dst_vectorised_reg));
//    DR_ASSERT(reg_is_xmm(scratch_vectorised_reg));
//    DR_ASSERT(reg_is_gpr(scratch_reg));
//
//     ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
//            src1_vectorised_opnd, dst_vectorised_reg, pc);
}

static void tb_simd_insert_propogate_1dst_2src_func(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc pc,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        opnd_t *src2_vectorised_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_reg) {

//    instr_t *union_label = INSTR_CREATE_label(drcontext);
//    instr_t *done_label = INSTR_CREATE_label(drcontext);
//
//	/* Load the source to scratch reg */
//    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
//            src1_vectorised_opnd, scratch_vectorised_reg, pc);
//
//	/* Load the 2nd source to dst reg */
//    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
//    		src2_vectorised_opnd, dst_vectorised_reg, pc);
//
//    ub_instrum_check_simd_null_true_case(drcontext, ilist, where,
//            scratch_vectorised_reg, done_label);
//
//    ub_instrum_check_simd_null_false_case(drcontext, ilist, where,
//    		dst_vectorised_reg, union_label);
//
//    ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(drcontext, ilist, where,
//    		opnd_create_reg(scratch_vectorised_reg), dst_vectorised_reg, pc);
//
//    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);
//
//    instrlist_meta_preinsert(ilist, where, union_label);
//
//
//    instrlist_meta_preinsert(ilist, where, done_label);
}

