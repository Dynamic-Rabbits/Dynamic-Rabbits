/*
 * pb_handlers.c
 *
 *      Author: john
 */

#include "pb_handlers.h"
#include "taint_bunny.h"
#include "drreg.h"
#include "../../pb_private.h"
#include "../pb_spill.h"
#include "string.h"

/***************************************************************
 * General Helpers
 */

static void pb_check_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t test_reg,
        reg_id_t test_reg2, pb_handle_cmp_func_t t_n_func,
        pb_handle_cmp_func_t n_t_func, pb_handle_cmp_func_t t_t_func) {

    instr_t *done_label = INSTR_CREATE_label(drcontext);
    instr_t *t_t_label;
    instr_t *t_n_label;
    instr_t *n_t_label;

    opnd_t opnd;
    opnd_t opnd2;
    instr_t *instr;

    if (t_t_func) {

        t_t_label = INSTR_CREATE_label(drcontext);

        opnd = opnd_create_reg(test_reg);
        opnd2 = opnd_create_reg(test_reg2);
        instr = INSTR_CREATE_test(drcontext, opnd, opnd2);
        instrlist_meta_preinsert(ilist, where, instr);

        instr = INSTR_CREATE_jcc(drcontext, OP_jnz,
                opnd_create_instr(t_t_label));
        instrlist_meta_preinsert(ilist, where, instr);
    }

    if (t_n_func || n_t_func) {

        opnd = opnd_create_reg(test_reg);
        opnd2 = opnd_create_reg(test_reg2);
        instr = INSTR_CREATE_cmp(drcontext, opnd, opnd2);
        instrlist_meta_preinsert(ilist, where, instr);

        if (t_n_func) {

            t_n_label = INSTR_CREATE_label(drcontext);

            instr = INSTR_CREATE_jcc(drcontext, OP_jg,
                    opnd_create_instr(t_n_label));
            instrlist_meta_preinsert(ilist, where, instr);
        }

        if (n_t_func) {

            n_t_label = INSTR_CREATE_label(drcontext);

            instr = INSTR_CREATE_jcc(drcontext, OP_jl,
                    opnd_create_instr(n_t_label));
            instrlist_meta_preinsert(ilist, where, instr);
        }
    }

    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    if (t_t_label) {
        instrlist_meta_preinsert(ilist, where, t_t_label);
        t_t_func(drcontext, ilist, where, pb_context->user_data);
        ub_instrum_direct_jmp(drcontext, ilist, where, done_label);
    }

    if (t_n_func) {
        instrlist_meta_preinsert(ilist, where, t_n_label);
        t_n_func(drcontext, ilist, where, pb_context->user_data);
        ub_instrum_direct_jmp(drcontext, ilist, where, done_label);
    }

    if (n_t_label) {

        instrlist_meta_preinsert(ilist, where, n_t_label);
        n_t_func(drcontext, ilist, where, pb_context->user_data);
    }

    instrlist_meta_preinsert(ilist, where, done_label);

}

static void pb_check_reg_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where,
        ub_opnd_access_t *comp_access_slot, size_t size,
        instr_t *is_tainted_label, reg_id_t scatch_reg, reg_id_t scatch_reg2,
        reg_id_t scratch_vector_reg) {

    DR_ASSERT(reg_is_xmm(scratch_vector_reg));
    DR_ASSERT(reg_is_gpr(scatch_reg));
    DR_ASSERT(reg_is_gpr(scatch_reg2));

    ib_insert_get_comp_opnd(drcontext, ilist, where, scatch_reg,
            comp_access_slot);

    tb_insert_is_some_reg_tainted_via_reg(pb_context->taint_bunny, drcontext,
            ilist, where, scatch_reg, scatch_reg2, scratch_vector_reg, size,
            is_tainted_label);
}

