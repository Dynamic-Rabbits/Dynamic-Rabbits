/*
 * ub_tk_lp_test.c
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

	void *tk_map = ub_tk_lp_hashmap_create();

	void *res = ub_tk_lp_hashmap_lookup_entry(tk_map, (intptr_t) 8,
			(intptr_t) 90);
	DR_ASSERT_MSG(res == NULL, "ub_tk_lp_test.c - test1 - 1 failed...");

	res = ub_tk_lp_hashmap_lookup_entry(tk_map, (intptr_t) 8, (intptr_t) 90);
	DR_ASSERT_MSG(res == NULL, "ub_tk_lp_test.c - test1 - 2 failed...");

	delete_count = 0;
	ub_tk_lp_hashmap_destroy(tk_map, destroy_me);
	DR_ASSERT_MSG(delete_count == 0,
			"ub_tk_lp_test.c - test1 - 3 failed...");
}

static void test2() {

	void *tk_map = ub_tk_lp_hashmap_create();

	ub_two_key_value_pair_t key_value;
	key_value.key1 = (intptr_t) 8;
	key_value.key2 = (intptr_t) 9;
	key_value.value = (void *) (intptr_t) 65;

	void *elem = ub_tk_lp_hashmap_insert_entry(tk_map, &key_value);
	DR_ASSERT_MSG(elem == NULL, "ub_tk_lp_test.c - test1 - 0 failed...");

	key_value.value = (void *) (intptr_t) 70;

	elem = ub_tk_lp_hashmap_insert_entry(tk_map, &key_value);
	DR_ASSERT_MSG(elem == (void * ) (uintptr_t ) 65,
			"ub_tk_lp_test.c - test1 - 1 failed...");

	void *res = ub_tk_lp_hashmap_lookup_entry(tk_map, (intptr_t) 8, (intptr_t) 9);
	DR_ASSERT_MSG(res == (void * ) (uintptr_t ) 70,
			"ub_tk_lp_test.c - test1 - 2 failed...");

	void *rem;
	bool removed = ub_tk_lp_hashmap_remove_entry(tk_map, (intptr_t) 8,
			(intptr_t) 9, &rem);
	DR_ASSERT_MSG(removed, "ub_tk_lp_test.c - test1 - 3 failed...");

	DR_ASSERT_MSG(rem == (void * ) (uintptr_t ) 70,
			"ub_tk_lp_test.c - test1 - 3 failed...");

	res = ub_tk_lp_hashmap_lookup_entry(tk_map, (intptr_t) 8, (intptr_t) 9);
	DR_ASSERT_MSG(res == NULL, "ub_tk_lp_test.c - test1 - 2 failed...");

	delete_count = 0;
	ub_tk_lp_hashmap_destroy(tk_map, destroy_me);
	DR_ASSERT_MSG(delete_count == 0,
			"ub_tk_lp_test.c - test1 - 4 failed...");
}

static void test3() {

	void *map = ub_tk_lp_hashmap_create();

	size_t size = 1000;
	for (int i = 1; i < size; i++) {

		ub_two_key_value_pair_t key_value;

		key_value.key1 = (uintptr_t) i;
		key_value.key2 = (uintptr_t) i;
		key_value.value = (void *) (uintptr_t) (i * 10);
		void* old = ub_tk_lp_hashmap_insert_entry(map, &key_value);

		DR_ASSERT_MSG(old == NULL, "ub_tk_lp_test.c - test3 - 1 failed...");

		void *res = ub_tk_lp_hashmap_lookup_entry(map, (intptr_t) i,
				(intptr_t) i);
		DR_ASSERT_MSG(res == (void * ) (uintptr_t ) (i * 10),
				"ub_tk_lp_test.c - test1 - 2 failed...");
	}

	delete_count = 0;
	ub_tk_lp_hashmap_destroy(map, destroy_me);
	DR_ASSERT_MSG(delete_count == size - 1,
			"ub_tk_lp_test.c - test3 - 3 failed...");
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
}
