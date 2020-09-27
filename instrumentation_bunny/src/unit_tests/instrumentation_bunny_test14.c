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

bool spilled = false;
bool restored = false;

void ib_spill_regs_func_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data, void **spill_user_data) {

    spilled = true;

    dr_save_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_restore_regs_func_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data, void *spill_user_data) {

    restored = true;
    dr_restore_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_clean_call(int value) {

    DR_ASSERT_MSG(value == 4, "ub_code_cache_test - test3 failed...");

    void *drcontext = dr_get_current_drcontext();

    int opcode = ib_get_opcode(dr_get_current_drcontext());
    DR_ASSERT_MSG(opcode == OP_lea, "ub_code_cache_test - test3 failed...");

    ub_opnd_access_t slot_acces;
    slot_acces.comp_field = UB_COMP_1;
    slot_acces.opnd_field = UB_SRC_OPND_1;

    loc_t type = ib_get_comp_type(dr_get_current_drcontext(), &slot_acces);
    DR_ASSERT_MSG(type == UB_MEM_TYPE, "ub_code_cache_test - test3 failed...");

    app_pc pc = ib_get_pc(dr_get_current_drcontext());

    instr_t instr;
    instr_init(drcontext, &instr);
    decode(drcontext, pc, &instr);

    size_t conc_size = ib_get_comp_size(dr_get_current_drcontext(),
            &slot_acces);

    // LEA must be sizeless
    DR_ASSERT_MSG(conc_size == 0, "ub_code_cache_test - test3 failed...");

    clean_called_1 = true;

    instr_free(drcontext, &instr);
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

    ib_hook_cache_to_instr(instrum_tool, OP_lea, &cc_data,
            IB_OPT_ADDR_OPND_INFO | IB_OPT_REG_OPND_INFO | IB_OPT_OPCODE_INFO
                    | IB_OPT_OPND_COUNT_INFO | IB_OPT_LOC_TYPE_INFO
                    | IB_OPT_PC_INFO | IB_OPT_CONC_INFO | IB_OPT_LOC_SIZE_INFO
                    | IB_OPT_ADDR_GEN_INFO | IB_OPT_FULL_OPND_INFO);

    dr_register_exit_event(event_exit);
}
