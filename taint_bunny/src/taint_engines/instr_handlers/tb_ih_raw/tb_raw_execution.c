/*
 * tb_raw_execution.c
 *
 *      Author: john
 */

#include "tb_raw_execution.h"
#include "tb_raw_execution_helper.h"

/***********************************************************************
 * SRC SRCDST
 */

void tb_raw_execute_src_srcdst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_srcdst_func_t src_srcdst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    src_srcdst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

/***********************************************************************
 * SRCDST
 */

void tb_raw_execute_srcdst_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_srcdst_func_t srcdst_func) {

    DR_ASSERT(instr_hndlr_info->tb_ctx);

    instr_t* exit_label = INSTR_CREATE_label(drcontext);

    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[0]);

    srcdst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

/***************************************************************************************************
 * SRC SRC DST DST
 */

void tb_raw_execute_src_srcdst_dst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_srcdst_dst_func_t src_srcdst_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t srcdst_slot;
    srcdst_slot.opnd_field = UB_SRC_OPND_2;
    srcdst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &srcdst_slot, spill_info->scaler_regs[1]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[2]);

    src_srcdst_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[2], spill_info->scaler_regs[1],
            spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

/***************************************************************************************************
 * SRC SRC DST
 */

void tb_raw_execute_src_src_dst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_src_dst_func_t src_src_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t src_slot2;
    src_slot2.opnd_field = UB_SRC_OPND_2;
    src_slot2.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot2, spill_info->scaler_regs[1]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[2]);

    src_src_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[2], spill_info->scaler_regs[0],
            spill_info->scaler_regs[1], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

/***************************************************************************************************
 * SRC SRCDST SRCDST
 */

void tb_raw_execute_src_srcdst_srcdst_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_srcdst_srcdst_func_t src_srcdst_srcdst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    ub_opnd_access_t dst_slot2;
    dst_slot2.opnd_field = UB_DST_OPND_2;
    dst_slot2.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot2, spill_info->scaler_regs[2]);

    src_srcdst_srcdst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[2], spill_info->scaler_regs[1],
            spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);

}

/***************************************************************************************************
 * SRC DST
 */

void tb_raw_execute_src_dst_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    src_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

void tb_raw_execute_pop_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_2;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    src_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

void tb_raw_execute_push_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_2;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    src_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

/***************************************************************************************************
 * LEA instructions
 */

void tb_raw_execute_lea_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_src_dst_func_t src_src_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ib_insert_load_per_thread_data(drcontext, ilist, where,
            spill_info->scaler_regs[3]);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_2;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t src_slot2;
    src_slot2.opnd_field = UB_SRC_OPND_1;
    src_slot2.comp_field = UB_COMP_3;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot2, spill_info->scaler_regs[1]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[2]);

    src_src_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[2], spill_info->scaler_regs[1],
            spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

void tb_raw_execute_lea_base_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ib_insert_load_per_thread_data(drcontext, ilist, where,
            spill_info->scaler_regs[2]);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_2;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    src_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

void tb_raw_execute_lea_index_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ib_insert_load_per_thread_data(drcontext, ilist, where,
            spill_info->scaler_regs[2]);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_3;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    src_dst_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

/***************************************************************************************************
 * REP
 */

