/*
 * ub_circular_buffer.h
 *
 *  Created on: 11 Sep 2019
 *      Author: john
 */

#ifndef DATASTRUCTS_BUFFERS_UB_CIRCULAR_BUFFER_H_
#define DATASTRUCTS_BUFFERS_UB_CIRCULAR_BUFFER_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"

/**
 * Note: I could have modified and used drx (provided by DynamoRIO), but I need
 * to separate buffers from thread location slots, which I cannot
 * do with drx.
 *
 * For example, the TB's jitter swaps circular buffers to relieve app threads
 * from sample processing.
 *
 * It is quite bare-bones. It does not support the loading or storing to the buffer.
 */

#define UB_CIRCULAR_BUF_SIZE (1 << 16)

typedef struct {

	app_pc *base;
	app_pc *buffer;
} ub_circular_buf_t;

void ub_create_circular_buffer(ub_circular_buf_t *circular_buf);

void ub_destroy_circular_buffer(ub_circular_buf_t *circular_buffer);

void ub_insert_increment_circular_buffer(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t buf_ptr_opnd, ushort stride);

app_pc * ub_get_start_of_circular_buffer(app_pc *buf_ptr);

void ub_get_clear_circular_buffer(ub_circular_buf_t *circular_buf);

#endif /* DATASTRUCTS_BUFFERS_UB_CIRCULAR_BUFFER_H_ */
