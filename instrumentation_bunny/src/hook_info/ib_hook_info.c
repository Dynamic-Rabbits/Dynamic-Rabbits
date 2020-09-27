/**
 *  @file ib_hook_info.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ib_hook_info.h"
#include "../code_cache/ib_code_cache.h"
#include "../code_inline/ib_code_inline.h"
#include <string.h>

void ib_hook_info_init_skip(ib_hook_info_t *hook_info) {

    hook_info->is_inline = false;
    hook_info->is_skip = true;
    hook_info->options = IB_OPT_BARE;
    hook_info->is_branch_hook = false;
    hook_info->pos = IB_INSTRUM_BEFORE;
    hook_info->check_hook_guard = NULL;
    hook_info->action_result = IB_GUARD_SKIP;
}

static void ib_hook_info_init_helper(ib_hook_info_t *hook_info,
        IB_INSTRUM_OPT options) {

    hook_info->is_skip = false;
    hook_info->check_hook_guard = NULL;
    hook_info->options = options;

    hook_info->is_branch_hook = false;

    hook_info->fall_through_func = NULL;

    hook_info->target_func = NULL;

    hook_info->pos = IB_INSTRUM_BEFORE;

}

void ib_hook_info_init_instrum_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *insert_hndle_data, IB_INSTRUM_OPT options) {

    hook_info->is_inline = true;

    if (insert_hndle_data)
        hook_info->user_func = ib_code_inline_init(insert_hndle_data);
    else
        hook_info->user_func = NULL;

    ib_hook_info_init_helper(hook_info, options);
}

void ib_hook_cache_info_init_instrum_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *insert_hndle_data, IB_INSTRUM_OPT options) {

    hook_info->is_inline = false;

    if (insert_hndle_data)
        hook_info->user_func = ib_code_cache_init(insert_hndle_data);
    else
        hook_info->user_func = NULL;

    ib_hook_info_init_helper(hook_info, options);
}

void ib_hook_info_init_instrum_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *user_instrum_data, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result) {

    ib_hook_info_init_instrum_instr(hook_info, user_instrum_data, options);

    DR_ASSERT_MSG(pos == IB_INSTRUM_BEFORE,
            "We only support position IB_INSTRUM_BEFORE for now. PR welcome!");
    hook_info->pos = pos;
    hook_info->check_hook_guard = check_hook_guard;
    hook_info->action_result = action_result;
}

void ib_hook_cache_info_init_instrum_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *code_cache_data, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result) {

    ib_hook_cache_info_init_instrum_instr(hook_info, code_cache_data, options);

    DR_ASSERT_MSG(pos == IB_INSTRUM_BEFORE,
            "We only support position IB_INSTRUM_BEFORE for now. PR welcome!");
    hook_info->pos = pos;
    hook_info->check_hook_guard = check_hook_guard;
    hook_info->action_result = action_result;
}

void ib_hook_info_init_instrum_branch_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *user_instrum_func,
        ib_insert_hndle_data_t *target_instrum_func,
        ib_insert_hndle_data_t *fall_instrum_func, IB_INSTRUM_OPT options) {

    ib_hook_info_init_instrum_instr(hook_info, user_instrum_func, options);

    if (target_instrum_func) {
        hook_info->target_func = ib_code_inline_init(target_instrum_func);
    } else {
        hook_info->target_func = NULL;
    }

    if (fall_instrum_func) {
        hook_info->fall_through_func = ib_code_inline_init(fall_instrum_func);
    } else {
        hook_info->fall_through_func = NULL;
    }

    hook_info->is_branch_hook = true;
}

void ib_hook_cache_info_init_instrum_branch_instr(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *code_cache_data,
        ib_insert_hndle_data_t *target_code_cache_data,
        ib_insert_hndle_data_t *fall_through_code_cache_data,
        IB_INSTRUM_OPT options) {

    ib_hook_cache_info_init_instrum_instr(hook_info, code_cache_data, options);

    if (target_code_cache_data) {
        hook_info->target_func = ib_code_cache_init(target_code_cache_data);
    } else {
        hook_info->target_func = NULL;
    }

    if (fall_through_code_cache_data) {
        hook_info->fall_through_func = ib_code_cache_init(
                fall_through_code_cache_data);
    } else {
        hook_info->fall_through_func = NULL;
    }

    hook_info->is_branch_hook = true;
}

void ib_hook_info_init_instrum_branch_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *user_instrum_func,
        ib_insert_hndle_data_t *target_instrum_func,
        ib_insert_hndle_data_t *fall_instrum_func, IB_INSTRUM_OPT options,
        IB_INSTRUM_POS pos, ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result) {

    ib_hook_info_init_instrum_branch_instr(hook_info, user_instrum_func,
            target_instrum_func, fall_instrum_func, options);

    DR_ASSERT_MSG(pos == IB_INSTRUM_BEFORE,
            "We only support position IB_INSTRUM_BEFORE for now. PR welcome!");

    hook_info->pos = pos;
    hook_info->check_hook_guard = check_hook_guard;
    hook_info->action_result = action_result;
}

void ib_hook_cache_info_init_instrum_branch_instr_ex(ib_hook_info_t *hook_info,
        ib_insert_hndle_data_t *code_cache_data,
        ib_insert_hndle_data_t *target_code_cache_data,
        ib_insert_hndle_data_t *fall_through_code_cache_data,
        IB_INSTRUM_OPT options, IB_INSTRUM_POS pos,
        ib_check_hook_guard_func_t check_hook_guard,
        ib_guard_result_t action_result) {

    ib_hook_cache_info_init_instrum_branch_instr(hook_info, code_cache_data,
            target_code_cache_data, fall_through_code_cache_data, options);

    DR_ASSERT_MSG(pos == IB_INSTRUM_BEFORE,
            "We only support position IB_INSTRUM_BEFORE for now. PR welcome!");

    hook_info->pos = pos;
    hook_info->check_hook_guard = check_hook_guard;
    hook_info->action_result = action_result;

}

void* ib_hook_info_create_from_other(ib_hook_info_t *src_opcode_hook_info) {

    DR_ASSERT(src_opcode_hook_info);

    void *created_opcode_hook_info = (ib_hook_info_t *) dr_global_alloc(
            sizeof(ib_hook_info_t));
    memcpy(created_opcode_hook_info, src_opcode_hook_info,
            sizeof(ib_hook_info_t));

    return created_opcode_hook_info;
}

void ib_hook_info_destroy(void *hook_info_opaque) {

    ib_hook_info_t *hook_info = hook_info_opaque;

    if (!hook_info->is_skip) {

        if (hook_info->is_inline && hook_info->user_func != NULL)
            ib_code_inline_exit(hook_info->user_func);

        if (!hook_info->is_inline && hook_info->user_func != NULL)
            ib_code_cache_exit(hook_info->user_func);

        if (hook_info->is_branch_hook) {

            if (hook_info->is_inline && hook_info->target_func != NULL)
                ib_code_inline_exit(hook_info->target_func);

            if (!hook_info->is_inline && hook_info->target_func)
                ib_code_cache_exit(hook_info->target_func);

            if (hook_info->is_inline && hook_info->fall_through_func != NULL)
                ib_code_inline_exit(hook_info->fall_through_func);

            if (!hook_info->is_inline && hook_info->fall_through_func != NULL)
                ib_code_cache_exit(hook_info->fall_through_func);
        }
    }

    dr_global_free(hook_info, sizeof(ib_hook_info_t));
}
