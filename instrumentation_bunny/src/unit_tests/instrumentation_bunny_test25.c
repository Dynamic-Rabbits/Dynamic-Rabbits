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

int count = 0;

void *instrum_tool;

bool clean_called_1 = false;

void ib_clean_call(int value) {

    clean_called_1 = true;
    DR_ASSERT_MSG(value == 4, "ub_code_cache_test - test3 failed...");

    DR_ASSERT_MSG(ib_get_opcode(dr_get_current_drcontext()) == OP_add,
            "ub_code_cache_test - test3 failed...");
    DR_ASSERT_MSG(ib_get_num_dsts(dr_get_current_drcontext()) == 1,
            "ub_code_cache_test - test3 failed...");
    DR_ASSERT_MSG(ib_get_num_srcs(dr_get_current_drcontext()) == 2,
            "ub_code_cache_test - test3 failed...");
}

void ib_code_cache_insert_hndle_func_test(void *drcontext, instrlist_t *bb,
        instr_t *where, instr_t *app, void *user_data, void *spilling_data) {

    DR_ASSERT_MSG(user_data == (void * ) 8,
            "ub_code_cache_test - test2 failed...");

    count++;
    dr_insert_clean_call(drcontext, bb, where, ib_clean_call, false, 1,
            OPND_CREATE_INTPTR(4));
}

static void event_exit() {

    DR_ASSERT_MSG(count > 0, "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(clean_called_1 == true,
            "ub_code_cache_test - test4 failed...");

    ib_unregister_instrum_tool(instrum_tool);
    ib_exit();
    drmgr_exit();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();

    ib_init(NULL);

    instrum_tool = ib_register_instrum_tool();

    ib_insert_hndle_data_t cc_data;
    cc_data.user_data = (void *) 8;
    cc_data.user_instrum_func = ib_code_cache_insert_hndle_func_test;
    cc_data.spill_reg_func = NULL;
    cc_data.restore_reg_func = NULL;
    cc_data.spilling_user_data = NULL;

    ib_hook_to_instr(instrum_tool, OP_add, &cc_data,
            IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO | IB_OPT_OPCODE_INFO | IB_OPT_OPND_COUNT_INFO  | IB_OPT_FULL_OPND_INFO);

    dr_register_exit_event(event_exit);
}
