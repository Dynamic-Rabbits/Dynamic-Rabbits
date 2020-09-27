/*
 * tb_simd_byte_ih_info.h
 *
 *  Created on: 5 Feb 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_SIMD_SIMD_INSTR_HNDLRS_TB_SIMD_BYTE_IH_INFO_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_SIMD_SIMD_INSTR_HNDLRS_TB_SIMD_BYTE_IH_INFO_H_

#include "../../tb_instruction_handler.h"

void tb_ih_simd_init_hndle_info(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque);

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_SIMD_SIMD_INSTR_HNDLRS_TB_SIMD_BYTE_IH_INFO_H_ */
