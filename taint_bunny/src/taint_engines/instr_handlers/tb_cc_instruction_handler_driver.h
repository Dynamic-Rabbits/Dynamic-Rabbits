/*
 * taint_engine.h
 *
 *  Created on: 4 Jul 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ENGINE_H_
#define TAINT_ENGINES_TAINT_ENGINE_H_

#include "tb_instruction_handler.h"
#include "../../tb_bunny_private.h"

tb_te_instr_hndlrs_t *tb_ih_cc_init_instr_handlers(tb_context_t *tb_ctx,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info);

void tb_ih_cc_destroy_instr_hndlrs(tb_te_instr_hndlrs_t * instr_hndlrs);

#endif /* TAINT_ENGINES_TAINT_ENGINE_H_ */
