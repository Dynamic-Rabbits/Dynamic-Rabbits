/*
 * shadow_mem_map_cc.c
 *
 *      Author: john
 */

#include "tb_cc_umbra_mem_map.h"
#include "signal.h"

#include "umbra.h"
#include <string.h>

void tb_umbra_init_mem_map(client_id_t client_id) {

    drmf_status_t result = umbra_init(client_id);
    DR_ASSERT(result == DRMF_SUCCESS);
}

void tb_umbra_exit_mem_map() {

    umbra_exit();
}

void *tb_cc_umbra_create_mem_map(void *user_data, void **start) {

    umbra_map_t *map;

    umbra_map_options_t umbra_options;
    memset(&umbra_options, 0, sizeof(umbra_map_options_t));
    umbra_options.struct_size = sizeof(sizeof(umbra_map_options_t));
    umbra_options.default_value = 0; // Default is untaint!
    umbra_options.default_value_size = 1;

    // We need to set up a RED ZONE to detect cross block.
    // We encountered this when dealing with REPS.
    // umbra_options.redzone_size = 256;
    // umbra_options.redzone_value = 0;
    // umbra_options.redzone_value_size = 1;

    umbra_options.make_redzone_faulty = true;
    umbra_options.flags = UMBRA_MAP_CREATE_SHADOW_ON_TOUCH
            | UMBRA_MAP_SHADOW_SHARED_READONLY;

#ifdef X86_32
    // For every byte, we scale it up to 4 bytes (32 bits)
    umbra_options.scale = UMBRA_MAP_SCALE_UP_4X;
#endif

#ifdef X86_64
    // For every byte, we scale it up to 8 bytes (64 bits)
    umbra_options.scale = UMBRA_MAP_SCALE_UP_8X;
#endif

    drmf_status_t result = umbra_create_mapping(&umbra_options, &map);
    DR_ASSERT(result == DRMF_SUCCESS);

    if (start)
        *start = map;

    return map;
}

/**
 * Called via shadow memory iteration to destroy allocated data.
 */
static bool tb_map_destroy_data(umbra_map_t *map,
        umbra_shadow_memory_info_t *info, void *user_data) {

    if (info->shadow_type == UMBRA_SHADOW_MEMORY_TYPE_NORMAL) {

        ub_destroy_value_func_t destroy_func =
                (ub_destroy_value_func_t) user_data;

        uintptr_t base = (uintptr_t) info->shadow_base;

        for (uintptr_t addr = base; addr < base + info->shadow_size; addr +=
                sizeof(void *)) {

            // Extract the label from shadow memory
            void *label;
            memcpy(&label, (void *) addr, sizeof(void *));

            // If label is not null, destroy it!
            if (label) {
                destroy_func(label);
            }
        }
    }

    return true;
}

void tb_cc_umbra_destroy_mem_map(void *map_opaque,
        ub_destroy_value_func_t destroy_func, void *user_data) {

    umbra_map_t * map = (umbra_map_t *) map_opaque;

    // Iterate through memory and destroy shadow data.
    if (destroy_func)
        umbra_iterate_shadow_memory(map, destroy_func, tb_map_destroy_data);

    umbra_destroy_mapping(map);
}

static void tb_umbra_safe(void *map_opaque, uintptr_t addr, size_t app_size,
        size_t shadow_size, uintptr_t result_base_buf,
        drmf_status_t (*umbra_func)(IN umbra_map_t *map, IN app_pc app_addr,
                IN size_t app_size, INOUT size_t *shadow_size, OUT byte *buffer)) {

    DR_ASSERT(map_opaque);

    umbra_map_t * map = (umbra_map_t *) map_opaque;

    intptr_t sub_read_size = 0;
    intptr_t total_read_size = 0;

    int scale;
    bool is_scale_down;
    umbra_get_granularity(map, &scale, &is_scale_down);

    uintptr_t cur_app_addr = addr;
    uintptr_t end_app_addr = addr + app_size;

    while (cur_app_addr < end_app_addr) {

        size_t cur_app_size = end_app_addr - cur_app_addr;

        if (is_scale_down && ((int) cur_app_size < scale))
            cur_app_size = scale;

        if (is_scale_down)
            sub_read_size = cur_app_size / (uintptr_t) scale;
        else
            sub_read_size = cur_app_size * (uintptr_t) scale;

        DR_ASSERT((size_t) (total_read_size + sub_read_size) <= shadow_size);

        uintptr_t result_buf = result_base_buf + total_read_size;
        DR_ASSERT(result_buf < result_base_buf + shadow_size);

        drmf_status_t status = umbra_func(map, (app_pc) cur_app_addr,
                cur_app_size, (size_t *) &sub_read_size,
                (byte *) result_base_buf);
        DR_ASSERT(status == DRMF_SUCCESS);

        if (sub_read_size == 0) {
            /* TODO: Found unaligned inner byte access. */
            return;
        }

        total_read_size += sub_read_size;

        if (is_scale_down)
            cur_app_addr += sub_read_size * (uintptr_t) scale;
        else
            cur_app_addr += sub_read_size / (uintptr_t) scale;
    }

    DR_ASSERT((size_t) total_read_size <= shadow_size);
}

