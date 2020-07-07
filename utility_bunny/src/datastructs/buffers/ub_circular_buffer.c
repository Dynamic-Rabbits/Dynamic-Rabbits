/*
 * ub_circular_buffer.c
 *
 *      Author: john
 */

#include "ub_circular_buffer.h"
#include "string.h"

#define ALIGN_FORWARD(x, alignment) \
    ((((ptr_uint_t)x) + ((alignment)-1)) & (~((alignment)-1)))

#define ALIGN_BACKWARD(x, alignment) (((ptr_uint_t)x) & (~((ptr_uint_t)(alignment)-1)))

void ub_create_circular_buffer(ub_circular_buf_t *circular_buf) {

	void *buf_base = dr_raw_mem_alloc(
	UB_CIRCULAR_BUF_SIZE * 2 /*Allocated twice for alignment*/,
	DR_MEMPROT_READ | DR_MEMPROT_WRITE, NULL);

	DR_ASSERT(buf_base != NULL);

	circular_buf->base = buf_base;
	circular_buf->buffer = (void *) ALIGN_FORWARD(buf_base,
			UB_CIRCULAR_BUF_SIZE);
}

void ub_destroy_circular_buffer(ub_circular_buf_t *circular_buf) {

	dr_raw_mem_free(circular_buf->base, UB_CIRCULAR_BUF_SIZE * 2);

	/* Destroy dangling pointers */
	circular_buf->base = NULL;
	circular_buf->buffer = NULL;
}

app_pc * ub_get_start_of_circular_buffer(app_pc *buf_ptr) {

	return (app_pc *) ALIGN_BACKWARD(buf_ptr, UB_CIRCULAR_BUF_SIZE);
}

void ub_get_clear_circular_buffer(ub_circular_buf_t *circular_buf) {

	memset(circular_buf->buffer, 0, UB_CIRCULAR_BUF_SIZE);
}

void ub_insert_increment_circular_buffer(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t buf_ptr_opnd, ushort stride) {

	DR_ASSERT(opnd_get_size(buf_ptr_opnd) == OPSZ_2);

	instr_t *instr = INSTR_CREATE_add(drcontext, buf_ptr_opnd,
			OPND_CREATE_INT16(stride));
	instrlist_meta_preinsert(ilist, where, instr);
}
