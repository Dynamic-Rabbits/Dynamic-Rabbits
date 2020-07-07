/**
 *  @file instrumentation_bunny_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "instrumentation_bunny.h"
#include <string.h>

int count1 = 0;
int count2 = 0;
int count3 = 0;

void *instrum_tool;

bool clean_called_1 = false;
bool clean_called_2 = false;
bool clean_called_3 = false;

void ib_clean_call_user() {

    clean_called_1 = true;
}

void ib_clean_call_target() {

    clean_called_2 = true;

    DR_ASSERT_MSG(ib_get_opcode(dr_get_current_drcontext()) == OP_je,
            "instrumentation_bunny15 - test3 failed...");

    uintptr_t flags = ib_get_flags(dr_get_current_drcontext());

    DR_ASSERT_MSG(ub_eflag_check_e(flags) == true,

    "instrumentation_bunny15 - test3 failed...");
}

void ib_clean_call_fall() {

    clean_called_3 = true;

    DR_ASSERT_MSG(ib_get_opcode(dr_get_current_drcontext()) == OP_je,
            "instrumentation_bunny15 - test3 failed...");

    uintptr_t flags = ib_get_flags(dr_get_current_drcontext());

    DR_ASSERT_MSG(!ub_eflag_check_e(flags),
            "instrumentation_bunny15 - test3 failed...");
}

void ib_user_insert_hndle_func_test(void *drcontext, instrlist_t *bb,
        instr_t *where, instr_t *app, void *user_data, void *spilling_data) {

    DR_ASSERT_MSG(user_data == (void * ) 3,
            "ub_code_cache_test - test2 failed...");

    count1++;
    dr_insert_clean_call(drcontext, bb, where, ib_clean_call_user, false, 0);
}

void ib_target_insert_hndle_func_test(void *drcontext, instrlist_t *bb,
        instr_t *where, instr_t *app, void *user_data, void *spilling_data) {

    DR_ASSERT_MSG(user_data == (void * ) 4,
            "ub_code_cache_test - test2 failed...");

    count2++;
    dr_insert_clean_call(drcontext, bb, where, ib_clean_call_target, false, 0);
}

void ib_fall_insert_hndle_func_test(void *drcontext, instrlist_t *bb,
        instr_t *where, instr_t *app, void *user_data, void *spilling_data) {

    DR_ASSERT_MSG(user_data == (void * ) 5,
            "ub_code_cache_test - test2 failed...");

    count3++;
    dr_insert_clean_call(drcontext, bb, where, ib_clean_call_fall, false, 0);
}

static void event_exit() {

    DR_ASSERT_MSG(count1 > 0, "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(count2 > 0, "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(count3 > 0, "ub_code_cache_test - test4 failed...");

    DR_ASSERT_MSG(clean_called_1 == true,
            "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(clean_called_2 == true,
            "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(clean_called_3 == true,
            "ub_code_cache_test - test4 failed...");

    ib_unregister_instrum_tool(instrum_tool);
    ib_exit();
    drmgr_exit();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();

    ib_init(NULL);

    instrum_tool = ib_register_instrum_tool();

    ib_insert_hndle_data_t in_data;
    in_data.user_data = (void *) 3;
    in_data.user_instrum_func = ib_user_insert_hndle_func_test;
    in_data.restore_reg_func = NULL;
    in_data.spill_reg_func = NULL;
    in_data.spilling_user_data = NULL;

    ib_insert_hndle_data_t target_data;
    target_data.user_data = (void *) 4;
    target_data.user_instrum_func = ib_target_insert_hndle_func_test;
    target_data.restore_reg_func = NULL;
    target_data.spill_reg_func = NULL;
    target_data.spilling_user_data = NULL;

    ib_insert_hndle_data_t fall_data;
    fall_data.user_data = (void *) 5;
    fall_data.user_instrum_func = ib_fall_insert_hndle_func_test;
    fall_data.restore_reg_func = NULL;
    fall_data.spill_reg_func = NULL;
    fall_data.spilling_user_data = NULL;

    ib_hook_to_branch_instr(instrum_tool, OP_je, &in_data, &target_data,
            &fall_data,
            IB_OPT_REG_OPND_INFO | IB_OPT_ADDR_OPND_INFO |
            IB_OPT_OPCODE_INFO | IB_OPT_OPND_COUNT_INFO | IB_OPT_PC_INFO
                    | IB_OPT_CONC_INFO | IB_OPT_ADDR_GEN_INFO  | IB_OPT_FULL_OPND_INFO
                    | IB_OPT_FLAG_INFO);

    dr_register_exit_event(event_exit);
}
