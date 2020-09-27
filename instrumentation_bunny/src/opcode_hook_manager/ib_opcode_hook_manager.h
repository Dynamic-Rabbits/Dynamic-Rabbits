/**
 *  @file ib_instr_map.h
 *  @brief Functions used to maintain a map that stores hook info
 *  for opcodes
 *  @author John F.X. Galea
 */

#ifndef IB_INSTR_MAP_H_
#define IB_INSTR_MAP_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "ib_hook_summary.h"
#include "../ib_data.h"
#include "../ib_defines.h"
#include "../hook_info/ib_hook_info.h"

/**
 *  Creates a new opcode hook mngr.
 *
 *  Needs to be destroyed by ib_destroy_opcode_map.
 *
 *  @return Returns the newly created opcode hook map.
 */
void* ib_opcode_hook_mngr_create();

/**
 *  Destroys a opcode hook mngr.
 *
 *  @param opcode_hook_mngr The opcode hook manager to destroy.
 */
void ib_opcode_hook_mngr_destroy(void *opcode_hook_mngr);

/**
 *  Registers a new instrum tool.
 *
 *  @param opcode_hook_mngr The opcode hook manager
 *  @param tool_id The given ID of the instrum tool. IDs from 1024 and below are reserved.
 */
void ib_opcode_hook_mngr_register_instrum_tool(void *hook_mngr,
        unsigned int tool_id);

/**
 *  Unregisters a instrum tool.
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param tool_id The ID of the instrum tool to unregister.
 */
bool ib_opcode_hook_mngr_unregister_instrum_tool(void *hook_mngr,
        unsigned int tool_id);

/**
 *  Registers a hook to instructions with a given opcode for a specific instrum tool.
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param tool_id The ID of the registered instrum tool.
 *  @param opcode The opcode to hook.
 *  @param src_opcode_hook_info Information related to the hook.
 */
void ib_opcode_hook_mngr_hook_opcode_for_tool(void *opcode_hook_mngr,
        unsigned int tool_id, int opcode, ib_hook_info_t *src_opcode_hook_info);

/**
 *  Unregisters a hook to instructions with a given opcode for a specific instrum tool.
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param tool_id The ID of the registered instrum tool.
 *  @param opcode The opcode to hook.
 *  @param src_opcode_hook_info Information related to the hook.
 */
void ib_opcode_hook_mngr_unhook_opcode_for_tool(void *opcode_hook_mngr,
        unsigned int tool_id, int opcode);

/**
 *  Registers the default hook for an instrum tool.
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param tool_id The ID of the instrum tool to unregister the hook.
 *  @param src_default_hook_info Information related to the default hook.
 */
void ib_opcode_hook_mngr_hook_default_for_tool(void *opcode_hook_mngr,
        unsigned int tool_id, ib_hook_info_t *src_default_hook_info);

/**
 *  Unregisters the default hook for an instrum tool.
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param tool_id The ID of the instrum tool to unregister the hook.
 *
 *  @return Returns whether the default hook was unregistered.
 */
bool ib_opcode_hook_mngr_unhook_default_for_tool(void *opcode_hook_mngr,
        unsigned int tool_id);

bool ib_opcode_hook_mngr_get_hook_summary(void *hook_mngr_opaque,
        instr_t *instr, ib_hook_summary_t *summary,
        ib_instrum_analysis_data_t *analysis_data);

/**************************************************************************
 * Option Flag Checks
 */

bool ib_is_pc_enabled_for_instr(instr_t *instr);

bool ib_is_immed_opnd_enabled_for_instr(instr_t *instr);

bool ib_is_reg_opnd_enabled_for_instr(instr_t *instr);

bool ib_is_addr_opnd_enabled_for_instr(instr_t *instr);

bool ib_is_full_addr_gen_enabled_for_instr(instr_t *instr);

bool ib_is_addr_gen_enabled_for_instr(instr_t *instr);

bool ib_is_loc_size_enabled_for_instr(instr_t *instr);

bool ib_is_loc_type_enabled_for_instr(instr_t *instr);

bool ib_is_conc_enabled_for_instr(instr_t *instr);

bool ib_is_opnd_count_enabled_for_instr(instr_t *instr);

bool ib_is_flag_enabled_for_instr(instr_t *instr);

bool ib_is_opcode_enabled_for_instr(instr_t *instr);

bool ib_is_full_opnd_storage_enabled_for_instr(instr_t *instr);

#endif /* INSTR_MAPPING_IB_INSTR_MAP_H_ */
