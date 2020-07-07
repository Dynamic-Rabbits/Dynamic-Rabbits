/*
 * tb_cc_taint_map.h
 *
 *  Created on: 11 Jul 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TAINT_MAPS_MEMORY_MAPS_TB_CC_MEM_MAPS_TB_CC_TAINT_MAP_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TAINT_MAPS_MEMORY_MAPS_TB_CC_MEM_MAPS_TB_CC_TAINT_MAP_H_

#include "instrumentation_bunny.h"

typedef void (*tb_cc_init_map_func_t)(client_id_t client_id);
typedef void (*tb_cc_exit_map_func_t)();
typedef void* (*tb_cc_create_map_func_t)(void *user_data, void **start);
typedef void (*tb_cc_destroy_map_func_t)(void *map_opaque,
        ub_destroy_value_func_t destroy_func, void *user_data);
typedef void* (*tb_cc_set_taint_and_get_old_func_t)(void *map_opaque,
        uintptr_t addr, void *label, bool *success);
typedef void* (*tb_cc_set_untaint_and_get_old_func_t)(void *map_opaque,
        uintptr_t addr, bool *success);
typedef void* (*tb_cc_get_label_func_t)(void *map_opaque, uintptr_t addr);

typedef struct {

    tb_cc_init_map_func_t init_map_func;
    tb_cc_exit_map_func_t exit_map_func;
    tb_cc_create_map_func_t create_map_func;
    tb_cc_destroy_map_func_t destroy_map_func;
    tb_cc_set_taint_and_get_old_func_t taint_func;
    tb_cc_set_untaint_and_get_old_func_t untaint_func;
    tb_cc_get_label_func_t get_label_func;
} tb_map_driver_t;

void tb_map_init_maps_drivers_from_cc_mode(tb_map_driver_t * cc_mem_map_driver,
        tb_map_driver_t * cc_reg_map_driver);

void tb_map_init_maps_drivers_from_raw_mode(tb_map_driver_t * cc_mem_map_driver,
        tb_map_driver_t * cc_reg_map_driver);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TAINT_MAPS_MEMORY_MAPS_TB_CC_MEM_MAPS_TB_CC_TAINT_MAP_H_ */
