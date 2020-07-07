/*
 * pb_spill.h
 *
 *  Created on: 9 Apr 2019
 *      Author: john
 */

#ifndef INSTRUMENTATION_PB_SPILL_H_
#define INSTRUMENTATION_PB_SPILL_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

#define pb_reg1 DR_REG_XDX
#define pb_reg2 DR_REG_XBX
#define pb_reg3 DR_REG_XMM1
#define pb_reg4_xcx DR_REG_XCX

void pb_live_regs_init();
void pb_live_regs_destroy();

void pb_spill_three_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void **spilling_data_opaque);

void pb_restore_three_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void *spilling_data_opaque);

void pb_spill_four_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void **spilling_data_opaque);

void pb_restore_four_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void *spilling_data_opaque);




#endif /* INSTRUMENTATION_PB_SPILL_H_ */
