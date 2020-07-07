/*
 * ib_hook_summary.c
 *
 *      Author: john
 */

#include "ib_hook_summary.h"
#include "ib_instrum_tool.h"
#include "string.h"
#include "../options/ib_option.h"

void ib_hook_summary_init(ib_hook_summary_t *hook_summary){

	memset(hook_summary, 0, sizeof(ib_hook_summary_t));
}

void ib_hook_summary_add(ib_hook_summary_t *hook_summary, ib_hook_info_t *hook_info, int index){

	hook_summary->considered_hooks[index] = hook_info;

	hook_summary->is_full_opnd_storage_enabled |= ib_options_is_full_opnd_storage_enabled(hook_info->options);
	hook_summary->is_conc_enabled |= ib_options_is_conc_enabled(hook_info->options);
	hook_summary->is_loc_type_enabled |= ib_options_is_loc_type_enabled(hook_info->options);
	hook_summary->is_loc_size_enabled |= ib_options_is_loc_size_enabled(hook_info->options);
	hook_summary->is_opcode_enabled |= ib_options_is_opcode_enabled(hook_info->options);
	hook_summary->is_opnd_count_enabled |= ib_options_is_opnd_count_enabled(hook_info->options);
	hook_summary->is_addr_gen_enabled |= ib_options_is_addr_gen_mode_enabled(hook_info->options);
	hook_summary->is_full_addr_gen_enabled |= ib_options_is_full_address_gen_enabled(hook_info->options);
	hook_summary->is_flag_enabled|= ib_options_is_flag_enabled(hook_info->options);
	hook_summary->is_pc_enabled |= ib_options_is_pc_enabled(hook_info->options);
    hook_summary->is_addr_opnd_enabled |= ib_options_is_addr_opnd_enabled(hook_info->options);
    hook_summary->is_reg_opnd_enabled |= ib_options_is_reg_opnd_enabled(hook_info->options);
    hook_summary->is_immed_opnd_enabled |= ib_options_is_immed_opnd_enabled(hook_info->options);



}

