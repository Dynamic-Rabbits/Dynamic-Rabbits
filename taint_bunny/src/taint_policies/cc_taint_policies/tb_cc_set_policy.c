/*
 * tb_set_policy.c
 *
 *      Author: john
 */

#include "tb_cc_set_policy.h"

static void * propogate_func_1dst_1src(void *src_set1);
static void * propogate_func_1dst_2src(void *src1, void *src2);

static void *get_default_label();
static void increment_set(void *set_opaque);
static void delete_set(void *set_opaque);
static bool meet(void **meet_tl, void *src);

/**
 * Not thread safe.
 * Keep calm, it's just a prototype.
 */

unsigned int counter = 1;

DR_EXPORT void tb_cc_initialise_set_taint_policy(
        tb_cc_taint_policy_t *taint_policy) {

    memset(taint_policy, 0, sizeof(tb_cc_taint_policy_t));

    taint_policy->new_ref_tl_func = increment_set;
    taint_policy->delete_ref_tl_func = delete_set;

    taint_policy->meet_func = meet;
    taint_policy->propagate_1dst_1src_func = propogate_func_1dst_1src;
    taint_policy->propagate_1dst_2src_func = propogate_func_1dst_2src;

    taint_policy->get_default_label = get_default_label;
}

static void *get_default_label() {

    tb_set_tl_t *src1_set = dr_global_alloc(sizeof(tb_set_tl_t));

    src1_set->set = ub_intptr_hashset_create();
    ub_intptr_hashset_insert(src1_set->set, (uintptr_t) counter);
    src1_set->count = 0;

    counter++;

    return src1_set;
}

static void * propogate_func_1dst_1src(void *src_set1_opaque) {

    return src_set1_opaque;
}

static void * propogate_func_1dst_2src(void *src_set1_opaque,
        void *src_set2_opaque) {

    tb_set_tl_t *src1_set = (tb_set_tl_t *) src_set1_opaque;
    tb_set_tl_t *src2_set = (tb_set_tl_t *) src_set2_opaque;

    if (!src1_set && !src2_set)
        return NULL;

    tb_set_tl_t *set = dr_global_alloc(sizeof(tb_set_tl_t));
    set->set = ub_intptr_hashset_create();
    set->count = 0;

    if (src1_set)
        ub_intptr_hashset_union(set->set, src1_set->set);

    if (src2_set)
        ub_intptr_hashset_union(set->set, src2_set->set);

    return set;
}

static bool meet(void **meet_tl, void *src) {

    if (src != NULL) {

        if (*meet_tl == NULL) {

            tb_set_tl_t *set = dr_global_alloc(sizeof(tb_set_tl_t));
            set->set = ub_intptr_hashset_create();
            set->count = 0;
            *meet_tl = set;
        }

        tb_set_tl_t *src_set = (tb_set_tl_t *) src;
        tb_set_tl_t *join_set = (tb_set_tl_t *) *meet_tl;
        ub_intptr_hashset_union(join_set->set, src_set->set);
    }

    return false;
}

static void increment_set(void *set_opaque) {

    tb_set_tl_t *set = (tb_set_tl_t *) set_opaque;
    set->count++;
}

static void delete_set(void *set_opaque) {

    tb_set_tl_t *set = (tb_set_tl_t *) set_opaque;

    set->count--;

    if (set->count <= 0) {
        ub_intptr_hashset_destroy(set->set);
        set->set = NULL;
        dr_global_free(set, sizeof(tb_set_tl_t));
    }
}
