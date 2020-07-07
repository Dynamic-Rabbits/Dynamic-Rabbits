#include "dr_defines.h"
#include "path_bunny.h"

#include "logger/cmp_logger/db_fuzz_cmp_logger.h"
#include "logger/lea_logger/db_fuzz_lea_logger.h"
#include "logger/lea_logger/db_fuzz_lea_spill.h"

void *taint_bunny;
void *path_bunny;

extern FILE *cmp_log_file;
extern FILE *lea_log_file;

void *fd_input_ctx;

void *lea_logger;

static void event_exit() {

    db_fuzz_lea_live_regs_destroy();

    ub_ev_fd_input_destroy_ctx(fd_input_ctx);

    pb_exit(path_bunny);

    tb_raw_exit(taint_bunny);
    taint_bunny = NULL;

    tb_raw_destroy_tree_taint_policy();

    ib_unregister_instrum_tool(lea_logger);

    /* Close out files. */
    fclose(cmp_log_file);
    fclose(lea_log_file);

    ib_exit();
    drmgr_exit();
}

static void got_read(ub_fd_input_data_t *input_data) {

    if (input_data->type == UB_FD_FILE) {

        ub_input_buf_t *input_buf = (ub_input_buf_t *) ub_list_get_ith_value(
                input_data->buf_list, 0);

        if (strstr(input_data->source_info.file_info.base_name, ".so") == NULL) {

            byte *array = (byte *) input_buf->buf;
            int index = (int) input_data->offset;

            for (uintptr_t addr = (uintptr_t) input_buf->buf;
                    addr < (uintptr_t) (input_buf->buf + input_buf->size);
                    addr++) {

                tb_taint_mem(taint_bunny, addr, tb_raw_tree_get_label(index));
                index++;
            }
        }
    }
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    ib_init(NULL);

    /* Open the logs */
    cmp_log_file = fopen("cmp.out", "w+");
    lea_log_file = fopen("lea.out", "w+");

    db_fuzz_lea_live_regs_init();

    /* Initialise taint bunny */
    tb_raw_taint_policy_t tb_policy;
    tb_raw_initialise_tree_taint_policy(&tb_policy);
    taint_bunny = tb_raw_init_default(id, &tb_policy);

    path_bunny_funcs_t pb_funcs;
    db_fuzz_init_pb_callbacks(&pb_funcs);
    /**
     * DB_FUZZ is a replacement to VUzzers Taint Engine. VUzzer only considers CMP
     * instructions. We do the same.
     */
    path_bunny = pb_init(taint_bunny, &pb_funcs, PB_EV_CMP, taint_bunny,
    IB_OPT_PC_INFO | IB_OPT_CONC_INFO);
    pb_register_hooks(path_bunny);

    lea_logger = ib_register_instrum_tool();
    db_fuzz_register_lea_checks(lea_logger, taint_bunny);

    tb_register_hooks(taint_bunny);

    /* We could use droptions for handling args.
     * We assume that the first and second args relate to filename.
     *
     * Keep calm, it's just a prototype.
     */
    DR_ASSERT(strcmp("-filename", argv[1]) == 0);

    fd_input_ctx = ub_ev_fd_input_init_ctx(got_read, false,
    UB_EV_FD_INPUT_OPT_SOURCE_INFO | UB_EV_FD_INPUT_OPT_FILE | UB_EV_FD_INPUT_OPT_OFFSET, id);

    char file_path[400];
    strncpy(file_path, argv[2], sizeof(file_path));

    char *base_name = ub_fr_get_basename(file_path);
    ub_ev_fd_input_register_file(fd_input_ctx, base_name);

    dr_register_exit_event(event_exit);
}
