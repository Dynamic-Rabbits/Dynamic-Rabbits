/*
 * tb_instr_flows.c
 *
 *      Author: john
 */

#include "ub_instr_flows.h"
#include "ub_instr_parser.h"
#include <string.h>

/**************************************************************************
 * Interface
 */

size_t ub_dataflow_num_flows(ub_instr_dataflow_t *dataflow_instr) {

    return (size_t) dataflow_instr->num_flows;
}

opnd_t ub_dataflow_get_flow_dst(instr_t *instr, ub_instr_dataflow_t *dataflow_instr_info,
        size_t flow_index) {

    DR_ASSERT(flow_index < dataflow_instr_info->num_flows);
    ub_dataflow_t dataflow_info = dataflow_instr_info->dataflow[flow_index];

    ub_opnd_access_t dst_access = dataflow_instr_info->opnd_access[dataflow_info.dst];

    return ub_opnd_access_get_opnd(instr, &dst_access);
}

ub_opnd_access_t ub_dataflow_get_flow_dst_access(ub_instr_dataflow_t *dataflow_instr_info,
        size_t flow_index) {

    DR_ASSERT(flow_index < dataflow_instr_info->num_flows);
    ub_dataflow_t dataflow_info = dataflow_instr_info->dataflow[flow_index];

    return dataflow_instr_info->opnd_access[dataflow_info.dst];
}

size_t ub_dataflow_flow_num_srcs(ub_instr_dataflow_t *dataflow_instr,
        size_t flow_index) {

    ub_instr_dataflow_t *dataflow_instr_info =
            (ub_instr_dataflow_t *) dataflow_instr;

    DR_ASSERT(flow_index < dataflow_instr_info->num_flows);

    ub_dataflow_t dataflow_info = dataflow_instr_info->dataflow[flow_index];
    return dataflow_info.num_srcs;
}

opnd_t ub_dataflow_get_flow_src(instr_t *instr, ub_instr_dataflow_t *dataflow_instr_info,
        size_t flow_index, size_t src_index) {

    DR_ASSERT(flow_index < dataflow_instr_info->num_flows);
    ub_dataflow_t dataflow_info = dataflow_instr_info->dataflow[flow_index];
    DR_ASSERT(src_index < dataflow_info.num_srcs);

    ub_opnd_access_t src_access = dataflow_instr_info->opnd_access[dataflow_info.srcs[src_index]];

    return ub_opnd_access_get_opnd(instr, &src_access);
}

ub_opnd_access_t ub_dataflow_get_flow_src_access(ub_instr_dataflow_t *dataflow_instr_info,
        size_t flow_index, size_t src_index) {

    DR_ASSERT(flow_index < dataflow_instr_info->num_flows);
    ub_dataflow_t dataflow_info = dataflow_instr_info->dataflow[flow_index];
    DR_ASSERT(src_index < dataflow_info.num_srcs);

    return dataflow_instr_info->opnd_access[dataflow_info.srcs[src_index]];
}


bool ub_dataflow_is_supported(ub_instr_dataflow_t *dataflow_instr) {

    return dataflow_instr->supported;
}

/**
 * Hey you ... yes you! Do you want to be awesome by implementing some instruction dataflow handlers?
 * PRs are welcome.
 */

