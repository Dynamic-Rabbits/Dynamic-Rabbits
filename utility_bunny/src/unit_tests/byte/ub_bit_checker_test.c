/**
 *  @file ub_bit_checker_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../utility_bunny.h"

static void test1() {

	unsigned int value = 0;
	unsigned int index = 4;

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, index, true);

	bool res = ub_byte_are_all_bit_set(value, 1, bit_check);

	DR_ASSERT_MSG(res == false,
			"ub_bit_checker_test - test1 failed...");
}

static void test2() {

	unsigned int value = 1;
	unsigned int index = 0;

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, index, true);

	bool res = ub_byte_are_all_bit_set(value, 1, bit_check);

	DR_ASSERT_MSG(res == true,
			"ub_bit_checker_test - test2 failed...");
}

static void test3() {

	unsigned int value = 10;

	unsigned int index1 = 0;
	unsigned int index2 = 1;
	unsigned int index3 = 2;
	unsigned int index4 = 3;

	ub_bit_check_t bit_check1;
	ub_byte_populate_check(&bit_check1, index1, true);

	ub_bit_check_t bit_check2;
	ub_byte_populate_check(&bit_check2, index2, true);

	ub_bit_check_t bit_check3;
	ub_byte_populate_check(&bit_check3, index3, true);

	ub_bit_check_t bit_check4;
	ub_byte_populate_check(&bit_check4, index4, true);

	DR_ASSERT_MSG(ub_byte_are_all_bit_set(value, 1, bit_check1) == false,
			"ub_bit_checker_test - test3 - 0 failed...");
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(value, 1, bit_check2) == true,
			"ub_bit_checker_test - test3 - 1 failed...");
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(value, 1, bit_check3) == false,
			"ub_bit_checker_test - test3 - 2 failed...");
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(value, 1, bit_check4) == true,
			"ub_bit_checker_test - test3 - 3 failed...");
}

static void test4() {

	unsigned int value = 256;

	ub_bit_check_t bit_check;

	for (int i = 0; i < 8; i++) {

		ub_byte_populate_check(&bit_check, i, true);

		DR_ASSERT_MSG(ub_byte_are_all_bit_set(value, 1, bit_check) == false,
				"ub_bit_checker_test - test4 - 0 failed...");
	}

	unsigned int index = 8;
	ub_byte_populate_check(&bit_check, index, true);

	DR_ASSERT_MSG(ub_byte_are_all_bit_set(value, 1, bit_check) == true,
			"ub_bit_checker_test - test4 - 1 failed...");
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
}
