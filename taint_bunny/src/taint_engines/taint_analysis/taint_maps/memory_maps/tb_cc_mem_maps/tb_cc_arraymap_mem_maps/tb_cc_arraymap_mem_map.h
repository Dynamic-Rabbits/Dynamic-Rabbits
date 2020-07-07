/*
 * te_cc_shadow_mem_map.h
 *
 *  Created on: 8 Jul 2018
 *      Author: john
 */

#ifndef TAINT_MAPS_MEMORY_MAPS_TE_CC_MEM_MAPS_TE_CC_ARRAYMAP_MEM_MAPS_TE_CC_ARRAYMAP_MEM_MAP_H_
#define TAINT_MAPS_MEMORY_MAPS_TE_CC_MEM_MAPS_TE_CC_ARRAYMAP_MEM_MAPS_TE_CC_ARRAYMAP_MEM_MAP_H_

#include "instrumentation_bunny.h"

void tb_cc_arraymap_init_mem_map(void *user_data);

void tb_cc_arraymap_exit_mem_map(void *user_data);

void *tb_cc_arraymap_create_mem_map();

void tb_cc_arraymap_destroy_mem_map(void *map_opaque,
		ub_destroy_value_func_t destroy_func);

void *tb_cc_arraymap_set_taint_mem_and_get_old(void *map_opaque, uintptr_t addr,
		void *label, bool *success);

void *tb_cc_arraymap_set_untaint_mem_and_get_old(void *map_opaque,
		uintptr_t addr, bool *success);

void *tb_cc_arraymap_get_mem_taint_label(void *map_opaque, uintptr_t addr);

#endif /* TAINT_MAPS_MEMORY_MAPS_TE_CC_MEM_MAPS_TE_CC_ARRAYMAP_MEM_MAPS_TE_CC_ARRAYMAP_MEM_MAP_H_ */
