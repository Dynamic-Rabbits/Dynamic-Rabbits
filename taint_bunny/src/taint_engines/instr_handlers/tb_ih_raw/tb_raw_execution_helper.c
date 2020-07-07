/*
 * tb_raw_execution_helper.c
 *
 *      Author: john
 */

#include "tb_raw_execution_helper.h"
#include "../../taint_analysis/taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_array_reg_map_definitions.h"

/**
 * These functions simply load up operand data in registers, and
 * passes them to functions responsible for propagating taint.
 *
 */

void tb_raw_execute_load_opnd_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        ub_opnd_access_t *slot, reg_id_t dst) {

    tb_context_t * tb_ctx = instr_hndlr_info->tb_ctx;

    if (tb_ctx->is_inline) {

        if (slot->comp_field == UB_COMP_1) {

            opnd_t opnd;

            if (slot->opnd_field < UB_NUM_OF_SRC_FIELDS) {
                int index = slot->opnd_field;
                opnd = instr_get_src(app_instr, index);
            }
            else if (slot->opnd_field >= UB_DST_OPND_1
                    && slot->opnd_field < UB_DST_OPND_END) {
                int index = slot->opnd_field - UB_DST_OPND_1;
                opnd = instr_get_dst(app_instr, index);

            } else
                DR_ASSERT(false);

            if (ub_opnd_is_reg(&opnd)) {
                /** In future work, we will remove this instruction and pass
                 * the byte id to our taint handlers. This will not only remove this
                 * instruction but also the lea.
                 *
                 * Nevertheless, this is better than actually loading it from a complost (memory).
                 */
                unsigned int id = ub_get_byte_id(opnd_get_reg(opnd), 0);
                DR_ASSERT(id <= REG_MAX_VAL);

                ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, id,
                        dst);
                return;
            }
        } else {

            /** Special case for lea **/
            DR_ASSERT(instr_get_opcode(app_instr) == OP_lea);

            opnd_t lea_mem = instr_get_src(app_instr, 0);

            if (slot->comp_field == UB_COMP_2) {
                reg_id_t base_reg = opnd_get_base(lea_mem);
                DR_ASSERT(base_reg != DR_REG_NULL);

                unsigned int id = ub_get_byte_id(base_reg, 0);

                DR_ASSERT(id <= REG_MAX_VAL);
                ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, id,
                        dst);
                return;
            }

            if (slot->comp_field == UB_COMP_3) {
                reg_id_t index_reg = opnd_get_index(lea_mem);
                DR_ASSERT(index_reg != DR_REG_NULL);

                unsigned int id = ub_get_byte_id(index_reg, 0);

                DR_ASSERT(id <= REG_MAX_VAL);
                ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, id,
                        dst);
                return;
            }
        }
    }

    ib_insert_get_comp_opnd(drcontext, ilist, where, dst, slot);
}

void tb_raw_execute_cmov(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        tb_spill_info_t *spill_info, tb_raw_check_flg_t flg_check_func,
        instr_t *consider_label, instr_t *done_label) {

    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            done_label);

    opnd_t done_label_opnd = opnd_create_instr(done_label);
    opnd_t consider_label_opnd = opnd_create_instr(consider_label);

    // Load IB thread data
    ib_insert_load_per_thread_data(drcontext, ilist, where,
            spill_info->scaler_regs[3]);

    // Create flag opnd
    opnd_t eflags_opnd = ib_insert_get_flags_opnd_ex(
            spill_info->scaler_regs[3]);

    flg_check_func(drcontext, ilist, where, &eflags_opnd, &consider_label_opnd,
            spill_info->scaler_regs[2]);

    instr_t *instr = INSTR_CREATE_jmp(drcontext, done_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

void tb_raw_execute_cmov_ex(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where,
        tb_spill_info_t *spill_info, tb_raw_check_flg_ex_t flg_check_func,
        instr_t *consider_label, instr_t *done_label) {

    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            done_label);

    opnd_t done_label_opnd = opnd_create_instr(done_label);
    opnd_t consider_label_opnd = opnd_create_instr(consider_label);

    // Load IB thread data
    ib_insert_load_per_thread_data(drcontext, ilist, where,
            spill_info->scaler_regs[3]);

    // Create flag opnd
    opnd_t eflags_opnd = ib_insert_get_flags_opnd_ex(
            spill_info->scaler_regs[3]);

    flg_check_func(drcontext, ilist, where, &eflags_opnd, &consider_label_opnd,
            reg_32_to_8(spill_info->scaler_regs[0]),
            reg_32_to_8(spill_info->scaler_regs[1]));

    instr_t *instr = INSTR_CREATE_jmp(drcontext, done_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

static void tb_raw_execute_cmpxchg_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, size_t size, reg_id_t data_reg, reg_id_t src1_reg,
        reg_id_t src2_reg, ub_opnd_access_t *comp_access_slot1,
        ub_opnd_access_t *comp_access_slot2) {

    ib_insert_get_comp_conc_ex(drcontext, ilist, where, data_reg, src1_reg,
            size, comp_access_slot1, 0);

    ib_insert_get_comp_conc_ex(drcontext, ilist, where, data_reg, src2_reg,
            size, comp_access_slot2, 0);

    // CMP conc values
    opnd_t opnd1 = opnd_create_reg(src1_reg);
    opnd_t opnd2 = opnd_create_reg(src2_reg);
    instr_t *instr = INSTR_CREATE_cmp(drcontext, opnd1, opnd2);
    instrlist_meta_preinsert(ilist, where, instr);
}

void tb_raw_execute_cmpxchg_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        size_t size, void *drcontext, instrlist_t *ilist, instr_t *where,
        tb_spill_info_t *spill_info, instr_t *consider_label,
        instr_t *no_consider_label, instr_t *done_label) {

    DR_ASSERT(spill_info->scaler_cnt > 3);

    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            done_label);

    opnd_t consider_label_opnd = opnd_create_instr(consider_label);
    opnd_t no_consider_label_opnd = opnd_create_instr(no_consider_label);

    // Load IB thread data
    ib_insert_load_per_thread_data(drcontext, ilist, where,
            spill_info->scaler_regs[3]);

    ub_opnd_access_t src2_slot;
    src2_slot.opnd_field = UB_SRC_OPND_2;
    src2_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t xax_slot;
    xax_slot.opnd_field = UB_DST_OPND_2;
    xax_slot.comp_field = UB_COMP_1;

    tb_raw_execute_cmpxchg_check(drcontext, ilist, where, size,
            spill_info->scaler_regs[3], spill_info->scaler_regs[0],
            spill_info->scaler_regs[1], &src2_slot, &xax_slot);

    // If equal jump to consider branch
    instr_t *instr = INSTR_CREATE_jcc(drcontext, OP_je, consider_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instr = INSTR_CREATE_jmp(drcontext, no_consider_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

