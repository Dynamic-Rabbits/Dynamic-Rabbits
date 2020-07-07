/*
 * @author John F.X. Galea
 */

#include "ub_arraymap.h"
#include <string.h>
#include "../../instrumentation/ub_instrum_insert.h"

/***************************************************************************
 *  Structs and defintions
 */

/**
 *  @struct ub_arraymap_list_node_t
 *
 *  @brief A struct that defines a node entry in the map
 *
 *  @var drarraymap_list_node::key
 *  The key, which is the operand being tracked
 *
 *  @var drarraymap_list_node::used_flag
 *  A flag denoting whether the node is being used. This is required for our hydration approach
 *
 *  @var drarraymap_list_node::value
 *  The value mapped by the key
 *
 *  @var drarraymap_list_node::next
 *  A pointer to the next node in the list.
 */
typedef struct arraymap_list_node {

	uintptr_t key;
	uintptr_t used_flag;
	void *value;
	struct arraymap_list_node *next;

} ub_arraymap_list_node_t;

/**
 *  @struct arraymap_map_t
 *
 *  @var drarraymap_map_t::max_size
 *  Size of arraymap
 *
 *  @var drarraymap_list_node_t::array_map
 *  The actual array map
 *
 *  @var drarraymap_list_node_t::type_flag
 *  Flag that defines whether the map is a Mem or Reg map.
 *
 */
typedef struct {

	size_t max_size;
	ub_arraymap_list_node_t **array_map;
} ub_arraymap_map_t;

/***************************************************************************
 *  Static Prototypes
 */

static ub_arraymap_list_node_t *ub_arraymap_create_list_node();

static ub_arraymap_list_node_t *ub_arraymap_lookup_node(void *map_opaque,
		uintptr_t key);

/***************************************************************************
 *  Map Operations.
 */

DR_EXPORT void *ub_arraymap_create_map(size_t size) {

	ub_arraymap_map_t *map = (ub_arraymap_map_t *) dr_global_alloc(
			sizeof(ub_arraymap_map_t));

	if (map != NULL) {

		// Allocation of array map
		ub_arraymap_list_node_t **array_map;
		array_map = (ub_arraymap_list_node_t**) dr_global_alloc(
				sizeof(ub_arraymap_list_node_t *) * size);

		if (array_map != NULL) {

			// Populate the struct.
			map->array_map = array_map;
			map->max_size = size;

			//Initialise array-map entries
			memset(map->array_map, 0,
					sizeof(ub_arraymap_list_node_t *) * map->max_size);

			return (void *) map;
		}

		// Since allocation for array map failed, we deallocate the map structure before returning.
		dr_global_free(map, sizeof(ub_arraymap_map_t));

	}

	return NULL;
}

DR_EXPORT void ub_arraymap_destroy_map(void *map_opaque,
		ub_destroy_value_func_t detroy_func) {

	ub_arraymap_map_t *map = (ub_arraymap_map_t *) map_opaque;

	if (map != NULL) {

		// Iterate through the array map, and deallocate all data containers.
		size_t i;
		for (i = 0; i < map->max_size; i++) {

			//dr_fprintf(STDERR, "Size: %d\n", i);
			ub_arraymap_list_node_t *node = map->array_map[i];

			while (node != NULL) {

				// Iterate through list and clear.
				ub_arraymap_list_node_t *freed_node = node;
				// Load next pointer.
				node = node->next;

				// Destroy value
				if (freed_node->used_flag && detroy_func)
					detroy_func(freed_node->value);

				// Destroy the struct
				dr_global_free(freed_node, sizeof(ub_arraymap_list_node_t));
			}
		}

		dr_global_free(map->array_map,
				sizeof(ub_arraymap_list_node_t *) * map->max_size);
		dr_global_free(map, sizeof(ub_arraymap_map_t));

	}
}

