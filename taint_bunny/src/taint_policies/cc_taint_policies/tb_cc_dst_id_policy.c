/*
 * tb_cc_dst_id_policy.c
 *
 *      Author: john
 */

#include "tb_cc_dst_id_policy.h"
#include <limits.h>

static void *get_result();
static void * get_default_label();
static void * propogate_1dst_1src(void *src1);
static void * propogate_1dst_2src(void *src1, void *src2);
static bool meet(void **meet, void *src);

/**
 * Not thread safe for now ...
 * Keep calm, its just a protoype.
 */

static unsigned int id_counter;

DR_EXPORT void tb_cc_initialise_id_taint_policy(
        tb_cc_taint_policy_t *taint_policy) {

    memset(taint_policy, 0, sizeof(tb_cc_taint_policy_t));

    id_counter = 0;
    taint_policy->meet_func = meet;
    taint_policy->propagate_1dst_1src_func = propogate_1dst_1src;
    taint_policy->propagate_1dst_2src_func = propogate_1dst_2src;

    taint_policy->get_default_label = get_default_label;
}

static bool meet(void **meet, void *src) {

    if (src)
        *meet = src;

    if (*meet)
        return true;

    return false;
}

static void *get_result() {

    if (id_counter == UINT32_MAX) {
        id_counter = 0;
    }

    // If src is tainted inc counter and return.
    id_counter++;

    return (void *) (uintptr_t) id_counter;
}

static void * get_default_label(){

    return get_result();

}

static void * propogate_1dst_1src(void *src1) {

    if (src1) {

        return get_result();
    }

    return NULL;
}

static void * propogate_1dst_2src(void *src1, void *src2) {

    if (src1 || src2){
        return get_result();
    }

    return NULL;
}

