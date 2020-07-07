/*
 * ib_thread_data_loader.h
 *
 *  Created on: 16 Aug 2018
 *      Author: john
 */

#ifndef INSTRUMENTATION_IB_THREAD_DATA_LOADER_H_
#define INSTRUMENTATION_IB_THREAD_DATA_LOADER_H_

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"

#include "../ib_defines.h"


typedef struct {

	bool is_loaded;
	reg_id_t reg1;
    reg_id_t reg2;

} ib_thrd_data_spill_info_t;

void ib_loaded_thread_data(void *drcontext,
		instrlist_t *ilist, instr_t *where, ib_thrd_data_spill_info_t *info);


#endif /* INSTRUMENTATION_IB_THREAD_DATA_LOADER_H_ */
