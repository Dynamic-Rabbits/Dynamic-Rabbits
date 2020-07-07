/*
 * addr_constant_reg_trancator.h
 *
 *  Created on: 10 Dec 2018
 *      Author: john
 */

#ifndef APP_BB_TRANCATORS_ADDR_CONSTANT_REG_TRUNCATOR_H_
#define APP_BB_TRANCATORS_ADDR_CONSTANT_REG_TRUNCATOR_H_

#include "dr_api.h"
#include "ub_truncator.h"

void ub_addr_const_reg_trunc_init();

void ub_addr_const_reg_trunc_exit();

app_pc ub_addr_const_reg_truncate(void *drcontext, instrlist_t *bb);

#endif /* APP_BB_TRANCATORS_ADDR_CONSTANT_REG_TRUNCATOR_H_ */
