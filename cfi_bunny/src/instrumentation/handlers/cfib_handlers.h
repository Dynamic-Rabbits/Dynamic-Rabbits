#ifndef CFI_HANDLERS_H_
#define CFI_HANDLERS_H_

#include "dr_defines.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"

void cfib_instrument_call_reg_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data);

void cfib_instrument_call_mem_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data);

void cfib_instrument_jmp_reg_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data);

void cfib_instrument_ret_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data);

void cfib_instrument_ret_immed_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data);

#endif /* CFI_HANDLERS_H_ */
