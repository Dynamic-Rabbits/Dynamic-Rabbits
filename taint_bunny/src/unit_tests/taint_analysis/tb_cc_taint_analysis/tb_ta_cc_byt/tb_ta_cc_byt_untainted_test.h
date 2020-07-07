/*
 * tb_ta_cc_byt_unsupport.h
 *
 *  Created on: 17 Jan 2019
 *      Author: john
 */

#ifndef UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_UNSUPPORT_H_
#define UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_UNSUPPORT_H_

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"
#include "../../../../taint_bunny.h"

void tb_test_untaint_mem(void *tb_ctx_opaque);

void tb_test_untaint_reg(void *tb_ctx_opaque);

#endif /* UNIT_TESTS_TAINT_ANALYSIS_TB_CC_TAINT_ANALYSIS_TB_TA_CC_BYT_TB_TA_CC_BYT_UNSUPPORT_H_ */
