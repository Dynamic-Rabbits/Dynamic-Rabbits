/*
 * tb_raw_execution.h
 *
 *  Created on: 20 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_RAW_INSTR_HNDLRS_TB_RAW_EXECUTION_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_RAW_INSTR_HNDLRS_TB_RAW_EXECUTION_H_

#include "../../../tb_bunny_private.h"
#include "../spill.h"

typedef void (*tb_raw_byt_handle_src_srcdst_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg, reg_id_t srcdst_reg, tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_srcdst_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg, tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_src_srcdst_dst_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg, reg_id_t srcdst_reg, reg_id_t dst_reg,
        tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_src_src_dst_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg, reg_id_t src_reg2, reg_id_t dst_reg,
        tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_src_srcdst_srcdst_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg, reg_id_t srcdst_reg, reg_id_t srcdst_reg2,
        tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_src_dst_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t src_reg, reg_id_t dst_reg, tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_src_dst_func_ex_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_xchg_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg, reg_id_t srcdst_reg2, tb_spill_info_t *spill_info);

typedef void (*tb_raw_byt_handle_untaint_func_t)(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t dst_reg, tb_spill_info_t *spill_info);

typedef void tb_raw_byte_handle_untaint_reg_ex_func_t(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t start, size_t end,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t reg_id_untaint, tb_spill_info_t *spill_info);

/***********************************************************************
 * SRC SRCDST
 */

void tb_raw_execute_src_srcdst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_srcdst_func_t src_srcdst_func);

/***********************************************************************
 * SRCDST
 */

void tb_raw_execute_srcdst_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_srcdst_func_t srcdst_func);

/***************************************************************************************************
 * SRC SRC DST DST
 */

void tb_raw_execute_src_srcdst_dst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_srcdst_dst_func_t src_srcdst_dst_func);

/***************************************************************************************************
 * SRC SRC DST
 */

void tb_raw_execute_src_src_dst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_src_dst_func_t srcdst_func);

/***************************************************************************************************
 * SRC SRCDST SRCDST
 */

void tb_raw_execute_src_srcdst_srcdst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_srcdst_srcdst_func_t src_srcdst_srcdst_func);

/***************************************************************************************************
 * SRC DST
 */

void tb_raw_execute_src_dst_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func);

void tb_raw_execute_pop_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func);

void tb_raw_execute_push_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func);

/***************************************************************************************************
 * LEA instructions
 */

void tb_raw_execute_lea_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_src_dst_func_t src_src_dst_func);
void tb_raw_execute_lea_base_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func);

void tb_raw_execute_lea_index_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func);

/***************************************************************************************************
 * REP
 */

void tb_raw_execute_rep_movs(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_ex_t src_dst_func);

void tb_raw_execute_rep_stos(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_ex_t src_dst_func);

/***************************************************************************************************
 * EXECUTE LEAVE
 */

void tb_raw_execute_leave_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func_reg_reg,
        tb_raw_byt_handle_src_dst_func_t src_dst_func_reg_mem);

/***************************************************************************************************
 * EXECUTE XCHG
 */

void tb_raw_execute_xchg_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_xchg_func_t xchg_func_reg_reg);

void tb_raw_execute_cmpxchg_consider_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t taken_mov_func);

void tb_raw_execute_cmpxchg_no_consider_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t not_taken_mov_func);

/*******************************************************************************
 * Untaint
 */

void tb_raw_execute_untaint_first_n_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, int n, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_untaint_func_t untaint_func);

void tb_raw_execute_untaint_sub_byte_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t index,
        size_t sub_start, size_t sub_end, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, tb_spill_info_t *spill_info,
        tb_raw_byte_handle_untaint_reg_ex_func_t untaint_func_ex);

void tb_raw_execute_push_immed_untaint_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_untaint_func_t untaint_func);

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_RAW_RAW_INSTR_HNDLRS_TB_RAW_EXECUTION_H_ */
