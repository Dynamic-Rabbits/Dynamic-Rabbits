/*
 * tb_cc_bitvect_tree_policy.h
 *
 *  Created on: 19 Aug 2019
 *      Author: john
 */

#ifndef TAINT_POLICIES_CC_TAINT_POLICIES_TB_CC_BITVECT_TREE_POLICY_H_
#define TAINT_POLICIES_CC_TAINT_POLICIES_TB_CC_BITVECT_TREE_POLICY_H_

#include "../tb_cc_taint_policy.h"

DR_EXPORT void tb_cc_initialise_bitvector_tree_taint_policy(
		tb_cc_taint_policy_t *taint_policy);

DR_EXPORT void tb_cc_destroy_bitvector_tree_taint_policy();

DR_EXPORT void *tb_cc_bitvector_tree_get_label(int index);

DR_EXPORT void *tb_cc_tree_get_inc_default_label();

DR_EXPORT void *tb_raw_tree_get_inc_default_label();

#endif /* TAINT_POLICIES_CC_TAINT_POLICIES_TB_CC_BITVECT_TREE_POLICY_H_ */