// TODO MOVE REP code to tb_raw_execution_helper.c
static void tb_raw_execute_rep(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size, bool inc_dst, bool inc_src,
        ub_opnd_field_t cnt_field, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_ex_t src_dst_func) {

    DR_ASSERT(spill_info->scaler_cnt > 4);

    instr_t* done_label = INSTR_CREATE_label(drcontext);

    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            done_label);

    ib_insert_load_per_thread_data(drcontext, ilist, where,
            spill_info->scaler_regs[3]);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    ub_opnd_access_t length_slot;
    length_slot.opnd_field = cnt_field;
    length_slot.comp_field = UB_COMP_1;
    ib_insert_get_comp_conc_ex(drcontext, ilist, where,
            spill_info->scaler_regs[3], spill_info->scaler_regs[4], 4,
            &length_slot, 0);

    instr_t* decrementing_index_entral_label = INSTR_CREATE_label(drcontext);
    instr_t* decrementing_index_label = INSTR_CREATE_label(drcontext);
    instr_t* incrementing_index_label = INSTR_CREATE_label(drcontext);

    opnd_t inc_label_opnd = opnd_create_instr(incrementing_index_label);
    opnd_t dec_label_entral_opnd = opnd_create_instr(
            decrementing_index_entral_label);
    opnd_t dec_label_opnd = opnd_create_instr(decrementing_index_label);

    opnd_t done_label_opnd = opnd_create_instr(done_label);

    // Check if length is zero, and if so, jump to done label
    ub_instrum_check_null_true_case(drcontext, ilist, where,
            spill_info->scaler_regs[4], done_label);

    opnd_t eflags_opnd = ib_insert_get_flags_opnd_ex(
            spill_info->scaler_regs[3]);

    ub_eflag_insert_check_direction(drcontext, ilist, where, &eflags_opnd,
            &dec_label_entral_opnd, spill_info->scaler_regs[2]);

// -------------------------  INCREMENT SECTION --------------------

    // Do translation!
    src_dst_func(instr_hndlr_info, true, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    if (inc_dst) {
        ub_instrum_add_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[1], inc_size * sizeof(void *));
    }

    if (inc_src) {
        ub_instrum_add_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[0], inc_size * sizeof(void *));
    }

    ub_instrum_dec_reg(drcontext, ilist, where, spill_info->scaler_regs[4]);

    instr_t* instr = INSTR_CREATE_jcc(drcontext, OP_jz, done_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instrlist_meta_preinsert(ilist, where, incrementing_index_label);

    src_dst_func(instr_hndlr_info, false, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    if (inc_dst)
        ub_instrum_add_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[1], inc_size * sizeof(void *));

    if (inc_src)
        ub_instrum_add_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[0], inc_size * sizeof(void *));

    ub_instrum_dec_reg(drcontext, ilist, where, spill_info->scaler_regs[4]);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, done_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    // fall through. Lets jump to the false!

    instr = INSTR_CREATE_jmp(drcontext, inc_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    // -------------------------  DECREMENT SECTION --------------------

    instrlist_meta_preinsert(ilist, where, decrementing_index_entral_label);

    src_dst_func(instr_hndlr_info, true, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    if (inc_dst)
        ub_instrum_sub_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[1], inc_size * sizeof(void *));

    if (inc_src)
        ub_instrum_sub_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[0], inc_size * sizeof(void *));

    ub_instrum_dec_reg(drcontext, ilist, where, spill_info->scaler_regs[4]);

    instr = INSTR_CREATE_jcc(drcontext, OP_jz, done_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instrlist_meta_preinsert(ilist, where, decrementing_index_label);

    src_dst_func(instr_hndlr_info, false, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    if (inc_dst)
        ub_instrum_sub_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[1], inc_size * sizeof(void *));

    if (inc_src)
        ub_instrum_sub_reg_immed(drcontext, ilist, where,
                spill_info->scaler_regs[0], inc_size * sizeof(void *));

    ub_instrum_dec_reg(drcontext, ilist, where, spill_info->scaler_regs[4]);

    instr = INSTR_CREATE_jcc(drcontext, OP_jnz, dec_label_opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    instrlist_meta_preinsert(ilist, where, done_label);
}

void tb_raw_execute_rep_movs(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_ex_t src_dst_func) {

    tb_raw_execute_rep(instr_hndlr_info, inc_size, true, true,
            UB_SRC_OPND_4, drcontext, ilist, where, app_instr, spill_info,
            src_dst_func);
}

void tb_raw_execute_rep_stos(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size, void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_ex_t src_dst_func) {

    tb_raw_execute_rep(instr_hndlr_info, inc_size, true, false,
            UB_SRC_OPND_3, drcontext, ilist, where, app_instr, spill_info,
            src_dst_func);
}

/***************************************************************************************************
 * EXECUTE LEAVE
 */

void tb_raw_execute_leave_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t src_dst_func_reg_reg,
        tb_raw_byt_handle_src_dst_func_t src_dst_func_reg_mem) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t srcdst_slot;
    srcdst_slot.opnd_field = UB_DST_OPND_2;
    srcdst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &srcdst_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    src_dst_func_reg_reg(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_3;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &srcdst_slot, spill_info->scaler_regs[1]);

    src_dst_func_reg_mem(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

/***************************************************************************************************
 * EXECUTE XCHG
 */

void tb_raw_execute_xchg_helper(tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_xchg_func_t xchg_func_reg_reg) {

    instr_t* exit_label = INSTR_CREATE_label(drcontext);
    tb_insert_is_analysis_on(drcontext, ilist, where, instr_hndlr_info->tb_ctx,
            exit_label);

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_2;
    src_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[1]);

    xchg_func_reg_reg(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);

    instrlist_meta_preinsert(ilist, where, exit_label);
}

