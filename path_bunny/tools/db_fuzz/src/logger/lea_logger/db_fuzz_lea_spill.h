/*
 * lea_spill.h
 *
 *  Created on: 12 Apr 2019
 *      Author: john
 */

#ifndef LOGGER_LEA_LOGGER_DB_FUZZ_LEA_SPILL_H_
#define LOGGER_LEA_LOGGER_DB_FUZZ_LEA_SPILL_H_


#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

#define db_fuzz_lea_reg1 DR_REG_XDX
#define db_fuzz_lea_reg2 DR_REG_XBX
#define db_fuzz_lea_reg3 DR_REG_XMM1

void db_fuzz_lea_live_regs_init();
void db_fuzz_lea_live_regs_destroy();

void db_fuzz_lea_spill_three_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void **spilling_data_opaque);

void db_fuzz_lea_restore_three_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void *spilling_data_opaque);

#endif /* LOGGER_LEA_LOGGER_DB_FUZZ_LEA_SPILL_H_ */
