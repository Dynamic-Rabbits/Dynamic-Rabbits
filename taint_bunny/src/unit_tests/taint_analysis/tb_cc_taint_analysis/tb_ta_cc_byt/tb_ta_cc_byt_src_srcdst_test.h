/*
 * tb_ta_cc_byt_src_srcdst_test.h
 *
 *  Created on: 18 Jan 2019
 *      Author: john
 */

#ifndef UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_TEST_H_
#define UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_TEST_H_

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"
#include "../../../../taint_bunny.h"

void tb_test_src_srcdst_whole_dreg_sreg_sreg(void *tb_ctx_opaque);

void tb_test_src_srcdst_whole_dreg_smem_sreg(void *tb_ctx_opaque);

void tb_test_src_srcdst_whole_dmem_sreg_smem(void *tb_ctx_opaque);

void tb_test_src_srcdst_dreg_sreg_sreg(void *tb_ctx_opaque);

void tb_test_src_srcdst_dreg_smem_sreg(void *tb_ctx_opaque);

void tb_test_src_srcdst_dmem_sreg_smem(void *tb_ctx_opaque);

#endif /* UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_TEST_H_ */
