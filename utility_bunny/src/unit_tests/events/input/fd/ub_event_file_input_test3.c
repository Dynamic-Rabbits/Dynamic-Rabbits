/**
 *  @file ub_event_file_input_test3.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

void *socket_input_ctx;
int count = 0;

static void got_read(ub_fd_input_data_t *input_data) {

	count++;
}

static void event_exit() {

	DR_ASSERT_MSG(count == 0,
			"ub_event_file_input_test3 - 0 failed...");
	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_read, false,
	UB_EV_FD_INPUT_OPT_FILE, id);

	ub_ev_fd_input_register_file(socket_input_ctx, "NO_NO_NO_NO_NO.txt");

	dr_register_exit_event(event_exit);
}

