#include "ub_symbol_access.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drsyms.h"
#include <string.h>
#include <stdint.h>

#define MAX_SIZE 300

void ub_sa_init() {

    drsym_init(0);
}

void ub_sa_exit() {

    drsym_exit();
}

static bool ub_sa_get_symb_info(drsym_info_t* info, app_pc pc) {

    //Get module
    module_data_t *data = dr_lookup_module(pc);

    drsym_error_t res = drsym_lookup_address(data->full_path, pc - data->start,
            info, DRSYM_DEFAULT_FLAGS);

    dr_free_module_data(data);

    if (res != DRSYM_SUCCESS)
        return false;

    return true;
}

void ub_sa_print_symb_info(app_pc pc) {

    drsym_info_t info;
    memset(&info, 0, sizeof(drsym_info_t));

    info.struct_size = sizeof(drsym_info_t);

    info.name_size = MAX_SIZE;
    char name[MAX_SIZE];
    info.name = name;

    info.file_size = MAX_SIZE;
    char file[MAX_SIZE];
    info.file = file;

    bool succ = ub_sa_get_symb_info(&info, pc);

    if (succ) {
        dr_fprintf(STDERR, "Function name: %s\n", info.name);
        dr_fprintf(STDERR, "Line: %llu\n", info.line);
        dr_fprintf(STDERR, "File: %s\n", info.file);
    }
}

