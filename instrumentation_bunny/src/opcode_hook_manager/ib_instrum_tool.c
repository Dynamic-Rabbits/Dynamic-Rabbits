/**
 *  @file ib_hooking.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ib_instrum_tool.h"
#include "utility_bunny.h"
#include "../hook_info/ib_hook_info.h"

/**
 *  @struct ib_instrum_tool_t
 *
 *  A struct that contains information on an instrumentation tool. These allows
 *  multiple components to make use of the same data of instructions
 *  extracted by the instrumenter.
 *
 *  @var ib_instrum_tool_t::opcode_map It maps opcodes to a list of hook info
 *  structs. During instrumentation of a given instruction having an opcode
 *  registered in the map, the instrumentation bunny iterates over the list,
 *  inserting calls to the code caches recorded in the hook info structs.
 */
typedef struct {
	unsigned int id;
	void *opcode_map;
	ib_hook_info_t *default_hook_info;
} ib_instrum_tool_t;

static void ib_instrum_tool_destroy_hooks(void *hook_list_per_instr);

void* ib_instrum_tool_create(unsigned int tool_id) {

	ib_instrum_tool_t *instrum_tool = dr_global_alloc(
			sizeof(ib_instrum_tool_t));

	instrum_tool->id = tool_id;
	instrum_tool->default_hook_info = NULL;
	instrum_tool->opcode_map = ub_intptr_hashmap_create_map();

	return (void *) instrum_tool;
}

static void ib_instrum_tool_destroy_hooks(void *hook_list_per_instr){

	ub_list_destroy(hook_list_per_instr, ib_hook_info_destroy);
}

void ib_instrum_tool_destroy(void *instrum_tool_opaque) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;

	if (instrum_tool->default_hook_info)
		ib_hook_info_destroy(instrum_tool->default_hook_info);

	// Destroy all hook infos in map.
	ub_intptr_hashmap_destroy_map(instrum_tool->opcode_map,
			ib_instrum_tool_destroy_hooks);

	dr_global_free(instrum_tool, sizeof(ib_instrum_tool_t));
}

void ib_instrum_tool_register_opcode_hook(void *instrum_tool_opaque, int opcode,
		ib_hook_info_t *src_opcode_hook_info) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;

	DR_ASSERT(instrum_tool);
	DR_ASSERT(instrum_tool->opcode_map);

	ib_hook_info_t *ib_opcode_hook_info = ib_hook_info_create_from_other(
			src_opcode_hook_info);

	void *instr_hook_list = ub_intptr_hashmap_lookup_entry(
			instrum_tool->opcode_map, opcode);

	if (!instr_hook_list) {

		instr_hook_list = ub_list_create();

		ub_key_value_pair_t key_value_pair;
		key_value_pair.key = opcode;
		key_value_pair.value = instr_hook_list;

		void *null_value = ub_intptr_hashmap_insert_entry(
				instrum_tool->opcode_map, &key_value_pair);

		DR_ASSERT(!null_value);
	}

	ub_list_insert(instr_hook_list, ib_opcode_hook_info);
}

bool ib_instrum_tool_unregister_opcode_hook(void *instrum_tool_opaque,
		int opcode) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;

	DR_ASSERT(instrum_tool);

	void *hook_info_list_per_instr = ub_intptr_hashmap_remove_entry(
			instrum_tool->opcode_map, (uintptr_t) opcode);

	if (hook_info_list_per_instr) {

		ub_list_destroy(hook_info_list_per_instr, ib_hook_info_destroy);
		return true;
	}

	return false;
}

void *ib_instrum_tool_get_hook_info(void *instrum_tool_opaque,
		int opcode) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;

	DR_ASSERT(instrum_tool);

	return ub_intptr_hashmap_lookup_entry(instrum_tool->opcode_map, opcode);
}

void ib_instrum_tool_register_default_opcode_hook(void *instrum_tool_opaque,
		ib_hook_info_t *src_default_hook_info) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;

	DR_ASSERT(instrum_tool);

	ib_hook_info_t * default_hook_info = ib_hook_info_create_from_other(
			src_default_hook_info);

	instrum_tool->default_hook_info = default_hook_info;
}

bool ib_instrum_tool_unregister_default_opcode_hook(void *instrum_tool_opaque) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;

	bool removed = false;

	if (instrum_tool->default_hook_info) {
		removed = true;
		ib_hook_info_destroy(instrum_tool->default_hook_info);
	}

	instrum_tool->default_hook_info = NULL;
	return removed;
}

bool ib_instrum_tool_is_default_opcode_hook_set(void *instrum_tool_opaque) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;
	return instrum_tool->default_hook_info != NULL;
}

ib_hook_info_t *ib_instrum_tool_get_default_opcode_hook(
		void *instrum_tool_opaque) {

	DR_ASSERT(instrum_tool_opaque);
	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;

	return instrum_tool->default_hook_info;
}

unsigned int ib_instrum_tool_get_id(void *instrum_tool_opaque) {

	ib_instrum_tool_t *instrum_tool = (ib_instrum_tool_t *) instrum_tool_opaque;
	return instrum_tool->id;
}
