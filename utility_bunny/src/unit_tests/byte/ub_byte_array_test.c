/**
 *  @file ub_byte_array_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "../../utility_bunny.h"

static void test1() {

	byte byte = 5;
	uint32_t value = 5;

	DR_ASSERT_MSG(ub_get_uint32_from_byte_array(&byte, 1) == value,
			"ub_byte_array_test - test1 failed...");
}

static void test2() {

	byte byte = 0;
	uint32_t value = 0;

	DR_ASSERT_MSG(ub_get_uint32_from_byte_array(&byte, 1) == value,
			"ub_byte_array_test - test2 failed...");
}

static void test3() {

	byte byte = 8;
	uint32_t value = 0;

	DR_ASSERT_MSG(ub_get_uint32_from_byte_array(&byte, 1) != value,
			"ub_byte_array_test - test3 failed...");
}

static void test4() {

	byte byte[2];
	byte[0] = 0;
	byte[1] = 0;
	byte[2] = 0;
	byte[3] = 5;

	uint32_t value = 83886080;

	uint32_t res = ub_get_uint32_from_byte_array(byte, 4);
	DR_ASSERT_MSG(res == value,
			"ub_byte_array_test - test4 failed...");
}

static void test5(){

	unsigned int main_value = 0;
	byte value = 255;

	unsigned int new_value = ub_modify_byte_of_value(main_value, sizeof(unsigned int), value, 0);

	DR_ASSERT_MSG(new_value == 255,
			"ub_byte_array_test - test5 failed...");
}

static void test6(){

	unsigned int main_value = 16711935;
	byte value = 255;

	unsigned int new_value = ub_modify_byte_of_value(main_value, sizeof(unsigned int), value, 1);

	DR_ASSERT_MSG(new_value == 16777215,
			"ub_byte_array_test - test6 failed...");
}

static void test7(){

	unsigned int main_value = 16711935;
	byte value = 0;

	size_t size =  sizeof(unsigned int);

	for (int i = 0; i < size; i++){

		main_value = (unsigned int) ub_modify_byte_of_value(main_value, size, value, i);
	}

	DR_ASSERT_MSG(main_value == 0,
			"ub_byte_array_test - test7 failed...");
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
}
