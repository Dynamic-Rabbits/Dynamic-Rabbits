/**
 *  @file ub_arraymap_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../utility_bunny.h"

int delete_count;

void destroy_me(void *value){

	delete_count++;
}

static void test1(){

	int size = 100;
	void *array_map = ub_arraymap_create_map(100);

	void *res = ub_arraymap_lookup_entry(array_map, (intptr_t) 8);
	DR_ASSERT_MSG(res == NULL,
			"ub_arraymap_test.c - test1 - 1 failed...");

	res = ub_arraymap_remove_entry(array_map, (intptr_t) 8);
	DR_ASSERT_MSG(res == NULL,
			"ub_arraymap_test.c - test1 - 2 failed...");

	delete_count = 0;
	ub_arraymap_destroy_map(array_map, destroy_me);
	DR_ASSERT_MSG(delete_count == 0,
			"ub_arraymap_test.c - test1 - 3 failed...");
}

static void test2() {

	int size = 100;
	void *array_map = ub_arraymap_create_map(100);

	ub_key_value_pair_t key_value;

	key_value.key = (intptr_t) 8;
	key_value.value = (void *) (intptr_t) 90;

	void *elem = ub_arraymap_insert_entry(array_map, &key_value);
	DR_ASSERT_MSG(elem == NULL,
			"ub_arraymap_test.c - test1 - 0 failed...");

	key_value.value = (void *) (intptr_t) 70;

	elem = ub_arraymap_insert_entry(array_map, &key_value);
	DR_ASSERT_MSG(elem == (void *) (uintptr_t) 90,
			"ub_arraymap_test.c - test1 - 1 failed...");

	void *res = ub_arraymap_lookup_entry(array_map, (intptr_t) 8);
	DR_ASSERT_MSG(res == (void *) (uintptr_t) 70,
			"ub_arraymap_test.c - test1 - 2 failed...");

	void *rem = ub_arraymap_remove_entry(array_map, (intptr_t) 8);
	DR_ASSERT_MSG(rem == (void *) (uintptr_t) 70,
			"ub_arraymap_test.c - test1 - 3 failed...");

	res = ub_arraymap_lookup_entry(array_map, (intptr_t) 8);
	DR_ASSERT_MSG(res == NULL,
			"ub_arraymap_test.c - test1 - 2 failed...");

	delete_count = 0;
	ub_arraymap_destroy_map(array_map, destroy_me);
	DR_ASSERT_MSG(delete_count == 0,
			"ub_arraymap_test.c - test1 - 4 failed...");
}

static void test3(){

	int size = 90;

	void *array_map = ub_arraymap_create_map(size);

	for (int i = 0; i < size; i++){

		ub_key_value_pair_t key_value;

		key_value.key = (uintptr_t) i;
		key_value.value = (void *) (uintptr_t) (i * 10);
		void* old = ub_arraymap_insert_entry(array_map, &key_value);

		DR_ASSERT_MSG(old == NULL,
				"ub_arraymap_test.c - test3 - 1 failed...");

		void *res = ub_arraymap_lookup_entry(array_map, (intptr_t) i);
		DR_ASSERT_MSG(res == (void *) (uintptr_t) (i * 10),
				"ub_arraymap_test.c - test1 - 2 failed...");

	}

	delete_count = 0;
	ub_arraymap_destroy_map(array_map, destroy_me);
	DR_ASSERT_MSG(delete_count == size,
			"ub_arraymap_test.c - test3 - 3 failed...");
}


DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
}