static void pb_check_mem_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where,
        ub_opnd_access_t *comp_access_slot, size_t size,
        instr_t *is_tainted_label, reg_id_t scatch_reg, reg_id_t scatch_reg2,
        reg_id_t scratch_vector_reg) {

    DR_ASSERT(reg_is_xmm(scratch_vector_reg));
    DR_ASSERT(reg_is_gpr(scatch_reg));
    DR_ASSERT(reg_is_gpr(scatch_reg2));

    ib_insert_get_comp_opnd(drcontext, ilist, where, scatch_reg,
            comp_access_slot);

    tb_insert_is_some_mem_tainted(pb_context->taint_bunny, drcontext, ilist,
            where, scatch_reg, scratch_vector_reg, scatch_reg2, size,
            is_tainted_label);
}

static void instrument_double_check_helper(pb_context_t *pb_context,
        void *drcontext, instrlist_t *ilist, instr_t *where, size_t size,
        bool is_src_reg, bool is_src2_reg, pb_handle_cmp_func_t tr_r_func,
        pb_handle_cmp_func_t r_tr_func, pb_handle_cmp_func_t tr_tr_func) {

    instr_t *done_label = INSTR_CREATE_label(drcontext);
    instr_t *next_label = INSTR_CREATE_label(drcontext);

    instr_t *is_tainted_label = INSTR_CREATE_label(drcontext);
    instr_t *is_tainted_label2 = INSTR_CREATE_label(drcontext);

    opnd_t immed_set = opnd_create_immed_uint(1, OPSZ_1);

    ub_instrum_clear_reg(drcontext, ilist, where, DR_REG_XCX);

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    if (is_src_reg)
        pb_check_reg_helper(pb_context, drcontext, ilist, where,
                &comp_access_slot, size, is_tainted_label, pb_reg1,
                pb_reg2, pb_reg3);
    else
        pb_check_mem_helper(pb_context, drcontext, ilist, where,
                &comp_access_slot, size, is_tainted_label, pb_reg1,
                pb_reg2, pb_reg3);

    // Skip the call!
    ub_instrum_direct_jmp(drcontext, ilist, where, next_label);

    instrlist_meta_preinsert(ilist, where, is_tainted_label);

    opnd_t opnd = opnd_create_reg(DR_REG_CL);
    instr_t *instr = INSTR_CREATE_mov_imm(drcontext, opnd, immed_set);
    instrlist_meta_preinsert(ilist, where, instr);

    instrlist_meta_preinsert(ilist, where, next_label);

    comp_access_slot.opnd_field = UB_SRC_OPND_2;
    comp_access_slot.comp_field = UB_COMP_1;

    if (is_src2_reg)
        pb_check_reg_helper(pb_context, drcontext, ilist, where,
                &comp_access_slot, size, is_tainted_label2, pb_reg1,
                pb_reg2, pb_reg3);
    else
        pb_check_mem_helper(pb_context, drcontext, ilist, where,
                &comp_access_slot, size, is_tainted_label2, pb_reg1,
                pb_reg2, pb_reg3);

    // Skip the call!
    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, is_tainted_label2);

    opnd = opnd_create_reg(DR_REG_CH);
    instr = INSTR_CREATE_mov_imm(drcontext, opnd, immed_set);
    instrlist_meta_preinsert(ilist, where, instr);

    instrlist_meta_preinsert(ilist, where, done_label);

    pb_check_helper(pb_context, drcontext, ilist, where, DR_REG_CL, DR_REG_CH,
            tr_r_func, r_tr_func, tr_tr_func);
}

/**
 * TODO: The following code is not optimised!
 * It is possible to improve by removing jmps done by the tb!
 */
/**
 * REG VS IMM
 */

static void instrument_r_i_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where, size_t size,
        pb_handle_cmp_func_t func) {

    instr_t *done_label = INSTR_CREATE_label(drcontext);
    instr_t *reg_tainted_label = INSTR_CREATE_label(drcontext);

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    pb_check_reg_helper(pb_context, drcontext, ilist, where, &comp_access_slot,
            size, reg_tainted_label, pb_reg1, pb_reg2, pb_reg3);

    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, reg_tainted_label);

    func(drcontext, ilist, where, pb_context->user_data);

    instrlist_meta_preinsert(ilist, where, done_label);
}

void pb_instrument_sreg_1_simm_1_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_i_helper(pb_context, drcontext, ilist, where, 1,
            pb_context->funcs.pb_cmp_tainted_reg_1_imm_1_func);
}

