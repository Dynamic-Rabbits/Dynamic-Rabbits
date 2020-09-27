/**
 *  @file ub_alloc_test2.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

int count = 0;

void got_alloc_data(ub_ev_alloc_data_t *data) {

	if (data->size == 1111)
		count++;
}

static void event_exit() {

	DR_ASSERT_MSG(count == 0,
			"ub_alloc_test2 - 0 failed...");

	ub_ev_heap_alloc_destroy_ctx();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	ub_ev_heap_alloc_init_ctx(NULL, got_alloc_data);
	dr_register_exit_event(event_exit);
}
