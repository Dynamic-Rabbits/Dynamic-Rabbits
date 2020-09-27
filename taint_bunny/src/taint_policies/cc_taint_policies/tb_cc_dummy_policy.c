/*
 * tb_dummy_policy.c
 *
 *      Author: john
 */

#include "tb_cc_dummy_policy.h"

static void *get_dummy_default_label();
static void * propogate_1dst_1src(void *src1);
static void * propogate_1dst_2src(void *src1, void *src2);
static bool meet(void **meet, void *src);

DR_EXPORT void tb_cc_initialise_dummy_taint_policy(tb_cc_taint_policy_t *taint_policy) {

    memset(taint_policy, 0, sizeof(tb_cc_taint_policy_t));

	taint_policy->meet_func = meet;
    taint_policy->propagate_1dst_1src_func = propogate_1dst_1src;
	taint_policy->propagate_1dst_2src_func = propogate_1dst_2src;

    taint_policy->get_default_label = get_dummy_default_label;
}

static void *get_dummy_default_label() {

    return (void *) 1;
}

static bool meet(void **meet, void *src) {

	return true;
}

static void * propogate_1dst_1src(void *src1) {

    return src1;
}

static void * propogate_1dst_2src(void *src1, void *src2) {

	return src1;
}
