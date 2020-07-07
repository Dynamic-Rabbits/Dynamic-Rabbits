/**
 *  @file instrumentation_bunny_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "instrumentation_bunny.h"
#include <string.h>

void *instrum_tool;
static void event_exit() {

	ib_unregister_instrum_tool(instrum_tool);
	ib_exit();
	drmgr_exit();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();

	ib_init(NULL);

	instrum_tool = ib_register_instrum_tool();
	dr_register_exit_event(event_exit);
}
