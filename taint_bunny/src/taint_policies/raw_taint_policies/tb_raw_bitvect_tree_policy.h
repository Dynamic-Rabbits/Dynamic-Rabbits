/*
 * tb_raw_bitvect_tree_policy.h
 *
 *  Created on: 10 Apr 2019
 *      Author: john
 */

#ifndef TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_BITVECT_TREE_POLICY_H_
#define TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_BITVECT_TREE_POLICY_H_

#include "../tb_raw_taint_policy.h"

DR_EXPORT void tb_raw_initialise_tree_taint_policy(tb_raw_taint_policy_t *taint_policy);

DR_EXPORT void tb_raw_destroy_tree_taint_policy();

DR_EXPORT void *tb_raw_tree_get_label(int index);

#endif /* TAINT_POLICIES_RAW_TAINT_POLICIES_TB_RAW_BITVECT_TREE_POLICY_H_ */
