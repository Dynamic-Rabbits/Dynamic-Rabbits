/*
 * tb_simd_byt_instr_hndlrs.h
 *
 *  Created on: 5 Feb 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_INSTR_HANDLERS_TB_IH_SIMD_SIMD_INSTR_HNDLRS_TB_SIMD_BYT_INSTR_HNDLRS_H_
#define TAINT_ENGINES_INSTR_HANDLERS_TB_IH_SIMD_SIMD_INSTR_HNDLRS_TB_SIMD_BYT_INSTR_HNDLRS_H_


#include "../../tb_instruction_handler.h"

/* SRC SRCDST */
void tb_simd_byt_execute_src_srcdst_dreg_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_srcdst_dreg_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_srcdst_dmem_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dmem_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dmem_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dmem_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_srcdst_dmem_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/*****************************************************************************
 * SRC SRCDST (WHOLE)
 */

void tb_simd_byt_execute_whole_src_srcdst_dreg_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_whole_src_srcdst_dreg_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_whole_src_srcdst_dmem_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dmem_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dmem_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dmem_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_src_srcdst_dmem_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/* P SRC SRCDST */
void tb_simd_byt_execute_pb_src_srcdst_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pb_src_srcdst_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pb_src_srcdst_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pb_src_srcdst_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pw_src_srcdst_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pw_src_srcdst_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pw_src_srcdst_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pw_src_srcdst_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pd_src_srcdst_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pd_src_srcdst_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pd_src_srcdst_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pd_src_srcdst_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pq_src_srcdst_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pq_src_srcdst_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pq_src_srcdst_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pq_src_srcdst_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PMADDWD **/
void tb_simd_byt_execute_pmaddwd_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pmaddwd_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pmaddwd_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pmaddwd_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/* Same SRC/DST */

void tb_simd_byt_execute_whole_srcdst_dsreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_srcdst_dsreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_whole_srcdst_dsmem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsmem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsmem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsmem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_srcdst_dsmem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_srcdst_dsmem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsmem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsmem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsmem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_srcdst_dsmem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PUSH **/
void tb_simd_byt_execute_push_dmem_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_push_dmem_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_push_dmem_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_push_dmem_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_push_dmem_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_push_dmem_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_push_dmem_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_push_dmem_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** POP **/

void tb_simd_byt_execute_pop_dreg_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pop_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pop_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pop_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/******************************************************************************
 * SRC SRC DST
 */

void tb_simd_byt_execute_src_src_dst_whole_dreg_2_sreg_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_src_dst_whole_dreg_2_smem_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_src_dst_whole_dreg_4_sreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_src_dst_whole_dreg_4_sreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_src_dst_whole_dreg_8_sreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_src_dst_whole_dreg_8_sreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/***********************************************************************
 *  SRC SRC DST DST
 **/

void tb_simd_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);


/** SRC SRC DST DST DST **/

void tb_simd_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_smem_4_sreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_src_src_dst_dst_dreg_1_dreg_1_smem_1_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_src_src_dst_dst_dreg_1_dreg_1_sreg_1_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** SRC DST (WHOLE) **/
void tb_simd_byt_execute_whole_mov_dmem_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dmem_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dmem_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dmem_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dmem_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_whole_mov_dreg_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_whole_mov_dreg_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_mov_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_whole_high_mov_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_whole_high_mov_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** SRC DST **/
void tb_simd_byt_execute_mov_dmem_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_mov_dreg_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_mov_dmem_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dmem_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_mov_dreg_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_mov_dmem_8_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_mov_dreg_16_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** LEA **/

