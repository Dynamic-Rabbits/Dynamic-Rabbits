#include "dr_defines.h"
#include "taint_bunny.h"

#include "instrumentation_bunny.h"
#include <inttypes.h>
#include <string.h>

tb_raw_taint_policy_t taint_policy;

void *taint_bunny;
void *ret_checker;

static void event_exit() {

    ib_unregister_instrum_tool(ret_checker);
    tb_raw_exit(taint_bunny);

    ib_exit();
    drmgr_exit();
}

static void ret_check() {

    ub_opnd_access_t ret_addr_slot;
    ret_addr_slot.opnd_field = UB_SRC_OPND_2;
    ret_addr_slot.comp_field = UB_COMP_1;

    uintptr_t xsp_val = ib_get_comp_opnd(dr_get_current_drcontext(),
            &ret_addr_slot);

    if (tb_is_some_mem_tainted(taint_bunny, xsp_val, sizeof(void*))) {
        dr_fprintf(STDERR, "Error: Stack Corruption detected at %p %d %p",
                ib_get_pc(dr_get_current_drcontext()), sizeof(void*), xsp_val);
        dr_exit_process(0);
    }
}

static void instrument_ret_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    dr_insert_clean_call(drcontext, ilist, where, ret_check, false, 0);
}

static void register_ret_checker() {

    ret_checker = ib_register_instrum_tool();

    ib_insert_hndle_data_t hndle_data;
    hndle_data.user_data = NULL;
    hndle_data.user_instrum_func = instrument_ret_checker;
    hndle_data.spill_reg_func = NULL;
    hndle_data.restore_reg_func = NULL;
    hndle_data.spilling_user_data = NULL;

    ib_hook_cache_to_instr_ex(ret_checker, OP_ret, &hndle_data,
            IB_OPT_ADDR_OPND_INFO | IB_OPT_PC_INFO | IB_OPT_FULL_OPND_INFO, IB_INSTRUM_BEFORE, ub_is_ret_instr,
            IB_GUARD_HOOK);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    ib_init(NULL);

    tb_raw_initialise_bitwise_taint_policy(&taint_policy);

    tb_options_t te_options;
    te_options.enable_inline = false;
    te_options.enable_taint_off = false;
    te_options.enable_fp = true;

    taint_bunny = tb_raw_init(id, IB_OPT_BARE, &te_options, NULL,
            &taint_policy);

    tb_register_hooks(taint_bunny);
    register_ret_checker();

    dr_register_exit_event(event_exit);
}
