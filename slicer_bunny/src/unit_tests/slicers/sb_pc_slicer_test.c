/**
 *  @file sb_module_slicer_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "utility_bunny.h"
#include "../../slicers/sb_pc_slicer.h"

static void test1() {

	void *pc_slicer = sb_pc_slicer_init();

	file_t pc_file = ub_fr_open_file_with_check("./pc_addr.txt", DR_FILE_READ);

	sb_pc_slicer_register_file(pc_slicer, pc_file);

	DR_ASSERT_MSG(sb_pc_slicer_slice_out(pc_slicer, (void *) 0x41414141) == true,
			"ub_pc_slicer_test - test1 - 0 - failed...");

	DR_ASSERT_MSG(sb_pc_slicer_slice_out(pc_slicer, (void *) 0x72892100) == true,
			"ub_register_test - test1 - 0 - failed...");


	DR_ASSERT_MSG(sb_pc_slicer_slice_out(pc_slicer, (void *) 0x7982212) == false,
			"ub_register_test - test1 - 0 - failed...");

	sb_pc_slicer_destroy(pc_slicer);
}

static void test2() {

	void *pc_slicer = sb_pc_slicer_init();

	file_t pc_file = ub_fr_open_file_with_check("./pc_addr.txt", DR_FILE_READ);
	sb_pc_slicer_register_file(pc_slicer, pc_file);

	file_t pc_file2 = ub_fr_open_file_with_check("./pc_addr2.txt", DR_FILE_READ);
	sb_pc_slicer_register_file(pc_slicer, pc_file2);

	DR_ASSERT_MSG(sb_pc_slicer_slice_out(pc_slicer, (void *) 0x41414141) == true,
			"ub_pc_slicer_test - test1 - 0 - failed...");

	DR_ASSERT_MSG(sb_pc_slicer_slice_out(pc_slicer, (void *) 0x72892100) == true,
			"ub_register_test - test1 - 0 - failed...");

	DR_ASSERT_MSG(sb_pc_slicer_slice_out(pc_slicer, (void *) 0x17171717) == true,
			"ub_register_test - test1 - 0 - failed...");

	DR_ASSERT_MSG(sb_pc_slicer_slice_out(pc_slicer, (void *) 0x7982212) == false,
			"ub_register_test - test1 - 0 - failed...");

	sb_pc_slicer_destroy(pc_slicer);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
}
