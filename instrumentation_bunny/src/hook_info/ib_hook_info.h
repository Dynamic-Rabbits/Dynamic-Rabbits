/**
 *  @file ib_hook_info.h
 *  @brief Translates Hook Info (user-level) to instrum_info (implementation level)
 *  @author John F.X. Galea
 */

#ifndef HOOK_INFO_IB_HOOK_INFO_H_
#define HOOK_INFO_IB_HOOK_INFO_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"

#include "utility_bunny.h"
#include "../ib_defines.h"
#include <stdint.h>
#include "../code_cache/ib_code_cache.h"
#include "../code_inline/ib_code_inline.h"

/**
 *  @struct ib_opcode_hook_info_t
 *
 *  @var ib_opcode_hook_info_t::user_instrum_func
 *  The function pointer to the instrumentation code of the user.
 *
 *  @var ib_opcode_hook_info_t::spill_reg_func
 *  Called to spill registers upon the calling of the callback function.
 *
 *  @var ib_opcode_hook_info_t::restore_reg_func
 *  Called to restore registers after the calling of the callback function.
 *
 *  @var ib_opcode_hook_info_t::pos
 *  The position of the call-back, that is, is the call-back called before or
 *  after the execution of the instruction.
 *
 *  @var ib_opcode_hook_info_t::options
 *  A description of options to consider when inserting the callback function.
 *
 *  @var ib_opcode_hook_info_t::is_branch_hook
 *  A flag that determines whether the instrumentation of a branch instruction is taking place
 *
 *  @var ib_opcode_hook_info_t::is_skip
 *  A flag denoting whether this instruction should be skipped, and not applicable to the
 *  default call-back.
 *
 *  @var ib_opcode_hook_info_t:: check_hook_guard
 *  A function pointer to a hook guard. It is optionally set to enable
 *  more fine-grained analysis on whether to perform instrumentation.
 */
typedef struct {

    bool is_inline;
    bool is_skip;
    bool is_branch_hook;
    IB_INSTRUM_POS pos;
    IB_INSTRUM_OPT options;

    ib_check_hook_guard_func_t check_hook_guard;
    ib_guard_result_t action_result;

    void *user_func;
    void *target_func;
    void *fall_through_func;

} ib_hook_info_t;

/**
 *  Copies hook info to a struct on the heap.
 *
 *  To destroy, call \p src_opcode_hook_info
 *
 *  @param hook_info The hook info to destroy.
 */
void* ib_hook_info_create_from_other(ib_hook_info_t *src_opcode_hook_info);

/**
 *  Destroys a hook info stored on the heap.
 */
void ib_hook_info_destroy(void *hook_info);

/**
 *  Initialises a hook info struct for skipping instrumentation of the instr.
 *
 *  @param hook_info The struct to initialise.
 */
void ib_hook_info_init_skip(ib_hook_info_t *hook_info);

/**
 *  Initialises a hook info struct for instrumentation an instr.It essentially sets
 *  the fields of the struct with the supplied data.
 *
 *  @param hook_info The struct to initialise.
 *  @param user_instrum_func A function pointer to user instrumentation code.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 */
void ib_hook_cache_info_init_instrum_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *insert_hndle_data, IB_INSTRUM_OPT options);

/**
 *  Initialises a hook info struct for instrumentation an instr. It essentially sets
 *  the fields of the struct with the supplied data.
 *
 *  Provides additional information in comparison to \p ib_hook_info_init_instrum_instr.
 *
 *  @param hook_info The struct to initialise.
 *  @param user_instrum_func A function pointer to user instrumentation code.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 *  @param pos Specifies where to place the instrumentation.
 *  @param check_hook_guard A function pointer for a employing a hook guard.
 *  May be set to NULL.
 */
void ib_hook_cache_info_init_instrum_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *code_cache_data,

        IB_INSTRUM_OPT options, IB_INSTRUM_POS pos,
        ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

/**
 *  Initialises a hook info struct for instrumentation a branch instr. It essentially sets
 *  the fields of the struct with the supplied data.
 *
 *  @param hook_info The struct to initialise.
 *  @param target_instrum_func A function pointer to user instrumentation
 *  code if the target branch is taken.
 *  @param fall_through_code_cache A function pointer to user instrumentation
 *  code if the fall through branch is taken.
 *  @param spill_reg A function pointer to spilling registers.
 *  @param restore_reg_func A function pointer to restoring registers.
 *  @param options Specification of options for instrumentation.
 */
void ib_hook_cache_info_init_instrum_branch_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *code_cache_data,
        ib_insert_hndle_data_t *target_code_cache_data,
        ib_insert_hndle_data_t *fall_through_code_cache_data,

        IB_INSTRUM_OPT options);

/**
 *  Initialises a hook info struct for instrumentation a branch instr. It essentially sets
 *  the fields of the struct with the supplied data.
 *
 *  Provides additional information in comparison to \p ib_hook_info_init_instrum_instr.
 *
 *  @param hook_info The struct to initialise.
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
void ib_hook_cache_info_init_instrum_branch_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *code_cache_data,
        ib_insert_hndle_data_t *target_code_cache_data,
        ib_insert_hndle_data_t *fall_through_code_cache_data,

        IB_INSTRUM_OPT options, IB_INSTRUM_POS pos,
        ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

void ib_hook_info_init_instrum_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *insert_hndle_data, IB_INSTRUM_OPT options);

void ib_hook_info_init_instrum_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

void ib_hook_info_init_instrum_branch_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *user_instrum_data,
        ib_insert_hndle_data_t *target_instrum_data,
        ib_insert_hndle_data_t *fall_instrum_data,

        IB_INSTRUM_OPT options);

void ib_hook_info_init_instrum_branch_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *user_instrum_data,
        ib_insert_hndle_data_t *target_instrum_data,
        ib_insert_hndle_data_t *fall_instrum_data,
        IB_INSTRUM_OPT options, IB_INSTRUM_POS pos,
        ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result);

#endif /* HOOK_INFO_IB_HOOK_INFO_H_ */
