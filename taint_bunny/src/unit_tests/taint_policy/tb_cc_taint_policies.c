/*
 * tb_cc_taint_policies.c
 *
 *      Author: john
 */

#include <stddef.h>
#include "utility_bunny.h"
#include "instrumentation_bunny.h"

#include "../../taint_policies/cc_taint_policies/tb_cc_bitwise_policy.h"
#include "../../taint_policies/cc_taint_policies/tb_cc_set_policy.h"
#include "../../taint_policies/cc_taint_policies/tb_cc_dst_id_policy.h"
#include "../../taint_policies/cc_taint_policies/tb_cc_bitvector_policy.h"

static void event_exit() {

    drmgr_exit();
}

void test_bitwise_policy() {

    tb_cc_taint_policy_t taint_policy;
    tb_cc_initialise_bitwise_taint_policy(&taint_policy);

    DR_ASSERT(taint_policy.meet_func);
    DR_ASSERT(taint_policy.propagate_1dst_2src_func);
    DR_ASSERT(taint_policy.propagate_1dst_1src_func);

    void *tainted = (void *) (intptr_t) 1;
    void *untainted = (void *) (intptr_t) 0;

    DR_ASSERT(
            taint_policy.propagate_1dst_2src_func(tainted, untainted) != NULL);
    DR_ASSERT(taint_policy.propagate_1dst_2src_func(tainted, tainted) != NULL);
    DR_ASSERT(
            taint_policy.propagate_1dst_2src_func(untainted, tainted) != NULL);
    DR_ASSERT(
            taint_policy.propagate_1dst_2src_func(untainted, untainted) == NULL);

    DR_ASSERT(taint_policy.propagate_1dst_1src_func(tainted) != NULL);
    DR_ASSERT(taint_policy.propagate_1dst_1src_func(untainted) == NULL);

    bool is_top = taint_policy.meet_func(&tainted, untainted);
    DR_ASSERT(is_top);
    DR_ASSERT(tainted != NULL);

    is_top = taint_policy.meet_func(&untainted, untainted);
    DR_ASSERT(!is_top);
    DR_ASSERT(untainted == NULL);
}

void test_set_policy() {

    tb_cc_taint_policy_t taint_policy;
    tb_cc_initialise_set_taint_policy(&taint_policy);

    DR_ASSERT(taint_policy.meet_func);
    DR_ASSERT(taint_policy.propagate_1dst_1src_func);
    DR_ASSERT(taint_policy.propagate_1dst_2src_func);

    DR_ASSERT(taint_policy.delete_ref_tl_func);

    tb_set_tl_t set1;
    set1.set = ub_intptr_hashset_create();
    ub_intptr_hashset_insert(set1.set, 1);

    tb_set_tl_t set2;
    set2.set = ub_intptr_hashset_create();
    ub_intptr_hashset_insert(set2.set, 2);

    tb_set_tl_t set3;
    set3.set = ub_intptr_hashset_create();
    ub_intptr_hashset_insert(set3.set, 3);

    tb_set_tl_t *ret_set = taint_policy.propagate_1dst_2src_func(&set1, NULL);
    DR_ASSERT(
            ub_intptr_hashset_is_included(ret_set->set, 1)
                    && ub_intptr_hashset_get_size(ret_set->set) == 1);
    taint_policy.delete_ref_tl_func(ret_set);

    ret_set = taint_policy.propagate_1dst_2src_func(NULL, &set1);
    DR_ASSERT(
            ub_intptr_hashset_is_included(ret_set->set, 1)
                    && ub_intptr_hashset_get_size(ret_set->set) == 1);
    taint_policy.delete_ref_tl_func(ret_set);

    ret_set = taint_policy.propagate_1dst_2src_func(&set2, &set1);
    DR_ASSERT(
            ub_intptr_hashset_is_included(ret_set->set, 1)
                    && ub_intptr_hashset_is_included(ret_set->set, 2)
                    && ub_intptr_hashset_get_size(ret_set->set) == 2);
    taint_policy.delete_ref_tl_func(ret_set);

    ret_set = taint_policy.propagate_1dst_2src_func(NULL, NULL);
    DR_ASSERT(ret_set == NULL);

    ret_set = taint_policy.propagate_1dst_1src_func(&set1);
    DR_ASSERT(
            ub_intptr_hashset_is_included(ret_set->set, 1)
                    && ub_intptr_hashset_get_size(ret_set->set) == 1);

    ret_set = taint_policy.propagate_1dst_1src_func(NULL);
    DR_ASSERT(ret_set == NULL);

    ret_set = NULL;
    bool is_top = taint_policy.meet_func((void **) &ret_set, &set1);
    DR_ASSERT(!is_top);
    DR_ASSERT(
            ub_intptr_hashset_is_included(ret_set->set, 1)
                    && ub_intptr_hashset_get_size(ret_set->set) == 1);
    taint_policy.delete_ref_tl_func(ret_set);

    ret_set = NULL;
    is_top = taint_policy.meet_func((void **) &ret_set, NULL);
    DR_ASSERT(!is_top);
    DR_ASSERT(!ret_set);

    ub_intptr_hashset_destroy(set1.set);
    ub_intptr_hashset_destroy(set2.set);
    ub_intptr_hashset_destroy(set3.set);
}

