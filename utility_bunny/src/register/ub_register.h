/**
 *  @file register.h
 *	@brief Provides useful functionality for dealing with registers
 *  @author John F.X. Galea
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"

/**
 *  Checks whether the register is supported by the dynamic bunnies.
 *
 *  @return True if supported
 */
DR_EXPORT bool ub_opnd_is_reg(opnd_t *opnd);

/**
 *  Retrieves the size of the register
 *
 *  @param reg_id The ID of the register given by DR
 *  @return The size of the register
 */
DR_EXPORT size_t ub_get_reg_size(reg_id_t reg_id);

/**
 *  Gets the ID of the reg's byte at a given index.
 *
 *  @param reg_id The register ID
 *  @param byte_index The index of the byte within the register
 *  @return The byte id of the register
 */
DR_EXPORT unsigned int ub_get_byte_id(reg_id_t reg_id, unsigned int byte_index);

/**
 *  Gets the register ID of the byte passed as param. Note the ID of the largest possible
 *  register is given.
 *
 *  @param reg_byte_id The byte ID to consider for obtaining the main register ID
 *  @return The ID of the register which contains the byte referenced by reg_byte_id
 */
DR_EXPORT reg_id_t ub_get_reg_id(unsigned int reg_byte_id);

/**
 *  Gets the register ID of the byte passed as param
 *
 *  @param reg_byte_id The byte ID to consider for obtaining the main register ID
 *  @return The ID of the register which contains the byte referenced by reg_byte_id
 */
DR_EXPORT size_t ub_get_reg_byte_index(unsigned int reg_byte_id);

/**
 *  Modifies the value of a byte inside a register. Mainly used to change the value of a register where the value is
 *  visible to the application.
 *
 *  @param mcontext The current machine context
 *  @param val The byte value to write
 *  @param reg_byte_id
 *
 */
DR_EXPORT bool ub_write_reg_byte(dr_mcontext_t *mcontext, unsigned int reg_byte_id, byte val);

#endif /* REGISTER_H_ */
