/*
 * tb_raw_byte_ih_info.h
 *
 *  Created on: 20 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_RAW_INSTR_HNDLRS_TB_RAW_BYTE_IH_INFO_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_RAW_INSTR_HNDLRS_TB_RAW_BYTE_IH_INFO_H_

#include "../../tb_instruction_handler.h"

void tb_ih_raw_init_hndle_info(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info,
        tb_taint_prepost_info_t *post_info,  void *tb_ctx_opaque);


#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_RAW_INSTR_HNDLRS_TB_RAW_BYTE_IH_INFO_H_ */
