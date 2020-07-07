/*
 * tb_ta_cc_byt_src_srcdst_dst_test.h
 *
 *  Created on: 26 Jan 2019
 *      Author: john
 */

#ifndef UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_DST_TEST_H_
#define UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_DST_TEST_H_

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "drext.h"
#include "dr_api.h"
#include "../../../../taint_bunny.h"

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4_test(void *tb_ctx_opaque);

#endif /* UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_SRC_SRCDST_DST_TEST_H_ */
