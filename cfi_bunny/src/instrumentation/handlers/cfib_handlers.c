/*
 * pb_handlers.c
 *
 *      Author: john
 */

#include "cfib_handlers.h"

#include "taint_bunny.h"
#include "drreg.h"
#include "string.h"

#include "../../cfib_private.h"

/***************************************************************
 * General Helpers
 */

static void cfib_spill_2_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t *scaler, reg_id_t *vector) {

    if (drreg_reserve_register(drcontext, ilist, where, NULL, scaler)
            != DRREG_SUCCESS
            || drreg_reserve_xmm_register(drcontext, ilist, where, NULL, vector)
                    != DRREG_SUCCESS
            || drreg_reserve_aflags(drcontext, ilist, where)!= DRREG_SUCCESS)

        DR_ASSERT(false);
}

static void cfib_spill_3_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t *scaler, reg_id_t *vector, reg_id_t *scaler2) {

    if (drreg_reserve_register(drcontext, ilist, where, NULL, scaler)
            != DRREG_SUCCESS
            || drreg_reserve_register(drcontext, ilist, where, NULL, scaler2)
                    != DRREG_SUCCESS
            || drreg_reserve_xmm_register(drcontext, ilist, where, NULL, vector)
                    != DRREG_SUCCESS
            || drreg_reserve_aflags(drcontext, ilist, where)!= DRREG_SUCCESS)

        DR_ASSERT(false);
}

static void cfib_restore_2_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t scaler, reg_id_t vector) {

    drreg_unreserve_aflags(drcontext, ilist, where);
    drreg_unreserve_xmm_register(drcontext, ilist, where, vector);
    drreg_unreserve_register(drcontext, ilist, where, scaler);
}

static void cfib_restore_3_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        reg_id_t scaler, reg_id_t vector, reg_id_t scaler2) {

    drreg_unreserve_aflags(drcontext, ilist, where);
    drreg_unreserve_xmm_register(drcontext, ilist, where, vector);
    drreg_unreserve_register(drcontext, ilist, where, scaler);
    drreg_unreserve_register(drcontext, ilist, where, scaler2);
}


static void cfib_handle_call_attack(cfib_context_t *cfib_ctx) {

    cfib_attack_type_t type = CFIB_CALL_ATTACK;

    ub_opnd_access_t corrupt_slot;
    corrupt_slot.opnd_field = UB_SRC_OPND_1;
    corrupt_slot.comp_field = UB_COMP_1;

    cfib_ctx->detection_func(type, &corrupt_slot, cfib_ctx->user_data);
}

static void cfib_handle_ret_attack(cfib_context_t *cfib_ctx) {

    cfib_attack_type_t type = CFIB_RET_ATTACK;

    ub_opnd_access_t corrupt_slot;
    corrupt_slot.opnd_field = UB_SRC_OPND_2;
    corrupt_slot.comp_field = UB_COMP_1;

    cfib_ctx->detection_func(type, &corrupt_slot, cfib_ctx->user_data);
}

static void cfib_handle_ret_immed_attack(cfib_context_t *cfib_ctx) {

    cfib_attack_type_t type = CFIB_RET_ATTACK;

    ub_opnd_access_t corrupt_slot;
    corrupt_slot.opnd_field = UB_SRC_OPND_3;
    corrupt_slot.comp_field = UB_COMP_1;

    cfib_ctx->detection_func(type, &corrupt_slot, cfib_ctx->user_data);
}


static void cfib_handle_jmp_attack(cfib_context_t *cfib_ctx) {

    cfib_attack_type_t type = CFIB_JMP_ATTACK;

    ub_opnd_access_t corrupt_slot;
    corrupt_slot.opnd_field = UB_SRC_OPND_1;
    corrupt_slot.comp_field = UB_COMP_1;

    cfib_ctx->detection_func(type, &corrupt_slot, cfib_ctx->user_data);
}