void tb_simd_byt_execute_lea_dreg_2_sreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_lea_dreg_4_sreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_lea_dreg_8_sreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_base_lea_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_base_lea_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_base_lea_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_index_lea_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_index_lea_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_index_lea_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** XCHG **/
void tb_simd_byt_execute_xchg_reg_1_reg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_reg_2_reg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_reg_4_reg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_reg_8_reg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_xchg_reg_1_mem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_reg_2_mem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_reg_4_mem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_reg_8_mem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_xchg_mem_1_reg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_mem_2_reg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_mem_4_reg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xchg_mem_8_reg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** XADD **/
void tb_simd_byt_execute_xadd_reg_1_reg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xadd_reg_2_reg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xadd_reg_4_reg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xadd_reg_8_reg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_xadd_mem_1_reg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xadd_mem_2_reg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xadd_mem_4_reg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_xadd_mem_8_reg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** LEAVE **/
void tb_simd_byt_execute_leave_dreg_4_sreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_leave_dreg_8_sreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** CMOV **/
void tb_simd_byt_execute_cmovb_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovb_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovb_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovb_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovb_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovb_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovnb_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnb_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnb_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovnb_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnb_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnb_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovbe_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovbe_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovbe_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovbe_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovbe_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovbe_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovnbe_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnbe_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnbe_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovnbe_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnbe_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnbe_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovo_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovo_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovo_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovo_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovo_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovo_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovno_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovno_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovno_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovno_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovno_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovno_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovp_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovp_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovp_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovp_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovp_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovp_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovnp_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnp_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnp_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovnp_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnp_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovnp_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovs_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovs_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovs_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovs_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovs_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovs_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovns_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovns_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovns_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovns_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovns_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovns_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmove_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmove_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmove_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmove_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmove_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmove_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovne_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovne_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovne_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovne_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovne_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovne_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovg_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovg_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovg_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovg_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovg_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovg_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovge_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovge_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovge_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovge_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovge_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovge_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovl_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovl_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovl_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovl_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovl_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovl_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovle_dreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovle_dreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovle_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmovle_dreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovle_dreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmovle_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PUNP **/
void tb_simd_byt_execute_punpcklbw_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpcklbw_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpcklbw_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpcklbw_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_punpcklwd_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpcklwd_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpcklwd_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpcklwd_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_punpckldq_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckldq_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckldq_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckldq_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_packswb_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_packswb_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_packswb_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_packswb_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_packsdw_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_packsdw_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_packsdw_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_packsdw_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PCMP **/
void tb_simd_byt_execute_pcmpb_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpb_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpb_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpb_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pcmpw_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpw_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpw_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpw_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pcmpd_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpd_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpd_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpd_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pcmpq_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpq_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpq_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pcmpq_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PUNPCK **/
void tb_simd_byt_execute_punpckhbw_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhbw_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhbw_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhbw_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_punpckhwd_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhwd_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhwd_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhwd_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_punpckhdq_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhdq_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhdq_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhdq_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_punpcklqdq_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpcklqdq_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_punpckhqdq_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_punpckhqdq_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** SHIFTD **/
void tb_simd_byt_execute_shift_dsmem_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_shift_dsmem_2_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_shift_dsmem_4_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_shift_dsmem_8_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_shift_dsreg_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_shift_dsreg_2_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_shift_dsreg_4_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_shift_dsreg_8_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_shiftd_dreg_2_sreg_2_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_shiftd_dreg_4_sreg_4_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_shiftd_dreg_8_sreg_8_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_shiftd_dmem_2_sreg_2_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_shiftd_dmem_4_sreg_4_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_shiftd_dmem_8_sreg_8_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** CMPXCHG **/

void tb_simd_byt_execute_cmpxchg_sreg_1_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmpxchg_sreg_2_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmpxchg_sreg_4_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmpxchg_sreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_cmpxchg_sreg_1_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmpxchg_sreg_2_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmpxchg_sreg_4_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_cmpxchg_sreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** MOVZX **/
void tb_simd_byt_execute_movzx_dreg_2_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_4_sreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_4_sreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_8_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_16_sreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_16_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_movzx_dreg_2_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_4_smem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_4_smem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_8_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_16_smem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_movzx_dreg_16_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PEXT **/
void tb_simd_byt_execute_pextb_dreg_4_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pextb_dmem_1_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pextw_dreg_4_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pextw_dreg_4_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pextw_dmem_2_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pextd_dreg_4_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pextd_dmem_4_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pextq_dmem_8_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** BSWAP **/
void tb_simd_byt_execute_bswap_dsreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_bswap_dsreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_bswap_dsmem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_bswap_dsmem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PMOVMSK **/
void tb_simd_byt_execute_pmovmsk_dreg_4_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pmovmsk_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pmovmsk_dreg_4_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pmovmsk_dreg_8_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** PMINMAX **/
void tb_simd_byt_execute_pminmaxb_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxb_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxb_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxb_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pminmaxw_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxw_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxw_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxw_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_pminmaxd_dreg_8_smem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxd_dreg_8_sreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxd_dreg_16_smem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_pminmaxd_dreg_16_sreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** REP **/
void tb_simd_byt_execute_rep_movsb(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_rep_movsw(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_rep_movsd(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_rep_movsq(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_rep_stosb(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_rep_stosw(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_rep_stosd(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_rep_stosq(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

/** UNTAINT **/
void tb_simd_byt_execute_untaint_dreg_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dreg_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dreg_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dreg_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dreg_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_untaint_first_2_dregs_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_2_dregs_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_2_dregs_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_2_dregs_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_2_dregs_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_untaint_first_3_dregs_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_3_dregs_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_3_dregs_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_3_dregs_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_3_dregs_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_untaint_first_4_dregs_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_4_dregs_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_4_dregs_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_4_dregs_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_first_4_dregs_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_untaint_dmem_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dmem_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dmem_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dmem_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dmem_16(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_untaint_dmem_2nd_1(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dmem_2nd_2(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dmem_2nd_4(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);
void tb_simd_byt_execute_untaint_dmem_2nd_8(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);

void tb_simd_byt_execute_untaint_dreg_untaint_1st_sub_3rd_4th(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data);


#endif /* TAINT_ENGINES_INSTR_HANDLERS_TB_IH_SIMD_SIMD_INSTR_HNDLRS_TB_SIMD_BYT_INSTR_HNDLRS_H_ */
