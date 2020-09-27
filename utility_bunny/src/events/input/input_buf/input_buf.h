/**
 *  @file input_buf.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_INPUT_BUF_H_
#define EVENTS_INPUT_INPUT_BUF_H_

#include "input_buf_defines.h"

/**
 *  Creates an input buf, which described a buf containing read data.
 *
 *  @param buf The buffer containing read data.
 *  @param size The size of the read content.
 */
ub_input_buf_t *ub_create_input_buf(void *buf, int64_t size);

/**
 *  Destroys an input buf.
 *
 *  @param input_buf The input buf to destroy.
 */
void ub_destroy_input_buf(void *input_buf);

#endif /* EVENTS_INPUT_INPUT_BUF_H_ */
