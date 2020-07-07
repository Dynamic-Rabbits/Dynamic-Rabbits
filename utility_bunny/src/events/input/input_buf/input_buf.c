/**
 *  @file input_buf.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "input_buf.h"
#include "dr_api.h"
#include "drmgr.h"

ub_input_buf_t *ub_create_input_buf(void *buf, int64_t size){

	ub_input_buf_t *ub_input_buf = (ub_input_buf_t *) dr_global_alloc(sizeof(ub_input_buf_t));
	ub_input_buf->buf = buf;
	ub_input_buf->size = size;

	return ub_input_buf;
}

void ub_destroy_input_buf(void *input_buf_opaque){

	dr_global_free(input_buf_opaque, sizeof(ub_input_buf_t));
}
