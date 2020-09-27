/*
 * tb_tls_access.h
 *
 *  Created on: 17 Aug 2018
 *      Author: john
 */

#ifndef TLS_ACCESS_IB_TLS_ACCESS_H_
#define TLS_ACCESS_IB_TLS_ACCESS_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

#define IB_RAW_SLOT_THRD_DATA 0
/* Slot used to return for code cache */
#define IB_RAW_SLOT_RET_DATA 1
/* Since operand and pc slots are used heavily, we store them in their own tls slot */
#define IB_RAW_SLOT_PC_DATA 2
/* While we have 12 slots, we only store the first 3 of src and first 3 of dst in addressable
 * tls.
 */
#define IB_RAW_SLOT_SRC_OPND_DATA_1 3
#define IB_RAW_SLOT_SRC_OPND_DATA_2 4
#define IB_RAW_SLOT_SRC_OPND_DATA_3 5
#define IB_RAW_SLOT_DST_OPND_DATA_1 6
#define IB_RAW_SLOT_DST_OPND_DATA_2 7
#define IB_RAW_SLOT_DST_OPND_DATA_3 8

opnd_t ib_tls_get_raw_slot_opnd(int slot_idx);

uintptr_t ib_tls_get_opnd_data(int index);

void *ib_get_thread_data(void *drcontext);

app_pc ib_tls_get_pc_data();

void ib_tls_set_thread_data(void *thread_data);

void tb_tls_set_return_data(void *return_data);

#endif /* TLS_ACCESS_IB_TLS_ACCESS_H_ */
