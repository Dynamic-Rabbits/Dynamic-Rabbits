/*
 * @author John F.X. Galea
 */

#include "ub_two_key_arraymap.h"
#include <string.h>
#include "../../instrumentation/ub_instrum_insert.h"

/***************************************************************************
 *  Structs and defintions
 */

#define MAX_SIZE 65536
#define DIFF_SIZE 8

typedef struct {
	ub_tk_arraymap_list_node_t **array_map;
} ub_tk_arraymap_map_t;

static unsigned int ref_count = 0;
static unsigned int *all_one_template = NULL;
static unsigned int *all_one_template_aligned = NULL;

static unsigned int *zero_template = NULL;
static unsigned int *zero_template_aligned = NULL;

/***************************************************************************
 *  Static Prototypes
 */

static ub_tk_arraymap_list_node_t *ub_tk_arraymap_create_list_node();
static ub_tk_arraymap_list_node_t *ub_tk_arraymap_lookup_node(
		ub_tk_arraymap_map_t *map, uintptr_t key1, uintptr_t key2);

/***************************************************************************
 *  Map Operations.
 */

DR_EXPORT void *ub_tk_arraymap_create_map() {

	if (ref_count == 0) {

		all_one_template = dr_global_alloc((sizeof(unsigned int) * 4) + 15);
		all_one_template_aligned = (void *) (((uintptr_t) all_one_template + 15)
				& ~(uintptr_t) 0x0F);
		memset(all_one_template_aligned, 0xFF, sizeof(unsigned int) * 4);

		zero_template = dr_global_alloc((sizeof(unsigned int) * 4) + 15);
		zero_template_aligned = (void *) (((uintptr_t) zero_template + 15)
				& ~(uintptr_t) 0x0F);
		memset(zero_template_aligned, 0, sizeof(unsigned int) * 4);
	}

	/* TODO: Racey */
	ref_count++;

	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) dr_global_alloc(
			sizeof(ub_tk_arraymap_map_t));

	if (map != NULL) {

		// Allocation of array map
		ub_tk_arraymap_list_node_t **array_map;
		array_map = (ub_tk_arraymap_list_node_t**) dr_global_alloc(
				sizeof(ub_tk_arraymap_list_node_t *) * MAX_SIZE);

		if (array_map != NULL) {

			// Populate the struct.
			map->array_map = array_map;

			//Initialise array-map entries
			memset(map->array_map, 0,
					sizeof(ub_tk_arraymap_list_node_t *) * MAX_SIZE);

			return (void *) map;
		}

		// Since allocation for array map failed, we deallocate the map structure before returning.
		dr_global_free(map, sizeof(ub_tk_arraymap_map_t));
	}

	return NULL;
}

DR_EXPORT void ub_tk_arraymap_destroy_map(void *map_opaque,
		ub_destroy_value_func_t detroy_func) {

	DR_ASSERT(map_opaque);

	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) map_opaque;

	// Iterate through the array map, and deallocate all data containers.
	size_t i;
	for (i = 0; i < MAX_SIZE; i++) {

		//dr_fprintf(STDERR, "Size: %d\n", i);
		ub_tk_arraymap_list_node_t *node = map->array_map[i];

		while (node != NULL) {

			// Iterate through list and clear.
			ub_tk_arraymap_list_node_t *freed_node = node;
			// Load next pointer.
			node = node->next;

			// Destroy value
			if (freed_node->used_flag && detroy_func)
				detroy_func(freed_node->value);

			// Destroy the struct
			dr_global_free(freed_node, sizeof(ub_tk_arraymap_list_node_t));
		}
	}

	dr_global_free(map->array_map,
			sizeof(ub_tk_arraymap_list_node_t *) * MAX_SIZE);
	dr_global_free(map, sizeof(ub_tk_arraymap_map_t));

	ref_count--;
	if (ref_count == 0) {
		dr_global_free(all_one_template, (sizeof(unsigned int) * 4) + 15);
		all_one_template = NULL;
		all_one_template_aligned = NULL;

		dr_global_free(zero_template, (sizeof(unsigned int) * 4) + 15);
		zero_template = NULL;
		zero_template_aligned = NULL;
	}
}

static size_t ub_tk_arraymap_get_index(ub_tk_arraymap_map_t *map, size_t key,
		size_t key2) {

	return ((key << DIFF_SIZE) + key2) & (MAX_SIZE - 1);
}

