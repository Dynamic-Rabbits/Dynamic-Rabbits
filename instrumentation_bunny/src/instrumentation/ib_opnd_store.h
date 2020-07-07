/**
 *  @file ib_opnd_store.h
 *  @brief Responsible for storing operand information in a slot found in
 *  instrum_data_t
 *  @author John F.X. Galea
 */

#ifndef INSTRUMENT_OPND_STORE_H_
#define INSTRUMENT_OPND_STORE_H_

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"
#include "../ib_defines.h"
#include "../opcode_hook_manager/ib_hook_summary.h"

#include "ib_thread_data_loader.h"

/**
 *  Inserts code responsible for storing information on the operands of the instruction.
 *
 *  @param instr The instruction to store the opcode of.
 *  @param where The instruction where instrumentation will be placed before it.
 *  @param opcode The opcode of the instruction
 */
void ib_insert_operands(void *drcontext, instrlist_t *ilist, instr_t *instr,
		instr_t *where, int opcode, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary);

#endif