/**
 *  Upon insertion, the function performs the following steps:
 *
 *  1)  If array head is NULL, simply create a list_node and make it as the head. Simply return afterwards.
 *  2)  If head is not NULL, iterate through the list and check if an entry with that key exists. Also record, if available,
 *      an unused list node during iteration.
 *  3)  If a node with the same key is found, then simply modify the node and return.
 *  4)  If no node is found that is associated with the key, check if an available node was recorded.
 *  5)  If an available node was recorded, simply modify it with the new data and return.
 *  6)  Lastly, if an available node was not found, create a new list node, append as the head of the list, and return.
 *
 *  Note that the data structure is designed to avoid invoking as many allocations as possible. (At a high-level, we are taking a hydration approach).
 *  Further optimisations are left for future work.
 */
DR_EXPORT void* ub_arraymap_insert_entry(void *map_opaque,
		ub_key_value_pair_t *key_val_pair) {

	DR_ASSERT(map_opaque);

	ub_arraymap_map_t *map = (ub_arraymap_map_t *) map_opaque;

	size_t index = ((size_t) key_val_pair->key) % map->max_size;

	ub_arraymap_list_node_t **node = &(map->array_map[index]);
	ub_arraymap_list_node_t *available_node = NULL;

	while (*node != NULL) {

		// If node is unused, record it.
		if (available_node == NULL && (*node)->used_flag == 0)
			available_node = *node;

		if (((*node)->used_flag == true) && key_val_pair->key == (*node)->key) {

			void *old_value = (*node)->value;
			(*node)->value = key_val_pair->value;

			return old_value;
		}

		// Try next node.
		node = &((*node)->next);
	}

	// No entry, with the associated key, was found.

	// Check if an available node was found during the iteration.
	if (available_node == NULL) {

		// Allocate the list node appropriately.
		available_node = ub_arraymap_create_list_node();

		if (available_node == NULL)
			return NULL;

		available_node->next = NULL;
		*node = available_node;
	}

	// Initialise node.
	available_node->key = key_val_pair->key;
	available_node->value = key_val_pair->value;
	available_node->used_flag = true;

	return NULL;
}

/**
 * Creates and returns a new list node.
 *
 * @return A new list node
 */
static ub_arraymap_list_node_t *ub_arraymap_create_list_node() {

	ub_arraymap_list_node_t *list_node = NULL;

	// Allocate the list_node with the proper allocator.

	list_node = (ub_arraymap_list_node_t *) dr_global_alloc(
			sizeof(ub_arraymap_list_node_t));

	if (list_node != NULL) {
		// Initialise the newly created node.
		memset(list_node, 0, sizeof(ub_arraymap_list_node_t));
	}

	return list_node;
}

/**
 *  Performs a lookup on the map and retrieves the node.
 *
 *  @param map The map to perform lookup operation on.
 *  @param key The key to lookup.
 *  @return Returns the found node. Returns Null if node is not found.
 */
static ub_arraymap_list_node_t *ub_arraymap_lookup_node(void *map_opaque,
		uintptr_t key) {

	ub_arraymap_map_t *map = (ub_arraymap_map_t *) map_opaque;

	size_t index = ((size_t) key) % map->max_size;

	ub_arraymap_list_node_t *node = (map->array_map[index]);

	// Iterate through bucket list.
	while (node != NULL) {

		// Note it is important to check that the node is actually in use.
		if (node->used_flag == true && key == node->key)
			return node;

		// Try next node.
		node = node->next;
	}

	// Failed to find a matching node.
	return NULL;
}

DR_EXPORT void *ub_arraymap_lookup_entry(void *map_opaque, uintptr_t key) {

	ub_arraymap_list_node_t * node = ub_arraymap_lookup_node(map_opaque, key);

	if (node != NULL)
		return node->value;
	else
		return NULL;
}

DR_EXPORT void * ub_arraymap_remove_entry(void *map_opaque, uintptr_t key) {

	ub_arraymap_list_node_t *node = ub_arraymap_lookup_node(map_opaque, key);

	if (node) {

		/**
		 *  We simply make it available by setting the flag to 0. Note that no forced
		 *  deallocation takes place for the node containers.
		 */
		node->used_flag = false;
		return node->value;
	}

	return NULL;
}

