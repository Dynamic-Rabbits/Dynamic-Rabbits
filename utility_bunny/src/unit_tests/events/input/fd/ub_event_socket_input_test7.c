/**
 *  @file ub_event_socket_input_test7.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "../../../../utility_bunny.h"
#include <string.h>

void *socket_input_ctx;
int count = 0;
bool saw_first = false;
bool saw_second = false;

static void got_read(ub_fd_input_data_t *input_data) {

	count++;
}

static void event_exit() {

	DR_ASSERT_MSG(count == 0, "ub_socket_input_test1 - 15 failed...");
	ub_ev_fd_input_destroy_ctx(socket_input_ctx);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	socket_input_ctx = ub_ev_fd_input_init_ctx(got_read, true,
			UB_EV_FD_INPUT_OPT_SOURCE_INFO | UB_EV_FD_INPUT_OPT_OFFSET
					| UB_EV_FD_INPUT_OPT_LOCAL_SOCKET, id);

	dr_register_exit_event(event_exit);
}


