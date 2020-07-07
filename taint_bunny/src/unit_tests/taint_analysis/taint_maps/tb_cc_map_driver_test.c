/*
 * tb_cc_map_driver_test.c
 *
 *      Author: john
 */

#include "instrumentation_bunny.h"
#include "../../../taint_engines/taint_analysis/taint_maps/tb_cc_map_driver.h"
#include "../../../taint_engines/taint_analysis/taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../../taint_engines/taint_analysis/taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include "../../../taint_engines/taint_analysis/taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"
#include "../../../taint_engines/taint_analysis/taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"

void is_standard_cc_reg(tb_map_driver_t *cc_reg_map_driver) {

    DR_ASSERT(
            cc_reg_map_driver->create_map_func
                    == tb_cc_arraymap_create_reg_map);
    DR_ASSERT(
            cc_reg_map_driver->destroy_map_func
                    == tb_cc_arraymap_destroy_reg_map);
    DR_ASSERT(cc_reg_map_driver->init_map_func == tb_cc_arraymap_init_reg_map);
    DR_ASSERT(cc_reg_map_driver->exit_map_func == tb_cc_arraymap_exit_reg_map);
    DR_ASSERT(
            cc_reg_map_driver->get_label_func
                    == tb_cc_arraymap_get_reg_taint_label);
    DR_ASSERT(
            cc_reg_map_driver->untaint_func
                    == tb_cc_arraymap_set_untaint_reg_and_get_old);
    DR_ASSERT(
            cc_reg_map_driver->taint_func
                    == tb_cc_arraymap_set_taint_reg_and_get_old);
}

void is_standard_cc_mem(tb_map_driver_t *cc_mem_map_driver) {

    DR_ASSERT(cc_mem_map_driver->create_map_func == tb_raw_umbra_create_mem_map);
    DR_ASSERT(
            cc_mem_map_driver->destroy_map_func == tb_raw_umbra_destroy_mem_map);
    DR_ASSERT(cc_mem_map_driver->init_map_func == tb_umbra_init_mem_map);
    DR_ASSERT(cc_mem_map_driver->exit_map_func == tb_umbra_exit_mem_map);
    DR_ASSERT(
            cc_mem_map_driver->get_label_func
                    == tb_umbra_get_mem_taint_label);
    DR_ASSERT(
            cc_mem_map_driver->untaint_func
                    == tb_umbra_set_untaint_mem_and_get_old);
    DR_ASSERT(
            cc_mem_map_driver->taint_func
                    == tb_umbra_set_taint_mem_and_get_old);
}

void is_standard_raw_mem(tb_map_driver_t *raw_mem_map_driver) {

    DR_ASSERT(raw_mem_map_driver->init_map_func == tb_umbra_init_mem_map);
    DR_ASSERT(raw_mem_map_driver->exit_map_func == tb_umbra_exit_mem_map);
    DR_ASSERT(
            raw_mem_map_driver->get_label_func
                    == tb_umbra_get_mem_taint_label);
    DR_ASSERT(
            raw_mem_map_driver->untaint_func
                    == tb_umbra_set_untaint_mem_and_get_old);
    DR_ASSERT(
            raw_mem_map_driver->taint_func
                    == tb_umbra_set_taint_mem_and_get_old);
}

void test_cc_engine() {

    tb_options_t option;
    tb_map_driver_t cc_mem_map_driver;
    tb_map_driver_t cc_reg_map_driver;

    //TB_CC_CACHE_BYTE,
    memset(&option, 0, sizeof(tb_options_t));
    memset(&cc_mem_map_driver, 0, sizeof(tb_map_driver_t));
    memset(&cc_reg_map_driver, 0, sizeof(tb_map_driver_t));
    tb_map_init_maps_drivers_from_cc_mode(&cc_mem_map_driver,
            &cc_reg_map_driver);
    is_standard_cc_reg(&cc_reg_map_driver);
    is_standard_cc_mem(&cc_mem_map_driver);

    //TB_CC_IN_BYTE,
    memset(&option, 0, sizeof(tb_options_t));
    memset(&cc_mem_map_driver, 0, sizeof(tb_map_driver_t));
    memset(&cc_reg_map_driver, 0, sizeof(tb_map_driver_t));
    option.enable_inline = true;
    tb_map_init_maps_drivers_from_cc_mode(&cc_mem_map_driver,
            &cc_reg_map_driver);
    is_standard_cc_reg(&cc_reg_map_driver);
    is_standard_cc_mem(&cc_mem_map_driver);
}

void test_raw_engine() {

    tb_options_t option;
    tb_map_driver_t raw_mem_map_driver;
    tb_map_driver_t raw_reg_map_driver;

    //TB_RAW_CACHE_BYTE,
    memset(&option, 0, sizeof(tb_options_t));
    memset(&raw_mem_map_driver, 0, sizeof(tb_map_driver_t));
    memset(&raw_reg_map_driver, 0, sizeof(tb_map_driver_t));
    tb_map_init_maps_drivers_from_raw_mode(&raw_mem_map_driver,
            &raw_reg_map_driver);
    is_standard_cc_reg(&raw_reg_map_driver);
    is_standard_raw_mem(&raw_mem_map_driver);

    DR_ASSERT(
            raw_mem_map_driver.create_map_func
                    == tb_raw_umbra_create_mem_map);
    DR_ASSERT(
            raw_mem_map_driver.destroy_map_func
                    == tb_raw_umbra_destroy_mem_map);

    //TB_RAW_IN_BYTE
    memset(&option, 0, sizeof(tb_options_t));
    memset(&raw_mem_map_driver, 0, sizeof(tb_map_driver_t));
    memset(&raw_reg_map_driver, 0, sizeof(tb_map_driver_t));
    option.enable_inline = true;
    tb_map_init_maps_drivers_from_raw_mode(&raw_mem_map_driver,
            &raw_reg_map_driver);
    is_standard_cc_reg(&raw_reg_map_driver);
    is_standard_raw_mem(&raw_mem_map_driver);

    DR_ASSERT(
            raw_mem_map_driver.create_map_func
                    == tb_raw_umbra_create_mem_map);
    DR_ASSERT(
            raw_mem_map_driver.destroy_map_func
                    == tb_raw_umbra_destroy_mem_map);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    test_cc_engine();
    test_raw_engine();
}

