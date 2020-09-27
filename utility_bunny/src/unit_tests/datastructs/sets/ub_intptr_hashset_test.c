/**
 *  @file ub_intptr_hashset_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../utility_bunny.h"

static void test1() {

	void *intptr_hashset = ub_intptr_hashset_create();
	bool result = ub_intptr_hashset_is_included(intptr_hashset, (uintptr_t) 18);
	DR_ASSERT_MSG(result == false,
			"ub_intptr_hashset_test - test1 - 0 failed...");
	ub_intptr_hashset_destroy(intptr_hashset);
}

static void test2() {

	void *intptr_hashset = ub_intptr_hashset_create();

	bool was_not_in_set = ub_intptr_hashset_insert(intptr_hashset,
			(uintptr_t) 10);
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_intptr_hashset_test.c - test2 - 0 failed...");

	bool is_in_set = ub_intptr_hashset_is_included(intptr_hashset,
			(uintptr_t) 10);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test2 - 1 failed...");

	bool is_not_in_set = ub_intptr_hashset_is_included(intptr_hashset,
			(uintptr_t) 20);
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_intptr_hashset_test.c - test2 - 2 failed...");

	is_in_set = ub_intptr_hashset_is_included(intptr_hashset, (uintptr_t) 10);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test2 - 3 failed...");

	is_not_in_set = ub_intptr_hashset_is_included(intptr_hashset,
			(uintptr_t) 15);
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_intptr_hashset_test.c - test2 - 4 failed...");

	ub_intptr_hashset_destroy(intptr_hashset);
}

static void test3() {

	void *intptr_hashset = ub_intptr_hashset_create();

	bool is_not_in_set = ub_intptr_hashset_is_included(intptr_hashset,
			(uintptr_t) 10);
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_intptr_hashset_test.c - test3 - 0 failed...");

	is_not_in_set = ub_intptr_hashset_is_included(intptr_hashset,
			(uintptr_t) 20);
	DR_ASSERT_MSG(is_not_in_set == false,
			"ub_intptr_hashset_test.c - test3 - 1 failed...");

	bool was_not_in_set = ub_intptr_hashset_insert(intptr_hashset,
			(uintptr_t) 20);
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_intptr_hashset_test.c - test3 - 2 failed...");

	was_not_in_set = ub_intptr_hashset_insert(intptr_hashset, (uintptr_t) 20);
	DR_ASSERT_MSG(was_not_in_set == false,
			"ub_intptr_hashset_test.c - test3 - 3 failed...");

	was_not_in_set = ub_intptr_hashset_insert(intptr_hashset, (uintptr_t) 10);
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_intptr_hashset_test.c - test3 - 4 failed...");

	bool is_in_set = ub_intptr_hashset_is_included(intptr_hashset,
			(uintptr_t) 20);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test2 - 5 failed...");

	is_in_set = ub_intptr_hashset_is_included(intptr_hashset, (uintptr_t) 10);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test2 - 6 failed...");

	ub_intptr_hashset_destroy(intptr_hashset);
}

static void test4() {

	void *intptr_hashset = ub_intptr_hashset_create();

	bool was_not_in_set = ub_intptr_hashset_insert(intptr_hashset,
			(uintptr_t) 20);
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 0 failed...");

	bool is_in_set = ub_intptr_hashset_is_included(intptr_hashset,
			(uintptr_t) 20);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 1 failed...");

	bool was_removed = ub_intptr_hashset_remove(intptr_hashset, (uintptr_t) 20);
	DR_ASSERT_MSG(was_removed == true,
			"ub_intptr_hashset_test.c - test4 - 2 failed...");

	was_removed = ub_intptr_hashset_remove(intptr_hashset, (uintptr_t) 20);
	DR_ASSERT_MSG(was_removed == false,
			"ub_intptr_hashset_test.c - test4 - 3 failed...");

	is_in_set = ub_intptr_hashset_is_included(intptr_hashset, (uintptr_t) 20);
	DR_ASSERT_MSG(is_in_set == false,
			"ub_intptr_hashset_test.c - test4 - 4 failed...");

	was_not_in_set = ub_intptr_hashset_insert(intptr_hashset, (uintptr_t) 20);
	DR_ASSERT_MSG(was_not_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 5 failed...");

	is_in_set = ub_intptr_hashset_is_included(intptr_hashset, (uintptr_t) 20);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test4 - 6 failed...");

	ub_intptr_hashset_destroy(intptr_hashset);
}

static void test5() {

	void *intptr_hashset = ub_intptr_hashset_create();
	void *intptr_hashset2 = ub_intptr_hashset_create();

	ub_intptr_hashset_insert(intptr_hashset,
			(uintptr_t) 20);

	ub_intptr_hashset_union(intptr_hashset2, intptr_hashset);

	bool is_in_set = ub_intptr_hashset_is_included(intptr_hashset2,
			(uintptr_t) 20);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test5 - 1 failed...");

	is_in_set = ub_intptr_hashset_is_included(intptr_hashset2,
			(uintptr_t) 21);
	DR_ASSERT_MSG(is_in_set == false,
			"ub_intptr_hashset_test.c - test5 - 1 failed...");

	ub_intptr_hashset_destroy(intptr_hashset);
	ub_intptr_hashset_destroy(intptr_hashset2);
}


static void test6() {

	void *intptr_hashset = ub_intptr_hashset_create();
	void *intptr_hashset2 = ub_intptr_hashset_create();

	ub_intptr_hashset_insert(intptr_hashset,
			(uintptr_t) 20);

	ub_intptr_hashset_insert(intptr_hashset2,
			(uintptr_t) 21);


	ub_intptr_hashset_union(intptr_hashset2, intptr_hashset);

	bool is_in_set = ub_intptr_hashset_is_included(intptr_hashset2,
			(uintptr_t) 20);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test5 - 1 failed...");

	is_in_set = ub_intptr_hashset_is_included(intptr_hashset2,
			(uintptr_t) 21);
	DR_ASSERT_MSG(is_in_set == true,
			"ub_intptr_hashset_test.c - test5 - 1 failed...");

	ub_intptr_hashset_destroy(intptr_hashset);
	ub_intptr_hashset_destroy(intptr_hashset2);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
}
