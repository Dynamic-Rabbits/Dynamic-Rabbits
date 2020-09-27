/*
 * tb_cc_instr_hndlr_helper.c
 *
 *      Author: john
 */

#include "tb_cc_execution.h"

//#define TB_PRINT_UNSUP 1

/***********************************************************************
 * SRC SRCDST
 */

void tb_cc_execute_src_srcdst_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_srcdst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst,
                uintptr_t src)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    uintptr_t src_opnd = ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t srcdst_slot;
    srcdst_slot.opnd_field = UB_DST_OPND_1;
    srcdst_slot.comp_field = UB_COMP_1;
    uintptr_t srcdst_opnd = ib_get_comp_opnd(drcontext, &srcdst_slot);

    execute_src_srcdst_handler(instr_hndlr_info, srcdst_opnd, src_opnd);
}

/***********************************************************************
 * SRCDST
 */

void tb_cc_execute_srcdst_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_srcdst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t srcdst_slot;
    srcdst_slot.opnd_field = UB_DST_OPND_1;
    srcdst_slot.comp_field = UB_COMP_1;
    uintptr_t srcdst_opnd = ib_get_comp_opnd(drcontext, &srcdst_slot);

    execute_srcdst_handler(instr_hndlr_info, srcdst_opnd);
}

/***************************************************************************************************
 * SRC SRC DST DST
 */

void tb_cc_execute_src_srcdst_dst_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_src_dst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t srcdst2, uintptr_t src1)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t srcdst_slot;
    srcdst_slot.opnd_field = UB_SRC_OPND_2;
    srcdst_slot.comp_field = UB_COMP_1;
    unsigned int srcdst_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &srcdst_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_src_src_dst_handler(instr_hndlr_info, dst_opnd, srcdst_opnd,
            src_opnd);
}

/***************************************************************************************************
 * SRC SRC DST
 */

void tb_cc_execute_src_src_dst_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_src_dst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t src1, uintptr_t src2)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t src2_slot;
    src2_slot.opnd_field = UB_SRC_OPND_2;
    src2_slot.comp_field = UB_COMP_1;
    unsigned int src2_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src2_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_src_src_dst_handler(instr_hndlr_info, dst_opnd, src_opnd,
            src2_opnd);
}

/***************************************************************************************************
 * SRC SRCDST SRCDST
 */

void tb_cc_execute_src_srcdst_srcdst_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_srcdst_srcdst_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t srcdst,
                uintptr_t srcdst2, uintptr_t src1)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    uintptr_t src_opnd = ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t srcdst_slot;
    srcdst_slot.opnd_field = UB_DST_OPND_1;
    srcdst_slot.comp_field = UB_COMP_1;
    uintptr_t src2_opnd = ib_get_comp_opnd(drcontext, &srcdst_slot);

    ub_opnd_access_t srcdst2_slot;
    srcdst2_slot.opnd_field = UB_DST_OPND_2;
    srcdst2_slot.comp_field = UB_COMP_1;
    uintptr_t src3_opnd = ib_get_comp_opnd(drcontext, &srcdst2_slot);

    execute_src_srcdst_srcdst_handler(instr_hndlr_info, src3_opnd, src2_opnd,
            src_opnd);
}

/***************************************************************************************************
 * SRC DST
 */

void tb_cc_execute_src_dst_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_mov_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_mov_handler(instr_hndlr_info, dst_opnd, src_opnd);
}

void tb_cc_execute_pop_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_pop_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_2;
    src_slot.comp_field = UB_COMP_1;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_pop_handler(instr_hndlr_info, dst_opnd, src_opnd);
}

void tb_cc_execute_push_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_push_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_2;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_push_handler(instr_hndlr_info, dst_opnd, src_opnd);
}

/***************************************************************************************************
 * LEA instructions
 */

void tb_cc_execute_lea_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_lea_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst, uintptr_t src1, uintptr_t src2)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_2;
    uintptr_t src_opnd = ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t src_slot2;
    src_slot2.opnd_field = UB_SRC_OPND_1;
    src_slot2.comp_field = UB_COMP_3;
    uintptr_t src_opnd2 = ib_get_comp_opnd(drcontext, &src_slot2);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_lea_handler(instr_hndlr_info, dst_opnd, src_opnd, src_opnd2);
}

void tb_cc_execute_lea_base_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_lea_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst, uintptr_t src1)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_2;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_lea_handler(instr_hndlr_info, dst_opnd, src_opnd);
}

void tb_cc_execute_lea_index_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_lea_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst, uintptr_t src1)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_3;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_lea_handler(instr_hndlr_info, dst_opnd, src_opnd);
}

