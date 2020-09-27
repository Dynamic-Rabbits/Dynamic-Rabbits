/*
 * ub_tk_lp_hashmap.c
 *
 *      Author: john
 */

#include "ub_tk_lp_hashmap.h"
#include <string.h>
#include "../../instrumentation/ub_instrum_insert.h"

#define STARTING_SIZE 4
#define PROBING_THRESHOLD 5
#define DIFF_SIZE 8

typedef struct {
	uint32_t size;
	uint32_t hash_base;
	uint32_t power_size;
	void **key1_store;
	void **key2_store;
	void **value_store;
} ub_tk_lp_map_t;

static void ub_tk_lp_map_free(ub_tk_lp_map_t *map) {

	dr_global_free(map->key1_store, sizeof(void *) * map->size);
	dr_global_free(map->key2_store, sizeof(void *) * map->size);
	dr_global_free(map->value_store, sizeof(void *) * map->size);
}

static void ub_tk_lp_map_init(ub_tk_lp_map_t *map, size_t power_size) {

	map->size = 1 << power_size;
	map->hash_base = map->size - 1;
	map->power_size = power_size;

	map->key1_store = (void **) dr_global_alloc(sizeof(void *) * map->size);
	memset(map->key1_store, 0, sizeof(void *) * map->size);

	map->key2_store = (void **) dr_global_alloc(sizeof(void *) * map->size);
	memset(map->key2_store, 0, sizeof(void *) * map->size);

	map->value_store = (void **) dr_global_alloc(sizeof(void *) * map->size);
	memset(map->value_store, 0, sizeof(void *) * map->size);
}

DR_EXPORT void *ub_tk_lp_hashmap_create() {

	ub_tk_lp_map_t *map = (ub_tk_lp_map_t *) dr_global_alloc(
			sizeof(ub_tk_lp_map_t));
	ub_tk_lp_map_init(map, STARTING_SIZE);

	return map;
}

DR_EXPORT void ub_tk_lp_hashmap_destroy(void *map_opaque,
		ub_destroy_value_func_t detroy_func) {

	ub_tk_lp_map_t *map = (ub_tk_lp_map_t *) map_opaque;

	if (detroy_func) {
		size_t i;
		for (i = 0; i < map->size; i++) {

			void *value = map->value_store[i];
			if (value != NULL)
				detroy_func(value);
		}
	}

	ub_tk_lp_map_free(map);
	dr_global_free(map, sizeof(ub_tk_lp_map_t));
}

static size_t ub_tk_lp_map_hash(ub_tk_lp_map_t *map, size_t key, size_t key2) {

	return ((key << DIFF_SIZE) + key2) & map->hash_base;
}

static bool ub_tk_lp_map_insert(ub_tk_lp_map_t *map,
		ub_two_key_value_pair_t *key_val_pair, void **old_val) {

	DR_ASSERT(key_val_pair != NULL);
	DR_ASSERT(key_val_pair->key1 != 0);
	DR_ASSERT(key_val_pair->key2 != 0);
	DR_ASSERT(key_val_pair->value != 0);

	if (old_val != NULL)
		*old_val = NULL;

	uint index = ub_tk_lp_map_hash(map, key_val_pair->key1, key_val_pair->key2);

	uint probe = 0;

	while (index < map->size
			&& !(map->key1_store[index] == NULL
					&& map->key2_store[index] == NULL)
			&& !(map->key1_store[index] == (void *) key_val_pair->key1
					&& map->key2_store[index] == (void *) key_val_pair->key2)
			&& probe < PROBING_THRESHOLD) {
		index++;
		probe++;
	}

	if (index >= map->size || probe >= PROBING_THRESHOLD) {
		return false;

	} else if (map->key1_store[index] == NULL && map->key2_store[index] == NULL) {

		DR_ASSERT(index < map->size);
		DR_ASSERT(map->value_store[index] == NULL);

		map->key1_store[index] = (void *) key_val_pair->key1;
		map->key2_store[index] = (void *) key_val_pair->key2;
		map->value_store[index] = key_val_pair->value;
		return true;

	} else if (map->key1_store[index] == (void *) key_val_pair->key1
			&& map->key2_store[index] == (void *) key_val_pair->key2) {

		DR_ASSERT(index < map->size);

		if (old_val != NULL)
			*old_val = map->value_store[index];

		map->value_store[index] = key_val_pair->value;
		return true;

	} else {
		DR_ASSERT(false); /* Unreachable */
	}

	/* Should never reach here */
	return false;
}

