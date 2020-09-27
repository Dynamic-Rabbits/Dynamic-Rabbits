/**
 *  @file instrumentation_bunny.h
 *  @brief The instrumentation Bunny is useful for instrumenting instructions. Multiple
 *  bunnies can hook instr, where the instrumentation bunny will ensure minimal context
 *  switching.
 *  @author John F.X. Galea
 */

#ifndef INSTRUMENTATION_BUNNY_H_
#define INSTRUMENTATION_BUNNY_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "utility_bunny.h"
#include "ib_defines.h"
#include <stdint.h>

/**
 * Name of instrumentation bunny instrumentation pass priorities for app2app
 */
#define DRMGR_PRIORITY_NAME_IB "INSTRUMENTATION BUNNY"
#define DRMGR_PRIORITY_NAME_FAULT_IB "INSTRUMENTATION BUNNY_FAULT"

enum {
    DRMGR_PRIORITY_INSERT_INSTRUMENTATION_BUNNY = 505,
};

DR_EXPORT void ib_init_debug(void *slicer, ib_skip_check_t ib_skip_func, void *skip_data);

/**
 *  Initialises the instrumentation context, registering passed call-back
 *  functions.
 */
DR_EXPORT void ib_init(void *slicer);

/**
 *  Destroys the instrumentation context
 */
DR_EXPORT void ib_exit();

/**
 *  @return Returns true if the instrumentation bunny is initialised.
 */
DR_EXPORT bool ib_is_initialised();

/**
 *  Registers an instrumentation tool.
 *
 *  @return Returns instrum tool information to enable reference to it.
 *  For instance, to unregister, the info needs to be passed to
 *  \p ib_unregister_instrum_tool.
 */
DR_EXPORT void* ib_register_instrum_tool();

/*
 * Enables bb dup functionality. Mainly an entry point for the Taint Bunny in order
 * to enable fast pasts.
 *
 * Can ONLY be called once.
 */
DR_EXPORT void* ib_register_instrum_tool_ex(ib_dup_opts_t *dup_opts,
        ib_dup_fp_settings_t *fp_settings);

/**
 *  Unregisters an instrumentation tool.
 *
 *  @param tool_id The given ID of the instrum tool to unregister.
 */
DR_EXPORT bool ib_unregister_instrum_tool(void *tool_info);

/********************************************************************
 * Hooking
 */

void ib_hook_to_default(void *tool_info,
        ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options);

/**
 *  Registers the default hook for an instrum tool.
 *
 *  If not set, the default behaviour is to SKIP the instrumentation
 *  of the unhandled instruction.
 *
 *  @param user_default_instrum_func A function pointer to user instrumentation code.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 */
DR_EXPORT void ib_hook_cache_to_default(void *tool_info,
        ib_insert_hndle_data_t *cache_data, IB_INSTRUM_OPT options);

/**
 *  Unregisters the default hook for an instrum tool.
 *
 *  @param tool_id The ID of the instrum tool to unregister the hook.
 */
DR_EXPORT void ib_remove_default_hook(void *tool_info);

/**
 *  Skips the instrumentation of the function. Does not even trigger the
 *  default hook.
 *
 *  @param tool_id The tool ID managing the instrumentation.
 *  @param opcode The opcode of the instructions to skip.
 */
DR_EXPORT void ib_hook_skip(void *tool_info, int opcode);

void ib_hook_to_instr(void *tool_info, int opcode,
        ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options);

