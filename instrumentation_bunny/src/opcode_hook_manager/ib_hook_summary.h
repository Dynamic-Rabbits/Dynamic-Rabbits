/*
 * ib_hook_summary.h
 *
 *  Created on: 17 Aug 2018
 *      Author: john
 */

#ifndef INSTRUMENTATION_IB_HOOK_SUMMARY_H_
#define INSTRUMENTATION_IB_HOOK_SUMMARY_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "ib_instrum_tool.h"

#define MAX_INSTRUM_HOOKS 8

typedef struct {

	ib_hook_info_t *considered_hooks[MAX_INSTRUM_HOOKS];

	bool is_full_opnd_storage_enabled;
	bool is_opcode_enabled;
	bool is_pc_enabled;
	bool is_flag_enabled;
	bool is_opnd_count_enabled;
	bool is_conc_enabled;
	bool is_loc_type_enabled;
	bool is_loc_size_enabled;
	bool is_addr_gen_enabled;
	bool is_full_addr_gen_enabled;
    bool is_addr_opnd_enabled;
    bool is_reg_opnd_enabled;
    bool is_immed_opnd_enabled;

} ib_hook_summary_t;

void ib_hook_summary_init(ib_hook_summary_t *hook_summary);

void ib_hook_summary_add(ib_hook_summary_t *hook_summary, ib_hook_info_t *hook_info, int index);


#endif /* INSTRUMENTATION_IB_HOOK_SUMMARY_H_ */
