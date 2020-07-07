/*
 * ub_bdd_test.c
 *
 *      Author: john
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../../../utility_bunny.h"

void test1() {

	ub_bdd_node_t bdd = ub_bdd_create();

	ub_bitvect_t *vect = ub_bitvect_create(10);

	for (int i = 0; i < 4; i++)
		ub_bitvect_set_bit(vect, i, true);

    ub_bitvect_set_bit(vect, 9, true);

	ub_bdd_node_t entry = ub_bdd_insert(bdd, vect);
	ub_bdd_node_t entry2 = ub_bdd_insert(bdd, vect);

	DR_ASSERT(entry == entry2);

	ub_bitvect_t *u = ub_bdd_get_bit_vect(entry);
	DR_ASSERT(ub_bitvect_equal(u, vect));

	size_t size = ub_bitvect_get_size(u);

    ub_bitvect_destroy(vect);
    ub_bitvect_destroy(u);

	ub_bdd_destroy(bdd);
}

void test2() {

	ub_bdd_node_t bdd = ub_bdd_create();

	ub_bitvect_t *vect = ub_bitvect_create(9);

	for (int i = 0; i < 9; i++){
		ub_bitvect_set_bit(vect, i, i % 2 == 0);
	}

	ub_bitvect_t *vect2 = ub_bitvect_create(10);
	for (int i = 0; i < 10; i++){
		ub_bitvect_set_bit(vect2, i, i % 2 ==1);
	}

	ub_bdd_node_t node1 = ub_bdd_insert(bdd, vect);
	ub_bdd_node_t node2 = ub_bdd_insert(bdd, vect2);

    ub_bitvect_println(vect);
    ub_bitvect_println(vect2);

    ub_bitvect_t *node1_bv = ub_bdd_get_bit_vect(node1);
	DR_ASSERT(ub_bitvect_equal(node1_bv, vect));
    ub_bitvect_destroy(node1_bv);

    ub_bitvect_t *node2_bv = ub_bdd_get_bit_vect(node2);
	DR_ASSERT(ub_bitvect_equal(node2_bv, vect2));
    ub_bitvect_destroy(node2_bv);

	ub_bdd_node_t union_node = ub_bdd_node_union(bdd, node1, node2);

    ub_bitvect_t *union_bitvect = ub_bitvect_create(10);
    for (int i = 0; i < 10; i++){
        ub_bitvect_set_bit(union_bitvect, i, true);
    }

    ub_bitvect_println(union_bitvect);

    ub_bitvect_t *node3_bv = ub_bdd_get_bit_vect(union_node);
    ub_bitvect_println(node3_bv);
    ub_bitvect_destroy(node3_bv);

    ub_bitvect_t *node4_bv = ub_bdd_get_bit_vect(union_node);
	DR_ASSERT(ub_bitvect_equal(union_bitvect, node4_bv));
    ub_bitvect_destroy(node4_bv);

	ub_bitvect_destroy(vect);
	ub_bitvect_destroy(vect2);
	ub_bitvect_destroy(union_bitvect);
	ub_bdd_destroy(bdd);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
}