/***************************************************************************************************
 * REP
 */

bool tb_cc_dir_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_direction(ib_get_flags(drcontext));
}

static void tb_cc_execute_rep(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size, bool inc_dst, bool inc_src,
        void (*execute_mov_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id)) {

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    ub_opnd_access_t length_slot;
    length_slot.opnd_field = UB_SRC_OPND_4;
    length_slot.comp_field = UB_COMP_1;
    size_t *length = (size_t *) ib_get_comp_conc(drcontext, &length_slot);

    // If direction flag is set, increment turns into decrement
    if (tb_cc_dir_check_flag())
        inc_size = inc_size * -1;

    for (size_t i = 0; i < *length; i++) {

        execute_mov_handler(instr_hndlr_info, dst_opnd, src_opnd);

        if (inc_dst)
            dst_opnd += inc_size;

        if (inc_src)
            src_opnd += inc_size;
    }
}

static void tb_cc_execute_rep_mem_reg(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, size_t inc_size,
        bool inc_dst, bool inc_src,
        void (*execute_mov_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id)) {

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    unsigned int src_opnd = (unsigned int) ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    ub_opnd_access_t length_slot;
    length_slot.opnd_field = UB_SRC_OPND_3;
    length_slot.comp_field = UB_COMP_1;
    size_t *length = (size_t *) ib_get_comp_conc(drcontext, &length_slot);

    // If direction flag is set, increment turns into decrement
    if (tb_cc_dir_check_flag())
        inc_size = inc_size * -1;

    for (size_t i = 0; i < *length; i++) {

        execute_mov_handler(instr_hndlr_info, dst_opnd, src_opnd);

        if (inc_dst)
            dst_opnd += inc_size;

        if (inc_src)
            src_opnd += inc_size;
    }
}

void tb_cc_execute_rep_movs_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size,
        void (*execute_rep_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id)) {

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    tb_cc_execute_rep(instr_hndlr_info, inc_size, true, true,
            execute_rep_handler);
}

void tb_cc_execute_rep_stos_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        size_t inc_size,
        void (*execute_rep_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t dst_addr, unsigned int src_reg_id)) {

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    tb_cc_execute_rep_mem_reg(instr_hndlr_info, inc_size, true, false,
            execute_rep_handler);
}

/***************************************************************************************************
 * Conditional
 */

bool tb_cc_cmovb_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_b(ib_get_flags(drcontext));
}

bool tb_cc_cmovnb_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_nb(ib_get_flags(drcontext));
}

bool tb_cc_cmovbe_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_be(ib_get_flags(drcontext));
}

bool tb_cc_cmovnbe_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_nbe(ib_get_flags(drcontext));
}

bool tb_cc_cmovo_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_o(ib_get_flags(drcontext));
}

bool tb_cc_cmovno_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_no(ib_get_flags(drcontext));
}

bool tb_cc_cmovp_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_p(ib_get_flags(drcontext));
}

bool tb_cc_cmovnp_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_np(ib_get_flags(drcontext));
}

bool tb_cc_cmovs_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_s(ib_get_flags(drcontext));
}

bool tb_cc_cmovns_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_ns(ib_get_flags(drcontext));
}

bool tb_cc_cmove_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_e(ib_get_flags(drcontext));
}
bool tb_cc_cmovne_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_ne(ib_get_flags(drcontext));
}

bool tb_cc_cmovg_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_g(ib_get_flags(drcontext));
}

bool tb_cc_cmovge_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_ge(ib_get_flags(drcontext));
}

bool tb_cc_cmovl_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_l(ib_get_flags(drcontext));
}

bool tb_cc_cmovle_check_flag() {

    void *drcontext = dr_get_current_drcontext();
    return ub_eflag_check_le(ib_get_flags(drcontext));
}

/***************************************************************************************************
 * EXECUTE LEAVE
 */

void tb_cc_execute_leave_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_src_dst_reg_reg_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t src),
        void (*execute_src_dst_reg_mem_handler)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst1,
                uintptr_t src)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t mem_slot;
    mem_slot.opnd_field = UB_SRC_OPND_3;
    mem_slot.comp_field = UB_COMP_1;
    uintptr_t mem_opnd = ib_get_comp_opnd(drcontext, &mem_slot);

    ub_opnd_access_t sp_slot;
    sp_slot.opnd_field = UB_DST_OPND_1;
    sp_slot.comp_field = UB_COMP_1;
    uintptr_t sp_opnd = ib_get_comp_opnd(drcontext, &sp_slot);

    ub_opnd_access_t bp_slot;
    bp_slot.opnd_field = UB_DST_OPND_2;
    bp_slot.comp_field = UB_COMP_1;
    uintptr_t bp_opnd = ib_get_comp_opnd(drcontext, &bp_slot);

    execute_src_dst_reg_reg_handler(instr_hndlr_info, sp_opnd, bp_opnd);
    execute_src_dst_reg_mem_handler(instr_hndlr_info, bp_opnd, mem_opnd);
}

