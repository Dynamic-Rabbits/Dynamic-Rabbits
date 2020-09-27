/**
 f *  @file ub_instrum_insert.h
 *  @brief Common assembly operations encoded as functions
 *  to facilitate their insertion.
 *  @author John F.X. Galea
 */

#ifndef UB_INSTRUM_INSERT_H_
#define UB_INSTRUM_INSERT_H_

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"

/**
 *  Loads memory to register.
 *
 *  @param where The address to place instrumentation code
 *  @param base_reg The base register for address generation
 *  @param disp The displacement value for address generation
 *  @param dest_reg The destination register for storing the loaded memory
 */
DR_EXPORT void ub_instrum_mov_ld_mem_to_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, app_pc pc, const reg_id_t base_reg,
        const unsigned int disp, const reg_id_t dest_reg);

DR_EXPORT void ub_instrum_mov_ld_mem_opnd_to_reg(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *mem_opnd,
        const reg_id_t dest_reg);

DR_EXPORT void ub_instrum_xchg_reg_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, reg_id_t addr_reg);

DR_EXPORT void ub_instrum_xchg_reg_mem_opnd(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, opnd_t *mem_opnd);

DR_EXPORT void ub_instrum_xchg_reg_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, const reg_id_t reg2);

DR_EXPORT void ub_instrum_mov_ld_mem_to_reg_via_base_disp_index(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const reg_id_t index_reg, const unsigned int disp,
        const reg_id_t dest_reg);

DR_EXPORT void ub_instrum_mov_st_reg_to_mem_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        opnd_t *dst_opnd);

/**
 *  Stores register content to memory
 *
 *  @param where The address to place instrumentation code
 *  @param src_reg The src register where its contents is stored in memory
 *  @param base_reg The destination base register for address generation
 *  @param disp The destination displacement value for address generation
 */
DR_EXPORT void ub_instrum_mov_st_reg_to_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t src_reg, const reg_id_t dst_base_reg,
        const unsigned int dst_disp);

DR_EXPORT void ub_instrum_mov_st_immed_to_mem_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const int immed_val,
		opnd_t *dst_opnd);

DR_EXPORT void ub_instrum_mov_st_immed_to_reg(void *drcontext,
        instrlist_t *ilist, instr_t * where, const int immed_val,
        const reg_id_t dst_reg);

/**
 *  Stores register content to another register
 *
 *  @param where The address to place instrumentation code
 *  @param src_reg The src register where its contents is stored in the dest reg
 *  @param dest_reg The destination register that stores the contents of the src reg
 */
DR_EXPORT void ub_instrum_mov_st_reg_to_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t src_reg, const reg_id_t dest_reg);

DR_EXPORT void ub_instrum_shift_right(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t shift_reg, int shift_size);

DR_EXPORT void ub_instrum_shift_left(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t shift_reg, int shift_size);

DR_EXPORT void ub_instrum_and_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t value_reg, int immed_value);

DR_EXPORT void ub_instrum_or_reg_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t srcdst_reg, reg_id_t src_reg);

DR_EXPORT void ub_instrum_or_reg_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t value_reg, int immed_value);

DR_EXPORT void ub_instrum_or_mem_and_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, opnd_t *mem_opnd, reg_id_t src_reg);

DR_EXPORT void ub_instrum_or_reg_and_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t dst_reg, opnd_t *mem_opnd);

DR_EXPORT void ub_instrum_or_mem_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, opnd_t *mem_opnd, int immed_value);

DR_EXPORT void ub_instrum_inc_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t base_reg, const unsigned int disp);

DR_EXPORT void ub_instrum_inc_mem_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const unsigned int disp, reg_id_t scratch);

DR_EXPORT void ub_instrum_dec_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t base_reg, const unsigned int disp);

DR_EXPORT void ub_instrum_dec_mem_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const unsigned int disp, reg_id_t scratch);

DR_EXPORT void ub_instrum_inc_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg);

DR_EXPORT void ub_instrum_inc_reg_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t reg);

DR_EXPORT void ub_instrum_dec_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg);

DR_EXPORT void ub_instrum_dec_reg_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t reg);

DR_EXPORT void ub_instrum_arith_reg_immed_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t reg, int immed_val);

DR_EXPORT void ub_instrum_add_reg_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, int immed_val);

DR_EXPORT void ub_instrum_sub_reg_immed(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t reg, int immed_val);

/**
 *  LEA instruction
 *
 *  @param where The address to place instrumentation code
 *  @param base_reg The destination base register for address generation
 *  @param disp The destination displacement value for address generation
 *  @param dest_reg The destination address where the computed address is placed.
 */
DR_EXPORT void ub_instrum_lea_base_disp(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t base_reg, const int disp,
        const reg_id_t dest_reg);