DR_EXPORT void ib_hook_to_instr_ex(void *tool_info, int opcode,
        ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

/**
 *  Inserts a callback function for the instrumentation of an instruction.
 *
 *  @param tool_id The tool ID managing the instrumentation.
 *  @param opcode The opcode of the instructions to instrument.
 *  @param user_instrum_func A function pointer to user instrumentation code.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 */
DR_EXPORT void ib_hook_cache_to_instr(void *tool_info, int opcode,
        ib_insert_hndle_data_t *cache_data, IB_INSTRUM_OPT options);

/**
 *  Inserts a callback function for the instrumentation of an instruction.
 *
 *  Allows the passing of further information compared to \p ib_hook_instr.
 *
 *  @param tool_id The tool ID managing the instrumentation.
 *  @param opcode The opcode of the instructions to instrument.
 *  @param user_instrum_func A function pointer to user instrumentation code.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 *  @param options Specification of options for instrumentation.
 *  @param check_hook_guard A function pointer for a employing a hook guard.
 *  May be set to NULL.
 */
DR_EXPORT void ib_hook_cache_to_instr_ex(void *tool_info, int opcode,
        ib_insert_hndle_data_t *cache_data, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

DR_EXPORT void ib_hook_to_branch_instr(void *tool_info, int opcode,
        ib_insert_hndle_data_t *user_instrum_data,
        ib_insert_hndle_data_t * target_instrum_data,
        ib_insert_hndle_data_t * fall_instrum_data, IB_INSTRUM_OPT options);

DR_EXPORT void ib_hook_to_branch_instr_ex(void *tool_info, int opcode,
        ib_insert_hndle_data_t * user_instrum_data,
        ib_insert_hndle_data_t *target_instrum_data,
        ib_insert_hndle_data_t * fall_instrum_data, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

/**
 *  Inserts a callback function for the instrumentation of a branch instruction.
 *
 *  @param tool_id The tool ID managing the instrumentation.
 *  @param opcode The opcode of the instructions to instrument.
 *  @param target_instrum_func A function pointer to user instrumentation
 *  code if the target branch is taken.
 *  @param fall_through_code_cache A function pointer to user instrumentation
 *  code if the fall through branch is taken.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 */
DR_EXPORT void ib_hook_cache_to_branch_instr(void *tool_info, int opcode,
        ib_insert_hndle_data_t *cache_data,
        ib_insert_hndle_data_t *target_cache_data,
        ib_insert_hndle_data_t *fall_through_code_cache,
        IB_INSTRUM_OPT options);

/**
 *  Inserts a callback function for the instrumentation of a branch instruction.
 *
 *  Allows the passing of further information compared to \p ib_hook_instr.
 *
 *  @param tool_id The tool ID managing the instrumentation.
 *  @param opcode The opcode of the instructions to instrument.
 *  @param target_instrum_func A function pointer to user instrumentation
 *  code if the target branch is taken.
 *  @param fall_through_code_cache A function pointer to user instrumentation
 *  code if the fall through branch is taken.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 *  @param check_hook_guard A function pointer for a employing a hook guard.
 *  May be set to NULL.
 */
DR_EXPORT void ib_hook_cache_to_branch_instr_ex(void *tool_info, int opcode,
        ib_insert_hndle_data_t *cache_data,
        ib_insert_hndle_data_t *target_cache_data,
        ib_insert_hndle_data_t *fall_through_code_cache, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

/**
 *  Unregisters a hook to instructions with a given opcode for a specific instrum tool.
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param tool_id The ID of the registered instrum tool.
 *  @param opcode The opcode to hook.
 *  @param src_opcode_hook_info Information related to the hook.
 */
DR_EXPORT void ib_remove_hook_via_opcode(void *tool_info, int opcode);

/********************************************************************
 * Information Retrieval
 */
/**
 *  Retrieves the opnd identifier stored in a given component slot
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @param comp_access_slot Component slot to access
 *  @return The opnd identifier
 */
DR_EXPORT uintptr_t ib_get_comp_opnd(void *drcontext,
        ub_opnd_access_t *opnd_access);

/**
 *  Retrieves the size of opnd stored in a given component slot.
 *  This is useful to iterate over the conc bytes
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @param comp_access_slot Component slot to access
 *  @return The size of operand
 */
DR_EXPORT uintptr_t ib_get_comp_size(void *drcontext,
        ub_opnd_access_t *opnd_access);

/**
 *  Retrieves the conc array of a given component slot
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @param comp_access_slot Component slot to access
 *  @return A pointer to the conc value
 */
DR_EXPORT byte *ib_get_comp_conc(void *drcontext,
        ub_opnd_access_t *opnd_access);

/**
 *  Retrieves the type of opnd stored in a given component slot
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @param comp_access_slot Component slot to access
 *  @return The type of location
 */
DR_EXPORT loc_t ib_get_comp_type(void *drcontext,
        ub_opnd_access_t *opnd_access);

/**
 *  Returns the number of sources of the instrumented instruction
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @return Source count
 */
DR_EXPORT size_t ib_get_num_srcs(void *drcontext);

/**
 *  Returns the number of destinations of the instrumented instruction
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @return Destination count
 */
DR_EXPORT size_t ib_get_num_dsts(void *drcontext);

/**
 *  Returns the pc of the instrumented instruction
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @return The pc of the instrumented instruction
 */
DR_EXPORT app_pc ib_get_pc(void *drcontext);

/**
 *  Returns the opcode of the instrumented instruction
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @return Returns the opcode.
 */
DR_EXPORT int ib_get_opcode(void *drcontext);

/**
 *  Returns the current value of the flags register.
 *
 *  Make sure that the appropriate flag is set when initialising the hook info
 *  before calling this function. Otherwise, you have undefined behaviour!
 *
 *  @return The value of the flags register
 */
DR_EXPORT uintptr_t ib_get_flags(void *drcontext);

/*******************************************************************************
 * INLINE interface.
 */

DR_EXPORT void ib_insert_load_per_thread_data(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t data_reg);

DR_EXPORT void ib_insert_get_num_srcs(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg);

DR_EXPORT void ib_insert_get_num_srcs_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_reg);

DR_EXPORT void ib_insert_get_num_dsts(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg);

DR_EXPORT void ib_insert_get_num_dsts_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_reg);

DR_EXPORT void ib_insert_get_pc(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg);

DR_EXPORT void ib_insert_get_opcode(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg);

DR_EXPORT void ib_insert_get_opcode_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_reg);

DR_EXPORT void ib_insert_get_flags(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg);

DR_EXPORT void ib_insert_get_flags_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_reg);

