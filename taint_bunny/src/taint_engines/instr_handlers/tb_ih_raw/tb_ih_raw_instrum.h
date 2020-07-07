/*
 * tb_ih_raw_instrum.h
 *
 *  Created on: 20 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_TB_IH_RAW_INSTRUM_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_TB_IH_RAW_INSTRUM_H_

#include "../tb_instruction_handler.h"

void tb_ih_raw_cache_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque);

void tb_ih_raw_in_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque);

void tb_ih_simd_cache_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque);

void tb_ih_simd_in_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info, void *tb_ctx_opaque);

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_TB_IH_RAW_INSTRUM_H_ */
