/**
 *  @file sb_module_slicer_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

//bool sb_slicer_module_slice_out(void *module_slicer, app_pc proc_address);
#include "dr_api.h"
#include "drmgr.h"
#include "utility_bunny.h"
#include "../../slicers/sb_module_slicer.h"
#include <string.h>

bool seen_present = false;
bool seen_not_present = false;

void *mod_slicer;

static void mod_recorder(void *drcontext, const module_data_t *mod, bool loaded) {

	if (mod->names.module_name != NULL) {

		dr_fprintf(STDERR, "The mod name is %s\n", mod->names.module_name);

		if (strcmp(mod->names.module_name, "libsb_mod_slicer_test.so") == 0) {

			seen_present = true;

			if (mod->contiguous) {

				for (app_pc i = mod->start; i < mod->end; i++) {

					DR_ASSERT_MSG(
							sb_slicer_module_slice_out(mod_slicer, i) == true,
							"sb_module_slicer_test - test1 failed...");
				}
			} else {

				DR_ASSERT_MSG(
						sb_slicer_module_slice_out(mod_slicer, mod->entry_point) == true,
						"sb_module_slicer_test - test2 failed...");
			}
		} else {
			seen_not_present = true;
		}
	}
}

static void event_exit() {

	DR_ASSERT_MSG(seen_present == true,
			"ub_env_var_input_option_test - test1 - 2 failed...");

	DR_ASSERT_MSG(seen_not_present == true,
			"ub_env_var_input_option_test - test1 - 2 failed...");

	sb_module_slicer_destroy(mod_slicer);

	drmgr_exit();

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	drmgr_init();

	drmgr_priority_t slicer_pri = { sizeof(drmgr_priority_t), "slicer_pri",
			NULL, NULL, 1 };

	mod_slicer = sb_module_slicer_init(&slicer_pri);

	drmgr_priority_t checker_pri = { sizeof(drmgr_priority_t), "checker_pri",
			NULL, NULL, 2 };

	drmgr_register_module_load_event_ex(mod_recorder, &checker_pri);

	file_t module_file = ub_fr_open_file_with_check("./mod.txt", DR_FILE_READ);
	sb_module_slicer_register_file(mod_slicer, module_file);


	dr_register_exit_event(event_exit);
}

