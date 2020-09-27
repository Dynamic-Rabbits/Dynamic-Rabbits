/*
 * stack_checker.c
 *
 *      Author: john
 */

#include "dr_defines.h"
#include "../path_bunny.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"
#include <inttypes.h>
#include <string.h>

tb_raw_taint_policy_t taint_policy;

void *path_bunny;
void *taint_bunny;
void *fd_input_ctx;

bool detected = false;

void clean_call_test() {

    app_pc pc = ib_get_pc(dr_get_current_drcontext());
    disassemble(dr_get_current_drcontext(), pc, STDERR);
    dr_fprintf(STDERR, "\n");
    detected = true;
}

void pb_handle_cmp_func(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, clean_call_test, false, 0);
}

static void init_funcs(path_bunny_funcs_t *func) {

    func->pb_cmp_tainted_reg_1_mem_1_func = pb_handle_cmp_func;
    func->pb_cmp_reg_1_tainted_mem_1_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_1_tainted_mem_1_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_2_mem_2_func = pb_handle_cmp_func;
    func->pb_cmp_reg_2_tainted_mem_2_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_2_tainted_mem_2_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_4_mem_4_func = pb_handle_cmp_func;
    func->pb_cmp_reg_4_tainted_mem_4_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_4_tainted_mem_4_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_8_mem_8_func = pb_handle_cmp_func;
    func->pb_cmp_reg_8_tainted_mem_8_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_8_tainted_mem_8_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_16_mem_16_func = pb_handle_cmp_func;
    func->pb_cmp_reg_16_tainted_mem_16_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_16_tainted_mem_16_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_1_reg_1_func = pb_handle_cmp_func;
    func->pb_cmp_mem_1_tainted_reg_1_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_1_tainted_reg_1_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_2_reg_2_func = pb_handle_cmp_func;
    func->pb_cmp_mem_2_tainted_reg_2_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_2_tainted_reg_2_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_4_reg_4_func = pb_handle_cmp_func;
    func->pb_cmp_mem_4_tainted_reg_4_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_4_tainted_reg_4_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_8_reg_8_func = pb_handle_cmp_func;
    func->pb_cmp_mem_8_tainted_reg_8_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_8_tainted_reg_8_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_16_reg_16_func = pb_handle_cmp_func;
    func->pb_cmp_mem_16_tainted_reg_16_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_16_tainted_reg_16_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_1_reg_1_func = pb_handle_cmp_func;
    func->pb_cmp_reg_1_tainted_reg_1_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_1_tainted_reg_1_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_2_reg_2_func = pb_handle_cmp_func;
    func->pb_cmp_reg_2_tainted_reg_2_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_2_tainted_reg_2_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_4_reg_4_func = pb_handle_cmp_func;
    func->pb_cmp_reg_4_tainted_reg_4_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_4_tainted_reg_4_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_8_reg_8_func = pb_handle_cmp_func;
    func->pb_cmp_reg_8_tainted_reg_8_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_8_tainted_reg_8_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_16_reg_16_func = pb_handle_cmp_func;
    func->pb_cmp_reg_16_tainted_reg_16_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_16_tainted_reg_16_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_reg_1_imm_1_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_2_imm_2_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_4_imm_4_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_reg_8_imm_8_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_1_imm_1_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_2_imm_2_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_4_imm_4_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_8_imm_8_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_1_mem_1_func = pb_handle_cmp_func;
    func->pb_cmp_mem_1_tainted_mem_1_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_1_tainted_mem_1_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_2_mem_2_func = pb_handle_cmp_func;
    func->pb_cmp_mem_2_tainted_mem_2_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_2_tainted_mem_2_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_4_mem_4_func = pb_handle_cmp_func;
    func->pb_cmp_mem_4_tainted_mem_4_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_4_tainted_mem_4_func = pb_handle_cmp_func;

    func->pb_cmp_tainted_mem_8_mem_8_func = pb_handle_cmp_func;
    func->pb_cmp_mem_8_tainted_mem_8_func = pb_handle_cmp_func;
    func->pb_cmp_tainted_mem_8_tainted_mem_8_func = pb_handle_cmp_func;
}

static void event_exit() {

    DR_ASSERT(detected);

    ub_ev_fd_input_destroy_ctx(fd_input_ctx);

    pb_exit(path_bunny);

    tb_raw_exit(taint_bunny);
    ib_exit();
    drmgr_exit();
}

static void got_read(ub_fd_input_data_t *input_data) {

    DR_ASSERT(taint_policy.get_default_label);

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

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    ib_init(NULL);

    tb_raw_initialise_bitwise_taint_policy(&taint_policy);

    taint_bunny = tb_raw_init_default(id, &taint_policy);

    path_bunny_funcs_t pb_func;
    init_funcs(&pb_func);
    path_bunny = pb_init(taint_bunny, &pb_func, PB_EV_CMP | PB_EV_TEST, NULL, IB_OPT_PC_INFO);

    pb_register_hooks(path_bunny);
    tb_register_hooks(taint_bunny);

    fd_input_ctx =
            ub_ev_fd_input_init_ctx(got_read, true,
                    UB_EV_FD_INPUT_OPT_LOCAL_SOCKET
                            | UB_EV_FD_INPUT_OPT_SOURCE_INFO
                            | UB_EV_FD_INPUT_OPT_REMOTE_SOCKET
                            | UB_EV_FD_INPUT_OPT_FILE, id);

    dr_register_exit_event(event_exit);
}
