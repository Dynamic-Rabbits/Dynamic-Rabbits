/*
 * tb_raw_bitvect_policy.h
 *
 *  Created on: 18 Mar 2019
 *      Author: john
 */

#ifndef TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_BITVECT_POLICY_H_
#define TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_BITVECT_POLICY_H_

#include "../tb_raw_taint_policy.h"
#include "../cc_taint_policies/tb_cc_bitvector_policy.h"

DR_EXPORT void tb_raw_initialise_bitvector_taint_policy(tb_raw_taint_policy_t *taint_policy);

DR_EXPORT void tb_raw_destroy_bitvector_taint_policy();

#endif /* TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_BITVECT_POLICY_H_ */
