/*
 * ub_lp_hashmap_test2.c
 *
 *      Author: john
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "dr_api.h"
#include "drmgr.h"
#include "drreg.h"
#include "drutil.h"
#include "../../../utility_bunny.h"

void *map;

static void event_exit();
static dr_emit_flags_t event_bb_insert(void *drcontext, void *tag,
		instrlist_t *bb, instr_t *instr, bool for_trace, bool translating,
		void *user_data);

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();
	drutil_init();

	map = ub_tk_lp_hashmap_create();

	drreg_options_t ops = { sizeof(ops), 4, false };

	drmgr_priority_t priority = { sizeof(priority), "array", NULL, NULL, 0 };
	dr_register_exit_event(event_exit);

	if (!drmgr_register_bb_instrumentation_event(NULL, event_bb_insert,
			&priority) || drreg_init(&ops) != DRREG_SUCCESS) {
		/* something is wrong: can't continue */
		DR_ASSERT(false);
		return;
	}
}

static void event_exit() {

	ub_tk_lp_hashmap_destroy(map, NULL);

	if (!drmgr_unregister_bb_insertion_event(event_bb_insert)
			|| drreg_exit() != DRREG_SUCCESS)
		DR_ASSERT(false);

	drutil_exit();
	drmgr_exit();
}

void test_null(reg_id_t reg) {

	void* drcontext = dr_get_current_drcontext();

	// Initialise machine context so that reg values may be retrieved.
	dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
	dr_get_mcontext(drcontext, &mcontext);

	uintptr_t val = (uintptr_t) reg_get_value(reg, &mcontext);
	DR_ASSERT((void *)val == NULL);

	val = (uintptr_t) ub_tk_lp_hashmap_lookup_entry(map, 6, 6);
	DR_ASSERT((void *)val == NULL);
}

void test_null2(reg_id_t reg) {

	void* drcontext = dr_get_current_drcontext();

	// Initialise machine context so that reg values may be retrieved.
	dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
	dr_get_mcontext(drcontext, &mcontext);

	uintptr_t val = (uintptr_t) reg_get_value(reg, &mcontext);
	DR_ASSERT((void *)val == NULL);

	val = (uintptr_t) ub_tk_lp_hashmap_lookup_entry(map, 7, 7);
	DR_ASSERT((void *)val == NULL);
}

void test_null3(reg_id_t reg) {

	void* drcontext = dr_get_current_drcontext();

	// Initialise machine context so that reg values may be retrieved.
	dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
	dr_get_mcontext(drcontext, &mcontext);

	uintptr_t val = (uintptr_t) reg_get_value(reg, &mcontext);
	DR_ASSERT((void *)val == NULL);

	val = (uintptr_t) ub_tk_lp_hashmap_lookup_entry(map, 6, 6);
	DR_ASSERT((void *)val == NULL);
}

void test_insert() {

	ub_two_key_value_pair_t key_val_pair;
	key_val_pair.key1 = 6;
	key_val_pair.key2 = 6;
	key_val_pair.value = (void *) 6;

	uintptr_t val = (uintptr_t) ub_tk_lp_hashmap_insert_entry(map,
			&key_val_pair);
	DR_ASSERT(val == 0);
}

void test_remove() {

	void *res;
	bool found = (uintptr_t) ub_tk_lp_hashmap_remove_entry(map, 6, 6, &res);
	DR_ASSERT(found);
	DR_ASSERT(res == (void * ) 6);
}

void test_check(reg_id_t reg) {

	void* drcontext = dr_get_current_drcontext();

	// Initialise machine context so that reg values may be retrieved.
	dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
	dr_get_mcontext(drcontext, &mcontext);

	uintptr_t val = (uintptr_t) reg_get_value(reg, &mcontext);
	DR_ASSERT(val == 6);

	val = (uintptr_t) ub_tk_lp_hashmap_lookup_entry(map, 6, 6);
	DR_ASSERT(val == 6);
}

/* event_bb_insert calls instrument_mem to instrument every
 * application memory reference.
 */
static dr_emit_flags_t event_bb_insert(void *drcontext, void *tag,
		instrlist_t *bb, instr_t *where, bool for_trace, bool translating,
		void *user_data) {

	instr_t *instr;
	opnd_t ref, opnd1, opnd2;
	reg_id_t key_reg, result_reg, scratch_reg;
	drvector_t allowed;

	drreg_init_and_fill_vector(&allowed, false);
	drreg_set_vector_entry(&allowed, DR_REG_XAX, true);
	if (drreg_reserve_register(drcontext, bb, where, &allowed, &result_reg)
			!= DRREG_SUCCESS
			|| drreg_reserve_register(drcontext, bb, where, NULL, &key_reg)
					!= DRREG_SUCCESS
			|| drreg_reserve_register(drcontext, bb, where, NULL, &scratch_reg)
					!= DRREG_SUCCESS
			|| drreg_reserve_aflags(drcontext, bb, where) != DRREG_SUCCESS) {
		DR_ASSERT(false); /* cannot recover */
		drvector_delete(&allowed);
		return DR_EMIT_DEFAULT;
	}
	drvector_delete(&allowed);

	ub_instrum_mov_st_immed_to_reg(drcontext, bb, where, 6, key_reg);

	ub_tk_lp_hashmap_insert_lookup_entry(map, drcontext, bb, where, result_reg,
			key_reg, key_reg, scratch_reg);

	dr_insert_clean_call(drcontext, bb, where, test_null, false, 1,
	OPND_CREATE_INTPTR(result_reg));

	dr_insert_clean_call(drcontext, bb, where, test_insert, false, 0);

	ub_tk_lp_hashmap_insert_lookup_entry(map, drcontext, bb, where, result_reg,
			key_reg, key_reg, scratch_reg);

	dr_insert_clean_call(drcontext, bb, where, test_check, false, 1,
	OPND_CREATE_INTPTR(result_reg));

	ub_instrum_mov_st_immed_to_reg(drcontext, bb, where, 7, key_reg);

	ub_tk_lp_hashmap_insert_lookup_entry(map, drcontext, bb, where, result_reg,
			key_reg, key_reg, scratch_reg);

	dr_insert_clean_call(drcontext, bb, where, test_null2, false, 1,
	OPND_CREATE_INTPTR(result_reg));

	dr_insert_clean_call(drcontext, bb, where, test_remove, false, 0);

	ub_instrum_mov_st_immed_to_reg(drcontext, bb, where, 6, key_reg);

	ub_tk_lp_hashmap_insert_lookup_entry(map, drcontext, bb, where, result_reg,
			key_reg, key_reg, scratch_reg);

	dr_insert_clean_call(drcontext, bb, where, test_null3, false, 1,
	OPND_CREATE_INTPTR(result_reg));

	if (drreg_unreserve_register(drcontext, bb, where, key_reg) != DRREG_SUCCESS
			|| drreg_unreserve_register(drcontext, bb, where, result_reg)
					!= DRREG_SUCCESS
			|| drreg_unreserve_register(drcontext, bb, where, scratch_reg)
					!= DRREG_SUCCESS
			|| drreg_unreserve_aflags(drcontext, bb, where) != DRREG_SUCCESS)
		DR_ASSERT(false);

	return DR_EMIT_DEFAULT;
}

