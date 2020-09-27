/*
 * ub_instr_flows.h
 *
 *  Created on: 8 Dec 2018
 *      Author: john
 */

#ifndef DATAFLOW_UB_INSTR_FLOWS_H_
#define DATAFLOW_UB_INSTR_FLOWS_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "ub_opnd_access.h"

typedef struct {
    uint dst;
    uint num_srcs;
    uint srcs[UB_NUM_OF_SRC_FIELDS];
} ub_dataflow_t;

typedef struct {
    bool supported;
    ub_opnd_access_t opnd_access[UB_NUM_OF_DST_FIELDS + UB_NUM_OF_SRC_FIELDS];
    uint num_opnds;
    uint num_flows;
    ub_dataflow_t dataflow[UB_NUM_OF_DST_FIELDS];
} ub_instr_dataflow_t;


void ub_dataflow_get_info(instr_t *instr, ub_instr_dataflow_t *dataflow);

size_t ub_dataflow_num_flows(ub_instr_dataflow_t *dataflow_instr);

opnd_t ub_dataflow_get_flow_dst(instr_t *instr, ub_instr_dataflow_t *dataflow_instr_info,
        size_t flow_index);

ub_opnd_access_t ub_dataflow_get_flow_dst_access(ub_instr_dataflow_t *dataflow_instr_info,
        size_t flow_index);

size_t ub_dataflow_flow_num_srcs(ub_instr_dataflow_t *dataflow_instr,
        size_t flow_index);

opnd_t ub_dataflow_get_flow_src(instr_t *instr, ub_instr_dataflow_t *dataflow_instr,
        size_t flow_index, size_t src_index);

ub_opnd_access_t ub_dataflow_get_flow_src_access(ub_instr_dataflow_t *dataflow_instr_info,
        size_t flow_index, size_t src_index);

bool ub_dataflow_is_supported(ub_instr_dataflow_t *dataflow_instr);

#endif /* DATAFLOW_UB_INSTR_FLOWS_H_ */
