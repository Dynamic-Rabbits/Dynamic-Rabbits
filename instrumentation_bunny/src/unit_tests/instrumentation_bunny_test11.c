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
int count2 = 0;
int count3 = 0;

void *instrum_tool;
void *instrum_tool2;

bool clean_called_1 = false;
bool clean_called_2 = false;

bool spilled = false;
bool restored = false;

void ib_spill_regs_func_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data, void **spill_data) {

    spilled = true;

    dr_save_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

void ib_restore_regs_func_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data, void *spill_user_data) {

    restored = true;
    dr_restore_reg(drcontext, ilist, where, DR_REG_XBX, SPILL_SLOT_2);
}

app_pc pc;
int num_dst;
int num_src;

byte *conc_val;
size_t conc_size;

int opcode;

void ib_clean_call(int value) {

    clean_called_1 = true;
    DR_ASSERT_MSG(value == 4, "ub_code_cache_test - test3 failed...");

    void *drcontext = dr_get_current_drcontext();

    opcode = ib_get_opcode(dr_get_current_drcontext());
    pc = ib_get_pc(dr_get_current_drcontext());
    num_dst = ib_get_num_dsts(dr_get_current_drcontext());
    num_src = ib_get_num_srcs(dr_get_current_drcontext());

    ub_opnd_access_t slot_acces;
    slot_acces.comp_field = UB_COMP_1;
    slot_acces.opnd_field = UB_SRC_OPND_1;

    conc_val = (byte *) ib_get_comp_conc(dr_get_current_drcontext(), &slot_acces);
    conc_size = ib_get_comp_size(dr_get_current_drcontext(), &slot_acces);

    DR_ASSERT_MSG(opcode == OP_mov_st, "ub_code_cache_test - test3 failed...");
}

void ib_clean_call2(int value) {

    clean_called_2 = true;
    DR_ASSERT_MSG(value == 4, "ub_code_cache_test - test3 failed...");

    DR_ASSERT_MSG(clean_called_1 == true,
            "ub_code_cache_test - test3 failed...");

    void *drcontext = dr_get_current_drcontext();

    DR_ASSERT_MSG(ib_get_opcode(dr_get_current_drcontext()) == opcode,
            "ub_code_cache_test - test3 failed...");
    DR_ASSERT_MSG(pc == ib_get_pc(dr_get_current_drcontext()), "ub_code_cache_test - test3 failed...");
    DR_ASSERT_MSG(num_dst = ib_get_num_dsts(dr_get_current_drcontext()),
            "ub_code_cache_test - test3 failed...");

    ub_opnd_access_t slot_acces;
    slot_acces.comp_field = UB_COMP_1;
    slot_acces.opnd_field = UB_SRC_OPND_1;

    DR_ASSERT_MSG(conc_size > 0, "ub_code_cache_test - test3 failed...");

    DR_ASSERT_MSG(conc_size == ib_get_comp_size(dr_get_current_drcontext(), &slot_acces),
            "ub_code_cache_test - test3 failed...");

    DR_ASSERT_MSG(
            memcmp(ib_get_comp_conc(dr_get_current_drcontext(), &slot_acces), conc_val, conc_size) == 0,
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

void ib_code_cache_insert_hndle_func_test2(void *drcontext, instrlist_t *bb,
        instr_t *where, instr_t *app, void *user_data, void *spilling_data) {

    DR_ASSERT_MSG(user_data == (void * ) 8,
            "ub_code_cache_test - test2 failed...");

    count2++;
    dr_insert_clean_call(drcontext, bb, where, ib_clean_call2, false, 1,
    OPND_CREATE_INTPTR(4));
}

static void event_exit() {

    DR_ASSERT_MSG(count > 0, "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(count2 > 0, "ub_code_cache_test - test4 failed...");

    DR_ASSERT_MSG(clean_called_1 == true,
            "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(clean_called_2 == true,
            "ub_code_cache_test - test4 failed...");

    DR_ASSERT_MSG(spilled == true, "ub_code_cache_test - test4 failed...");
    DR_ASSERT_MSG(restored == true, "ub_code_cache_test - test4 failed...");

    ib_unregister_instrum_tool(instrum_tool2);
    ib_unregister_instrum_tool(instrum_tool);
    ib_exit();
    drmgr_exit();
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    /***
     * NOTE: THIS TEST WILL FAIL IF MULTI_THREADED. THIS IS A FLACKY TEST!
     */

    drmgr_init();

    ib_init(NULL);

    instrum_tool = ib_register_instrum_tool();
    instrum_tool2 = ib_register_instrum_tool();

    ib_insert_hndle_data_t cc_data;
    cc_data.user_data = (void *) 8;
    cc_data.user_instrum_func = ib_code_cache_insert_hndle_func_test;
    cc_data.restore_reg_func = ib_restore_regs_func_test;
    cc_data.spill_reg_func = ib_spill_regs_func_test;
    cc_data.spilling_user_data = NULL;

    ib_hook_cache_to_instr_ex(instrum_tool, OP_mov_st, &cc_data,
            IB_OPT_OPCODE_INFO | IB_OPT_OPND_COUNT_INFO | IB_OPT_PC_INFO
                    | IB_OPT_CONC_INFO | IB_OPT_LOC_SIZE_INFO,
            IB_INSTRUM_BEFORE, check_hook_guard_func_test, IB_GUARD_HOOK);

    ib_insert_hndle_data_t cc_data2;
    cc_data2.user_data = (void *) 8;
    cc_data2.user_instrum_func = ib_code_cache_insert_hndle_func_test2;
    cc_data2.restore_reg_func = ib_restore_regs_func_test;
    cc_data2.spill_reg_func = ib_spill_regs_func_test;
    cc_data2.spilling_user_data = NULL;

    ib_hook_cache_to_instr_ex(instrum_tool2, OP_mov_st, &cc_data2,
            IB_OPT_OPCODE_INFO | IB_OPT_OPND_COUNT_INFO | IB_OPT_PC_INFO
                    | IB_OPT_CONC_INFO | IB_OPT_LOC_SIZE_INFO  | IB_OPT_FULL_OPND_INFO,
            IB_INSTRUM_BEFORE, check_hook_guard_func_test, IB_GUARD_HOOK);

    dr_register_exit_event(event_exit);
}
