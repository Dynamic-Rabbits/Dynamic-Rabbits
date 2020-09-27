/*
 * tb_raw_dummy_policy.h
 *
 *  Created on: 19 Mar 2019
 *      Author: john
 */

#ifndef TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_DUMMY_POLICY_H_
#define TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_DUMMY_POLICY_H_

#include "../tb_raw_taint_policy.h"
#include "../cc_taint_policies/tb_cc_dummy_policy.h"

void tb_raw_initialise_dummy_taint_policy(tb_raw_taint_policy_t *taint_policy);

#endif /* TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_DUMMY_POLICY_H_ */
