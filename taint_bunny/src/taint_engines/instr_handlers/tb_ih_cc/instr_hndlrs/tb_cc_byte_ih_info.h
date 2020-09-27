/*
 * tb_cc_cache_byte_oapprox.h
 *
 *  Created on: 16 Sep 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_CACHE_TB_CACHE_BYTE_OAPPROX_TB_CC_CACHE_BYTE_OAPPROX_OLD_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_CACHE_TB_CACHE_BYTE_OAPPROX_TB_CC_CACHE_BYTE_OAPPROX_OLD_H_

#include "../../tb_instruction_handler.h"

void tb_ih_cc_init_hndle_info(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque);

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_CACHE_TB_CACHE_BYTE_OAPPROX_TB_CC_CACHE_BYTE_OAPPROX_OLD_H_ */
