/*
 * tb_ta_raw_byt_pack.h
 *
 *  Created on: 29 Jan 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_PACK_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_PACK_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../../../tb_bunny_private.h"

void tb_raw_byt_handle_pack_dreg_8_sreg_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_pack_dreg_16_sreg_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_reg_id,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_pack_dreg_8_smem_8_sreg_8(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info);

void tb_raw_byt_handle_pack_dreg_16_smem_16_sreg_16(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        reg_id_t srcdst_reg_id, reg_id_t src_mem_id,
        tb_spill_info_t *spill_info);

#endif /* TAINT_ENGINES_TAINT_ANALYSIS_TB_RAW_TAINT_ANALYSIS_TB_TA_RAW_BYT_TB_TA_RAW_BYT_PACK_H_ */