static bool ub_tk_lp_map_switch_maps(ub_tk_lp_map_t *src_map,
		ub_tk_lp_map_t *dst_map) {

	bool successful_switch = true;

	ub_two_key_value_pair_t key_val_pair;

	size_t i;
	for (i = 0; i < src_map->size; i++) {

		void *key1 = src_map->key1_store[i];
		void *key2 = src_map->key2_store[i];

		if (key1 != NULL && key2 != NULL) {

			void *value = src_map->value_store[i];
			DR_ASSERT(value != NULL);

			key_val_pair.key1 = (uintptr_t) key1;
			key_val_pair.key2 = (uintptr_t) key2;
			key_val_pair.value = value;

			void * old_val = NULL;
			bool succ = ub_tk_lp_map_insert(dst_map, &key_val_pair, &old_val);

			if (succ) {
				DR_ASSERT(old_val == NULL);
			} else {
				successful_switch = false;
				break;
			}
		}
	}

	return successful_switch;
}

static void ub_tk_lp_map_increase_size(ub_tk_lp_map_t *map) {

	size_t new_power_size = map->power_size;
	ub_tk_lp_map_t new_map;

	bool succ = false;

	do {
		new_power_size++;
		ub_tk_lp_map_init(&new_map, new_power_size);
		succ = ub_tk_lp_map_switch_maps(map, &new_map);

		if (!succ)
			ub_tk_lp_map_free(&new_map);

	} while (!succ);

	ub_tk_lp_map_free(map);

	memcpy(map, &new_map, sizeof(ub_tk_lp_map_t));
}

DR_EXPORT void* ub_tk_lp_hashmap_insert_entry(void *map_opaque,
		ub_two_key_value_pair_t *two_key_val_pair) {

	void *old_val = NULL;

	ub_tk_lp_map_t *map = (ub_tk_lp_map_t *) map_opaque;

	bool success = ub_tk_lp_map_insert(map, two_key_val_pair, &old_val);

	while (!success) {
		ub_tk_lp_map_increase_size(map);
		success = ub_tk_lp_map_insert(map, two_key_val_pair, &old_val);
	}

	return old_val;
}

DR_EXPORT void *ub_tk_lp_hashmap_lookup_entry(void *map_opaque, uintptr_t key1,
		uintptr_t key2) {

	DR_ASSERT(key1 != 0);
	DR_ASSERT(key2 != 0);

	ub_tk_lp_map_t *map = (ub_tk_lp_map_t *) map_opaque;

	uint index = ub_tk_lp_map_hash(map, key1, key2);
	uint probe = 0;

	while (index < map->size
			&& !(map->key1_store[index] == NULL
					&& map->key2_store[index] == NULL)
			&& !(map->key1_store[index] == (void *) key1
					&& map->key2_store[index] == (void *) key2)
			&& probe < PROBING_THRESHOLD) {

		index++;
		probe++;
	}

	if (index < map->size && map->key1_store[index] == (void *) key1
			&& map->key2_store[index] == (void *) key2) {
		void *value = map->value_store[index];
		DR_ASSERT(value != NULL);
		return value;
	}

	return NULL;
}

DR_EXPORT bool ub_tk_lp_hashmap_remove_entry(void *map_opaque, uintptr_t key1,
		uintptr_t key2, void **old_val) {

	DR_ASSERT(key1 != 0);
	DR_ASSERT(key2 != 0);

	/**
	 * Note: we can't just set the entry to NULL, because that will
	 * break the link with other collided keys further up the
	 * probe.
	 */

	ub_tk_lp_map_t *map = (ub_tk_lp_map_t *) map_opaque;

	uint hash = ub_tk_lp_map_hash(map, key1, key2);
	uint index = hash;
	uint probe = 0;

	if (old_val != NULL)
		*old_val = NULL;

	while (index < map->size
			&& !(map->key1_store[index] == NULL
					&& map->key2_store[index] == NULL)
			&& !(map->key1_store[index] == (void *) key1
					&& map->key2_store[index] == (void *) key2)
			&& probe < PROBING_THRESHOLD) {
		index++;
		probe++;
	}

	if (index < map->size && map->key1_store[index] == (void *) key1
			&& map->key2_store[index] == (void *) key2) {

		if (old_val != NULL)
			*old_val = map->value_store[index];

		map->key1_store[index] = NULL;
		map->key2_store[index] = NULL;
		map->value_store[index] = NULL;
		uint pre_index = index;

		while (index + 1 < map->size && probe < PROBING_THRESHOLD) {
			index++;
			probe++;

			void *next_key1 = map->key1_store[index];
			void *next_key2 = map->key2_store[index];

			if (next_key1 == NULL || next_key2 == NULL)
				break;
			else if (hash
					== ub_tk_lp_map_hash(map, (size_t) (uintptr_t) next_key1,
							(size_t) (uintptr_t) next_key2)) {

				map->key1_store[pre_index] = map->key1_store[index];
				map->key2_store[pre_index] = map->key2_store[index];
				map->value_store[pre_index] = map->value_store[index];

				map->key1_store[index] = NULL;
				map->key2_store[index] = NULL;
				map->value_store[index] = NULL;
				pre_index = index;
			}
		}
		return true;
	}

	return false;
}

