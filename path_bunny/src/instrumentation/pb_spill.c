/*
 * pb_spill.c
 *
 *      Author: john
 */

#include "pb_spill.h"

#include "drreg.h"
#include "string.h"

void pb_live_regs_init() {

    drreg_options_t ops;
    ops.struct_size = sizeof(ops);
    ops.conservative = false;
    ops.num_spill_slots = 5;

    // We do not want to add more slots to those already made
    // in previous drreg inits, but get the max.
    // TODO Test this, because I am getting some strange behaviour with spillage
    ops.do_not_sum_slots = true;

    // Initialise drreg
    if (drreg_init(&ops) != DRREG_SUCCESS)
        DR_ASSERT(false);
}

void pb_live_regs_destroy() {

    drreg_exit();
}

void pb_spill_three_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void **spilling_data_opaque) {

    drvector_t allowed;
    drreg_init_and_fill_vector(&allowed, false);
    drreg_set_vector_entry(&allowed, pb_reg1, true);
    drreg_set_vector_entry(&allowed, pb_reg2, true);

    reg_id_t reg;
    if (drreg_reserve_register(drcontext, ilist, where, &allowed, &(reg))
            != DRREG_SUCCESS
            || drreg_reserve_register(drcontext, ilist, where, &allowed, &(reg))
                    != DRREG_SUCCESS
            || drreg_reserve_aflags(drcontext, ilist, where) != DRREG_SUCCESS) {

        DR_ASSERT(false); /* cannot recover */
    }

    drvector_delete(&allowed);

    drreg_init_and_fill_xmm_vector(&allowed, false);
    drreg_set_vector_xmm_entry(&allowed, pb_reg3, true);

    if (drreg_reserve_xmm_register(drcontext, ilist, where, &allowed, &(reg))
            != DRREG_SUCCESS) {

        DR_ASSERT(false); /* cannot recover */
    }

    drvector_delete(&allowed);

    *spilling_data_opaque = NULL;
}

void pb_restore_three_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void *spilling_data_opaque) {

    if (drreg_unreserve_register(drcontext, ilist, where, pb_reg1)
            != DRREG_SUCCESS)
        DR_ASSERT(false);

    if (drreg_unreserve_register(drcontext, ilist, where, pb_reg2)
            != DRREG_SUCCESS)
        DR_ASSERT(false);

    if (drreg_unreserve_xmm_register(drcontext, ilist, where, pb_reg3)
            != DRREG_SUCCESS)
        DR_ASSERT(false);

    drreg_unreserve_aflags(drcontext, ilist, where);
}

void pb_spill_four_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void **spilling_data_opaque) {

    pb_spill_three_regs(drcontext, ilist, where, user_data,
            spilling_data_opaque);

    drvector_t allowed;
    drreg_init_and_fill_vector(&allowed, false);
    drreg_set_vector_entry(&allowed, pb_reg4_xcx, true);

    reg_id_t reg;
    if (drreg_reserve_register(drcontext, ilist, where, &allowed, &(reg))
            != DRREG_SUCCESS) {

        DR_ASSERT(false); /* cannot recover */
    }

    drvector_delete(&allowed);
    *spilling_data_opaque = NULL;
}

void pb_restore_four_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void *spilling_data_opaque) {

    if (drreg_unreserve_register(drcontext, ilist, where, pb_reg4_xcx)
            != DRREG_SUCCESS)
        DR_ASSERT(false);

    pb_restore_three_regs(drcontext, ilist, where, user_data,
            spilling_data_opaque);
}
