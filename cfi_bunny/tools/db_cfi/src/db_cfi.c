#include "dr_defines.h"
#include "drext.h"
#include "dr_api.h"
#include "cfi_bunny.h"

void *taint_bunny;
void *cfi_bunny;
void *fd_input_ctx;
void *arg_input_ctx;

bool enable_raw;
bool enable_fp;

static void event_exit() {

    cfib_exit(cfi_bunny);

    ub_ev_env_var_input_destroy_ctx();
    ub_ev_cl_arg_input_destroy_ctx(arg_input_ctx);
    ub_ev_fd_input_destroy_ctx(fd_input_ctx);

    if (enable_raw)
        tb_raw_exit(taint_bunny);
    else
        tb_cc_exit(taint_bunny);

    ib_exit();
    drmgr_exit();
}

static void got_read_from_env(ub_ev_env_var_data_t *env_var_data) {

    if (env_var_data->value) {

        size_t len = strlen(env_var_data->value);
        tb_taint_mem_block(taint_bunny, (uintptr_t) env_var_data->value, len,
                (void *) 1);
    }
}

static void got_read_from_arg(ub_ev_cl_arg_data_t *cl_arg_data) {

    size_t len = strlen(cl_arg_data->arg);
    tb_taint_mem_block(taint_bunny, (uintptr_t) cl_arg_data->arg, len,
            (void *) 1);
}

static void got_read_from_fd(ub_fd_input_data_t *input_data) {

    void *it = ub_list_get_start_it(input_data->buf_list);

    while (it) {

        ub_input_buf_t *input_buf = ub_list_get_it_value(it);
        it = ub_list_get_next_it(it);

        if (input_data->type == UB_FD_FILE) {

            if (strstr(input_data->source_info.file_info.base_name,
                    ".so") != NULL)
                continue;

        }

        size_t input_size = (size_t) (int) input_buf->size;
        tb_taint_mem_block(taint_bunny, (uintptr_t) input_buf->buf,
                (size_t) (int) input_buf->size, (void *) 1);
    }
}

static void handle_hijack_func(cfib_attack_type_t type,
        ub_opnd_access_t *corrupt_slot, void *user_data) {

    char buff[750];
    dr_snprintf(buff, 750, "./attack_%d.txt", dr_get_process_id());
    file_t attack_file = dr_open_file(buff, DR_FILE_WRITE_APPEND);
    dr_fprintf(attack_file, "------ ATTACK -------\n");

    void *drcontext = dr_get_current_drcontext();

    instr_t instr;
    instr_init(drcontext, &instr);

    app_pc current_pc = ib_get_pc(drcontext);
    decode(drcontext, current_pc, &instr);

    switch (type) {

    case CFIB_CALL_ATTACK:

        dr_fprintf(attack_file, "Call Hijack detected at %p\n",
                ib_get_pc(drcontext));
        break;

    case CFIB_JMP_ATTACK:
        dr_fprintf(attack_file, "Jump Hijack detected at %p\n",
                ib_get_pc(drcontext));
        break;

    case CFIB_RET_ATTACK:
        dr_fprintf(attack_file, "Return Hijack detected at %p\n",
                ib_get_pc(drcontext));
        break;
    default:
        DR_ASSERT(false);
    }

    void **conc_val = (void **) ib_get_comp_conc(drcontext, corrupt_slot);
    dr_fprintf(attack_file, "The data is %p\n", *conc_val);
    instr_disassemble_to_buffer(drcontext, &instr, buff, 750);
    dr_fprintf(attack_file, "Instr: %s\n", buff);

    instr_free(drcontext, &instr);

    dr_time_t time;
    dr_get_time(&time);

    dr_fprintf(attack_file, "TIME: %u:%u:%u.%u\n", time.hour, time.minute, time.second, time.milliseconds);

    dr_close_file(attack_file);

    dr_exit_process(0);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    ib_init(NULL);

    DR_ASSERT(argc == 2);
    enable_raw = (bool) strtol(argv[1], NULL, 10);

    /* Using a bitwise policy suffices in this case - such a simple but limited policy. */

    if (enable_raw) {
        tb_raw_taint_policy_t bitwise_taint_policy;
        tb_raw_initialise_bitwise_taint_policy(&bitwise_taint_policy);
        taint_bunny = tb_raw_init_default(id, &bitwise_taint_policy);
    } else {

        tb_cc_taint_policy_t bitwise_taint_policy;
        tb_cc_initialise_bitwise_taint_policy(&bitwise_taint_policy);

        tb_options_t te_options;
        te_options.enable_inline = false;
        te_options.enable_taint_off = false;
        te_options.enable_fp = false;

        taint_bunny = tb_cc_init(id, IB_OPT_OPND_COUNT_INFO, &te_options, NULL,
                &bitwise_taint_policy);


    }

    /**
     * We don't check jmps because we can get false positives due to tainted indexes popular with
     * jump tables. This is a difficult limitation to solve as it depends whether the data used as
     * an index is sanitized by the program. If it is, we are okay and a TP will occur.
     * If it is not than a FP will occur. Our analysis does not consider sanitization at the moment.
     *
     * In future work, we will combine with actual CFI techniques where we have some sort of list
     * of safe targets. Coupled with taint analysis, we can address some challenges at the cost of
     * runtime overhead. The Dynamic Bunnies is not intended to be used on deployment of course, and
     * won't be used to detect live attacks. BUT with this extension, we could investigate limitations
     *  of control flow integrity, PARTICULARLY when dealing JITed code - current CFI
     *  implements suffer with jited code!
     *
     * Keep calm, it's just a prototype.
     */
    cfi_bunny = cfib_init(taint_bunny, handle_hijack_func,
    CFIB_EV_DETECT_CALL | CFIB_EV_DETECT_RET,
    IB_OPT_PC_INFO | IB_OPT_CONC_INFO, NULL);
    cfib_register_hooks(cfi_bunny);

    tb_register_hooks(taint_bunny);

    // Register input tracking!
    ub_ev_env_var_input_init_ctx(got_read_from_env, true,
    UB_EV_ENV_VAR_INPUT_OPT_BARE);

    arg_input_ctx = ub_ev_cl_arg_input_init_ctx(got_read_from_arg, true,
    UB_EV_CL_ARG_INPUT_OPT_BARE);

    fd_input_ctx =
            ub_ev_fd_input_init_ctx(got_read_from_fd, true,
                    UB_EV_FD_INPUT_OPT_LOCAL_SOCKET
                            | UB_EV_FD_INPUT_OPT_SOURCE_INFO
                            | UB_EV_FD_INPUT_OPT_REMOTE_SOCKET
                            | UB_EV_FD_INPUT_OPT_FILE, id);

    dr_register_exit_event(event_exit);
}
