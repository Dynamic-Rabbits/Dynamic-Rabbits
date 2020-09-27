/*
 * shadow_mem_map_cc.c
 *
 *      Author: john
 */

#include "tb_cc_arraymap_mem_map.h"

#include <string.h>

void tb_cc_arraymap_init_mem_map(void *user_data) {

	DR_ASSERT_MSG(false, "NYI");
}

void tb_cc_arraymap_exit_mem_map(void *user_data) {
	DR_ASSERT_MSG(false, "NYI");
}

void *tb_cc_arraymap_create_mem_map() {

	DR_ASSERT_MSG(false, "NYI");
	return NULL;
}

void tb_cc_arraymap_destroy_mem_map(void *map_opaque,
		ub_destroy_value_func_t destroy_func) {

	DR_ASSERT_MSG(false, "NYI");
}

void *tb_cc_arraymap_set_taint_mem_and_get_old(void *map_opaque, uintptr_t addr,
		void *label, bool *success) {

	DR_ASSERT_MSG(false, "NYI");
	return NULL;
}

void *tb_cc_arraymap_set_untaint_mem_and_get_old(void *map_opaque,
		uintptr_t addr, bool *success) {

	DR_ASSERT_MSG(false, "NYI");
	return NULL;
}

void *tb_cc_arraymap_get_mem_taint_label(void *map_opaque, uintptr_t addr) {

	DR_ASSERT_MSG(false, "NYI");
	return NULL;
}
