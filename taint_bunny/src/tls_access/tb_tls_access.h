/*
 * tb_tls_access.h
 *
 *  Created on: 17 Aug 2018
 *      Author: john
 */

#ifndef TLS_ACCESS_TB_TLS_ACCESS_H_
#define TLS_ACCESS_TB_TLS_ACCESS_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "../tb_bunny_private.h"
#include "drext.h"
#include <stdint.h>

#include "instrumentation_bunny.h"

/***************************************************************************
 *  Structs and Definitions
 */


#define TB_RAW_SLOT_IDX_MAP 0
#define TB_RAW_SLOT_IDX_ANALYSIS_SWITCH 1
#define TB_FP_SLOT_ADDR 2
#define TB_FP_SLOT_REG_STATE 3
#define TB_RAW_SLOT_IDX_PRE_PROP_CALLED 4
#define TB_RAW_SLOT_IDX_PRE_POST_PROP_LABEL 5

opnd_t tb_raw_get_tls_raw_slot_opnd(tb_context_t *tb_ctx, int slot_idx);

void *tb_get_reg_map(tb_context_t *tb_ctx);

void tb_set_reg_map(tb_context_t *tb_ctx, void *reg_map);

void *tb_get_analysis_switch(tb_context_t *tb_ctx);

void *tb_get_fp_address_spill(tb_context_t *tb_ctx);

void tb_set_reg_analysis_switch(tb_context_t *tb_ctx, bool analysis_switch);

uint32_t tb_get_fp_reg_state(tb_context_t *tb_ctx);

void tb_set_fp_reg_state(tb_context_t *tb_ctx, uint32_t reg_state);

#endif /* TLS_ACCESS_TB_TLS_ACCESS_H_ */
