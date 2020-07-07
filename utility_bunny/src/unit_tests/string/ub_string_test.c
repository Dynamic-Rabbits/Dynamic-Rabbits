/**
 *  @file ub_string_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "../../string/ub_string.h"
#include "dr_api.h"
#include "drext.h"
#include <string.h>

static void test1() {

	char *string = ub_string_create_copy("Hello there!!");

	DR_ASSERT_MSG(strcmp(string, "Hello there!!") == 0,
			"ub_string_test - test1 - 0 - failed...");
	ub_string_destroy(string);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
}
