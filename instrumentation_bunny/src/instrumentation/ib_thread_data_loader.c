#include "ib_thread_data_loader.h"

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"
#include "../ib_defines.h"
#include "../ib_data.h"
#include "../tls_access/ib_tls_access.h"

void ib_loaded_thread_data(void *drcontext, instrlist_t *ilist, instr_t *where,
		ib_thrd_data_spill_info_t *info) {

	if (!info->is_loaded) {

		opnd_t thread_data_opnd = ib_tls_get_raw_slot_opnd(
				IB_RAW_SLOT_THRD_DATA);
		opnd_t opnd = opnd_create_reg(info->reg1);
		instr_t *instr = INSTR_CREATE_mov_ld(drcontext, opnd, thread_data_opnd);
		instrlist_meta_preinsert(ilist, where, instr);

		info->is_loaded = true;
	}
}
