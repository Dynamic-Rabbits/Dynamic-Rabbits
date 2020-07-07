/*
 * tb_raw_taint_policy.h
 *
 *  Created on: 19 Jul 2018
 *      Author: john
 */

#ifndef TAINT_POLICIES_TB_RAW_TAINT_POLICY_H_
#define TAINT_POLICIES_TB_RAW_TAINT_POLICY_H_

#include <stddef.h>
#include "utility_bunny.h"
#include "instrumentation_bunny.h"
#include "tb_cc_taint_policy.h"

typedef void (*tb_raw_insert_meet_func_t)(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc app_instr, reg_id_t meet_reg,
        opnd_t *label_lowest_opnd, opnd_t *src1_opnd, reg_id_t scratch_reg);
typedef void (*tb_simd_insert_meet_func_t)(void *drcontext, instrlist_t *ilist,
        instr_t *where, app_pc app_instr, reg_id_t meet_reg, opnd_t *label_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

typedef void (*tb_raw_insert_propogate_1dst_1src_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc app_instr, reg_id_t dst_reg,
        opnd_t *src1_opnd, reg_id_t scratch_reg);
typedef void (*tb_raw_insert_propogate_1dst_2src_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc app_instr, reg_id_t dst_reg,
        opnd_t *src1_opnd, opnd_t *src2_opnd, reg_id_t scratch_reg);

typedef void (*tb_simd_insert_propogate_1dst_1src_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc app_instr,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_reg);
typedef void (*tb_simd_insert_propogate_1dst_2src_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc app_instr,
        reg_id_t dst_vectorised_reg, opnd_t *src1_vectorised_opnd,
        opnd_t *src2_vectorised_opnd, reg_id_t scratch_vectorised_reg,
        reg_id_t scratch_reg);

typedef void (*tb_raw_insert_new_ref_tl_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t taint_label,
        reg_id_t scratch_reg);
typedef void (*tb_raw_insert_delete_ref_tl_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t taint_label,
        reg_id_t scratch_reg);

typedef void (*tb_simd_insert_new_ref_tl_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t taint_label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);
typedef void (*tb_simd_insert_delete_ref_tl_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t taint_label_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

typedef void (*tb_raw_insert_untaint_mem_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t old_reg,
        reg_id_t scratch_reg);
typedef void (*tb_raw_insert_untaint_reg_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t old_reg,
        reg_id_t scratch_reg);

typedef void (*tb_simd_insert_untaint_mem_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t old_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);
typedef void (*tb_simd_insert_untaint_reg_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t old_vectorised_reg,
        reg_id_t scratch_vectorised_reg, reg_id_t scratch_scaler_reg);

/**
 * Spill and restore functions.
 *
 * It could be that the taint policy requires more scratch registers for its
 * implementation. When TB is spilling and restoring, these functions are called
 * to enable the user to spill further registers.
 *
 * However, we are limited in the nunmber of registers and the user should take care not to spill
 * a lot (dynamorio will fail with an assertion in this case.
 * Typically, the use of 2 registers is the maximum and then one needs to start
 * spilling to tls!
 *
 * We use this function primarily to spill XAX as some cases specifically needs this
 * register to perform locks (provided by the UB).
 *
 * In future work, I will try to contribute a virtual register component to DR building
 * upon drreg to hopefully facilitate spilling once and for all. This is a difficult task
 * (ping me if youre interested!).
 *
 * Keep calm, it's just a prototype.
 *
 */
typedef void (*tb_raw_insert_spill_regs_func_t)(void *drcontext, instrlist_t *ilist, instr_t *where, bool is_inline);
typedef void (*tb_raw_insert_restore_regs_func_t)(void *drcontext, instrlist_t *ilist, instr_t *where, bool is_inline);

typedef struct {

    tb_cc_init_func_t init_func;
    tb_cc_destroy_func_t destroy_func;

    tb_cc_intro_taint_mem_func_t intro_taint_mem_func;
    tb_cc_intro_taint_reg_func_t intro_taint_reg_func;

    tb_cc_new_ref_tl_func_t new_ref_tl_func;
    tb_raw_insert_new_ref_tl_func_t insert_raw_new_ref_tl;
    tb_simd_insert_new_ref_tl_func_t insert_simd_new_ref_tl;

    tb_cc_delete_ref_tl_func_t delete_ref_tl_func;
    tb_raw_insert_delete_ref_tl_func_t insert_raw_delete_ref_tl;
    tb_simd_insert_delete_ref_tl_func_t insert_simd_delete_ref_tl;

    tb_cc_untaint_mem_func_t untaint_mem_func;
    tb_raw_insert_untaint_mem_func_t insert_raw_untaint_mem;
    tb_simd_insert_untaint_mem_func_t insert_simd_untaint_mem;

    tb_cc_untaint_reg_func_t untaint_reg_func;
    tb_raw_insert_untaint_reg_func_t insert_raw_untaint_reg;
    tb_simd_insert_untaint_reg_func_t insert_simd_untaint_reg;

    tb_taint_prepost_info_t *pre_propagate_funcs;
    tb_taint_prepost_info_t *post_propagate_funcs;

    tb_raw_insert_meet_func_t insert_raw_meet;
    tb_simd_insert_meet_func_t insert_simd_meet;

    tb_raw_insert_propogate_1dst_1src_func_t insert_raw_propogate_1dst_1src;
    tb_simd_insert_propogate_1dst_1src_func_t insert_simd_propogate_1dst_1src;

    tb_raw_insert_propogate_1dst_2src_func_t insert_raw_propogate_1dst_2src;
    tb_simd_insert_propogate_1dst_2src_func_t insert_simd_propogate_1dst_2src;

    tb_raw_insert_spill_regs_func_t insert_raw_spill_additional_regs;
    tb_raw_insert_restore_regs_func_t insert_raw_restore_additional_regs;

    tb_cc_get_default_label_t get_default_label;

} tb_raw_taint_policy_t;

#endif /* TAINT_POLICIES_TB_RAW_TAINT_POLICY_H_ */