void tb_raw_execute_cmpxchg_consider_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t taken_mov_func) {

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t src2_slot;
    src2_slot.opnd_field = UB_SRC_OPND_2;
    src2_slot.comp_field = UB_COMP_1;

    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src_slot, spill_info->scaler_regs[0]);

    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src2_slot, spill_info->scaler_regs[1]);

    taken_mov_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);
}

void tb_raw_execute_cmpxchg_no_consider_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info,
        void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_src_dst_func_t not_taken_mov_func) {

    ub_opnd_access_t src2_slot;
    src2_slot.opnd_field = UB_SRC_OPND_2;
    src2_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t xax_slot;
    xax_slot.opnd_field = UB_DST_OPND_2;
    xax_slot.comp_field = UB_COMP_1;

    // Load the opnd of src
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &src2_slot, spill_info->scaler_regs[0]);

    // Load the opnd of dst
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &xax_slot, spill_info->scaler_regs[1]);

    not_taken_mov_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[1], spill_info->scaler_regs[0], spill_info);
}

/*******************************************************************************
 * Untaint
 */

void tb_raw_execute_untaint_first_n_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, int n, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_untaint_func_t untaint_func) {

    for (int i = 0; i < n; i++) {

        ub_opnd_access_t dst_slot;
        dst_slot.opnd_field = UB_DST_OPND_1 + i;
        dst_slot.comp_field = UB_COMP_1;

        tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist,
                where, app_instr, &dst_slot, spill_info->scaler_regs[0]);

        untaint_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
                spill_info->scaler_regs[0], spill_info);
    }
}

void tb_raw_execute_untaint_sub_byte_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t index,
        size_t sub_start, size_t sub_end, void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, tb_spill_info_t *spill_info,
        tb_raw_byte_handle_untaint_reg_ex_func_t untaint_func_ex) {

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1 + index;
    dst_slot.comp_field = UB_COMP_1;

    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[0]);

    untaint_func_ex(instr_hndlr_info, sub_start, sub_end, drcontext, ilist,
            where, app_instr, spill_info->scaler_regs[0], spill_info);
}

void tb_raw_execute_push_immed_untaint_helper(
        tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr,
        tb_spill_info_t *spill_info,
        tb_raw_byt_handle_untaint_func_t untaint_func) {

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_2;
    dst_slot.comp_field = UB_COMP_1;
    tb_raw_execute_load_opnd_helper(instr_hndlr_info, drcontext, ilist, where,
            app_instr, &dst_slot, spill_info->scaler_regs[0]);

    untaint_func(instr_hndlr_info, drcontext, ilist, where, app_instr,
            spill_info->scaler_regs[0], spill_info);
}

