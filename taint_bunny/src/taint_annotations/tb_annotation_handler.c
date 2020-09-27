/*
 * tb_annotation_handler.c
 *
 *      Author: john
 */

#include "tb_annotation_handler.h"
#include "dr_api.h"
#include <stdint.h>

static tb_context_t *tb_ctx = NULL;

static void tb_handle_taint_annotation(void *start, size_t size) {

	DR_ASSERT(tb_ctx);
	if (tb_ctx->get_taint_label) {
		for (size_t i = 0; i < size; i++) {
			tb_taint_mem(tb_ctx, (uintptr_t) start + i,
					tb_ctx->get_taint_label());
		}
	}
}

static void tb_handle_untaint_annotation(void *start, size_t size) {

	DR_ASSERT(tb_ctx);

	for (size_t i = 0; i < size; i++) {
		tb_untaint_mem(tb_ctx, (uintptr_t) start + i);
	}
}

void tb_init_annotation_handler(tb_context_t *in_tb_ctx) {

	DR_ASSERT(in_tb_ctx != NULL);
	tb_ctx = in_tb_ctx;

	/* Register taint annotation */
	dr_annotation_register_call("tr_annotate_taint", tb_handle_taint_annotation,
	false, 2, DR_ANNOTATION_CALL_TYPE_FASTCALL);

	/* Register untaint annotation */
	dr_annotation_register_call("tr_annotate_untaint", tb_handle_untaint_annotation,
	false, 2, DR_ANNOTATION_CALL_TYPE_FASTCALL);
}
