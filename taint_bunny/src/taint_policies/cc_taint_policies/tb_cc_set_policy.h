/*
 * tb_set_policy.h
 *
 *  Created on: 24 Jun 2018
 *      Author: john
 */

#ifndef TB_CC_SET_POLICY_H_
#define TB_CC_SET_POLICY_H_

#include "../tb_cc_taint_policy.h"

typedef struct {

	void *set;
	int count;
} tb_set_tl_t;

DR_EXPORT void tb_cc_initialise_set_taint_policy(tb_cc_taint_policy_t *taint_policy);

#endif /* TB_SET_POLICY_H_ */
