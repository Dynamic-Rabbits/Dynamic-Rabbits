/*
 * ub_lp_hashmap_test.c
 *
 *      Author: john
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../utility_bunny.h"

int delete_count;

void destroy_me(void *value) {

	delete_count++;
}

static void test1() {

	void *map = ub_lp_map_create();

	void *res = ub_lp_map_lookup_entry(map, (void *) (intptr_t) 8);
	DR_ASSERT_MSG(res == NULL, "ub_lp_hashmap_test.c - test1 - 1 failed...");

	bool found = ub_lp_map_remove(map, (void *) (intptr_t) 8, NULL);
	DR_ASSERT_MSG(!found, "ub_lp_hashmap_test.c - test1 - 2 failed...");

	delete_count = 0;
	ub_lp_map_destroy(map, destroy_me);
	DR_ASSERT_MSG(delete_count == 0,
			"ub_lp_hashmap_test.c - test1 - 3 failed...");
}

static void test2() {

	void *map = ub_lp_map_create();

	ub_key_value_pair_t key_value;

	key_value.key = (intptr_t) 8;
	key_value.value = (void *) (intptr_t) 90;

	void *elem = ub_lp_map_insert_entry(map, &key_value);
	DR_ASSERT_MSG(elem == NULL, "ub_lp_hashmap_test.c - test1 - 0 failed...");

	key_value.value = (void *) (intptr_t) 70;

	elem = ub_lp_map_insert_entry(map, &key_value);
	DR_ASSERT_MSG(elem == (void * ) (uintptr_t ) 90,
			"ub_lp_hashmap_test.c - test1 - 1 failed...");

	void *res = ub_lp_map_lookup_entry(map, (void *) (intptr_t) 8);
	DR_ASSERT_MSG(res == (void * ) (uintptr_t ) 70,
			"ub_lp_hashmap_test.c - test1 - 2 failed...");

	void *rem;
	bool found = ub_lp_map_remove(map, (void *) (intptr_t) 8, &rem);
	DR_ASSERT_MSG(found, "ub_lp_hashmap_test.c - test1 - 3 failed...");
	DR_ASSERT_MSG(rem == (void * ) (uintptr_t ) 70,
			"ub_lp_hashmap_test.c - test1 - 4 failed...");

	res = ub_lp_map_lookup_entry(map, (void *) (intptr_t) 8);
	DR_ASSERT_MSG(res == NULL, "ub_lp_hashmap_test.c - test1 - 5 failed...");

	delete_count = 0;
	ub_lp_map_destroy(map, destroy_me);
	DR_ASSERT_MSG(delete_count == 0,
			"ub_lp_hashmap_test.c - test1 - 6 failed...");
}

static void test3() {

	int size = 600000;

	void *map = ub_lp_map_create();

	for (int i = 1; i < size; i++) {

		ub_key_value_pair_t key_value;

		key_value.key = (uintptr_t) i;
		key_value.value = (void *) (uintptr_t) (i * 10);
		void* old = ub_lp_map_insert_entry(map, &key_value);

		DR_ASSERT_MSG(old == NULL,
				"ub_lp_hashmap_test.c - test3 - 1 failed...");

		void *res = ub_lp_map_lookup_entry(map, (void *) (intptr_t) i);
		DR_ASSERT_MSG(res == (void * ) (uintptr_t ) (i * 10),
				"ub_lp_hashmap_test.c - test1 - 2 failed...");

	}

	delete_count = 0;
	ub_lp_map_destroy(map, destroy_me);
	DR_ASSERT_MSG(delete_count == size-1,
			"ub_lp_hashmap_test.c - test3 - 3 failed...");
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
}

