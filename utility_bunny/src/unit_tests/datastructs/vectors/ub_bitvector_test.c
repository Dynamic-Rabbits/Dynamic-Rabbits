/*
 * bit_vector_test.c
 *
 *      Author: john
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../utility_bunny.h"

void test1() {

    ub_bitvect_t *bitvect = ub_bitvect_create(10);

    for (size_t i = 0; i < 10; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect, i) == false);
    }

    ub_bitvect_println(bitvect);

    ub_bitvect_destroy(bitvect);
}

void test2() {
    ub_bitvect_t *bitvect = ub_bitvect_create(10);

    for (size_t i = 0; i < 10; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect, i) == false);
    }

    for (size_t i = 0; i < 10; i++) {
        ub_bitvect_set_bit(bitvect, i, true);
    }

    for (size_t i = 0; i < 10; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect, i) == true);
    }

    ub_bitvect_println(bitvect);

    ub_bitvect_destroy(bitvect);
}

void test3() {

    ub_bitvect_t *bitvect = ub_bitvect_create(100);

    for (size_t i = 0; i < 100; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect, i) == false);
    }

    for (size_t i = 0; i < 10; i++) {
        ub_bitvect_set_bit(bitvect, i, true);
    }

    ub_bitvect_destroy(bitvect);
}

void test4() {

    ub_bitvect_t *bitvect = ub_bitvect_create(100);
    ub_bitvect_t *bitvect2 = ub_bitvect_create(100);

    for (size_t i = 0; i < 10; i++) {
        ub_bitvect_set_bit(bitvect, i, true);
    }

    ub_bitvect_t *bitvect3 = ub_bitvect_union(bitvect, bitvect2);

    for (size_t i = 0; i < 10; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect3, i) == true);
    }

    for (size_t i = 10; i < 100; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect3, i) == false);
    }

    ub_bitvect_destroy(bitvect);
    ub_bitvect_destroy(bitvect2);
    ub_bitvect_destroy(bitvect3);

}

void test5() {

    ub_bitvect_t *bitvect = ub_bitvect_create(100);
    ub_bitvect_t *bitvect2 = ub_bitvect_create(100);

    for (size_t i = 0; i < 10; i++) {
        ub_bitvect_set_bit(bitvect, i, true);
    }

    ub_bitvect_println(bitvect);

    for (size_t i = 0; i < 90; i++) {
        ub_bitvect_set_bit(bitvect2, i, true);
    }

    ub_bitvect_println(bitvect2);

    ub_bitvect_t *bitvect3 = ub_bitvect_union(bitvect, bitvect2);

    for (size_t i = 0; i < 90; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect3, i) == true);
    }

    for (size_t i = 90; i < 100; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect3, i) == false);
    }

    ub_bitvect_destroy(bitvect);
    ub_bitvect_destroy(bitvect2);
    ub_bitvect_destroy(bitvect3);
}

void test6() {

    ub_bitvect_t *bitvect = ub_bitvect_create(100);
    ub_bitvect_t *bitvect2 = ub_bitvect_create(100);

    for (size_t i = 0; i < 100; i++) {
        ub_bitvect_set_bit(bitvect, i, i % 2 == 0);
    }

    ub_bitvect_println(bitvect);

    for (size_t i = 0; i < 100; i++) {
        ub_bitvect_set_bit(bitvect2, i, i % 2 != 0);
    }

    ub_bitvect_println(bitvect2);

    ub_bitvect_t *bitvect3 = ub_bitvect_union(bitvect, bitvect2);

    for (size_t i = 0; i < 100; i++) {

        DR_ASSERT(
                ub_bitvect_get_bit(bitvect, i)
                        != ub_bitvect_get_bit(bitvect2, i));
        DR_ASSERT(ub_bitvect_get_bit(bitvect3, i) == true);
    }

    ub_bitvect_destroy(bitvect);
    ub_bitvect_destroy(bitvect2);
    ub_bitvect_destroy(bitvect3);
}

void test7() {
    ub_bitvect_t *bitvect = ub_bitvect_create(9);
    ub_bitvect_set_bit(bitvect, 8, true);
    DR_ASSERT(ub_bitvect_get_bit(bitvect, 8) == true);
    ub_bitvect_destroy(bitvect);
}

void test8() {
    ub_bitvect_t *bitvect = ub_bitvect_create(9);
    ub_bitvect_set_bit(bitvect, 5, true);
    size_t size = ub_bitvect_get_start_trailing_zero(bitvect);
    DR_ASSERT(size == 6);
    ub_bitvect_destroy(bitvect);

    bitvect = ub_bitvect_create(9);
    size = ub_bitvect_get_start_trailing_zero(bitvect);
    DR_ASSERT(size == 0);
    ub_bitvect_destroy(bitvect);

    bitvect = ub_bitvect_create(9);
    ub_bitvect_set_bit(bitvect, 8, true);
    size = ub_bitvect_get_start_trailing_zero(bitvect);
    DR_ASSERT(size == 9);
    ub_bitvect_destroy(bitvect);

    bitvect = ub_bitvect_create(9);
    ub_bitvect_set_bit(bitvect, 7, true);
    size = ub_bitvect_get_start_trailing_zero(bitvect);
    DR_ASSERT(size == 8);
    ub_bitvect_destroy(bitvect);
}

void test9() {

    ub_bitvect_t *bitvect = ub_bitvect_create(9);
    ub_bitvect_set_bit(bitvect, 5, true);

    ub_bitvect_t *bitvect2 = ub_bitvect_create(6);
    ub_bitvect_set_bit(bitvect2, 5, true);

    DR_ASSERT(ub_bitvect_equal(bitvect, bitvect2));

    ub_bitvect_set_bit(bitvect2, 1, true);
    DR_ASSERT(!ub_bitvect_equal(bitvect, bitvect2));

    ub_bitvect_destroy(bitvect);
    ub_bitvect_destroy(bitvect2);
}

void test10() {

    ub_bitvect_t *bitvect = ub_bitvect_create(9);
    ub_bitvect_set_bit(bitvect, 5, true);
    DR_ASSERT(bitvect->bit_size == 9);

    ub_bitvect_println(bitvect);

    ub_bitvect_trim(bitvect);

    ub_bitvect_println(bitvect);

    DR_ASSERT(bitvect->bit_size == 6);
    DR_ASSERT(ub_bitvect_get_bit(bitvect, 5));

    ub_bitvect_destroy(bitvect);
}

void test11() {

    ub_bitvect_t *bitvect = ub_bitvect_create(100);
    ub_bitvect_t *bitvect2 = ub_bitvect_create(100);

    for (size_t i = 0; i < 10; i++)
        ub_bitvect_set_bit(bitvect, i, true);

    ub_bitvect_fixed_union(bitvect, bitvect2);

    for (size_t i = 0; i < 10; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect, i) == true);
    }

    for (size_t i = 10; i < 100; i++) {
        DR_ASSERT(ub_bitvect_get_bit(bitvect, i) == false);
    }

    ub_bitvect_destroy(bitvect);
    ub_bitvect_destroy(bitvect2);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
}
