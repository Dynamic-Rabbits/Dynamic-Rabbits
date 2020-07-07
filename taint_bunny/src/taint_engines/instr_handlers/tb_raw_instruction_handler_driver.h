/*
 * tb_max6_instruction_handler_driver.h
 *
 *  Created on: 21 Jul 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_MAX6_INSTRUCTION_HANDLER_DRIVER_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_MAX6_INSTRUCTION_HANDLER_DRIVER_H_

#include "tb_instruction_handler.h"
#include "../../tb_bunny_private.h"

tb_te_instr_hndlrs_t *tb_ih_raw_init_instr_handlers(tb_context_t *tb_ctx,
        tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info);

void tb_ih_raw_destroy_instr_hndlrs(tb_te_instr_hndlrs_t * instr_hndlrs);

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_MAX6_INSTRUCTION_HANDLER_DRIVER_H_ */
