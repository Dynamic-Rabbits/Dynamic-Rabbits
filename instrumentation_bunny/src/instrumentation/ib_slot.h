/**
 *  @file ib_slot.h
 *  @brief Functions responsible for interacting with operand and component slots
 *  in the ib_opnd_data_t struct.
 *  @author John F.X. Galea
 */

#ifndef IB_OPND_SLOT_H_
#define IB_OPND_SLOT_H_

#include "dr_api.h"
#include "drmgr.h"
#include "dr_defines.h"

#include "utility_bunny.h"

#include "../ib_defines.h"

/**
 * Gets a Mem Ptr to the opnd field found in a component slot
 *
 * @param data_reg Register containing a pointer to instrumentation data.
 * @param comp_access_slot The component slot considered for accessing.
 * @return A Mem Ptr operand that refers to the opnd in a component slot.
 */

bool ib_get_fast_slot(ub_opnd_access_t *opnd_access,
        opnd_t *fast_opnd);

opnd_t ib_get_slow_comp_slot_opnd(reg_id_t data_reg,
		ub_opnd_access_t *opnd_access);

/**
 *  Gets a Mem Ptr to conc field found in a component slot
 *
 *  @param data_reg Register containing a pointer to instrumentation.
 *  @param comp_access_slot The component slot considered for accessing.
 *  @param disp Adds displacement to aid in stepwise storing concrete values.
 *  @return A Mem Ptr operand that refers to a conc byte in a component slot.
 */
opnd_t ib_get_comp_slot_conc(reg_id_t data_reg, size_t opnd_size,
		ub_opnd_access_t * opnd_access, size_t disp);

/**
 *  Gets a Mem Ptr to the type field found in a component slot
 *
 * @param data_reg Register containing a pointer to instrumentation data.
 * @param comp_access_slot The component slot considered for accessing.
 * @return A Mem Ptr operand that refers to type in a component slot.
 */
opnd_t ib_get_comp_slot_type(reg_id_t data_reg,
        ub_opnd_access_t *opnd_access);

/**
 * Gets a Mem Ptr to the size field found in a component slot
 *
 * @param data_reg Register containing a pointer to instrumentation data.
 * @param comp_access_slot The component slot considered for accessing.
 * @return A Mem Ptr operand that refers to size field in a component slot.
 */
opnd_t ib_get_comp_slot_size(reg_id_t data_reg,
        ub_opnd_access_t *opnd_access);

/**
 *  Determines whether the passed opnd slot is valid (within range)
 *  @param opnd_slot The opnd slot to check
 *  @return Returns true if opnd_slot is valid
 */
bool ib_is_opnd_slot_valid(ub_opnd_field_t opnd_field);

/**
 *  Determines whether the passed comp slot is valid (within range)
 *  @param comp_slot The comp slot to check
 *  @return Returns true if comp_slot is valid
 */
bool ib_is_comp_slot_valid(ub_comp_field_t comp_field);

#endif
