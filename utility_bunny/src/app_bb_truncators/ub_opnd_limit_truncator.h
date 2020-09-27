/*
 * ub_opnd_limit_trancator.h
 *
 *  Created on: 7 Mar 2019
 *      Author: john
 */

#ifndef APP_BB_TRUNCATORS_UB_OPND_LIMIT_TRUNCATOR_H_
#define APP_BB_TRUNCATORS_UB_OPND_LIMIT_TRUNCATOR_H_

#include "dr_api.h"
#include "ub_truncator.h"

void ub_opnd_trunc_init();

void ub_opnd_trunc_exit();

void ub_opnd_truncate(void *drcontext, instrlist_t *bb);

#endif /* APP_BB_TRUNCATORS_UB_OPND_LIMIT_TRUNCATOR_H_ */
