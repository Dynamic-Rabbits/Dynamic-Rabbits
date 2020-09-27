/*
 * tb_shadow_reg_map.h
 *
 *  Created on: 11 Jul 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TAINT_MAPS_REGISTER_MAP_TB_CC_REG_MAPS_TB_SHADOW_REG_MAP_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TAINT_MAPS_REGISTER_MAP_TB_CC_REG_MAPS_TB_SHADOW_REG_MAP_H_

#include "dr_api.h"
#include "dr_defines.h"

//Todo calculate this more accurately.
#define REG_MAX_VAL ((DR_REG_YMM15 + 1) * 16)


typedef struct {

	void *reg_map[REG_MAX_VAL];
} tb_map_reg_map_t;



#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TAINT_MAPS_REGISTER_MAP_TB_CC_REG_MAPS_TB_SHADOW_REG_MAP_H_ */
