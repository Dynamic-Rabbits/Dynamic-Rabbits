/**
 *  @author John F.X. Galea
 */

#include "ib_slot.h"
#include <stddef.h>
#include "../ib_data.h"
#include "../tls_access/ib_tls_access.h"

/***********************************************************************
 * Prototypes
 */

static opnd_t ib_determine_slot_opnd_size(reg_id_t data_reg, size_t opnd_size,
        size_t ofst);

static unsigned int ib_calculate_comp_offset(ub_opnd_access_t *opnd_access,
        unsigned int field_offset);

static opnd_t ib_create_comp_slot_field_access(reg_id_t data_reg,
        ub_opnd_access_t *opnd_access, unsigned int field_offset);

/***********************************************************************
 * Implementation
 */

bool ib_is_opnd_slot_valid(ub_opnd_field_t opnd_field) {
    return UB_SRC_OPND_1 <= opnd_field && opnd_field < UB_DST_OPND_END;
}

bool ib_is_comp_slot_valid(ub_comp_field_t comp_slot) {
    return UB_COMP_1 <= comp_slot && comp_slot <= UB_COMP_5;
}

/**
 *  Calculates offset to field in a component slot.
 *
 *  @param comp_access_slot The operand slot considered for access
 *  @param field_offset The offset value to access a particular field from a ib_opnd_comp_t
 *  struct
 *  @return The calculated offset
 */
static unsigned int ib_calculate_comp_offset(ub_opnd_access_t *opnd_access,
        unsigned int field_offset) {

    unsigned int opnd_offset = offsetof(ib_per_thread_t, components)
            + (opnd_access->opnd_field * sizeof(ib_comp_data_t) * 5);

    unsigned int comp_offset = opnd_offset
            + (sizeof(ib_comp_data_t) * opnd_access->comp_field);

    return comp_offset + field_offset;
}

/**
 *	Enables access to a field in a ib_opnd_comp_t struct
 *
 *  @param data_reg The register containing a pointer to instrumentation data
 *  @param comp_access_slot The component slots considered for access
 *  @param field_offset The offset value to access a particular field from a ib_opnd_comp_t
 *  struct
 *  @return An opnd that denotes the mem access ptr
 */
static opnd_t ib_create_comp_slot_field_access(reg_id_t data_reg,
        ub_opnd_access_t *opnd_access, unsigned int field_offset) {

    if (ib_is_opnd_slot_valid(opnd_access->opnd_field)
            && ib_is_comp_slot_valid(opnd_access->comp_field)) {

        unsigned int comp_offset = ib_calculate_comp_offset(opnd_access,
                field_offset);

        return OPND_CREATE_MEMPTR(data_reg, comp_offset);
    }

    DR_ASSERT(false);

    return opnd_create_null();
}

/**
 *  A helper function to retrieve the mem reference size of the opnd.
 *
 *  @param data_reg The register containing a pointer to instrumentation data
 *  @param opnd_size The opnd size of the mem reference
 *  @param offset The offset value
 *  @return An opnd that denotes the mem access ptr with the appropriate reference
 *  size
 */
static opnd_t ib_determine_slot_opnd_size(reg_id_t data_reg, size_t opnd_size,
        size_t ofst) {

    switch (opnd_size) {

    case 16:
        return opnd_create_base_disp(data_reg, DR_REG_NULL, 0, ofst, OPSZ_16);

    case 8:
        return OPND_CREATE_MEM64(data_reg, ofst);

    case 4:
        return OPND_CREATE_MEM32(data_reg, ofst);

    case 2:
        return OPND_CREATE_MEM16(data_reg, ofst);

    case 1:
        return OPND_CREATE_MEM8(data_reg, ofst);

    default:
        return OPND_CREATE_MEMPTR(data_reg, ofst);
    }
}

bool ib_get_fast_slot(ub_opnd_access_t *opnd_access, opnd_t *fast_opnd) {

    if (opnd_access->comp_field == UB_COMP_1) {

        if (opnd_access->opnd_field <= UB_SRC_OPND_3) {

            int index = IB_RAW_SLOT_SRC_OPND_DATA_1 + opnd_access->opnd_field;
            DR_ASSERT(
                    index >= IB_RAW_SLOT_SRC_OPND_DATA_1 && index <= IB_RAW_SLOT_SRC_OPND_DATA_3);
            *fast_opnd = ib_tls_get_raw_slot_opnd(index);

            return true;
        }

        if (opnd_access->opnd_field >= UB_DST_OPND_1
                && opnd_access->opnd_field <= UB_DST_OPND_3) {

            int offset = opnd_access->opnd_field - UB_DST_OPND_1;
            DR_ASSERT(offset >= 0);

            int index = IB_RAW_SLOT_DST_OPND_DATA_1 + offset;
            DR_ASSERT(
                    index >= IB_RAW_SLOT_DST_OPND_DATA_1 && index <= IB_RAW_SLOT_DST_OPND_DATA_3);
            *fast_opnd = ib_tls_get_raw_slot_opnd(index);

            return true;
        }
    }

    return false;
}

opnd_t ib_get_slow_comp_slot_opnd(reg_id_t data_reg,
        ub_opnd_access_t *comp_access_slot) {

    opnd_t fast_opnd;
    bool succ = ib_get_fast_slot(comp_access_slot, &fast_opnd);

    if (succ)
        return fast_opnd;

    return ib_create_comp_slot_field_access(data_reg, comp_access_slot,
            offsetof(ib_comp_data_t, opnd));
}

opnd_t ib_get_comp_slot_conc(reg_id_t data_reg, size_t opnd_size,
        ub_opnd_access_t *comp_access_slot, size_t disp) {

    return ib_determine_slot_opnd_size(data_reg, opnd_size,
            ib_calculate_comp_offset(comp_access_slot,
                    offsetof(ib_comp_data_t, conc)) + disp);
}

opnd_t ib_get_comp_slot_type(reg_id_t data_reg,
        ub_opnd_access_t *comp_access_slot) {

    return ib_create_comp_slot_field_access(data_reg, comp_access_slot,
            offsetof(ib_comp_data_t, type));
}

opnd_t ib_get_comp_slot_size(reg_id_t data_reg,
        ub_opnd_access_t *comp_access_slot) {

    return ib_create_comp_slot_field_access(data_reg, comp_access_slot,
            offsetof(ib_comp_data_t, size));
}