void pb_instrument_sreg_2_simm_2_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_i_helper(pb_context, drcontext, ilist, where, 2,
            pb_context->funcs.pb_cmp_tainted_reg_2_imm_2_func);
}

void pb_instrument_sreg_4_simm_4_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_i_helper(pb_context, drcontext, ilist, where, 4,
            pb_context->funcs.pb_cmp_tainted_reg_4_imm_4_func);
}

void pb_instrument_sreg_8_simm_8_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_i_helper(pb_context, drcontext, ilist, where, 8,
            pb_context->funcs.pb_cmp_tainted_reg_8_imm_8_func);
}

/**
 * MEM VS IMM
 */

static void instrument_mem_i_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where, size_t size,
        pb_handle_cmp_func_t func) {

    instr_t *done_label = INSTR_CREATE_label(drcontext);
    instr_t *reg_tainted_label = INSTR_CREATE_label(drcontext);

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    pb_check_mem_helper(pb_context, drcontext, ilist, where, &comp_access_slot,
            size, reg_tainted_label, pb_reg1, pb_reg2, pb_reg3);

    // Skip the call!
    ub_instrum_direct_jmp(drcontext, ilist, where, done_label);

    instrlist_meta_preinsert(ilist, where, reg_tainted_label);

    func(drcontext, ilist, where, pb_context->user_data);

    instrlist_meta_preinsert(ilist, where, done_label);
}

void pb_instrument_smem_1_simm_1_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_mem_i_helper(pb_context, drcontext, ilist, where, 1,
            pb_context->funcs.pb_cmp_tainted_mem_1_imm_1_func);
}

void pb_instrument_smem_2_simm_2_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_mem_i_helper(pb_context, drcontext, ilist, where, 2,
            pb_context->funcs.pb_cmp_tainted_mem_2_imm_2_func);
}

void pb_instrument_smem_4_simm_4_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_mem_i_helper(pb_context, drcontext, ilist, where, 4,
            pb_context->funcs.pb_cmp_tainted_mem_4_imm_4_func);
}

void pb_instrument_smem_8_simm_8_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_mem_i_helper(pb_context, drcontext, ilist, where, 8,
            pb_context->funcs.pb_cmp_tainted_mem_8_imm_8_func);
}

/**
 * REG VS REG
 */

static void instrument_r_r_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where, size_t size,
        pb_handle_cmp_func_t tr_r_func, pb_handle_cmp_func_t r_tr_func,
        pb_handle_cmp_func_t tr_tr_func) {

    instrument_double_check_helper(pb_context, drcontext, ilist, where, size,
    true, true, tr_r_func, r_tr_func, tr_tr_func);
}

void pb_instrument_sreg_1_sreg_1_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_r_helper(pb_context, drcontext, ilist, where, 1,
            pb_context->funcs.pb_cmp_tainted_reg_1_reg_1_func,
            pb_context->funcs.pb_cmp_reg_1_tainted_reg_1_func,
            pb_context->funcs.pb_cmp_tainted_reg_1_tainted_reg_1_func);
}

void pb_instrument_sreg_2_sreg_2_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_r_helper(pb_context, drcontext, ilist, where, 2,
            pb_context->funcs.pb_cmp_tainted_reg_2_reg_2_func,
            pb_context->funcs.pb_cmp_reg_2_tainted_reg_2_func,
            pb_context->funcs.pb_cmp_tainted_reg_2_tainted_reg_2_func);
}

void pb_instrument_sreg_4_sreg_4_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_r_helper(pb_context, drcontext, ilist, where, 4,
            pb_context->funcs.pb_cmp_tainted_reg_4_reg_4_func,
            pb_context->funcs.pb_cmp_reg_4_tainted_reg_4_func,
            pb_context->funcs.pb_cmp_tainted_reg_4_tainted_reg_4_func);
}

void pb_instrument_sreg_8_sreg_8_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_r_helper(pb_context, drcontext, ilist, where, 8,
            pb_context->funcs.pb_cmp_tainted_reg_8_reg_8_func,
            pb_context->funcs.pb_cmp_reg_8_tainted_reg_8_func,
            pb_context->funcs.pb_cmp_tainted_reg_8_tainted_reg_8_func);
}

