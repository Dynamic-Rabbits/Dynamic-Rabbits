/**
 *  @file ub_dealloc_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

int alloc_count = 0;
int dealloc_count = 0;
int realloc_count = 0;

void *allocated;

void got_alloc_data(ub_ev_alloc_data_t *data) {

	if (data->size == 1111) {

		DR_ASSERT_MSG(data->addr != NULL,
				"ub_dealloc_test1 - 0 failed...");

		allocated = data->addr;
		alloc_count++;
	}
}

void got_dealloc_data(ub_ev_dealloc_data_t *data) {

	if (data->addr == allocated)
		dealloc_count++;

	allocated = NULL;
}

void got_realloc_data(ub_ev_realloc_data_t *data) {

	if (data->addr == allocated || data->passed_addr == allocated)
		realloc_count++;

	allocated = NULL;
}

static void event_exit() {

	DR_ASSERT_MSG(alloc_count == 8, "ub_delloc_test1 - 1 failed...");

	DR_ASSERT_MSG(dealloc_count == 8, "ub_delloc_test1 - 2 failed...");

	DR_ASSERT_MSG(realloc_count == 0, "ub_delloc_test1 - 3 failed...");

	ub_ev_heap_alloc_destroy_ctx();
	ub_ev_heap_dealloc_destroy_ctx();
	ub_ev_heap_realloc_destroy_ctx();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	ub_ev_heap_alloc_init_ctx(NULL, got_alloc_data);
	ub_ev_heap_dealloc_init_ctx(NULL, got_dealloc_data);
	ub_ev_heap_realloc_init_ctx(NULL, got_realloc_data);

	dr_register_exit_event(event_exit);
}
