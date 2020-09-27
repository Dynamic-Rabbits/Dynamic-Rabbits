/**
 * @author John F.X. Galea
 */

/*
 * Source modified from open source: http://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c
 */

#include "ub_splaytree.h"
#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drutil.h"
#include <stddef.h>

typedef struct splay_tree_node {
	struct splay_tree_node * left, *right;
	uintptr_t key;
	void *value;
} splay_tree_node_t;

typedef struct splay_tree {
	size_t size;
	splay_tree_node_t *root;
} splay_tree_t;

static splay_tree_node_t* splay_tree_splay(splay_tree_node_t *splay_tree_node,
		uintptr_t key);

DR_EXPORT void * ub_splay_tree_create() {

	splay_tree_t *splay_tree = dr_global_alloc(sizeof(splay_tree_t));
	splay_tree->root = NULL;
	splay_tree->size = 0;

	return splay_tree;
}

DR_EXPORT void ub_splay_tree_destroy(void *splay_tree_opaque) {

	splay_tree_t *splay_tree = (splay_tree_t *) splay_tree_opaque;

	// Keep on deleting the root till no node is left.
	while (splay_tree->root != NULL) {
		DR_ASSERT(splay_tree->size);
		ub_splay_tree_remove(splay_tree_opaque, splay_tree->root->key);
	}
	dr_global_free(splay_tree, sizeof(splay_tree_t));
}

DR_EXPORT size_t ub_splay_tree_get_count(void * splay_tree_opaque) {

	splay_tree_t *splay_tree = (splay_tree_t *) splay_tree_opaque;
	return splay_tree->size;
}

DR_EXPORT bool ub_splay_tree_find(void *splay_tree_opaque, uintptr_t key,
		OUT ub_key_value_pair_t *out_found_entry,
		ub_splay_tree_neighbour_preference pref) {

	splay_tree_t *splay_tree = (splay_tree_t *) splay_tree_opaque;

	splay_tree_node_t *found_node = splay_tree_splay(splay_tree->root, key);

	if (found_node) {

		if (pref == SPLAY_TREE_LOWER_NEIGHBOUR&&
		found_node->key > key &&
		found_node->left != NULL) {
			found_node = splay_tree_splay(found_node->left->value, key);
		}

		if (pref == SPLAY_TREE_UPPER_NEIGHBOUR&&
		found_node->key < key &&
		found_node->right != NULL) {
			found_node = splay_tree_splay(found_node->right->value, key);
		}

		out_found_entry->key = found_node->key;
		out_found_entry->value = found_node->value;
		splay_tree->root = found_node;
	}

	return out_found_entry->key == key;
}

/**
 *  Accesses node and places it as the top node. Its next access will be
 *  done quickly.
 *
 *  @param splay_tree_node The top node
 *  @param key The key used for lookup
 *  @return The found node that is equal to the key or close to the key
 */
static splay_tree_node_t* splay_tree_splay(splay_tree_node_t *splay_tree_node,
		uintptr_t key) {

	splay_tree_node_t node, *left, *right, *y;

	if (splay_tree_node == NULL)
		return NULL;

	node.left = NULL;
	node.right = NULL;
	left = right = &node;

	while (true) {

		if (key < splay_tree_node->key) {

			if (splay_tree_node->left == NULL)
				break;

			if (key < splay_tree_node->left->key) {
				y = splay_tree_node->left;
				splay_tree_node->left = y->right;
				y->right = splay_tree_node;
				splay_tree_node = y;
				if (splay_tree_node->left == NULL)
					break;
			}

			right->left = splay_tree_node;
			right = splay_tree_node;
			splay_tree_node = splay_tree_node->left;

		} else if (key > splay_tree_node->key) {

			if (splay_tree_node->right == NULL)
				break;
			if (key > splay_tree_node->right->key) {
				y = splay_tree_node->right;
				splay_tree_node->right = y->left;
				y->left = splay_tree_node;
				splay_tree_node = y;
				if (splay_tree_node->right == NULL)
					break;
			}
			left->right = splay_tree_node;
			left = splay_tree_node;
			splay_tree_node = splay_tree_node->right;

		} else {
			break;
		}
	}

	left->right = splay_tree_node->left;
	right->left = splay_tree_node->right;
	splay_tree_node->left = node.right;
	splay_tree_node->right = node.left;
	return splay_tree_node;
}

DR_EXPORT void ub_splay_tree_insert(void * splay_tree_opaque,
		ub_key_value_pair_t *entry) {

	splay_tree_node_t *new_node = (splay_tree_node_t *) dr_global_alloc(
			sizeof(splay_tree_node_t));

	new_node->key = entry->key;
	new_node->value = entry->value;

	splay_tree_t *splay_tree = (splay_tree_t *) splay_tree_opaque;

	if (splay_tree->root == NULL) {
		new_node->left = NULL;
		new_node->right = NULL;
		splay_tree->size++;
		splay_tree->root = new_node;
		return;
	}

	// We splay then insert.
	splay_tree->root = splay_tree_splay(splay_tree->root, entry->key);

	if (entry->key < splay_tree->root->key) {

		new_node->left = splay_tree->root->left;
		new_node->right = splay_tree->root;
		splay_tree->root->left = NULL;
		splay_tree->size++;
		splay_tree->root = new_node;

	} else if (entry->key > splay_tree->root->key) {

		new_node->right = splay_tree->root->right;
		new_node->left = splay_tree->root;
		splay_tree->root->right = NULL;
		splay_tree->size++;
		splay_tree->root = new_node;

	} else {
		dr_global_free(new_node, sizeof(splay_tree_node_t));
		splay_tree->root->key = entry->key;
		splay_tree->root->value = entry->value;
	}
}

DR_EXPORT bool ub_splay_tree_remove(void * splay_tree_opaque, uintptr_t key) {

	splay_tree_t *splay_tree = (splay_tree_t *) splay_tree_opaque;

	if (splay_tree->root == NULL)
		return false;

	splay_tree_node_t *new_root;

	splay_tree->root = splay_tree_splay(splay_tree->root, key);

	if (key == splay_tree->root->key) {

		if (splay_tree->root->left == NULL) {
			new_root = splay_tree->root->right;
		} else {
			new_root = splay_tree_splay(splay_tree->root->left, key);
			DR_ASSERT(new_root->right == NULL);
			new_root->right = splay_tree->root->right;
		}

		splay_tree->size--;
		dr_global_free(splay_tree->root, sizeof(splay_tree_node_t));
		splay_tree->root = new_root;
		return true;
	}

	return false;
}
