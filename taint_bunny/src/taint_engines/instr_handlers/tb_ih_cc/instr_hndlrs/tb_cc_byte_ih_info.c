/*
 * te_cleancall.c
 *
 *      Author: john
 */

#include "tb_cc_byte_ih_info.h"

#include "../../../../tb_bunny_private.h"

#include "tb_cc_byt_instr_hndlrs.h"
#include "../../tb_instruction_handler.h"
#include "instrumentation_bunny.h"

void tb_ih_cc_init_hndle_info(tb_te_instr_hndlrs_t *instr_hndlrs,
		tb_taint_prepost_info_t *pre_info, tb_taint_prepost_info_t *post_info,
		void *tb_ctx_opaque) {

	tb_taint_prepost_info_t pre_info_null;
	tb_taint_prepost_info_t post_info_null;

	if (!pre_info) {
		memset(&pre_info_null, 0, sizeof(tb_taint_prepost_info_t));
		pre_info = &pre_info_null;
	}

	if (!post_info) {
		memset(&post_info_null, 0, sizeof(tb_taint_prepost_info_t));
		post_info = &post_info_null;
	}

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_smem_1,
							pre_info->add_dreg_1_smem_1_func,
							post_info->add_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_smem_2,
							pre_info->add_dreg_2_smem_2_func,
							post_info->add_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_smem_4,
							pre_info->add_dreg_4_smem_4_func,
							post_info->add_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->add_dreg_8_smem_8_func,
							post_info->add_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->add_dreg_1_simm_1_func,
							post_info->add_dreg_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->add_dreg_2_simm_2_func,
							post_info->add_dreg_2_simm_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->add_dreg_4_simm_4_func,
							post_info->add_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_sreg_1,
							pre_info->add_dreg_1_sreg_1_func,
							post_info->add_dreg_1_sreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_sreg_2,
							pre_info->add_dreg_2_sreg_2_func,
							post_info->add_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_sreg_4,
							pre_info->add_dreg_4_sreg_4_func,
							post_info->add_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->add_dreg_8_sreg_8_func,
							post_info->add_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_1_sreg_1,
							pre_info->add_dmem_1_sreg_1_func,
							post_info->add_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_2_sreg_2,
							pre_info->add_dmem_2_sreg_2_func,
							post_info->add_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_4_sreg_4,
							pre_info->add_dmem_4_sreg_4_func,
							post_info->add_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_8_sreg_8,
							pre_info->add_dmem_8_sreg_8_func,
							post_info->add_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->add_dmem_1_simm_1_func,
							post_info->add_dmem_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->add_dmem_2_simm_2_func,
							post_info->add_dmem_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->add_dmem_4_simm_4_func,
							post_info->add_dmem_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->add_dreg_2_simm_1_func,
							post_info->add_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->add_dreg_4_simm_1_func,
							post_info->add_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->add_dreg_8_simm_1_func,
							post_info->add_dreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->add_dmem_2_simm_1_func,
							post_info->add_dmem_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->add_dmem_4_simm_1_func,
							post_info->add_dmem_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADD_DMEM_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->add_dmem_8_simm_1_func,
							post_info->add_dmem_8_simm_1_func };

	/** OR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_1_smem_1,
							pre_info->or_dreg_1_smem_1_func,
							post_info->or_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_2_smem_2,
							pre_info->or_dreg_2_smem_2_func,
							post_info->or_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_4_smem_4,
							pre_info->or_dreg_4_smem_4_func,
							post_info->or_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_smem_8,
							pre_info->or_dreg_8_smem_8_func,
							post_info->or_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_1,
							pre_info->or_dreg_1_simm_1_func,
							post_info->or_dreg_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_2,
							pre_info->or_dreg_2_simm_2_func,
							post_info->or_dreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_4,
							pre_info->or_dreg_4_simm_4_func,
							post_info->or_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_1_sreg_1,
							pre_info->or_dreg_1_sreg_1_func,
							post_info->or_dreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_2_sreg_2,
							pre_info->or_dreg_2_sreg_2_func,
							post_info->or_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_4_sreg_4,
							pre_info->or_dreg_4_sreg_4_func,
							post_info->or_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->or_dreg_8_sreg_8_func,
							post_info->or_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_1_sreg_1,
							pre_info->or_dmem_1_sreg_1_func,
							post_info->or_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_2_sreg_2,
							pre_info->or_dmem_2_sreg_2_func,
							post_info->or_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_4_sreg_4,
							pre_info->or_dmem_4_sreg_4_func,
							post_info->or_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_8_sreg_8,
							pre_info->or_dmem_8_sreg_8_func,
							post_info->or_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_1,
							pre_info->or_dmem_1_simm_1_func,
							post_info->or_dmem_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_2,
							pre_info->or_dmem_2_simm_2_func,
							post_info->or_dmem_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_4,
							pre_info->or_dmem_4_simm_4_func,
							post_info->or_dmem_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_2,
							pre_info->or_dreg_2_simm_1_func,
							post_info->or_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_4,
							pre_info->or_dreg_4_simm_1_func,
							post_info->or_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_8,
							pre_info->or_dreg_8_simm_1_func,
							post_info->or_dreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_2,
							pre_info->or_dmem_2_simm_1_func,
							post_info->or_dmem_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_4,
							pre_info->or_dmem_4_simm_1_func,
							post_info->or_dmem_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_OR_DMEM_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_8,
							pre_info->or_dmem_8_simm_1_func,
							post_info->or_dmem_8_simm_1_func };

	/** ADC **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_smem_1,
							pre_info->adc_dreg_1_smem_1_func,
							post_info->adc_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_smem_2,
							pre_info->adc_dreg_2_smem_2_func,
							post_info->adc_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_smem_4,
							pre_info->adc_dreg_4_smem_4_func,
							post_info->adc_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->adc_dreg_8_smem_8_func,
							post_info->adc_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->adc_dreg_1_simm_1_func,
							post_info->adc_dreg_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->adc_dreg_2_simm_2_func,
							post_info->adc_dreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->adc_dreg_4_simm_4_func,
							post_info->adc_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_sreg_1,
							pre_info->adc_dreg_1_sreg_1_func,
							post_info->adc_dreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_sreg_2,
							pre_info->adc_dreg_2_sreg_2_func,
							post_info->adc_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_sreg_4,
							pre_info->adc_dreg_4_sreg_4_func,
							post_info->adc_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->adc_dreg_8_sreg_8_func,
							post_info->adc_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_1_sreg_1,
							pre_info->adc_dmem_1_sreg_1_func,
							post_info->adc_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_2_sreg_2,
							pre_info->adc_dmem_2_sreg_2_func,
							post_info->adc_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_4_sreg_4,
							pre_info->adc_dmem_4_sreg_4_func,
							post_info->adc_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_8_sreg_8,
							pre_info->adc_dmem_8_sreg_8_func,
							post_info->adc_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->adc_dmem_1_simm_1_func,
							post_info->adc_dmem_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->adc_dmem_2_simm_2_func,
							post_info->adc_dmem_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->adc_dmem_4_simm_4_func,
							post_info->adc_dmem_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->adc_dreg_2_simm_1_func,
							post_info->adc_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->adc_dreg_4_simm_1_func,
							post_info->adc_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->adc_dreg_8_simm_1_func,
							post_info->adc_dreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->adc_dmem_2_simm_1_func,
							post_info->adc_dmem_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->adc_dmem_4_simm_1_func,
							post_info->adc_dmem_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ADC_DMEM_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->adc_dmem_8_simm_1_func,
							post_info->adc_dmem_8_simm_1_func };

	/** SBB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_smem_1,
							pre_info->sbb_dreg_1_smem_1_func,
							post_info->sbb_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_smem_2,
							pre_info->sbb_dreg_2_smem_2_func,
							post_info->sbb_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_smem_4,
							pre_info->sbb_dreg_4_smem_4_func,
							post_info->sbb_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->sbb_dreg_8_smem_8_func,
							post_info->sbb_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->sbb_dreg_1_simm_1_func,
							post_info->sbb_dreg_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->sbb_dreg_2_simm_2_func,
							post_info->sbb_dreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->sbb_dreg_4_simm_4_func,
							post_info->sbb_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_sreg_1,
							pre_info->sbb_dreg_1_sreg_1_func,
							post_info->sbb_dreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_sreg_2,
							pre_info->sbb_dreg_2_sreg_2_func,
							post_info->sbb_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_sreg_4,
							pre_info->sbb_dreg_4_sreg_4_func,
							post_info->sbb_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->sbb_dreg_8_sreg_8_func,
							post_info->sbb_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_1_sreg_1,
							pre_info->sbb_dmem_1_sreg_1_func,
							post_info->sbb_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_2_sreg_2,
							pre_info->sbb_dmem_2_sreg_2_func,
							post_info->sbb_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_4_sreg_4,
							pre_info->sbb_dmem_4_sreg_4_func,
							post_info->sbb_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_8_sreg_8,
							pre_info->sbb_dmem_8_sreg_8_func,
							post_info->sbb_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->sbb_dmem_1_simm_1_func,
							post_info->sbb_dmem_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->sbb_dmem_2_simm_2_func,
							post_info->sbb_dmem_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->sbb_dmem_4_simm_4_func,
							post_info->sbb_dmem_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->sbb_dreg_2_simm_1_func,
							post_info->sbb_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->sbb_dreg_4_simm_1_func,
							post_info->sbb_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->sbb_dreg_8_simm_1_func,
							post_info->sbb_dreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->sbb_dmem_2_simm_1_func,
							post_info->sbb_dmem_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->sbb_dmem_4_simm_1_func,
							post_info->sbb_dmem_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SBB_DMEM_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->sbb_dmem_8_simm_1_func,
							post_info->sbb_dmem_8_simm_1_func };

	/** AND **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_1_smem_1,
							pre_info->and_dreg_1_smem_1_func,
							post_info->and_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_2_smem_2,
							pre_info->and_dreg_2_smem_2_func,
							post_info->and_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_4_smem_4,
							pre_info->and_dreg_4_smem_4_func,
							post_info->and_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_smem_8,
							pre_info->and_dreg_8_smem_8_func,
							post_info->and_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_1,
							pre_info->and_dreg_1_simm_1_func,
							post_info->and_dreg_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_2,
							pre_info->and_dreg_2_simm_2_func,
							post_info->and_dreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_4,
							pre_info->and_dreg_4_simm_4_func,
							post_info->and_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_1_sreg_1,
							pre_info->and_dreg_1_sreg_1_func,
							post_info->and_dreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_2_sreg_2,
							pre_info->and_dreg_2_sreg_2_func,
							post_info->and_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_4_sreg_4,
							pre_info->and_dreg_4_sreg_4_func,
							post_info->and_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->and_dreg_8_sreg_8_func,
							post_info->and_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_1_sreg_1,
							pre_info->and_dmem_1_sreg_1_func,
							post_info->and_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_2_sreg_2,
							pre_info->and_dmem_2_sreg_2_func,
							post_info->and_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_4_sreg_4,
							pre_info->and_dmem_4_sreg_4_func,
							post_info->and_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_8_sreg_8,
							pre_info->and_dmem_8_sreg_8_func,
							post_info->and_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_1,
							pre_info->and_dmem_1_simm_1_func,
							post_info->and_dmem_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_2,
							pre_info->and_dmem_2_simm_2_func,
							post_info->and_dmem_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_4,
							pre_info->and_dmem_4_simm_4_func,
							post_info->and_dmem_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_2,
							pre_info->and_dreg_2_simm_1_func,
							post_info->and_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_4,
							pre_info->and_dreg_4_simm_1_func,
							post_info->and_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_8,
							pre_info->and_dreg_8_simm_1_func,
							post_info->and_dreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_2,
							pre_info->and_dmem_2_simm_1_func,
							post_info->and_dmem_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_4,
							pre_info->and_dmem_4_simm_1_func,
							post_info->and_dmem_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_AND_DMEM_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_8,
							pre_info->and_dmem_8_simm_1_func,
							post_info->and_dmem_8_simm_1_func };

	/** SUB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_smem_1,
							pre_info->sub_dreg_1_smem_1_func,
							post_info->sub_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_smem_2,
							pre_info->sub_dreg_2_smem_2_func,
							post_info->sub_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_smem_4,
							pre_info->sub_dreg_4_smem_4_func,
							post_info->sub_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->sub_dreg_8_smem_8_func,
							post_info->sub_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->sub_dreg_1_simm_1_func,
							post_info->sub_dreg_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->sub_dreg_2_simm_2_func,
							post_info->sub_dreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->sub_dreg_4_simm_4_func,
							post_info->sub_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_1_sreg_1,
							pre_info->sub_dreg_1_sreg_1_func,
							post_info->sub_dreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_sreg_2,
							pre_info->sub_dreg_2_sreg_2_func,
							post_info->sub_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_sreg_4,
							pre_info->sub_dreg_4_sreg_4_func,
							post_info->sub_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->sub_dreg_8_sreg_8_func,
							post_info->sub_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_1_sreg_1,
							pre_info->sub_dmem_1_sreg_1_func,
							post_info->sub_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_2_sreg_2,
							pre_info->sub_dmem_2_sreg_2_func,
							post_info->sub_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_4_sreg_4,
							pre_info->sub_dmem_4_sreg_4_func,
							post_info->sub_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dmem_8_sreg_8,
							pre_info->sub_dmem_8_sreg_8_func,
							post_info->sub_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->sub_dmem_1_simm_1_func,
							post_info->sub_dmem_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->sub_dmem_2_simm_2_func,
							post_info->sub_dmem_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->sub_dmem_4_simm_4_func,
							post_info->sub_dmem_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->sub_dreg_2_simm_1_func,
							post_info->sub_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->sub_dreg_4_simm_1_func,
							post_info->sub_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->sub_dreg_8_simm_1_func,
							post_info->sub_dreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->sub_dmem_2_simm_1_func,
							post_info->sub_dmem_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->sub_dmem_4_simm_1_func,
							post_info->sub_dmem_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SUB_DMEM_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->sub_dmem_8_simm_1_func,
							post_info->sub_dmem_8_simm_1_func };

	/** XOR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_1_smem_1,
							pre_info->xor_dreg_1_smem_1_func,
							post_info->xor_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_2_smem_2,
							pre_info->xor_dreg_2_smem_2_func,
							post_info->xor_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_4_smem_4,
							pre_info->xor_dreg_4_smem_4_func,
							post_info->xor_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_smem_8,
							pre_info->xor_dreg_8_smem_8_func,
							post_info->xor_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_1,
							pre_info->xor_dreg_1_simm_1_func,
							post_info->xor_dreg_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_2,
							pre_info->xor_dreg_2_simm_2_func,
							post_info->xor_dreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_4,
							pre_info->xor_dreg_4_simm_4_func,
							post_info->xor_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_1_sreg_1,
							pre_info->xor_dreg_1_sreg_1_func,
							post_info->xor_dreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_2_sreg_2,
							pre_info->xor_dreg_2_sreg_2_func,
							post_info->xor_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_4_sreg_4,
							pre_info->xor_dreg_4_sreg_4_func,
							post_info->xor_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->xor_dreg_8_sreg_8_func,
							post_info->xor_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_1_sreg_1,
							pre_info->xor_dmem_1_sreg_1_func,
							post_info->xor_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_2_sreg_2,
							pre_info->xor_dmem_2_sreg_2_func,
							post_info->xor_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_4_sreg_4,
							pre_info->xor_dmem_4_sreg_4_func,
							post_info->xor_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dmem_8_sreg_8,
							pre_info->xor_dmem_8_sreg_8_func,
							post_info->xor_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_1_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_1,
							pre_info->xor_dmem_1_simm_1_func,
							post_info->xor_dmem_1_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_2,
							pre_info->xor_dmem_2_simm_2_func,
							post_info->xor_dmem_2_simm_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_4,
							pre_info->xor_dmem_4_simm_4_func,
							post_info->xor_dmem_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_2,
							pre_info->xor_dreg_2_simm_1_func,
							post_info->xor_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_4,
							pre_info->xor_dreg_4_simm_1_func,
							post_info->xor_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsreg_8,
							pre_info->xor_dreg_8_simm_1_func,
							post_info->xor_dreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_2,
							pre_info->xor_dmem_2_simm_1_func,
							post_info->xor_dmem_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_4,
							pre_info->xor_dmem_4_simm_1_func,
							post_info->xor_dmem_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XOR_DMEM_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_srcdst_dsmem_8,
							pre_info->xor_dmem_8_simm_1_func,
							post_info->xor_dmem_8_simm_1_func };

	/** INC **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->inc_dsmem_1_func,
							post_info->inc_dsmem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->inc_dsmem_2_func,
							post_info->inc_dsmem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->inc_dsmem_4_func,
							post_info->inc_dsmem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->inc_dsmem_8_func,
							post_info->inc_dsmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->inc_dsreg_1_func,
							post_info->inc_dsreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->inc_dsreg_2_func,
							post_info->inc_dsreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->inc_dsreg_4_func,
							post_info->inc_dsreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_INC_DSREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->inc_dsreg_8_func,
							post_info->inc_dsreg_8_func };
	/** DEC **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->dec_dsmem_1_func,
							post_info->dec_dsmem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->dec_dsmem_2_func,
							post_info->dec_dsmem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->dec_dsmem_4_func,
							post_info->dec_dsmem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->dec_dsmem_8_func,
							post_info->dec_dsmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->dec_dsreg_1_func,
							post_info->dec_dsreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->dec_dsreg_2_func,
							post_info->dec_dsreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->dec_dsreg_4_func,
							post_info->dec_dsreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DEC_DSREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->dec_dsreg_8_func,
							post_info->dec_dsreg_8_func };

	/** PUSH **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_1_sreg_1,
							pre_info->push_dmem_1_sreg_1_func,
							post_info->push_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_2_sreg_2,
							pre_info->push_dmem_2_sreg_2_func,
							post_info->push_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_4_sreg_4,
							pre_info->push_dmem_4_sreg_4_func,
							post_info->push_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_8_sreg_8,
							pre_info->push_dmem_8_sreg_8_func,
							post_info->push_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_1_smem_1,
							pre_info->push_dmem_1_smem_1_func,
							post_info->push_dmem_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_2_smem_2,
							pre_info->push_dmem_2_smem_2_func,
							post_info->push_dmem_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_4_smem_4,
							pre_info->push_dmem_4_smem_4_func,
							post_info->push_dmem_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUSH_DMEM_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_push_dmem_8_smem_8,
							pre_info->push_dmem_8_smem_8_func,
							post_info->push_dmem_8_smem_8_func };

	/** POP **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POP_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pop_dreg_1_smem_1,
							pre_info->pop_dreg_1_smem_1_func,
							post_info->pop_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POP_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pop_dreg_2_smem_2,
							pre_info->pop_dreg_2_smem_2_func,
							post_info->pop_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POP_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pop_dreg_4_smem_4,
							pre_info->pop_dreg_4_smem_4_func,
							post_info->pop_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POP_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pop_dreg_8_smem_8,
							pre_info->pop_dreg_8_smem_8_func,
							post_info->pop_dreg_8_smem_8_func };

	/** IMUL **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_2_sreg_1_sreg_1,
							pre_info->imul_dreg_2_sreg_1_sreg_1_func,
							post_info->imul_dreg_2_sreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_2_smem_1_sreg_1,
							pre_info->imul_dreg_2_smem_1_sreg_1_func,
							post_info->imul_dreg_2_smem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_DREG_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4,
							pre_info->imul_dreg_4_dreg_4_sreg_4_sreg_4_func,
							post_info->imul_dreg_4_dreg_4_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_DREG_4_SMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4,
							pre_info->imul_dreg_4_dreg_4_smem_4_sreg_4_func,
							post_info->imul_dreg_4_dreg_4_smem_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_smem_2,
							pre_info->imul_dreg_2_smem_2_func,
							post_info->imul_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_smem_4,
							pre_info->imul_dreg_4_smem_4_func,
							post_info->imul_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_2_sreg_2,
							pre_info->imul_dreg_2_sreg_2_func,
							post_info->imul_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_4_sreg_4,
							pre_info->imul_dreg_4_sreg_4_func,
							post_info->imul_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->imul_dreg_2_simm_1_func,
							post_info->imul_dreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->imul_dreg_4_simm_1_func,
							post_info->imul_dreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->imul_dreg_2_simm_2_func,
							post_info->imul_dreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->imul_dreg_4_simm_4_func,
							post_info->imul_dreg_4_simm_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SREG_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->imul_dreg_2_sreg_2_simm_2_func,
							post_info->imul_dreg_2_sreg_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_SREG_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->imul_dreg_4_sreg_4_simm_4_func,
							post_info->imul_dreg_4_sreg_4_simm_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_2_SMEM_2_SIMM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_smem_2,
							pre_info->imul_dreg_2_smem_2_simm_2_func,
							post_info->imul_dreg_2_smem_2_simm_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IMUL_DREG_4_SMEM_4_SIMM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_smem_4,
							pre_info->imul_dreg_4_smem_4_simm_4_func,
							post_info->imul_dreg_4_smem_4_simm_4_func };

	/** MOV_LD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_1_smem_1,
							pre_info->mov_dreg_1_smem_1_func,
							post_info->mov_dreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_2_smem_2,
							pre_info->mov_dreg_2_smem_2_func,
							post_info->mov_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_4_smem_4,
							pre_info->mov_dreg_4_smem_4_func,
							post_info->mov_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_smem_8,
							pre_info->mov_dreg_8_smem_8_func,
							post_info->mov_dreg_8_smem_8_func };
	/** MOV_ST **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_1_sreg_1,
							pre_info->mov_dreg_1_sreg_1_func,
							post_info->mov_dreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_2_sreg_2,
							pre_info->mov_dreg_2_sreg_2_func,
							post_info->mov_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_4_sreg_4,
							pre_info->mov_dreg_4_sreg_4_func,
							post_info->mov_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_sreg_8,
							pre_info->mov_dreg_8_sreg_8_func,
							post_info->mov_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_1_sreg_1,
							pre_info->mov_dmem_1_sreg_1_func,
							post_info->mov_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_2_sreg_2,
							pre_info->mov_dmem_2_sreg_2_func,
							post_info->mov_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_4_sreg_4,
							pre_info->mov_dmem_4_sreg_4_func,
							post_info->mov_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOV_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_8_sreg_8,
							pre_info->mov_dmem_8_sreg_8_func,
							post_info->mov_dmem_8_sreg_8_func };

	/** LEA **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_DREG_2_SREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_lea_dreg_2_sreg_2_sreg_2,
							pre_info->lea_dreg_2_sreg_2_sreg_2_func,
							post_info->lea_dreg_2_sreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_DREG_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_lea_dreg_4_sreg_4_sreg_4,
							pre_info->lea_dreg_4_sreg_4_sreg_4_func,
							post_info->lea_dreg_4_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_lea_dreg_8_sreg_8_sreg_8,
							pre_info->lea_dreg_8_sreg_8_sreg_8_func,
							post_info->lea_dreg_8_sreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_BASE_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_base_lea_dreg_2_sreg_2,
							pre_info->lea_base_dreg_2_sreg_2_func,
							post_info->lea_base_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_BASE_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_base_lea_dreg_4_sreg_4,
							pre_info->lea_base_dreg_4_sreg_4_func,
							post_info->lea_base_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_BASE_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_base_lea_dreg_8_sreg_8,
							pre_info->lea_base_dreg_8_sreg_8_func,
							post_info->lea_base_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_INDEX_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_index_lea_dreg_2_sreg_2,
							pre_info->lea_index_dreg_2_sreg_2_func,
							post_info->lea_index_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_INDEX_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_index_lea_dreg_4_sreg_4,
							pre_info->lea_index_dreg_4_sreg_4_func,
							post_info->lea_index_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEA_INDEX_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_ADDR_GEN_INFO,
							tb_cc_byt_execute_index_lea_dreg_8_sreg_8,
							pre_info->lea_index_dreg_8_sreg_8_func,
							post_info->lea_index_dreg_8_sreg_8_func };

	/** XCHG **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_1_reg_1,
							pre_info->xchg_reg_1_reg_1_func,
							post_info->xchg_reg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_2_REG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_2_reg_2,
							pre_info->xchg_reg_2_reg_2_func,
							post_info->xchg_reg_2_reg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_4_REG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_4_reg_4,
							pre_info->xchg_reg_4_reg_4_func,
							post_info->xchg_reg_4_reg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_8_REG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_8_reg_8,
							pre_info->xchg_reg_8_reg_8_func,
							post_info->xchg_reg_8_reg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_MEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_mem_1_reg_1,
							pre_info->xchg_mem_1_reg_1_func,
							post_info->xchg_mem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_MEM_2_REG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_mem_2_reg_2,
							pre_info->xchg_mem_2_reg_2_func,
							post_info->xchg_mem_2_reg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_MEM_4_REG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_mem_4_reg_4,
							pre_info->xchg_mem_4_reg_4_func,
							post_info->xchg_mem_4_reg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_MEM_8_REG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_mem_8_reg_8,
							pre_info->xchg_mem_8_reg_8_func,
							post_info->xchg_mem_8_reg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_1_MEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_1_mem_1,
							pre_info->xchg_reg_1_mem_1_func,
							post_info->xchg_reg_1_mem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_2_MEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_2_mem_2,
							pre_info->xchg_reg_2_mem_2_func,
							post_info->xchg_reg_2_mem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_4_MEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_4_mem_4,
							pre_info->xchg_reg_4_mem_4_func,
							post_info->xchg_reg_4_mem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XCHG_REG_8_MEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xchg_reg_8_mem_8,
							pre_info->xchg_reg_8_mem_8_func,
							post_info->xchg_reg_8_mem_8_func };

	/** LEAVE **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEAVE_DREG_4_DREG_4_SREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_leave_dreg_4_sreg_4_smem_4,
							pre_info->leave_dreg_4_dreg_4_sreg_4_smem_4_func,
							post_info->leave_dreg_4_dreg_4_sreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LEAVE_DREG_8_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_leave_dreg_8_sreg_8_smem_8,
							pre_info->leave_dreg_8_dreg_8_sreg_8_smem_8_func,
							post_info->leave_dreg_8_dreg_8_sreg_8_smem_8_func };

	/** CMOVO **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVO_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovo_dreg_2_sreg_2,
							pre_info->cmovo_dreg_2_sreg_2_func,
							post_info->cmovo_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVO_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovo_dreg_4_sreg_4,
							pre_info->cmovo_dreg_4_sreg_4_func,
							post_info->cmovo_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVO_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovo_dreg_8_sreg_8,
							pre_info->cmovo_dreg_8_sreg_8_func,
							post_info->cmovo_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVO_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovo_dreg_2_smem_2,
							pre_info->cmovo_dreg_2_smem_2_func,
							post_info->cmovo_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVO_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovo_dreg_4_smem_4,
							pre_info->cmovo_dreg_4_smem_4_func,
							post_info->cmovo_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVO_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovo_dreg_8_smem_8,
							pre_info->cmovo_dreg_8_smem_8_func,
							post_info->cmovo_dreg_8_smem_8_func };

	/** CMOVNO **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNO_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovno_dreg_2_sreg_2,
							pre_info->cmovno_dreg_2_sreg_2_func,
							post_info->cmovno_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNO_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovno_dreg_4_sreg_4,
							pre_info->cmovno_dreg_4_sreg_4_func,
							post_info->cmovno_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNO_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovno_dreg_8_sreg_8,
							pre_info->cmovno_dreg_8_sreg_8_func,
							post_info->cmovno_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNO_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovno_dreg_2_smem_2,
							pre_info->cmovno_dreg_2_smem_2_func,
							post_info->cmovno_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNO_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovno_dreg_4_smem_4,
							pre_info->cmovno_dreg_4_smem_4_func,
							post_info->cmovno_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNO_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovno_dreg_8_smem_8,
							pre_info->cmovno_dreg_8_smem_8_func,
							post_info->cmovno_dreg_8_smem_8_func };

	/** CMOVB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVB_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovb_dreg_2_sreg_2,
							pre_info->cmovb_dreg_2_sreg_2_func,
							post_info->cmovb_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVB_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovb_dreg_4_sreg_4,
							pre_info->cmovb_dreg_4_sreg_4_func,
							post_info->cmovb_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovb_dreg_8_sreg_8,
							pre_info->cmovb_dreg_8_sreg_8_func,
							post_info->cmovb_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVB_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovb_dreg_2_smem_2,
							pre_info->cmovb_dreg_2_smem_2_func,
							post_info->cmovb_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVB_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovb_dreg_4_smem_4,
							pre_info->cmovb_dreg_4_smem_4_func,
							post_info->cmovb_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovb_dreg_8_smem_8,
							pre_info->cmovb_dreg_8_smem_8_func,
							post_info->cmovb_dreg_8_smem_8_func };

	/** CMOVNB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNB_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnb_dreg_2_sreg_2,
							pre_info->cmovnb_dreg_2_sreg_2_func,
							post_info->cmovnb_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNB_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnb_dreg_4_sreg_4,
							pre_info->cmovnb_dreg_4_sreg_4_func,
							post_info->cmovnb_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnb_dreg_8_sreg_8,
							pre_info->cmovnb_dreg_8_sreg_8_func,
							post_info->cmovnb_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNB_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnb_dreg_2_smem_2,
							pre_info->cmovnb_dreg_2_smem_2_func,
							post_info->cmovnb_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNB_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnb_dreg_4_smem_4,
							pre_info->cmovnb_dreg_4_smem_4_func,
							post_info->cmovnb_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnb_dreg_8_smem_8,
							pre_info->cmovnb_dreg_8_smem_8_func,
							post_info->cmovnb_dreg_8_smem_8_func };

	/** CMOVZ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVE_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmove_dreg_2_sreg_2,
							pre_info->cmove_dreg_2_sreg_2_func,
							post_info->cmove_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVE_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmove_dreg_4_sreg_4,
							pre_info->cmove_dreg_4_sreg_4_func,
							post_info->cmove_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVE_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmove_dreg_8_sreg_8,
							pre_info->cmove_dreg_8_sreg_8_func,
							post_info->cmove_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVE_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmove_dreg_2_smem_2,
							pre_info->cmove_dreg_2_smem_2_func,
							post_info->cmove_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVE_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmove_dreg_4_smem_4,
							pre_info->cmove_dreg_4_smem_4_func,
							post_info->cmove_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVE_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmove_dreg_8_smem_8,
							pre_info->cmove_dreg_8_smem_8_func,
							post_info->cmove_dreg_8_smem_8_func };

	/** CMOVNZ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNE_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovne_dreg_2_sreg_2,
							pre_info->cmovne_dreg_2_sreg_2_func,
							post_info->cmovne_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNE_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovne_dreg_4_sreg_4,
							pre_info->cmovne_dreg_4_sreg_4_func,
							post_info->cmovne_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNE_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovne_dreg_8_sreg_8,
							pre_info->cmovne_dreg_8_sreg_8_func,
							post_info->cmovne_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNE_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovne_dreg_2_smem_2,
							pre_info->cmovne_dreg_2_smem_2_func,
							post_info->cmovne_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNE_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovne_dreg_4_smem_4,
							pre_info->cmovne_dreg_4_smem_4_func,
							post_info->cmovne_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNE_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovne_dreg_8_smem_8,
							pre_info->cmovne_dreg_8_smem_8_func,
							post_info->cmovne_dreg_8_smem_8_func };

	/** CMOVBE **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVBE_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovbe_dreg_2_sreg_2,
							pre_info->cmovbe_dreg_2_sreg_2_func,
							post_info->cmovbe_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVBE_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovbe_dreg_4_sreg_4,
							pre_info->cmovbe_dreg_4_sreg_4_func,
							post_info->cmovbe_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVBE_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovbe_dreg_8_sreg_8,
							pre_info->cmovbe_dreg_8_sreg_8_func,
							post_info->cmovbe_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVBE_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovbe_dreg_2_smem_2,
							pre_info->cmovbe_dreg_2_smem_2_func,
							post_info->cmovbe_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVBE_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovbe_dreg_4_smem_4,
							pre_info->cmovbe_dreg_4_smem_4_func,
							post_info->cmovbe_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVBE_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovbe_dreg_8_smem_8,
							pre_info->cmovbe_dreg_8_smem_8_func,
							post_info->cmovbe_dreg_8_smem_8_func };

	/** CMOVNBE **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNBE_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnbe_dreg_2_sreg_2,
							pre_info->cmovnbe_dreg_2_sreg_2_func,
							post_info->cmovnbe_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNBE_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnbe_dreg_4_sreg_4,
							pre_info->cmovnbe_dreg_4_sreg_4_func,
							post_info->cmovnbe_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNBE_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnbe_dreg_8_sreg_8,
							pre_info->cmovnbe_dreg_8_sreg_8_func,
							post_info->cmovnbe_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNBE_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnbe_dreg_2_smem_2,
							pre_info->cmovnbe_dreg_2_smem_2_func,
							post_info->cmovnbe_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNBE_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnbe_dreg_4_smem_4,
							pre_info->cmovnbe_dreg_4_smem_4_func,
							post_info->cmovnbe_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNBE_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnbe_dreg_8_smem_8,
							pre_info->cmovnbe_dreg_8_smem_8_func,
							post_info->cmovnbe_dreg_8_smem_8_func };

	/** CMOVS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVS_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovs_dreg_2_sreg_2,
							pre_info->cmovs_dreg_2_sreg_2_func,
							post_info->cmovs_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVS_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovs_dreg_4_sreg_4,
							pre_info->cmovs_dreg_4_sreg_4_func,
							post_info->cmovs_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVS_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovs_dreg_8_sreg_8,
							pre_info->cmovs_dreg_8_sreg_8_func,
							post_info->cmovs_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVS_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovs_dreg_2_smem_2,
							pre_info->cmovs_dreg_2_smem_2_func,
							post_info->cmovs_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVS_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovs_dreg_4_smem_4,
							pre_info->cmovs_dreg_4_smem_4_func,
							post_info->cmovs_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVS_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovs_dreg_8_smem_8,
							pre_info->cmovs_dreg_8_smem_8_func,
							post_info->cmovs_dreg_8_smem_8_func };

	/** CMOVNS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNS_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovns_dreg_2_sreg_2,
							pre_info->cmovns_dreg_2_sreg_2_func,
							post_info->cmovns_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNS_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovns_dreg_4_sreg_4,
							pre_info->cmovns_dreg_4_sreg_4_func,
							post_info->cmovns_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNS_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovns_dreg_8_sreg_8,
							pre_info->cmovns_dreg_8_sreg_8_func,
							post_info->cmovns_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNS_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovns_dreg_2_smem_2,
							pre_info->cmovns_dreg_2_smem_2_func,
							post_info->cmovns_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNS_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovns_dreg_4_smem_4,
							pre_info->cmovns_dreg_4_smem_4_func,
							post_info->cmovns_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNS_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovns_dreg_8_smem_8,
							pre_info->cmovns_dreg_8_smem_8_func,
							post_info->cmovns_dreg_8_smem_8_func };

	/** CMOVP **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVP_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovp_dreg_2_sreg_2,
							pre_info->cmovp_dreg_2_sreg_2_func,
							post_info->cmovp_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVP_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovp_dreg_4_sreg_4,
							pre_info->cmovp_dreg_4_sreg_4_func,
							post_info->cmovp_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVP_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovp_dreg_8_sreg_8,
							pre_info->cmovp_dreg_8_sreg_8_func,
							post_info->cmovp_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVP_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovp_dreg_2_smem_2,
							pre_info->cmovp_dreg_2_smem_2_func,
							post_info->cmovp_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVP_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovp_dreg_4_smem_4,
							pre_info->cmovp_dreg_4_smem_4_func,
							post_info->cmovp_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVP_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovp_dreg_8_smem_8,
							pre_info->cmovp_dreg_8_smem_8_func,
							post_info->cmovp_dreg_8_smem_8_func };

	/** CMOVNP **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNP_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnp_dreg_2_sreg_2,
							pre_info->cmovnp_dreg_2_sreg_2_func,
							post_info->cmovnp_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNP_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnp_dreg_4_sreg_4,
							pre_info->cmovnp_dreg_4_sreg_4_func,
							post_info->cmovnp_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNP_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnp_dreg_8_sreg_8,
							pre_info->cmovnp_dreg_8_sreg_8_func,
							post_info->cmovnp_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNP_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnp_dreg_2_smem_2,
							pre_info->cmovnp_dreg_2_smem_2_func,
							post_info->cmovnp_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNP_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnp_dreg_4_smem_4,
							pre_info->cmovnp_dreg_4_smem_4_func,
							post_info->cmovnp_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVNP_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovnp_dreg_8_smem_8,
							pre_info->cmovnp_dreg_8_smem_8_func,
							post_info->cmovnp_dreg_8_smem_8_func };

	/** CMOVL **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVL_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovl_dreg_2_sreg_2,
							pre_info->cmovl_dreg_2_sreg_2_func,
							post_info->cmovl_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVL_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovl_dreg_4_sreg_4,
							pre_info->cmovl_dreg_4_sreg_4_func,
							post_info->cmovl_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVL_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovl_dreg_8_sreg_8,
							pre_info->cmovl_dreg_8_sreg_8_func,
							post_info->cmovl_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVL_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovl_dreg_2_smem_2,
							pre_info->cmovl_dreg_2_smem_2_func,
							post_info->cmovl_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVL_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovl_dreg_4_smem_4,
							pre_info->cmovl_dreg_4_smem_4_func,
							post_info->cmovl_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVL_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovl_dreg_8_smem_8,
							pre_info->cmovl_dreg_8_smem_8_func,
							post_info->cmovl_dreg_8_smem_8_func };

	/** CMOVNL **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVGE_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovge_dreg_2_sreg_2,
							pre_info->cmovge_dreg_2_sreg_2_func,
							post_info->cmovge_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVGE_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovge_dreg_4_sreg_4,
							pre_info->cmovge_dreg_4_sreg_4_func,
							post_info->cmovge_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVGE_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovge_dreg_8_sreg_8,
							pre_info->cmovge_dreg_8_sreg_8_func,
							post_info->cmovge_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVGE_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovge_dreg_2_smem_2,
							pre_info->cmovge_dreg_2_smem_2_func,
							post_info->cmovge_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVGE_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovge_dreg_4_smem_4,
							pre_info->cmovge_dreg_4_smem_4_func,
							post_info->cmovge_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVGE_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovge_dreg_8_smem_8,
							pre_info->cmovge_dreg_8_smem_8_func,
							post_info->cmovge_dreg_8_smem_8_func };

	/** CMOVLE **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVLE_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovle_dreg_2_sreg_2,
							pre_info->cmovle_dreg_2_sreg_2_func,
							post_info->cmovle_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVLE_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovle_dreg_4_sreg_4,
							pre_info->cmovle_dreg_4_sreg_4_func,
							post_info->cmovle_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVLE_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovle_dreg_8_sreg_8,
							pre_info->cmovle_dreg_8_sreg_8_func,
							post_info->cmovle_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVLE_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovle_dreg_2_smem_2,
							pre_info->cmovle_dreg_2_smem_2_func,
							post_info->cmovle_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVLE_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovle_dreg_4_smem_4,
							pre_info->cmovle_dreg_4_smem_4_func,
							post_info->cmovle_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVLE_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovle_dreg_8_smem_8,
							pre_info->cmovle_dreg_8_smem_8_func,
							post_info->cmovle_dreg_8_smem_8_func };

	/** CMOVNLE **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVG_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovg_dreg_2_sreg_2,
							pre_info->cmovg_dreg_2_sreg_2_func,
							post_info->cmovg_dreg_2_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVG_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovg_dreg_4_sreg_4,
							pre_info->cmovg_dreg_4_sreg_4_func,
							post_info->cmovg_dreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVG_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovg_dreg_8_sreg_8,
							pre_info->cmovg_dreg_8_sreg_8_func,
							post_info->cmovg_dreg_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVG_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovg_dreg_2_smem_2,
							pre_info->cmovg_dreg_2_smem_2_func,
							post_info->cmovg_dreg_2_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVG_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovg_dreg_4_smem_4,
							pre_info->cmovg_dreg_4_smem_4_func,
							post_info->cmovg_dreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMOVG_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_FLAG_INFO, tb_cc_byt_execute_cmovg_dreg_8_smem_8,
							pre_info->cmovg_dreg_8_smem_8_func,
							post_info->cmovg_dreg_8_smem_8_func };

	/** PUNPCKLBW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLBW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklbw_dreg_8_sreg_8,
							pre_info->punpcklbw_dreg_8_sreg_8_func,
							post_info->punpcklbw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLBW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklbw_dreg_8_smem_8,
							pre_info->punpcklbw_dreg_8_smem_8_func,
							post_info->punpcklbw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLBW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklbw_dreg_16_sreg_16,
							pre_info->punpcklbw_dreg_16_sreg_16_func,
							post_info->punpcklbw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLBW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklbw_dreg_16_smem_16,
							pre_info->punpcklbw_dreg_16_smem_16_func,
							post_info->punpcklbw_dreg_16_smem_16_func };

	/** PUNPCKLWD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLWD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklwd_dreg_8_sreg_8,
							pre_info->punpcklwd_dreg_8_sreg_8_func,
							post_info->punpcklwd_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLWD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklwd_dreg_8_smem_8,
							pre_info->punpcklwd_dreg_8_smem_8_func,
							post_info->punpcklwd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLWD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklwd_dreg_16_sreg_16,
							pre_info->punpcklwd_dreg_16_sreg_16_func,
							post_info->punpcklwd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLWD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklwd_dreg_16_smem_16,
							pre_info->punpcklwd_dreg_16_smem_16_func,
							post_info->punpcklwd_dreg_16_smem_16_func };

	/** PUNPCKLDQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLDQ_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckldq_dreg_8_sreg_8,
							pre_info->punpckldq_dreg_8_sreg_8_func,
							post_info->punpckldq_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLDQ_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckldq_dreg_8_smem_8,
							pre_info->punpckldq_dreg_8_smem_8_func,
							post_info->punpckldq_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLDQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckldq_dreg_16_sreg_16,
							pre_info->punpckldq_dreg_16_sreg_16_func,
							post_info->punpckldq_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLDQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckldq_dreg_16_smem_16,
							pre_info->punpckldq_dreg_16_smem_16_func,
							post_info->punpckldq_dreg_16_smem_16_func };

	/** PACKSSWB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSWB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_8_sreg_8,
							pre_info->packsswb_dreg_8_sreg_8_func,
							post_info->packsswb_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSWB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_8_smem_8,
							pre_info->packsswb_dreg_8_smem_8_func,
							post_info->packsswb_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSWB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_16_sreg_16,
							pre_info->packsswb_dreg_16_sreg_16_func,
							post_info->packsswb_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSWB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_16_smem_16,
							pre_info->packsswb_dreg_16_smem_16_func,
							post_info->packsswb_dreg_16_smem_16_func };

	/** PCMPGTB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_8_smem_8,
							pre_info->pcmpgtb_dreg_8_smem_8_func,
							post_info->pcmpgtb_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_8_sreg_8,
							pre_info->pcmpgtb_dreg_8_sreg_8_func,
							post_info->pcmpgtb_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_16_smem_16,
							pre_info->pcmpgtb_dreg_16_smem_16_func,
							post_info->pcmpgtb_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_16_sreg_16,
							pre_info->pcmpgtb_dreg_16_sreg_16_func,
							post_info->pcmpgtb_dreg_16_sreg_16_func };

	/** PCMPGTW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_8_smem_8,
							pre_info->pcmpgtw_dreg_8_smem_8_func,
							post_info->pcmpgtw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_8_sreg_8,
							pre_info->pcmpgtw_dreg_8_sreg_8_func,
							post_info->pcmpgtw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_16_smem_16,
							pre_info->pcmpgtw_dreg_16_smem_16_func,
							post_info->pcmpgtw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_16_sreg_16,
							pre_info->pcmpgtw_dreg_16_sreg_16_func,
							post_info->pcmpgtw_dreg_16_sreg_16_func };

	/** PCMPGTD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_8_smem_8,
							pre_info->pcmpgtd_dreg_8_smem_8_func,
							post_info->pcmpgtd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_8_sreg_8,
							pre_info->pcmpgtd_dreg_8_sreg_8_func,
							post_info->pcmpgtd_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_16_smem_16,
							pre_info->pcmpgtd_dreg_16_smem_16_func,
							post_info->pcmpgtd_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_16_sreg_16,
							pre_info->pcmpgtd_dreg_16_sreg_16_func,
							post_info->pcmpgtd_dreg_16_sreg_16_func };

	/** PACKUSWB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKUSWB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_8_sreg_8,
							pre_info->packuswb_dreg_8_sreg_8_func,
							post_info->packuswb_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKUSWB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_8_smem_8,
							pre_info->packuswb_dreg_8_smem_8_func,
							post_info->packuswb_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKUSWB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_16_sreg_16,
							pre_info->packuswb_dreg_16_sreg_16_func,
							post_info->packuswb_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKUSWB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packswb_dreg_16_smem_16,
							pre_info->packuswb_dreg_16_smem_16_func,
							post_info->packuswb_dreg_16_smem_16_func };

	/** PUNPCKHBW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHBW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhbw_dreg_8_sreg_8,
							pre_info->punpckhbw_dreg_8_sreg_8_func,
							post_info->punpckhbw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHBW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhbw_dreg_8_smem_8,
							pre_info->punpckhbw_dreg_8_smem_8_func,
							post_info->punpckhbw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHBW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhbw_dreg_16_sreg_16,
							pre_info->punpckhbw_dreg_16_sreg_16_func,
							post_info->punpckhbw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHBW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklbw_dreg_16_smem_16,
							pre_info->punpckhbw_dreg_16_smem_16_func,
							post_info->punpckhbw_dreg_16_smem_16_func };

	/** PUNPCKHWD**/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHWD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhwd_dreg_8_sreg_8,
							pre_info->punpckhwd_dreg_8_sreg_8_func,
							post_info->punpckhwd_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHWD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhwd_dreg_8_smem_8,
							pre_info->punpckhwd_dreg_8_smem_8_func,
							post_info->punpckhwd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHWD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhwd_dreg_16_sreg_16,
							pre_info->punpckhwd_dreg_16_sreg_16_func,
							post_info->punpckhwd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHWD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhwd_dreg_16_smem_16,
							pre_info->punpckhwd_dreg_16_smem_16_func,
							post_info->punpckhwd_dreg_16_smem_16_func };

	/** PUNPCKHDQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHDQ_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhdq_dreg_8_sreg_8,
							pre_info->punpckhdq_dreg_8_sreg_8_func,
							post_info->punpckhdq_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHDQ_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhdq_dreg_8_smem_8,
							pre_info->punpckhdq_dreg_8_smem_8_func,
							post_info->punpckhdq_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHDQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhdq_dreg_16_sreg_16,
							pre_info->punpckhdq_dreg_16_sreg_16_func,
							post_info->punpckhdq_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHDQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhdq_dreg_16_smem_16,
							pre_info->punpckhdq_dreg_16_smem_16_func,
							post_info->punpckhdq_dreg_16_smem_16_func };

	/** PACKSSDW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSDW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packsdw_dreg_8_sreg_8,
							pre_info->packssdw_dreg_8_sreg_8_func,
							post_info->packssdw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSDW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packsdw_dreg_8_smem_8,
							pre_info->packssdw_dreg_8_smem_8_func,
							post_info->packssdw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSDW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packsdw_dreg_16_sreg_16,
							pre_info->packssdw_dreg_16_sreg_16_func,
							post_info->packssdw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKSSDW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packsdw_dreg_16_smem_16,
							pre_info->packssdw_dreg_16_smem_16_func,
							post_info->packssdw_dreg_16_smem_16_func };

	/** PUNPCKLQDQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLQDQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklqdq_dreg_16_sreg_16,
							pre_info->punpcklqdq_dreg_16_sreg_16_func,
							post_info->punpcklqdq_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKLQDQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpcklqdq_dreg_16_smem_16,
							pre_info->punpcklqdq_dreg_16_smem_16_func,
							post_info->punpcklqdq_dreg_16_smem_16_func };

	/** PUNPCKHQDQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHQDQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhqdq_dreg_16_sreg_16,
							pre_info->punpckhqdq_dreg_16_sreg_16_func,
							post_info->punpckhqdq_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PUNPCKHQDQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_punpckhqdq_dreg_16_smem_16,
							pre_info->punpckhqdq_dreg_16_smem_16_func,
							post_info->punpckhqdq_dreg_16_smem_16_func };

	/** MOVD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_4_smem_4,
							pre_info->movd_dreg_4_smem_4_func,
							post_info->movd_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_4_sreg_4,
							pre_info->movd_dreg_4_sreg_4_func,
							post_info->movd_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_4_sreg_4,
							pre_info->movd_dmem_4_sreg_4_func,
							post_info->movd_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_8_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_8_smem_4,
							pre_info->movd_dreg_8_smem_4_func,
							post_info->movd_dreg_8_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_8_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_8_sreg_4,
							pre_info->movd_dreg_8_sreg_4_func,
							post_info->movd_dreg_8_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_4_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_4_sreg_4,
							pre_info->movd_dreg_4_sreg_8_func,
							post_info->movd_dreg_4_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DMEM_4_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_4_sreg_4,
							pre_info->movd_dmem_4_sreg_8_func,
							post_info->movd_dmem_4_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_16_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_16_smem_4,
							pre_info->movd_dreg_16_smem_4_func,
							post_info->movd_dreg_16_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_16_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_16_sreg_4,
							pre_info->movd_dreg_16_sreg_4_func,
							post_info->movd_dreg_16_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DMEM_4_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_4_sreg_4,
							pre_info->movd_dmem_4_sreg_16_func,
							post_info->movd_dmem_4_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVD_DREG_4_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_4_sreg_4,
							pre_info->movd_dreg_4_sreg_16_func,
							post_info->movd_dreg_4_sreg_16_func };

	/** MOVQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_smem_8,
							pre_info->movq_dreg_8_smem_8_func,
							post_info->movq_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_sreg_8,
							pre_info->movq_dreg_8_sreg_8_func,
							post_info->movq_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_8_sreg_8,
							pre_info->movq_dmem_8_sreg_8_func,
							post_info->movq_dmem_8_sreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ_DREG_16_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_16_smem_8,
							pre_info->movq_dreg_16_smem_8_func,
							post_info->movq_dreg_16_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ_DREG_16_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_16_sreg_8,
							pre_info->movq_dreg_16_sreg_8_func,
							post_info->movq_dreg_16_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ_DMEM_8_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_8_sreg_8,
							pre_info->movq_dmem_8_sreg_16_func,
							post_info->movq_dmem_8_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ_DREG_8_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_sreg_8,
							pre_info->movq_dreg_8_sreg_16_func,
							post_info->movq_dreg_8_sreg_16_func };

	/** MOVDQU **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVDQU_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_smem_16,
							pre_info->movdqu_dreg_16_smem_16_func,
							post_info->movdqu_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVDQU_DMEM_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_16_sreg_16,
							pre_info->movdqu_dmem_16_sreg_16_func,
							post_info->movdqu_dmem_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVDQU_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_sreg_16,
							pre_info->movdqu_dreg_16_sreg_16_func,
							post_info->movdqu_dreg_16_sreg_16_func };

	/** MOVDQA **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVDQA_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_smem_16,
							pre_info->movdqa_dreg_16_smem_16_func,
							post_info->movdqa_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVDQA_DMEM_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_16_sreg_16,
							pre_info->movdqa_dmem_16_sreg_16_func,
							post_info->movdqa_dmem_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVDQA_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_sreg_16,
							pre_info->movdqa_dreg_16_sreg_16_func,
							post_info->movdqa_dreg_16_sreg_16_func };

	/** PSHUFW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->pshufw_dreg_8_smem_8_func,
							post_info->pshufw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->pshufw_dreg_8_sreg_8_func,
							post_info->pshufw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_16_smem_16,
							pre_info->pshufw_dreg_16_smem_16_func,
							post_info->pshufw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_16_sreg_16,
							pre_info->pshufw_dreg_16_sreg_16_func,
							post_info->pshufw_dreg_16_sreg_16_func };

	/** PSHUFD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->pshufd_dreg_8_smem_8_func,
							post_info->pshufd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->pshufd_dreg_8_sreg_8_func,
							post_info->pshufd_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_16_smem_16,
							pre_info->pshufd_dreg_16_smem_16_func,
							post_info->pshufd_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_16_sreg_16,
							pre_info->pshufd_dreg_16_sreg_16_func,
							post_info->pshufd_dreg_16_sreg_16_func };

	/** PSHUFHW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFHW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_high_mov_dreg_16_smem_16,
							pre_info->pshufhw_dreg_16_smem_16_func,
							post_info->pshufhw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFHW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_high_mov_dreg_16_sreg_16,
							pre_info->pshufhw_dreg_16_sreg_16_func,
							post_info->pshufhw_dreg_16_sreg_16_func };

	/** PSHUFLW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFLW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->pshuflw_dreg_16_smem_16_func,
							post_info->pshuflw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFLW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->pshuflw_dreg_16_sreg_16_func,
							post_info->pshuflw_dreg_16_sreg_16_func };

	/** PCMPEQB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_8_smem_8,
							pre_info->pcmpeqb_dreg_8_smem_8_func,
							post_info->pcmpeqb_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_8_sreg_8,
							pre_info->pcmpeqb_dreg_8_sreg_8_func,
							post_info->pcmpeqb_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_16_smem_16,
							pre_info->pcmpeqb_dreg_16_smem_16_func,
							post_info->pcmpeqb_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpb_dreg_16_sreg_16,
							pre_info->pcmpeqb_dreg_16_sreg_16_func,
							post_info->pcmpeqb_dreg_16_sreg_16_func };

	/** PCMPEQW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_8_smem_8,
							pre_info->pcmpeqw_dreg_8_smem_8_func,
							post_info->pcmpeqw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_8_sreg_8,
							pre_info->pcmpeqw_dreg_8_sreg_8_func,
							post_info->pcmpeqw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_16_smem_16,
							pre_info->pcmpeqw_dreg_16_smem_16_func,
							post_info->pcmpeqw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpw_dreg_16_sreg_16,
							pre_info->pcmpeqw_dreg_16_sreg_16_func,
							post_info->pcmpeqw_dreg_16_sreg_16_func };

	/** PCMPEQD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_8_smem_8,
							pre_info->pcmpeqd_dreg_8_smem_8_func,
							post_info->pcmpeqd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_8_sreg_8,
							pre_info->pcmpeqd_dreg_8_sreg_8_func,
							post_info->pcmpeqd_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_16_smem_16,
							pre_info->pcmpeqd_dreg_16_smem_16_func,
							post_info->pcmpeqd_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpd_dreg_16_sreg_16,
							pre_info->pcmpeqd_dreg_16_sreg_16_func,
							post_info->pcmpeqd_dreg_16_sreg_16_func };

	/** SHLD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DMEM_2_SREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dmem_2_sreg_2,
							pre_info->shld_dmem_2_sreg_2_simm_1_func,
							post_info->shld_dmem_2_sreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DMEM_4_SREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dmem_4_sreg_4,
							pre_info->shld_dmem_4_sreg_4_simm_1_func,
							post_info->shld_dmem_4_sreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DMEM_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dmem_8_sreg_8,
							pre_info->shld_dmem_8_sreg_8_simm_1_func,
							post_info->shld_dmem_8_sreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DREG_2_SREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->shld_dreg_2_sreg_2_simm_1_func,
							post_info->shld_dreg_2_sreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DREG_4_SREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->shld_dreg_4_sreg_4_simm_1_func,
							post_info->shld_dreg_4_sreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->shld_dreg_8_sreg_8_simm_1_func,
							post_info->shld_dreg_8_sreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DMEM_2_SREG_2_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dmem_2_sreg_2_sreg_1,
							pre_info->shld_dmem_2_sreg_2_sreg_1_func,
							post_info->shld_dmem_2_sreg_2_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DMEM_4_SREG_4_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dmem_4_sreg_4_sreg_1,
							pre_info->shld_dmem_4_sreg_4_sreg_1_func,
							post_info->shld_dmem_4_sreg_4_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DMEM_8_SREG_8_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dmem_8_sreg_8_sreg_1,
							pre_info->shld_dmem_8_sreg_8_sreg_1_func,
							post_info->shld_dmem_8_sreg_8_sreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DREG_2_SREG_2_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dreg_2_sreg_2_sreg_1,
							pre_info->shld_dreg_2_sreg_2_sreg_1_func,
							post_info->shld_dreg_2_sreg_2_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DREG_4_SREG_4_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dreg_4_sreg_4_sreg_1,
							pre_info->shld_dreg_4_sreg_4_sreg_1_func,
							post_info->shld_dreg_4_sreg_4_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHLD_DREG_8_SREG_8_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dreg_8_sreg_8_sreg_1,
							pre_info->shld_dreg_8_sreg_8_sreg_1_func,
							post_info->shld_dreg_8_sreg_8_sreg_1_func };

	/** SHRD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DMEM_2_SREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dmem_2_sreg_2,
							pre_info->shrd_dmem_2_sreg_2_simm_1_func,
							post_info->shrd_dmem_2_sreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DMEM_4_SREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dmem_4_sreg_4,
							pre_info->shrd_dmem_4_sreg_4_simm_1_func,
							post_info->shrd_dmem_4_sreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DMEM_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dmem_8_sreg_8,
							pre_info->shrd_dmem_8_sreg_8_simm_1_func,
							post_info->shrd_dmem_8_sreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DREG_2_SREG_2_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->shrd_dreg_2_sreg_2_simm_1_func,
							post_info->shrd_dreg_2_sreg_2_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DREG_4_SREG_4_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->shrd_dreg_4_sreg_4_simm_1_func,
							post_info->shrd_dreg_4_sreg_4_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->shrd_dreg_8_sreg_8_simm_1_func,
							post_info->shrd_dreg_8_sreg_8_simm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DMEM_2_SREG_2_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dmem_2_sreg_2_sreg_1,
							pre_info->shrd_dmem_2_sreg_2_sreg_1_func,
							post_info->shrd_dmem_2_sreg_2_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DMEM_4_SREG_4_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dmem_4_sreg_4_sreg_1,
							pre_info->shrd_dmem_4_sreg_4_sreg_1_func,
							post_info->shrd_dmem_4_sreg_4_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DMEM_8_SREG_8_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dmem_8_sreg_8_sreg_1,
							pre_info->shrd_dmem_8_sreg_8_sreg_1_func,
							post_info->shrd_dmem_8_sreg_8_sreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DREG_2_SREG_2_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dreg_2_sreg_2_sreg_1,
							pre_info->shrd_dreg_2_sreg_2_sreg_1_func,
							post_info->shrd_dreg_2_sreg_2_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DREG_4_SREG_4_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dreg_4_sreg_4_sreg_1,
							pre_info->shrd_dreg_4_sreg_4_sreg_1_func,
							post_info->shrd_dreg_4_sreg_4_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHRD_DREG_8_SREG_8_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shiftd_dreg_8_sreg_8_sreg_1,
							pre_info->shrd_dreg_8_sreg_8_sreg_1_func,
							post_info->shrd_dreg_8_sreg_8_sreg_1_func };

	/** CMPXCHG **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_1_smem_1,
							pre_info->cmpxchg_sreg_1_smem_1_func,
							post_info->cmpxchg_sreg_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_2_smem_2,
							pre_info->cmpxchg_sreg_2_smem_2_func,
							post_info->cmpxchg_sreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_4_smem_4,
							pre_info->cmpxchg_sreg_4_smem_4_func,
							post_info->cmpxchg_sreg_4_smem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_8_smem_8,
							pre_info->cmpxchg_sreg_8_smem_8_func,
							post_info->cmpxchg_sreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_1_sreg_1,
							pre_info->cmpxchg_sreg_1_sreg_1_func,
							post_info->cmpxchg_sreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_2_sreg_2,
							pre_info->cmpxchg_sreg_2_sreg_2_func,
							post_info->cmpxchg_sreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_4_sreg_4,
							pre_info->cmpxchg_sreg_4_sreg_4_func,
							post_info->cmpxchg_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_CMPXCHG_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_cmpxchg_sreg_8_sreg_8,
							pre_info->cmpxchg_sreg_8_sreg_8_func,
							post_info->cmpxchg_sreg_8_sreg_8_func };

	/** MOVZX **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVZX_DREG_2_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_2_smem_1,
							pre_info->movzx_dreg_2_smem_1_func,
							post_info->movzx_dreg_2_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVZX_DREG_4_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_smem_1,
							pre_info->movzx_dreg_4_smem_1_func,
							post_info->movzx_dreg_4_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVZX_DREG_4_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_smem_2,
							pre_info->movzx_dreg_4_smem_2_func,
							post_info->movzx_dreg_4_smem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVZX_DREG_2_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_2_sreg_1,
							pre_info->movzx_dreg_2_sreg_1_func,
							post_info->movzx_dreg_2_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVZX_DREG_4_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_sreg_1,
							pre_info->movzx_dreg_4_sreg_1_func,
							post_info->movzx_dreg_4_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVZX_DREG_4_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_sreg_2,
							pre_info->movzx_dreg_4_sreg_2_func,
							post_info->movzx_dreg_4_sreg_2_func };

	/** BSF **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSF_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_smem_2,
							pre_info->bsf_dreg_2_smem_2_func,
							post_info->bsf_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSF_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_smem_4,
							pre_info->bsf_dreg_4_smem_4_func,
							post_info->bsf_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSF_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->bsf_dreg_8_smem_8_func,
							post_info->bsf_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSF_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->bsf_dreg_2_sreg_2_func,
							post_info->bsf_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSF_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->bsf_dreg_4_sreg_4_func,
							post_info->bsf_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSF_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->bsf_dreg_8_sreg_8_func,
							post_info->bsf_dreg_8_sreg_8_func };

	/** BSR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSR_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_smem_2,
							pre_info->bsr_dreg_2_smem_2_func,
							post_info->bsr_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSR_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_smem_4,
							pre_info->bsr_dreg_4_smem_4_func,
							post_info->bsr_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSR_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->bsr_dreg_8_smem_8_func,
							post_info->bsr_dreg_8_smem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSR_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->bsr_dreg_2_sreg_2_func,
							post_info->bsr_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSR_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->bsr_dreg_4_sreg_4_func,
							post_info->bsr_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSR_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->bsr_dreg_8_sreg_8_func,
							post_info->bsr_dreg_8_sreg_8_func };

	/** MOVSX **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVSX_DREG_2_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_2_smem_1,
							pre_info->movsx_dreg_2_smem_1_func,
							post_info->movsx_dreg_2_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVSX_DREG_4_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_smem_1,
							pre_info->movsx_dreg_4_smem_1_func,
							post_info->movsx_dreg_4_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVSX_DREG_4_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_smem_2,
							pre_info->movsx_dreg_4_smem_2_func,
							post_info->movsx_dreg_4_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVSX_DREG_2_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_2_sreg_1,
							pre_info->movsx_dreg_2_sreg_1_func,
							post_info->movsx_dreg_2_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVSX_DREG_4_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_sreg_1,
							pre_info->movsx_dreg_4_sreg_1_func,
							post_info->movsx_dreg_4_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVSX_DREG_4_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_movzx_dreg_4_sreg_2,
							pre_info->movsx_dreg_4_sreg_2_func,
							post_info->movsx_dreg_4_sreg_2_func };

	/** XADD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_REG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_reg_1_reg_1,
							pre_info->xadd_reg_1_reg_1_func,
							post_info->xadd_reg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_REG_2_REG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_reg_2_reg_2,
							pre_info->xadd_reg_2_reg_2_func,
							post_info->xadd_reg_2_reg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_REG_4_REG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_reg_4_reg_4,
							pre_info->xadd_reg_4_reg_4_func,
							post_info->xadd_reg_4_reg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_REG_8_REG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_reg_8_reg_8,
							pre_info->xadd_reg_8_reg_8_func,
							post_info->xadd_reg_8_reg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_MEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_mem_1_reg_1,
							pre_info->xadd_mem_1_reg_1_func,
							post_info->xadd_mem_1_reg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_MEM_2_REG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_mem_2_reg_2,
							pre_info->xadd_mem_2_reg_2_func,
							post_info->xadd_mem_2_reg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_MEM_4_REG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_mem_4_reg_4,
							pre_info->xadd_mem_4_reg_4_func,
							post_info->xadd_mem_4_reg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XADD_MEM_8_REG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_xadd_mem_8_reg_8,
							pre_info->xadd_mem_8_reg_8_func,
							post_info->xadd_mem_8_reg_8_func };

	/** PEXT **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXTRW_DREG_4_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pextw_dreg_4_sreg_16,
							pre_info->pextrw_dreg_4_sreg_16_func,
							post_info->pextrw_dreg_4_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXTRW_DREG_4_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pextw_dreg_4_sreg_8,
							pre_info->pextrw_dreg_4_sreg_8_func,
							post_info->pextrw_dreg_4_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXTRW_DMEM_2_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pextw_dmem_2_sreg_16,
							pre_info->pextrw_dmem_2_sreg_16_func,
							post_info->pextrw_dmem_2_sreg_16_func };

	/** BSWAP **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSWAP_DSREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_bswap_dsreg_4,
							pre_info->bswap_dsreg_4_func,
							post_info->bswap_dsreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSWAP_DSREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_bswap_dsreg_8,
							pre_info->bswap_dsreg_8_func,
							post_info->bswap_dsreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSWAP_DSMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_bswap_dsmem_4,
							pre_info->bswap_dsmem_4_func,
							post_info->bswap_dsmem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_BSWAP_DSMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_bswap_dsmem_8,
							pre_info->bswap_dsmem_8_func,
							post_info->bswap_dsmem_8_func };

	/** PSRLW **/

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLW_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->psrlw_dreg_8_sreg_8_sreg_8_func,
							post_info->psrlw_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLW_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->psrlw_dreg_16_sreg_16_sreg_16_func,
							post_info->psrlw_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLW_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->psrlw_dreg_8_sreg_8_smem_8_func,
							post_info->psrlw_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLW_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->psrlw_dreg_16_sreg_16_smem_16_func,
							post_info->psrlw_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLW_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->psrlw_dreg_8_sreg_8_simm_1_func,
							post_info->psrlw_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLW_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psrlw_dreg_16_sreg_16_simm_1_func,
							post_info->psrlw_dreg_16_sreg_16_simm_1_func };

	/** PSRLD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLD_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->psrld_dreg_8_sreg_8_sreg_8_func,
							post_info->psrld_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLD_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->psrld_dreg_16_sreg_16_sreg_16_func,
							post_info->psrld_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLD_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->psrld_dreg_8_sreg_8_smem_8_func,
							post_info->psrld_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLD_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->psrld_dreg_16_sreg_16_smem_16_func,
							post_info->psrld_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLD_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->psrld_dreg_8_sreg_8_simm_1_func,
							post_info->psrld_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLD_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psrld_dreg_16_sreg_16_simm_1_func,
							post_info->psrld_dreg_16_sreg_16_simm_1_func };

	/** PSRLQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLQ_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->psrlq_dreg_8_sreg_8_sreg_8_func,
							post_info->psrlq_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLQ_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->psrlq_dreg_16_sreg_16_sreg_16_func,
							post_info->psrlq_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLQ_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->psrlq_dreg_8_sreg_8_smem_8_func,
							post_info->psrlq_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLQ_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->psrlq_dreg_16_sreg_16_smem_16_func,
							post_info->psrlq_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLQ_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->psrlq_dreg_8_sreg_8_simm_1_func,
							post_info->psrlq_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLQ_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psrlq_dreg_16_sreg_16_simm_1_func,
							post_info->psrlq_dreg_16_sreg_16_simm_1_func };

	/** PADDQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDQ_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pq_src_srcdst_dreg_8_sreg_8,
							pre_info->paddq_dreg_8_sreg_8_func,
							post_info->paddq_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pq_src_srcdst_dreg_16_sreg_16,
							pre_info->paddq_dreg_16_sreg_16_func,
							post_info->paddq_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDQ_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pq_src_srcdst_dreg_8_smem_8,
							pre_info->paddq_dreg_8_smem_8_func,
							post_info->paddq_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pq_src_srcdst_dreg_16_smem_16,
							pre_info->paddq_dreg_16_smem_16_func,
							post_info->paddq_dreg_16_smem_16_func };

	/** PMULLW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULLW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_sreg_8,
							pre_info->pmullw_dreg_8_sreg_8_func,
							post_info->pmullw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULLW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_sreg_16,
							pre_info->pmullw_dreg_16_sreg_16_func,
							post_info->pmullw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULLW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_smem_8,
							pre_info->pmullw_dreg_8_smem_8_func,
							post_info->pmullw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULLW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_smem_16,
							pre_info->pmullw_dreg_16_smem_16_func,
							post_info->pmullw_dreg_16_smem_16_func };

	/** PMOVMSKB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMOVMSK_DREG_4_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmovmsk_dreg_4_sreg_8,
							pre_info->pmovmsk_dreg_4_sreg_8_func,
							post_info->pmovmsk_dreg_4_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMOVMSK_DREG_4_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmovmsk_dreg_4_sreg_16,
							pre_info->pmovmsk_dreg_4_sreg_16_func,
							post_info->pmovmsk_dreg_4_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMOVMSK_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmovmsk_dreg_8_sreg_8,
							pre_info->pmovmsk_dreg_8_sreg_8_func,
							post_info->pmovmsk_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMOVMSK_DREG_8_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmovmsk_dreg_8_sreg_16,
							pre_info->pmovmsk_dreg_8_sreg_16_func,
							post_info->pmovmsk_dreg_8_sreg_16_func };

	/** PMINMAX **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_8_smem_8,
							pre_info->pminub_dreg_8_smem_8_func,
							post_info->pminub_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_8_sreg_8,
							pre_info->pminub_dreg_8_sreg_8_func,
							post_info->pminub_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_smem_16,
							pre_info->pminub_dreg_16_smem_16_func,
							post_info->pminub_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_sreg_16,
							pre_info->pminub_dreg_16_sreg_16_func,
							post_info->pminub_dreg_16_sreg_16_func };

	/** PAND **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PAND_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->pand_dreg_8_sreg_8_func,
							post_info->pand_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PAND_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->pand_dreg_16_sreg_16_func,
							post_info->pand_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PAND_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_smem_8,
							pre_info->pand_dreg_8_smem_8_func,
							post_info->pand_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PAND_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->pand_dreg_16_smem_16_func,
							post_info->pand_dreg_16_smem_16_func };

	/** PMAXUB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_8_smem_8,
							pre_info->pmaxub_dreg_8_smem_8_func,
							post_info->pmaxub_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_8_sreg_8,
							pre_info->pmaxub_dreg_8_sreg_8_func,
							post_info->pmaxub_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_smem_16,
							pre_info->pmaxub_dreg_16_smem_16_func,
							post_info->pmaxub_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_sreg_16,
							pre_info->pmaxub_dreg_16_sreg_16_func,
							post_info->pmaxub_dreg_16_sreg_16_func };

	/** PANDN **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PANDN_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->pandn_dreg_8_sreg_8_func,
							post_info->pandn_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PANDN_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->pandn_dreg_16_sreg_16_func,
							post_info->pandn_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PANDN_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_smem_8,
							pre_info->pandn_dreg_8_smem_8_func,
							post_info->pandn_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PANDN_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->pandn_dreg_16_smem_16_func,
							post_info->pandn_dreg_16_smem_16_func };

	/** PSRAW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAW_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->psraw_dreg_8_sreg_8_sreg_8_func,
							post_info->psraw_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAW_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->psraw_dreg_16_sreg_16_sreg_16_func,
							post_info->psraw_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAW_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->psraw_dreg_8_sreg_8_smem_8_func,
							post_info->psraw_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAW_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->psraw_dreg_16_sreg_16_smem_16_func,
							post_info->psraw_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAW_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->psraw_dreg_8_sreg_8_simm_1_func,
							post_info->psraw_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAW_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psraw_dreg_16_sreg_16_simm_1_func,
							post_info->psraw_dreg_16_sreg_16_simm_1_func };

	/** PSRAD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAD_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->psrad_dreg_8_sreg_8_sreg_8_func,
							post_info->psrad_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAD_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->psrad_dreg_16_sreg_16_sreg_16_func,
							post_info->psrad_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAD_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->psrad_dreg_8_sreg_8_smem_8_func,
							post_info->psrad_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAD_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->psrad_dreg_16_sreg_16_smem_16_func,
							post_info->psrad_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAD_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->psrad_dreg_8_sreg_8_simm_1_func,
							post_info->psrad_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRAD_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psrad_dreg_16_sreg_16_simm_1_func,
							post_info->psrad_dreg_16_sreg_16_simm_1_func };

	/** PMULHUW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHUW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_sreg_8,
							pre_info->pmulhuw_dreg_8_sreg_8_func,
							post_info->pmulhuw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHUW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_sreg_16,
							pre_info->pmulhuw_dreg_16_sreg_16_func,
							post_info->pmulhuw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHUW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_smem_8,
							pre_info->pmulhuw_dreg_8_smem_8_func,
							post_info->pmulhuw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHUW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_smem_16,
							pre_info->pmulhuw_dreg_16_smem_16_func,
							post_info->pmulhuw_dreg_16_smem_16_func };

	/** PMULHW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_sreg_8,
							pre_info->pmulhw_dreg_8_sreg_8_func,
							post_info->pmulhw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_sreg_16,
							pre_info->pmulhw_dreg_16_sreg_16_func,
							post_info->pmulhw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_smem_8,
							pre_info->pmulhw_dreg_8_smem_8_func,
							post_info->pmulhw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULHW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_smem_16,
							pre_info->pmulhw_dreg_16_smem_16_func,
							post_info->pmulhw_dreg_16_smem_16_func };

	/** PMINSW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_8_smem_8,
							pre_info->pminsw_dreg_8_smem_8_func,
							post_info->pminsw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_8_sreg_8,
							pre_info->pminsw_dreg_8_sreg_8_func,
							post_info->pminsw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_smem_16,
							pre_info->pminsw_dreg_16_smem_16_func,
							post_info->pminsw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_sreg_16,
							pre_info->pminsw_dreg_16_sreg_16_func,
							post_info->pminsw_dreg_16_sreg_16_func };

	/** POR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POR_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->por_dreg_8_sreg_8_func,
							post_info->por_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POR_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->por_dreg_16_sreg_16_func,
							post_info->por_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POR_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_smem_8,
							pre_info->por_dreg_8_smem_8_func,
							post_info->por_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POR_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->por_dreg_16_smem_16_func,
							post_info->por_dreg_16_smem_16_func };

	/** PMAXSW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_8_smem_8,
							pre_info->pmaxsw_dreg_8_smem_8_func,
							post_info->pmaxsw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_8_sreg_8,
							pre_info->pmaxsw_dreg_8_sreg_8_func,
							post_info->pmaxsw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_smem_16,
							pre_info->pmaxsw_dreg_16_smem_16_func,
							post_info->pmaxsw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_sreg_16,
							pre_info->pmaxsw_dreg_16_sreg_16_func,
							post_info->pmaxsw_dreg_16_sreg_16_func };

	/** PXOR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PXOR_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_sreg_8,
							pre_info->pxor_dreg_8_sreg_8_func,
							post_info->pxor_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PXOR_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->pxor_dreg_16_sreg_16_func,
							post_info->pxor_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PXOR_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_8_smem_8,
							pre_info->pxor_dreg_8_smem_8_func,
							post_info->pxor_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PXOR_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->pxor_dreg_16_smem_16_func,
							post_info->pxor_dreg_16_smem_16_func };

	/** PSLLW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLW_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->psllw_dreg_8_sreg_8_sreg_8_func,
							post_info->psllw_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLW_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->psllw_dreg_16_sreg_16_sreg_16_func,
							post_info->psllw_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLW_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->psllw_dreg_8_sreg_8_smem_8_func,
							post_info->psllw_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLW_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->psllw_dreg_16_sreg_16_smem_16_func,
							post_info->psllw_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLW_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->psllw_dreg_8_sreg_8_simm_1_func,
							post_info->psllw_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLW_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psllw_dreg_16_sreg_16_simm_1_func,
							post_info->psllw_dreg_16_sreg_16_simm_1_func };

	/** PSLLD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLD_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->pslld_dreg_8_sreg_8_sreg_8_func,
							post_info->pslld_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLD_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->pslld_dreg_16_sreg_16_sreg_16_func,
							post_info->pslld_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLD_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->pslld_dreg_8_sreg_8_smem_8_func,
							post_info->pslld_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLD_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->pslld_dreg_16_sreg_16_smem_16_func,
							post_info->pslld_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLD_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->pslld_dreg_8_sreg_8_simm_1_func,
							post_info->pslld_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLD_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->pslld_dreg_16_sreg_16_simm_1_func,
							post_info->pslld_dreg_16_sreg_16_simm_1_func };

	/** PSLLQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLQ_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->psllq_dreg_8_sreg_8_sreg_8_func,
							post_info->psllq_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLQ_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->psllq_dreg_16_sreg_16_sreg_16_func,
							post_info->psllq_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLQ_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->psllq_dreg_8_sreg_8_smem_8_func,
							post_info->psllq_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLQ_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->psllq_dreg_16_sreg_16_smem_16_func,
							post_info->psllq_dreg_16_sreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLQ_DREG_8_SREG_8_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->psllq_dreg_8_sreg_8_simm_1_func,
							post_info->psllq_dreg_8_sreg_8_simm_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLQ_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psllq_dreg_16_sreg_16_simm_1_func,
							post_info->psllq_dreg_16_sreg_16_simm_1_func };

	/** PMADDWD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMADDWD_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmaddwd_dreg_8_sreg_8,
							pre_info->pmaddwd_dreg_8_sreg_8_sreg_8_func,
							post_info->pmaddwd_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMADDWD_DREG_16_SREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmaddwd_dreg_16_sreg_16,
							pre_info->pmaddwd_dreg_16_sreg_16_sreg_16_func,
							post_info->pmaddwd_dreg_16_sreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMADDWD_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmaddwd_dreg_8_smem_8,
							pre_info->pmaddwd_dreg_8_sreg_8_smem_8_func,
							post_info->pmaddwd_dreg_8_sreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMADDWD_DREG_16_SREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pmaddwd_dreg_16_smem_16,
							pre_info->pmaddwd_dreg_16_sreg_16_smem_16_func,
							post_info->pmaddwd_dreg_16_sreg_16_smem_16_func };

	/** PSUBB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pb_src_srcdst_dreg_8_sreg_8,
							pre_info->psubb_dreg_8_sreg_8_func,
							post_info->psubb_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pb_src_srcdst_dreg_16_sreg_16,
							pre_info->psubb_dreg_16_sreg_16_func,
							post_info->psubb_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pb_src_srcdst_dreg_8_smem_8,
							pre_info->psubb_dreg_8_smem_8_func,
							post_info->psubb_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pb_src_srcdst_dreg_16_smem_16,
							pre_info->psubb_dreg_16_smem_16_func,
							post_info->psubb_dreg_16_smem_16_func };

	/** PSUBW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_sreg_8,
							pre_info->psubw_dreg_8_sreg_8_func,
							post_info->psubw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_sreg_16,
							pre_info->psubw_dreg_16_sreg_16_func,
							post_info->psubw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_smem_8,
							pre_info->psubw_dreg_8_smem_8_func,
							post_info->psubw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_smem_16,
							pre_info->psubw_dreg_16_smem_16_func,
							post_info->psubw_dreg_16_smem_16_func };

	/** PSUBD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pd_src_srcdst_dreg_8_sreg_8,
							pre_info->psubd_dreg_8_sreg_8_func,
							post_info->psubd_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pd_src_srcdst_dreg_16_sreg_16,
							pre_info->psubd_dreg_16_sreg_16_func,
							post_info->psubd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pd_src_srcdst_dreg_8_smem_8,
							pre_info->psubd_dreg_8_smem_8_func,
							post_info->psubd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pd_src_srcdst_dreg_16_smem_16,
							pre_info->psubd_dreg_16_smem_16_func,
							post_info->psubd_dreg_16_smem_16_func };

	/** PSUBQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBQ_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pq_src_srcdst_dreg_8_sreg_8,
							pre_info->psubq_dreg_8_sreg_8_func,
							post_info->psubq_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pq_src_srcdst_dreg_16_sreg_16,
							pre_info->psubq_dreg_16_sreg_16_func,
							post_info->psubq_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBQ_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pq_src_srcdst_dreg_8_smem_8,
							pre_info->psubq_dreg_8_smem_8_func,
							post_info->psubq_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSUBQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pq_src_srcdst_dreg_16_smem_16,
							pre_info->psubq_dreg_16_smem_16_func,
							post_info->psubq_dreg_16_smem_16_func };

	/** PADDB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pb_src_srcdst_dreg_8_sreg_8,
							pre_info->paddb_dreg_8_sreg_8_func,
							post_info->paddb_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pb_src_srcdst_dreg_16_sreg_16,
							pre_info->paddb_dreg_16_sreg_16_func,
							post_info->paddb_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pb_src_srcdst_dreg_8_smem_8,
							pre_info->paddb_dreg_8_smem_8_func,
							post_info->paddb_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pb_src_srcdst_dreg_16_smem_16,
							pre_info->paddb_dreg_16_smem_16_func,
							post_info->paddb_dreg_16_smem_16_func };

	/** PADDW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDW_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_sreg_8,
							pre_info->paddw_dreg_8_sreg_8_func,
							post_info->paddw_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_sreg_16,
							pre_info->paddw_dreg_16_sreg_16_func,
							post_info->paddw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDW_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pw_src_srcdst_dreg_8_smem_8,
							pre_info->paddw_dreg_8_smem_8_func,
							post_info->paddw_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pw_src_srcdst_dreg_16_smem_16,
							pre_info->paddw_dreg_16_smem_16_func,
							post_info->paddw_dreg_16_smem_16_func };

	/** PADDD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDD_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pd_src_srcdst_dreg_8_sreg_8,
							pre_info->paddd_dreg_8_sreg_8_func,
							post_info->paddd_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pd_src_srcdst_dreg_16_sreg_16,
							pre_info->paddd_dreg_16_sreg_16_func,
							post_info->paddd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDD_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pd_src_srcdst_dreg_8_smem_8,
							pre_info->paddd_dreg_8_smem_8_func,
							post_info->paddd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PADDD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pd_src_srcdst_dreg_16_smem_16,
							pre_info->paddd_dreg_16_smem_16_func,
							post_info->paddd_dreg_16_smem_16_func };

	/** PSRLDQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSRLDQ_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->psrldq_dreg_16_sreg_16_simm_1_func,
							post_info->psrldq_dreg_16_sreg_16_simm_1_func };

	// OP_PSLLDQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSLLDQ_DREG_16_SREG_16_SIMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_16,
							pre_info->pslldq_dreg_16_sreg_16_simm_1_func,
							post_info->pslldq_dreg_16_sreg_16_simm_1_func };

	/** ROL**/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->rol_sole_dreg_1_func,
							post_info->rol_sole_dreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rol_sole_dreg_2_func,
							post_info->rol_sole_dreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->rol_sole_dreg_4_func,
							post_info->rol_sole_dreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rol_sole_dreg_8_func,
							post_info->rol_sole_dreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->rol_dreg_1_imm_1_func,
							post_info->rol_dreg_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rol_dreg_2_imm_1_func,
							post_info->rol_dreg_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->rol_dreg_4_imm_1_func,
							post_info->rol_dreg_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rol_dreg_8_imm_1_func,
							post_info->rol_dreg_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->rol_dreg_1_reg_1_func,
							post_info->rol_dreg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->rol_dreg_2_reg_1_func,
							post_info->rol_dreg_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->rol_dreg_4_reg_1_func,
							post_info->rol_dreg_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DREG_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->rol_dreg_8_reg_1_func,
							post_info->rol_dreg_8_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->rol_sole_dmem_1_func,
							post_info->rol_sole_dmem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->rol_sole_dmem_2_func,
							post_info->rol_sole_dmem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->rol_sole_dmem_4_func,
							post_info->rol_sole_dmem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_SOLE_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->rol_sole_dmem_8_func,
							post_info->rol_sole_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->rol_dmem_1_imm_1_func,
							post_info->rol_dmem_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->rol_dmem_2_imm_1_func,
							post_info->rol_dmem_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->rol_dmem_4_imm_1_func,
							post_info->rol_dmem_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->rol_dmem_8_imm_1_func,
							post_info->rol_dmem_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_1_sreg_1,
							pre_info->rol_dmem_1_reg_1_func,
							post_info->rol_dmem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_2_sreg_1,
							pre_info->rol_dmem_2_reg_1_func,
							post_info->rol_dmem_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_4_sreg_1,
							pre_info->rol_dmem_4_reg_1_func,
							post_info->rol_dmem_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROL_DMEM_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_8_sreg_1,
							pre_info->rol_dmem_8_reg_1_func,
							post_info->rol_dmem_8_reg_1_func };

	/** ROR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->ror_sole_dreg_1_func,
							post_info->ror_sole_dreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->ror_sole_dreg_2_func,
							post_info->ror_sole_dreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->ror_sole_dreg_4_func,
							post_info->ror_sole_dreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->ror_sole_dreg_8_func,
							post_info->ror_sole_dreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->ror_dreg_1_imm_1_func,
							post_info->ror_dreg_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->ror_dreg_2_imm_1_func,
							post_info->ror_dreg_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->ror_dreg_4_imm_1_func,
							post_info->ror_dreg_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->ror_dreg_8_imm_1_func,
							post_info->ror_dreg_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->ror_dreg_1_reg_1_func,
							post_info->ror_dreg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->ror_dreg_2_reg_1_func,
							post_info->ror_dreg_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->ror_dreg_4_reg_1_func,
							post_info->ror_dreg_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DREG_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->ror_dreg_8_reg_1_func,
							post_info->ror_dreg_8_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->ror_sole_dmem_1_func,
							post_info->ror_sole_dmem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->ror_sole_dmem_2_func,
							post_info->ror_sole_dmem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->ror_sole_dmem_4_func,
							post_info->ror_sole_dmem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_SOLE_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->ror_sole_dmem_8_func,
							post_info->ror_sole_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->ror_dmem_1_imm_1_func,
							post_info->ror_dmem_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->ror_dmem_2_imm_1_func,
							post_info->ror_dmem_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->ror_dmem_4_imm_1_func,
							post_info->ror_dmem_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->ror_dmem_8_imm_1_func,
							post_info->ror_dmem_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_1_sreg_1,
							pre_info->ror_dmem_1_reg_1_func,
							post_info->ror_dmem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_2_sreg_1,
							pre_info->ror_dmem_2_reg_1_func,
							post_info->ror_dmem_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_4_sreg_1,
							pre_info->ror_dmem_4_reg_1_func,
							post_info->ror_dmem_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ROR_DMEM_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_8_sreg_1,
							pre_info->ror_dmem_8_reg_1_func,
							post_info->ror_dmem_8_reg_1_func };

	/** RCL **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->rcl_sole_dreg_1_func,
							post_info->rcl_sole_dreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rcl_sole_dreg_2_func,
							post_info->rcl_sole_dreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->rcl_sole_dreg_4_func,
							post_info->rcl_sole_dreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rcl_sole_dreg_8_func,
							post_info->rcl_sole_dreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->rcl_dreg_1_imm_1_func,
							post_info->rcl_dreg_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rcl_dreg_2_imm_1_func,
							post_info->rcl_dreg_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->rcl_dreg_4_imm_1_func,
							post_info->rcl_dreg_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rcl_dreg_8_imm_1_func,
							post_info->rcl_dreg_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->rcl_dreg_1_reg_1_func,
							post_info->rcl_dreg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->rcl_dreg_2_reg_1_func,
							post_info->rcl_dreg_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->rcl_dreg_4_reg_1_func,
							post_info->rcl_dreg_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DREG_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->rcl_dreg_8_reg_1_func,
							post_info->rcl_dreg_8_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->rcl_sole_dmem_1_func,
							post_info->rcl_sole_dmem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rcl_sole_dmem_2_func,
							post_info->rcl_sole_dmem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->rcl_sole_dmem_4_func,
							post_info->rcl_sole_dmem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_SOLE_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rcl_sole_dmem_8_func,
							post_info->rcl_sole_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->rcl_dmem_1_imm_1_func,
							post_info->rcl_dmem_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rcl_dmem_2_imm_1_func,
							post_info->rcl_dmem_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->rcl_dmem_4_imm_1_func,
							post_info->rcl_dmem_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rcl_dmem_8_imm_1_func,
							post_info->rcl_dmem_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->rcl_dmem_1_reg_1_func,
							post_info->rcl_dmem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->rcl_dmem_2_reg_1_func,
							post_info->rcl_dmem_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->rcl_dmem_4_reg_1_func,
							post_info->rcl_dmem_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCL_DMEM_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->rcl_dmem_8_reg_1_func,
							post_info->rcl_dmem_8_reg_1_func };

	/** RCR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->rcr_sole_dreg_1_func,
							post_info->rcr_sole_dreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rcr_sole_dreg_2_func,
							post_info->rcr_sole_dreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->rcr_sole_dreg_4_func,
							post_info->rcr_sole_dreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rcr_sole_dreg_8_func,
							post_info->rcr_sole_dreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->rcr_dreg_1_imm_1_func,
							post_info->rcr_dreg_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->rcr_dreg_2_imm_1_func,
							post_info->rcr_dreg_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->rcr_dreg_4_imm_1_func,
							post_info->rcr_dreg_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->rcr_dreg_8_imm_1_func,
							post_info->rcr_dreg_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->rcr_dreg_1_reg_1_func,
							post_info->rcr_dreg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->rcr_dreg_2_reg_1_func,
							post_info->rcr_dreg_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->rcr_dreg_4_reg_1_func,
							post_info->rcr_dreg_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DREG_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->rcr_dreg_8_reg_1_func,
							post_info->rcr_dreg_8_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->rcr_sole_dmem_1_func,
							post_info->rcr_sole_dmem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->rcr_sole_dmem_2_func,
							post_info->rcr_sole_dmem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->rcr_sole_dmem_4_func,
							post_info->rcr_sole_dmem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_SOLE_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->rcr_sole_dmem_8_func,
							post_info->rcr_sole_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->rcr_dmem_1_imm_1_func,
							post_info->rcr_dmem_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->rcr_dmem_2_imm_1_func,
							post_info->rcr_dmem_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->rcr_dmem_4_imm_1_func,
							post_info->rcr_dmem_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->rcr_dmem_8_imm_1_func,
							post_info->rcr_dmem_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_1_sreg_1,
							pre_info->rcr_dmem_1_reg_1_func,
							post_info->rcr_dmem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_2_sreg_1,
							pre_info->rcr_dmem_2_reg_1_func,
							post_info->rcr_dmem_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_4_sreg_1,
							pre_info->rcr_dmem_4_reg_1_func,
							post_info->rcr_dmem_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_RCR_DMEM_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_8_sreg_1,
							pre_info->rcr_dmem_8_reg_1_func,
							post_info->rcr_dmem_8_reg_1_func };

	/** SHL **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->shl_sole_dreg_1_func,
							post_info->shl_sole_dreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->shl_sole_dreg_2_func,
							post_info->shl_sole_dreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->shl_sole_dreg_4_func,
							post_info->shl_sole_dreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->shl_sole_dreg_8_func,
							post_info->shl_sole_dreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->shl_dreg_1_imm_1_func,
							post_info->shl_dreg_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->shl_dreg_2_imm_1_func,
							post_info->shl_dreg_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->shl_dreg_4_imm_1_func,
							post_info->shl_dreg_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->shl_dreg_8_imm_1_func,
							post_info->shl_dreg_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->shl_dreg_1_reg_1_func,
							post_info->shl_dreg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->shl_dreg_2_reg_1_func,
							post_info->shl_dreg_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->shl_dreg_4_reg_1_func,
							post_info->shl_dreg_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DREG_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->shl_dreg_8_reg_1_func,
							post_info->shl_dreg_8_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->shl_sole_dmem_1_func,
							post_info->shl_sole_dmem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->shl_sole_dmem_2_func,
							post_info->shl_sole_dmem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->shl_sole_dmem_4_func,
							post_info->shl_sole_dmem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_SOLE_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->shl_sole_dmem_8_func,
							post_info->shl_sole_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->shl_dmem_1_imm_1_func,
							post_info->shl_dmem_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->shl_dmem_2_imm_1_func,
							post_info->shl_dmem_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->shl_dmem_4_imm_1_func,
							post_info->shl_dmem_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->shl_dmem_8_imm_1_func,
							post_info->shl_dmem_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_1_sreg_1,
							pre_info->shl_dmem_1_reg_1_func,
							post_info->shl_dmem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_2_sreg_1,
							pre_info->shl_dmem_2_reg_1_func,
							post_info->shl_dmem_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_4_sreg_1,
							pre_info->shl_dmem_4_reg_1_func,
							post_info->shl_dmem_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHL_DMEM_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_8_sreg_1,
							pre_info->shl_dmem_8_reg_1_func,
							post_info->shl_dmem_8_reg_1_func };

	/** SHR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->shr_sole_dreg_1_func,
							post_info->shr_sole_dreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->shr_sole_dreg_2_func,
							post_info->shr_sole_dreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->shr_sole_dreg_4_func,
							post_info->shr_sole_dreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->shr_sole_dreg_8_func,
							post_info->shr_sole_dreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->shr_dreg_1_imm_1_func,
							post_info->shr_dreg_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->shr_dreg_2_imm_1_func,
							post_info->shr_dreg_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->shr_dreg_4_imm_1_func,
							post_info->shr_dreg_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->shr_dreg_8_imm_1_func,
							post_info->shr_dreg_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->shr_dreg_1_reg_1_func,
							post_info->shr_dreg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->shr_dreg_2_reg_1_func,
							post_info->shr_dreg_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->shr_dreg_4_reg_1_func,
							post_info->shr_dreg_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DREG_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->shr_dreg_8_reg_1_func,
							post_info->shr_dreg_8_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->shr_sole_dmem_1_func,
							post_info->shr_sole_dmem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->shr_sole_dmem_2_func,
							post_info->shr_sole_dmem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->shr_sole_dmem_4_func,
							post_info->shr_sole_dmem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_SOLE_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->shr_sole_dmem_8_func,
							post_info->shr_sole_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->shr_dmem_1_imm_1_func,
							post_info->shr_dmem_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->shr_dmem_2_imm_1_func,
							post_info->shr_dmem_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->shr_dmem_4_imm_1_func,
							post_info->shr_dmem_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->shr_dmem_8_imm_1_func,
							post_info->shr_dmem_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_1_sreg_1,
							pre_info->shr_dmem_1_reg_1_func,
							post_info->shr_dmem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_2_sreg_1,
							pre_info->shr_dmem_2_reg_1_func,
							post_info->shr_dmem_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_4_sreg_1,
							pre_info->shr_dmem_4_reg_1_func,
							post_info->shr_dmem_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SHR_DMEM_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_8_sreg_1,
							pre_info->shr_dmem_8_reg_1_func,
							post_info->shr_dmem_8_reg_1_func };

	/** SAR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->sar_sole_dreg_1_func,
							post_info->sar_sole_dreg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->sar_sole_dreg_2_func,
							post_info->sar_sole_dreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->sar_sole_dreg_4_func,
							post_info->sar_sole_dreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->sar_sole_dreg_8_func,
							post_info->sar_sole_dreg_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->sar_dreg_1_imm_1_func,
							post_info->sar_dreg_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->sar_dreg_2_imm_1_func,
							post_info->sar_dreg_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->sar_dreg_4_imm_1_func,
							post_info->sar_dreg_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->sar_dreg_8_imm_1_func,
							post_info->sar_dreg_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_1_sreg_1,
							pre_info->sar_dreg_1_reg_1_func,
							post_info->sar_dreg_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_2_sreg_1,
							pre_info->sar_dreg_2_reg_1_func,
							post_info->sar_dreg_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_4_sreg_1,
							pre_info->sar_dreg_4_reg_1_func,
							post_info->sar_dreg_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DREG_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsreg_8_sreg_1,
							pre_info->sar_dreg_8_reg_1_func,
							post_info->sar_dreg_8_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->shr_sole_dmem_1_func,
							post_info->shr_sole_dmem_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->shr_sole_dmem_2_func,
							post_info->sar_sole_dmem_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->sar_sole_dmem_4_func,
							post_info->sar_sole_dmem_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_SOLE_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->sar_sole_dmem_8_func,
							post_info->sar_sole_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_1_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->sar_dmem_1_imm_1_func,
							post_info->sar_dmem_1_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_2_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->sar_dmem_2_imm_1_func,
							post_info->sar_dmem_2_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_4_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->sar_dmem_4_imm_1_func,
							post_info->sar_dmem_4_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_8_IMM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->sar_dmem_8_imm_1_func,
							post_info->sar_dmem_8_imm_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_1_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_1_sreg_1,
							pre_info->sar_dmem_1_reg_1_func,
							post_info->sar_dmem_1_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_2_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_2_sreg_1,
							pre_info->sar_dmem_2_reg_1_func,
							post_info->sar_dmem_2_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_4_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_4_sreg_1,
							pre_info->sar_dmem_4_reg_1_func,
							post_info->sar_dmem_4_reg_1_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_SAR_DMEM_8_REG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_shift_dsmem_8_sreg_1,
							pre_info->sar_dmem_8_reg_1_func,
							post_info->sar_dmem_8_reg_1_func };

	/** NOT **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DMEM_1_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->not_dmem_1_dmem_1_func,
							post_info->not_dmem_1_dmem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DMEM_2_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->not_dmem_2_dmem_2_func,
							post_info->not_dmem_2_dmem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DMEM_4_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->not_dmem_4_dmem_4_func,
							post_info->not_dmem_4_dmem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DMEM_8_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->not_dmem_8_dmem_8_func,
							post_info->not_dmem_8_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DREG_1_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->not_dreg_1_dreg_1_func,
							post_info->not_dreg_1_dreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DREG_2_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->not_dreg_2_dreg_2_func,
							post_info->not_dreg_2_dreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DREG_4_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->not_dreg_4_dreg_4_func,
							post_info->not_dreg_4_dreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NOT_DREG_8_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->not_dreg_8_dreg_8_func,
							post_info->not_dreg_8_dreg_8_func };

	/** NEG **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DMEM_1_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_1,
							pre_info->neg_dmem_1_dmem_1_func,
							post_info->neg_dmem_1_dmem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DMEM_2_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_2,
							pre_info->neg_dmem_2_dmem_2_func,
							post_info->neg_dmem_2_dmem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DMEM_4_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_4,
							pre_info->neg_dmem_4_dmem_4_func,
							post_info->neg_dmem_4_dmem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DMEM_8_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsmem_8,
							pre_info->neg_dmem_8_dmem_8_func,
							post_info->neg_dmem_8_dmem_8_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DREG_1_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_1,
							pre_info->neg_dreg_1_dreg_1_func,
							post_info->neg_dreg_1_dreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DREG_2_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_2,
							pre_info->neg_dreg_2_dreg_2_func,
							post_info->neg_dreg_2_dreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DREG_4_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_4,
							pre_info->neg_dreg_4_dreg_4_func,
							post_info->neg_dreg_4_dreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_NEG_DREG_8_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_srcdst_dsreg_8,
							pre_info->neg_dreg_8_dreg_8_func,
							post_info->neg_dreg_8_dreg_8_func };

	/** MUL **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MUL_DREG_2_SREG_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_2_sreg_1_sreg_1,
							pre_info->mul_dreg_2_sreg_1_sreg_1_func,
							post_info->mul_dreg_2_sreg_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MUL_DREG_2_SMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_2_smem_1_sreg_1,
							pre_info->mul_dreg_2_smem_1_sreg_1_func,
							post_info->mul_dreg_2_smem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MUL_DREG_4_DREG_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4,
							pre_info->mul_dreg_4_dreg_4_sreg_4_sreg_4_func,
							post_info->mul_dreg_4_dreg_4_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MUL_DREG_4_DREG_4_SMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4,
							pre_info->mul_dreg_4_dreg_4_smem_4_sreg_4_func,
							post_info->mul_dreg_4_dreg_4_smem_4_sreg_4_func };

	/** DIV **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DIV_DREG_4_DREG_4_SMEM_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_smem_4_sreg_4_sreg_4,
							pre_info->div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_func,
							post_info->div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DIV_DREG_4_DREG_4_SREG_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4,
							pre_info->div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_func,
							post_info->div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DIV_DREG_1_DREG_1_SREG_1_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_dreg_1_dreg_1_sreg_1_sreg_2,
							pre_info->div_dreg_1_dreg_1_sreg_1_sreg_2_func,
							post_info->div_dreg_1_dreg_1_sreg_1_sreg_2_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_DIV_DREG_1_DREG_1_SMEM_1_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_dreg_1_dreg_1_smem_1_sreg_2,
							pre_info->div_dreg_1_dreg_1_smem_1_sreg_2_func,
							post_info->div_dreg_1_dreg_1_smem_1_sreg_2_func };

	/** IDIV **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IDIV_DREG_4_DREG_4_SMEM_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_smem_4_sreg_4_sreg_4,
							pre_info->idiv_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_func,
							post_info->idiv_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IDIV_DREG_4_DREG_4_SREG_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_src_dst_dst_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4,
							pre_info->idiv_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_func,
							post_info->idiv_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IDIV_DREG_1_DREG_1_SREG_1_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_dreg_1_dreg_1_sreg_1_sreg_2,
							pre_info->idiv_dreg_1_dreg_1_sreg_1_sreg_2_func,
							post_info->idiv_dreg_1_dreg_1_sreg_1_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_IDIV_DREG_1_DREG_1_SMEM_1_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_dst_dreg_1_dreg_1_smem_1_sreg_2,
							pre_info->idiv_dreg_1_dreg_1_smem_1_sreg_2_func,
							post_info->idiv_dreg_1_dreg_1_smem_1_sreg_2_func };

	/** MOVUPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVUPS_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_smem_16,
							pre_info->movups_dreg_16_smem_16_func,
							post_info->movups_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVUPS_DMEM_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_16_sreg_16,
							pre_info->movups_dmem_16_sreg_16_func,
							post_info->movups_dmem_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVUPS_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_sreg_16,
							pre_info->movups_dreg_16_sreg_16_func,
							post_info->movups_dreg_16_sreg_16_func };

	/** MOVUPD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVUPD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_smem_16,
							pre_info->movupd_dreg_16_smem_16_func,
							post_info->movupd_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVUPD_DMEM_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_16_sreg_16,
							pre_info->movupd_dmem_16_sreg_16_func,
							post_info->movupd_dmem_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVUPD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_sreg_16,
							pre_info->movupd_dreg_16_sreg_16_func,
							post_info->movupd_dreg_16_sreg_16_func };

	/** MOVLPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVLPS_DREG_16_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_smem_8,
							pre_info->movlps_dreg_16_smem_8_func,
							post_info->movlps_dreg_16_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVLPS_DMEM_8_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_8_sreg_16,
							pre_info->movlps_dmem_8_sreg_16_func,
							post_info->movlps_dmem_8_sreg_16_func };

	/** MOVLPD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVLPD_DREG_16_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_smem_8,
							pre_info->movlpd_dreg_8_smem_8_func,
							post_info->movlpd_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVLPD_DMEM_8_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_8_sreg_8,
							pre_info->movlpd_dmem_8_sreg_8_func,
							post_info->movlpd_dmem_8_sreg_8_func };

	/** MOVAPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVAPS_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_smem_16,
							pre_info->movaps_dreg_16_smem_16_func,
							post_info->movaps_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVAPS_DMEM_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_16_sreg_16,
							pre_info->movaps_dmem_16_sreg_16_func,
							post_info->movaps_dmem_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVAPS_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_sreg_16,
							pre_info->movaps_dreg_16_sreg_16_func,
							post_info->movaps_dreg_16_sreg_16_func };

	/** ANDPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDPS_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->andps_dreg_16_sreg_16_func,
							post_info->andps_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDPS_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->andps_dreg_16_smem_16_func,
							post_info->andps_dreg_16_smem_16_func };

	/** ANDPD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDPD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->andpd_dreg_16_sreg_16_func,
							post_info->andpd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDPD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->andpd_dreg_16_smem_16_func,
							post_info->andpd_dreg_16_smem_16_func };

	/** ANDNPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDNPS_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->andnps_dreg_16_sreg_16_func,
							post_info->andnps_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDNPS_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->andnps_dreg_16_smem_16_func,
							post_info->andnps_dreg_16_smem_16_func };

	/** ANDNPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDNPD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->andnpd_dreg_16_sreg_16_func,
							post_info->andnpd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ANDNPD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->andnpd_dreg_16_smem_16_func,
							post_info->andnpd_dreg_16_smem_16_func };

	/** ORPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ORPS_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->orps_dreg_16_sreg_16_func,
							post_info->orps_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ORPS_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->orps_dreg_16_smem_16_func,
							post_info->orps_dreg_16_smem_16_func };

	/** ORPD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ORPD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->orpd_dreg_16_sreg_16_func,
							post_info->orpd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_ORPD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->orpd_dreg_16_smem_16_func,
							post_info->orpd_dreg_16_smem_16_func };

	/** XORPS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XORPS_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->xorps_dreg_16_sreg_16_func,
							post_info->xorps_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XORPS_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->xorps_dreg_16_smem_16_func,
							post_info->xorps_dreg_16_smem_16_func };

	/** XORPD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XORPD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->xorpd_dreg_16_sreg_16_func,
							post_info->xorpd_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_XORPD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_smem_16,
							pre_info->xorpd_dreg_16_smem_16_func,
							post_info->xorpd_dreg_16_smem_16_func };

	/** MOVS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVS_DMEM_1_SMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_1_smem_1,
							pre_info->movs_dmem_1_smem_1_func,
							post_info->movs_dmem_1_smem_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVS_DMEM_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_2_smem_2,
							pre_info->movs_dmem_2_smem_2_func,
							post_info->movs_dmem_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVS_DMEM_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_4_smem_4,
							pre_info->movs_dmem_4_smem_4_func,
							post_info->movs_dmem_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVS_DMEM_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_8_smem_8,
							pre_info->movs_dmem_8_smem_8_func,
							post_info->movs_dmem_8_smem_8_func };

	/** REP_MOVS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_MOVSB] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_movsb,
							pre_info->rep_movsb_func, post_info->rep_movsb_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_MOVSW] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_movsw,
							pre_info->rep_movsw_func, post_info->rep_movsw_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_MOVSD] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_movsd,
							pre_info->rep_movsd_func, post_info->rep_movsd_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_MOVSQ] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_movsq,
							pre_info->rep_movsq_func, post_info->rep_movsq_func };

	/** STOS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_STOS_DMEM_1_SREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_1_sreg_1,
							pre_info->stos_dmem_1_sreg_1_func,
							post_info->stos_dmem_1_sreg_1_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_STOS_DMEM_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_2_sreg_2,
							pre_info->stos_dmem_2_sreg_2_func,
							post_info->stos_dmem_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_STOS_DMEM_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_4_sreg_4,
							pre_info->stos_dmem_4_sreg_4_func,
							post_info->stos_dmem_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_STOS_DMEM_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dmem_8_sreg_8,
							pre_info->stos_dmem_8_sreg_8_func,
							post_info->stos_dmem_8_sreg_8_func };

	/** REP_STOS **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_STOSB] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_stosb,
							pre_info->rep_stosb_func, post_info->rep_stosb_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_STOSW] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_stosw,
							pre_info->rep_stosw_func, post_info->rep_stosw_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_STOSD] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_stosd,
							pre_info->rep_stosd_func, post_info->rep_stosd_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_REP_STOSQ] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_CONC_INFO | IB_OPT_FLAG_INFO,
							tb_cc_byt_execute_rep_stosq,
							pre_info->rep_stosq_func, post_info->rep_stosq_func };

	/** LDDQU **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LDDQU_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_16_smem_16,
							pre_info->lddqu_dreg_16_smem_16_func,
							post_info->lddqu_dreg_16_smem_16_func };

	/** PSHUFB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFB_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->pshufb_dreg_8_smem_8_func,
							post_info->pshufb_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFB_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->pshufb_dreg_8_sreg_8_func,
							post_info->pshufb_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->pshufb_dreg_16_smem_16_func,
							post_info->pshufb_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PSHUFB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_sreg_16,
							pre_info->pshufb_dreg_16_sreg_16_func,
							post_info->pshufb_dreg_16_sreg_16_func };

	/** PALIGNR **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PALIGNR_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_smem_8,
							pre_info->palignr_dreg_8_smem_8_func,
							post_info->palignr_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PALIGNR_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_8_sreg_8,
							pre_info->palignr_dreg_8_sreg_8_func,
							post_info->palignr_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PALIGNR_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_whole_src_srcdst_dreg_16_smem_16,
							pre_info->palignr_dreg_16_smem_16_func,
							post_info->palignr_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PALIGNR_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_src_srcdst_dreg_16_sreg_16,
							pre_info->palignr_dreg_16_sreg_16_func,
							post_info->palignr_dreg_16_sreg_16_func };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POPCNT_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->popcnt_dreg_2_sreg_2_func,
							post_info->popcnt_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POPCNT_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_smem_2,
							pre_info->popcnt_dreg_2_smem_2_func,
							post_info->popcnt_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POPCNT_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->popcnt_dreg_4_sreg_4_func,
							post_info->popcnt_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POPCNT_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_smem_4,
							pre_info->popcnt_dreg_4_smem_4_func,
							post_info->popcnt_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POPCNT_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->popcnt_dreg_8_sreg_8_func,
							post_info->popcnt_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_POPCNT_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->popcnt_dreg_8_smem_8_func,
							post_info->popcnt_dreg_8_smem_8_func };

	/** LZCNT **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LZCNT_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_smem_2,
							pre_info->lzcnt_dreg_2_smem_2_func,
							post_info->lzcnt_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LZCNT_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_smem_4,
							pre_info->lzcnt_dreg_4_smem_4_func,
							post_info->lzcnt_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LZCNT_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->lzcnt_dreg_8_smem_8_func,
							post_info->lzcnt_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LZCNT_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->lzcnt_dreg_2_sreg_2_func,
							post_info->lzcnt_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LZCNT_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->lzcnt_dreg_4_sreg_4_func,
							post_info->lzcnt_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_LZCNT_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->lzcnt_dreg_8_sreg_8_func,
							post_info->lzcnt_dreg_8_sreg_8_func };

	/** PCMPEQQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQQ_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_8_smem_8,
							pre_info->pcmpeqq_dreg_8_smem_8_func,
							post_info->pcmpeqq_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQQ_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_8_sreg_8,
							pre_info->pcmpeqq_dreg_8_sreg_8_func,
							post_info->pcmpeqq_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_16_smem_16,
							pre_info->pcmpeqq_dreg_16_smem_16_func,
							post_info->pcmpeqq_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPEQQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_16_sreg_16,
							pre_info->pcmpeqq_dreg_16_sreg_16_func,
							post_info->pcmpeqq_dreg_16_sreg_16_func };

	/** PACKUSDW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKUSDW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packsdw_dreg_16_sreg_16,
							pre_info->packusdw_dreg_16_sreg_16_func,
							post_info->packusdw_dreg_16_sreg_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PACKUSDW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_packsdw_dreg_16_smem_16,
							pre_info->packusdw_dreg_16_smem_16_func,
							post_info->packusdw_dreg_16_smem_16_func };

	/** PCMPGTQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTQ_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_8_smem_8,
							pre_info->pcmpgtq_dreg_8_smem_8_func,
							post_info->pcmpgtq_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTQ_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_8_sreg_8,
							pre_info->pcmpgtq_dreg_8_sreg_8_func,
							post_info->pcmpgtq_dreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTQ_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_16_smem_16,
							pre_info->pcmpgtq_dreg_16_smem_16_func,
							post_info->pcmpgtq_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PCMPGTQ_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pcmpq_dreg_16_sreg_16,
							pre_info->pcmpgtq_dreg_16_sreg_16_func,
							post_info->pcmpgtq_dreg_16_sreg_16_func };

	/** PPMINSB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_smem_16,
							pre_info->pminsb_dreg_16_smem_16_func,
							post_info->pminsb_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_sreg_16,
							pre_info->pminsb_dreg_16_sreg_16_func,
							post_info->pminsb_dreg_16_sreg_16_func };

	/** PPMINSD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxd_dreg_16_smem_16,
							pre_info->pminsd_dreg_16_smem_16_func,
							post_info->pminsd_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINSD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxd_dreg_16_sreg_16,
							pre_info->pminsd_dreg_16_sreg_16_func,
							post_info->pminsd_dreg_16_sreg_16_func };

	/** PMINUW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_smem_16,
							pre_info->pminuw_dreg_16_smem_16_func,
							post_info->pminuw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_sreg_16,
							pre_info->pminuw_dreg_16_sreg_16_func,
							post_info->pminuw_dreg_16_sreg_16_func };

	/** PMINUD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxd_dreg_16_smem_16,
							pre_info->pminud_dreg_16_smem_16_func,
							post_info->pminud_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMINUD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxd_dreg_16_sreg_16,
							pre_info->pminud_dreg_16_sreg_16_func,
							post_info->pminud_dreg_16_sreg_16_func };

	/** PMAXSB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSB_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_smem_16,
							pre_info->pmaxsb_dreg_16_smem_16_func,
							post_info->pmaxsb_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSB_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxb_dreg_16_sreg_16,
							pre_info->pmaxsb_dreg_16_sreg_16_func,
							post_info->pmaxsb_dreg_16_sreg_16_func };

	/** PMAXSD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxd_dreg_16_smem_16,
							pre_info->pmaxsd_dreg_16_smem_16_func,
							post_info->pmaxsd_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXSD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxd_dreg_16_sreg_16,
							pre_info->pmaxsd_dreg_16_sreg_16_func,
							post_info->pmaxsd_dreg_16_sreg_16_func };

	/** PMAXUW **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUW_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_smem_16,
							pre_info->pmaxuw_dreg_16_smem_16_func,
							post_info->pmaxuw_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUW_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_sreg_16,
							pre_info->pmaxuw_dreg_16_sreg_16_func,
							post_info->pmaxuw_dreg_16_sreg_16_func };

	/** PMAXUD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_smem_16,
							pre_info->pmaxud_dreg_16_smem_16_func,
							post_info->pmaxud_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMAXUD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pminmaxw_dreg_16_sreg_16,
							pre_info->pmaxud_dreg_16_sreg_16_func,
							post_info->pmaxud_dreg_16_sreg_16_func };

	/** PMULLD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULLD_DREG_16_SMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pd_src_srcdst_dreg_16_smem_16,
							pre_info->pmulld_dreg_16_smem_16_func,
							post_info->pmulld_dreg_16_smem_16_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PMULLD_DREG_16_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_pd_src_srcdst_dreg_16_sreg_16,
							pre_info->pmulld_dreg_16_sreg_16_func,
							post_info->pmulld_dreg_16_sreg_16_func };

	/** PEXTRB **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXTRB_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pextb_dreg_4_sreg_16,
							pre_info->pextrb_dreg_4_func,
							post_info->pextrb_dreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXTRB_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pextb_dmem_1_sreg_16,
							pre_info->pextrb_dmem_4_func,
							post_info->pextrb_dmem_4_func };

	/** PEXTRD **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXTRD_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pextd_dreg_4_sreg_16,
							pre_info->pextrd_dreg_4_func,
							post_info->pextrd_dreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXTRD_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_pextd_dmem_4_sreg_16,
							pre_info->pextrd_dmem_4_func,
							post_info->pextrd_dmem_4_func };

	/** MOVQ2DQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVQ2DQ_DREG_16_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_sreg_8,
							pre_info->movq2dq_dreg_16_sreg_8_func,
							post_info->movq2dq_dreg_16_sreg_8_func };

	/** MOVQ2DQ **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_MOVDQ2Q_DREG_8_SREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_mov_dreg_8_sreg_8,
							pre_info->movdq2q_dreg_8_sreg_16_func,
							post_info->movdq2q_dreg_8_sreg_16_func };

	/** OP_TZCNT **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_TZCNT_DREG_2_SMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_smem_2,
							pre_info->tzcnt_dreg_2_smem_2_func,
							post_info->tzcnt_dreg_2_smem_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_TZCNT_DREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_smem_4,
							pre_info->tzcnt_dreg_4_smem_4_func,
							post_info->tzcnt_dreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_TZCNT_DREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_smem_8,
							pre_info->tzcnt_dreg_8_smem_8_func,
							post_info->tzcnt_dreg_8_smem_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_TZCNT_DREG_2_SREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_2_sreg_2,
							pre_info->tzcnt_dreg_2_sreg_2_func,
							post_info->tzcnt_dreg_2_sreg_2_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_TZCNT_DREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_4_sreg_4,
							pre_info->tzcnt_dreg_4_sreg_4_func,
							post_info->tzcnt_dreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_TZCNT_DREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_whole_mov_dreg_8_sreg_8,
							pre_info->tzcnt_dreg_8_sreg_8_func,
							post_info->tzcnt_dreg_8_sreg_8_func };

	/** OP_PEXT **/
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXT_DREG_4_SREG_4_SREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_4_sreg_4_sreg_4,
							pre_info->pext_dreg_4_sreg_4_sreg_4_func,
							post_info->pext_dreg_4_sreg_4_sreg_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXT_DREG_4_SREG_4_SMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_4_sreg_4_smem_4,
							pre_info->pext_dreg_4_sreg_4_smem_4_func,
							post_info->pext_dreg_4_sreg_4_smem_4_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXT_DREG_8_SREG_8_SREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_8_sreg_8_sreg_8,
							pre_info->pext_dreg_8_sreg_8_sreg_8_func,
							post_info->pext_dreg_8_sreg_8_sreg_8_func };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_PEXT_DREG_8_SREG_8_SMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_src_src_dst_whole_dreg_8_sreg_8_smem_8,
							pre_info->pext_dreg_8_sreg_8_smem_8_func,
							post_info->pext_dreg_8_sreg_8_smem_8_func };

	/** UNTAINT INSTRUCTION HANDLERS **/

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DREG_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dreg_1, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DREG_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dreg_2, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DREG_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dreg_4, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DREG_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dreg_8, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DREG_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dreg_16, NULL, NULL };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_1, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_2, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_4, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_8, NULL, NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_16] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_16, NULL, NULL };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_2_DREGS_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_2_dregs_1, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_2_DREGS_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_2_dregs_2, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_2_DREGS_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_2_dregs_4, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_2_DREGS_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_2_dregs_8, NULL,
					NULL };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_3_DREGS_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_3_dregs_1, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_3_DREGS_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_3_dregs_2, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_3_DREGS_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_3_dregs_4, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_3_DREGS_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_3_dregs_8, NULL,
					NULL };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_4_DREGS_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_4_dregs_1, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_4_DREGS_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_4_dregs_2, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_4_DREGS_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_4_dregs_4, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_FIRST_4_DREGS_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_execute_untaint_first_4_dregs_8, NULL,
					NULL };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_1] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_2nd_1, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_2] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_2nd_2, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_4] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_2nd_4, NULL,
					NULL };
	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DMEM_2ND_8] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE, tb_cc_byt_execute_untaint_dmem_2nd_8, NULL,
					NULL };

	instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[TB_INSTRUM_ID_UNTAINT_DREG_1ST_SUB_3RD_4TH] =
			(tb_cc_instr_hndlr_info_t ) {
					IB_OPT_BARE,
							tb_cc_byt_execute_untaint_dreg_untaint_1st_sub_3rd_4th,
							NULL, NULL };

	for (int i = 0; i < TB_INSTRUM_ID_END; i++) {

		instr_hndlrs->tb_instr_hndlr_info.instrum_cc_infos[i].tb_ctx =
				tb_ctx_opaque;
	}
}
