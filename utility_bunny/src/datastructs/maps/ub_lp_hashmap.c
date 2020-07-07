/*
 * ub_linear_probing_map.c
 *
 *      Author: john
 */

#include "ub_lp_hashmap.h"
#include "string.h"
#include "../../instrumentation/ub_instrum_insert.h"

#define STARTING_SIZE 4
#define PROBING_THRESHOLD 5

typedef struct {
	size_t size;
	size_t hash_base;
	size_t power_size;
	void **key_store;
	void **value_store;
} ub_lp_map_t;

static void ub_lp_map_free(ub_lp_map_t *map) {

	dr_global_free(map->key_store, sizeof(void *) * map->size);
	dr_global_free(map->value_store, sizeof(void *) * map->size);
}

static void ub_lp_map_init(ub_lp_map_t *map, size_t power_size) {

	map->size = 1 << power_size;
	map->hash_base = map->size - 1;
	map->power_size = power_size;

	map->key_store = (void **) dr_global_alloc(sizeof(void *) * map->size);
	memset(map->key_store, 0, sizeof(void *) * map->size);

	map->value_store = (void **) dr_global_alloc(sizeof(void *) * map->size);
	memset(map->value_store, 0, sizeof(void *) * map->size);
}

DR_EXPORT void *ub_lp_map_create() {

	ub_lp_map_t *map = (ub_lp_map_t *) dr_global_alloc(sizeof(ub_lp_map_t));
	ub_lp_map_init(map, STARTING_SIZE);

	return map;
}

DR_EXPORT void ub_lp_map_destroy(void *map_opaque,
		ub_destroy_value_func_t detroy_func) {

	ub_lp_map_t *map = (ub_lp_map_t *) map_opaque;

	if (detroy_func) {
		size_t i;
		for (i = 0; i < map->size; i++) {

			void *value = map->value_store[i];
			if (value != NULL)
				detroy_func(value);
		}
	}

	ub_lp_map_free(map);
	dr_global_free(map, sizeof(ub_lp_map_t));
}

static uint ub_lp_map_hash(ub_lp_map_t *map, void *key) {

	/* Simple and hash assuming size is a power of 2 */
	return ((uintptr_t) key) & (map->size - 1);
}

