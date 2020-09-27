/*
 * ub_in_out_analysis.h
 *
 *  Created on: 25 Nov 2018
 *      Author: john
 */

#ifndef DATA_FLOW_UB_IN_OUT_ANALYSIS_H_
#define DATA_FLOW_UB_IN_OUT_ANALYSIS_H_

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include  <stdint.h>
#include  "../datastructs/lists/ub_list.h"
#include  "../location/ub_loc.h"

typedef struct {

    /** Stores list of opnds **/
    void *reg_list;
    void *mem_list;
    void *mem_base_list;
} ub_in_out_set_t;

typedef struct {

    /** Stores list of opnds **/
    ub_in_out_set_t in_set;
    ub_in_out_set_t out_set;
} ub_in_out_opnds_t;

void ub_init_in_out_set(ub_in_out_set_t *set);
void ub_init_in_out_opnds(ub_in_out_opnds_t *in_out_opnds);

void ub_delete_in_out_set(ub_in_out_set_t *set);
void ub_delete_in_out_opnds(ub_in_out_opnds_t *in_out_opnds);

void ub_get_in_out_set(ub_in_out_set_t *set, instrlist_t *bb);
void ub_get_out_set_of_regs(ub_in_out_set_t *set, instrlist_t *bb);
void ub_get_in_out_opnds(ub_in_out_opnds_t *in_out_opnds, instrlist_t *bb);

bool ub_is_opnd_in_out_set(ub_in_out_set_t *set, opnd_t *opnd,
        ub_loc_info_t *loc_info);

size_t ub_size_in_out_set(ub_in_out_set_t *set);
size_t ub_size_in_out_opnds(ub_in_out_opnds_t *in_out_opnds);

#endif /* DATA_FLOW_UB_IN_OUT_ANALYSIS_H_ */
