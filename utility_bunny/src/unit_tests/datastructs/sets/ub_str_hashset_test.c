/**
 *  @file ub_intptr_hashset_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../utility_bunny.h"

static void test1() {

	void *str_hashset = ub_str_hashset_create();
	bool result = ub_str_hashset_is_included(str_hashset, "This is the TEST!");
	DR_ASSERT_MSG(result == false, "ub_str_hashset_test - test1 - 0 failed...");
	ub_str_hashset_destroy(str_hashset);
}

static void test2() {

	void *str_hashset = ub_str_hashset_create();

	bool was_not_in_set = ub_str_hashset_insert(str_hashset,
			"This is the TEST!");
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_str_hashset_test.c - test2 - 0 failed...");

	bool is_in_set = ub_str_hashset_is_included(str_hashset,
			"This is the TEST!");
	DR_ASSERT_MSG(is_in_set == true,
			"ub_str_hashset_test.c - test2 - 1 failed...");

	bool is_not_in_set = ub_str_hashset_is_included(str_hashset,
			"This is the TEST");
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_str_hashset_test.c - test2 - 2 failed...");

	is_in_set = ub_str_hashset_is_included(str_hashset, "This is the TEST!");
	DR_ASSERT_MSG(is_in_set == true,
			"ub_str_hashset_test.c - test2 - 3 failed...");

	is_not_in_set = ub_str_hashset_is_included(str_hashset, "HELLO");
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_str_hashset_test.c - test2 - 4 failed...");

	ub_str_hashset_destroy(str_hashset);
}

static void test3() {

	void *str_hashset = ub_str_hashset_create();

	bool is_not_in_set = ub_str_hashset_is_included(str_hashset,
			"This is the TEST");
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_str_hashset_test.c - test3 - 0 failed...");

	is_not_in_set = ub_str_hashset_is_included(str_hashset,
			"This is the TEST!");
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_str_hashset_test.c - test3 - 1 failed...");

	bool was_not_in_set = ub_str_hashset_insert(str_hashset,
			"This is the TEST!");
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_str_hashset_test.c - test3 - 2 failed...");

	was_not_in_set = ub_str_hashset_insert(str_hashset, "This is the TEST!");
	DR_ASSERT_MSG(was_not_in_set == false,
			"ub_str_hashset_test.c - test3 - 3 failed...");

	was_not_in_set = ub_str_hashset_insert(str_hashset, "This is the TEST");
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_str_hashset_test.c - test3 - 4 failed...");

	bool is_in_set = ub_str_hashset_is_included(str_hashset,
			"This is the TEST!");
	DR_ASSERT_MSG(is_in_set == true,
			"ub_str_hashset_test.c - test2 - 5 failed...");

	is_in_set = ub_str_hashset_is_included(str_hashset, "This is the TEST");
	DR_ASSERT_MSG(is_in_set == true,
			"ub_str_hashset_test.c - test2 - 6 failed...");

	ub_str_hashset_destroy(str_hashset);
}

static void test4() {

	void *str_hashset = ub_str_hashset_create();

	bool was_not_in_set = ub_str_hashset_insert(str_hashset,
			"This is the TEST");
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 0 failed...");

	bool is_in_set = ub_str_hashset_is_included(str_hashset,
			"This is the TEST");
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 1 failed...");

	bool was_removed = ub_str_hashset_remove(str_hashset, "This is the TEST");
	DR_ASSERT_MSG(was_removed == true,
			"ub_intptr_hashset_test.c - test4 - 2 failed...");

	was_removed = ub_str_hashset_remove(str_hashset, "This is the TEST");
	DR_ASSERT_MSG(was_removed == false,
			"ub_intptr_hashset_test.c - test4 - 3 failed...");

	is_in_set = ub_str_hashset_is_included(str_hashset, "This is the TEST");
	DR_ASSERT_MSG(is_in_set == false,
			"ub_intptr_hashset_test.c - test4 - 4 failed...");

	was_not_in_set = ub_str_hashset_insert(str_hashset, "This is the TEST");
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 5 failed...");

	is_in_set = ub_str_hashset_is_included(str_hashset, "This is the TEST");
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 6 failed...");

	ub_str_hashset_destroy(str_hashset);
}

static void test5() {

	void *str_hashset = ub_str_hashset_create();
	void *str_hashset2 = ub_str_hashset_create();

	ub_str_hashset_insert(str_hashset, "This is the TEST");

	ub_str_hashset_union(str_hashset2, str_hashset);

	bool in_set = ub_str_hashset_is_included(str_hashset2, "This is the TEST");
	DR_ASSERT_MSG(in_set == true,
			"ub_intptr_hashset_test.c - test5 - 0 failed...");

	ub_str_hashset_destroy(str_hashset);
	ub_str_hashset_destroy(str_hashset2);

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
	test5();
}
