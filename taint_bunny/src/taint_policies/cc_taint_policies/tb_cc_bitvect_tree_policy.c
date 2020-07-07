/*
 * tb_raw_tree.c
 *
 *      Author: john
 */

#include "tb_cc_bitvect_tree_policy.h"

#include "utility_bunny.h"
#include "drreg.h"

/*********************************************************************
 * Prototypes
 */

static void *tb_cc_tree_get_default_label();
static bool meet(void **meet_tl, void *src);
static void *propogate_func_1dst_1src(void *src);
static void *propogate_func_1dst_2src(void *src_opaque, void *src2_opaque);

/*********************************************************************
 * Global variables
 */

#define COUNTER_MAX 32
static int counter = 0;

static ub_bdd_node_t root_node = NULL;
static void *map;

void *mutex;

/*********************************************************************
 * Implementation
 */

DR_EXPORT void * tb_cc_bitvector_tree_get_label_helper(int index) {

	ub_bitvect_t*bitvect = ub_bitvect_create(index + 1);
	ub_bitvect_set_bit(bitvect, index, true);

	ub_bdd_node_t node = ub_bdd_insert(root_node, bitvect);
	ub_two_key_value_pair_t key_val_pair;
	key_val_pair.value = (void *) node;
	key_val_pair.key1 = (uintptr_t) node;
	key_val_pair.key2 = (uintptr_t) node;
	ub_tk_arraymap_insert_entry(map, &key_val_pair);

	ub_bitvect_destroy(bitvect);

	return (void *) node;
}

static void *tb_cc_tree_get_default_label() {

	return (void *) tb_cc_bitvector_tree_get_label(0);
}

DR_EXPORT void *tb_cc_tree_get_inc_default_label() {

	dr_mutex_lock(mutex);
	void *new_label = (void *) tb_cc_bitvector_tree_get_label_helper(counter);

	counter++;

	if (counter >= COUNTER_MAX)
		counter = 0;

	dr_mutex_unlock(mutex);

	return new_label;
}

DR_EXPORT void tb_cc_initialise_bitvector_tree_taint_policy(
		tb_cc_taint_policy_t *taint_policy) {

	root_node = ub_bdd_create();
	map = ub_tk_arraymap_create_map();

	mutex = dr_mutex_create();
	memset(taint_policy, 0, sizeof(tb_cc_taint_policy_t));

	taint_policy->meet_func = meet;
	taint_policy->propagate_1dst_1src_func = propogate_func_1dst_1src;
	taint_policy->propagate_1dst_2src_func = propogate_func_1dst_2src;

	taint_policy->get_default_label = tb_cc_tree_get_default_label;
}

DR_EXPORT void tb_cc_destroy_bitvector_tree_taint_policy() {

	ub_bdd_destroy(root_node);
	root_node = NULL;

	ub_tk_arraymap_destroy_map(map, NULL);
	map = NULL;

	dr_mutex_destroy(mutex);
	mutex = NULL;
}

DR_EXPORT void * tb_cc_bitvector_tree_get_label(int index) {

	dr_mutex_lock(mutex);
	void *res = tb_cc_bitvector_tree_get_label_helper(index);
	dr_mutex_unlock(mutex);

	return res;
}

static ub_bdd_node_t insert_new_bitvector(ub_bdd_node_t node1,
		ub_bdd_node_t node2) {

	DR_ASSERT(node1 != NULL);
	DR_ASSERT(node2 != NULL);

	ub_bdd_node_t res = ub_bdd_node_union(root_node, (ub_bdd_node_t) node1,
			(ub_bdd_node_t) node2);

	ub_two_key_value_pair_t key_val_pair;
	key_val_pair.value = (void *) res;

	void* old = NULL;

	/* Add the different combos to the map */
	key_val_pair.key1 = (uintptr_t) node1;
	key_val_pair.key2 = (uintptr_t) node2;
	old = ub_tk_arraymap_insert_entry(map, &key_val_pair);
	DR_ASSERT(!old);

	key_val_pair.key1 = (uintptr_t) node2;
	key_val_pair.key2 = (uintptr_t) node1;
	old = ub_tk_arraymap_insert_entry(map, &key_val_pair);
	DR_ASSERT(!old);

	key_val_pair.key1 = (uintptr_t) node1;
	key_val_pair.key2 = (uintptr_t) res;
	old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

	key_val_pair.key1 = (uintptr_t) res;
	key_val_pair.key2 = (uintptr_t) node1;
	old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

	key_val_pair.key1 = (uintptr_t) node2;
	key_val_pair.key2 = (uintptr_t) res;
	old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

	key_val_pair.key1 = (uintptr_t) res;
	key_val_pair.key2 = (uintptr_t) node2;
	old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

	key_val_pair.key1 = (uintptr_t) res;
	key_val_pair.key2 = (uintptr_t) res;
	old = ub_tk_arraymap_insert_entry(map, &key_val_pair);

	return res;
}

static bool meet(void **meet_tl, void *src) {

	if (src != NULL) {

		if (*meet_tl == NULL) {
			*meet_tl = src;
		} else {

			dr_mutex_lock(mutex);
			ub_bdd_node_t result = ub_tk_arraymap_lookup_entry(map,
					(intptr_t) src, (intptr_t) *meet_tl);

			if (result == NULL) {
				result = insert_new_bitvector(src, *meet_tl);
			}
			dr_mutex_unlock(mutex);

			*meet_tl = src;
		}
	}

	return false;
}

static void *propogate_func_1dst_1src(void *src) {

	return src;
}

static void *propogate_func_1dst_2src(void *src_opaque, void *src2_opaque) {

	ub_bdd_node_t bdd_node = (ub_bdd_node_t *) src_opaque;
	ub_bdd_node_t bdd_node2 = (ub_bdd_node_t *) src2_opaque;

	if (!bdd_node && !bdd_node2)
		return NULL;

	else if (bdd_node && !bdd_node2)
		return bdd_node;

	else if (!bdd_node && bdd_node2)
		return bdd_node2;
	else {

		dr_mutex_lock(mutex);

		ub_bdd_node_t result = ub_tk_arraymap_lookup_entry(map,
				(intptr_t) bdd_node, (intptr_t) bdd_node2);

		if (result == NULL)
			result = insert_new_bitvector(bdd_node, bdd_node2);

		dr_mutex_unlock(mutex);

		return result;
	}
}
