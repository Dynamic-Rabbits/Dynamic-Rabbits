/**
 *  @file ub_eflags_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../utility_bunny.h"

static void test1() {


	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, CF_FLAG_INDEX, true);

	DR_ASSERT_MSG(ub_byte_are_all_bit_set(7, 1, bit_check) == true,
			"ub_register_test - test1 - 0 - failed...");

	ub_byte_populate_check(&bit_check, PF_FLAG_INDEX, true);
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(7, 1, bit_check) == true,
			"ub_register_test - test1 - 1 - failed...");

	ub_byte_populate_check(&bit_check, PF_FLAG_INDEX, true);
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(3, 1, bit_check) == false,
			"ub_register_test - test1 - 2 - failed...");

	ub_byte_populate_check(&bit_check, AF_FLAG_INDEX, true);
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(18, 1, bit_check) == true,
			"ub_register_test - test1 - 3 - failed...");

	ub_byte_populate_check(&bit_check, ZF_FLAG_INDEX, true);
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(18, 1, bit_check) == false,
			"ub_register_test - test1 - 4 - failed...");

	DR_ASSERT_MSG(ub_byte_are_all_bit_set(66, 1, bit_check) == true,
			"ub_register_test - test1 - 5 - failed...");

	ub_byte_populate_check(&bit_check, SF_FLAG_INDEX, true);
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(1944, 1, bit_check) == true,
			"ub_register_test - test1 - 6 - failed...");

	ub_byte_populate_check(&bit_check, DF_FLAG_INDEX, true);
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(3266, 1, bit_check) == true,
			"ub_register_test - test1 - 7 - failed...");

	ub_byte_populate_check(&bit_check, OF_FLAG_INDEX, true);
	DR_ASSERT_MSG(ub_byte_are_all_bit_set(3435, 1, bit_check)  == true,
			"ub_register_test - test1 - 8 - failed...");

	DR_ASSERT_MSG(ub_byte_are_all_bit_set(5314, 1, bit_check) == false,
			"ub_register_test - test1 - 9 - failed...");

	DR_ASSERT_MSG(ub_byte_are_all_bit_set(7364, 1, bit_check)  == true,
			"ub_register_test - test9 failed...");
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
}
