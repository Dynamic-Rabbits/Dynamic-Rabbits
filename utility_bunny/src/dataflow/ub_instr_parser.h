/*
 * instr_parser.h
 *
 *  Created on: 8 Dec 2018
 *      Author: john
 */

#ifndef DATAFLOW_INSTR_PARSER_H_
#define DATAFLOW_INSTR_PARSER_H_

#include "ub_instr_flows.h"

void ub_dataflow_parse_cpuid(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_untaint_1dst(instr_t *instr,
        ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_imul(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_div(instr_t *instr, ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_cmpxchg(instr_t *instr,
        ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_2src_2dst(instr_t *instr,
        ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_shiftd(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_none(instr_t *instr,
        ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_rdtsc(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_xgetbv(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_enter(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_leave(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_srcdst(instr_t *instr,
        ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_xadd(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_loop(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_conditional_src_dst(instr_t *instr,
        ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_src_dst(instr_t *instr,
        ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_rep_movs(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_rep_stos(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_mov_st(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_same_src(instr_t *instr,
        ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_pop(instr_t *instr, ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_push(instr_t *instr,
        ub_instr_dataflow_t *instr_dataflow);

void ub_dataflow_parse_popa(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_pusha(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_call(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_lea(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_xor(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_pushf(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_xchg(instr_t *instr, ub_instr_dataflow_t *dataflow);

void ub_dataflow_parse_undefined(instr_t *instr, ub_instr_dataflow_t *dataflow);

#endif /* DATAFLOW_INSTR_PARSER_H_ */
