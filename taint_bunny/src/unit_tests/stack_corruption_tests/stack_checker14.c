#include "dr_defines.h"
#include "taint_bunny.h"

#include "instrumentation_bunny.h"
#include <inttypes.h>
#include <string.h>

tb_raw_taint_policy_t taint_policy;

void *taint_bunny;
void *fd_input_ctx;
void *ret_checker;

static void event_exit() {

    ib_unregister_instrum_tool(ret_checker);

    ub_ev_fd_input_destroy_ctx(fd_input_ctx);

    tb_raw_exit(taint_bunny);

    tb_raw_destroy_tree_taint_policy();
    ib_exit();
    drmgr_exit();
}

static void got_read(ub_fd_input_data_t *input_data) {

    ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
            input_data->buf_list, 0);

    if (input_data->type == UB_FD_FILE) {

        if (strstr(input_data->source_info.file_info.base_name, ".so") == NULL) {

            tb_taint_mem_block(taint_bunny, (uintptr_t) input_buf->buf,
                    input_buf->size, taint_policy.get_default_label());
        }
    } else {

        tb_taint_mem_block(taint_bunny, (uintptr_t) input_buf->buf,
                input_buf->size, taint_policy.get_default_label());

    }
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

    tb_raw_initialise_tree_taint_policy(&taint_policy);

    tb_options_t te_options;
    te_options.enable_inline = false;
    te_options.enable_taint_off = false;
    te_options.enable_fp = false;

    taint_bunny = tb_raw_init(id, IB_OPT_BARE, &te_options, NULL, &taint_policy);

    tb_register_hooks(taint_bunny);
    register_ret_checker();

    fd_input_ctx =
            ub_ev_fd_input_init_ctx(got_read, true,
                    UB_EV_FD_INPUT_OPT_LOCAL_SOCKET
                            | UB_EV_FD_INPUT_OPT_SOURCE_INFO
                            | UB_EV_FD_INPUT_OPT_REMOTE_SOCKET
                            | UB_EV_FD_INPUT_OPT_FILE, id);

    dr_register_exit_event(event_exit);
}