void ub_dataflow_get_info(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    memset(dataflow, 0, sizeof(ub_instr_dataflow_t));

    int opcode = instr_get_opcode(instr);

    switch (opcode) {

    case OP_LABEL:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_add:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_or:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_adc:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_sbb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_and:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
//    case OP_daa:
    case OP_sub:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
//    case OP_das:
    case OP_xor:
        ub_dataflow_parse_xor(instr, dataflow);
        break;
//    case OP_aaa:
    case OP_cmp:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_aas:
    case OP_inc:
        ub_dataflow_parse_same_src(instr, dataflow);
        break;
    case OP_dec:
        ub_dataflow_parse_same_src(instr, dataflow);
        break;
    case OP_push:
        ub_dataflow_parse_push(instr, dataflow);
        break;
    case OP_push_imm:
        ub_dataflow_parse_push(instr, dataflow);
        break;
    case OP_pop:
        ub_dataflow_parse_pop(instr, dataflow);
        break;
    case OP_pusha:
        ub_dataflow_parse_pusha(instr, dataflow);
        break;
    case OP_popa:
        ub_dataflow_parse_popa(instr, dataflow);
        break;
//    case OP_bound:
//    case OP_arpl:
    case OP_imul:
        ub_dataflow_parse_imul(instr, dataflow);
        break;

    case OP_jo_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jno_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jb_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnb_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jz_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnz_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jbe_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnbe_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_js_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jns_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jp_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnp_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jl_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnl_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jle_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnle_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;

    case OP_call:
        ub_dataflow_parse_call(instr, dataflow);
        break;
    case OP_call_ind:
        ub_dataflow_parse_call(instr, dataflow);
        break;
    case OP_call_far:
        ub_dataflow_parse_call(instr, dataflow);
        break;
    case OP_call_far_ind:
        ub_dataflow_parse_call(instr, dataflow);
        break;
    case OP_jmp:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jmp_short:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jmp_ind:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jmp_far:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jmp_far_ind:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_loopne:
        ub_dataflow_parse_loop(instr, dataflow);
        break;
    case OP_loope:
        ub_dataflow_parse_loop(instr, dataflow);
        break;
    case OP_loop:
        ub_dataflow_parse_loop(instr, dataflow);
        break;
    case OP_jecxz:
        ub_dataflow_parse_none(instr, dataflow);
        break;

    case OP_mov_ld:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_mov_st:
        ub_dataflow_parse_mov_st(instr, dataflow);
        break;
    case OP_mov_imm:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
//    case OP_mov_seg:
//    case OP_mov_priv:
    case OP_test:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_lea:
        ub_dataflow_parse_lea(instr, dataflow);
        break;
    case OP_xchg:
        ub_dataflow_parse_xchg(instr, dataflow);
        break;
    case OP_cwde:
        ub_dataflow_parse_same_src(instr, dataflow);
        break;
    case OP_cdq:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_fwait:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_pushf:
        ub_dataflow_parse_pushf(instr, dataflow);
        break;

    case OP_popf:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_sahf:
//    case OP_lahf:
//
    case OP_ret:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_ret_far:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_les:
//    case OP_lds:
    case OP_enter:
        ub_dataflow_parse_enter(instr, dataflow);

        break;
    case OP_leave:
        ub_dataflow_parse_leave(instr, dataflow);
        break;
    case OP_int3:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_int:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_into:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_iret:
//    case OP_aam:
//    case OP_aad:
//    case OP_xlat:
//    case OP_in:
//    case OP_out:
    case OP_hlt:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_cmc:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_clc:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_stc:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_cli:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_sti:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_cld:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_std:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_lar:
//    case OP_lsl:
    case OP_syscall:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_clts:
//    case OP_sysret:
//    case OP_invd:
//    case OP_wbinvd:
//    case OP_ud2a:
//    case OP_nop_modrm:
//    case OP_movntps:
//    case OP_movntpd:
//    case OP_wrmsr:
    case OP_rdtsc:
        ub_dataflow_parse_rdtsc(instr, dataflow);
        break;
//    case OP_rdmsr:
//    case OP_rdpmc:
    case OP_sysenter:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_sysexit:
        ub_dataflow_parse_none(instr, dataflow);
        break;

    case OP_cmovo:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovno:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovb:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovnb:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovz:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovnz:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovbe:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovnbe:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovs:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovns:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovp:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovnp:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovl:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovnl:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovle:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;
    case OP_cmovnle:
        ub_dataflow_parse_conditional_src_dst(instr, dataflow);
        break;

    case OP_punpcklbw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_punpcklwd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_punpckldq:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_packsswb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pcmpgtb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pcmpgtw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pcmpgtd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_packuswb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_punpckhbw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_punpckhwd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_punpckhdq:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_packssdw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_punpcklqdq:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_punpckhqdq:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;

    case OP_movd:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movq:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movdqu:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movdqa:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;

    case OP_pshufw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pshufd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pshufhw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pshuflw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pcmpeqb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pcmpeqw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pcmpeqd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
//    case OP_emms:
    case OP_jo:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jno:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jb:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnb:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jz:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnz:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jbe:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnbe:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_js:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jns:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jp:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnp:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jl:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnl:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jle:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_jnle:
        ub_dataflow_parse_none(instr, dataflow);
        break;

    case OP_seto:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setno:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setb:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setnb:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setz:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setnz:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setbe:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setnbe:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_sets:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setns:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setp:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setnp:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setl:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setnl:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setle:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;
    case OP_setnle:
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
        break;

    case OP_cpuid:
        ub_dataflow_parse_cpuid(instr, dataflow);
        break;
    case OP_bt:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_shld:
        ub_dataflow_parse_shiftd(instr, dataflow);
        break;
//    case OP_rsm:
//    case OP_bts:
    case OP_shrd:
        ub_dataflow_parse_shiftd(instr, dataflow);
        break;
    case OP_cmpxchg:
        ub_dataflow_parse_cmpxchg(instr, dataflow);
        break;
//    case OP_lss:
//    case OP_btr:
//    case OP_lfs:
//    case OP_lgs:
    case OP_movzx:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
//    case OP_ud2b:
//    case OP_btc:
    case OP_bsf:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_bsr:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movsx:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_xadd:
        ub_dataflow_parse_xadd(instr, dataflow);
        break;
    case OP_movnti:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
//    case OP_pinsrw:
//    case OP_pextrw:
    case OP_bswap:
        ub_dataflow_parse_same_src(instr, dataflow);
        break;
    case OP_psrlw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psrld:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psrlq:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddq:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_pmullw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmovmskb:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_psubusb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psubusw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pminub:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pand:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddusb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddusw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmaxub:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pandn:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pavgb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psraw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psrad:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pavgw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmulhuw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmulhw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;

    case OP_movntq:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movntdq:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_psubsb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psubsw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pminsw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_por:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddsb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddsw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmaxsw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pxor:
        ub_dataflow_parse_xor(instr, dataflow);
        break;
//    case OP_psllw:
//    case OP_pslld:
//    case OP_psllq:
//    case OP_pmuludq:
//    case OP_pmaddwd:
//    case OP_psadbw:
//    case OP_maskmovq:
//    case OP_maskmovdqu:
    case OP_psubb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psubw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psubd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_psubq:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_paddd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
//    case OP_psrldq:
//    case OP_pslldq:
//
    case OP_rol:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_ror:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_rcl:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_rcr:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_shl:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_shr:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_sar:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_not:
        ub_dataflow_parse_same_src(instr, dataflow);
        break;
    case OP_neg:
        ub_dataflow_parse_same_src(instr, dataflow);
        break;
    case OP_mul:
        ub_dataflow_parse_imul(instr, dataflow);
        break;
    case OP_div:
        ub_dataflow_parse_div(instr, dataflow);
        break;
    case OP_idiv:
        ub_dataflow_parse_div(instr, dataflow);
        break;
//    case OP_sldt:
//    case OP_str:
//    case OP_lldt:
//    case OP_ltr:
//    case OP_verr:
//    case OP_verw:
//    case OP_sgdt:
//    case OP_sidt:
//    case OP_lgdt:
//    case OP_lidt:
//    case OP_smsw:
//    case OP_lmsw:
//    case OP_invlpg:
//    case OP_cmpxchg8b:
//    case OP_fxsave32:
//    case OP_fxrstor32:
//    case OP_ldmxcsr:
//    case OP_stmxcsr:
    case OP_lfence:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_mfence:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_clflush:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_sfence:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_prefetchnta:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_prefetcht0:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_prefetcht1:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_prefetcht2:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_prefetch:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_prefetchw:
        ub_dataflow_parse_none(instr, dataflow);
        break;

    case OP_movups:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movss:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movupd:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movsd:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movlps:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movlpd:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
//    case OP_unpcklps:
//    case OP_unpcklpd:
//    case OP_unpckhps:
//    case OP_unpckhpd:
//    case OP_movhps:
//    case OP_movhpd:
    case OP_movaps:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
//    case OP_movapd:
//    case OP_cvtpi2ps:
//    case OP_cvtsi2ss:
//    case OP_cvtpi2pd:
//    case OP_cvtsi2sd:
//    case OP_cvttps2pi:
//    case OP_cvttss2si:
//    case OP_cvttpd2pi:
//    case OP_cvttsd2si:
//    case OP_cvtps2pi:
//    case OP_cvtss2si:
//    case OP_cvtpd2pi:
//    case OP_cvtsd2si:
//    case OP_ucomiss:
//    case OP_ucomisd:
//    case OP_comiss:
//    case OP_comisd:
//    case OP_movmskps:
//    case OP_movmskpd:
//    case OP_sqrtps:
//    case OP_sqrtss:
//    case OP_sqrtpd:
//    case OP_sqrtsd:
//    case OP_rsqrtps:
//    case OP_rsqrtss:
//    case OP_rcpps:
//    case OP_rcpss:
//    case OP_andps:
//    case OP_andpd:
//    case OP_andnps:
//    case OP_andnpd:
//    case OP_orps:
//    case OP_orpd:
//    case OP_xorps:
//    case OP_xorpd:
//    case OP_addps:
//    case OP_addss:
//    case OP_addpd:
//    case OP_addsd:
//    case OP_mulps:
//    case OP_mulss:
//    case OP_mulpd:
//    case OP_mulsd:
//    case OP_cvtps2pd:
//    case OP_cvtss2sd:
//    case OP_cvtpd2ps:
//    case OP_cvtsd2ss:
//    case OP_cvtdq2ps:
//    case OP_cvttps2dq:
//    case OP_cvtps2dq:
//    case OP_subps:
//    case OP_subss:
//    case OP_subpd:
//    case OP_subsd:
//    case OP_minps:
//    case OP_minss:
//    case OP_minpd:
//    case OP_minsd:
//    case OP_divps:
//    case OP_divss:
//    case OP_divpd:
//    case OP_divsd:
//    case OP_maxps:
//    case OP_maxss:
//    case OP_maxpd:
//    case OP_maxsd:
//    case OP_cmpps:
//    case OP_cmpss:
//    case OP_cmppd:
//    case OP_cmpsd:
//    case OP_shufps:
//    case OP_shufpd:
//    case OP_cvtdq2pd:
//    case OP_cvttpd2dq:
//    case OP_cvtpd2dq:
    case OP_nop:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_pause:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//
//    case OP_ins:
//    case OP_rep_ins:
//    case OP_outs:
//    case OP_rep_outs:
    case OP_movs:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_rep_movs:
        ub_dataflow_parse_rep_movs(instr, dataflow);
        break;
    case OP_stos:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_rep_stos:
        ub_dataflow_parse_rep_stos(instr, dataflow);
        break;
//    case OP_lods:
//    case OP_rep_lods:
    case OP_cmps:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_rep_cmps:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_repne_cmps:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_scas:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_rep_scas:
        ub_dataflow_parse_none(instr, dataflow);
        break;
    case OP_repne_scas:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_fadd:
//    case OP_fmul:
//    case OP_fcom:
//    case OP_fcomp:
//    case OP_fsub:
//    case OP_fsubr:
//    case OP_fdiv:
//    case OP_fdivr:
//    case OP_fld:
//    case OP_fst:
//    case OP_fstp:
//    case OP_fldenv:
//    case OP_fldcw:
//    case OP_fnstenv:
//    case OP_fnstcw:
//    case OP_fiadd:
//    case OP_fimul:
//    case OP_ficom:
//    case OP_ficomp:
//    case OP_fisub:
//    case OP_fisubr:
//    case OP_fidiv:
//    case OP_fidivr:
//    case OP_fild:
//    case OP_fist:
//    case OP_fistp:
//    case OP_frstor:
//    case OP_fnsave:
//    case OP_fnstsw:
//
//    case OP_fbld:
//    case OP_fbstp:
//
//    case OP_fxch:
    case OP_fnop:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_fchs:
//    case OP_fabs:
//    case OP_ftst:
//    case OP_fxam:
//    case OP_fld1:
//    case OP_fldl2t:
//    case OP_fldl2e:
//    case OP_fldpi:
//    case OP_fldlg2:
//    case OP_fldln2:
//    case OP_fldz:
//    case OP_f2xm1:
//    case OP_fyl2x:
//    case OP_fptan:
//    case OP_fpatan:
//    case OP_fxtract:
//    case OP_fprem1:
//    case OP_fdecstp:
//    case OP_fincstp:
//    case OP_fprem:
//    case OP_fyl2xp1:
//    case OP_fsqrt:
//    case OP_fsincos:
//    case OP_frndint:
//    case OP_fscale:
//    case OP_fsin:
//    case OP_fcos:
//    case OP_fcmovb:
//    case OP_fcmove:
//    case OP_fcmovbe:
//    case OP_fcmovu:
//    case OP_fucompp:
//    case OP_fcmovnb:
//    case OP_fcmovne:
//    case OP_fcmovnbe:
//    case OP_fcmovnu:
//    case OP_fnclex:
//    case OP_fninit:
//    case OP_fucomi:
//    case OP_fcomi:
//    case OP_ffree:
//    case OP_fucom:
//    case OP_fucomp:
//    case OP_faddp:
//    case OP_fmulp:
//    case OP_fcompp:
//    case OP_fsubrp:
//    case OP_fsubp:
//    case OP_fdivrp:
//    case OP_fdivp:
//    case OP_fucomip:
//    case OP_fcomip:
//
//        // SSE3 instructions :
//    case OP_fisttp:
//    case OP_haddpd:
//    case OP_haddps:
//    case OP_hsubpd:
//    case OP_hsubps:
//    case OP_addsubpd:
//    case OP_addsubps:
//    case OP_lddqu:
//    case OP_monitor:
//    case OP_mwait:
//    case OP_movsldup:
//    case OP_movshdup:
//    case OP_movddup:
//
//        // 3D-Now! instructions :
//    case OP_femms:
//    case OP_unknown_3dnow:
//    case OP_pavgusb:
//    case OP_pfadd:
//    case OP_pfacc:
//    case OP_pfcmpge:
//    case OP_pfcmpgt:
//    case OP_pfcmpeq:
//    case OP_pfmin:
//    case OP_pfmax:
//    case OP_pfmul:
//    case OP_pfrcp:
//    case OP_pfrcpit1:
//    case OP_pfrcpit2:
//    case OP_pfrsqrt:
//    case OP_pfrsqit1:
//    case OP_pmulhrw:
//    case OP_pfsub:
//    case OP_pfsubr:
//    case OP_pi2fd:
//    case OP_pf2id:
//    case OP_pi2fw:
//    case OP_pf2iw:
//    case OP_pfnacc:
//    case OP_pfpnacc:
//    case OP_pswapd:
//
//        // SSSE3 :
    case OP_pshufb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
//    case OP_phaddw:
//    case OP_phaddd:
//    case OP_phaddsw:
//    case OP_pmaddubsw:
//    case OP_phsubw:
//    case OP_phsubd:
//    case OP_phsubsw:
//    case OP_psignb:
//    case OP_psignw:
//    case OP_psignd:
//    case OP_pmulhrsw:
//    case OP_pabsb:
//    case OP_pabsw:
//    case OP_pabsd:
    case OP_palignr:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
//        // SSE4 (incl AMD (SSE4A) and Intel-specific (SSE4.1, SSE4.2) extensions :
    case OP_popcnt:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
//    case OP_movntss:
//    case OP_movntsd:
//    case OP_extrq:
//    case OP_insertq:
    case OP_lzcnt:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
//    case OP_pblendvb:
//    case OP_blendvps:
//    case OP_blendvpd:
    case OP_ptest:
        ub_dataflow_parse_none(instr, dataflow);
        break;
//    case OP_pmovsxbw:
//    case OP_pmovsxbd:
//    case OP_pmovsxbq:
//    case OP_pmovsxwd:
//    case OP_pmovsxwq:
//    case OP_pmovsxdq:
//    case OP_pmuldq:
//    case OP_pcmpeqq:
//    case OP_movntdqa:
//    case OP_packusdw:
//    case OP_pmovzxbw:
//    case OP_pmovzxbd:
//    case OP_pmovzxbq:
//    case OP_pmovzxwd:
//    case OP_pmovzxwq:
//    case OP_pmovzxdq:
//    case OP_pcmpgtq:
    case OP_pminsb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pminsd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pminuw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pminud:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmaxsb:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmaxsd:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmaxuw:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmaxud:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
    case OP_pmulld:
        ub_dataflow_parse_srcdst(instr, dataflow);
        break;
//    case OP_phminposuw:
//    case OP_crc32:
//    case OP_pextrb:
//    case OP_pextrd:
//    case OP_extractps:
//    case OP_roundps:
//    case OP_roundpd:
//    case OP_roundss:
//    case OP_roundsd:
//    case OP_blendps:
//    case OP_blendpd:
//    case OP_pblendw:
//    case OP_pinsrb:
//    case OP_insertps:
//    case OP_pinsrd:
//    case OP_dpps:
//    case OP_dppd:
//    case OP_mpsadbw:
//    case OP_pcmpestrm:
//    case OP_pcmpestri:
//    case OP_pcmpistrm:
//    case OP_pcmpistri:
//
//        // x64 :
//    case OP_movsxd:
//    case OP_swapgs:
//
//        // VMX :
//    case OP_vmcall:
//    case OP_vmlaunch:
//    case OP_vmresume:
//    case OP_vmxoff:
//    case OP_vmptrst:
//    case OP_vmptrld:
//    case OP_vmxon:
//    case OP_vmclear:
//    case OP_vmread:
//    case OP_vmwrite:
//
//        // undocumented :
//    case OP_int1:
//    case OP_salc:
//    case OP_ffreep:
//
//        // AMD SVM :
//    case OP_vmrun:
//    case OP_vmmcall:
//    case OP_vmload:
//    case OP_vmsave:
//    case OP_stgi:
//    case OP_clgi:
//    case OP_skinit:
//    case OP_invlpga:
//
//        // AMD though not part of SVM :
//    case OP_rdtscp:
//
//        // Intel VMX additions :
//    case OP_invept:
//    case OP_invvpid:
//
//        // added in Intel Westmere :
//    case OP_pclmulqdq:
//    case OP_aesimc:
//    case OP_aesenc:
//    case OP_aesenclast:
//    case OP_aesdec:
//    case OP_aesdeclast:
//    case OP_aeskeygenassist:
//
//        // added in Intel Atom :
//    case OP_movbe:
//
//        // added in Intel Sandy Bridge :
    case OP_xgetbv:
        ub_dataflow_parse_xgetbv(instr, dataflow);
        break;
//    case OP_xsetbv:
//    case OP_xsave32:
//    case OP_xrstor32:
//    case OP_xsaveopt32:
//
//        // AVX :
//    case OP_vmovss:
//    case OP_vmovsd:
//    case OP_vmovups:
//    case OP_vmovupd:
//    case OP_vmovlps:
//    case OP_vmovsldup:
//    case OP_vmovlpd:
//    case OP_vmovddup:
//    case OP_vunpcklps:
//    case OP_vunpcklpd:
//    case OP_vunpckhps:
//    case OP_vunpckhpd:
//    case OP_vmovhps:
//    case OP_vmovshdup:
//    case OP_vmovhpd:
//    case OP_vmovaps:
//    case OP_vmovapd:
//    case OP_vcvtsi2ss:
//    case OP_vcvtsi2sd:
//    case OP_vmovntps:
//    case OP_vmovntpd:
//    case OP_vcvttss2si:
//    case OP_vcvttsd2si:
//    case OP_vcvtss2si:
//    case OP_vcvtsd2si:
//    case OP_vucomiss:
//    case OP_vucomisd:
//    case OP_vcomiss:
//    case OP_vcomisd:
//    case OP_vmovmskps:
//    case OP_vmovmskpd:
//    case OP_vsqrtps:
//    case OP_vsqrtss:
//    case OP_vsqrtpd:
//    case OP_vsqrtsd:
//    case OP_vrsqrtps:
//    case OP_vrsqrtss:
//    case OP_vrcpps:
//    case OP_vrcpss:
//    case OP_vandps:
//    case OP_vandpd:
//    case OP_vandnps:
//    case OP_vandnpd:
//    case OP_vorps:
//    case OP_vorpd:
//    case OP_vxorps:
//    case OP_vxorpd:
//    case OP_vaddps:
//    case OP_vaddss:
//    case OP_vaddpd:
//    case OP_vaddsd:
//    case OP_vmulps:
//    case OP_vmulss:
//    case OP_vmulpd:
//    case OP_vmulsd:
//    case OP_vcvtps2pd:
//    case OP_vcvtss2sd:
//    case OP_vcvtpd2ps:
//    case OP_vcvtsd2ss:
//    case OP_vcvtdq2ps:
//    case OP_vcvttps2dq:
//    case OP_vcvtps2dq:
//    case OP_vsubps:
//    case OP_vsubss:
//    case OP_vsubpd:
//    case OP_vsubsd:
//    case OP_vminps:
//    case OP_vminss:
//    case OP_vminpd:
//    case OP_vminsd:
//    case OP_vdivps:
//    case OP_vdivss:
//    case OP_vdivpd:
//    case OP_vdivsd:
//    case OP_vmaxps:
//    case OP_vmaxss:
//    case OP_vmaxpd:
//    case OP_vmaxsd:
//    case OP_vpunpcklbw:
//    case OP_vpunpcklwd:
//    case OP_vpunpckldq:
//    case OP_vpacksswb:
//    case OP_vpcmpgtb:
//    case OP_vpcmpgtw:
//    case OP_vpcmpgtd:
//    case OP_vpackuswb:
//    case OP_vpunpckhbw:
//    case OP_vpunpckhwd:
//    case OP_vpunpckhdq:
//    case OP_vpackssdw:
//    case OP_vpunpcklqdq:
//    case OP_vpunpckhqdq:
//    case OP_vmovd:
//    case OP_vpshufhw:
//    case OP_vpshufd:
//    case OP_vpshuflw:
//    case OP_vpcmpeqb:
//    case OP_vpcmpeqw:
//    case OP_vpcmpeqd:
//    case OP_vmovq:
//    case OP_vcmpps:
//    case OP_vcmpss:
//    case OP_vcmppd:
//    case OP_vcmpsd:
//    case OP_vpinsrw:
//    case OP_vpextrw:
//    case OP_vshufps:
//    case OP_vshufpd:
//    case OP_vpsrlw:
//    case OP_vpsrld:
//    case OP_vpsrlq:
//    case OP_vpaddq:
//    case OP_vpmullw:
//    case OP_vpmovmskb:
//    case OP_vpsubusb:
//    case OP_vpsubusw:
//    case OP_vpminub:
//    case OP_vpand:
//    case OP_vpaddusb:
//    case OP_vpaddusw:
//    case OP_vpmaxub:
//    case OP_vpandn:
//    case OP_vpavgb:
//    case OP_vpsraw:
//    case OP_vpsrad:
//    case OP_vpavgw:
//    case OP_vpmulhuw:
//    case OP_vpmulhw:
//    case OP_vcvtdq2pd:
//    case OP_vcvttpd2dq:
//    case OP_vcvtpd2dq:
//    case OP_vmovntdq:
//    case OP_vpsubsb:
//    case OP_vpsubsw:
//    case OP_vpminsw:
//    case OP_vpor:
//    case OP_vpaddsb:
//    case OP_vpaddsw:
//    case OP_vpmaxsw:
//    case OP_vpxor:
//    case OP_vpsllw:
//    case OP_vpslld:
//    case OP_vpsllq:
//    case OP_vpmuludq:
//    case OP_vpmaddwd:
//    case OP_vpsadbw:
//    case OP_vmaskmovdqu:
//    case OP_vpsubb:
//    case OP_vpsubw:
//    case OP_vpsubd:
//    case OP_vpsubq:
//    case OP_vpaddb:
//    case OP_vpaddw:
//    case OP_vpaddd:
//    case OP_vpsrldq:
//    case OP_vpslldq:
//    case OP_vmovdqu:
//    case OP_vmovdqa:
//    case OP_vhaddpd:
//    case OP_vhaddps:
//    case OP_vhsubpd:
//    case OP_vhsubps:
//    case OP_vaddsubpd:
//    case OP_vaddsubps:
//    case OP_vlddqu:
//    case OP_vpshufb:
//    case OP_vphaddw:
//    case OP_vphaddd:
//    case OP_vphaddsw:
//    case OP_vpmaddubsw:
//    case OP_vphsubw:
//    case OP_vphsubd:
//    case OP_vphsubsw:
//    case OP_vpsignb:
//    case OP_vpsignw:
//    case OP_vpsignd:
//    case OP_vpmulhrsw:
//    case OP_vpabsb:
//    case OP_vpabsw:
//    case OP_vpabsd:
//    case OP_vpalignr:
//    case OP_vpblendvb:
//    case OP_vblendvps:
//    case OP_vblendvpd:
//    case OP_vptest:
//    case OP_vpmovsxbw:
//    case OP_vpmovsxbd:
//    case OP_vpmovsxbq:
//    case OP_vpmovsxwd:
//    case OP_vpmovsxwq:
//    case OP_vpmovsxdq:
//    case OP_vpmuldq:
//    case OP_vpcmpeqq:
//    case OP_vmovntdqa:
//    case OP_vpackusdw:
//    case OP_vpmovzxbw:
//    case OP_vpmovzxbd:
//    case OP_vpmovzxbq:
//    case OP_vpmovzxwd:
//    case OP_vpmovzxwq:
//    case OP_vpmovzxdq:
//    case OP_vpcmpgtq:
//    case OP_vpminsb:
//    case OP_vpminsd:
//    case OP_vpminuw:
//    case OP_vpminud:
//    case OP_vpmaxsb:
//    case OP_vpmaxsd:
//    case OP_vpmaxuw:
//    case OP_vpmaxud:
//    case OP_vpmulld:
//    case OP_vphminposuw:
//    case OP_vaesimc:
//    case OP_vaesenc:
//    case OP_vaesenclast:
//    case OP_vaesdec:
//    case OP_vaesdeclast:
//    case OP_vpextrb:
//    case OP_vpextrd:
//    case OP_vextractps:
//    case OP_vroundps:
//    case OP_vroundpd:
//    case OP_vroundss:
//    case OP_vroundsd:
//    case OP_vblendps:
//    case OP_vblendpd:
//    case OP_vpblendw:
//    case OP_vpinsrb:
//    case OP_vinsertps:
//    case OP_vpinsrd:
//    case OP_vdpps:
//    case OP_vdppd:
//    case OP_vmpsadbw:
//    case OP_vpcmpestrm:
//    case OP_vpcmpestri:
//    case OP_vpcmpistrm:
//    case OP_vpcmpistri:
//    case OP_vpclmulqdq:
//    case OP_vaeskeygenassist:
//    case OP_vtestps:
//    case OP_vtestpd:
//    case OP_vzeroupper:
//    case OP_vzeroall:
//    case OP_vldmxcsr:
//    case OP_vstmxcsr:
//    case OP_vbroadcastss:
//    case OP_vbroadcastsd:
//    case OP_vbroadcastf128:
//    case OP_vmaskmovps:
//    case OP_vmaskmovpd:
//    case OP_vpermilps:
//    case OP_vpermilpd:
//    case OP_vperm2f128:
//    case OP_vinsertf128:
//    case OP_vextractf128:
//
//        // added in Ivy Bridge I believe, and covered by F16C cpuid flag :
//    case OP_vcvtph2ps:
//    case OP_vcvtps2ph:
//
//        // FMA :
//    case OP_vfmadd132ps:
//    case OP_vfmadd132pd:
//    case OP_vfmadd213ps:
//    case OP_vfmadd213pd:
//    case OP_vfmadd231ps:
//    case OP_vfmadd231pd:
//    case OP_vfmadd132ss:
//    case OP_vfmadd132sd:
//    case OP_vfmadd213ss:
//    case OP_vfmadd213sd:
//    case OP_vfmadd231ss:
//    case OP_vfmadd231sd:
//    case OP_vfmaddsub132ps:
//    case OP_vfmaddsub132pd:
//    case OP_vfmaddsub213ps:
//    case OP_vfmaddsub213pd:
//    case OP_vfmaddsub231ps:
//    case OP_vfmaddsub231pd:
//    case OP_vfmsubadd132ps:
//    case OP_vfmsubadd132pd:
//    case OP_vfmsubadd213ps:
//    case OP_vfmsubadd213pd:
//    case OP_vfmsubadd231ps:
//    case OP_vfmsubadd231pd:
//    case OP_vfmsub132ps:
//    case OP_vfmsub132pd:
//    case OP_vfmsub213ps:
//    case OP_vfmsub213pd:
//    case OP_vfmsub231ps:
//    case OP_vfmsub231pd:
//    case OP_vfmsub132ss:
//    case OP_vfmsub132sd:
//    case OP_vfmsub213ss:
//    case OP_vfmsub213sd:
//    case OP_vfmsub231ss:
//    case OP_vfmsub231sd:
//    case OP_vfnmadd132ps:
//    case OP_vfnmadd132pd:
//    case OP_vfnmadd213ps:
//    case OP_vfnmadd213pd:
//    case OP_vfnmadd231ps:
//    case OP_vfnmadd231pd:
//    case OP_vfnmadd132ss:
//    case OP_vfnmadd132sd:
//    case OP_vfnmadd213ss:
//    case OP_vfnmadd213sd:
//    case OP_vfnmadd231ss:
//    case OP_vfnmadd231sd:
//    case OP_vfnmsub132ps:
//    case OP_vfnmsub132pd:
//    case OP_vfnmsub213ps:
//    case OP_vfnmsub213pd:
//    case OP_vfnmsub231ps:
//    case OP_vfnmsub231pd:
//    case OP_vfnmsub132ss:
//    case OP_vfnmsub132sd:
//    case OP_vfnmsub213ss:
//    case OP_vfnmsub213sd:
//    case OP_vfnmsub231ss:
//    case OP_vfnmsub231sd:
//
    case OP_movq2dq:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
    case OP_movdq2q:
        ub_dataflow_parse_src_dst(instr, dataflow);
        break;
//    case OP_fxsave64:
//    case OP_fxrstor64:
//    case OP_xsave64:
//    case OP_xrstor64:
//    case OP_xsaveopt64:
//
//        // added in Intel Ivy Bridge: RDRAND and FSGSBASE cpuid flags :
//    case OP_rdrand:
//    case OP_rdfsbase:
//    case OP_rdgsbase:
//    case OP_wrfsbase:
//    case OP_wrgsbase:
//
//        // coming in the future but adding now since enough details are known :
//    case OP_rdseed:
//
//        // AMD FMA4 :
//    case OP_vfmaddsubps:
//    case OP_vfmaddsubpd:
//    case OP_vfmsubaddps:
//    case OP_vfmsubaddpd:
//    case OP_vfmaddps:
//    case OP_vfmaddpd:
//    case OP_vfmaddss:
//    case OP_vfmaddsd:
//    case OP_vfmsubps:
//    case OP_vfmsubpd:
//    case OP_vfmsubss:
//    case OP_vfmsubsd:
//    case OP_vfnmaddps:
//    case OP_vfnmaddpd:
//    case OP_vfnmaddss:
//    case OP_vfnmaddsd:
//    case OP_vfnmsubps:
//    case OP_vfnmsubpd:
//    case OP_vfnmsubss:
//    case OP_vfnmsubsd:
//
//        // AMD XOP :
//    case OP_vfrczps:
//    case OP_vfrczpd:
//    case OP_vfrczss:
//    case OP_vfrczsd:
//    case OP_vpcmov:
//    case OP_vpcomb:
//    case OP_vpcomw:
//    case OP_vpcomd:
//    case OP_vpcomq:
//    case OP_vpcomub:
//    case OP_vpcomuw:
//    case OP_vpcomud:
//    case OP_vpcomuq:
//    case OP_vpermil2pd:
//    case OP_vpermil2ps:
//    case OP_vphaddbw:
//    case OP_vphaddbd:
//    case OP_vphaddbq:
//    case OP_vphaddwd:
//    case OP_vphaddwq:
//    case OP_vphadddq:
//    case OP_vphaddubw:
//    case OP_vphaddubd:
//    case OP_vphaddubq:
//    case OP_vphadduwd:
//    case OP_vphadduwq:
//    case OP_vphaddudq:
//    case OP_vphsubbw:
//    case OP_vphsubwd:
//    case OP_vphsubdq:
//    case OP_vpmacssww:
//    case OP_vpmacsswd:
//    case OP_vpmacssdql:
//    case OP_vpmacssdd:
//    case OP_vpmacssdqh:
//    case OP_vpmacsww:
//    case OP_vpmacswd:
//    case OP_vpmacsdql:
//    case OP_vpmacsdd:
//    case OP_vpmacsdqh:
//    case OP_vpmadcsswd:
//    case OP_vpmadcswd:
//    case OP_vpperm:
//    case OP_vprotb:
//    case OP_vprotw:
//    case OP_vprotd:
//    case OP_vprotq:
//    case OP_vpshlb:
//    case OP_vpshlw:
//    case OP_vpshld:
//    case OP_vpshlq:
//    case OP_vpshab:
//    case OP_vpshaw:
//    case OP_vpshad:
//    case OP_vpshaq:
//
//        // AMD TBM :
//    case OP_bextr:
//    case OP_blcfill:
//    case OP_blci:
//    case OP_blcic:
//    case OP_blcmsk:
//    case OP_blcs:
//    case OP_blsfill:
//    case OP_blsic:
//    case OP_t1mskc:
//    case OP_tzmsk:
//
//        // AMD LWP :
//    case OP_llwpcb:
//    case OP_slwpcb:
//    case OP_lwpins:
//    case OP_lwpval:
//
//        // Intel BMI1 :
//        // (includes non-immed form of OP_bextr) :
//    case OP_andn:
//    case OP_blsr:
//    case OP_blsmsk:
//    case OP_blsi:
//    case OP_tzcnt:
//
//        // Intel BMI2 :
//    case OP_bzhi:
//    case OP_pext:
//    case OP_pdep:
//    case OP_sarx:
//    case OP_shlx:
//    case OP_shrx:
//    case OP_rorx:
//    case OP_mulx:
//
//        // Intel Safer Mode Extensions :
//    case OP_getsec:
//
//        // Misc Intel additions :
//    case OP_vmfunc:
//    case OP_invpcid:
//
//        // Intel TSX :
//    case OP_xabort:
//    case OP_xbegin:
//    case OP_xend:
//    case OP_xtest:
//
//        // AVX2
//    case OP_vpgatherdd:
//    case OP_vpgatherdq:
//    case OP_vpgatherqd:
//    case OP_vpgatherqq:
//    case OP_vgatherdps:
//    case OP_vgatherdpd:
//    case OP_vgatherqps:
//    case OP_vgatherqpd:
//    case OP_vbroadcasti128:
//    case OP_vinserti128:
//    case OP_vextracti128:
//    case OP_vpmaskmovd:
//    case OP_vpmaskmovq:
//    case OP_vperm2i128:
//    case OP_vpermd:
//    case OP_vpermps:
//    case OP_vpermq:
//    case OP_vpermpd:
//    case OP_vpblendd:
//    case OP_vpsllvd:
//    case OP_vpsllvq:
//    case OP_vpsravd:
//    case OP_vpsrlvd:
//    case OP_vpsrlvq:
//    case OP_vpbroadcastb:
//    case OP_vpbroadcastw:
//    case OP_vpbroadcastd:
//    case OP_vpbroadcastq:
//
//        // Added in Intel Skylake :
//    case OP_xsavec32:
//    case OP_xsavec64:
//
//        // Intel ADX :
//    case OP_adox:
//    case OP_adcx:
//
    default:
        ub_dataflow_parse_undefined(instr, dataflow);
    }

}
