/**
 *  @file ub_file_reader_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../utility_bunny.h"
#include <string.h>

static void test1() {

	file_t file = ub_fr_open_file_with_check("./ub_file_reader_test1.txt",
	DR_FILE_READ);
	char buf[250];

	bool got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == true,
			"ub_file_reader_test - test1 - 0 -failed...");

	DR_ASSERT_MSG(strcmp(buf, "hello") == 0,
			"ub_file_reader_test - test1 - 1 -failed...");

	got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == true,
			"ub_file_reader_test - test1 - 2 -failed...");

	DR_ASSERT_MSG(strcmp(buf, "my") == 0,
			"ub_file_reader_test - test1 - 3 -failed...");

	got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == true,
			"ub_file_reader_test - test1 - 4 -failed...");

	DR_ASSERT_MSG(strcmp(buf, "name") == 0,
			"ub_file_reader_test - test1 - 5 -failed...");

	DR_ASSERT_MSG(strcmp(buf, "no") != 0,
			"ub_file_reader_test - test1 - 6 -failed...");

	got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == true,
			"ub_file_reader_test - test1 - 7 -failed...");

	DR_ASSERT_MSG(strcmp(buf, "is") == 0,
			"ub_file_reader_test - test1 - 8 -failed...");

	got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(strcmp(buf, "john") == 0,
			"ub_file_reader_test - test1 - 9 -failed...");

	got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == false,
			"ub_file_reader_test - test1 - 11 -failed...");

	dr_close_file(file);
}

static void test2() {

	file_t file = ub_fr_open_file_with_check("./ub_file_reader_test2.txt",
	DR_FILE_READ);
	char buf[250];

	bool got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == true,
			"ub_file_reader_test - test2 - 0 -failed...");

	DR_ASSERT_MSG(strcmp(buf, "hello there!") == 0,
			"ub_file_reader_test - test2 - 1 -failed...");

	got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == false,
			"ub_file_reader_test - test2 - 2 -failed...");

	dr_close_file(file);
}

static void test3() {

	file_t file = ub_fr_open_file_with_check("./ub_file_reader_test3.txt",
	DR_FILE_READ);
	char buf[250];

	bool got_read = ub_fr_get_line(file, buf, 250);

	DR_ASSERT_MSG(got_read == false,
			"ub_file_reader_test - test3 - 0 - failed...");

	dr_close_file(file);

}

static void test4() {

	DR_ASSERT_MSG(
			 strcmp(ub_fr_get_basename("./ub_file_reader_test3.txt"),
									"ub_file_reader_test3.txt") == 0,
			"ub_file_reader_test - test4 - 0 - failed...");

	dr_fprintf(STDERR, "The basename is %s \n", ub_fr_get_basename("./hello/there/ub_file_reader_test3.txt"));


	DR_ASSERT_MSG(
			strcmp(ub_fr_get_basename("./hello/there/ub_file_reader_test3.txt"),
					"ub_file_reader_test3.txt") == 0,
					"ub_file_reader_test - test4 - 1 - failed...");

	DR_ASSERT_MSG(
			strcmp(ub_fr_get_basename("ub_file_reader_test3.txt"),
					"ub_file_reader_test3.txt") == 0,
					"ub_file_reader_test - test4 - 2 - failed...");

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
}