/***************************************************************************************************
 * EXECUTE XCHG
 */

void tb_cc_execute_xchg_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_xchg_handler)(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
                uintptr_t srcdst1, uintptr_t srcdst2)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_2;
    src_slot.comp_field = UB_COMP_1;
    uintptr_t src_opnd = ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_xchg_handler(instr_hndlr_info, dst_opnd, src_opnd);
}

void tb_cc_execute_cmpxchg_helper(tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        size_t size,
        void (*execute_mov_handler_not_taken)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_addr,
                uintptr_t src_reg_id),
        void (*execute_mov_handler_taken)(
                tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_addr,
                uintptr_t src_reg_id)) {

    void *drcontext = dr_get_current_drcontext();

    if (!tb_is_analysis_on(instr_hndlr_info->tb_ctx,
            dr_get_current_drcontext()))
        return;

    ub_opnd_access_t src_slot;
    src_slot.opnd_field = UB_SRC_OPND_1;
    src_slot.comp_field = UB_COMP_1;
    uintptr_t src_opnd = ib_get_comp_opnd(drcontext, &src_slot);

    ub_opnd_access_t src2_slot;
    src2_slot.opnd_field = UB_SRC_OPND_2;
    src2_slot.comp_field = UB_COMP_1;
    uintptr_t src2_opnd = ib_get_comp_opnd(drcontext, &src2_slot);
    byte *src2_conc_val = ib_get_comp_conc(drcontext, &src2_slot);

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_2;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t eax_val_opnd = ib_get_comp_opnd(drcontext, &dst_slot);
    byte *dst_conc_val = ib_get_comp_conc(drcontext, &dst_slot);

    if (memcmp(src2_conc_val, dst_conc_val, size) == 0) {
        execute_mov_handler_taken(instr_hndlr_info, src2_opnd, src_opnd);
    } else
        execute_mov_handler_not_taken(instr_hndlr_info, eax_val_opnd,
                src2_opnd);
}

/***************************************************************************************************
 * Unsupported
 */

//#define TB_PRINT_UNSUP 1

#ifdef TB_PRINT_UNSUP
static void tb_cc_print_instruction() {

    void *drcontext = dr_get_current_drcontext();

    app_pc pc = ib_get_pc(drcontext);

    instr_t instr;
    instr_init(drcontext, &instr);
    decode(drcontext, pc, &instr);

    char buff[500];
    instr_disassemble_to_buffer(drcontext, &instr, buff, 500);

    dr_fprintf(STDERR, "UNSUPPORTED INSTRUCTION %s and opc: %d\n", buff,
            instr_get_opcode(&instr));
    dr_fprintf(STDERR, "-----------------------------------------\n");


    if (instr_is_floating(&instr)) {
        instr_free(drcontext, &instr);
        return;
    }

    int sources = instr_num_srcs(&instr);
    int destinations = instr_num_dsts(&instr);

    for (int i = 0; i < sources; i++) {

        opnd_t src = instr_get_src(&instr, i);

        dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
        dr_get_mcontext(drcontext, &mcontext);

        if (opnd_is_memory_reference(src)) {

            dr_fprintf(STDERR, "\t Source: %p\n",
                    opnd_compute_address(src, &mcontext));

            byte *buf = NULL;
            size_t read_size;
            dr_safe_read((void *) opnd_compute_address(src, &mcontext), 4, &buf,
                    &read_size);

            opnd_size_t size_opnd = opnd_get_size(src);

            dr_fprintf(STDERR, "\t\t The value is : %p %u\n", buf,
                    opnd_size_in_bytes(size_opnd));

        } else if (ub_opnd_is_reg(&src)) {
            dr_fprintf(STDERR, "\t Source: %p\n",
                    ub_get_byte_id(opnd_get_reg(src), 0));

            if (reg_is_xmm(opnd_get_reg(src))
                    || reg_is_gpr(opnd_get_reg(src))) {
                void *buf[200];
                reg_get_value_ex(opnd_get_reg(src), &mcontext, (byte*) buf);

                opnd_size_t size_opnd = opnd_get_size(src);

                dr_fprintf(STDERR, "\t\t The value is : %p %u\n", *buf,
                        opnd_size_in_bytes(size_opnd));

            }
        }
    }

    for (int i = 0; i < destinations; i++) {

        opnd_t dst = instr_get_dst(&instr, i);

        dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
        dr_get_mcontext(drcontext, &mcontext);

        if (opnd_is_memory_reference(dst)) {
            dr_fprintf(STDERR, "\t Dest: %p\n",
                    opnd_compute_address(dst, &mcontext));

            byte *buf = NULL;
            size_t read_size;
            dr_safe_read((void *) opnd_compute_address(dst, &mcontext), 4, &buf,
                    &read_size);
            dr_fprintf(STDERR, "\t\t The value is : %p\n", buf);

            opnd_size_t size_opnd = opnd_get_size(dst);
            dr_fprintf(STDERR, "\t\t The value is : %p %u\n", buf,
                    opnd_size_in_bytes(size_opnd));

        } else if (ub_opnd_is_reg(&dst)) {
            dr_fprintf(STDERR, "\t Dest: %p\n",
                    ub_get_byte_id(opnd_get_reg(dst), 0));

            if (reg_is_xmm(opnd_get_reg(dst))
                    || reg_is_gpr(opnd_get_reg(dst))) {
                void *buf[200];
                reg_get_value_ex(opnd_get_reg(dst), &mcontext, (byte*) &buf);

                opnd_size_t size_opnd = opnd_get_size(dst);
                dr_fprintf(STDERR, "\t\t The value is : %p %u\n", *buf,
                        opnd_size_in_bytes(size_opnd));
            }

        }
    }

    instr_free(drcontext, &instr);
}
#endif

