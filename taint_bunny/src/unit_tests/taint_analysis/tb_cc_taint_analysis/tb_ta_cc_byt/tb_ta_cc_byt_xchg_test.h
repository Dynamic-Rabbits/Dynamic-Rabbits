/*
 * tb_ta_cc_byt_xchg_test.h
 *
 *  Created on: 26 Jan 2019
 *      Author: john
 */

#ifndef UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_XCHG_TEST_H_
#define UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_XCHG_TEST_H_

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"
#include "../../../../taint_bunny.h"

void tb_cc_byt_handle_xchg_reg_4_reg_4_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_xchg_mem_4_reg_4_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_xchg_reg_4_mem_4_test(void *tb_ctx_opaque);

void tb_cc_handle_bswap_dsreg_4_test(void *tb_ctx_opaque);

void tb_cc_handle_bswap_dsmem_4_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_xadd_reg_4_reg_4_test(void *tb_ctx_opaque);

void tb_cc_byt_handle_xadd_mem_4_reg_4_test(void *tb_ctx_opaque);

#endif /* UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_XCHG_TEST_H_ */
