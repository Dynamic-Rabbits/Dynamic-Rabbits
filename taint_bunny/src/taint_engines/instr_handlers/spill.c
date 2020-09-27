/*
 * spill.c
 *
 *      Author: john
 */

#include "spill.h"
#include "../../tb_bunny_private.h"
#include "tb_instruction_handler.h"
#include "drreg.h"

tb_spill_info_t tb_1_scaler = { 1, { DR_REG_XBX }, 0 };
tb_spill_info_t tb_2_scaler = { 2, { DR_REG_XDX, DR_REG_XBX }, 0 };
tb_spill_info_t tb_3_scaler = { 3, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI }, 0 };
tb_spill_info_t tb_4_scaler = { 4, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI }, 0 };
tb_spill_info_t tb_5_scaler = { 5, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI, DR_REG_XCX }, 0 };
tb_spill_info_t tb_6_scaler = { 6, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI, DR_REG_XCX, DR_REG_XBP }, 0 };

tb_spill_info_t tb_3_scaler_2_xmm = { 3, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI },
        2, { DR_REG_XMM0, DR_REG_XMM1 } };
tb_spill_info_t tb_3_scaler_3_xmm = { 3, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI },
        3, { DR_REG_XMM0, DR_REG_XMM1, DR_REG_XMM2 } };
tb_spill_info_t tb_2_scaler_2_xmm = { 2, { DR_REG_XDX, DR_REG_XBX }, 2, {
        DR_REG_XMM0, DR_REG_XMM1 } };
tb_spill_info_t tb_4_scaler_2_xmm = { 4, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI }, 2, { DR_REG_XMM0, DR_REG_XMM1 } };
tb_spill_info_t tb_4_scaler_3_xmm = { 4, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI }, 3, { DR_REG_XMM0, DR_REG_XMM1, DR_REG_XMM2 } };
tb_spill_info_t tb_4_scaler_4_xmm = { 4, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI }, 4, { DR_REG_XMM0, DR_REG_XMM1, DR_REG_XMM2, DR_REG_XMM3 } };
tb_spill_info_t tb_5_scaler_2_xmm = { 5, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI, DR_REG_XCX }, 2, { DR_REG_XMM0, DR_REG_XMM1 } };
tb_spill_info_t tb_5_scaler_4_xmm = { 5, { DR_REG_XDX, DR_REG_XBX, DR_REG_XDI,
DR_REG_XSI, DR_REG_XCX }, 4, { DR_REG_XMM0, DR_REG_XMM1, DR_REG_XMM2,
        DR_REG_XMM3 } };

static void init_reg_ops(int spill_count) {

    drreg_options_t ops;
    ops.struct_size = sizeof(ops);
    ops.conservative = false;
    ops.num_spill_slots = spill_count + 1;

    // We do not want to add more slots to those already made
    // in previous drreg inits, but get the max.
    // TODO Test this, because I am getting some strange behaviour with spillage
    ops.do_not_sum_slots = true;

    // Initialise drreg
    drreg_status_t status = drreg_init(&ops);
    if (status != DRREG_SUCCESS){
        dr_fprintf(STDERR, "The error is %d\n", status);
        DR_ASSERT(false);
    }
}

void tb_live_regs_init() {

    init_reg_ops(6);
}

void tb_live_regs_destroy() {

    drreg_exit();
}