/**
 * TODO: EVENTUALLY this function should phase out
 * when we support all instructions #the_dream.
 */
void tb_cc_execute_unsup_instr(void *tb_ctx_opaque,
        void (*execute_untaint_reg_handler)(void *tb_ctx_opaque,
                uintptr_t dst_reg),
        void (*execute_untaint_mem_handler)(void *tb_ctx_opaque,
                uintptr_t dst_addr)) {

    void *drcontext = dr_get_current_drcontext();

#ifdef TB_PRINT_UNSUP
    tb_cc_print_instruction();
#endif
    size_t size = ib_get_num_dsts(drcontext);

    for (size_t i = 0; i < size; i++) {

        ub_opnd_access_t slot;
        slot.opnd_field = UB_DST_OPND_1 + i;
        slot.comp_field = UB_COMP_1;

        size_t opnd_size = ib_get_comp_size(drcontext, &slot);
        uintptr_t opnd = ib_get_comp_opnd(drcontext, &slot);
        loc_t type = ib_get_comp_type(drcontext, &slot);

        for (size_t j = 0; j < opnd_size; j++) {

            if (type == UB_REG_TYPE) {
                execute_untaint_reg_handler(tb_ctx_opaque,
                        (unsigned int) j + opnd);

            } else if (type == UB_MEM_TYPE) {

                execute_untaint_mem_handler(tb_ctx_opaque,
                        (unsigned int) j + opnd);
            }
        }
    }

}

/*******************************************************************************
 * Untaint
 */

void tb_cc_execute_untaint_first_n_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, int n,
        void (*execute_untaint_handler)(void *tb_ctx_opaque, uintptr_t dst_addr)) {

    void *drcontext = dr_get_current_drcontext();

    for (int i = 0; i < n; i++) {

        ub_opnd_access_t dst_slot;
        dst_slot.opnd_field = UB_DST_OPND_1 + i;
        dst_slot.comp_field = UB_COMP_1;
        uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

        execute_untaint_handler(instr_hndlr_info->tb_ctx, dst_opnd);
    }
}

void tb_cc_execute_untaint_sub_byte_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info, size_t index,
        size_t sub_start, size_t sub_end,
        void (*execute_untaint_handler)(void *tb_ctx_opaque, uintptr_t dst_addr)) {

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_1 + index;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    for (size_t i = sub_start; i < sub_end; i++) {

        execute_untaint_handler(instr_hndlr_info->tb_ctx, dst_opnd + i);
    }
}

void tb_cc_execute_push_immed_untaint_helper(
        tb_cc_instr_hndlr_info_t *instr_hndlr_info,
        void (*execute_untaint_handler)(void *tb_ctx_opaque, uintptr_t dst_addr)) {

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t dst_slot;
    dst_slot.opnd_field = UB_DST_OPND_2;
    dst_slot.comp_field = UB_COMP_1;
    uintptr_t dst_opnd = ib_get_comp_opnd(drcontext, &dst_slot);

    execute_untaint_handler(instr_hndlr_info->tb_ctx, dst_opnd);
}
