/**
 *  @file ub_loc_.c
 *  @brief Provides information related to a memory location.
 *  @author John F.X. Galea
 */

#ifndef UB_LOC_H_
#define UB_LOC_H_

#include "dr_api.h"
#include "dr_defines.h"
#include <stdint.h>

/**
 * @var loc_t A type to distinguish between operands.
 *
 * REG_TYPE denotes a location of a register
 * MEM_TYPE denotes a location of a memory
 * IMMED_TYPE denotes a location of a immediate address
 *
 * TODO LEA is not really a mem deref type. Create this type, ensuring that it
 * is compatible with current code.
 */
typedef unsigned char loc_t;

#define UB_REG_TYPE 'R'
#define UB_MEM_TYPE 'M'
#define UB_IMMED_TYPE 'I'
#define UB_PC_TYPE 'P'

/**
 *  @struct loc_info_t
 *
 *  Information of a location
 *
 *  @var loc_info_t::opnd
 *  The value that represents the opnd. Could be a reg_id or an effective addr
 *
 *	@var loc_info_t::size
 *	The size of the operand. E.g. EAX is of size 4 bytes
 *
 *	@var loc_info_t::type
 *	The type of operand. Is it a reg or a addr
 */
typedef struct {
    uintptr_t opnd;
    uintptr_t size;
    loc_t type;
} ub_loc_info_t;

/**
 *  Initialises a loc info struct.
 *
 *  @param out_loc_info The loc info struct to initialise
 *  @param opnd The opnd to set
 *  @param size The size to set
 *  @param type The type to set
 */
DR_EXPORT void ub_loc_populate(ub_loc_info_t *out_opnd_info, uintptr_t opnd,
        uintptr_t size, loc_t type);

DR_EXPORT void ub_get_loc_info(ub_loc_info_t *loc_info, opnd_t *opnd);

DR_EXPORT bool ub_is_supported_loc(opnd_t *opnd);

#endif
