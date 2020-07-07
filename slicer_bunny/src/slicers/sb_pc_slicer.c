/**
 *  @file sb_pc_slicer.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "sb_pc_slicer.h"
#include "utility_bunny.h"
#include <string.h>

#define LINE_BUF_SIZE 120

typedef struct preslicer {
	void *pc_hashset;
} sb_pc_slicer_t;

/**
 *  Initialises the PC slicer.
 *
 *  Reads the file by making use of ub_file_reader.c
 */
void *sb_pc_slicer_init() {

	sb_pc_slicer_t *pc_slicer = dr_global_alloc(sizeof(sb_pc_slicer_t));

	pc_slicer->pc_hashset = ub_intptr_hashset_create();

	return pc_slicer;
}

/**
 * Destroys the PC slicer.
 */
void sb_pc_slicer_destroy(void *pc_slicer_opaque) {

	sb_pc_slicer_t *pc_slicer = (sb_pc_slicer_t *) pc_slicer_opaque;

	ub_intptr_hashset_destroy(pc_slicer->pc_hashset);

	dr_global_free(pc_slicer, sizeof(sizeof(sb_pc_slicer_t)));
}

/**
 * Registers the pc addr to slice, which are listed in a given file.
 *
 * @param pc_file The file listing the instr addresses to slice.
 */
void sb_pc_slicer_register_file(void *pc_slicer_opaque, file_t pc_file) {

	sb_pc_slicer_t *pc_slicer = (sb_pc_slicer_t *) pc_slicer_opaque;

	char line_buf[LINE_BUF_SIZE];

	// We stop looping when we encounter a failed read. We read the file here to avoid creating a new data structure.
	while (ub_fr_get_line(pc_file, line_buf, LINE_BUF_SIZE)) {

		uintptr_t ptr = 0;
		dr_sscanf(line_buf, "%p", (void **)&ptr);
		ub_intptr_hashset_insert(pc_slicer->pc_hashset, ptr);
	}
}

/**
 *  States whether to slice the proc address.
 *
 *  @param proc_address The proc address to check.
 *  @return Returns True if the proc_address should be sliced (not analysed).
 */
bool sb_pc_slicer_slice_out(void *pc_slicer_opaque, app_pc proc_address) {

	sb_pc_slicer_t *pc_slicer = (sb_pc_slicer_t *) pc_slicer_opaque;
	return ub_intptr_hashset_is_included(pc_slicer->pc_hashset, (uintptr_t) proc_address);
}
