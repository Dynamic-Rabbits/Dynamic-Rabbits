/*
 * te_cc_shadow_reg_map.h
 *
 *  Created on: 8 Jul 2018
 *      Author: john
 */

#ifndef TAINT_MAPS_REGISTER_MAP_TB_CC_REG_MAPS_TB_CC_SHADOW_REG_MAPS_TB_CC_SHADOW_REG_MAP_H_
#define TAINT_MAPS_REGISTER_MAP_TB_CC_REG_MAPS_TB_CC_SHADOW_REG_MAPS_TB_CC_SHADOW_REG_MAP_H_

#include "instrumentation_bunny.h"

void tb_cc_arraymap_init_reg_map(client_id_t client_id);

void tb_cc_arraymap_exit_reg_map();

void *tb_cc_arraymap_create_reg_map(void *user_data, void **start);

void tb_cc_arraymap_destroy_reg_map(void *map_opaque, ub_destroy_value_func_t detroy_func, void *user_data);

void *tb_cc_arraymap_set_taint_reg_and_get_old(void *map_opaque,
		unsigned int reg_byte_id, void *label, bool *success);

void *tb_cc_arraymap_set_untaint_reg_and_get_old(void *map_opaque,
		unsigned int reg_byte_id, bool *success);

void *tb_cc_arraymap_get_reg_taint_label(void *map_opaque, unsigned int reg_byte_id);

#endif /* TAINT_MAPS_REGISTER_MAP_TB_CC_REG_MAPS_TB_CC_SHADOW_REG_MAPS_TB_CC_SHADOW_REG_MAP_H_ */
