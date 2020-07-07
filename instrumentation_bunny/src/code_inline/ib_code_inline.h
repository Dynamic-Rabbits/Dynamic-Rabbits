/*
 * ib_code_inline.h
 *
 *  Created on: 22 Jul 2018
 *      Author: john
 */

#ifndef CODE_INLINE_IB_CODE_INLINE_H_
#define CODE_INLINE_IB_CODE_INLINE_H_

#include "dr_api.h"
#include "dr_defines.h"
#include <stdint.h>
#include "../ib_defines.h"

void *ib_code_inline_init(ib_insert_hndle_data_t *insert_hndle_data);

void ib_code_inline_exit(void *code_inline_opaque);

void ib_insert_code_inline(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *code_inline_opaque);

#endif /* CODE_INLINE_IB_CODE_INLINE_H_ */
