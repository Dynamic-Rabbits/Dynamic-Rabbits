/**
 *  @file ub_loc_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../utility_bunny.h"

static void test1() {

	ub_loc_info_t loc_info;
	ub_loc_populate(&loc_info, 780, 2, UB_MEM_TYPE);

	DR_ASSERT_MSG(loc_info.opnd == 780,
			"ub_loc_test - test1 failed...");

	DR_ASSERT_MSG(loc_info.size == 2,
			"ub_loc_test - test2 failed...");

	DR_ASSERT_MSG(loc_info.type == UB_MEM_TYPE,
			"ub_loc_test - test3 failed...");
}

static void test2() {

	ub_loc_info_t loc_info;
	ub_loc_populate(&loc_info, 20, 1, UB_REG_TYPE);

	DR_ASSERT_MSG(loc_info.opnd == 20,
			"ub_loc_test - test1 failed...");

	DR_ASSERT_MSG(loc_info.size == 1,
			"ub_loc_test - test2 failed...");

	DR_ASSERT_MSG(loc_info.type == UB_REG_TYPE,
			"ub_loc_test - test3 failed...");
}

static void test3() {

	ub_loc_info_t loc_info;
	ub_loc_populate(&loc_info, 400, 2, UB_IMMED_TYPE);

	DR_ASSERT_MSG(loc_info.opnd == 400,
			"ub_loc_test - test1 failed...");

	DR_ASSERT_MSG(loc_info.size == 2,
			"ub_loc_test - test2 failed...");

	DR_ASSERT_MSG(loc_info.type == UB_IMMED_TYPE,
			"ub_loc_test - test3 failed...");
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
}
