/*
 * te_cc_shadow_mem_map.h
 *
 *  Created on: 8 Jul 2018
 *      Author: john
 */

#ifndef TAINT_MAPS_MEMORY_MAPS_TE_CC_MEM_MAPS_TE_CC_UMBRA_MEM_MAPS_TE_CC_UMBRA_MEM_MAP_H_
#define TAINT_MAPS_MEMORY_MAPS_TE_CC_MEM_MAPS_TE_CC_UMBRA_MEM_MAPS_TE_CC_UMBRA_MEM_MAP_H_

#include "instrumentation_bunny.h"

void tb_umbra_init_mem_map(client_id_t client_id);
void tb_umbra_exit_mem_map();

void *tb_cc_umbra_create_mem_map(void *user_data, void **start);
void tb_cc_umbra_destroy_mem_map(void *map_opaque,
        ub_destroy_value_func_t destroy_func, void *user_data);

void tb_umbra_safe_read(void *map_opaque, uintptr_t addr, size_t app_size,
        size_t shadow_size, uintptr_t result_buf);

void tb_umbra_safe_write(void *map_opaque, uintptr_t addr, size_t app_size,
        size_t shadow_size, uintptr_t src_buf);

void *tb_umbra_set_taint_mem_and_get_old(void *map_opaque, uintptr_t addr,
        void *label, bool *success);
void *tb_umbra_set_untaint_mem_and_get_old(void *map_opaque, uintptr_t addr,
        bool *success);

void tb_umbra_set_taint_mem_block_and_get_old(void *map_opaque,
        uintptr_t start_addr, size_t block_size, void **new_shadow_buf,
        void **old_shadow_buf, size_t shadow_buf_size);

void tb_umbra_set_untaint_mem_block_and_get_old(void *map_opaque,
        uintptr_t start_addr, size_t block_size, void **old_shadow_buf,
        size_t shadow_buf_size);

void *tb_umbra_get_mem_taint_label(void *map_opaque, uintptr_t addr);

void tb_umbra_get_mem_taint_block_labels(void *map_opaque, uintptr_t addr,
        size_t block_size, size_t label_buf_size, void **label_buf);

#endif /* TAINT_MAPS_MEMORY_MAPS_TE_CC_MEM_MAPS_TE_CC_SHADOW_MEM_MAPS_TE_CC_SHADOW_MEM_MAP_H_ */
