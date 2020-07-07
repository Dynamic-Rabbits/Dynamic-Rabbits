/**
 *  @file ub_splaytree_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../../utility_bunny.h"

static void test1() {

	void *splay_tree = ub_splay_tree_create();

	for (int i = 0; i < 4; i++) {

		ub_key_value_pair_t key_value;
		key_value.key = i;
		key_value.value = (void *) (uintptr_t) i;

		ub_splay_tree_insert(splay_tree, &key_value);

		dr_fprintf(STDERR, "ADDED!-----\n");
		ub_key_value_pair_t out;
		bool ret = ub_splay_tree_find(splay_tree, i, &out,
				SPLAY_TREE_LOWER_NEIGHBOUR);

		DR_ASSERT_MSG(ret == true, "ub_splaytree_test - test1 failed...");

		DR_ASSERT_MSG(out.key == i, "ub_splaytree_test - test1 failed...");

		dr_fprintf(STDERR, "DONE!-- %d ---\n", i);

	}

	DR_ASSERT_MSG(ub_splay_tree_get_count(splay_tree) == 4,
			"ub_splaytree_test - test1 failed...");

	ub_key_value_pair_t out;

	bool ret = ub_splay_tree_find(splay_tree, 1, &out,
			SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(ret == true, "ub_splaytree_test - test1 failed...");

	DR_ASSERT_MSG(out.key == 1, "ub_splaytree_test - test1 failed...");

	DR_ASSERT_MSG(out.value == (void * ) (uintptr_t ) 1,
			"ub_splaytree_test - test1 failed...");

	ub_splay_tree_destroy(splay_tree);
}

static void test2() {

	void *splay_tree = ub_splay_tree_create();

	for (int i = 0; i < 4; i++) {

		ub_key_value_pair_t key_value;
		key_value.key = i;
		key_value.value = (void *) (uintptr_t) i;

		ub_splay_tree_insert(splay_tree, &key_value);
	}

	ub_key_value_pair_t key_value;
	key_value.key = 5;
	key_value.value = (void *) (uintptr_t) 5;

	ub_splay_tree_insert(splay_tree, &key_value);

	DR_ASSERT_MSG(ub_splay_tree_get_count(splay_tree) == 5,
			"ub_splaytree_test - test1 failed...");

	ub_key_value_pair_t out;

	bool ret = ub_splay_tree_find(splay_tree, 4, &out,
			SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(ret == false, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.key == 3, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.value == (void * ) (uintptr_t ) 3,
			"ub_splaytree_test - test1 failed...");

	ret = ub_splay_tree_find(splay_tree, 4, &out, SPLAY_TREE_UPPER_NEIGHBOUR);

	DR_ASSERT_MSG(ret == false, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.key == 5, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.value == (void * ) (uintptr_t ) 5,
			"ub_splaytree_test - test1 failed...");

	ub_splay_tree_destroy(splay_tree);
}

static void test3() {

	void *splay_tree = ub_splay_tree_create();

	for (int i = 0; i < 1000; i++) {

		ub_key_value_pair_t key_value;
		key_value.key = i;
		key_value.value = (void *) (uintptr_t) i;

		ub_splay_tree_insert(splay_tree, &key_value);
	}

	ub_key_value_pair_t out;
	bool ret = ub_splay_tree_find(splay_tree, 50, &out,
			SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(ret == true, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.key == 50, "ub_splaytree_test - test1 failed...");

	ret = ub_splay_tree_find(splay_tree, 1000, &out, SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(ret == false, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.key == 999, "ub_splaytree_test - test1 failed...");

	ub_splay_tree_destroy(splay_tree);
}

static void test4() {

	void *splay_tree = ub_splay_tree_create();

	for (int i = 0; i < 1000; i++) {

		ub_key_value_pair_t key_value;
		key_value.key = i;
		key_value.value = (void *) (uintptr_t) i;

		ub_splay_tree_insert(splay_tree, &key_value);
	}

	ub_key_value_pair_t out;
	bool ret = ub_splay_tree_find(splay_tree, 50, &out,
			SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(ret == true, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.key == 50, "ub_splaytree_test - test1 failed...");

	ret = ub_splay_tree_find(splay_tree, 70, &out, SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(ub_splay_tree_get_count(splay_tree) == 1000,
			"ub_splaytree_test - test1 failed...");

	ret = ub_splay_tree_remove(splay_tree, 50);

	DR_ASSERT_MSG(ret == true, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(ub_splay_tree_get_count(splay_tree) == 999,
			"ub_splaytree_test - test1 failed...");

	ret = ub_splay_tree_remove(splay_tree, 50);

	DR_ASSERT_MSG(ret == false, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(ub_splay_tree_get_count(splay_tree) == 999,
			"ub_splaytree_test - test1 failed...");

	ret = ub_splay_tree_find(splay_tree, 50, &out, SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(ret == false, "ub_splaytree_test - test1 failed...");
	DR_ASSERT_MSG(out.key == 49, "ub_splaytree_test - test1 failed...");

	ub_key_value_pair_t key_value;
	key_value.key = 50;
	key_value.value = (void *) (uintptr_t) 50;
	ub_splay_tree_insert(splay_tree, &key_value);

	ret = ub_splay_tree_find(splay_tree, 50, &out, SPLAY_TREE_LOWER_NEIGHBOUR);

	DR_ASSERT_MSG(out.key == 50, "ub_splaytree_test - test1 failed...");


	DR_ASSERT_MSG(ub_splay_tree_get_count(splay_tree) == 1000,
			"ub_splaytree_test - test1 failed...");

	ub_splay_tree_destroy(splay_tree);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();

}
