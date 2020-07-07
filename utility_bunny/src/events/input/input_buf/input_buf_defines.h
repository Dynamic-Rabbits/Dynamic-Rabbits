/**
 *  @file input_buf_defines.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_INPUT_BUF_INPUT_BUF_DEFINES_H_
#define EVENTS_INPUT_INPUT_BUF_INPUT_BUF_DEFINES_H_

#include "dr_api.h"
#include "drmgr.h"

#define UB_INPUT_PRIORITY 0

/**
 *  @struct ub_input_buf_t Describes a buffer containing read input.
 *
 *  @param ub_input_buf_t::buf The buf containing input data.
 *  @param ub_input_buf_t::size The size of the input data.
 */
typedef struct {
	void *buf;
	int64_t size;
} ub_input_buf_t;

#endif /* EVENTS_INPUT_INPUT_BUF_INPUT_BUF_DEFINES_H_ */
