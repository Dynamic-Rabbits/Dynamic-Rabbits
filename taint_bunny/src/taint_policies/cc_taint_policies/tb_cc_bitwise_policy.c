/*
 * tb_bitwise_policy.c
 *
 *      Author: john
 */

#include "tb_cc_bitwise_policy.h"

static void *tb_cc_bitwise_get_default_label();
static void * propogate_1dst_1src(void *src1);
static void * propogate_1dst_2src(void *src1, void *src2);
static bool meet(void **meet, void *src);

DR_EXPORT void tb_cc_initialise_bitwise_taint_policy(
		tb_cc_taint_policy_t *taint_policy) {

    memset(taint_policy, 0, sizeof(tb_cc_taint_policy_t));

	taint_policy->meet_func = meet;
    taint_policy->propagate_1dst_1src_func = propogate_1dst_1src;
	taint_policy->propagate_1dst_2src_func = propogate_1dst_2src;

    taint_policy->get_default_label = tb_cc_bitwise_get_default_label;
}

static void *tb_cc_bitwise_get_default_label(){

    return (void *) 1;
}

static bool meet(void **meet, void *src) {

	if (src)
		*meet = src;

	if (*meet)
		return true;

	return false;
}

static void * propogate_1dst_1src(void *src1) {

    return (void *) ((uintptr_t) src1);
}

static void * propogate_1dst_2src(void *src1, void *src2) {

    return (void *) ((uintptr_t) src1 | (uintptr_t) src2);
}
