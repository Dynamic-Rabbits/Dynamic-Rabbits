/*
 * tb_ta_cc_byt_punpck.h
 *
 *  Created on: 25 Jan 2019
 *      Author: john
 */

#ifndef UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_PUNPCK_H_
#define UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_PUNPCK_H_

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"
#include "../../../../taint_bunny.h"

void tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16_test(void *tb_ctx_opaque);

#endif /* UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_PUNPCK_H_ */
