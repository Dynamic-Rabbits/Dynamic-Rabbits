/*
 * tb_cc_bitvector_policy.h
 *
 *  Created on: 17 Mar 2019
 *      Author: john
 */

#ifndef TAINT_POLICIES_CC_TAINT_POLICIES_TB_CC_BITVECTOR_POLICY_H_
#define TAINT_POLICIES_CC_TAINT_POLICIES_TB_CC_BITVECTOR_POLICY_H_

#include "../tb_cc_taint_policy.h"

//CHANGE THIS VALUE IF YOU WANT A BIGGER VECT! Size is in bytes!
#define TB_BITVECT_SIZE 32

typedef struct {

    byte bitvect[TB_BITVECT_SIZE];
    int count;
} tb_bitvector_tl_t;

DR_EXPORT void tb_cc_initialise_bitvector_taint_policy(
        tb_cc_taint_policy_t *taint_policy);

DR_EXPORT void tb_cc_destroy_bitvector_taint_policy();


#endif /* TAINT_POLICIES_CC_TAINT_POLICIES_TB_CC_BITVECTOR_POLICY_H_ */