void pb_instrument_sreg_16_sreg_16_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_r_helper(pb_context, drcontext, ilist, where, 16,
            pb_context->funcs.pb_cmp_tainted_reg_16_reg_16_func,
            pb_context->funcs.pb_cmp_reg_16_tainted_reg_16_func,
            pb_context->funcs.pb_cmp_tainted_reg_16_tainted_reg_16_func);
}

/**
 * REP CMP
 */

void pb_instrument_rep_cmp_smem_1_smem_1_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

void pb_instrument_rep_cmp_smem_2_smem_2_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

void pb_instrument_rep_cmp_smem_4_smem_4_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

void pb_instrument_rep_cmp_smem_8_smem_8_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

/**
 * REP SCAS
 */

void pb_instrument_rep_scas_smem_1_smem_1_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

void pb_instrument_rep_scas_smem_2_smem_2_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

void pb_instrument_rep_scas_smem_4_smem_4_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

void pb_instrument_rep_scas_smem_8_smem_8_check(void *drcontext,
        instrlist_t *ilist, instr_t *where, instr_t *app_instr, void *user_data,
        void *spill_data) {

}

/**
 * MEM VS MEM
 */

static void instrument_m_m_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where, size_t size,
        pb_handle_cmp_func_t tm_m_func, pb_handle_cmp_func_t m_tm_func,
        pb_handle_cmp_func_t tm_tm_func) {

    instrument_double_check_helper(pb_context, drcontext, ilist, where, size,
    false, false, tm_m_func, m_tm_func, tm_tm_func);
}

void pb_instrument_smem_1_smem_1_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_m_helper(pb_context, drcontext, ilist, where, 1,
            pb_context->funcs.pb_cmp_tainted_mem_1_mem_1_func,
            pb_context->funcs.pb_cmp_mem_1_tainted_mem_1_func,
            pb_context->funcs.pb_cmp_tainted_mem_1_tainted_mem_1_func);
}

void pb_instrument_smem_2_smem_2_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_m_helper(pb_context, drcontext, ilist, where, 2,
            pb_context->funcs.pb_cmp_tainted_mem_2_mem_2_func,
            pb_context->funcs.pb_cmp_mem_2_tainted_mem_2_func,
            pb_context->funcs.pb_cmp_tainted_mem_2_tainted_mem_2_func);
}

void pb_instrument_smem_4_smem_4_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_m_helper(pb_context, drcontext, ilist, where, 4,
            pb_context->funcs.pb_cmp_tainted_mem_4_mem_4_func,
            pb_context->funcs.pb_cmp_mem_4_tainted_mem_4_func,
            pb_context->funcs.pb_cmp_tainted_mem_4_tainted_mem_4_func);
}

void pb_instrument_smem_8_smem_8_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_m_helper(pb_context, drcontext, ilist, where, 8,
            pb_context->funcs.pb_cmp_tainted_mem_8_mem_8_func,
            pb_context->funcs.pb_cmp_mem_8_tainted_mem_8_func,
            pb_context->funcs.pb_cmp_tainted_mem_8_tainted_mem_8_func);
}

/**
 * MEM VS REG
 */

static void instrument_m_r_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where, size_t size,
        pb_handle_cmp_func_t tm_r_func, pb_handle_cmp_func_t m_tr_func,
        pb_handle_cmp_func_t tm_tr_func) {

    instrument_double_check_helper(pb_context, drcontext, ilist, where, size,
    false, true, tm_r_func, m_tr_func, tm_tr_func);
}

void pb_instrument_smem_1_sreg_1_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_r_helper(pb_context, drcontext, ilist, where, 1,
            pb_context->funcs.pb_cmp_tainted_mem_1_reg_1_func,
            pb_context->funcs.pb_cmp_mem_1_tainted_reg_1_func,
            pb_context->funcs.pb_cmp_tainted_mem_1_tainted_reg_1_func);
}

