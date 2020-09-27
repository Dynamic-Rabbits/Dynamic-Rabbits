/*
 * tb_ta_cc_byt_src_dst_test.h
 *
 *  Created on: 17 Jan 2019
 *      Author: john
 */

#ifndef UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_DST_TEST_H_
#define UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_DST_TEST_H_

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"
#include "../../../../taint_bunny.h"

void tb_test_src_dst_dmem_smem(void *tb_ctx_opaque);

void tb_test_src_dst_dmem_sreg(void *tb_ctx_opaque);

void tb_test_src_dst_dreg_sreg(void *tb_ctx_opaque);

void tb_test_src_dst_dreg_smem(void *tb_ctx_opaque);

void tb_test_src_dst_reg_extension(void *tb_ctx_opaque);

void tb_test_src_dst_mem_extension(void *tb_ctx_opaque);

void tb_test_src_dst_whole_dreg_sreg(void *tb_ctx_opaque);

void tb_test_src_dst_whole_dreg_smem(void *tb_ctx_opaque);

void tb_test_src_dst_whole_dmem_sreg(void *tb_ctx_opaque);

void tb_test_src_dst_high_src_dst_mem(void *tb_ctx_opaque);

void tb_test_src_dst_high_src_dst_reg(void *tb_ctx_opaque);

#endif /* UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_DST_TEST_H_ */
