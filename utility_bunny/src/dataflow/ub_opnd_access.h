/*
 * ub_slot.c
 *
 *  Created on: 5 Aug 2019
 *      Author: john
 */

#ifndef DATAFLOW_UB_OPND_ACCESS_H_
#define DATAFLOW_UB_OPND_ACCESS_H_


#include "dr_defines.h"
#include "dr_api.h"

/**
 *  Do not change numbers, we use them for array indexes.
 */
typedef enum {
    UB_SRC_OPND_1 = 0,
    UB_SRC_OPND_2 = 1,
    UB_SRC_OPND_3 = 2,
    UB_SRC_OPND_4 = 3,
    UB_SRC_OPND_5 = 4,
    UB_SRC_OPND_6 = 5,
    UB_SRC_OPND_7 = 6,
    UB_SRC_OPND_8 = 7,

    UB_DST_OPND_1 = 8,
    UB_DST_OPND_2 = 9,
    UB_DST_OPND_3 = 10,
    UB_DST_OPND_4 = 11,
    UB_DST_OPND_5 = 12,
    UB_DST_OPND_6 = 13,
    UB_DST_OPND_7 = 14,
    UB_DST_OPND_8 = 15,
    UB_DST_OPND_END = 16,
} ub_opnd_field_t;

#define UB_NUM_OF_SRC_FIELDS UB_DST_OPND_1
#define UB_NUM_OF_DST_FIELDS UB_DST_OPND_END - UB_DST_OPND_1

/**
 *  Component slots are used for storing effective operands as well as the sub components
 *  used for address generation.
 *
 *  Do not change numbers, we use them for array indexes.
 */
typedef enum {
    UB_COMP_1 = 0,
    UB_COMP_2 = 1,
    UB_COMP_3 = 2,
    UB_COMP_4 = 3,
    UB_COMP_5 = 4,
} ub_comp_field_t;

/**
 *  A struct that defines the two slots to access an operand's component.
 *
 *  opnd_access(opnd_slot).comp_access(comp_slot)
 *
 *  @var opnd_slot The opnd slot for accessing
 *  @var comp_slot The comp slot for accessing.
 */
typedef struct {

    ub_opnd_field_t opnd_field;
    ub_comp_field_t comp_field;
} ub_opnd_access_t;

opnd_t ub_opnd_access_get_opnd(instr_t *instr, ub_opnd_access_t *opnd_access);

#endif /* DATAFLOW_UB_SLOT_C_ */
