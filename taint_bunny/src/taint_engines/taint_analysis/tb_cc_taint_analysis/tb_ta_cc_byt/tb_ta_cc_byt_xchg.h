/*
 * tb_ta_cc_byt_xchg.h
 *
 *  Created on: 16 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_XCHG_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_XCHG_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/*****************************************************************************
 * XCHG SRCDST SRCDST - DREG DREG
 */

void tb_cc_byt_handle_xchg_reg_1_reg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);
void tb_cc_byt_handle_xchg_reg_2_reg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);
void tb_cc_byt_handle_xchg_reg_4_reg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);
void tb_cc_byt_handle_xchg_reg_8_reg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);

/*****************************************************************************
 * XCHG SRCDST SRCDST - DMEM DREG
 */

void tb_cc_byt_handle_xchg_mem_1_reg_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2);
void tb_cc_byt_handle_xchg_mem_2_reg_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2);
void tb_cc_byt_handle_xchg_mem_4_reg_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2);
void tb_cc_byt_handle_xchg_mem_8_reg_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t addr_id1,
        uintptr_t reg_id2);

/*****************************************************************************
 * XCHG SRCDST SRCDST - DREG DMEM
 */

void tb_cc_byt_handle_xchg_reg_1_mem_1(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2);
void tb_cc_byt_handle_xchg_reg_2_mem_2(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2);
void tb_cc_byt_handle_xchg_reg_4_mem_4(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2);
void tb_cc_byt_handle_xchg_reg_8_mem_8(
        tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t mem_id2);

/********************************************************************
 * BSWAP SRCDST - DREG
 */

void tb_cc_byt_handle_bswap_dsreg_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);

void tb_cc_byt_handle_bswap_dsreg_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);

/********************************************************************
 * BSWAP SRCDST - DMEM
 */

void tb_cc_byt_handle_bswap_dsmem_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);

void tb_cc_byt_handle_bswap_dsmem_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);

/********************************************************************
 * XADD - REG REG
 */

void tb_cc_byt_handle_xadd_reg_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);

void tb_cc_byt_handle_xadd_reg_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);

void tb_cc_byt_handle_xadd_reg_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);

void tb_cc_byt_handle_xadd_reg_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t reg_id1,
        uintptr_t reg_id2);

/*****************************************************************************
 * XADD - MEM REG
 */

void tb_cc_byt_handle_xadd_mem_1_reg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id,
        uintptr_t reg_id);
void tb_cc_byt_handle_xadd_mem_2_reg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id,
        uintptr_t reg_id);
void tb_cc_byt_handle_xadd_mem_4_reg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id,
        uintptr_t reg_id);
void tb_cc_byt_handle_xadd_mem_8_reg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t mem_id,
        uintptr_t reg_id);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_XCHG_H_ */
