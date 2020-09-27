/*
 * tb_cc_instr_hndlr_helper.h
 *
 *  Created on: 15 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_HELPERS_TB_CC_INSTR_HNDLR_HELPER_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_HELPERS_TB_CC_INSTR_HNDLR_HELPER_H_

#include "../../../../tb_bunny_private.h"

/***********************************************************************
 * SRC SRCDST
 */

void tb_cc_execute_src_srcdst_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_srcdst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst,
                uintptr_t src));

/***********************************************************************
 * SRCDST
 */

void tb_cc_execute_srcdst_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_srcdst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst));

/***************************************************************************************************
 * SRC SRC DST DST
 */

void tb_cc_execute_src_srcdst_dst_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_src_dst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t srcdst2, uintptr_t src1));

/***************************************************************************************************
 * SRC SRC DST
 */

void tb_cc_execute_src_src_dst_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_src_dst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t src1, uintptr_t src2));

/***************************************************************************************************
 * SRC SRCDST SRCDST
 */

void tb_cc_execute_src_srcdst_srcdst_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_arith_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst,
                uintptr_t srcdst2, uintptr_t src1));

/***************************************************************************************************
 * SRC DST
 */

void tb_cc_execute_src_dst_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_rep_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id));

void tb_cc_execute_pop_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_pop_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id));

void tb_cc_execute_push_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_push_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id));

/***************************************************************************************************
 * LEA instructions
 */

void tb_cc_execute_lea_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_lea_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst, uintptr_t src1, uintptr_t src2));

void tb_cc_execute_lea_base_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_lea_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst, uintptr_t src1));

void tb_cc_execute_lea_index_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_arith_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst,
                uintptr_t src1));

/***************************************************************************************************
 * REP
 */

bool tb_cc_dir_check_flag();

void tb_cc_execute_rep_movs_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size,
        void (*execute_rep_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id));

void tb_cc_execute_rep_stos_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size,
        void (*execute_rep_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id));

/***************************************************************************************************
 * Conditional
 */

bool tb_cc_cmovb_check_flag();
bool tb_cc_cmovnb_check_flag();
bool tb_cc_cmovbe_check_flag();
bool tb_cc_cmovnbe_check_flag();
bool tb_cc_cmovo_check_flag();
bool tb_cc_cmovno_check_flag();
bool tb_cc_cmovp_check_flag();
bool tb_cc_cmovnp_check_flag();
bool tb_cc_cmovs_check_flag();
bool tb_cc_cmovns_check_flag();
bool tb_cc_cmove_check_flag();
bool tb_cc_cmovne_check_flag();
bool tb_cc_cmovg_check_flag();
bool tb_cc_cmovge_check_flag();
bool tb_cc_cmovl_check_flag();
bool tb_cc_cmovle_check_flag();

/***************************************************************************************************
 * EXECUTE LEAVE
 */

void tb_cc_execute_leave_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_dst_reg_reg_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t src),
        void (*execute_src_dst_reg_mem_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t src));

/***************************************************************************************************
 * EXECUTE XCHG
 */

void tb_cc_execute_xchg_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_xchg_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t srcdst1, uintptr_t srcdst2));

void tb_cc_execute_cmpxchg_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        size_t size,
        void (*execute_mov_handler_not_taken)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_addr,
                uintptr_t src_reg_id),
        void (*execute_mov_handler_taken)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_addr,
                uintptr_t src_reg_id));

/***************************************************************************************************
 * Unsupported
 */

void tb_cc_execute_unsup_instr(void *instr_hndlr_info,
        void (*execute_untaint_reg_handler)(void *tb_ctx_opaque,
                uintptr_t dst_reg),
        void (*execute_untaint_mem_handler)(void *tb_ctx_opaque,
                uintptr_t dst_addr));

/***************************************************************************************************
 * UNTAINT
 */

void tb_cc_execute_untaint_first_n_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, int n,
        void (*execute_untaint_handler)(void *tb_ctx_opaque,
                uintptr_t dst_addr));

void tb_cc_execute_untaint_sub_byte_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, size_t index,
        size_t sub_start, size_t sub_end,
        void (*execute_untaint_handler)(void *tb_ctx_opaque,
                uintptr_t dst_addr));

void tb_cc_execute_push_immed_untaint_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_untaint_handler)(void *tb_ctx_opaque,
                uintptr_t dst_addr));

#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_CC_HELPERS_TB_CC_INSTR_HNDLR_HELPER_H_ */