void tb_umbra_safe_read(void *map_opaque, uintptr_t addr, size_t app_size,
        size_t shadow_size, uintptr_t result_buf) {

    tb_umbra_safe(map_opaque, addr, app_size, shadow_size, result_buf,
            umbra_read_shadow_memory);
}

void tb_umbra_safe_write(void *map_opaque, uintptr_t addr, size_t app_size,
        size_t shadow_size, uintptr_t src_buf) {

    tb_umbra_safe(map_opaque, addr, app_size, shadow_size, src_buf,
            umbra_write_shadow_memory);
}

void *tb_umbra_set_taint_mem_and_get_old(void *map_opaque, uintptr_t addr,
        void *label, bool *success) {

    umbra_map_t * map = (umbra_map_t *) map_opaque;

    void *old_label = NULL;

    size_t size = sizeof(void *);

    tb_umbra_safe_read(map, (uintptr_t) addr, 1, size, (uintptr_t) &old_label);

    if (old_label != label) {
        tb_umbra_safe_write(map, addr, 1, size, (uintptr_t) &label);
    }

    *success = true;

    return old_label;
}

void tb_umbra_set_taint_mem_block_and_get_old(void *map_opaque,
        uintptr_t start_addr, size_t block_size, void **new_shadow_buf,
        void **old_shadow_buf, size_t shadow_buf_size) {

    shadow_buf_size = shadow_buf_size * sizeof(void *);

    umbra_map_t *map = (umbra_map_t *) map_opaque;

    tb_umbra_safe_read(map, (uintptr_t) start_addr, block_size, shadow_buf_size,
            (uintptr_t) old_shadow_buf);

    /* Set */
    tb_umbra_safe_write(map, start_addr, block_size, shadow_buf_size,
            (uintptr_t) new_shadow_buf);
}

void *tb_umbra_set_untaint_mem_and_get_old(void *map_opaque, uintptr_t addr,
        bool *success) {

    umbra_map_t *map = (umbra_map_t *) map_opaque;

    void *old_label = NULL;
    size_t size = sizeof(void *);

    tb_umbra_safe_read(map, (uintptr_t) addr, 1, size, (uintptr_t) &old_label);

    if (old_label != NULL) {
        void *untaint_val = NULL;
        tb_umbra_safe_write(map, addr, 1, size, (uintptr_t) &untaint_val);
    }

    *success = true;

    return old_label;
}

void tb_umbra_set_untaint_mem_block_and_get_old(void *map_opaque,
        uintptr_t start_addr, size_t block_size, void **old_shadow_buf,
        size_t shadow_buf_size) {

    umbra_map_t *map = (umbra_map_t *) map_opaque;

    size_t shadow_size_out = shadow_buf_size * sizeof(void *);

    /* Read */
    tb_umbra_safe_read(map, (uintptr_t) start_addr, block_size, shadow_size_out,
            (uintptr_t) old_shadow_buf);

    /* Check if there are any taint labels */
    bool found = false;
    for (size_t i = 0; i < shadow_buf_size; i++) {

        if (old_shadow_buf[i] != NULL) {
            found = true;
            break;
        }
    }

    if (found) {
        /* Set */

        /* May not be safe, but we will assert if we encounter */
        drmf_status_t status = umbra_shadow_set_range(map, (app_pc) start_addr,
                block_size, &shadow_size_out, 0, 1);
        DR_ASSERT(status == DRMF_SUCCESS);
        DR_ASSERT(shadow_size_out == (shadow_buf_size * sizeof(void *)));
    }
}

void *tb_umbra_get_mem_taint_label(void *map_opaque, uintptr_t addr) {

    umbra_map_t *map = (umbra_map_t *) map_opaque;

    void *taint_label;

    size_t size = sizeof(void *);
    drmf_status_t status = umbra_read_shadow_memory(map, (app_pc) addr, 1,
            &size, (byte *) &taint_label);
    DR_ASSERT(status == DRMF_SUCCESS);

    DR_ASSERT(size == sizeof(void *));

#ifdef DEBUG
    DR_ASSERT(status == DRMF_SUCCESS);
#endif

    return taint_label;
}

void tb_umbra_get_mem_taint_block_labels(void *map_opaque, uintptr_t addr,
        size_t block_size, size_t label_buf_size, void **label_buf) {

    umbra_map_t *map = (umbra_map_t *) map_opaque;

    tb_umbra_safe_read(map, (uintptr_t) addr, block_size, label_buf_size,
            (uintptr_t) label_buf);
}
