/*
 * ub_symbol_access.h
 *
 *  Created on: 22 May 2018
 *      Author: john
 */

#ifndef SYMBOL_ACCESS_UB_SYMBOL_ACCESS_H_
#define SYMBOL_ACCESS_UB_SYMBOL_ACCESS_H_

#include "dr_api.h"
#include "drmgr.h"
#include "drsyms.h"

void ub_sa_init();
void ub_sa_print_symb_info(app_pc pc);
void ub_sa_exit();

#endif /* SYMBOL_ACCESS_UB_SYMBOL_ACCESS_H_ */