DR_EXPORT void* ub_tk_arraymap_insert_entry(void *map_opaque,
		ub_two_key_value_pair_t *key_val_pair) {

	DR_ASSERT(map_opaque);

	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) map_opaque;

	size_t index = ub_tk_arraymap_get_index(map, key_val_pair->key1,
			key_val_pair->key2);

	ub_tk_arraymap_list_node_t **node = &(map->array_map[index]);
	ub_tk_arraymap_list_node_t *available_node = NULL;

	while (*node != NULL) {

		// If node is unused, record it.
		if (available_node == NULL && (*node)->used_flag == false)
			available_node = *node;

		if (((*node)->used_flag == true) && key_val_pair->key1 == (*node)->key
				&& key_val_pair->key2 == (*node)->key2) {

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
		available_node = ub_tk_arraymap_create_list_node();

		if (available_node == NULL)
			return NULL;

		available_node->next = NULL;
		*node = available_node;
	}

	// Initialise node.
	available_node->key = key_val_pair->key1;
	available_node->key2 = key_val_pair->key2;
	available_node->value = key_val_pair->value;
	available_node->used_flag = true;

	return NULL;
}

/**
 * Creates and returns a new list node.
 *
 * @return A new list node
 */
static ub_tk_arraymap_list_node_t *ub_tk_arraymap_create_list_node() {

	ub_tk_arraymap_list_node_t *list_node = NULL;

	// Allocate the list_node with the proper allocator.

	list_node = (ub_tk_arraymap_list_node_t *) dr_global_alloc(
			sizeof(ub_tk_arraymap_list_node_t));

	if (list_node != NULL) {
		// Initialise the newly created node.
		memset(list_node, 0, sizeof(ub_tk_arraymap_list_node_t));
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
static ub_tk_arraymap_list_node_t *ub_tk_arraymap_lookup_node(
		ub_tk_arraymap_map_t *map, uintptr_t key1, uintptr_t key2) {

	size_t index = ub_tk_arraymap_get_index(map, key1, key2);

	ub_tk_arraymap_list_node_t *node = (map->array_map[index]);

	// Iterate through bucket list.
	while (node != NULL) {

		// Note it is important to check that the node is actually in use.
		if (node->used_flag == true && key1 == node->key && key2 == node->key2)
			return node;

		// Try next node.
		node = node->next;
	}

	// Failed to find a matching node.
	return NULL;
}

DR_EXPORT void *ub_tk_arraymap_lookup_entry(void *map_opaque, uintptr_t key1,
		uintptr_t key2) {

	ub_tk_arraymap_list_node_t * node = ub_tk_arraymap_lookup_node(map_opaque,
			key1, key2);

	if (node != NULL)
		return node->value;
	else
		return NULL;
}

DR_EXPORT void * ub_tk_arraymap_remove_entry(void *map_opaque, uintptr_t key1,
		uintptr_t key2) {

	ub_tk_arraymap_list_node_t *node = ub_tk_arraymap_lookup_node(map_opaque,
			key1, key2);

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

/***********************************************************************************************
 * Inline interface
 */

static void ub_tk_arraymap_insert_hash(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_reg, reg_id_t key_reg,
		reg_id_t key2_reg) {

	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, key_reg, result_reg);
	ub_instrum_shift_left(drcontext, ilist, where, result_reg, DIFF_SIZE);

	opnd_t opnd = opnd_create_reg(result_reg);
	opnd_t opnd2 = opnd_create_reg(key2_reg);
	instr_t *instr = INSTR_CREATE_add(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_instrum_and_immed(drcontext, ilist, where, result_reg, MAX_SIZE - 1);
}

static void ub_tk_arraymap_insert_simd_hash(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_vector_reg, reg_id_t key_vector_reg,
		reg_id_t key2_vector_reg, reg_id_t scratch_vector_reg,
		reg_id_t scratch_scaler_reg) {

//	ub_instrum_simd_mov_st_reg_to_reg_opnd(drcontext, ilist, where,
//			key_vector_reg, result_vector_reg);
//
//	/* Shift the keys */
//	opnd_t opnd = opnd_create_reg(result_vector_reg);
//	opnd_t opnd2 = opnd_create_immed_int(DIFF_SIZE, OPSZ_1);
//	instr_t *instr = INSTR_CREATE_pslld(drcontext, opnd, opnd2);
//	instrlist_meta_preinsert(ilist, where, instr);
//
//	opnd = opnd_create_reg(result_vector_reg);
//	opnd2 = opnd_create_reg(key2_vector_reg);
//	instr = INSTR_CREATE_paddd(drcontext, opnd, opnd2);
//	instrlist_meta_preinsert(ilist, where, instr);
//
//	ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, MAX_SIZE - 1,
//			scratch_scaler_reg);
//
//	opnd = opnd_create_reg(scratch_scaler_reg);
//	opnd2 = opnd_create_reg(scratch_vector_reg);
//	instr = INSTR_CREATE_movd(drcontext, opnd2, opnd);
//	instrlist_meta_preinsert(ilist, where, instr);
//
//	opnd_t imm_opnd = opnd_create_immed_uint(0, opnd_size_from_bytes(1));
//	opnd2 = opnd_create_reg(scratch_vector_reg);
//	instr = INSTR_CREATE_pshufd(drcontext, opnd2, opnd2, imm_opnd);
//	instrlist_meta_preinsert(ilist, where, instr);
//
//	opnd = opnd_create_reg(result_vector_reg);
//	opnd2 = opnd_create_reg(scratch_vector_reg);
//	instr = INSTR_CREATE_pand(drcontext, opnd, opnd2);
//	instrlist_meta_preinsert(ilist, where, instr);
}

static void ub_tk_arraymap_insert_simd_lookup_entry(void *map_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where,
		reg_id_t key_vector_reg, reg_id_t key2_vector_reg,
		reg_id_t scratch_vector_reg, reg_id_t scratch2_vector_reg,
		reg_id_t scratch_scaler_reg) {
//
//	DR_ASSERT(zero_template_aligned);
//
//	opnd_t opnd;
//	opnd_t opnd2;
//	opnd_t opnd3;
//	instr_t *instr;
//
//	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) map_opaque;
//
//	ub_tk_arraymap_insert_simd_hash(drcontext, ilist, where, scratch_vector_reg,
//			key_vector_reg, key2_vector_reg, scratch2_vector_reg,
//			scratch_scaler_reg);
//
//	/* Load the hash map */
//	opnd = instr_create_reg(scratch_scaler_reg);
//	instr = instrlist_insert_mov_immed_ptrsz(drcontext, map->array_map, opnd,
//			ilist, where, NULL, NULL);
//
//	/* Set all bits to 1 */
//	opnd = instr_create_reg(scratch2_vector_reg);
//	instr = INSTR_CREATE_pcmpeqd(drcontext, opnd, opnd);
//
//	/* Perform lookup */
//	opnd = instr_create_reg(scratch_vector_reg);
//	opnd2 = opnd_create_base_disp(scratch_scaler_reg, scratch_vector_reg, 4, 0,
//			OPSZ_1);
//	opnd3 = instr_create_reg(scratch2_vector_reg);
//	instr = INSTR_CREATE_vgatherdpd(drcontext, opnd, opnd2, opnd3);
//
//	/* Filter out those that are NULL */
//
//	instr_t* done_label = INSTR_CREATE_label(drcontext);
//	instr_t* iterate_label = INSTR_CREATE_label(drcontext);
//
//	instrlist_meta_preinsert(ilist, where, iterate_label);
//
//	// Create mask with pcmpeqd
//	ub_instrum_simd_mov_st_reg_to_reg_opnd(drcontext, ilist, where,
//			scratch_vector_reg, scratch2_vector_reg);
//
//	instr = INSTR_CREATE_pcmpeqd(drcontext,
//			opnd_create_reg(scratch2_vector_reg),
//			opnd_create_abs_addr(zero_template_aligned, OPSZ_16));
//	instrlist_meta_preinsert(ilist, where, instr);
//
//	/* We need to check that the keys for the null case are also zero.
//	 * Otherwise, we have a new bvect.
//	 */
//	instr = INSTR_CREATE_pxor(drcontext, opnd_create_reg(scratch2_vector_reg),
//			opnd_create_abs_addr(zero_template_aligned, OPSZ_16));
//	instrlist_meta_preinsert(ilist, where, instr);
//
//	opnd = instr_create_reg(scratch_vector_reg);
//	opnd2 = opnd_create_base_disp(DR_REG_NULL, scratch_vector_reg, 4, 0,
//			OPSZ_1);
//	opnd3 = instr_create_reg(scratch2_vector_reg);
//	instr = INSTR_CREATE_vgatherdpd(drcontext, opnd, opnd2, opnd3);
//
//	instrlist_meta_preinsert(ilist, where, done_label);
}

static void ub_tk_arraymap_insert_lookup_entry(void *map_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t key_reg,
		reg_id_t key2_reg, reg_id_t found_reg, reg_id_t available_reg) {

	opnd_t opnd;
	opnd_t opnd2;
	instr_t *instr;

	bool prepare_available = available_reg != DR_REG_NULL;

	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) map_opaque;

	/** Get hash */
	ub_tk_arraymap_insert_hash(drcontext, ilist, where, found_reg, key_reg,
			key2_reg);

	/** Hard code load the array map **/

	opnd = opnd_create_base_disp(DR_REG_NULL, found_reg,
			sizeof(ub_tk_arraymap_list_node_t *),
			(int) (intptr_t) map->array_map, OPSZ_PTR);
	opnd2 = opnd_create_reg(found_reg);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd2, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Clear scratch (now considered the available node).
	if (prepare_available)
		ub_instrum_clear_reg(drcontext, ilist, where, available_reg);

	// Initialise needed labels to iterate over bucket list.
	instr_t* begin_label = INSTR_CREATE_label(drcontext);
	instr_t* done_label = INSTR_CREATE_label(drcontext);
	instr_t* iterate_label = INSTR_CREATE_label(drcontext);
	instr_t* available_label = NULL;

	if (prepare_available)
		available_label = INSTR_CREATE_label(drcontext);

	// Insert iteration label of loop.
	instrlist_meta_preinsert(ilist, where, begin_label);

	// Check whether the head of the bucket list is null

	ub_instrum_check_null_true_case(drcontext, ilist, where, found_reg,
			done_label);

	/* Otherwise, check if the node is in use. */
	opnd_t live_flag_opnd =
			OPND_CREATE_MEMPTR(found_reg, offsetof(ub_tk_arraymap_list_node_t, used_flag));
	ub_instrum_check_mem_null_true_case(drcontext, ilist, where, NULL,
			&live_flag_opnd,
			prepare_available ? available_label : iterate_label);

	/* Check first key */
	opnd_t key_opnd =
	OPND_CREATE_MEMPTR(found_reg, offsetof(ub_tk_arraymap_list_node_t, key));
	opnd = opnd_create_reg(key_reg);
	instr = INSTR_CREATE_cmp(drcontext, opnd, key_opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_instr(iterate_label);
	instr = INSTR_CREATE_jcc(drcontext, OP_jne, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	/* Check second key */
	key_opnd =
	OPND_CREATE_MEMPTR(found_reg, offsetof(ub_tk_arraymap_list_node_t, key2));
	opnd = opnd_create_reg(key2_reg);
	instr = INSTR_CREATE_cmp(drcontext, opnd, key_opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_instr(done_label);
	instr = INSTR_CREATE_jcc(drcontext, OP_je, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Insert available label.

	if (prepare_available) {

		opnd = opnd_create_instr(iterate_label);
		instr = INSTR_CREATE_jmp(drcontext, opnd);
		instrlist_meta_preinsert(ilist, where, instr);

		instrlist_meta_preinsert(ilist, where, available_label);

		ub_instrum_check_null_false_case(drcontext, ilist, where, available_reg,
				iterate_label);

		ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, found_reg,
				available_reg);
	}

	// Insert the iterate label to move to the next node.
	instrlist_meta_preinsert(ilist, where, iterate_label);

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, found_reg,
			offsetof(ub_tk_arraymap_list_node_t, next), found_reg);

	// Jump to the beginning of the loop.
	opnd = opnd_create_instr(begin_label);
	instr = INSTR_CREATE_jmp(drcontext, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	// Insert done label at the end of code.
	instrlist_meta_preinsert(ilist, where, done_label);
}

DR_EXPORT void ub_tk_arraymap_insert_lookup(void *map_opaque, void *drcontext,
		instrlist_t *ilist, instr_t *where, reg_id_t key_reg, reg_id_t key2_reg,
		reg_id_t found_reg) {

	instr_t* done_label = INSTR_CREATE_label(drcontext);

	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) map_opaque;

	ub_tk_arraymap_insert_lookup_entry(map, drcontext, ilist, where, key_reg,
			key2_reg, found_reg, DR_REG_NULL);

	ub_instrum_check_null_true_case(drcontext, ilist, where, found_reg,
			done_label);

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, found_reg,
			offsetof(ub_tk_arraymap_list_node_t, value), found_reg);

	instrlist_meta_preinsert(ilist, where, done_label);
}

DR_EXPORT void ub_tk_arraymap_insert_inline_map_remove(void *map_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t key_reg,
		reg_id_t key2_reg, reg_id_t scratch_reg) {

	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) map_opaque;

	instr_t *done_label = INSTR_CREATE_label(drcontext);

	// Lookup destination node.
	ub_tk_arraymap_insert_lookup_entry(map, drcontext, ilist, where, key_reg,
			key2_reg, scratch_reg, DR_REG_NULL);

	ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg,
			done_label);

	// Set flag to 0, as it is no longer in use.
	ub_instrum_clear_mem(drcontext, ilist, where, scratch_reg,
			offsetof(ub_tk_arraymap_list_node_t, used_flag));

	// insert done label at the end.
	instrlist_meta_preinsert(ilist, where, done_label);
}

static void ub_tk_arraymap_cc_create(ub_tk_arraymap_map_t *map, size_t key1,
		size_t key2, reg_id_t dst_reg) {

	DR_ASSERT(map);

	void* drcontext = dr_get_current_drcontext();

	// Initialise machine context so that reg values may be retrieved.
	dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
	dr_get_mcontext(drcontext, &mcontext);

	// Perform lookup.
	size_t index = ub_tk_arraymap_get_index(map, key1, key2);
	ub_tk_arraymap_list_node_t **node = &(map->array_map[index]);

	ub_tk_arraymap_list_node_t * new_node = NULL;

	// Get the tail of the list.
	while ((*node) != NULL) {

		DR_ASSERT((*node)->used_flag != 0);
		DR_ASSERT((*node)->key != key1);
		DR_ASSERT((*node)->key2 != key2);

		// Try next node.
		node = &((*node)->next);
	}

	// Allocate the list node appropriately.

	new_node = ub_tk_arraymap_create_list_node();

	// Initialise node.
	new_node->key = key1;
	new_node->key2 = key2;

	new_node->used_flag = (uintptr_t) true;
	new_node->next = NULL;
	*node = new_node;

	reg_set_value(dst_reg, &mcontext, (reg_t) new_node);

	// Don't forget to update the mcontext, as otherwise our change won't be put to effect.
	dr_set_mcontext(drcontext, &mcontext);
}

DR_EXPORT opnd_t ub_tk_arraymap_get_val_opnd(reg_id_t entry_reg) {

	return OPND_CREATE_MEMPTR(entry_reg,
			offsetof(ub_tk_arraymap_list_node_t, value));
}

DR_EXPORT void ub_tk_arraymap_insert_map_entry(void *map_opaque,
		void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t key_reg,
		reg_id_t key2_reg, reg_id_t new_node_reg, reg_id_t scratch_reg2) {

	ub_tk_arraymap_map_t *map = (ub_tk_arraymap_map_t *) map_opaque;

	opnd_t opnd;
	instr_t *instr;

	instr_t *done_label = INSTR_CREATE_label(drcontext);
	instr_t *allocate_label = INSTR_CREATE_label(drcontext);

	// Perform a lookup.
	ub_tk_arraymap_insert_lookup_entry(map_opaque, drcontext, ilist, where,
			key_reg, key2_reg, new_node_reg, scratch_reg2);

	// Check if lookup is NULL. If not null, we already have an entry!
	ub_instrum_check_null_false_case(drcontext, ilist, where, new_node_reg,
			done_label);

	/**
	 * If it is null, jump to allocate label.
	 * This means that no available node was found.
	 */
	ub_instrum_check_null_true_case(drcontext, ilist, where, scratch_reg2,
			allocate_label);

	// Set the key.
	ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, key_reg, scratch_reg2,
			offsetof(ub_tk_arraymap_list_node_t, key));

	ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where, key2_reg,
			scratch_reg2, offsetof(ub_tk_arraymap_list_node_t, key2));

	// Set in use
	opnd = OPND_CREATE_MEMPTR(scratch_reg2,
			offsetof(ub_tk_arraymap_list_node_t, used_flag));
	instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) true, opnd, ilist,
			where, NULL, NULL);

	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, scratch_reg2,
			new_node_reg);

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
	dr_insert_clean_call(drcontext, ilist, where, ub_tk_arraymap_cc_create,
	false, 4, OPND_CREATE_INTPTR(map), opnd_create_reg(key_reg),
			opnd_create_reg(key2_reg), OPND_CREATE_INTPTR(new_node_reg));

	instrlist_meta_preinsert(ilist, where, done_label);
}
