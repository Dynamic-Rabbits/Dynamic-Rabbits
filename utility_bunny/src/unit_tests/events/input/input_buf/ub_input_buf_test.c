/**
 *  @file ub_input_buf_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

static void test1() {

	ub_input_buf_t *input_buf = ub_create_input_buf((void *) (uintptr_t) 8989, 80);

	DR_ASSERT_MSG(input_buf->buf == (void *) (uintptr_t) 8989,
			"ub_input_buf_test - test1 - 0 failed...");

	DR_ASSERT_MSG(input_buf->size == 80,
			"ub_input_buf_test - test1 - 0 failed...");

	ub_destroy_input_buf(input_buf);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {
	test1();
}