void pb_instrument_smem_2_sreg_2_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_r_helper(pb_context, drcontext, ilist, where, 2,
            pb_context->funcs.pb_cmp_tainted_mem_2_reg_2_func,
            pb_context->funcs.pb_cmp_mem_2_tainted_reg_2_func,
            pb_context->funcs.pb_cmp_tainted_mem_2_tainted_reg_2_func);
}

void pb_instrument_smem_4_sreg_4_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_r_helper(pb_context, drcontext, ilist, where, 4,
            pb_context->funcs.pb_cmp_tainted_mem_4_reg_4_func,
            pb_context->funcs.pb_cmp_mem_4_tainted_reg_4_func,
            pb_context->funcs.pb_cmp_tainted_mem_4_tainted_reg_4_func);
}

void pb_instrument_smem_8_sreg_8_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_r_helper(pb_context, drcontext, ilist, where, 8,
            pb_context->funcs.pb_cmp_tainted_mem_8_reg_8_func,
            pb_context->funcs.pb_cmp_mem_8_tainted_reg_8_func,
            pb_context->funcs.pb_cmp_tainted_mem_8_tainted_reg_8_func);
}

void pb_instrument_smem_16_sreg_16_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_m_r_helper(pb_context, drcontext, ilist, where, 16,
            pb_context->funcs.pb_cmp_tainted_mem_16_reg_16_func,
            pb_context->funcs.pb_cmp_mem_16_tainted_reg_16_func,
            pb_context->funcs.pb_cmp_tainted_mem_16_tainted_reg_16_func);
}

/**
 * REG VS MEM
 */

static void instrument_r_m_helper(pb_context_t *pb_context, void *drcontext,
        instrlist_t *ilist, instr_t *where, size_t size,
        pb_handle_cmp_func_t tr_m_func, pb_handle_cmp_func_t r_tm_func,
        pb_handle_cmp_func_t tr_tm_func) {

    instrument_double_check_helper(pb_context, drcontext, ilist, where, size,
    true, false, tr_m_func, r_tm_func, tr_tm_func);
}

void pb_instrument_sreg_1_smem_1_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_m_helper(pb_context, drcontext, ilist, where, 1,
            pb_context->funcs.pb_cmp_tainted_reg_1_mem_1_func,
            pb_context->funcs.pb_cmp_reg_1_tainted_mem_1_func,
            pb_context->funcs.pb_cmp_tainted_reg_1_tainted_mem_1_func);
}

void pb_instrument_sreg_2_smem_2_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_m_helper(pb_context, drcontext, ilist, where, 2,
            pb_context->funcs.pb_cmp_tainted_reg_2_mem_2_func,
            pb_context->funcs.pb_cmp_reg_2_tainted_mem_2_func,
            pb_context->funcs.pb_cmp_tainted_reg_2_tainted_mem_2_func);
}

void pb_instrument_sreg_4_smem_4_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_m_helper(pb_context, drcontext, ilist, where, 4,
            pb_context->funcs.pb_cmp_tainted_reg_4_mem_4_func,
            pb_context->funcs.pb_cmp_reg_4_tainted_mem_4_func,
            pb_context->funcs.pb_cmp_tainted_reg_4_tainted_mem_4_func);

}

void pb_instrument_sreg_8_smem_8_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_m_helper(pb_context, drcontext, ilist, where, 8,
            pb_context->funcs.pb_cmp_tainted_reg_8_mem_8_func,
            pb_context->funcs.pb_cmp_reg_8_tainted_mem_8_func,
            pb_context->funcs.pb_cmp_tainted_reg_8_tainted_mem_8_func);
}

void pb_instrument_sreg_16_smem_16_check(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t *app_instr, void *user_data, void *spill_data) {

    pb_context_t *pb_context = (pb_context_t *) user_data;

    instrument_r_m_helper(pb_context, drcontext, ilist, where, 16,
            pb_context->funcs.pb_cmp_tainted_reg_16_mem_16_func,
            pb_context->funcs.pb_cmp_reg_16_tainted_mem_16_func,
            pb_context->funcs.pb_cmp_tainted_reg_16_tainted_mem_16_func);
}
