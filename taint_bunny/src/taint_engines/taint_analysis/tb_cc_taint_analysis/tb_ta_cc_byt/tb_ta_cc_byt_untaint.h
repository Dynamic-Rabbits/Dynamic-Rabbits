/*
 * tb_ta_untaint_cleancall.h
 *
 *  Created on: 7 May 2018
 *      Author: john
 */

#ifndef TAINT_ANALYSIS_TB_TA_UNTAINT_CLEANCALL_H_
#define TAINT_ANALYSIS_TB_TA_UNTAINT_CLEANCALL_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

void tb_cc_byt_handle_untaint_mem_1(void *tb_ctx, uintptr_t addr);
void tb_cc_byt_handle_untaint_mem_2(void *tb_ctx, uintptr_t addr);
void tb_cc_byt_handle_untaint_mem_4(void *tb_ctx, uintptr_t addr);
void tb_cc_byt_handle_untaint_mem_8(void *tb_ctx, uintptr_t addr);
void tb_cc_byt_handle_untaint_mem_16(void *tb_ctx, uintptr_t addr);

void tb_cc_byt_handle_untaint_reg_1(void *tb_ctx, unsigned int reg_byte_id);
void tb_cc_byt_handle_untaint_reg_2(void *tb_ctx, unsigned int reg_byte_id);
void tb_cc_byt_handle_untaint_reg_4(void *tb_ctx, unsigned int reg_byte_id);
void tb_cc_byt_handle_untaint_reg_8(void *tb_ctx, unsigned int reg_byte_id);
void tb_cc_byt_handle_untaint_reg_16(void *tb_ctx, unsigned int reg_byte_id);

#endif /* TAINT_ANALYSIS_TB_TA_UNTAINT_CLEANCALL_H_ */