DR_EXPORT opnd_t ib_insert_get_flags_opnd_ex(reg_id_t data_reg);

DR_EXPORT void ib_load_flags(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t scratch_reg_xsp);

DR_EXPORT void ib_insert_get_comp_opnd(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg, ub_opnd_access_t *opnd_access);

DR_EXPORT bool ib_insert_get_direct_opnd_to_comp_opnd(void *drcontext,
        ub_opnd_access_t *opnd_access, opnd_t *out_opnd);

DR_EXPORT void ib_insert_get_comp_opnd_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_data,
        ub_opnd_access_t *opnd_access);

DR_EXPORT void ib_insert_get_comp_size(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg, ub_opnd_access_t *opnd_access);

DR_EXPORT void ib_insert_get_comp_size_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_reg,
        ub_opnd_access_t *opnd_access);

DR_EXPORT void ib_insert_get_comp_conc(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg, size_t opnd_size,
        ub_opnd_access_t *opnd_access, size_t disp);

DR_EXPORT void ib_insert_get_comp_conc_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_reg, size_t opnd_size,
        ub_opnd_access_t *opnd_access, size_t disp);

DR_EXPORT opnd_t ib_get_comp_conc_opnd_ex(reg_id_t data_reg, size_t opnd_size,
        ub_opnd_access_t *opnd_access, size_t disp);

DR_EXPORT void ib_insert_get_comp_type(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t reg, ub_opnd_access_t *opnd_access);

DR_EXPORT void ib_insert_get_comp_type_ex(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t data_reg, reg_id_t res_reg,
        ub_opnd_access_t *opnd_access);

#endif /* INSTRUMENTATION_BUNNY_H_ */
