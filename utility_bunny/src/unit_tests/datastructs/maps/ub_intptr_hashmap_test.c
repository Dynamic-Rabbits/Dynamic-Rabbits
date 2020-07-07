/**
 *  @file ub_intptr_hashmap_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../utility_bunny.h"

int delete_count = 0;
void *value_check;
int del_add_value_check;

void delete_me(void *value) {
	delete_count++;
}

int applied_count;
int applied_add;

void apply_me(void *value) {
	applied_count++;
	applied_add += (uintptr_t) value;
}

void specific_delete_me(void *value) {

	DR_ASSERT_MSG(value_check == value, "Value check does not match!");
	delete_count++;
}

void add_delete_me(void *value) {

	del_add_value_check += (uintptr_t) value;
	delete_count++;
}

static void test1() {

	void *intptr_hashmap = ub_intptr_hashmap_create_map();
	delete_count = 0;
	ub_intptr_hashmap_destroy_map(intptr_hashmap, delete_me);

	DR_ASSERT_MSG(delete_count == 0,
			"ub_intptr_hashmap_test.c - test1 - 0 failed...");
}

static void test2() {

	void *intptr_hashmap = ub_intptr_hashmap_create_map();

	void *value = ub_intptr_hashmap_lookup_entry(intptr_hashmap, (uintptr_t) 15);
	DR_ASSERT_MSG(value == NULL, "ub_intptr_hashmap_test.c - test2 - 0 failed...");

	ub_key_value_pair_t key_value_pair;
	key_value_pair.key = (uintptr_t) 15;
	key_value_pair.value = (void *)(uintptr_t) 88;

	void *old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test2 - 1 failed...");

	value = ub_intptr_hashmap_lookup_entry(intptr_hashmap, (uintptr_t) 15);
	DR_ASSERT_MSG(value == (void *) (intptr_t) 88, "ub_intptr_hashmap_test.c - test2 - 2 failed...");

	value_check = (void *)(uintptr_t) 88;

	delete_count = 0;
	ub_intptr_hashmap_destroy_map(intptr_hashmap, specific_delete_me);

	DR_ASSERT_MSG(delete_count == 1,
			"ub_intptr_hashmap_test.c - test2 - 3 failed...");
}

static void test3() {

	void *intptr_hashmap = ub_intptr_hashmap_create_map();

	void *value = ub_intptr_hashmap_lookup_entry(intptr_hashmap, (uintptr_t) 220);
	DR_ASSERT_MSG(value == NULL, "ub_intptr_hashmap_test.c - test3 - 0 failed...");

	value = ub_intptr_hashmap_lookup_entry(intptr_hashmap, (uintptr_t) 15);
	DR_ASSERT_MSG(value == NULL, "ub_intptr_hashmap_test.c - test3 - 1 failed...");

	ub_key_value_pair_t key_value_pair;
	key_value_pair.key = (uintptr_t) 15;
	key_value_pair.value = (void *) (uintptr_t) 88;

	void *old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test3 - 2 failed...");

	key_value_pair.key = (uintptr_t) 15;
	key_value_pair.value = (void *)(uintptr_t) 89;
	old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == (void *)(uintptr_t ) 88,
			"ub_intptr_hashmap_test.c - test3 - 3 failed...");

	value = ub_intptr_hashmap_remove_entry(intptr_hashmap, (uintptr_t) 15);
	DR_ASSERT_MSG(value == (void *)(uintptr_t) 89,
			"ub_intptr_hashmap_test.c - test3 - 4 failed...");

	delete_count = 0;
	ub_intptr_hashmap_destroy_map(intptr_hashmap, delete_me);
	DR_ASSERT_MSG(delete_count == 0,
			"ub_intptr_hashmap_test.c - test3 - 5 failed...");
}

static void test4() {

	void *intptr_hashmap = ub_intptr_hashmap_create_map();

	ub_key_value_pair_t key_value_pair;
	key_value_pair.key = (uintptr_t) (uintptr_t) 15;
	key_value_pair.value = (void *) (uintptr_t) 1;

	void *old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test4 - 0 failed...");

	key_value_pair.key = (uintptr_t) (uintptr_t) 89;
	key_value_pair.value = (void *) (uintptr_t) 2;
	old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test4 - 1 failed...");

	key_value_pair.key = (uintptr_t) (uintptr_t) 1002;
	key_value_pair.value = (void *) (uintptr_t) 3;
	old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test4 - 2 failed...");

	delete_count = 0;
	ub_intptr_hashmap_destroy_map(intptr_hashmap, add_delete_me);
	DR_ASSERT_MSG(delete_count == 3,
			"ub_intptr_hashmap_test.c - test4 - 3 failed...");

	DR_ASSERT_MSG(del_add_value_check == 6,
			"ub_intptr_hashmap_test.c - test3 - 5 failed...");
}

static void test5() {

	void *intptr_hashmap = ub_intptr_hashmap_create_map();

	ub_key_value_pair_t key_value_pair;
	key_value_pair.key = (uintptr_t) (uintptr_t) 15;
	key_value_pair.value = (void *) (uintptr_t) 1;

	void *old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test5 - 0 failed...");

	key_value_pair.key = (uintptr_t) (uintptr_t) 33;
	key_value_pair.value = (void *) (uintptr_t) 2;
	old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test5 - 1 failed...");

	key_value_pair.key = (uintptr_t) (uintptr_t) 177;
	key_value_pair.value = (void *) (uintptr_t) 3;
	old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test5 - 2 failed...");

	void *value = ub_intptr_hashmap_remove_entry(intptr_hashmap, (uintptr_t) 15);
	DR_ASSERT_MSG(value == (void *) (uintptr_t ) 1,
			"ub_intptr_hashmap_test.c - test5 - 3 failed...");

	delete_count = 0;
	del_add_value_check = 0;
	ub_intptr_hashmap_destroy_map(intptr_hashmap, add_delete_me);
	DR_ASSERT_MSG(delete_count == 2,
			"ub_intptr_hashmap_test.c - test5 - 4 failed...");

	DR_ASSERT_MSG(del_add_value_check == 5,
			"ub_intptr_hashmap_test.c - test5 - 5 failed...");
}

static void test6() {

	void *intptr_hashmap = ub_intptr_hashmap_create_map();

	ub_key_value_pair_t key_value_pair;
	key_value_pair.key = (uintptr_t) (uintptr_t) 15;
	key_value_pair.value = (void *) (uintptr_t) 1;

	void *old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test6 - 0 failed...");

	key_value_pair.key = (uintptr_t) (uintptr_t) 1;
	key_value_pair.value = (void *) (uintptr_t) 2;
	old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test6 - 1 failed...");

	key_value_pair.key = (uintptr_t) (uintptr_t) 90;
	key_value_pair.value = (void *) (uintptr_t) 3;
	old_value = ub_intptr_hashmap_insert_entry(intptr_hashmap, &key_value_pair);
	DR_ASSERT_MSG(old_value == NULL,
			"ub_intptr_hashmap_test.c - test6 - 2 failed...");

	applied_count = 0;
	applied_add = 0;
	ub_intptr_hashmap_apply_all_values(intptr_hashmap, apply_me);

	DR_ASSERT_MSG(applied_count == 3,
			"ub_intptr_hashmap_test.c - test6 - 3 failed...");

	DR_ASSERT_MSG(applied_add == 6,
			"ub_intptr_hashmap_test.c - test6 - 4 failed...");

	delete_count = 0;
	del_add_value_check = 0;
	ub_intptr_hashmap_destroy_map(intptr_hashmap, add_delete_me);
	DR_ASSERT_MSG(delete_count == 3,
			"ub_intptr_hashmap_test.c - test6 - 5 failed...");

	DR_ASSERT_MSG(del_add_value_check == 6,
			"ub_intptr_hashmap_test.c - test6 - 6 failed...");
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
}
