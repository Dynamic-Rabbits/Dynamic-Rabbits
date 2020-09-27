/**
 *  @file splaytree.h
 *  @brief A Splay Tree is a balanced binary tree with the additional
 *  property that recently accessed nodes are quickly accessed again.
 *  If we consider frequently used memory addresses, this data
 *  structures might be particularly effective.
 *  @author John F.X. Galea
 */

#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include <stdint.h>

/**
 * Enum of neighbour preferences.
 *
 */
typedef enum {

	SPLAY_TREE_LOWER_NEIGHBOUR,
	SPLAY_TREE_UPPER_NEIGHBOUR
} ub_splay_tree_neighbour_preference;


/**
 *	Creates a splay tree. To destroy use splay_tree_destroy
 *
 *	@return Returns a pointer to a net splay tree
 */
DR_EXPORT void * ub_splay_tree_create();

/**
 *	Destroys a splay tree. Assumes that the values in the tree have already been
 *	destroyed safely.
 *
 *	@param splay_tree The splay tree to destroy.
 */
DR_EXPORT void ub_splay_tree_destroy(void *splay_tree);

/**
 *	Finds the the closest entry in the splay tree to the key
 *
 *	@param splay_tree The splay tree used for insertion
 *	@param key The key to lookup
 *	@param out_found_entry Populates the entry with the found data
 *	@param pref Determines which closest neighbour preference should be returned
 *	if a node with the key is not foudn
 *  @return Returns true if an entry has been found. Returns false if a matching
 *  entry has not been found. In this case, the out_found_entry is populated with
 *  the closest entry key value
 */
DR_EXPORT bool ub_splay_tree_find(void *splay_tree_opaque, uintptr_t key,
		OUT ub_key_value_pair_t *out_found_entry, ub_splay_tree_neighbour_preference pref);

/**
 *	Inserts a new entry to the splay tree
 *
 *	@param splay_tree The splay tree used for insertion
 *	@param entry The entry to insert to the splay tree
 */
DR_EXPORT void ub_splay_tree_insert(void * splay_tree, ub_key_value_pair_t *entry);

/**
 *	Removes an entry from the splay tree
 *
 *	@param splay_tree The splay tree used for insertion
 *  @param key The key to perform lookup and delete
 *  @return Returns true upon successful deletion.
 */
DR_EXPORT bool ub_splay_tree_remove(void *splay_tree, uintptr_t key);

/**
 * @return Returns the number of nodes in the tree
 */
DR_EXPORT size_t ub_splay_tree_get_count(void * splay_tree);

#endif /* SPLAYTREE_H_ */