/**
 *  Inserts inline code that performs a look-up .
 *
 *  DR_REG_XDX -> lookup res (out)
 *  opnd_reg -> opnd (in) (preserved)
 *  DR_REG_XAX -> scratch
 *
 *  map_reg -> the map reg (in) (preserved)
 *  scratch_reg -> scratch
 *  scratch_reg -> scratch
 *
 *  Note XAX needs to be scratch due to the div operation
 *
 *  As a result:
 *    DR_REG_XDX -> located node (if found).
 *    else:  available node (if found).
 *    else:  NULL.
 */
void ub_arraymap_insert_lookup_entry(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t key_reg, reg_id_t map_reg,
		reg_id_t scratch_reg) {
    DR_ASSERT(false);
	opnd_t opnd, opnd2;
	instr_t *instr;

	// Clear XDX with XOR
	opnd = opnd_create_reg(DR_REG_XDX);
	instr = INSTR_CREATE_xor(drcontext, opnd, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Place opnd data into XAX to prepare for div instr.

	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, key_reg, DR_REG_XAX);

	// Load map size
	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, map_reg,
			offsetof(ub_arraymap_map_t, max_size), scratch_reg);
	/**
	 *  Insert div instruction to perform modulus operation. Divisor is placed in XAX (we are not interested in the divisor),
	 *  whilst remainder is placed in XDX.
	 */

	instr = instr_create_2dst_3src(drcontext, OP_div,
			opnd_create_reg(DR_REG_XDX), opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(scratch_reg), opnd_create_reg(DR_REG_XDX),
			opnd_create_reg(DR_REG_XAX));
	instrlist_meta_preinsert(ilist, where, instr);

	// Load array pointer.
	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, map_reg,
			offsetof(ub_arraymap_map_t, array_map), DR_REG_XAX);

	/**
	 *  Create base + disp operand to fetch the correct bucket list from array map.
	 *  [base + index*scale + disp] where:
	 *    base is the start of the array map
	 *    index is the remainder of the div operation.
	 *    scale is the size of a node pointer.
	 *    disp is set to 0.
	 *
	 *  As a result, XDX contains the head of the list. Note this could be NULL in case the
	 *  bucket has not yet been initialised.
	 */

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, map_reg,
			offsetof(ub_arraymap_map_t, array_map), DR_REG_XAX);

	opnd = opnd_create_base_disp(
	DR_REG_XAX, DR_REG_XDX, sizeof(ub_arraymap_map_t *), 0,
	OPSZ_PTR);
	opnd2 = opnd_create_reg(DR_REG_XDX);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd2, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Clear scratch (now considered the available node).
	opnd = opnd_create_reg(DR_REG_XAX);
	instr = INSTR_CREATE_xor(drcontext, opnd, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Initialise needed labels to iterate over bucket list.
	instr_t* begin_label = INSTR_CREATE_label(drcontext);
	instr_t* final_check_label = INSTR_CREATE_label(drcontext);
	instr_t* done_label = INSTR_CREATE_label(drcontext);
	instr_t* iterate_label = INSTR_CREATE_label(drcontext);
	instr_t* available_label = INSTR_CREATE_label(drcontext);

	// Insert iteration label of loop.
	instrlist_meta_preinsert(ilist, where, begin_label);

	// Check whether the head of the bucket list is null

	ub_instrum_check_null_true_case(drcontext, ilist, where, DR_REG_XDX,
			final_check_label);

	// Otherwise, check if the node is in use.

	// Load use flag
	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, DR_REG_XDX,
			offsetof(ub_arraymap_list_node_t, used_flag), scratch_reg);

	// Check if the flag is not in use
	ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
			available_label);

	// Check that the operand and the key are equal.

	// Load key
	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, DR_REG_XDX,
			offsetof(ub_arraymap_list_node_t, key), scratch_reg);

	opnd = opnd_create_reg(scratch_reg);
	opnd2 = opnd_create_reg(key_reg);
	instr = INSTR_CREATE_cmp(drcontext, opnd2, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// If they are equal, jump to done label.
	opnd = opnd_create_instr(done_label);
	instr = INSTR_CREATE_jcc(drcontext, OP_je, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_instr(iterate_label);
	instr = INSTR_CREATE_jmp(drcontext, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Insert available label.
	instrlist_meta_preinsert(ilist, where, available_label);

	// Check if XAX already has stored an available node.

	ub_instrum_check_null_false_case(drcontext, ilist, where, DR_REG_XAX,
			iterate_label);

	// Otherwise, initialise  with the node stored in XDX.
	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, DR_REG_XAX,
			DR_REG_XDX);

	// Insert the iterate label to move to the next node.
	instrlist_meta_preinsert(ilist, where, iterate_label);

	// Load next node, and place it into XDX.
	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, DR_REG_XDX,
			offsetof(ub_arraymap_list_node_t, next), DR_REG_XDX);

	// Jump to the beginning of the loop.
	opnd = opnd_create_instr(begin_label);
	instr = INSTR_CREATE_jmp(drcontext, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Insert done label at the end of code.
	instrlist_meta_preinsert(ilist, where, final_check_label);

	// Check if XDX needs to hold an available node.
	ub_instrum_check_null_false_case(drcontext, ilist, where, DR_REG_XDX,
			done_label);

	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, DR_REG_XAX,
	DR_REG_XDX);

	instrlist_meta_preinsert(ilist, where, done_label);
}