void test_id_policy() {

    tb_cc_taint_policy_t taint_policy;
    tb_cc_initialise_id_taint_policy(&taint_policy);

    DR_ASSERT(taint_policy.meet_func);
    DR_ASSERT(taint_policy.propagate_1dst_1src_func);
    DR_ASSERT(taint_policy.propagate_1dst_2src_func);

    tb_set_tl_t set;

    set.set = ub_intptr_hashset_create();
    for (uint32_t i = 0; i < 10000; i++) {
        uint32_t id = (uint32_t) taint_policy.propagate_1dst_1src_func(
                (void *) 1);
        DR_ASSERT(id != 0);
        bool already_inserted = ub_intptr_hashset_insert(set.set, id);
        DR_ASSERT(already_inserted);
    }
    ub_intptr_hashset_destroy(set.set);

    set.set = ub_intptr_hashset_create();
    for (uint32_t i = 0; i < 100; i++) {
        uint32_t id = (uint32_t) taint_policy.propagate_1dst_2src_func(
                (void *) 1, (void *) 1);
        DR_ASSERT(id != 0);
        bool already_inserted = ub_intptr_hashset_insert(set.set, id);
        DR_ASSERT(already_inserted);
    }
    ub_intptr_hashset_destroy(set.set);

    DR_ASSERT(taint_policy.propagate_1dst_1src_func(
            (void *) 1));
    DR_ASSERT(!taint_policy.propagate_1dst_1src_func(
            NULL));

    DR_ASSERT(taint_policy.propagate_1dst_2src_func(
                (void *) 1, (void *) 1));
    DR_ASSERT(taint_policy.propagate_1dst_2src_func(
                    (void *) 1, NULL));
    DR_ASSERT(taint_policy.propagate_1dst_2src_func(
                    NULL, (void *) 1));
    DR_ASSERT(!taint_policy.propagate_1dst_2src_func(
                    NULL, NULL));
}


void test_bitvect_policy() {

    tb_cc_taint_policy_t taint_policy;
    tb_cc_initialise_bitvector_taint_policy(&taint_policy);

    DR_ASSERT(taint_policy.meet_func);
    DR_ASSERT(taint_policy.propagate_1dst_1src_func);
    DR_ASSERT(taint_policy.propagate_1dst_2src_func);

    tb_bitvector_tl_t new_bitvect;
    ub_bitvect_basic_init(new_bitvect.bitvect, TB_BITVECT_SIZE);
    new_bitvect.count = 1;

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(new_bitvect.bitvect[i] == 0);
    }

    tb_bitvector_tl_t new_bitvect2;
    ub_bitvect_basic_init(new_bitvect2.bitvect, TB_BITVECT_SIZE);
    new_bitvect2.count = 1;

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(new_bitvect2.bitvect[i] == 0);
    }

    tb_bitvector_tl_t *ret_bit_vect = taint_policy.propagate_1dst_2src_func(
            &new_bitvect, &new_bitvect2);
    DR_ASSERT(ret_bit_vect != NULL);

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(ret_bit_vect->bitvect[i] == 0);
    }
    dr_global_free(ret_bit_vect, sizeof(tb_bitvector_tl_t));

    ret_bit_vect = taint_policy.propagate_1dst_1src_func(
            &new_bitvect);
    DR_ASSERT(ret_bit_vect != NULL);

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(ret_bit_vect->bitvect[i] == 0);
    }

    /* Second setup */

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(new_bitvect2.bitvect[i] == 0);
        new_bitvect.bitvect[i] = 0x01;
    }

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(new_bitvect2.bitvect[i] == 0);
        new_bitvect2.bitvect[i] = 0x02;
    }

    ret_bit_vect = taint_policy.propagate_1dst_2src_func(
            &new_bitvect, &new_bitvect2);
    DR_ASSERT(ret_bit_vect != NULL);

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(ret_bit_vect->bitvect[i] = 0x03);
    }

    ret_bit_vect = taint_policy.propagate_1dst_1src_func(
            ret_bit_vect);
    DR_ASSERT(ret_bit_vect != NULL);

    for (int i = 0; i < TB_BITVECT_SIZE; i++){
        DR_ASSERT(ret_bit_vect->bitvect[i] = 0x03);
    }

    dr_global_free(ret_bit_vect, sizeof(tb_bitvector_tl_t));

    tb_cc_destroy_bitvector_taint_policy();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();

    test_bitwise_policy();
    test_set_policy();
    test_id_policy();
    test_bitvect_policy();

    dr_register_exit_event(event_exit);
}

