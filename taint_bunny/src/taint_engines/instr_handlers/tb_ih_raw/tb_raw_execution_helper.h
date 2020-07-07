/*
 * tb_raw_execution_helper.h
 *
 *  Created on: 27 Apr 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_TB_RAW_EXECUTION_HELPER_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_TB_RAW_EXECUTION_HELPER_H_

#include "../../../tb_bunny_private.h"
#include "../spill.h"

typedef void (*tb_raw_check_flg_t)(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
        reg_id_t scratch_reg);

typedef void (*tb_raw_check_flg_ex_t)(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
        reg_id_t low_scratch_reg, reg_id_t high_scratch_reg);

void tb_raw_execute_load_opnd_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        ub_opnd_access_t *slot, reg_id_t dst);

void tb_raw_execute_cmov(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        tb_spill_info_t *spill_info, tb_raw_check_flg_t flg_check_func,
        instr_t *consider_label, instr_t *done_label);

void tb_raw_execute_cmov_ex(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        tb_spill_info_t *spill_info, tb_raw_check_flg_ex_t flg_check_func,
        instr_t *consider_label, instr_t *done_label);

void tb_raw_execute_cmpxchg_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        size_t size, void *drcontext, instrlist_t *ilist, instr_t *where,
        tb_spill_info_t *spill_info, instr_t *consider_label,
        instr_t *no_consider_label, instr_t *done_label);

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_TB_RAW_EXECUTION_HELPER_H_ */