/**************************************************************************
 * Inline interface.
 */

static void ub_tk_lp_hashmap_insert_hash(ub_tk_lp_map_t *map, void *drcontext,
		instrlist_t *ilist, instr_t *where, reg_id_t result_reg,
		reg_id_t key_reg, reg_id_t key2_reg) {

	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, key_reg, result_reg);
	ub_instrum_shift_left(drcontext, ilist, where, result_reg, DIFF_SIZE);

	opnd_t opnd = opnd_create_reg(result_reg);
	opnd_t opnd2 = opnd_create_reg(key2_reg);
	instr_t *instr = INSTR_CREATE_add(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_reg(result_reg);
	opnd2 = opnd_create_abs_addr(&(map->hash_base), OPSZ_4);
	instr = INSTR_CREATE_and(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);
}

void ub_tk_lp_hashmap_insert_lookup_entry(void *map_opaque, void *drcontext,
		instrlist_t *ilist, instr_t *where, reg_id_t result_reg,
		reg_id_t key_reg, reg_id_t key2_reg, reg_id_t scratch_reg) {

	DR_ASSERT(map_opaque != NULL);

	ub_tk_lp_map_t *map = (ub_tk_lp_map_t *) map_opaque;

	opnd_t opnd;
	instr_t *instr;

	instr_t *done_label = INSTR_CREATE_label(drcontext);
	instr_t *found_label = INSTR_CREATE_label(drcontext);

	/* Get index via hash */
	ub_tk_lp_hashmap_insert_hash(map, drcontext, ilist, where, scratch_reg,
			key_reg, key2_reg);

	for (int i = 0; i < PROBING_THRESHOLD; i++) {

		instr_t *not_found_label = INSTR_CREATE_label(drcontext);

		/* Load key store */
		opnd = opnd_create_abs_addr(&(map->key1_store), OPSZ_4);
		ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &opnd,
				result_reg);

		/* Compare with passed key */
		opnd = opnd_create_base_disp(result_reg, scratch_reg, sizeof(void *), 0,
		OPSZ_PTR);
		instr = INSTR_CREATE_cmp(drcontext, opnd, opnd_create_reg(key_reg));
		instrlist_meta_preinsert(ilist, where, instr);

		/* If key found, jmp */
		instr = INSTR_CREATE_jcc(drcontext, OP_jnz,
				opnd_create_instr(not_found_label));
		instrlist_meta_preinsert(ilist, where, instr);

		/* Load key 2 store */
		opnd = opnd_create_abs_addr(&(map->key2_store), OPSZ_4);
		ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &opnd,
				result_reg);

		/* Compare with passed key */
		opnd = opnd_create_base_disp(result_reg, scratch_reg, sizeof(void *), 0,
		OPSZ_PTR);
		instr = INSTR_CREATE_cmp(drcontext, opnd, opnd_create_reg(key2_reg));
		instrlist_meta_preinsert(ilist, where, instr);

		instr = INSTR_CREATE_jcc(drcontext, OP_jz,
				opnd_create_instr(found_label));
		instrlist_meta_preinsert(ilist, where, instr);

		instrlist_meta_preinsert(ilist, where, not_found_label);

		/* Increment the index for linear probe */
		ub_instrum_add_reg_immed(drcontext, ilist, where, scratch_reg,
				sizeof(void *));

		/* Clear the result label */
		ub_instrum_clear_reg(drcontext, ilist, where, result_reg);

		if (i != PROBING_THRESHOLD - 1) {
			/* Check out of bounds */
			opnd = opnd_create_abs_addr(&(map->size), OPSZ_4);
			instr = INSTR_CREATE_cmp(drcontext, opnd,
					opnd_create_reg(scratch_reg));
			instrlist_meta_preinsert(ilist, where, instr);

			/* Jump to done if out of bounds */
			instr = INSTR_CREATE_jcc(drcontext, OP_jl,
					opnd_create_instr(done_label));
			instrlist_meta_preinsert(ilist, where, instr);
		}
	}

	/* Finished probing, jump to done label */
	instr = INSTR_CREATE_jmp(drcontext, opnd_create_instr(done_label));
	instrlist_meta_preinsert(ilist, where, instr);

	instrlist_meta_preinsert(ilist, where, found_label);

	/* Load value store */
	opnd = opnd_create_abs_addr(&(map->value_store), OPSZ_4);
	ub_instrum_mov_ld_mem_opnd_to_reg(drcontext, ilist, where, &opnd,
			result_reg);

	/* Load the value into result register */
	opnd = opnd_create_base_disp(result_reg, scratch_reg, sizeof(void *), 0,
	OPSZ_PTR);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(result_reg), opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	/* Exit */
	instrlist_meta_preinsert(ilist, where, done_label);
}