/**
 *  Checks whether the node stored in looked_node is present. In particular, it checks whether it is NULL and that an in-use flag is set.
 *
 *  looked_node -> lookup res (in) (preserved)
 *  scratch_reg -> scratch
 *  scratch_reg2 -> scratch2
 *
 */

void ub_arraymap_insert_lookup_check(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t* not_valid_opnd_label, reg_id_t looked_node,
		reg_id_t scratch_reg) {

    DR_ASSERT(false);

    instr_t *instr;

	ub_instrum_check_null_true_case(drcontext, ilist, where, looked_node,
			not_valid_opnd_label);

	// Next, we need to check the `use` flag.

	// Load to used flag

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, DR_REG_XDX,
			offsetof(ub_arraymap_list_node_t, used_flag), scratch_reg);

	// Check if use flag is already set to off (0)
	ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
			not_valid_opnd_label);
}

/**
 *  Inserts inline code that is responsible for removing an entry from the map.
 *
 *  map_reg -> map (in) (preserved)
 *  DR_REG_XDX -> scratch
 *  DR_REG_XAX -> scratch
 *  scratch_reg -> scratch
 *  scratch_reg2 -> scratch
 */
void ub_arraymap_insert_inline_map_remove(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t opnd_reg, reg_id_t map_reg,
		reg_id_t scratch_reg) {

    DR_ASSERT(false);

    opnd_t opnd, opnd2;
	instr_t *instr;

	instr_t *done_label = INSTR_CREATE_label(drcontext);

	// Lookup destination node.
	ub_arraymap_insert_lookup_entry(drcontext, ilist, where, opnd_reg, map_reg,
			scratch_reg);

	// Check lookup, and if no entry was found to be removed, simply jump to done label.
	ub_arraymap_insert_lookup_check(drcontext, ilist, where, done_label,
	DR_REG_XDX, scratch_reg);

	opnd = opnd_create_reg(scratch_reg);
	instr = INSTR_CREATE_xor(drcontext, opnd, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Set flag to 0, as it is no longer in use.
	opnd = opnd_create_reg(scratch_reg);
	opnd2 =
			OPND_CREATE_MEMPTR(DR_REG_XDX, offsetof(ub_arraymap_list_node_t, used_flag));
	instr = INSTR_CREATE_mov_st(drcontext, opnd2, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, scratch_reg,
	DR_REG_XDX, offsetof(ub_arraymap_list_node_t, used_flag));

	// insert done label at the end.
	instrlist_meta_preinsert(ilist, where, done_label);
}

void drarraymap_symb_insert_new_node(reg_id_t opnd_reg, reg_id_t map_reg) {

    // NYI - basic idea is here but not yet implemented. See two key arraymap!
    DR_ASSERT(false);

    void* drcontext = dr_get_current_drcontext();

	// Initialise machine context so that reg values may be retrieved.
	dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
	dr_get_mcontext(drcontext, &mcontext);

	// Fetch data from registers
	uintptr_t opnd;
	reg_get_value_ex(opnd_reg, &mcontext, (byte*) &opnd);

	ub_arraymap_map_t *map;
	reg_get_value_ex(map_reg, &mcontext, (byte*) &map);

	// Perform lookup.
	size_t index = ((size_t) opnd) % map->max_size;
	ub_arraymap_list_node_t **node = &(map->array_map[index]);

	ub_arraymap_list_node_t * new_node = NULL;

	// Get the tail of the list.
	while ((*node) != NULL) {

		/**
		 *  While we fetch the tail, we perform some checks.
		 *
		 *  These checks ensure that no available node or the same entry were in the list.
		 *
		 *  TODO: Keep track of tail, rather than iterating.
		 */
		DR_ASSERT((*node)->used_flag != 0);
		DR_ASSERT((*node)->key != opnd);

		// Try next node.
		node = &((*node)->next);
	}

	// Allocate the list node appropriately.

	new_node = ub_arraymap_create_list_node();

	// Initialise node.
	new_node->key = opnd;
	new_node->used_flag = (uintptr_t) true;
	new_node->next = NULL;
	*node = new_node;

	// Set XDX to the new node.
	reg_set_value(DR_REG_XDX, &mcontext, (reg_t) new_node);

	// Don't forget to update the mcontext, as otherwise our change to XDX won't be put to effect.
	dr_set_mcontext(drcontext, &mcontext);
}

/**
 *  Inline code that inserts an entry to a symb map.
 *
 *  DR_REG_XDX -> new node (out)
 *  DR_REG_XAX -> scratch
 *  map_reg -> map
 *  scratch_reg -> scratch
 *  scratch_reg2 -> scratch
 */
void ub_arraymap_insert_map_entry(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t opnd_reg, reg_id_t map_reg,
		reg_id_t scratch_reg) {

    DR_ASSERT(false);

	opnd_t opnd, opnd2;
	instr_t *instr;

	instr_t *done_label = INSTR_CREATE_label(drcontext);
	instr_t *use_available_label = INSTR_CREATE_label(drcontext);
	instr_t *allocate_label = INSTR_CREATE_label(drcontext);

	// Perform a lookup.

	ub_arraymap_insert_lookup_entry(drcontext, ilist, where, opnd_reg, map_reg,
			scratch_reg);

	// Check if lookup is NULL.
	ub_instrum_check_null_true_case(drcontext, ilist, where, DR_REG_XDX,
			allocate_label);

	/**
	 * If it is null, jump to allocate label.
	 * This means that no available node was found.
	 */

	// Set the key.
	ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, opnd_reg, DR_REG_XDX,
			offsetof(ub_arraymap_list_node_t, key));

	// Set in use

	opnd = opnd_create_reg(scratch_reg);
	instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) 1, opnd, ilist,
			where, NULL, NULL);

	ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, scratch_reg,
	DR_REG_XDX, offsetof(ub_arraymap_list_node_t, used_flag));

	// Jump to done.
	opnd = opnd_create_instr(done_label);
	instr = INSTR_CREATE_jmp(drcontext, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Create a new node.
	instrlist_meta_preinsert(ilist, where, allocate_label);

	/**
	 * We need to perform a clean call in order to insert new nodes to the bucket list.
	 * (We try to avoid this as much as possible).
	 */
	dr_insert_clean_call(drcontext, ilist, where,
			(void *) drarraymap_symb_insert_new_node, false, 2,
			OPND_CREATE_INTPTR(opnd_reg), OPND_CREATE_INTPTR(map_reg));

	instrlist_meta_preinsert(ilist, where, done_label);
}