void tb_spill_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void **spilling_data_opaque) {

    tb_raw_instr_hndlr_info_t *raw_instr_hndlr =
            (tb_raw_instr_hndlr_info_t *) user_data;

    tb_spill_info_t **spill_data_ptr = (tb_spill_info_t**) spilling_data_opaque;
    DR_ASSERT(spill_data_ptr != NULL);
    tb_spill_info_t *spill_data = *spill_data_ptr;

    tb_context_t * tb_ctx = raw_instr_hndlr->tb_ctx;

    // Spill registers required by taint policy
    if (tb_ctx->insert_spill_regs)
        tb_ctx->insert_spill_regs(drcontext, ilist, where, tb_ctx->is_inline);

    if (drreg_reserve_aflags(drcontext, ilist, where) != DRREG_SUCCESS)
        DR_ASSERT(false);

    if (tb_ctx->is_inline) {

        tb_spill_info_t *spill_new_data = (tb_spill_info_t*) dr_global_alloc(
                sizeof(tb_spill_info_t));

        spill_new_data->scaler_cnt = spill_data->scaler_cnt;
        spill_new_data->xmm_cnt = spill_data->xmm_cnt;

        // The first 2 registers needs to be able to access lower 8-bit reg.
        drvector_t allowed;
        drreg_init_and_fill_vector(&allowed, true);
        drreg_set_vector_entry(&allowed, DR_REG_ESP, false);
        drreg_set_vector_entry(&allowed, DR_REG_ESI, false);
        drreg_set_vector_entry(&allowed, DR_REG_EBP, false);
        drreg_set_vector_entry(&allowed, DR_REG_EDI, false);

        int max = (spill_data->scaler_cnt > 2) ? 2 : spill_data->scaler_cnt;

        for (int i = 0; i < max; i++) {
            if (drreg_reserve_register(drcontext, ilist, where, &allowed,
                    &(spill_new_data->scaler_regs[i])) != DRREG_SUCCESS) {
                DR_ASSERT(false); /* cannot recover */
            }
        }
        drvector_delete(&allowed);

        for (int i = max; i < spill_data->scaler_cnt; i++) {
            if (drreg_reserve_register(drcontext, ilist, where, NULL,
                    &(spill_new_data->scaler_regs[i])) != DRREG_SUCCESS) {
                DR_ASSERT(false); /* cannot recover */
            }
        }

        for (int i = 0; i < spill_data->xmm_cnt; i++) {
            if (drreg_reserve_xmm_register(drcontext, ilist, where,
            NULL, &(spill_new_data->xmm_regs[i])) != DRREG_SUCCESS) {

                DR_ASSERT(false); /* cannot recover */
            }
        }

        *spill_data_ptr = spill_new_data;

    } else {

        // Scaler
        drvector_t allowed;

        drreg_init_and_fill_vector(&allowed, false);

        for (int i = 0; i < spill_data->scaler_cnt; i++) {

            drreg_set_vector_entry(&allowed, spill_data->scaler_regs[i], true);
        }

        for (int i = 0; i < spill_data->scaler_cnt; i++) {

            reg_id_t reg_check;
            if (drreg_reserve_register(drcontext, ilist, where, &allowed,
                    &reg_check) != DRREG_SUCCESS) {
                DR_ASSERT(false); /* cannot recover */
                drvector_delete(&allowed);
            }
        }

        drvector_delete(&allowed);

        // XMM
        drvector_t xmm_allowed;
        drreg_init_and_fill_xmm_vector(&xmm_allowed, false);

        for (int i = 0; i < spill_data->xmm_cnt; i++) {

            drreg_set_vector_xmm_entry(&xmm_allowed, spill_data->xmm_regs[i],
            true);
        }

        for (int i = 0; i < spill_data->xmm_cnt; i++) {
            reg_id_t reg_check;
            if (drreg_reserve_xmm_register(drcontext, ilist, where,
                    &xmm_allowed, &reg_check) != DRREG_SUCCESS) {

                DR_ASSERT(false); /* cannot recover */
                drvector_delete(&xmm_allowed);
            }
        }

        drvector_delete(&xmm_allowed);
    }
}

void tb_restore_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void *spilling_data_opaque) {

    tb_raw_instr_hndlr_info_t *raw_instr_hndlr =
            (tb_raw_instr_hndlr_info_t *) user_data;

    tb_spill_info_t *spill_data = (tb_spill_info_t*) spilling_data_opaque;
    DR_ASSERT(spill_data != NULL);

    tb_context_t * tb_ctx = raw_instr_hndlr->tb_ctx;

    for (int i = 0; i < spill_data->xmm_cnt; i++) {
        if (drreg_unreserve_xmm_register(drcontext, ilist, where,
                spill_data->xmm_regs[i]) != DRREG_SUCCESS)
            DR_ASSERT(false);
    }

    for (int i = 0; i < spill_data->scaler_cnt; i++) {
        if (drreg_unreserve_register(drcontext, ilist, where,
                spill_data->scaler_regs[i]) != DRREG_SUCCESS)
            DR_ASSERT(false);
    }

    if (drreg_unreserve_aflags(drcontext, ilist, where) != DRREG_SUCCESS)
        DR_ASSERT(false);

    // Spill registers required by taint policy
    if (tb_ctx->insert_restore_regs)
        tb_ctx->insert_restore_regs(drcontext, ilist, where, tb_ctx->is_inline);

    if (tb_ctx->is_inline)
        dr_global_free(spill_data, sizeof(tb_spill_info_t));
}

