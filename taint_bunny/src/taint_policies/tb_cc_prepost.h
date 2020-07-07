/*
 * tb_cc_prepost.h
 *
 *  Created on: 12 Jan 2019
 *      Author: john
 */

#ifndef TAINT_POLICIES_TB_CC_PREPOST_H_
#define TAINT_POLICIES_TB_CC_PREPOST_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

typedef void (*tb_cc_pre_propagate_func_t)(void *tb_ctx);
typedef void (*tb_cc_post_propagate_func_t)(void *tb_ctx);

typedef void (*tb_raw_insert_pre_propagate_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t tb_ctx_reg,
        reg_id_t scratch_reg);
typedef void (*tb_raw_insert_post_propagate_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t tb_ctx_reg,
        reg_id_t scratch_reg);

typedef void (*tb_simd_insert_pre_propagate_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t tb_ctx_reg,
        reg_id_t scratch_xmm_reg, reg_id_t scratch_xmm_reg2,
        reg_id_t scratch_scaler_reg);
typedef void (*tb_simd_insert_post_propagate_func_t)(void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t tb_ctx_reg,
        reg_id_t scratch_xmm_reg, reg_id_t scratch_xmm_reg2,
        reg_id_t scratch_scaler_reg);

typedef struct {

    // OP_add:
    void * add_dreg_1_smem_1_func;
    void * add_dreg_2_smem_2_func;
    void * add_dreg_4_smem_4_func;
    void * add_dreg_8_smem_8_func;

    void * add_dreg_1_simm_1_func;
    void * add_dreg_2_simm_2_func;
    void * add_dreg_4_simm_4_func;

    void * add_dreg_1_sreg_1_func;
    void * add_dreg_2_sreg_2_func;
    void * add_dreg_4_sreg_4_func;
    void * add_dreg_8_sreg_8_func;

    void * add_dmem_1_sreg_1_func;
    void * add_dmem_2_sreg_2_func;
    void * add_dmem_4_sreg_4_func;
    void * add_dmem_8_sreg_8_func;

    void * add_dmem_1_simm_1_func;
    void * add_dmem_2_simm_2_func;
    void * add_dmem_4_simm_4_func;

    void * add_dreg_2_simm_1_func;
    void * add_dreg_4_simm_1_func;
    void * add_dreg_8_simm_1_func;

    void * add_dmem_2_simm_1_func;
    void * add_dmem_4_simm_1_func;
    void * add_dmem_8_simm_1_func;

    // OP_or:
    void * or_dreg_1_smem_1_func;
    void * or_dreg_2_smem_2_func;
    void * or_dreg_4_smem_4_func;
    void * or_dreg_8_smem_8_func;

    void * or_dreg_1_simm_1_func;
    void * or_dreg_2_simm_2_func;
    void * or_dreg_4_simm_4_func;

    void * or_dreg_1_sreg_1_func;
    void * or_dreg_2_sreg_2_func;
    void * or_dreg_4_sreg_4_func;
    void * or_dreg_8_sreg_8_func;

    void * or_dmem_1_sreg_1_func;
    void * or_dmem_2_sreg_2_func;
    void * or_dmem_4_sreg_4_func;
    void * or_dmem_8_sreg_8_func;

    void * or_dmem_1_simm_1_func;
    void * or_dmem_2_simm_2_func;
    void * or_dmem_4_simm_4_func;

    void * or_dreg_2_simm_1_func;
    void * or_dreg_4_simm_1_func;
    void * or_dreg_8_simm_1_func;

    void * or_dmem_2_simm_1_func;
    void * or_dmem_4_simm_1_func;
    void * or_dmem_8_simm_1_func;

    // OP_adc:
    void * adc_dreg_1_smem_1_func;
    void * adc_dreg_2_smem_2_func;
    void * adc_dreg_4_smem_4_func;
    void * adc_dreg_8_smem_8_func;

    void * adc_dreg_1_simm_1_func;
    void * adc_dreg_2_simm_2_func;
    void * adc_dreg_4_simm_4_func;

    void * adc_dreg_1_sreg_1_func;
    void * adc_dreg_2_sreg_2_func;
    void * adc_dreg_4_sreg_4_func;
    void * adc_dreg_8_sreg_8_func;

    void * adc_dmem_1_sreg_1_func;
    void * adc_dmem_2_sreg_2_func;
    void * adc_dmem_4_sreg_4_func;
    void * adc_dmem_8_sreg_8_func;

    void * adc_dmem_1_simm_1_func;
    void * adc_dmem_2_simm_2_func;
    void * adc_dmem_4_simm_4_func;

    void * adc_dreg_2_simm_1_func;
    void * adc_dreg_4_simm_1_func;
    void * adc_dreg_8_simm_1_func;

    void * adc_dmem_2_simm_1_func;
    void * adc_dmem_4_simm_1_func;
    void * adc_dmem_8_simm_1_func;

    // OP_sbb:
    void * sbb_dreg_1_smem_1_func;
    void * sbb_dreg_2_smem_2_func;
    void * sbb_dreg_4_smem_4_func;
    void * sbb_dreg_8_smem_8_func;

    void * sbb_dreg_1_simm_1_func;
    void * sbb_dreg_2_simm_2_func;
    void * sbb_dreg_4_simm_4_func;

    void * sbb_dreg_1_sreg_1_func;
    void * sbb_dreg_2_sreg_2_func;
    void * sbb_dreg_4_sreg_4_func;
    void * sbb_dreg_8_sreg_8_func;

    void * sbb_dmem_1_sreg_1_func;
    void * sbb_dmem_2_sreg_2_func;
    void * sbb_dmem_4_sreg_4_func;
    void * sbb_dmem_8_sreg_8_func;

    void * sbb_dmem_1_simm_1_func;
    void * sbb_dmem_2_simm_2_func;
    void * sbb_dmem_4_simm_4_func;

    void * sbb_dreg_2_simm_1_func;
    void * sbb_dreg_4_simm_1_func;
    void * sbb_dreg_8_simm_1_func;

    void * sbb_dmem_2_simm_1_func;
    void * sbb_dmem_4_simm_1_func;
    void * sbb_dmem_8_simm_1_func;

    // OP_and:
    void * and_dreg_1_smem_1_func;
    void * and_dreg_2_smem_2_func;
    void * and_dreg_4_smem_4_func;
    void * and_dreg_8_smem_8_func;

    void * and_dreg_1_simm_1_func;
    void * and_dreg_2_simm_2_func;
    void * and_dreg_4_simm_4_func;

    void * and_dreg_1_sreg_1_func;
    void * and_dreg_2_sreg_2_func;
    void * and_dreg_4_sreg_4_func;
    void * and_dreg_8_sreg_8_func;

    void * and_dmem_1_sreg_1_func;
    void * and_dmem_2_sreg_2_func;
    void * and_dmem_4_sreg_4_func;
    void * and_dmem_8_sreg_8_func;

    void * and_dmem_1_simm_1_func;
    void * and_dmem_2_simm_2_func;
    void * and_dmem_4_simm_4_func;

    void * and_dreg_2_simm_1_func;
    void * and_dreg_4_simm_1_func;
    void * and_dreg_8_simm_1_func;

    void * and_dmem_2_simm_1_func;
    void * and_dmem_4_simm_1_func;
    void * and_dmem_8_simm_1_func;

    // OP_daa:

    // OP_sub:
    void * sub_dreg_1_smem_1_func;
    void * sub_dreg_2_smem_2_func;
    void * sub_dreg_4_smem_4_func;
    void * sub_dreg_8_smem_8_func;

    void * sub_dreg_1_simm_1_func;
    void * sub_dreg_2_simm_2_func;
    void * sub_dreg_4_simm_4_func;

    void * sub_dreg_1_sreg_1_func;
    void * sub_dreg_2_sreg_2_func;
    void * sub_dreg_4_sreg_4_func;
    void * sub_dreg_8_sreg_8_func;

    void * sub_dmem_1_sreg_1_func;
    void * sub_dmem_2_sreg_2_func;
    void * sub_dmem_4_sreg_4_func;
    void * sub_dmem_8_sreg_8_func;

    void * sub_dmem_1_simm_1_func;
    void * sub_dmem_2_simm_2_func;
    void * sub_dmem_4_simm_4_func;

    void * sub_dreg_2_simm_1_func;
    void * sub_dreg_4_simm_1_func;
    void * sub_dreg_8_simm_1_func;

    void * sub_dmem_2_simm_1_func;
    void * sub_dmem_4_simm_1_func;
    void * sub_dmem_8_simm_1_func;

    // OP_das:

    // OP_xor:
    void * xor_dreg_1_smem_1_func;
    void * xor_dreg_2_smem_2_func;
    void * xor_dreg_4_smem_4_func;
    void * xor_dreg_8_smem_8_func;

    void * xor_dreg_1_simm_1_func;
    void * xor_dreg_2_simm_2_func;
    void * xor_dreg_4_simm_4_func;

    void * xor_dreg_1_sreg_1_func;
    void * xor_dreg_2_sreg_2_func;
    void * xor_dreg_4_sreg_4_func;
    void * xor_dreg_8_sreg_8_func;

    void * xor_dmem_1_sreg_1_func;
    void * xor_dmem_2_sreg_2_func;
    void * xor_dmem_4_sreg_4_func;
    void * xor_dmem_8_sreg_8_func;

    void * xor_dmem_1_simm_1_func;
    void * xor_dmem_2_simm_2_func;
    void * xor_dmem_4_simm_4_func;

    void * xor_dreg_2_simm_1_func;
    void * xor_dreg_4_simm_1_func;
    void * xor_dreg_8_simm_1_func;

    void * xor_dmem_2_simm_1_func;
    void * xor_dmem_4_simm_1_func;
    void * xor_dmem_8_simm_1_func;

    // OP_aaa:

    // OP_aas:

    // OP_inc:
    void * inc_dsmem_1_func;
    void * inc_dsmem_2_func;
    void * inc_dsmem_4_func;
    void * inc_dsmem_8_func;
    void * inc_dsreg_1_func;
    void * inc_dsreg_2_func;
    void * inc_dsreg_4_func;
    void * inc_dsreg_8_func;

    // OP_dec:
    void * dec_dsmem_1_func;
    void * dec_dsmem_2_func;
    void * dec_dsmem_4_func;
    void * dec_dsmem_8_func;
    void * dec_dsreg_1_func;
    void * dec_dsreg_2_func;
    void * dec_dsreg_4_func;
    void * dec_dsreg_8_func;

    // OP_push:
    void * push_dmem_1_sreg_1_func;
    void * push_dmem_2_sreg_2_func;
    void * push_dmem_4_sreg_4_func;
    void * push_dmem_8_sreg_8_func;
    void * push_dmem_1_smem_1_func;
    void * push_dmem_2_smem_2_func;
    void * push_dmem_4_smem_4_func;
    void * push_dmem_8_smem_8_func;

    // OP_push_imm:

    // OP_pop:
    void * pop_dreg_1_smem_1_func;
    void * pop_dreg_2_smem_2_func;
    void * pop_dreg_4_smem_4_func;
    void * pop_dreg_8_smem_8_func;

    // OP_pusha:

    // OP_popa:

    // OP_bound:

    // OP_arpl:

    // OP_imul:
    void * imul_dreg_2_sreg_1_sreg_1_func;
    void * imul_dreg_2_smem_1_sreg_1_func;
    void * imul_dreg_4_dreg_4_sreg_4_sreg_4_func;
    void * imul_dreg_4_dreg_4_smem_4_sreg_4_func;

    void * imul_dreg_2_smem_2_func;
    void * imul_dreg_4_smem_4_func;

    void * imul_dreg_2_sreg_2_func;
    void * imul_dreg_4_sreg_4_func;

    void * imul_dreg_2_simm_1_func;
    void * imul_dreg_4_simm_1_func;
    void * imul_dreg_2_simm_2_func;
    void * imul_dreg_4_simm_4_func;

    void * imul_dreg_2_sreg_2_simm_2_func;
    void * imul_dreg_4_sreg_4_simm_4_func;

    void * imul_dreg_2_smem_2_simm_2_func;
    void * imul_dreg_4_smem_4_simm_4_func;

    // OP_call:
    // OP_call_ind:
    // OP_call_far:
    // OP_call_far_ind:
    // OP_loopne:
    // OP_loope:
    // OP_loop:
    // OP_jecxz:

    // OP_mov_ld:
    void * mov_dreg_1_smem_1_func;
    void * mov_dreg_2_smem_2_func;
    void * mov_dreg_4_smem_4_func;
    void * mov_dreg_8_smem_8_func;
    void * mov_dreg_16_smem_16_func;

    // OP_mov_st:
    void * mov_dreg_1_sreg_1_func;
    void * mov_dreg_2_sreg_2_func;
    void * mov_dreg_4_sreg_4_func;
    void * mov_dreg_8_sreg_8_func;
    void * mov_dreg_16_sreg_16_func;

    void * mov_dmem_1_sreg_1_func;
    void * mov_dmem_2_sreg_2_func;
    void * mov_dmem_4_sreg_4_func;
    void * mov_dmem_8_sreg_8_func;
    void * mov_dmem_16_sreg_16_func;

    // OP_mov_imm:

    // OP_mov_seg:
    // OP_mov_priv:

    // OP_lea:
    void * lea_dreg_2_sreg_2_sreg_2_func;
    void * lea_dreg_4_sreg_4_sreg_4_func;
    void * lea_dreg_8_sreg_8_sreg_8_func;

    void * lea_base_dreg_2_sreg_2_func;
    void * lea_base_dreg_4_sreg_4_func;
    void * lea_base_dreg_8_sreg_8_func;

    void * lea_index_dreg_2_sreg_2_func;
    void * lea_index_dreg_4_sreg_4_func;
    void * lea_index_dreg_8_sreg_8_func;

    // OP_xchg:
    void * xchg_reg_1_reg_1_func;
    void * xchg_reg_2_reg_2_func;
    void * xchg_reg_4_reg_4_func;
    void * xchg_reg_8_reg_8_func;
    void * xchg_mem_1_reg_1_func;
    void * xchg_mem_2_reg_2_func;
    void * xchg_mem_4_reg_4_func;
    void * xchg_mem_8_reg_8_func;
    void * xchg_reg_1_mem_1_func;
    void * xchg_reg_2_mem_2_func;
    void * xchg_reg_4_mem_4_func;
    void * xchg_reg_8_mem_8_func;

    // OP_cwde:
    void * cwde_func;

    // OP_cdq:
    void * cdq_func;

    // OP_fwait:

    // OP_pushf:
    // OP_popf:
    // OP_sahf:
    // OP_lahf:

    // OP_ret:

    // OP_ret_far:

    // OP_les:

    // OP_lds:

    // OP_enter:

    // OP_leave:
    void * leave_dreg_4_dreg_4_sreg_4_smem_4_func;
    void * leave_dreg_8_dreg_8_sreg_8_smem_8_func;

    // OP_into:

    // OP_iret:
    // OP_aam:

    // OP_aad:

    // OP_xlat:
    // OP_in:
    // OP_out:
    // OP_hlt:

    // OP_lar:
    // OP_lsl:

    // OP_clts:
    // OP_sysret:
    // OP_invd:
    // OP_wbinvd:
    // OP_ud2a:
    // OP_nop_modrm:
    // OP_movntps:

    // OP_movntpd:

    // OP_wrmsr:
    // OP_rdtsc:
    // OP_rdmsr:
    // OP_rdpmc:

    // OP_cmovo:
    void * cmovo_dreg_2_sreg_2_func;
    void * cmovo_dreg_4_sreg_4_func;
    void * cmovo_dreg_8_sreg_8_func;
    void * cmovo_dreg_2_smem_2_func;
    void * cmovo_dreg_4_smem_4_func;
    void * cmovo_dreg_8_smem_8_func;

    // OP_cmovno:
    void * cmovno_dreg_2_sreg_2_func;
    void * cmovno_dreg_4_sreg_4_func;
    void * cmovno_dreg_8_sreg_8_func;
    void * cmovno_dreg_2_smem_2_func;
    void * cmovno_dreg_4_smem_4_func;
    void * cmovno_dreg_8_smem_8_func;

    // OP_cmovb:
    void * cmovb_dreg_2_sreg_2_func;
    void * cmovb_dreg_4_sreg_4_func;
    void * cmovb_dreg_8_sreg_8_func;
    void * cmovb_dreg_2_smem_2_func;
    void * cmovb_dreg_4_smem_4_func;
    void * cmovb_dreg_8_smem_8_func;

    // OP_cmovnb:
    void * cmovnb_dreg_2_sreg_2_func;
    void * cmovnb_dreg_4_sreg_4_func;
    void * cmovnb_dreg_8_sreg_8_func;
    void * cmovnb_dreg_2_smem_2_func;
    void * cmovnb_dreg_4_smem_4_func;
    void * cmovnb_dreg_8_smem_8_func;

    // OP_cmovz:
    void * cmove_dreg_2_sreg_2_func;
    void * cmove_dreg_4_sreg_4_func;
    void * cmove_dreg_8_sreg_8_func;
    void * cmove_dreg_2_smem_2_func;
    void * cmove_dreg_4_smem_4_func;
    void * cmove_dreg_8_smem_8_func;

    // OP_cmovnz:
    void * cmovne_dreg_2_sreg_2_func;
    void * cmovne_dreg_4_sreg_4_func;
    void * cmovne_dreg_8_sreg_8_func;
    void * cmovne_dreg_2_smem_2_func;
    void * cmovne_dreg_4_smem_4_func;
    void * cmovne_dreg_8_smem_8_func;

    // OP_cmovbe:
    void * cmovbe_dreg_2_sreg_2_func;
    void * cmovbe_dreg_4_sreg_4_func;
    void * cmovbe_dreg_8_sreg_8_func;
    void * cmovbe_dreg_2_smem_2_func;
    void * cmovbe_dreg_4_smem_4_func;
    void * cmovbe_dreg_8_smem_8_func;

    // OP_cmovnbe:
    void * cmovnbe_dreg_2_sreg_2_func;
    void * cmovnbe_dreg_4_sreg_4_func;
    void * cmovnbe_dreg_8_sreg_8_func;
    void * cmovnbe_dreg_2_smem_2_func;
    void * cmovnbe_dreg_4_smem_4_func;
    void * cmovnbe_dreg_8_smem_8_func;

    // OP_cmovs:
    void * cmovs_dreg_2_sreg_2_func;
    void * cmovs_dreg_4_sreg_4_func;
    void * cmovs_dreg_8_sreg_8_func;
    void * cmovs_dreg_2_smem_2_func;
    void * cmovs_dreg_4_smem_4_func;
    void * cmovs_dreg_8_smem_8_func;

    // OP_cmovns:
    void * cmovns_dreg_2_sreg_2_func;
    void * cmovns_dreg_4_sreg_4_func;
    void * cmovns_dreg_8_sreg_8_func;
    void * cmovns_dreg_2_smem_2_func;
    void * cmovns_dreg_4_smem_4_func;
    void * cmovns_dreg_8_smem_8_func;

    // OP_cmovp:
    void * cmovp_dreg_2_sreg_2_func;
    void * cmovp_dreg_4_sreg_4_func;
    void * cmovp_dreg_8_sreg_8_func;
    void * cmovp_dreg_2_smem_2_func;
    void * cmovp_dreg_4_smem_4_func;
    void * cmovp_dreg_8_smem_8_func;

    // OP_cmovnp:
    void * cmovnp_dreg_2_sreg_2_func;
    void * cmovnp_dreg_4_sreg_4_func;
    void * cmovnp_dreg_8_sreg_8_func;
    void * cmovnp_dreg_2_smem_2_func;
    void * cmovnp_dreg_4_smem_4_func;
    void * cmovnp_dreg_8_smem_8_func;

    // OP_cmovl:
    void * cmovl_dreg_2_sreg_2_func;
    void * cmovl_dreg_4_sreg_4_func;
    void * cmovl_dreg_8_sreg_8_func;
    void * cmovl_dreg_2_smem_2_func;
    void * cmovl_dreg_4_smem_4_func;
    void * cmovl_dreg_8_smem_8_func;

    // OP_cmovnl:
    void * cmovge_dreg_2_sreg_2_func;
    void * cmovge_dreg_4_sreg_4_func;
    void * cmovge_dreg_8_sreg_8_func;
    void * cmovge_dreg_2_smem_2_func;
    void * cmovge_dreg_4_smem_4_func;
    void * cmovge_dreg_8_smem_8_func;

    // OP_cmovle:
    void * cmovle_dreg_2_sreg_2_func;
    void * cmovle_dreg_4_sreg_4_func;
    void * cmovle_dreg_8_sreg_8_func;
    void * cmovle_dreg_2_smem_2_func;
    void * cmovle_dreg_4_smem_4_func;
    void * cmovle_dreg_8_smem_8_func;

    // OP_cmovnle:
    void * cmovg_dreg_2_sreg_2_func;
    void * cmovg_dreg_4_sreg_4_func;
    void * cmovg_dreg_8_sreg_8_func;
    void * cmovg_dreg_2_smem_2_func;
    void * cmovg_dreg_4_smem_4_func;
    void * cmovg_dreg_8_smem_8_func;

    // OP_punpcklbw:
    void * punpcklbw_dreg_8_sreg_8_func;
    void * punpcklbw_dreg_8_smem_8_func;
    void * punpcklbw_dreg_16_sreg_16_func;
    void * punpcklbw_dreg_16_smem_16_func;

    // OP_punpcklwd:
    void * punpcklwd_dreg_8_sreg_8_func;
    void * punpcklwd_dreg_8_smem_8_func;
    void * punpcklwd_dreg_16_sreg_16_func;
    void * punpcklwd_dreg_16_smem_16_func;

    // OP_punpckldq:
    void * punpckldq_dreg_8_sreg_8_func;
    void * punpckldq_dreg_8_smem_8_func;
    void * punpckldq_dreg_16_sreg_16_func;
    void * punpckldq_dreg_16_smem_16_func;

    // OP_packsswb:
    void * packsswb_dreg_8_sreg_8_func;
    void * packsswb_dreg_8_smem_8_func;
    void * packsswb_dreg_16_sreg_16_func;
    void * packsswb_dreg_16_smem_16_func;

    // OP_pcmpgtb:
    void * pcmpgtb_dreg_8_smem_8_func;
    void * pcmpgtb_dreg_8_sreg_8_func;
    void * pcmpgtb_dreg_16_smem_16_func;
    void * pcmpgtb_dreg_16_sreg_16_func;

    // OP_pcmpgtw:
    void * pcmpgtw_dreg_8_smem_8_func;
    void * pcmpgtw_dreg_8_sreg_8_func;
    void * pcmpgtw_dreg_16_smem_16_func;
    void * pcmpgtw_dreg_16_sreg_16_func;

    // OP_pcmpgtd:
    void * pcmpgtd_dreg_8_smem_8_func;
    void * pcmpgtd_dreg_8_sreg_8_func;
    void * pcmpgtd_dreg_16_smem_16_func;
    void * pcmpgtd_dreg_16_sreg_16_func;

    // OP_packuswb:
    void * packuswb_dreg_8_sreg_8_func;
    void * packuswb_dreg_8_smem_8_func;
    void * packuswb_dreg_16_sreg_16_func;
    void * packuswb_dreg_16_smem_16_func;

    // OP_punpckhbw:
    void * punpckhbw_dreg_8_sreg_8_func;
    void * punpckhbw_dreg_8_smem_8_func;
    void * punpckhbw_dreg_16_sreg_16_func;
    void * punpckhbw_dreg_16_smem_16_func;

    // OP_punpckhwd:
    void * punpckhwd_dreg_8_sreg_8_func;
    void * punpckhwd_dreg_8_smem_8_func;
    void * punpckhwd_dreg_16_sreg_16_func;
    void * punpckhwd_dreg_16_smem_16_func;

    // OP_punpckhdq:
    void * punpckhdq_dreg_8_sreg_8_func;
    void * punpckhdq_dreg_8_smem_8_func;
    void * punpckhdq_dreg_16_sreg_16_func;
    void * punpckhdq_dreg_16_smem_16_func;

    // OP_packssdw:
    void * packssdw_dreg_8_sreg_8_func;
    void * packssdw_dreg_8_smem_8_func;
    void * packssdw_dreg_16_sreg_16_func;
    void * packssdw_dreg_16_smem_16_func;

    // OP_punpcklqdq:
    void * punpcklqdq_dreg_16_sreg_16_func;
    void * punpcklqdq_dreg_16_smem_16_func;

    // OP_punpckhqdq:
    void * punpckhqdq_dreg_16_sreg_16_func;
    void * punpckhqdq_dreg_16_smem_16_func;

    // OP_movd:
    void * movd_dreg_4_smem_4_func;
    void * movd_dreg_4_sreg_4_func;
    void * movd_dmem_4_sreg_4_func;

    void * movd_dreg_8_smem_4_func;
    void * movd_dreg_8_sreg_4_func;
    void * movd_dreg_4_sreg_8_func;
    void * movd_dmem_4_sreg_8_func;

    void * movd_dreg_16_smem_4_func;
    void * movd_dreg_16_sreg_4_func;
    void * movd_dmem_4_sreg_16_func;
    void * movd_dreg_4_sreg_16_func;

    // OP_movq:
    void * movq_dreg_8_smem_8_func;
    void * movq_dreg_8_sreg_8_func;
    void * movq_dmem_8_sreg_8_func;

    void * movq_dreg_16_smem_8_func;
    void * movq_dreg_16_sreg_8_func;
    void * movq_dmem_8_sreg_16_func;
    void * movq_dreg_8_sreg_16_func;

    // OP_movdqu:
    void * movdqu_dreg_16_smem_16_func;
    void * movdqu_dmem_16_sreg_16_func;
    void * movdqu_dreg_16_sreg_16_func;

    // OP_movdqa:
    void * movdqa_dreg_16_smem_16_func;
    void * movdqa_dmem_16_sreg_16_func;
    void * movdqa_dreg_16_sreg_16_func;

    // OP_pshufw:
    void * pshufw_dreg_8_smem_8_func;
    void * pshufw_dreg_8_sreg_8_func;
    void * pshufw_dreg_16_smem_16_func;
    void * pshufw_dreg_16_sreg_16_func;

    // OP_pshufd:
    void * pshufd_dreg_8_smem_8_func;
    void * pshufd_dreg_8_sreg_8_func;
    void * pshufd_dreg_16_smem_16_func;
    void * pshufd_dreg_16_sreg_16_func;

    // OP_pshufhw:
    void * pshufhw_dreg_16_smem_16_func;
    void * pshufhw_dreg_16_sreg_16_func;

    // OP_pshuflw:
    void * pshuflw_dreg_16_smem_16_func;
    void * pshuflw_dreg_16_sreg_16_func;

    // OP_pcmpeqb:
    void * pcmpeqb_dreg_8_smem_8_func;
    void * pcmpeqb_dreg_8_sreg_8_func;
    void * pcmpeqb_dreg_16_smem_16_func;
    void * pcmpeqb_dreg_16_sreg_16_func;

    // OP_pcmpeqw:
    void * pcmpeqw_dreg_8_smem_8_func;
    void * pcmpeqw_dreg_8_sreg_8_func;
    void * pcmpeqw_dreg_16_smem_16_func;
    void * pcmpeqw_dreg_16_sreg_16_func;

    // OP_pcmpeqd:
    void * pcmpeqd_dreg_8_smem_8_func;
    void * pcmpeqd_dreg_8_sreg_8_func;
    void * pcmpeqd_dreg_16_smem_16_func;
    void * pcmpeqd_dreg_16_sreg_16_func;

    // OP_emms:

    // OP_seto:

    // OP_setno:

    // OP_setb:

    // OP_setnb:

    // OP_setz:

    // OP_setnz:

    // OP_setbe:

    // OP_setnbe:

    // OP_sets:

    // OP_setns:

    // OP_setp:

    // OP_setnp:

    // OP_setl:

    // OP_setnl:

    // OP_setle:

    // OP_setnle:

    // OP_cpuid:

    // OP_shld:
    void * shld_dmem_2_sreg_2_simm_1_func;
    void * shld_dmem_4_sreg_4_simm_1_func;
    void * shld_dmem_8_sreg_8_simm_1_func;
    void * shld_dreg_2_sreg_2_simm_1_func;
    void * shld_dreg_4_sreg_4_simm_1_func;
    void * shld_dreg_8_sreg_8_simm_1_func;
    void * shld_dmem_2_sreg_2_sreg_1_func;
    void * shld_dmem_4_sreg_4_sreg_1_func;
    void * shld_dmem_8_sreg_8_sreg_1_func;
    void * shld_dreg_2_sreg_2_sreg_1_func;
    void * shld_dreg_4_sreg_4_sreg_1_func;
    void * shld_dreg_8_sreg_8_sreg_1_func;

    // OP_rsm:
    // OP_bts:

    // OP_shrd:
    void * shrd_dmem_2_sreg_2_simm_1_func;
    void * shrd_dmem_4_sreg_4_simm_1_func;
    void * shrd_dmem_8_sreg_8_simm_1_func;
    void * shrd_dreg_2_sreg_2_simm_1_func;
    void * shrd_dreg_4_sreg_4_simm_1_func;
    void * shrd_dreg_8_sreg_8_simm_1_func;
    void * shrd_dmem_2_sreg_2_sreg_1_func;
    void * shrd_dmem_4_sreg_4_sreg_1_func;
    void * shrd_dmem_8_sreg_8_sreg_1_func;
    void * shrd_dreg_2_sreg_2_sreg_1_func;
    void * shrd_dreg_4_sreg_4_sreg_1_func;
    void * shrd_dreg_8_sreg_8_sreg_1_func;

    // OP_cmpxchg:
    void * cmpxchg_sreg_1_smem_1_func;
    void * cmpxchg_sreg_2_smem_2_func;
    void * cmpxchg_sreg_4_smem_4_func;
    void * cmpxchg_sreg_8_smem_8_func;
    void * cmpxchg_sreg_1_sreg_1_func;
    void * cmpxchg_sreg_2_sreg_2_func;
    void * cmpxchg_sreg_4_sreg_4_func;
    void * cmpxchg_sreg_8_sreg_8_func;

    // OP_lss:
    // OP_btr:
    // OP_lfs:
    // OP_lgs:

    // OP_movzx:
    void * movzx_dreg_2_smem_1_func;
    void * movzx_dreg_4_smem_1_func;
    void * movzx_dreg_4_smem_2_func;
    void * movzx_dreg_2_sreg_1_func;
    void * movzx_dreg_4_sreg_1_func;
    void * movzx_dreg_4_sreg_2_func;

    // OP_ud2b:
    // OP_btc:
    // OP_bsf:
    void * bsf_dreg_2_smem_2_func;
    void * bsf_dreg_4_smem_4_func;
    void * bsf_dreg_8_smem_8_func;
    void * bsf_dreg_2_sreg_2_func;
    void * bsf_dreg_4_sreg_4_func;
    void * bsf_dreg_8_sreg_8_func;

    // OP_bsr:
    void * bsr_dreg_2_smem_2_func;
    void * bsr_dreg_4_smem_4_func;
    void * bsr_dreg_8_smem_8_func;
    void * bsr_dreg_2_sreg_2_func;
    void * bsr_dreg_4_sreg_4_func;
    void * bsr_dreg_8_sreg_8_func;

    // OP_movsx:
    void * movsx_dreg_2_smem_1_func;
    void * movsx_dreg_4_smem_1_func;
    void * movsx_dreg_4_smem_2_func;
    void * movsx_dreg_2_sreg_1_func;
    void * movsx_dreg_4_sreg_1_func;
    void * movsx_dreg_4_sreg_2_func;

    // OP_xadd:
    void * xadd_reg_1_reg_1_func;
    void * xadd_reg_2_reg_2_func;
    void * xadd_reg_4_reg_4_func;
    void * xadd_reg_8_reg_8_func;
    void * xadd_mem_1_reg_1_func;
    void * xadd_mem_2_reg_2_func;
    void * xadd_mem_4_reg_4_func;
    void * xadd_mem_8_reg_8_func;

    // OP_movnti:

    // OP_pinsrw:

    // OP_pextrw:
    void * pextrw_dreg_4_sreg_16_func;
    void * pextrw_dreg_4_sreg_8_func;
    void * pextrw_dmem_2_sreg_16_func;

    // OP_bswap:
    void * bswap_dsreg_1_func;
    void * bswap_dsreg_2_func;
    void * bswap_dsreg_4_func;
    void * bswap_dsreg_8_func;
    void * bswap_dsmem_1_func;
    void * bswap_dsmem_2_func;
    void * bswap_dsmem_4_func;
    void * bswap_dsmem_8_func;

    // OP_psrlw:
    void * psrlw_dreg_8_sreg_8_sreg_8_func;
    void * psrlw_dreg_16_sreg_16_sreg_16_func;
    void * psrlw_dreg_8_sreg_8_smem_8_func;
    void * psrlw_dreg_16_sreg_16_smem_16_func;
    void * psrlw_dreg_8_sreg_8_simm_1_func;
    void * psrlw_dreg_16_sreg_16_simm_1_func;

    // OP_psrld:
    void * psrld_dreg_8_sreg_8_sreg_8_func;
    void * psrld_dreg_16_sreg_16_sreg_16_func;
    void * psrld_dreg_8_sreg_8_smem_8_func;
    void * psrld_dreg_16_sreg_16_smem_16_func;
    void * psrld_dreg_8_sreg_8_simm_1_func;
    void * psrld_dreg_16_sreg_16_simm_1_func;

    // OP_psrlq:
    void * psrlq_dreg_8_sreg_8_sreg_8_func;
    void * psrlq_dreg_16_sreg_16_sreg_16_func;
    void * psrlq_dreg_8_sreg_8_smem_8_func;
    void * psrlq_dreg_16_sreg_16_smem_16_func;
    void * psrlq_dreg_8_sreg_8_simm_1_func;
    void * psrlq_dreg_16_sreg_16_simm_1_func;

    // OP_paddq:
    void * paddq_dreg_8_sreg_8_func;
    void * paddq_dreg_16_sreg_16_func;
    void * paddq_dreg_8_smem_8_func;
    void * paddq_dreg_16_smem_16_func;

    // OP_pmullw:
    void * pmullw_dreg_8_sreg_8_func;
    void * pmullw_dreg_16_sreg_16_func;
    void * pmullw_dreg_8_smem_8_func;
    void * pmullw_dreg_16_smem_16_func;

    // OP_pmovmskb:
    void * pmovmsk_dreg_4_sreg_8_func;
    void * pmovmsk_dreg_4_sreg_16_func;
    void * pmovmsk_dreg_8_sreg_8_func;
    void * pmovmsk_dreg_8_sreg_16_func;

    // OP_psubusb:

    // OP_psubusw:

    // OP_pminub:
    void * pminub_dreg_8_smem_8_func;
    void * pminub_dreg_8_sreg_8_func;
    void * pminub_dreg_16_smem_16_func;
    void * pminub_dreg_16_sreg_16_func;

    // OP_pand:
    void * pand_dreg_8_smem_8_func;
    void * pand_dreg_8_sreg_8_func;
    void * pand_dreg_16_smem_16_func;
    void * pand_dreg_16_sreg_16_func;

    // OP_paddusb:

    // OP_paddusw:

    // OP_pmaxub:
    void * pmaxub_dreg_8_smem_8_func;
    void * pmaxub_dreg_8_sreg_8_func;
    void * pmaxub_dreg_16_smem_16_func;
    void * pmaxub_dreg_16_sreg_16_func;

    // OP_pandn:
    void * pandn_dreg_8_smem_8_func;
    void * pandn_dreg_8_sreg_8_func;
    void * pandn_dreg_16_smem_16_func;
    void * pandn_dreg_16_sreg_16_func;

    // OP_pavgb:

    // OP_psraw:
    void * psraw_dreg_8_sreg_8_sreg_8_func;
    void * psraw_dreg_16_sreg_16_sreg_16_func;
    void * psraw_dreg_8_sreg_8_smem_8_func;
    void * psraw_dreg_16_sreg_16_smem_16_func;
    void * psraw_dreg_8_sreg_8_simm_1_func;
    void * psraw_dreg_16_sreg_16_simm_1_func;

    // OP_psrad:
    void * psrad_dreg_8_sreg_8_sreg_8_func;
    void * psrad_dreg_16_sreg_16_sreg_16_func;
    void * psrad_dreg_8_sreg_8_smem_8_func;
    void * psrad_dreg_16_sreg_16_smem_16_func;
    void * psrad_dreg_8_sreg_8_simm_1_func;
    void * psrad_dreg_16_sreg_16_simm_1_func;

    // OP_pavgw:

    // OP_pmulhuw:
    void * pmulhuw_dreg_8_smem_8_func;
    void * pmulhuw_dreg_8_sreg_8_func;
    void * pmulhuw_dreg_16_smem_16_func;
    void * pmulhuw_dreg_16_sreg_16_func;

    // OP_pmulhw:
    void * pmulhw_dreg_8_smem_8_func;
    void * pmulhw_dreg_8_sreg_8_func;
    void * pmulhw_dreg_16_smem_16_func;
    void * pmulhw_dreg_16_sreg_16_func;

    // OP_movntq:
    // OP_movntdq:
    // OP_psubsb:

    // OP_psubsw:

    // OP_pminsw:
    void * pminsw_dreg_8_smem_8_func;
    void * pminsw_dreg_8_sreg_8_func;
    void * pminsw_dreg_16_smem_16_func;
    void * pminsw_dreg_16_sreg_16_func;

    // OP_por:
    void * por_dreg_8_smem_8_func;
    void * por_dreg_8_sreg_8_func;
    void * por_dreg_16_smem_16_func;
    void * por_dreg_16_sreg_16_func;

    // OP_paddsb:

    // OP_paddsw:

    // OP_pmaxsw:
    void * pmaxsw_dreg_8_smem_8_func;
    void * pmaxsw_dreg_8_sreg_8_func;
    void * pmaxsw_dreg_16_smem_16_func;
    void * pmaxsw_dreg_16_sreg_16_func;

    // OP_pxor:
    void * pxor_dreg_8_smem_8_func;
    void * pxor_dreg_8_sreg_8_func;
    void * pxor_dreg_16_smem_16_func;
    void * pxor_dreg_16_sreg_16_func;

    // OP_psllw:
    void * psllw_dreg_8_sreg_8_sreg_8_func;
    void * psllw_dreg_16_sreg_16_sreg_16_func;
    void * psllw_dreg_8_sreg_8_smem_8_func;
    void * psllw_dreg_16_sreg_16_smem_16_func;
    void * psllw_dreg_8_sreg_8_simm_1_func;
    void * psllw_dreg_16_sreg_16_simm_1_func;

    // OP_pslld:
    void * pslld_dreg_8_sreg_8_sreg_8_func;
    void * pslld_dreg_16_sreg_16_sreg_16_func;
    void * pslld_dreg_8_sreg_8_smem_8_func;
    void * pslld_dreg_16_sreg_16_smem_16_func;
    void * pslld_dreg_8_sreg_8_simm_1_func;
    void * pslld_dreg_16_sreg_16_simm_1_func;

    // OP_psllq:
    void * psllq_dreg_8_sreg_8_sreg_8_func;
    void * psllq_dreg_16_sreg_16_sreg_16_func;
    void * psllq_dreg_8_sreg_8_smem_8_func;
    void * psllq_dreg_16_sreg_16_smem_16_func;
    void * psllq_dreg_8_sreg_8_simm_1_func;
    void * psllq_dreg_16_sreg_16_simm_1_func;

    // OP_pmuludq:

    // OP_pmaddwd:
    void * pmaddwd_dreg_8_sreg_8_sreg_8_func;
    void * pmaddwd_dreg_16_sreg_16_sreg_16_func;
    void * pmaddwd_dreg_8_sreg_8_smem_8_func;
    void * pmaddwd_dreg_16_sreg_16_smem_16_func;

    // OP_psadbw:
    // OP_maskmovq:
    // OP_maskmovdqu:

    // OP_psubb:
    void * psubb_dreg_8_smem_8_func;
    void * psubb_dreg_16_smem_16_func;
    void * psubb_dreg_8_sreg_8_func;
    void * psubb_dreg_16_sreg_16_func;

    // OP_psubw:
    void * psubw_dreg_8_sreg_8_func;
    void * psubw_dreg_16_sreg_16_func;
    void * psubw_dreg_8_smem_8_func;
    void * psubw_dreg_16_smem_16_func;

    // OP_psubd:
    void * psubd_dreg_8_smem_8_func;
    void * psubd_dreg_16_smem_16_func;
    void * psubd_dreg_8_sreg_8_func;
    void * psubd_dreg_16_sreg_16_func;

    // OP_psubq:
    void * psubq_dreg_8_sreg_8_func;
    void * psubq_dreg_16_sreg_16_func;
    void * psubq_dreg_8_smem_8_func;
    void * psubq_dreg_16_smem_16_func;

    // OP_paddb:
    void * paddb_dreg_8_smem_8_func;
    void * paddb_dreg_16_smem_16_func;
    void * paddb_dreg_8_sreg_8_func;
    void * paddb_dreg_16_sreg_16_func;

    // OP_paddw:
    void * paddw_dreg_8_smem_8_func;
    void * paddw_dreg_16_smem_16_func;
    void * paddw_dreg_8_sreg_8_func;
    void * paddw_dreg_16_sreg_16_func;

    // OP_paddd:
    void * paddd_dreg_8_smem_8_func;
    void * paddd_dreg_16_smem_16_func;
    void * paddd_dreg_8_sreg_8_func;
    void * paddd_dreg_16_sreg_16_func;

    // OP_psrldq:
    void * psrldq_dreg_16_sreg_16_simm_1_func;

    // OP_pslldq:
    void * pslldq_dreg_16_sreg_16_simm_1_func;

    // OP_rol:
    void * rol_sole_dreg_1_func;
    void * rol_sole_dreg_2_func;
    void * rol_sole_dreg_4_func;
    void * rol_sole_dreg_8_func;
    void * rol_dreg_1_imm_1_func;
    void * rol_dreg_2_imm_1_func;
    void * rol_dreg_4_imm_1_func;
    void * rol_dreg_8_imm_1_func;
    void * rol_dreg_1_reg_1_func;
    void * rol_dreg_2_reg_1_func;
    void * rol_dreg_4_reg_1_func;
    void * rol_dreg_8_reg_1_func;

    void * rol_sole_dmem_1_func;
    void * rol_sole_dmem_2_func;
    void * rol_sole_dmem_4_func;
    void * rol_sole_dmem_8_func;
    void * rol_dmem_1_imm_1_func;
    void * rol_dmem_2_imm_1_func;
    void * rol_dmem_4_imm_1_func;
    void * rol_dmem_8_imm_1_func;
    void * rol_dmem_1_reg_1_func;
    void * rol_dmem_2_reg_1_func;
    void * rol_dmem_4_reg_1_func;
    void * rol_dmem_8_reg_1_func;

    // OP_ror:
    void * ror_sole_dreg_1_func;
    void * ror_sole_dreg_2_func;
    void * ror_sole_dreg_4_func;
    void * ror_sole_dreg_8_func;
    void * ror_dreg_1_imm_1_func;
    void * ror_dreg_2_imm_1_func;
    void * ror_dreg_4_imm_1_func;
    void * ror_dreg_8_imm_1_func;
    void * ror_dreg_1_reg_1_func;
    void * ror_dreg_2_reg_1_func;
    void * ror_dreg_4_reg_1_func;
    void * ror_dreg_8_reg_1_func;

    void * ror_sole_dmem_1_func;
    void * ror_sole_dmem_2_func;
    void * ror_sole_dmem_4_func;
    void * ror_sole_dmem_8_func;
    void * ror_dmem_1_imm_1_func;
    void * ror_dmem_2_imm_1_func;
    void * ror_dmem_4_imm_1_func;
    void * ror_dmem_8_imm_1_func;
    void * ror_dmem_1_reg_1_func;
    void * ror_dmem_2_reg_1_func;
    void * ror_dmem_4_reg_1_func;
    void * ror_dmem_8_reg_1_func;

    // OP_rcl:
    void * rcl_sole_dreg_1_func;
    void * rcl_sole_dreg_2_func;
    void * rcl_sole_dreg_4_func;
    void * rcl_sole_dreg_8_func;
    void * rcl_dreg_1_imm_1_func;
    void * rcl_dreg_2_imm_1_func;
    void * rcl_dreg_4_imm_1_func;
    void * rcl_dreg_8_imm_1_func;
    void * rcl_dreg_1_reg_1_func;
    void * rcl_dreg_2_reg_1_func;
    void * rcl_dreg_4_reg_1_func;
    void * rcl_dreg_8_reg_1_func;

    void * rcl_sole_dmem_1_func;
    void * rcl_sole_dmem_2_func;
    void * rcl_sole_dmem_4_func;
    void * rcl_sole_dmem_8_func;
    void * rcl_dmem_1_imm_1_func;
    void * rcl_dmem_2_imm_1_func;
    void * rcl_dmem_4_imm_1_func;
    void * rcl_dmem_8_imm_1_func;
    void * rcl_dmem_1_reg_1_func;
    void * rcl_dmem_2_reg_1_func;
    void * rcl_dmem_4_reg_1_func;
    void * rcl_dmem_8_reg_1_func;

    // OP_rcr:
    void * rcr_sole_dreg_1_func;
    void * rcr_sole_dreg_2_func;
    void * rcr_sole_dreg_4_func;
    void * rcr_sole_dreg_8_func;
    void * rcr_dreg_1_imm_1_func;
    void * rcr_dreg_2_imm_1_func;
    void * rcr_dreg_4_imm_1_func;
    void * rcr_dreg_8_imm_1_func;
    void * rcr_dreg_1_reg_1_func;
    void * rcr_dreg_2_reg_1_func;
    void * rcr_dreg_4_reg_1_func;
    void * rcr_dreg_8_reg_1_func;

    void * rcr_sole_dmem_1_func;
    void * rcr_sole_dmem_2_func;
    void * rcr_sole_dmem_4_func;
    void * rcr_sole_dmem_8_func;
    void * rcr_dmem_1_imm_1_func;
    void * rcr_dmem_2_imm_1_func;
    void * rcr_dmem_4_imm_1_func;
    void * rcr_dmem_8_imm_1_func;
    void * rcr_dmem_1_reg_1_func;
    void * rcr_dmem_2_reg_1_func;
    void * rcr_dmem_4_reg_1_func;
    void * rcr_dmem_8_reg_1_func;

    // OP_shl:
    void * shl_sole_dreg_1_func;
    void * shl_sole_dreg_2_func;
    void * shl_sole_dreg_4_func;
    void * shl_sole_dreg_8_func;
    void * shl_dreg_1_imm_1_func;
    void * shl_dreg_2_imm_1_func;
    void * shl_dreg_4_imm_1_func;
    void * shl_dreg_8_imm_1_func;
    void * shl_dreg_1_reg_1_func;
    void * shl_dreg_2_reg_1_func;
    void * shl_dreg_4_reg_1_func;
    void * shl_dreg_8_reg_1_func;

    void * shl_sole_dmem_1_func;
    void * shl_sole_dmem_2_func;
    void * shl_sole_dmem_4_func;
    void * shl_sole_dmem_8_func;
    void * shl_dmem_1_imm_1_func;
    void * shl_dmem_2_imm_1_func;
    void * shl_dmem_4_imm_1_func;
    void * shl_dmem_8_imm_1_func;
    void * shl_dmem_1_reg_1_func;
    void * shl_dmem_2_reg_1_func;
    void * shl_dmem_4_reg_1_func;
    void * shl_dmem_8_reg_1_func;

    // OP_shr:
    void * shr_sole_dreg_1_func;
    void * shr_sole_dreg_2_func;
    void * shr_sole_dreg_4_func;
    void * shr_sole_dreg_8_func;
    void * shr_dreg_1_imm_1_func;
    void * shr_dreg_2_imm_1_func;
    void * shr_dreg_4_imm_1_func;
    void * shr_dreg_8_imm_1_func;
    void * shr_dreg_1_reg_1_func;
    void * shr_dreg_2_reg_1_func;
    void * shr_dreg_4_reg_1_func;
    void * shr_dreg_8_reg_1_func;

    void * shr_sole_dmem_1_func;
    void * shr_sole_dmem_2_func;
    void * shr_sole_dmem_4_func;
    void * shr_sole_dmem_8_func;
    void * shr_dmem_1_imm_1_func;
    void * shr_dmem_2_imm_1_func;
    void * shr_dmem_4_imm_1_func;
    void * shr_dmem_8_imm_1_func;
    void * shr_dmem_1_reg_1_func;
    void * shr_dmem_2_reg_1_func;
    void * shr_dmem_4_reg_1_func;
    void * shr_dmem_8_reg_1_func;

    // OP_sar:
    void * sar_sole_dreg_1_func;
    void * sar_sole_dreg_2_func;
    void * sar_sole_dreg_4_func;
    void * sar_sole_dreg_8_func;
    void * sar_dreg_1_imm_1_func;
    void * sar_dreg_2_imm_1_func;
    void * sar_dreg_4_imm_1_func;
    void * sar_dreg_8_imm_1_func;
    void * sar_dreg_1_reg_1_func;
    void * sar_dreg_2_reg_1_func;
    void * sar_dreg_4_reg_1_func;
    void * sar_dreg_8_reg_1_func;

    void * sar_sole_dmem_1_func;
    void * sar_sole_dmem_2_func;
    void * sar_sole_dmem_4_func;
    void * sar_sole_dmem_8_func;
    void * sar_dmem_1_imm_1_func;
    void * sar_dmem_2_imm_1_func;
    void * sar_dmem_4_imm_1_func;
    void * sar_dmem_8_imm_1_func;
    void * sar_dmem_1_reg_1_func;
    void * sar_dmem_2_reg_1_func;
    void * sar_dmem_4_reg_1_func;
    void * sar_dmem_8_reg_1_func;

    // OP_not:
    void * not_dmem_1_dmem_1_func;
    void * not_dmem_2_dmem_2_func;
    void * not_dmem_4_dmem_4_func;
    void * not_dmem_8_dmem_8_func;
    void * not_dreg_1_dreg_1_func;
    void * not_dreg_2_dreg_2_func;
    void * not_dreg_4_dreg_4_func;
    void * not_dreg_8_dreg_8_func;

    // OP_neg:
    void * neg_dmem_1_dmem_1_func;
    void * neg_dmem_2_dmem_2_func;
    void * neg_dmem_4_dmem_4_func;
    void * neg_dmem_8_dmem_8_func;
    void * neg_dreg_1_dreg_1_func;
    void * neg_dreg_2_dreg_2_func;
    void * neg_dreg_4_dreg_4_func;
    void * neg_dreg_8_dreg_8_func;

    // OP_mul:
    void * mul_dreg_2_sreg_1_sreg_1_func;
    void * mul_dreg_2_smem_1_sreg_1_func;
    void * mul_dreg_4_dreg_4_sreg_4_sreg_4_func;
    void * mul_dreg_4_dreg_4_smem_4_sreg_4_func;

    // OP_div:
    void * div_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_func;
    void * div_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_func;
    void * div_dreg_1_dreg_1_sreg_1_sreg_2_func;
    void * div_dreg_1_dreg_1_smem_1_sreg_2_func;

    // OP_idiv:
    void * idiv_dreg_4_dreg_4_smem_4_sreg_4_sreg_4_func;
    void * idiv_dreg_4_dreg_4_sreg_4_sreg_4_sreg_4_func;
    void * idiv_dreg_1_dreg_1_sreg_1_sreg_2_func;
    void * idiv_dreg_1_dreg_1_smem_1_sreg_2_func;

    // OP_sldt:
    // OP_str:
    // OP_lldt:
    // OP_ltr:
    // OP_verr:
    // OP_verw:
    // OP_sgdt:
    // OP_sidt:
    // OP_lgdt:
    // OP_lidt:
    // OP_smsw:
    // OP_lmsw:
    // OP_invlpg:
    // OP_cmpxchg8b:
    // OP_fxsave32:
    // OP_fxrstor32:
    // OP_ldmxcsr:
    // OP_stmxcsr:
    // OP_lfence:

    // OP_mfence:

    // OP_sfence:

    // OP_movups:
    void * movups_dreg_16_smem_16_func;
    void * movups_dmem_16_sreg_16_func;
    void * movups_dreg_16_sreg_16_func;

    // OP_movss:

    // OP_movupd:
    void * movupd_dreg_16_smem_16_func;
    void * movupd_dmem_16_sreg_16_func;
    void * movupd_dreg_16_sreg_16_func;

    // OP_movsd:

    // OP_movlps:
    void * movlps_dreg_16_smem_8_func;
    void * movlps_dmem_8_sreg_16_func;

    // OP_movlpd:
    void * movlpd_dreg_8_smem_8_func;
    void * movlpd_dmem_8_sreg_8_func;

    // OP_unpcklps:
    // OP_unpcklpd:
    // OP_unpckhps:
    // OP_unpckhpd:
    // OP_movhps:
    // OP_movhpd:
    // OP_movaps:
    void * movaps_dreg_16_smem_16_func;
    void * movaps_dmem_16_sreg_16_func;
    void * movaps_dreg_16_sreg_16_func;

    // OP_movapd:
    // OP_cvtpi2ps:
    // OP_cvtsi2ss:
    // OP_cvtpi2pd:
    // OP_cvtsi2sd:
    // OP_cvttps2pi:
    // OP_cvttss2si:
    // OP_cvttpd2pi:
    // OP_cvttsd2si:
    // OP_cvtps2pi:
    // OP_cvtss2si:
    // OP_cvtpd2pi:
    // OP_cvtsd2si:
    // OP_ucomiss:
    // OP_ucomisd:
    // OP_comiss:
    // OP_comisd:
    // OP_movmskps:
    // OP_movmskpd:
    // OP_sqrtps:
    // OP_sqrtss:
    // OP_sqrtpd:
    // OP_sqrtsd:
    // OP_rsqrtps:
    // OP_rsqrtss:
    // OP_rcpps:
    // OP_rcpss:
    // OP_andps:
    void * andps_dreg_16_sreg_16_func;
    void * andps_dreg_16_smem_16_func;

    // OP_andpd:
    void * andpd_dreg_16_sreg_16_func;
    void * andpd_dreg_16_smem_16_func;

    // OP_andnps:
    void * andnps_dreg_16_sreg_16_func;
    void * andnps_dreg_16_smem_16_func;

    // OP_andnpd:
    void * andnpd_dreg_16_sreg_16_func;
    void * andnpd_dreg_16_smem_16_func;

    // OP_orps:
    void * orps_dreg_16_sreg_16_func;
    void * orps_dreg_16_smem_16_func;

    // OP_orpd:
    void * orpd_dreg_16_sreg_16_func;
    void * orpd_dreg_16_smem_16_func;

    // OP_xorps:
    void * xorps_dreg_16_sreg_16_func;
    void * xorps_dreg_16_smem_16_func;

    // OP_xorpd:
    void * xorpd_dreg_16_sreg_16_func;
    void * xorpd_dreg_16_smem_16_func;

    // OP_addps:
    // OP_addss:
    // OP_addpd:
    // OP_addsd:
    // OP_mulps:
    // OP_mulss:
    // OP_mulpd:
    // OP_mulsd:
    // OP_cvtps2pd:
    // OP_cvtss2sd:
    // OP_cvtpd2ps:
    // OP_cvtsd2ss:
    // OP_cvtdq2ps:
    // OP_cvttps2dq:
    // OP_cvtps2dq:
    // OP_subps:
    // OP_subss:
    // OP_subpd:
    // OP_subsd:
    // OP_minps:
    // OP_minss:
    // OP_minpd:
    // OP_minsd:
    // OP_divps:
    // OP_divss:
    // OP_divpd:
    // OP_divsd:
    // OP_maxps:
    // OP_maxss:
    // OP_maxpd:
    // OP_maxsd:
    // OP_cmpps:
    // OP_cmpss:
    // OP_cmppd:
    // OP_cmpsd:
    // OP_shufps:
    // OP_shufpd:
    // OP_cvtdq2pd:
    // OP_cvttpd2dq:
    // OP_cvtpd2dq:

    // OP_pause:

    // OP_ins:
    // OP_rep_ins:
    // OP_outs:
    // OP_rep_outs:

    // OP_movs:
    void * movs_dmem_1_smem_1_func;
    void * movs_dmem_2_smem_2_func;
    void * movs_dmem_4_smem_4_func;
    void * movs_dmem_8_smem_8_func;

    // OP_rep_movs:
    void * rep_movsb_func;
    void * rep_movsw_func;
    void * rep_movsd_func;
    void * rep_movsq_func;

    // OP_stos:
    void * stos_dmem_1_sreg_1_func;
    void * stos_dmem_2_sreg_2_func;
    void * stos_dmem_4_sreg_4_func;
    void * stos_dmem_8_sreg_8_func;

    // OP_rep_stos:
    void * rep_stosb_func;
    void * rep_stosw_func;
    void * rep_stosd_func;
    void * rep_stosq_func;

    // OP_lods:
    // OP_rep_lods:

    // OP_rep_cmps:

    // OP_repne_cmps:

    // OP_fadd:
    // OP_fmul:
    // OP_fcom:
    // OP_fcomp:
    // OP_fsub:
    // OP_fsubr:
    // OP_fdiv:
    // OP_fdivr:
    // OP_fld:
    // OP_fst:
    // OP_fstp:
    // OP_fldenv:
    // OP_fldcw:
    // OP_fnstenv:
    // OP_fnstcw:
    // OP_fiadd:
    // OP_fimul:
    // OP_ficom:
    // OP_ficomp:
    // OP_fisub:
    // OP_fisubr:
    // OP_fidiv:
    // OP_fidivr:
    // OP_fild:
    // OP_fist:
    // OP_fistp:
    // OP_frstor:
    // OP_fnsave:
    // OP_fnstsw:

    // OP_fbld:
    // OP_fbstp:

    // OP_fxch:

    // OP_fchs:
    // OP_fabs:
    // OP_ftst:
    // OP_fxam:
    // OP_fld1:
    // OP_fldl2t:
    // OP_fldl2e:
    // OP_fldpi:
    // OP_fldlg2:
    // OP_fldln2:
    // OP_fldz:
    // OP_f2xm1:
    // OP_fyl2x:
    // OP_fptan:
    // OP_fpatan:
    // OP_fxtract:
    // OP_fprem1:
    // OP_fdecstp:
    // OP_fincstp:
    // OP_fprem:
    // OP_fyl2xp1:
    // OP_fsqrt:
    // OP_fsincos:
    // OP_frndint:
    // OP_fscale:
    // OP_fsin:
    // OP_fcos:
    // OP_fcmovb:
    // OP_fcmove:
    // OP_fcmovbe:
    // OP_fcmovu:
    // OP_fucompp:
    // OP_fcmovnb:
    // OP_fcmovne:
    // OP_fcmovnbe:
    // OP_fcmovnu:
    // OP_fnclex:
    // OP_fninit:
    // OP_fucomi:
    // OP_fcomi:
    // OP_ffree:
    // OP_fucom:
    // OP_fucomp:
    // OP_faddp:
    // OP_fmulp:
    // OP_fcompp:
    // OP_fsubrp:
    // OP_fsubp:
    // OP_fdivrp:
    // OP_fdivp:
    // OP_fucomip:
    // OP_fcomip:

    // OP_fisttp:
    // OP_haddpd:
    // OP_haddps:
    // OP_hsubpd:
    // OP_hsubps:
    // OP_addsubpd:
    // OP_addsubps:
    // OP_lddqu:
    void * lddqu_dreg_16_smem_16_func;

    // OP_monitor:
    // OP_mwait:
    // OP_movsldup:
    // OP_movshdup:
    // OP_movddup:

    // OP_femms:
    // OP_unknown_3dnow:
    // OP_pavgusb:
    // OP_pfadd:
    // OP_pfacc:
    // OP_pfcmpge:
    // OP_pfcmpgt:
    // OP_pfcmpeq:
    // OP_pfmin:
    // OP_pfmax:
    // OP_pfmul:
    // OP_pfrcp:
    // OP_pfrcpit1:
    // OP_pfrcpit2:
    // OP_pfrsqrt:
    // OP_pfrsqit1:
    // OP_pmulhrw:
    // OP_pfsub:
    // OP_pfsubr:
    // OP_pi2fd:
    // OP_pf2id:
    // OP_pi2fw:
    // OP_pf2iw:
    // OP_pfnacc:
    // OP_pfpnacc:
    // OP_pswapd:

    // OP_pshufb:
    void * pshufb_dreg_8_smem_8_func;
    void * pshufb_dreg_8_sreg_8_func;
    void * pshufb_dreg_16_smem_16_func;
    void * pshufb_dreg_16_sreg_16_func;

    // OP_phaddw:
    // OP_phaddd:
    // OP_phaddsw:
    // OP_pmaddubsw:
    // OP_phsubw:
    // OP_phsubd:
    // OP_phsubsw:
    // OP_psignb:
    // OP_psignw:
    // OP_psignd:
    // OP_pmulhrsw:
    // OP_pabsb:
    // OP_pabsw:
    // OP_pabsd:

    // OP_palignr:
    void * palignr_dreg_8_sreg_8_func;
    void * palignr_dreg_8_smem_8_func;
    void * palignr_dreg_16_sreg_16_func;
    void * palignr_dreg_16_smem_16_func;

    // OP_popcnt:
    void * popcnt_dreg_2_sreg_2_func;
    void * popcnt_dreg_2_smem_2_func;
    void * popcnt_dreg_4_sreg_4_func;
    void * popcnt_dreg_4_smem_4_func;
    void * popcnt_dreg_8_sreg_8_func;
    void * popcnt_dreg_8_smem_8_func;

    // OP_movntss:
    // OP_movntsd:
    // OP_extrq:
    // OP_insertq:
    // OP_lzcnt:
    void * lzcnt_dreg_2_smem_2_func;
    void * lzcnt_dreg_4_smem_4_func;
    void * lzcnt_dreg_8_smem_8_func;
    void * lzcnt_dreg_2_sreg_2_func;
    void * lzcnt_dreg_4_sreg_4_func;
    void * lzcnt_dreg_8_sreg_8_func;

    // OP_pblendvb:
    // OP_blendvps:
    // OP_blendvpd:

    // OP_pmovsxbw:
    // OP_pmovsxbd:
    // OP_pmovsxbq:
    // OP_pmovsxwd:
    // OP_pmovsxwq:
    // OP_pmovsxdq:
    // OP_pmuldq:

    // OP_pcmpeqq:
    void * pcmpeqq_dreg_8_smem_8_func;
    void * pcmpeqq_dreg_8_sreg_8_func;
    void * pcmpeqq_dreg_16_smem_16_func;
    void * pcmpeqq_dreg_16_sreg_16_func;

    // OP_movntdqa:
    // OP_packusdw:
    void * packusdw_dreg_16_smem_16_func;
    void * packusdw_dreg_16_sreg_16_func;

    // OP_pmovzxbw:
    // OP_pmovzxbd:
    // OP_pmovzxbq:
    // OP_pmovzxwd:
    // OP_pmovzxwq:
    // OP_pmovzxdq:

    // OP_pcmpgtq:
    void * pcmpgtq_dreg_8_smem_8_func;
    void * pcmpgtq_dreg_8_sreg_8_func;
    void * pcmpgtq_dreg_16_smem_16_func;
    void * pcmpgtq_dreg_16_sreg_16_func;

    // OP_pminsb:
    void * pminsb_dreg_16_smem_16_func;
    void * pminsb_dreg_16_sreg_16_func;

    // OP_pminsd:
    void * pminsd_dreg_16_smem_16_func;
    void * pminsd_dreg_16_sreg_16_func;

    // OP_pminuw:
    void * pminuw_dreg_16_smem_16_func;
    void * pminuw_dreg_16_sreg_16_func;

    // OP_pminud:
    void * pminud_dreg_16_smem_16_func;
    void * pminud_dreg_16_sreg_16_func;

    // OP_pmaxsb:
    void * pmaxsb_dreg_16_smem_16_func;
    void * pmaxsb_dreg_16_sreg_16_func;

    // OP_pmaxsd:
    void * pmaxsd_dreg_16_smem_16_func;
    void * pmaxsd_dreg_16_sreg_16_func;

    // OP_pmaxuw:
    void * pmaxuw_dreg_16_smem_16_func;
    void * pmaxuw_dreg_16_sreg_16_func;

    // OP_pmaxud:
    void * pmaxud_dreg_16_smem_16_func;
    void * pmaxud_dreg_16_sreg_16_func;

    // OP_pmulld:
    void * pmulld_dreg_16_smem_16_func;
    void * pmulld_dreg_16_sreg_16_func;

    // OP_phminposuw:
    // OP_crc32:

    // OP_pextrb:
    void * pextrb_dreg_4_func;
    void * pextrb_dmem_4_func;

    // OP_pextrd:
    void * pextrd_dreg_4_func;
    void * pextrd_dmem_4_func;

    // OP_extractps:
    // OP_roundps:
    // OP_roundpd:
    // OP_roundss:
    // OP_roundsd:
    // OP_blendps:
    // OP_blendpd:
    // OP_pblendw:
    // OP_pinsrb:
    // OP_insertps:
    // OP_pinsrd:
    // OP_dpps:
    // OP_dppd:
    // OP_mpsadbw:
    // OP_pcmpestrm:
    // OP_pcmpestri:
    // OP_pcmpistrm:
    // OP_pcmpistri:

    // OP_movsxd:
    // OP_swapgs:

    // OP_vmcall:
    // OP_vmlaunch:
    // OP_vmresume:
    // OP_vmxoff:
    // OP_vmptrst:
    // OP_vmptrld:
    // OP_vmxon:
    // OP_vmclear:
    // OP_vmread:
    // OP_vmwrite:

    // OP_int1:
    // OP_salc:
    // OP_ffreep:

    // OP_vmrun:
    // OP_vmmcall:
    // OP_vmload:
    // OP_vmsave:
    // OP_stgi:
    // OP_clgi:
    // OP_skinit:
    // OP_invlpga:

    // OP_rdtscp:

    // OP_invept:
    // OP_invvpid:

    // OP_pclmulqdq:
    // OP_aesimc:
    // OP_aesenc:
    // OP_aesenclast:
    // OP_aesdec:
    // OP_aesdeclast:
    // OP_aeskeygenassist:

    // OP_movbe:

    // OP_xgetbv:
    // OP_xsetbv:
    // OP_xsave32:
    // OP_xrstor32:
    // OP_xsave// OPt32:

    // OP_vmovss:
    // OP_vmovsd:
    // OP_vmovups:
    // OP_vmovupd:
    // OP_vmovlps:
    // OP_vmovsldup:
    // OP_vmovlpd:
    // OP_vmovddup:
    // OP_vunpcklps:
    // OP_vunpcklpd:
    // OP_vunpckhps:
    // OP_vunpckhpd:
    // OP_vmovhps:
    // OP_vmovshdup:
    // OP_vmovhpd:
    // OP_vmovaps:
    // OP_vmovapd:
    // OP_vcvtsi2ss:
    // OP_vcvtsi2sd:
    // OP_vmovntps:
    // OP_vmovntpd:
    // OP_vcvttss2si:
    // OP_vcvttsd2si:
    // OP_vcvtss2si:
    // OP_vcvtsd2si:
    // OP_vucomiss:
    // OP_vucomisd:
    // OP_vcomiss:
    // OP_vcomisd:
    // OP_vmovmskps:
    // OP_vmovmskpd:
    // OP_vsqrtps:
    // OP_vsqrtss:
    // OP_vsqrtpd:
    // OP_vsqrtsd:
    // OP_vrsqrtps:
    // OP_vrsqrtss:
    // OP_vrcpps:
    // OP_vrcpss:
    // OP_vandps:
    // OP_vandpd:
    // OP_vandnps:
    // OP_vandnpd:
    // OP_vorps:
    // OP_vorpd:
    // OP_vxorps:
    // OP_vxorpd:
    // OP_vaddps:
    // OP_vaddss:
    // OP_vaddpd:
    // OP_vaddsd:
    // OP_vmulps:
    // OP_vmulss:
    // OP_vmulpd:
    // OP_vmulsd:
    // OP_vcvtps2pd:
    // OP_vcvtss2sd:
    // OP_vcvtpd2ps:
    // OP_vcvtsd2ss:
    // OP_vcvtdq2ps:
    // OP_vcvttps2dq:
    // OP_vcvtps2dq:
    // OP_vsubps:
    // OP_vsubss:
    // OP_vsubpd:
    // OP_vsubsd:
    // OP_vminps:
    // OP_vminss:
    // OP_vminpd:
    // OP_vminsd:
    // OP_vdivps:
    // OP_vdivss:
    // OP_vdivpd:
    // OP_vdivsd:
    // OP_vmaxps:
    // OP_vmaxss:
    // OP_vmaxpd:
    // OP_vmaxsd:
    // OP_vpunpcklbw:
    // OP_vpunpcklwd:
    // OP_vpunpckldq:
    // OP_vpacksswb:
    // OP_vpcmpgtb:
    // OP_vpcmpgtw:
    // OP_vpcmpgtd:
    // OP_vpackuswb:
    // OP_vpunpckhbw:
    // OP_vpunpckhwd:
    // OP_vpunpckhdq:
    // OP_vpackssdw:
    // OP_vpunpcklqdq:
    // OP_vpunpckhqdq:
    // OP_vmovd:
    // OP_vpshufhw:
    // OP_vpshufd:
    // OP_vpshuflw:
    // OP_vpcmpeqb:
    // OP_vpcmpeqw:
    // OP_vpcmpeqd:
    // OP_vmovq:
    // OP_vcmpps:
    // OP_vcmpss:
    // OP_vcmppd:
    // OP_vcmpsd:
    // OP_vpinsrw:
    // OP_vpextrw:
    // OP_vshufps:
    // OP_vshufpd:
    // OP_vpsrlw:
    // OP_vpsrld:
    // OP_vpsrlq:
    // OP_vpaddq:
    // OP_vpmullw:
    // OP_vpmovmskb:
    // OP_vpsubusb:
    // OP_vpsubusw:
    // OP_vpminub:
    // OP_vpand:
    // OP_vpaddusb:
    // OP_vpaddusw:
    // OP_vpmaxub:
    // OP_vpandn:
    // OP_vpavgb:
    // OP_vpsraw:
    // OP_vpsrad:
    // OP_vpavgw:
    // OP_vpmulhuw:
    // OP_vpmulhw:
    // OP_vcvtdq2pd:
    // OP_vcvttpd2dq:
    // OP_vcvtpd2dq:
    // OP_vmovntdq:
    // OP_vpsubsb:
    // OP_vpsubsw:
    // OP_vpminsw:
    // OP_vpor:
    // OP_vpaddsb:
    // OP_vpaddsw:
    // OP_vpmaxsw:
    // OP_vpxor:
    // OP_vpsllw:
    // OP_vpslld:
    // OP_vpsllq:
    // OP_vpmuludq:
    // OP_vpmaddwd:
    // OP_vpsadbw:
    // OP_vmaskmovdqu:
    // OP_vpsubb:
    // OP_vpsubw:
    // OP_vpsubd:
    // OP_vpsubq:
    // OP_vpaddb:
    // OP_vpaddw:
    // OP_vpaddd:
    // OP_vpsrldq:
    // OP_vpslldq:
    // OP_vmovdqu:
    // OP_vmovdqa:
    // OP_vhaddpd:
    // OP_vhaddps:
    // OP_vhsubpd:
    // OP_vhsubps:
    // OP_vaddsubpd:
    // OP_vaddsubps:
    // OP_vlddqu:
    // OP_vpshufb:
    // OP_vphaddw:
    // OP_vphaddd:
    // OP_vphaddsw:
    // OP_vpmaddubsw:
    // OP_vphsubw:
    // OP_vphsubd:
    // OP_vphsubsw:
    // OP_vpsignb:
    // OP_vpsignw:
    // OP_vpsignd:
    // OP_vpmulhrsw:
    // OP_vpabsb:
    // OP_vpabsw:
    // OP_vpabsd:
    // OP_vpalignr:
    // OP_vpblendvb:
    // OP_vblendvps:
    // OP_vblendvpd:
    // OP_vptest:
    // OP_vpmovsxbw:
    // OP_vpmovsxbd:
    // OP_vpmovsxbq:
    // OP_vpmovsxwd:
    // OP_vpmovsxwq:
    // OP_vpmovsxdq:
    // OP_vpmuldq:
    // OP_vpcmpeqq:
    // OP_vmovntdqa:
    // OP_vpackusdw:
    // OP_vpmovzxbw:
    // OP_vpmovzxbd:
    // OP_vpmovzxbq:
    // OP_vpmovzxwd:
    // OP_vpmovzxwq:
    // OP_vpmovzxdq:
    // OP_vpcmpgtq:
    // OP_vpminsb:
    // OP_vpminsd:
    // OP_vpminuw:
    // OP_vpminud:
    // OP_vpmaxsb:
    // OP_vpmaxsd:
    // OP_vpmaxuw:
    // OP_vpmaxud:
    // OP_vpmulld:
    // OP_vphminposuw:
    // OP_vaesimc:
    // OP_vaesenc:
    // OP_vaesenclast:
    // OP_vaesdec:
    // OP_vaesdeclast:
    // OP_vpextrb:
    // OP_vpextrd:
    // OP_vextractps:
    // OP_vroundps:
    // OP_vroundpd:
    // OP_vroundss:
    // OP_vroundsd:
    // OP_vblendps:
    // OP_vblendpd:
    // OP_vpblendw:
    // OP_vpinsrb:
    // OP_vinsertps:
    // OP_vpinsrd:
    // OP_vdpps:
    // OP_vdppd:
    // OP_vmpsadbw:
    // OP_vpcmpestrm:
    // OP_vpcmpestri:
    // OP_vpcmpistrm:
    // OP_vpcmpistri:
    // OP_vpclmulqdq:
    // OP_vaeskeygenassist:
    // OP_vtestps:
    // OP_vtestpd:
    // OP_vzeroupper:
    // OP_vzeroall:
    // OP_vldmxcsr:
    // OP_vstmxcsr:
    // OP_vbroadcastss:
    // OP_vbroadcastsd:
    // OP_vbroadcastf128:
    // OP_vmaskmovps:
    // OP_vmaskmovpd:
    // OP_vpermilps:
    // OP_vpermilpd:
    // OP_vperm2f128:
    // OP_vinsertf128:
    // OP_vextractf128:

    // OP_vcvtph2ps:
    // OP_vcvtps2ph:

    // OP_vfmadd132ps:
    // OP_vfmadd132pd:
    // OP_vfmadd213ps:
    // OP_vfmadd213pd:
    // OP_vfmadd231ps:
    // OP_vfmadd231pd:
    // OP_vfmadd132ss:
    // OP_vfmadd132sd:
    // OP_vfmadd213ss:
    // OP_vfmadd213sd:
    // OP_vfmadd231ss:
    // OP_vfmadd231sd:
    // OP_vfmaddsub132ps:
    // OP_vfmaddsub132pd:
    // OP_vfmaddsub213ps:
    // OP_vfmaddsub213pd:
    // OP_vfmaddsub231ps:
    // OP_vfmaddsub231pd:
    // OP_vfmsubadd132ps:
    // OP_vfmsubadd132pd:
    // OP_vfmsubadd213ps:
    // OP_vfmsubadd213pd:
    // OP_vfmsubadd231ps:
    // OP_vfmsubadd231pd:
    // OP_vfmsub132ps:
    // OP_vfmsub132pd:
    // OP_vfmsub213ps:
    // OP_vfmsub213pd:
    // OP_vfmsub231ps:
    // OP_vfmsub231pd:
    // OP_vfmsub132ss:
    // OP_vfmsub132sd:
    // OP_vfmsub213ss:
    // OP_vfmsub213sd:
    // OP_vfmsub231ss:
    // OP_vfmsub231sd:
    // OP_vfnmadd132ps:
    // OP_vfnmadd132pd:
    // OP_vfnmadd213ps:
    // OP_vfnmadd213pd:
    // OP_vfnmadd231ps:
    // OP_vfnmadd231pd:
    // OP_vfnmadd132ss:
    // OP_vfnmadd132sd:
    // OP_vfnmadd213ss:
    // OP_vfnmadd213sd:
    // OP_vfnmadd231ss:
    // OP_vfnmadd231sd:
    // OP_vfnmsub132ps:
    // OP_vfnmsub132pd:
    // OP_vfnmsub213ps:
    // OP_vfnmsub213pd:
    // OP_vfnmsub231ps:
    // OP_vfnmsub231pd:
    // OP_vfnmsub132ss:
    // OP_vfnmsub132sd:
    // OP_vfnmsub213ss:
    // OP_vfnmsub213sd:
    // OP_vfnmsub231ss:
    // OP_vfnmsub231sd:

    // OP_movq2dq:
    void * movq2dq_dreg_16_sreg_8_func;

    // OP_movdq2q:
    void * movdq2q_dreg_8_sreg_16_func;

    // OP_fxsave64:
    // OP_fxrstor64:
    // OP_xsave64:
    // OP_xrstor64:
    // OP_xsave// OPt64:

    // OP_rdrand:
    // OP_rdfsbase:
    // OP_rdgsbase:
    // OP_wrfsbase:
    // OP_wrgsbase:

    // OP_rdseed:

    // OP_vfmaddsubps:
    // OP_vfmaddsubpd:
    // OP_vfmsubaddps:
    // OP_vfmsubaddpd:
    // OP_vfmaddps:
    // OP_vfmaddpd:
    // OP_vfmaddss:
    // OP_vfmaddsd:
    // OP_vfmsubps:
    // OP_vfmsubpd:
    // OP_vfmsubss:
    // OP_vfmsubsd:
    // OP_vfnmaddps:
    // OP_vfnmaddpd:
    // OP_vfnmaddss:
    // OP_vfnmaddsd:
    // OP_vfnmsubps:
    // OP_vfnmsubpd:
    // OP_vfnmsubss:
    // OP_vfnmsubsd:

    // OP_vfrczps:
    // OP_vfrczpd:
    // OP_vfrczss:
    // OP_vfrczsd:
    // OP_vpcmov:
    // OP_vpcomb:
    // OP_vpcomw:
    // OP_vpcomd:
    // OP_vpcomq:
    // OP_vpcomub:
    // OP_vpcomuw:
    // OP_vpcomud:
    // OP_vpcomuq:
    // OP_vpermil2pd:
    // OP_vpermil2ps:
    // OP_vphaddbw:
    // OP_vphaddbd:
    // OP_vphaddbq:
    // OP_vphaddwd:
    // OP_vphaddwq:
    // OP_vphadddq:
    // OP_vphaddubw:
    // OP_vphaddubd:
    // OP_vphaddubq:
    // OP_vphadduwd:
    // OP_vphadduwq:
    // OP_vphaddudq:
    // OP_vphsubbw:
    // OP_vphsubwd:
    // OP_vphsubdq:
    // OP_vpmacssww:
    // OP_vpmacsswd:
    // OP_vpmacssdql:
    // OP_vpmacssdd:
    // OP_vpmacssdqh:
    // OP_vpmacsww:
    // OP_vpmacswd:
    // OP_vpmacsdql:
    // OP_vpmacsdd:
    // OP_vpmacsdqh:
    // OP_vpmadcsswd:
    // OP_vpmadcswd:
    // OP_vpperm:
    // OP_vprotb:
    // OP_vprotw:
    // OP_vprotd:
    // OP_vprotq:
    // OP_vpshlb:
    // OP_vpshlw:
    // OP_vpshld:
    // OP_vpshlq:
    // OP_vpshab:
    // OP_vpshaw:
    // OP_vpshad:
    // OP_vpshaq:

    // OP_bextr:
    // OP_blcfill:
    // OP_blci:
    // OP_blcic:
    // OP_blcmsk:
    // OP_blcs:
    // OP_blsfill:
    // OP_blsic:
    // OP_t1mskc:
    // OP_tzmsk:

    // OP_llwpcb:
    // OP_slwpcb:
    // OP_lwpins:
    // OP_lwpval:

    // OP_andn:
    // OP_blsr:
    // OP_blsmsk:
    // OP_blsi:
    // OP_tzcnt:
    void * tzcnt_dreg_2_smem_2_func;
    void * tzcnt_dreg_4_smem_4_func;
    void * tzcnt_dreg_8_smem_8_func;
    void * tzcnt_dreg_2_sreg_2_func;
    void * tzcnt_dreg_4_sreg_4_func;
    void * tzcnt_dreg_8_sreg_8_func;

    // OP_bzhi:
    // OP_pext:

    void * pext_dreg_4_sreg_4_sreg_4_func;
    void * pext_dreg_8_sreg_8_sreg_8_func;
    void * pext_dreg_4_sreg_4_smem_4_func;
    void * pext_dreg_8_sreg_8_smem_8_func;

    // OP_pdep:
    // OP_sarx:
    // OP_shlx:
    // OP_shrx:
    // OP_rorx:
    // OP_mulx:

    // OP_getsec:

    // OP_vmfunc:
    // OP_invpcid:

    // OP_xabort:
    // OP_xbegin:
    // OP_xend:
    // OP_xtest:

    // OP_vpgatherdd:
    // OP_vpgatherdq:
    // OP_vpgatherqd:
    // OP_vpgatherqq:
    // OP_vgatherdps:
    // OP_vgatherdpd:
    // OP_vgatherqps:
    // OP_vgatherqpd:
    // OP_vbroadcasti128:
    // OP_vinserti128:
    // OP_vextracti128:
    // OP_vpmaskmovd:
    // OP_vpmaskmovq:
    // OP_vperm2i128:
    // OP_vpermd:
    // OP_vpermps:
    // OP_vpermq:
    // OP_vpermpd:
    // OP_vpblendd:
    // OP_vpsllvd:
    // OP_vpsllvq:
    // OP_vpsravd:
    // OP_vpsrlvd:
    // OP_vpsrlvq:
    // OP_vpbroadcastb:
    // OP_vpbroadcastw:
    // OP_vpbroadcastd:
    // OP_vpbroadcastq:

    // OP_xsavec32:
    // OP_xsavec64:

    // OP_adox:
    // OP_adcx:

} tb_taint_prepost_info_t;

#endif /* TAINT_POLICIES_TB_CC_PREPOST_H_ */
