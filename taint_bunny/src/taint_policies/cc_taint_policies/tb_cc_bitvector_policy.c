/*
 * tb_cc_bitvector_policy.c
 *
 *      Author: john
 */

#include "tb_cc_bitvector_policy.h"
#include "utility_bunny.h"
#include "string.h"

/**
 * Some notes:
 *  - We use the basic bit vector API provided by the UB (not the high-level ub_bitvector).
 *  - We assume that bit vectors always maintains the same size.
 */

/******************************************************************************************
 * PROTOTYPES
 */

static void *get_default_label();
static void increment_ref(void *bitvect_opaque);
static void delete_ref(void *bitvect_opaque);
static bool meet(void **meet_tl, void *src);
static void *propogate_func_1dst_1src(void *src_set1);
static void *propogate_func_1dst_2src(void *src1, void *src2);

/******************************************************************************************
 * Implementation
 */

static void *mutex;

DR_EXPORT void tb_cc_initialise_bitvector_taint_policy(
        tb_cc_taint_policy_t *taint_policy) {

    mutex = dr_mutex_create();

    memset(taint_policy, 0, sizeof(tb_cc_taint_policy_t));

    taint_policy->new_ref_tl_func = increment_ref;
    taint_policy->delete_ref_tl_func = delete_ref;

    taint_policy->meet_func = meet;
    taint_policy->propagate_1dst_1src_func = propogate_func_1dst_1src;
    taint_policy->propagate_1dst_2src_func = propogate_func_1dst_2src;

    taint_policy->get_default_label = get_default_label;
}

DR_EXPORT void tb_cc_destroy_bitvector_taint_policy(){

    DR_ASSERT(mutex);
    dr_mutex_destroy(mutex);
    mutex = NULL;
}

static void *get_default_label() {

    tb_bitvector_tl_t *bitvect = dr_global_alloc(sizeof(tb_bitvector_tl_t));
    ub_bitvect_basic_init(bitvect->bitvect, TB_BITVECT_SIZE);
    bitvect->count = 0;
    return bitvect;
}

static void *propogate_func_1dst_1src(void *src1_bitvect_opaque) {

    return src1_bitvect_opaque;
}

static void *propogate_func_1dst_2src(void *src_bitvect1_opaque,
        void *src_bitvect2_opaque) {

    tb_bitvector_tl_t *bitvect1 = (tb_bitvector_tl_t *) src_bitvect1_opaque;
    tb_bitvector_tl_t *bitvect2 = (tb_bitvector_tl_t *) src_bitvect2_opaque;

    if (!bitvect1 && !bitvect2)
        return NULL;

    tb_bitvector_tl_t *new_bitvect = dr_global_alloc(sizeof(tb_bitvector_tl_t));
    ub_bitvect_basic_init(new_bitvect->bitvect, TB_BITVECT_SIZE);
    new_bitvect->count = 0;

    if (bitvect1)
        ub_bitvect_basic_union(new_bitvect->bitvect, new_bitvect->bitvect,
                bitvect1->bitvect, TB_BITVECT_SIZE);

    if (bitvect2)
        ub_bitvect_basic_union(new_bitvect->bitvect, new_bitvect->bitvect,
                bitvect2->bitvect, TB_BITVECT_SIZE);

    return new_bitvect;
}

static bool meet(void **meet_tl, void *src) {

    if (src != NULL) {

        if (*meet_tl == NULL) {

            tb_bitvector_tl_t *new_bitvect = dr_global_alloc(
                    sizeof(tb_bitvector_tl_t));
            ub_bitvect_basic_init(new_bitvect->bitvect, TB_BITVECT_SIZE);
            new_bitvect->count = 0;

            *meet_tl = new_bitvect;
        }

        tb_bitvector_tl_t *src_set = (tb_bitvector_tl_t *) src;
        tb_bitvector_tl_t *meet_set = (tb_bitvector_tl_t *) *meet_tl;

        ub_bitvect_basic_union(meet_set->bitvect, meet_set->bitvect,
                src_set->bitvect, TB_BITVECT_SIZE);
    }

    return false;
}

static void increment_ref(void *bitvect_opaque) {

    dr_mutex_lock(mutex);

    tb_bitvector_tl_t *bitvect = (tb_bitvector_tl_t *) bitvect_opaque;
    bitvect->count++;
    dr_mutex_unlock(mutex);

}

static void delete_ref(void *bitvect_opaque) {

    dr_mutex_lock(mutex);

    tb_bitvector_tl_t *bitvect = (tb_bitvector_tl_t *) bitvect_opaque;

    DR_ASSERT(bitvect->count > 0);

    bitvect->count--;

    if (bitvect->count <= 0)
        dr_global_free(bitvect, sizeof(tb_bitvector_tl_t));

    dr_mutex_unlock(mutex);

}
