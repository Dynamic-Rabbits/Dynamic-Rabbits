/*
 * ub_misc_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_misc_instr.h"

void ub_is_leave_dreg_4_dreg_4_sreg_4_smem_4_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr = INSTR_CREATE_leave(drcontext);
    DR_ASSERT(ub_is_leave_dreg_4_dreg_4_sreg_4_smem_4_instr(instr));

    instr_destroy(drcontext, instr);

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_leave_dreg_4_dreg_4_sreg_4_smem_4_instr_test();
}
