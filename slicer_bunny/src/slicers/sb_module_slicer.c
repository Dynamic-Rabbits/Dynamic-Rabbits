/**
 * @author John F.X. Galea
 */

#include "sb_module_slicer.h"
#include "utility_bunny.h"
#include <string.h>

#define LINE_BUF_SIZE 120

/**
 *  @struct sb_slicer_module_t
 *
 *  Maintains information pertaining to the code base of modules to slice.
 *
 *  @var sb_slicer_module_t::module_addr_ranges A splay tree that stores the ranges of proc
 *  addresses to slice away and not analyse
 *
 *  @var sb_slicer_module_t::module_hashset A set of names of modules to slice away.
 */
typedef struct preslicer {
	void *module_addr_ranges;
	void *module_hashset;
} sb_module_slicer_t;

static void sb_slicer_module_load(void *drcontext, const module_data_t *mod,
		bool loaded, void *module_slicer_opaque);

static void sb_slicer_module_unload(void *drcontext, const module_data_t *mod,
		void *module_slicer_opaque);

/******************************************************************************
 *
 * Implementation
 *
 ******************************************************************************/

/**
 * Initialises the preslicer according to the instruction details found in the slice file.
 *
 * @param preslicer The preslicer to intitialise
 * @param slice_file The file to read
 */
void sb_module_slicer_register_file(void *module_slicer_opaque,
		file_t module_file) {

	sb_module_slicer_t *module_slicer =
			(sb_module_slicer_t *) module_slicer_opaque;

	char line_buf[LINE_BUF_SIZE];

	// We stop looping when we encounter a failed read. We read the file here to avoid creating a new data structure.
	while (ub_fr_get_line(module_file, line_buf, LINE_BUF_SIZE)) {

		bool is_new_entry = ub_str_hashset_insert(module_slicer->module_hashset,
				line_buf);
		DR_ASSERT(is_new_entry);
	}
}

/**
 * Callback function triggered upon module load.
 */
static void sb_slicer_module_load(void *drcontext, const module_data_t *mod,
		bool loaded, void *module_slicer_opaque) {

	sb_module_slicer_t *module_slicer =
			(sb_module_slicer_t *) module_slicer_opaque;

	if (mod->names.module_name != NULL) {

		DR_ASSERT(module_slicer);

		int module_name_size = strlen(mod->names.module_name) + 1;
		char module_name[module_name_size];

		memcpy(module_name, mod->names.module_name, module_name_size);

		if (ub_str_hashset_is_included(module_slicer->module_hashset,
				module_name)) {

			ub_key_value_pair_t key_value_pair;

			if (mod->contiguous) {

				key_value_pair.key = (uintptr_t) mod->start;
				key_value_pair.value = mod->end;

				ub_splay_tree_insert(module_slicer->module_addr_ranges,
						&key_value_pair);
			} else {

				for (int i = 0; i < mod->num_segments; i++) {
					module_segment_data_t * seg_data = &(mod->segments[i]);

					key_value_pair.key = (uintptr_t) seg_data->start;
					key_value_pair.value = seg_data->end;

					ub_splay_tree_insert(module_slicer->module_addr_ranges,
							&key_value_pair);
				}
			}

		}
	}
}

/**
 * Callback function triggered upon module unload.
 */
static void sb_slicer_module_unload(void *drcontext, const module_data_t *mod,
		void *module_slicer_opaque) {

	sb_module_slicer_t *module_slicer =
			(sb_module_slicer_t *) module_slicer_opaque;

	if (mod->names.module_name != NULL) {

		DR_ASSERT(module_slicer);

		int module_name_size = strlen(mod->names.module_name) + 1;
		char module_name[module_name_size];

		memcpy(module_name, mod->names.module_name, module_name_size);

		if (ub_str_hashset_is_included(module_slicer->module_hashset,
				module_name)) {

			dr_fprintf(STDERR, "Unloaded DLL:  %s\n", module_name);

			ub_splay_tree_remove(module_slicer->module_addr_ranges,
					(intptr_t) mod->start);
		}
	}
}

void *sb_module_slicer_init(drmgr_priority_t *priority) {

	drmgr_init();

	sb_module_slicer_t *module_slicer = dr_global_alloc(
			sizeof(sb_module_slicer_t));

	if (!drmgr_register_module_load_event_user_data(sb_slicer_module_load,
			priority, (void *) module_slicer)
			|| !drmgr_register_module_unload_event_user_data(
					sb_slicer_module_unload, NULL, (void *) module_slicer)) {

		dr_global_free(module_slicer, sizeof(sb_module_slicer_t));
		return NULL;
	}

	module_slicer->module_addr_ranges = ub_splay_tree_create();
	module_slicer->module_hashset = ub_str_hashset_create();

	return module_slicer;
}

void sb_module_slicer_destroy(void *module_slicer_opaque) {

	sb_module_slicer_t *module_slicer =
			(sb_module_slicer_t *) module_slicer_opaque;

	if (!drmgr_unregister_module_load_event_user_data(sb_slicer_module_load)
			|| !drmgr_unregister_module_unload_event_user_data(
					sb_slicer_module_unload)) {

		DR_ASSERT(false);
	}

	ub_splay_tree_destroy(module_slicer->module_addr_ranges);
	ub_str_hashset_destroy(module_slicer->module_hashset);

	dr_global_free(module_slicer, sizeof(sb_module_slicer_t));

	drmgr_exit();
}

bool sb_slicer_module_slice_out(void *module_slicer_opaque, app_pc proc_address) {

	sb_module_slicer_t *module_slicer =
			(sb_module_slicer_t *) module_slicer_opaque;

	DR_ASSERT(module_slicer);

	ub_key_value_pair_t found_val;

	ub_splay_tree_find(module_slicer->module_addr_ranges,
			(uintptr_t) proc_address, &found_val, SPLAY_TREE_LOWER_NEIGHBOUR);

	return (void *) found_val.key <= (void *) proc_address
			&& (void *) proc_address < (void *) found_val.value;
}

