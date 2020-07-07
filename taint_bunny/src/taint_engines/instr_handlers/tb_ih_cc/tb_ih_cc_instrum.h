/*
 * tb_ih_cc_instrum.h
 *
 *  Created on: 13 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_TB_IH_CC_INSTRUM_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_TB_IH_CC_INSTRUM_H_

#include "../tb_instruction_handler.h"

void tb_ih_cc_cache_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque);

void tb_ih_cc_in_init_instr_hndlrs(tb_te_instr_hndlrs_t *instr_hndlrs,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
        void *tb_ctx_opaque);

void tb_ih_cc_insert_unsupported_handle(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data);

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_TB_IH_CC_INSTRUM_H_ */