DR_EXPORT void ub_instrum_lea_base_disp_index(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t base_reg,
        const reg_id_t index_reg, const int disp, const int scale,
        const reg_id_t dest_reg);

DR_EXPORT void ub_instrum_clear_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t clear_reg);

DR_EXPORT void ub_instrum_clear_mem(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t base_reg, int disp);

DR_EXPORT void ub_instrum_clear_mem_opnd(void *drcontext, instrlist_t *ilist,
        instr_t * where, opnd_t *mem_opnd);

/**
 *  Creates a register without using an XOR instruction in order to avoid
 *  corrupting the FLAGS register.
 *
 *  @param where The address to place instrumentation code
 *  @param clear_reg The register to clear
 */
DR_EXPORT void ub_instrum_clear_reg_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t clear_reg);

/**
 *  Creates memory without using an XOR instruction in order to avoid
 *  corrupting the FLAGS register.
 *
 *  @param where The address to place instrumentation code
 *  @param clear_reg The register to clear
 */
DR_EXPORT void ub_instrum_clear_mem_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t base_reg, int disp);

DR_EXPORT void ub_instrum_clear_mem_opnd_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *opnd);

DR_EXPORT void ub_instrum_direct_jmp(void *drcontext, instrlist_t *ilist,
        instr_t *where, instr_t* true_label);

/**
 * Test instruction to check whether a register is equal to zero.
 */

DR_EXPORT void ub_instrum_check_mem_immed_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, opnd_t *check_mem_opnd,
        int immed_val, instr_t* true_label);

DR_EXPORT void ub_instrum_check_mem_immed_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, opnd_t *check_mem_opnd,
        int immed_val, instr_t* false_label);

DR_EXPORT void ub_instrum_check_mem_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, opnd_t *check_mem_opnd,
        instr_t* true_label);

DR_EXPORT void ub_instrum_check_mem_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, app_pc translation, opnd_t *check_mem_opnd,
        instr_t* false_label);

DR_EXPORT void ub_instrum_check_null(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t check_reg, instr_t* true_label,
        instr_t* false_label);

DR_EXPORT void ub_instrum_check_simd_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_reg,
        instr_t* true_label);

DR_EXPORT void ub_instrum_check_simd_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_reg,
        instr_t* true_label);

DR_EXPORT void ub_instrum_check_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t check_reg,
        instr_t* true_label);

DR_EXPORT void ub_instrum_check_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t check_reg,
        instr_t* false_label);

/**
 * Checks null with no eflag corrupt.
 */
DR_EXPORT void ub_instrum_check_null_no_eflag_corrupt(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t check_reg,
        instr_t* true_label, instr_t* false_label);

DR_EXPORT void ub_instrum_check_null_no_eflag_corrupt_true_case(void *drcontext,
        instrlist_t *ilist, instr_t * where, reg_id_t check_reg,
        instr_t* true_label);

DR_EXPORT void ub_instrum_store_eflags(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t dst_base_reg, int offset);

DR_EXPORT void ub_instrum_load_eflags(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t src_base_reg, int offset);

/*********************************************************************
 * SIMD Instructions
 */

DR_EXPORT void ub_instrum_simd_mov_ld_mem_opnd_to_reg(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *mem_opnd,
        const reg_id_t dest_reg);

DR_EXPORT void ub_instrum_simd_mov_ld_mem_opnd_to_reg_ex(void *drcontext,
        instrlist_t *ilist, instr_t * where, opnd_t *mem_opnd,
        const reg_id_t dest_reg, app_pc translation);

DR_EXPORT void ub_instrum_simd_mov_st_reg_to_reg_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        const reg_id_t dst_reg);

DR_EXPORT void ub_instrum_simd_mov_st_reg_to_mem_opnd_ex(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        opnd_t *mem_opnd, app_pc translation);

DR_EXPORT void ub_instrum_simd_mov_st_reg_to_mem_opnd(void *drcontext,
        instrlist_t *ilist, instr_t * where, const reg_id_t src_reg,
        opnd_t *mem_opnd);

DR_EXPORT void ub_instrum_simd_clear_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, const reg_id_t src_reg);

DR_EXPORT void ub_instrum_simd_test(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t vector_check_reg);

DR_EXPORT void ub_instrum_simd_check_null_true_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_check_reg,
        instr_t* true_label);

DR_EXPORT void ub_instrum_simd_check_null_false_case(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t vector_check_reg,
        instr_t* false_label);

DR_EXPORT void ub_instrum_simd_negate_reg(void *drcontext, instrlist_t *ilist,
        instr_t * where, reg_id_t vector_src_reg, reg_id_t vector_scratch_reg);

#endif
