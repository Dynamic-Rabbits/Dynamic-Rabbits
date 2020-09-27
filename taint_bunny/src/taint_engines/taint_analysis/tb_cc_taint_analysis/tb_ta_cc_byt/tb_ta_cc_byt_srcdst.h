/*
 * tb_ta_cc_byt_srcdst.h
 *
 *  Created on: 16 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRCDST_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRCDST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

/**************************************************************
 * SRCDST DREG
 */

void tb_cc_byt_handle_srcdst_dsreg_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsreg_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsreg_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsreg_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsreg_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);

/**************************************************************
 * SRCDST DREG (WHOLE)
 */

void tb_cc_byt_handle_srcdst_whole_dsreg_1(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsreg_2(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsreg_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsreg_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsreg_16(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);


/**************************************************************
 * SRCDST DMEM
 */

void tb_cc_byt_handle_srcdst_dsmem_1(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsmem_2(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsmem_4(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsmem_8(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_dsmem_16(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst_reg_id);

/**************************************************************
 * SRCDST DMEM (WHOLE)
 */

void tb_cc_byt_handle_srcdst_whole_dsmem_1(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsmem_2(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsmem_4(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsmem_8(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);
void tb_cc_byt_handle_srcdst_whole_dsmem_16(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        uintptr_t srcdst_reg_id);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRCDST_H_ */