static void cfib_taint_check_reg(cfib_context_t *cfib_ctx, void *drcontext,
        size_t size, instrlist_t *ilist, instr_t *where,
        unsigned int byte_reg_id, void (*cfib_func)(cfib_context_t *cfib_ctx)) {

    reg_id_t map_reg;
    reg_id_t vector_reg;

    cfib_spill_2_regs(drcontext, ilist, where, &map_reg, &vector_reg);

    instr_t *done_label = INSTR_CREATE_label(drcontext);
    instr_t *reg_tainted_label = INSTR_CREATE_label(drcontext);

    tb_insert_is_some_reg_tainted(cfib_ctx->taint_bunny, drcontext, ilist, where,
            map_reg, byte_reg_id, vector_reg, map_reg, size,
            reg_tainted_label);

    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, reg_tainted_label);

    dr_insert_clean_call(drcontext, ilist, where, cfib_func, false, 1,
    OPND_CREATE_INTPTR(cfib_ctx));

    instrlist_meta_preinsert(ilist, where, done_label);

    cfib_restore_2_regs(drcontext, ilist, where, map_reg, vector_reg);
}

static void cfib_taint_check_mem(cfib_context_t *cfib_ctx, void *drcontext,
        size_t size, instrlist_t *ilist, instr_t *where,
        ub_opnd_access_t *comp_access_slot,
        void (*cfib_func)(cfib_context_t *cfib_ctx)) {

    reg_id_t addr_reg;
    reg_id_t vector_reg;
    reg_id_t scratch_reg;

    cfib_spill_3_regs(drcontext, ilist, where, &addr_reg, &vector_reg, &scratch_reg);

    instr_t *done_label = INSTR_CREATE_label(drcontext);
    instr_t *reg_tainted_label = INSTR_CREATE_label(drcontext);

    ib_insert_get_comp_opnd(drcontext, ilist, where, addr_reg,
            comp_access_slot);

    tb_insert_is_some_mem_tainted(cfib_ctx->taint_bunny, drcontext, ilist, where,
            addr_reg, vector_reg, scratch_reg, size, reg_tainted_label);

    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, reg_tainted_label);

    dr_insert_clean_call(drcontext, ilist, where, cfib_func, false, 1,
    OPND_CREATE_INTPTR(cfib_ctx));

    instrlist_meta_preinsert(ilist, where, done_label);

    cfib_restore_3_regs(drcontext, ilist, where, addr_reg, vector_reg, scratch_reg);
}

/***************************************************************
 * Handlers
 */

void cfib_instrument_call_reg_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    DR_ASSERT(instr_is_call(app_instr));

    cfib_context_t *cfib_ctx = (cfib_context_t *) user_data;
    reg_id_t reg = opnd_get_reg(instr_get_src(app_instr, 0));
    unsigned int reg_byte_id = ub_get_byte_id(reg, 0);

    cfib_taint_check_reg(cfib_ctx, drcontext, sizeof(void *), ilist, where,
            reg_byte_id, cfib_handle_call_attack);
}

void cfib_instrument_call_mem_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    DR_ASSERT(instr_is_call(app_instr));

    cfib_context_t *cfib_ctx = (cfib_context_t *) user_data;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;

    cfib_taint_check_mem(cfib_ctx, drcontext, sizeof(void *), ilist, where,
            &src_slot, cfib_handle_call_attack);
}

void cfib_instrument_jmp_reg_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    cfib_context_t *cfib_ctx = (cfib_context_t *) user_data;
    reg_id_t reg = opnd_get_reg(instr_get_src(app_instr, 0));
    unsigned int reg_byte_id = ub_get_byte_id(reg, 0);

    cfib_taint_check_reg(cfib_ctx, drcontext, sizeof(void *), ilist, where,
            reg_byte_id, cfib_handle_jmp_attack);
}

void cfib_instrument_ret_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    cfib_context_t *cfib_ctx = (cfib_context_t *) user_data;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_2;
    src_slot.comp_field = UB_COMP_1;

    cfib_taint_check_mem(cfib_ctx, drcontext, sizeof(void *), ilist, where,
            &src_slot, cfib_handle_ret_attack);
}

void cfib_instrument_ret_immed_checker(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    /* For ret immed, the addr is the 3rd opnd not 2nd like normal ret. */

    cfib_context_t *cfib_ctx = (cfib_context_t *) user_data;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_3;
    src_slot.comp_field = UB_COMP_1;

    cfib_taint_check_mem(cfib_ctx, drcontext, sizeof(void *), ilist, where,
            &src_slot, cfib_handle_ret_immed_attack);
}
