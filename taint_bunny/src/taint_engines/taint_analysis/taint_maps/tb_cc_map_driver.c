/*
 * tb_cc_map_driver.c
 *
 *      Author: john
 */

#include "tb_cc_map_driver.h"
#include "memory_maps/tb_cc_mem_maps/tb_cc_arraymap_mem_maps/tb_cc_arraymap_mem_map.h"
#include "memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

/************************************************************************************
 * Memory Maps
 */

static void tb_mem_umbra_map_init_driver(tb_map_driver_t * cc_map_driver) {

    cc_map_driver->init_map_func = tb_umbra_init_mem_map;
    cc_map_driver->exit_map_func = tb_umbra_exit_mem_map;
    cc_map_driver->create_map_func = tb_raw_umbra_create_mem_map;
    cc_map_driver->destroy_map_func = tb_raw_umbra_destroy_mem_map;
    cc_map_driver->taint_func = tb_umbra_set_taint_mem_and_get_old;
    cc_map_driver->untaint_func = tb_umbra_set_untaint_mem_and_get_old;
    cc_map_driver->get_label_func = tb_umbra_get_mem_taint_label;
}

static void tb_mem_umbra_raw_map_init_driver(tb_map_driver_t * cc_map_driver) {

    cc_map_driver->init_map_func = tb_umbra_init_mem_map;
    cc_map_driver->exit_map_func = tb_umbra_exit_mem_map;
    cc_map_driver->create_map_func = tb_raw_umbra_create_mem_map;
    cc_map_driver->destroy_map_func = tb_raw_umbra_destroy_mem_map;
    cc_map_driver->taint_func = tb_umbra_set_taint_mem_and_get_old;
    cc_map_driver->untaint_func = tb_umbra_set_untaint_mem_and_get_old;
    cc_map_driver->get_label_func = tb_umbra_get_mem_taint_label;
}

/************************************************************************************
 * Reg Maps
 */

static void tb_reg_arraymap_map_init_driver(tb_map_driver_t * cc_map_driver) {

    cc_map_driver->init_map_func = tb_cc_arraymap_init_reg_map;
    cc_map_driver->exit_map_func = tb_cc_arraymap_exit_reg_map;
    cc_map_driver->create_map_func = tb_cc_arraymap_create_reg_map;
    cc_map_driver->destroy_map_func = tb_cc_arraymap_destroy_reg_map;
    cc_map_driver->taint_func = tb_cc_arraymap_set_taint_reg_and_get_old;
    cc_map_driver->untaint_func = tb_cc_arraymap_set_untaint_reg_and_get_old;
    cc_map_driver->get_label_func = tb_cc_arraymap_get_reg_taint_label;
}

/*****************************************************************
 * HELPER Functions
 */

void tb_map_init_maps_drivers_from_cc_mode(tb_map_driver_t * cc_mem_map_driver,
        tb_map_driver_t * cc_reg_map_driver) {

    DR_ASSERT(cc_mem_map_driver);
    DR_ASSERT(cc_reg_map_driver);

    tb_mem_umbra_map_init_driver(cc_mem_map_driver);
    tb_reg_arraymap_map_init_driver(cc_reg_map_driver);
}

void tb_map_init_maps_drivers_from_raw_mode(tb_map_driver_t * mem_map_driver,
        tb_map_driver_t * reg_map_driver) {

    DR_ASSERT(mem_map_driver);
    DR_ASSERT(reg_map_driver);

    tb_mem_umbra_raw_map_init_driver(mem_map_driver);
    tb_reg_arraymap_map_init_driver(reg_map_driver);
}
