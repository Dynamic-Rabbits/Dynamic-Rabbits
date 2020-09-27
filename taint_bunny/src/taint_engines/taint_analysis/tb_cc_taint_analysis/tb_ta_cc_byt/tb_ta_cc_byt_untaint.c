/*
 * tb_ta_untaint_cleancall.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_untaint.h"

#include "../tb_ta_cc_byt_functionality.h"
#include "../../../../tb_bunny_private.h"
#include "../../../../tls_access/tb_tls_access.h"
#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#include "utility_bunny.h"

#include <stdint.h>

static void tb_cc_handle_hp_untaint_reg(tb_context_t *tb_ctx, size_t size,
        unsigned int reg_byte_id) {

    void *reg_map = tb_get_reg_map(tb_ctx);

    for (size_t i = 0; i < size; i++) {
        tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, reg_byte_id + i);
    }
}

void tb_cc_byt_handle_untaint_reg_1(void *tb_ctx,
        unsigned int reg_byte_id) {

    tb_cc_handle_hp_untaint_reg(tb_ctx, 1, reg_byte_id);
}

void tb_cc_byt_handle_untaint_reg_2(void *tb_ctx,
        unsigned int reg_byte_id) {

    tb_cc_handle_hp_untaint_reg(tb_ctx, 2, reg_byte_id);
}

void tb_cc_byt_handle_untaint_reg_4(void *tb_ctx,
        unsigned int reg_byte_id) {

    tb_cc_handle_hp_untaint_reg(tb_ctx, 4, reg_byte_id);
}

void tb_cc_byt_handle_untaint_reg_8(void *tb_ctx,
        unsigned int reg_byte_id) {

    tb_cc_handle_hp_untaint_reg(tb_ctx, 8, reg_byte_id);
}

void tb_cc_byt_handle_untaint_reg_16(void *tb_ctx,
         unsigned int reg_byte_id) {

    tb_cc_handle_hp_untaint_reg(tb_ctx, 16, reg_byte_id);
}

static void tb_cc_handle_hp_untaint_mem(tb_context_t *tb_ctx, size_t size,
        uintptr_t addr) {

    for (size_t i = 0; i < size; i++) {
        tb_ta_cc_set_untaint_mem(tb_ctx, addr + i);
    }
}

void tb_cc_byt_handle_untaint_mem_1(void *tb_ctx, uintptr_t addr) {

    tb_cc_handle_hp_untaint_mem(tb_ctx, 1, addr);
}

void tb_cc_byt_handle_untaint_mem_2(void *tb_ctx, uintptr_t addr) {

    tb_cc_handle_hp_untaint_mem(tb_ctx, 2, addr);
}

void tb_cc_byt_handle_untaint_mem_4(void *tb_ctx, uintptr_t addr) {

    tb_cc_handle_hp_untaint_mem(tb_ctx, 4, addr);
}

void tb_cc_byt_handle_untaint_mem_8(void *tb_ctx, uintptr_t addr) {

    tb_cc_handle_hp_untaint_mem(tb_ctx, 8, addr);
}

void tb_cc_byt_handle_untaint_mem_16(void *tb_ctx, uintptr_t addr) {

    tb_cc_handle_hp_untaint_mem(tb_ctx, 16, addr);
}
