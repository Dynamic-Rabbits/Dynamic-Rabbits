/**
 *	@file ib_instrumenter.h
 *	@brief Provides functionality for instrumenting instructions. Operand information
 *	are stored and accessible during runtime.
 *  @author John F.X. Galea
 */

#ifndef IB_INSTRUMENTER_H_
#define IB_INSTRUMENTER_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"

#include "../ib_data.h"
#include "../ib_defines.h"
#include "ib_slot.h"
#include "../code_cache/ib_code_cache.h"
#include "../opcode_hook_manager/ib_opcode_hook_manager.h"
#include <stdint.h>

/**
 * Initialises the instrument component.
 */
void ib_instrumenter_init();

/**
 * Destroy the instrument component.
 */
void ib_instrumenter_exit();

void ib_dispatch_instr(void *drcontext, instrlist_t *ilist, instr_t *instr,
		instr_t *where, ib_instrum_analysis_data_t *analysis_data);
#endif
