/**
 *  @file ub_list_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../utility_bunny.h"

static void test1() {

	DR_ASSERT(UB_CIRCULAR_BUF_SIZE % sizeof(void *) == 0);

	ub_circular_buf_t circular_buf;
	ub_create_circular_buffer(&circular_buf);
	ub_get_clear_circular_buffer(&circular_buf);

	app_pc *start = ub_get_start_of_circular_buffer(circular_buf.buffer);
	DR_ASSERT(start == circular_buf.buffer);

	start = ub_get_start_of_circular_buffer(circular_buf.buffer + 6);
	DR_ASSERT(start == circular_buf.buffer);

	size_t size = UB_CIRCULAR_BUF_SIZE / sizeof(void *);
	for (int i = 0; i < size; i++) {
		DR_ASSERT(start[i] == 0);
	}

	ub_destroy_circular_buffer(&circular_buf);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
}

