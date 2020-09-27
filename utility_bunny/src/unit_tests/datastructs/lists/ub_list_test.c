/**
 *  @file ub_list_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../utility_bunny.h"

unsigned int destroy_count;
unsigned int compare_count;

static void destroy_me(void *elem) {

	destroy_count++;
}

static bool compare_me(const void *elem1, const void *elem2) {

	compare_count++;
	return elem1 == elem2;
}

static void test1() {

	void *list = ub_list_create();

	void *elem = ub_list_pop(list);
	DR_ASSERT_MSG(elem == NULL, "ub_list_test - test1 - 0 failed...");

	DR_ASSERT_MSG(ub_list_get_size(list) == 0,
			"ub_list_test - test1 - 1 failed...");

	compare_count = 0;
	elem = ub_list_search(list, (void *) (uintptr_t) 2, compare_me);
	DR_ASSERT_MSG(elem == NULL, "ub_list_test - test1 - 2 failed...");
	DR_ASSERT_MSG(compare_count == 0, "ub_list_test - test1 - 3 failed...");

	compare_count = 0;
	elem = ub_list_remove(list, (void *) (uintptr_t) 2, compare_me);
	DR_ASSERT_MSG(elem == NULL, "ub_list_test - test1 - 3 failed...");
	DR_ASSERT_MSG(compare_count == 0, "ub_list_test - test1 - 4 failed...");

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);

	DR_ASSERT_MSG(destroy_count == 0, "ub_list_test - test1 - 4 failed...");
}

static void test2() {

	void *list = ub_list_create();

	ub_list_insert(list, (void *) (uintptr_t) 2);

	DR_ASSERT_MSG(ub_list_get_size(list) == 1,
			"ub_list_test - test1 - 1 failed...");

	void *elem = ub_list_pop(list);
	DR_ASSERT_MSG(elem == (void * ) (uintptr_t ) 2,
			"ub_list_test - test1 - 0 failed...");

	DR_ASSERT_MSG(ub_list_get_size(list) == 0,
			"ub_list_test - test1 - 1 failed...");

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);

	DR_ASSERT_MSG(destroy_count == 0, "ub_list_test - test1 - 4 failed...");
}

static void test3() {

	void *list = ub_list_create();

	int size = 90;

	for (int i = 0; i < size; i++) {

		ub_list_insert(list, (void *) (uintptr_t) i);

		compare_count = 0;

		void *elem = ub_list_search(list, (void *) (uintptr_t) i, compare_me);
		DR_ASSERT_MSG(elem == (void * ) (uintptr_t ) i,
				"ub_list_test - test3 - 0 failed...");

		DR_ASSERT_MSG(compare_count <= i + 1,
				"ub_list_test - test1 - 1 failed...");

		DR_ASSERT_MSG(ub_list_get_size(list) == i + 1,
				"ub_list_test - test3 - 2 failed...");
	}

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == size, "ub_list_test - test3 - 3 failed...");
}

static void test4() {

	void *list = ub_list_create();

	ub_list_insert(list, (void *) (uintptr_t) 2);
	ub_list_insert(list, (void *) (uintptr_t) 4);

	void *elem = ub_list_pop(list);
	DR_ASSERT_MSG(elem == (void * ) (uintptr_t ) 2,
			"ub_list_test - test4 - 0 failed...");

	elem = ub_list_pop(list);
	DR_ASSERT_MSG(elem == (void * ) (uintptr_t ) 4,
			"ub_list_test - test4 - 1 failed...");

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == 0, "ub_list_test - test4 - 2 failed...");

}

static void test5() {

	void *list = ub_list_create();

	int size = 90;

	for (int i = 0; i < size; i++) {

		ub_list_insert(list, (void *) (uintptr_t) i);
	}

	for (int i = size - 1; i >= 0; i--) {

		void * elem = ub_list_remove(list, (void *) (uintptr_t) i, compare_me);
		DR_ASSERT_MSG(elem == (void * ) (uintptr_t ) i,
				"ub_list_test - test4 - 3 failed...");
	}

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == 0, "ub_list_test - test3 - 2 failed...");
}

static void test6() {

	void *list = ub_list_create();

	int size = 90;

	for (int i = 0; i < size; i++) {
		ub_list_insert(list, (void *) (uintptr_t) i);
	}

	int counter = 0;

	void *list_it = ub_list_get_start_it(list);

	while (list_it != NULL) {

		void *value = ub_list_get_it_value(list_it);

		DR_ASSERT_MSG(counter < size, "ub_list_test - test6 - 1 failed...");
		DR_ASSERT_MSG(value == (void * ) (uintptr_t ) counter,
				"ub_list_test - test6 - 2 failed...");

		counter++;
		list_it = ub_list_get_next_it(list_it);
	}

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == size, "ub_list_test - test3 - 2 failed...");
}

static void test7() {

	void *list = ub_list_create();

	int size = 90;

	for (int i = 0; i < size; i++) {

		ub_list_insert(list, (void *) (uintptr_t) i);
	}

	for (int i = size - 1; i >= 0; i--) {

		uintptr_t elem = (uintptr_t) ub_list_get_ith_value(list, i);

		DR_ASSERT_MSG(elem == (uintptr_t ) i,
				"ub_list_test - test4 - 3 failed...");
	}

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == 90, "ub_list_test - test3 - 2 failed...");
}

static void test8() {

	void *list = ub_list_create();

	int size = 90;

	for (int i = 0; i < size; i++) {

		ub_list_insert(list, (void *) (uintptr_t) i);
	}

	for (int i = size - 1; i >= 0; i--) {

		void * elem = (void *) ub_list_get_ith_value(list, i);

		DR_ASSERT_MSG(elem == (void * ) i,
				"ub_list_test - test4 - 3 failed...");
	}

	ub_list_insert_at_ith(list, (void *) 1000, 0);
	ub_list_insert_at_ith(list, (void *) 1010, 0);

	void * elem = (void *) ub_list_get_ith_value(list, 0);
	DR_ASSERT(elem == (void * ) 1010);
	elem = (void *) ub_list_get_ith_value(list, 1);
	DR_ASSERT(elem == (void * ) 1000);
	elem = (void *) ub_list_get_ith_value(list, 2);
	DR_ASSERT(elem == (void * ) 0);

	ub_list_remove_at_ith(list, 1);
	elem = (void *) ub_list_get_ith_value(list, 0);
	DR_ASSERT(elem == (void * ) 1010);
	elem = (void *) ub_list_get_ith_value(list, 1);
	DR_ASSERT(elem == (void * ) 0);

	ub_list_remove_at_ith(list, 0);
	elem = (void *) ub_list_get_ith_value(list, 0);
	DR_ASSERT(elem == (void * ) 0);

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == 90, "ub_list_test - test3 - 2 failed...");
}

static void test9() {

	void *list = ub_list_create();

	int size = 90;

	for (int i = 0; i < size; i++) {
		ub_list_insert(list, (void *) (uintptr_t) i);
	}

	DR_ASSERT(ub_list_get_size(list) == size);

	ub_list_insert_it_value(list, NULL, (void *) (uintptr_t) 7000);
	DR_ASSERT(ub_list_get_size(list) == size + 1);

	ub_list_insert_it_value(list, NULL, (void *) (uintptr_t) 8000);
	DR_ASSERT(ub_list_get_size(list) == size + 2);

	void * elem = (void *) ub_list_get_ith_value(list, 0);
	DR_ASSERT(elem == (void * ) (uintptr_t ) 8000);

	elem = (void *) ub_list_get_ith_value(list, 1);
	DR_ASSERT(elem == (void * ) (uintptr_t ) 7000);

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == 90 + 2,
			"ub_list_test - test3 - 2 failed...");
}

static void test10() {

	int size = 90;
	int counter = 90;

	void *list = ub_list_create();

	for (int i = 0; i < size; i++) {
		ub_list_insert(list, (void *) (intptr_t) i);
	}

	void *list_it = ub_list_get_end_it(list);

	while (list_it != NULL) {

		void *value = ub_list_get_it_value(list_it);

		counter--;
		DR_ASSERT_MSG(counter == (int ) value,
				"ub_list_test - test10 - 1 failed...");

		list_it = ub_list_get_prev_it(list_it);
	}

	destroy_count = 0;
	ub_list_destroy(list, destroy_me);
	DR_ASSERT_MSG(destroy_count == 90,
			"ub_list_test - test10 - 2 failed...");
}

static void test11() {

	void *list = ub_list_create();

	void *list_it = ub_list_get_end_it(list);

	DR_ASSERT_MSG(list_it == NULL,
			"ub_list_test - test11 - 1 failed...");

	ub_list_destroy(list, destroy_me);
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