static bool ub_lp_map_insert(ub_lp_map_t *map,
		ub_key_value_pair_t *key_val_pair, void **old_val) {

	DR_ASSERT(key_val_pair != NULL);
	DR_ASSERT(key_val_pair->key != 0);
	DR_ASSERT(key_val_pair->value != 0);

	if (old_val != NULL)
		*old_val = NULL;

	uint index = ub_lp_map_hash(map, (void *) key_val_pair->key);
	uint probe = 0;

	while (index < map->size && map->key_store[index] != NULL
			&& map->key_store[index] != (void *) key_val_pair->key
			&& probe < PROBING_THRESHOLD) {
		index++;
		probe++;
	}

	if (index >= map->size || probe >= PROBING_THRESHOLD) {

		for (int i = probe; i > 0; i--) {

			DR_ASSERT(map->key_store[index -i ] != NULL);
		}

		return false;

	} else if (map->key_store[index] == NULL) {

		DR_ASSERT(index < map->size);
		DR_ASSERT(map->value_store[index] == NULL);

		map->key_store[index] = (void *) key_val_pair->key;
		map->value_store[index] = key_val_pair->value;
		return true;

	} else if (map->key_store[index] == (void *) key_val_pair->key) {
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

static bool ub_lp_map_switch_maps(ub_lp_map_t *src_map, ub_lp_map_t *dst_map) {

	bool successful_switch = true;

	ub_key_value_pair_t key_val_pair;

	size_t i;
	for (i = 0; i < src_map->size; i++) {

		void *key = src_map->key_store[i];
		if (key != NULL) {

			void *value = src_map->value_store[i];
			DR_ASSERT(value != NULL);

			key_val_pair.key = (uintptr_t) key;
			key_val_pair.value = value;

			void * old_val = NULL;
			bool succ = ub_lp_map_insert(dst_map, &key_val_pair, &old_val);

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

static void ub_lp_map_increase_size(ub_lp_map_t *map) {

	size_t new_power_size = map->power_size;
	ub_lp_map_t new_map;

	bool succ = false;

	do {
		new_power_size++;
		ub_lp_map_init(&new_map, new_power_size);
		succ = ub_lp_map_switch_maps(map, &new_map);

		if (!succ)
			ub_lp_map_free(&new_map);

	} while (!succ);

	ub_lp_map_free(map);

	memcpy(map, &new_map, sizeof(ub_lp_map_t));
}

DR_EXPORT void* ub_lp_map_insert_entry(void *map_opaque,
		ub_key_value_pair_t *key_val_pair) {

	void *old_val = NULL;

	ub_lp_map_t *map = (ub_lp_map_t *) map_opaque;

	bool success = ub_lp_map_insert(map, key_val_pair, &old_val);

	while (!success) {

		ub_lp_map_increase_size(map);
		success = ub_lp_map_insert(map, key_val_pair, &old_val);
	}

	return old_val;
}

DR_EXPORT void* ub_lp_map_lookup_entry(void *map_opaque, void *key) {

	DR_ASSERT(key != NULL);

	ub_lp_map_t *map = (ub_lp_map_t *) map_opaque;

	uint index = ub_lp_map_hash(map, key);
	uint probe = 0;

	while (index < map->size && map->key_store[index] != key
			&& probe < PROBING_THRESHOLD) {
		index++;
		probe++;
	}

	if (index < map->size && map->key_store[index] == key) {
		void *value = map->value_store[index];
		DR_ASSERT(value != NULL);
		return value;
	}

	return NULL;
}

DR_EXPORT bool ub_lp_map_remove(void *map_opaque, void *key, void **old_val) {

	DR_ASSERT(key != NULL);

	/**
	 * Note: we can't just set the entry to NULL, because that will
	 * break the link with other collided keys further up the
	 * probe.
	 */

	ub_lp_map_t *map = (ub_lp_map_t *) map_opaque;

	uint hash = ub_lp_map_hash(map, key);
	uint index = hash;
	uint probe = 0;

	if (old_val != NULL)
		*old_val = NULL;

	while (index < map->size && map->key_store[index] != key
			&& probe < PROBING_THRESHOLD) {
		index++;
		probe++;
	}

	if (index < map->size && map->key_store[index] == key) {

		if (old_val != NULL)
			*old_val = map->value_store[index];

		map->key_store[index] = NULL;
		map->value_store[index] = NULL;
		uint pre_index = index;

		while (index + 1 < map->size && probe < PROBING_THRESHOLD) {
			index++;
			probe++;

			void *next_key = map->key_store[index];

			if (next_key == NULL)
				break;
			else if (hash == ub_lp_map_hash(map, next_key)) {

				map->key_store[pre_index] = map->key_store[index];
				map->value_store[pre_index] = map->value_store[index];

				map->key_store[index] = NULL;
				map->value_store[index] = NULL;
				pre_index = index;
			}
		}
		return true;
	}

	return false;
}

static void ub_lp_hashmap_insert_hash(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_reg, reg_id_t key_reg, reg_id_t map_reg) {

	opnd_t opnd;
	instr_t *instr;

	opnd = opnd_create_reg(result_reg);
	instr = INSTR_CREATE_mov_st(drcontext, opnd, opnd_create_reg(key_reg));
	instrlist_meta_preinsert(ilist, where, instr);

	instr = INSTR_CREATE_and(drcontext, opnd,
			OPND_CREATE_MEMPTR(map_reg, offsetof(ub_lp_map_t, hash_base)));
	instrlist_meta_preinsert(ilist, where, instr);
}

static void ub_lp_hashmap_insert_simd_hash(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_vector_reg, reg_id_t key_vector_reg,
		reg_id_t map_reg) {

	opnd_t opnd, opnd2;
	instr_t *instr;

	opnd = OPND_CREATE_MEMPTR(map_reg, offsetof(ub_lp_map_t, hash_base));
	opnd2 = opnd_create_reg(result_vector_reg);
	instr = INSTR_CREATE_movd(drcontext, opnd2, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd_t imm_opnd = opnd_create_immed_uint(0, opnd_size_from_bytes(1));
	opnd2 = opnd_create_reg(result_vector_reg);
	instr = INSTR_CREATE_pshufd(drcontext, opnd2, opnd2, imm_opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_reg(key_vector_reg);
	opnd2 = opnd_create_reg(result_vector_reg);
	instr = INSTR_CREATE_pand(drcontext, opnd2, opnd);
	instrlist_meta_preinsert(ilist, where, instr);
}

void ub_lp_hashmap_insert_lookup_entry_ex(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_reg, reg_id_t key_reg, reg_id_t map_reg,
		reg_id_t scratch_reg, bool check_map) {

	opnd_t opnd;
	instr_t *instr;

	instr_t *done_label = INSTR_CREATE_label(drcontext);
	instr_t *found_label = INSTR_CREATE_label(drcontext);

	if (check_map) {

		ub_instrum_clear_reg(drcontext, ilist, where, result_reg);

		ub_instrum_check_null_true_case(drcontext, ilist, where, map_reg,
				done_label);
	}

	/* Get index via hash */
	ub_lp_hashmap_insert_hash(drcontext, ilist, where, scratch_reg, key_reg,
			map_reg);

	for (int i = 0; i < PROBING_THRESHOLD; i++) {

		/* Load key store */
		ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, map_reg,
				offsetof(ub_lp_map_t, key_store), result_reg);

		/* Compare with passed key */
		opnd = opnd_create_base_disp(result_reg, scratch_reg, sizeof(void *), 0,
		OPSZ_PTR);
		instr = INSTR_CREATE_cmp(drcontext, opnd, opnd_create_reg(key_reg));
		instrlist_meta_preinsert(ilist, where, instr);

		/* If key found, jmp */
		instr = INSTR_CREATE_jcc(drcontext, OP_jz,
				opnd_create_instr(found_label));
		instrlist_meta_preinsert(ilist, where, instr);

		/* Increment the index for linear probe */
		ub_instrum_add_reg_immed(drcontext, ilist, where, scratch_reg,
				sizeof(void *));

		/* Clear the result label */
		ub_instrum_clear_reg(drcontext, ilist, where, result_reg);

		if (i != PROBING_THRESHOLD - 1) {
			/* Check out of bounds */
			opnd = OPND_CREATE_MEMPTR(map_reg, offsetof(ub_lp_map_t, size));
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
	instr = INSTR_CREATE_jcc(drcontext, OP_jmp, opnd_create_instr(done_label));
	instrlist_meta_preinsert(ilist, where, instr);

	instrlist_meta_preinsert(ilist, where, found_label);

	/* Load value store */
	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, map_reg,
			offsetof(ub_lp_map_t, value_store), result_reg);

	/* Load the value into result reg */
	opnd = opnd_create_base_disp(result_reg, scratch_reg, sizeof(void *), 0,
	OPSZ_PTR);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(result_reg), opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	/* Exit */
	instrlist_meta_preinsert(ilist, where, done_label);
}

void ub_lp_hashmap_insert_lookup_entry(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_reg, reg_id_t key_reg, reg_id_t map_reg,
		reg_id_t scratch_reg) {

	ub_lp_hashmap_insert_lookup_entry_ex(drcontext, ilist, where, result_reg,
			key_reg, map_reg, scratch_reg, false);
}

void ub_lp_hashmap_insert_simd_lookup_entry(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t result_vector_reg, reg_id_t key_vector_reg,
		reg_id_t map_reg, reg_id_t scratch_reg, reg_id_t scratch_vector_reg,
		reg_id_t scratch_vector_reg2) {

	opnd_t opnd;
	opnd_t opnd2;
	opnd_t opnd3;
	instr_t *instr;

	instr_t *done_label = INSTR_CREATE_label(drcontext);
	instr_t *found_label = INSTR_CREATE_label(drcontext);

	/* Create a mask for keys which are not NULL */
	ub_instrum_simd_clear_reg(drcontext, ilist, where, result_vector_reg);

	ub_instrum_simd_clear_reg(drcontext, ilist, where, scratch_vector_reg2);
	instr = INSTR_CREATE_pcmpeqd(drcontext, opnd_create_reg(scratch_vector_reg2),
			opnd_create_reg(key_vector_reg));
	instrlist_meta_preinsert(ilist, where, instr);
	ub_instrum_simd_negate_reg(drcontext, ilist, where, scratch_vector_reg2,
			scratch_vector_reg);

	ub_lp_hashmap_insert_simd_hash(drcontext, ilist, where, scratch_vector_reg,
			key_vector_reg, map_reg);

	for (int i = 0; i < PROBING_THRESHOLD; i++) {

		/* Load key store */
		ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, map_reg,
				offsetof(ub_lp_map_t, key_store), scratch_reg);

		opnd = opnd_create_base_disp(scratch_reg, scratch_vector_reg,
				sizeof(void *), 0, OPSZ_PTR);
		opnd2 = opnd_create_reg(result_vector_reg);
		opnd3 = opnd_create_reg(scratch_vector_reg2);
		instr = INSTR_CREATE_vgatherdpd(drcontext, opnd2, opnd,
				opnd3);
		instrlist_meta_preinsert(ilist, where, instr);

		/* Compare keys */
		opnd = opnd_create_reg(result_vector_reg);
		opnd2 = opnd_create_reg(key_vector_reg);
		instr = INSTR_CREATE_pcmpeqd(drcontext, opnd,
				opnd2);
		instrlist_meta_preinsert(ilist, where, instr);

		/* Prepare new mask */
		opnd = opnd_create_reg(scratch_vector_reg2);
		instr = INSTR_CREATE_pcmpeqd(drcontext, opnd, opnd);
		instrlist_meta_preinsert(ilist, where, instr);

		opnd = opnd_create_reg(scratch_vector_reg2);
		opnd2 = opnd_create_reg(result_vector_reg);
		instr = INSTR_CREATE_ptest(drcontext, opnd, opnd2);
		instrlist_meta_preinsert(ilist, where, instr);

		/* If key found, jmp */
		instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd_create_instr(found_label));
		instrlist_meta_preinsert(ilist, where, instr);

		opnd = opnd_create_reg(scratch_vector_reg2);
		opnd2 = opnd_create_reg(result_vector_reg);
		instr = INSTR_CREATE_pxor(drcontext, opnd, opnd2);
		instrlist_meta_preinsert(ilist, where, instr);

		/* Increment the index for linear probe */
		ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, sizeof(void *),
				scratch_reg);

		opnd = opnd_create_reg(scratch_reg);
		opnd2 = opnd_create_reg(result_vector_reg);
		instr = INSTR_CREATE_movd(drcontext, opnd2, opnd);
		instrlist_meta_preinsert(ilist, where, instr);

		opnd = opnd_create_reg(result_vector_reg);
		opnd_t imm_opnd = opnd_create_immed_uint(0, opnd_size_from_bytes(1));
		instr = INSTR_CREATE_pshufd(drcontext, opnd, opnd, imm_opnd);
		instrlist_meta_preinsert(ilist, where, instr);

		opnd = opnd_create_reg(scratch_vector_reg2);
		opnd2 = opnd_create_reg(result_vector_reg);
		instr = INSTR_CREATE_pand(drcontext, opnd2, opnd);
		instrlist_meta_preinsert(ilist, where, instr);

		opnd = opnd_create_reg(scratch_vector_reg);
		opnd2 = opnd_create_reg(result_vector_reg);
		instr = INSTR_CREATE_paddd(drcontext, opnd, opnd2);
		instrlist_meta_preinsert(ilist, where, instr);

		if (i != PROBING_THRESHOLD - 1) {
			opnd = OPND_CREATE_MEMPTR(map_reg, offsetof(ub_lp_map_t, size));
			opnd2 = opnd_create_reg(result_vector_reg);
			instr = INSTR_CREATE_vbroadcastsd(drcontext, opnd2, opnd);
			instrlist_meta_preinsert(ilist, where, instr);

			instr = INSTR_CREATE_pcmpeqd(drcontext,
					opnd_create_reg(result_vector_reg),
					opnd_create_reg(scratch_vector_reg));
			instrlist_meta_preinsert(ilist, where, instr);

			instr = INSTR_CREATE_pmovmskb(drcontext,
					opnd_create_reg(scratch_reg),
					opnd_create_reg(result_vector_reg));
			instrlist_meta_preinsert(ilist, where, instr);

			/* Check out of bounds */
			instr = INSTR_CREATE_cmp(drcontext, opnd_create_reg(scratch_reg),
					opnd_create_immed_int(0xFFFF, OPSZ_4));
			instrlist_meta_preinsert(ilist, where, instr);

			/* Jump to done if out of bounds */
			instr = INSTR_CREATE_jcc(drcontext, OP_jnz, opnd_create_instr(done_label));
			instrlist_meta_preinsert(ilist, where, instr);
		}
	}

	/* Finished probing, jump to done label */
	instr = INSTR_CREATE_jmp(drcontext, opnd_create_instr(done_label));
	instrlist_meta_preinsert(ilist, where, instr);

	instrlist_meta_preinsert(ilist, where, found_label);

	ub_instrum_simd_clear_reg(drcontext, ilist, where, scratch_vector_reg2);
	instr = INSTR_CREATE_pcmpeqd(drcontext, opnd_create_reg(scratch_vector_reg2),
			opnd_create_reg(key_vector_reg));
	instrlist_meta_preinsert(ilist, where, instr);
	ub_instrum_simd_negate_reg(drcontext, ilist, where, scratch_vector_reg2,
			result_vector_reg);

	/* Load value store */
	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL, map_reg,
			offsetof(ub_lp_map_t, value_store), scratch_reg);

	/* Load the value into result reg */
	opnd = opnd_create_base_disp(scratch_reg, scratch_vector_reg,
			sizeof(void *), 0, OPSZ_PTR);
	opnd2 = opnd_create_reg(result_vector_reg);
	opnd3 = opnd_create_reg(scratch_vector_reg2);
	instr = INSTR_CREATE_vgatherdpd(drcontext, opnd2, opnd,
			opnd3);
	instrlist_meta_preinsert(ilist, where, instr);

	/* Exit */
	instrlist_meta_preinsert(ilist, where, done_label);
}

