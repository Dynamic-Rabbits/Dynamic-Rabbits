/*
 * shadow_reg_map_cleancall.c
 *
 *      Author: john
 */

#include "tb_cc_array_reg_map.h"
#include <string.h>
#include "tb_array_reg_map_definitions.h"

void tb_cc_arraymap_init_reg_map(client_id_t client_id) {
    // Do nothing
}

void tb_cc_arraymap_exit_reg_map() {
    // Do nothing
}

static void* tb_cc_arraymap_get_aligned(void *start) {
    return (void *) (((uintptr_t) start + 15) & ~(uintptr_t) 0x0F);
}

void *tb_cc_arraymap_create_reg_map(void *user_data, void **start) {

    DR_ASSERT(start);

    tb_map_reg_map_t *reg_map = (tb_map_reg_map_t *) dr_global_alloc(
            sizeof(tb_map_reg_map_t) + 15);
    memset(reg_map, 0, sizeof(tb_map_reg_map_t)+ 15);

    *start = reg_map;

    return tb_cc_arraymap_get_aligned(reg_map);
}

void tb_cc_arraymap_destroy_reg_map(void *map_opaque,
        ub_destroy_value_func_t detroy_func, void *user_data) {

    tb_map_reg_map_t *map = (tb_map_reg_map_t *) tb_cc_arraymap_get_aligned(
            map_opaque);

    if (detroy_func) {

        for (int i = 0; i < REG_MAX_VAL; i++) {

            void *label = map->reg_map[i];

            if (label)
                detroy_func(label);
        }
    }

    // Remove dangling pointers.
    memset(map, 0, sizeof(tb_map_reg_map_t));

    dr_global_free(map_opaque, sizeof(tb_map_reg_map_t)  + 15 );

}

void *tb_cc_arraymap_set_taint_reg_and_get_old(void *map_opaque,
        uintptr_t reg_byte_id, void *label, bool *success) {

#ifdef DEBUG
    DR_ASSERT(reg_byte_id < REG_MAX_VAL);
#endif

    tb_map_reg_map_t *map = map_opaque;
    void *old = map->reg_map[reg_byte_id];

    map->reg_map[reg_byte_id] = label;

    *success = true;

    return old;
}

void *tb_cc_arraymap_set_untaint_reg_and_get_old(void *map_opaque,
        uintptr_t reg_byte_id, bool *success) {

#ifdef DEBUG
    DR_ASSERT(reg_byte_id < REG_MAX_VAL);
#endif

    tb_map_reg_map_t *map = map_opaque;
    void *old = map->reg_map[reg_byte_id];
    map->reg_map[reg_byte_id] = NULL;

    *success = true;
    return old;
}

void *tb_cc_arraymap_get_reg_taint_label(void *map_opaque,
        uintptr_t reg_byte_id) {

#ifdef DEBUG
    DR_ASSERT(reg_byte_id < REG_MAX_VAL);
#endif

    tb_map_reg_map_t *map = map_opaque;
    return map->reg_map[reg_byte_id];
}
