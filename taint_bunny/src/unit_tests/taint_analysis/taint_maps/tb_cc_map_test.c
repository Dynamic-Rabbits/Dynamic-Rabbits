/*
 * tb_cc_map_test.c
 *
 *      Author: john
 */

#include "instrumentation_bunny.h"
#include "../../../taint_engines/taint_analysis/taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"
#include "../../../taint_engines/taint_analysis/taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    drutil_init();

    tb_cc_arraymap_init_reg_map(id);
    tb_umbra_init_mem_map(id);


    /**********************************************
     * REG MAP
     */

    void *start;
    void *reg_map = tb_cc_arraymap_create_reg_map(NULL, &start);
    bool succ = false;

    void *tl = tb_cc_arraymap_get_reg_taint_label(reg_map,
            ub_get_byte_id(DR_REG_XAX, 0));
    DR_ASSERT(tl == NULL);


    void *old = tb_cc_arraymap_set_taint_reg_and_get_old(reg_map,
            ub_get_byte_id(DR_REG_XAX, 0), (void *) 121, &succ);

    DR_ASSERT(!old);
    DR_ASSERT(succ);

    tl = tb_cc_arraymap_get_reg_taint_label(reg_map,
            ub_get_byte_id(DR_REG_XAX, 0));
    DR_ASSERT(tl == (void *) 121);

    old = tb_cc_arraymap_set_taint_reg_and_get_old(reg_map,
            ub_get_byte_id(DR_REG_XAX, 0), (void *) 122, &succ);
    DR_ASSERT(old == (void *) 121);

    succ = false;
    old = tb_cc_arraymap_set_untaint_reg_and_get_old(reg_map,
            ub_get_byte_id(DR_REG_XAX, 0), &succ);

    DR_ASSERT(old == (void *) 122);
    DR_ASSERT(succ);

    tl = tb_cc_arraymap_get_reg_taint_label(reg_map,
            ub_get_byte_id(DR_REG_XAX, 0));
    DR_ASSERT(tl == NULL);

    tb_cc_arraymap_destroy_reg_map(start, NULL, NULL);

    /**********************************************
     * MEM MAP
     */

    void *umbra_map = tb_cc_umbra_create_mem_map(NULL, NULL);

    tl = tb_umbra_get_mem_taint_label(umbra_map, (intptr_t) 121);
    DR_ASSERT(tl == NULL);

    succ= false;
    old = tb_umbra_set_taint_mem_and_get_old(umbra_map, (intptr_t) 121,
            (void *) 1, &succ);
    DR_ASSERT(!old);
    DR_ASSERT(succ);

    tl = tb_umbra_get_mem_taint_label(umbra_map, (intptr_t) 121);
    DR_ASSERT(tl == (void *) 1);

    succ= false;
    old = tb_umbra_set_untaint_mem_and_get_old(umbra_map, (intptr_t) 121,
            &succ);

    DR_ASSERT(old == (void *) 1);
    DR_ASSERT(succ);

    tl = tb_umbra_get_mem_taint_label(umbra_map, (intptr_t) 121);
    DR_ASSERT(tl == NULL);

    tb_cc_umbra_destroy_mem_map(umbra_map, NULL, NULL);

    tb_umbra_exit_mem_map();
    tb_cc_arraymap_exit_reg_map();

    drmgr_exit();
    drutil_exit();

}
