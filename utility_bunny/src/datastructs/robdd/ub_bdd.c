#include "ub_bdd.h"
#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drutil.h"
#include <stddef.h>
#include <string.h>

typedef struct bdd_node {

    struct bdd_node *parent;
    struct bdd_node *left_child;
    struct bdd_node *right_child;
    unsigned int level;
} bdd_node_t;

static bdd_node_t *ub_bdd_create_node(unsigned int level) {

    bdd_node_t *node = dr_global_alloc(sizeof(bdd_node_t));

    node->parent = NULL;
    node->left_child = NULL;
    node->right_child = NULL;
    node->level = level;

    return node;
}

static void ub_bdd_destroy_node(ub_bdd_node_t node_opaque) {

    DR_ASSERT(node_opaque);
    bdd_node_t *node = (bdd_node_t *) node_opaque;
    dr_global_free(node, sizeof(bdd_node_t));
}

DR_EXPORT ub_bdd_node_t ub_bdd_create() {

    // Create a root node and simply return it.
    return (ub_bdd_node_t) ub_bdd_create_node(0);
}

DR_EXPORT void ub_bdd_destroy(ub_bdd_node_t root_node_opaque) {

	DR_ASSERT(root_node_opaque);

    bdd_node_t *root_node = (bdd_node_t *) root_node_opaque;

    // Destroy left subtree
    if (root_node->left_child)
        ub_bdd_destroy((ub_bdd_node_t) root_node->left_child);

    // Destroy right subtree
    if (root_node->right_child)
        ub_bdd_destroy((ub_bdd_node_t) root_node->right_child);

    // Delete the node.
    ub_bdd_destroy_node((ub_bdd_node_t) root_node);
}

DR_EXPORT ub_bitvect_t *ub_bdd_get_bit_vect(ub_bdd_node_t node_opaque) {

    bdd_node_t *node = (bdd_node_t *) node_opaque;
    DR_ASSERT(node);

    ub_bitvect_t *bitvect = ub_bitvect_create(node->level);

    int index = node->level - 1;

    while (index >= 0) {

        bdd_node_t *parent = node->parent;
        DR_ASSERT(parent);

        if (parent->left_child == node) {
            ub_bitvect_set_bit(bitvect, index, false);
        } else if (parent->right_child == node) {
            ub_bitvect_set_bit(bitvect, index, true);

        } else {
            DR_ASSERT(false);
        }

        node = parent;

        index--;
    }

    return bitvect;
}

DR_EXPORT ub_bdd_node_t ub_bdd_insert(ub_bdd_node_t root_node,
        ub_bitvect_t *bit_vect) {

    DR_ASSERT(bit_vect);
    DR_ASSERT(root_node);

    ub_bitvect_trim(bit_vect);

    DR_ASSERT(
            ub_bitvect_get_start_trailing_zero(bit_vect) == bit_vect->bit_size);

    bdd_node_t *node = (bdd_node_t *) root_node;
    bdd_node_t *temp_node = NULL;

    size_t level = 1;
    byte mask = 1;
    for (size_t i = 0; i < bit_vect->byte_size; i++) {

        byte val = bit_vect->value[i];
        size_t size = UB_BYTE_SIZE;

        if ((i + 1) * UB_BYTE_SIZE > bit_vect->bit_size)
            size = bit_vect->bit_size - (i * UB_BYTE_SIZE);

        for (size_t j = 0; j < size; j++) {

            if (val & mask) {

                temp_node = node->right_child;

                if (!temp_node) {
                    // Create next.
                    temp_node = ub_bdd_create_node(level);
                    node->right_child = temp_node;
                    temp_node->parent = node;
                }

            } else {

                temp_node = node->left_child;

                if (!temp_node) {
                    temp_node = ub_bdd_create_node(level);
                    node->left_child = temp_node;
                    temp_node->parent = node;
                }
            }

            val = val >> 1;

            node = temp_node;
            level++;
        }
    }

    return (ub_bdd_node_t) node;
}

DR_EXPORT ub_bdd_node_t ub_bdd_node_union(ub_bdd_node_t root_node_opaque,
        ub_bdd_node_t node_opaque, ub_bdd_node_t node2_opaque) {

    bdd_node_t *node = (bdd_node_t *) node_opaque;
    bdd_node_t *node2 = (bdd_node_t *) node2_opaque;

    ub_bitvect_t *bitvect1 = ub_bdd_get_bit_vect(node);
    ub_bitvect_t *bitvect2 = ub_bdd_get_bit_vect(node2);

    ub_bitvect_t * union_vect = ub_bitvect_union(bitvect1, bitvect2);

    bdd_node_t *result = ub_bdd_insert(root_node_opaque, union_vect);

    ub_bitvect_destroy(union_vect);
    ub_bitvect_destroy(bitvect1);
    ub_bitvect_destroy(bitvect2);

    return (ub_bdd_node_t) result;
}
