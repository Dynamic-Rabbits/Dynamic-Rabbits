/**
 *  @file ib_hooking.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef IB_HOOKING_H_
#define IB_HOOKING_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "../ib_defines.h"
#include "../hook_info/ib_hook_info.h"

/**
 * Creates a new instrum tool.
 *
 * @param tool_id The ID of the new instrum tool.
 * @return Returns the newly created instrum tool.
 */
void* ib_instrum_tool_create(unsigned int tool_id);

/**
 * Destroys the instrum tool.
 *
 * @param instrum_tool The instrum tool to destroy.
 */
void ib_instrum_tool_destroy(void *instrum_tool);

/**
 *  Registers a hook for a given opcode.
 *
 *  @param instrum_tool The instrum tool.
 *  @param opcode The opcode of the instruction to hook.
 *  @param opcode_hook_info The info about the hook.
 */
void ib_instrum_tool_register_opcode_hook(void *instrum_tool,
		int opcode, ib_hook_info_t *opcode_hook_info);

/**
 *  Returns the hook info of a given opcode. Returns NULL if the opcode
 *  is not registered.
 *
 *  @param instrum_tool The instrum tool.
 *  @param opcode The opcode of the instruction in order to perform lookup.
 *  @return Returns the list of hook info registered to the opcode.
 */
void *ib_instrum_tool_get_hook_info(void *instrum_tool,
		int opcode);

/**
 *  Registers a default hook.
 *
 *  Note one needs to set the skip flag if an instruction of an
 *  unregistered opcode does not want to be hooked by the default
 *  analysis function. This is done via the
 *  \p ib_instrum_tool_register_opcode_hook function.
 *
 *  @param instrum_tool The instrum tool.
 *  @param default_hook_info The info about the hook.
 */
void ib_instrum_tool_register_default_opcode_hook(void *instrum_tool,
		ib_hook_info_t *default_hook_info);

/**
 *  Registers a default hook.
 *
 *  Note one needs to set the skip flag if an instruction of an
 *  unregistered opcode does not want to be hooked by the default
 *  analysis function. This is done via the
 *  \p ib_instrum_tool_register_opcode_hook function.
 *
 *  @param instrum_tool The instrum tool.
 *  @param default_hook_info The info about the hook.
 *  @return Returns the default opcode hook. NULL is not set.
 */
ib_hook_info_t *ib_instrum_tool_get_default_opcode_hook(
		void *instrum_tool);

/**
 *  Specifies whether the default opcode hook is set.
 *
 *  @param instrum_tool The instrum tool.
 *  @return Returns true if the default opcode hook is set.
 */
bool ib_instrum_tool_is_default_opcode_hook_set(void *instrum_tool);

/**
 * Removes hook associated with an opcode.
 *
 * @param instrum_tool The instrum tool.
 * @param opcode The opcode to unregister the hook from.
 * @return Returns true if a hook is removed.
 */
bool ib_instrum_tool_unregister_opcode_hook(void *opcode_hook_mngr, int opcode);

/**
 * Removes the default hook of the instrum tool
 *
 * @param instrum_tool The instrum tool.
 */
bool ib_instrum_tool_unregister_default_opcode_hook(void *instrum_tool);

/**
 *  Returns the ID of the Instrumentation Tool
 */
unsigned int ib_instrum_tool_get_id(void *instrum_tool_opaque);


#endif /* IB_HOOKING_H_ */
