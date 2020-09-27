/**
 *  @file instrumentation_bunny.h
 *  @brief The instrumentation Bunny is useful for instrumenting instructions. Multiple
 *  bunnies can hook instr, where the instrumentation bunny will ensure minimal context
 *  switching.
 *  @author John F.X. Galea
 */

#ifndef PATH_BUNNY_H_
#define PATH_BUNNY_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"

#include "taint_bunny.h"

#include <stdint.h>

typedef unsigned int PB_EV_OPT_t;
// No additional information
#define PB_EV_ERROR 0
#define PB_EV_TEST 1
#define PB_EV_CMP 2
#define PB_EV_PSIMD 4
#define PB_EV_REP_CMP 8

typedef void (*pb_handle_cmp_func_t)(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data);

typedef struct {

    pb_handle_cmp_func_t pb_cmp_tainted_reg_1_mem_1_func;
    pb_handle_cmp_func_t pb_cmp_reg_1_tainted_mem_1_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_1_tainted_mem_1_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_2_mem_2_func;
    pb_handle_cmp_func_t pb_cmp_reg_2_tainted_mem_2_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_2_tainted_mem_2_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_4_mem_4_func;
    pb_handle_cmp_func_t pb_cmp_reg_4_tainted_mem_4_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_4_tainted_mem_4_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_8_mem_8_func;
    pb_handle_cmp_func_t pb_cmp_reg_8_tainted_mem_8_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_8_tainted_mem_8_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_16_mem_16_func;
    pb_handle_cmp_func_t pb_cmp_reg_16_tainted_mem_16_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_16_tainted_mem_16_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_1_reg_1_func;
    pb_handle_cmp_func_t pb_cmp_mem_1_tainted_reg_1_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_1_tainted_reg_1_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_2_reg_2_func;
    pb_handle_cmp_func_t pb_cmp_mem_2_tainted_reg_2_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_2_tainted_reg_2_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_4_reg_4_func;
    pb_handle_cmp_func_t pb_cmp_mem_4_tainted_reg_4_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_4_tainted_reg_4_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_8_reg_8_func;
    pb_handle_cmp_func_t pb_cmp_mem_8_tainted_reg_8_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_8_tainted_reg_8_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_16_reg_16_func;
    pb_handle_cmp_func_t pb_cmp_mem_16_tainted_reg_16_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_16_tainted_reg_16_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_1_reg_1_func;
    pb_handle_cmp_func_t pb_cmp_reg_1_tainted_reg_1_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_1_tainted_reg_1_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_2_reg_2_func;
    pb_handle_cmp_func_t pb_cmp_reg_2_tainted_reg_2_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_2_tainted_reg_2_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_4_reg_4_func;
    pb_handle_cmp_func_t pb_cmp_reg_4_tainted_reg_4_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_4_tainted_reg_4_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_8_reg_8_func;
    pb_handle_cmp_func_t pb_cmp_reg_8_tainted_reg_8_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_8_tainted_reg_8_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_16_reg_16_func;
    pb_handle_cmp_func_t pb_cmp_reg_16_tainted_reg_16_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_16_tainted_reg_16_func;

    pb_handle_cmp_func_t pb_cmp_tainted_reg_1_imm_1_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_2_imm_2_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_4_imm_4_func;
    pb_handle_cmp_func_t pb_cmp_tainted_reg_8_imm_8_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_1_imm_1_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_2_imm_2_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_4_imm_4_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_8_imm_8_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_1_mem_1_func;
    pb_handle_cmp_func_t pb_cmp_mem_1_tainted_mem_1_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_1_tainted_mem_1_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_2_mem_2_func;
    pb_handle_cmp_func_t pb_cmp_mem_2_tainted_mem_2_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_2_tainted_mem_2_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_4_mem_4_func;
    pb_handle_cmp_func_t pb_cmp_mem_4_tainted_mem_4_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_4_tainted_mem_4_func;

    pb_handle_cmp_func_t pb_cmp_tainted_mem_8_mem_8_func;
    pb_handle_cmp_func_t pb_cmp_mem_8_tainted_mem_8_func;
    pb_handle_cmp_func_t pb_cmp_tainted_mem_8_tainted_mem_8_func;

} path_bunny_funcs_t;

DR_EXPORT void *pb_init(void *taint_bunny, path_bunny_funcs_t *funcs,
        PB_EV_OPT_t pb_opts, void *user_data, IB_INSTRUM_OPT ib_options);

DR_EXPORT void pb_exit(void *path_bunny);

DR_EXPORT void pb_register_hooks(void *path_ctx);

#endif /* SLICER_BUNNY_H_ */
