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
#include <drreg.h>

int count = 0;

void *instrum_tool;

bool clean_called_1 = false;

bool spilled = false;
bool restored = false;

void ib_spill_regs_func_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data, void **spill_data) {

    spilled = true;

    dr_save_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_restore_regs_func_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data, void *spill_data) {

    restored = true;
    dr_restore_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_clean_call(int value) {

    clean_called_1 = true;
    DR_ASSERT_MSG(value == 4, "ub_code_cache_test - test3 failed...");

    void *drcontext = dr_get_current_drcontext();

    int opcode = ib_get_opcode(dr_get_current_drcontext());

    ub_opnd_access_t slot_acces;
    slot_acces.comp_field = UB_COMP_1;
    slot_acces.opnd_field = UB_DST_OPND_1;

    loc_t type = ib_get_comp_type(dr_get_current_drcontext(), &slot_acces);
    DR_ASSERT_MSG(type == UB_REG_TYPE, "ub_code_cache_test - test3 failed...");

    byte *conc_val = (byte *) ib_get_comp_conc(dr_get_current_drcontext(), &slot_acces);
    size_t conc_size = ib_get_comp_size(dr_get_current_drcontext(), &slot_acces);

    DR_ASSERT_MSG(conc_size > 0, "ub_code_cache_test - test3 failed...");

    uintptr_t opnd = ib_get_comp_opnd(dr_get_current_drcontext(), &slot_acces);
    DR_ASSERT_MSG(opnd == ub_get_byte_id(DR_REG_XAX, 0),
            "ub_code_cache_test - test3 failed...");

    DR_ASSERT_MSG(opcode == OP_mov_st, "ub_code_cache_test - test3 failed...");
}

bool check_hook_guard_func_test(instr_t *instr) {

    DR_ASSERT_MSG(instr_get_opcode(instr) == OP_mov_st,
            "ub_code_cache_test - test3 failed...");

    opnd_t dst = instr_get_dst(instr, 0);

    return (opnd_is_reg(dst) && opnd_get_reg(dst) == DR_REG_XAX);
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

    DR_ASSERT_MSG(spilled == true, "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(restored == true, "ub_code_cache_test - test4 failed...");

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
    cc_data.restore_reg_func = ib_restore_regs_func_test;
    cc_data.spill_reg_func = ib_spill_regs_func_test;
    cc_data.spilling_user_data = NULL;

    ib_hook_cache_to_instr_ex(instrum_tool, OP_mov_st, &cc_data,
            IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO | IB_OPT_OPCODE_INFO | IB_OPT_OPND_COUNT_INFO | IB_OPT_PC_INFO
                    | IB_OPT_LOC_TYPE_INFO | IB_OPT_CONC_INFO
                    | IB_OPT_LOC_SIZE_INFO  | IB_OPT_FULL_OPND_INFO,
            IB_INSTRUM_BEFORE, check_hook_guard_func_test, IB_GUARD_HOOK);

    dr_register_exit_event(event_exit);
}
