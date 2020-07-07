/*
 * instrumentation_bunny.c
 *
 *      Author: john
 */

#include "slicer_bunny.h"

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>

#include "utility_bunny.h"

#include "slicers/sb_module_slicer.h"
#include "slicers/sb_pc_slicer.h"

#include <stddef.h>

typedef struct{
	void *module_slicer;
	void *pc_slicer; /** ASLR turned off? **/

} sb_slicer_t;

/********************************************************************
 * Implementation
 */

DR_EXPORT void *sb_init() {

	sb_slicer_t *slicer = (sb_slicer_t *) dr_global_alloc(sizeof(sb_slicer_t));

	slicer->module_slicer = NULL;
	slicer->pc_slicer = NULL;

	return slicer;
}

DR_EXPORT void sb_exit(void *slicer_opaque) {

	sb_slicer_t *slicer = (sb_slicer_t *) slicer_opaque;

	if (slicer->module_slicer)
		sb_module_slicer_destroy(slicer->module_slicer);

	if (slicer->pc_slicer)
		sb_pc_slicer_destroy(slicer->pc_slicer);

	dr_global_free(slicer, sizeof(sb_slicer_t));
}

DR_EXPORT void sb_register_module_slicer(void *slicer_opaque, file_t module_list){

	sb_slicer_t *slicer = (sb_slicer_t *) slicer_opaque;
	DR_ASSERT(slicer);

	if (!slicer->module_slicer){
		drmgr_priority_t checker_pri = { sizeof(drmgr_priority_t), "checker_pri",
				NULL, NULL, 401 };
		slicer->module_slicer = sb_module_slicer_init(&checker_pri);
	}

	sb_module_slicer_register_file(slicer->module_slicer, module_list);
}

DR_EXPORT void sb_register_pc_slicer(void *slicer_opaque, file_t pc_list){

	sb_slicer_t *slicer = (sb_slicer_t *) slicer_opaque;
	DR_ASSERT(slicer);

	if (slicer->pc_slicer)
		slicer->pc_slicer = sb_pc_slicer_init();

	sb_pc_slicer_register_file(slicer->pc_slicer, pc_list);
}

DR_EXPORT bool sb_slice_instr(void *slicer_opaque, app_pc instr_addr){

	sb_slicer_t *slicer = (sb_slicer_t *) slicer_opaque;
	DR_ASSERT(slicer);

	if (sb_slicer_module_slice_out(slicer->module_slicer, instr_addr))
		return true;

	return false;
}
