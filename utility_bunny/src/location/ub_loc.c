/*
 *  @file ub_loc_.c
 *  @author John F.X. Galea
 */

#include "ub_loc.h"
#include "../register/ub_register.h"

DR_EXPORT void ub_loc_populate(ub_loc_info_t *loc_info, uintptr_t opnd,
        uintptr_t size, loc_t type) {
    loc_info->opnd = opnd;
    loc_info->size = size;
    loc_info->type = type;
}

DR_EXPORT bool ub_is_supported_loc(opnd_t *opnd) {

    ub_loc_info_t loc_info;
    ub_get_loc_info(&loc_info, opnd);

    switch (loc_info.type) {

    case UB_REG_TYPE:
    case UB_MEM_TYPE:
    case UB_IMMED_TYPE:
    case UB_PC_TYPE:
        return true;
    }

    return false;
}

DR_EXPORT void ub_get_loc_info(ub_loc_info_t *loc_info, opnd_t *opnd) {

    // Set out data with default NULL values.
    // Set to -1 to indicate error as 0 is more likely to be mapped.
    // TODO Design SMELL!!!!!!!! FIX ME!!!!!!!!!!!!!!!!!!!!! FIX ME!!!!!!!!!!!!!
    loc_info->opnd = (uintptr_t) -1;
    loc_info->type = (loc_t) 0;
    loc_info->size = 0;

    if (opnd_is_memory_reference(*opnd)) {

        loc_info->opnd = (uintptr_t) NULL;
        loc_info->type = UB_MEM_TYPE;

        opnd_size_t size_opnd = opnd_get_size(*opnd);
        loc_info->size = opnd_size_in_bytes(size_opnd);

    } else if (ub_opnd_is_reg(opnd)) {

        reg_id_t reg_id = opnd_get_reg(*opnd);

        // Retrieve the ID of the register by calling the opnd_get_reg function.
        loc_info->opnd = (uintptr_t) reg_id;
        loc_info->type = UB_REG_TYPE;
        opnd_size_t size_opnd = opnd_get_size(*opnd);
        loc_info->size = opnd_size_in_bytes(size_opnd);

    } else if (opnd_is_immed_int(*opnd)) {

        loc_info->opnd = (ptr_int_t) opnd_get_immed_int(*opnd);
        loc_info->type = UB_IMMED_TYPE;
        opnd_size_t size_opnd = opnd_get_size(*opnd);
        loc_info->size = opnd_size_in_bytes(size_opnd);

    } else if (opnd_is_pc(*opnd)) {

        loc_info->opnd = (ptr_int_t) opnd_get_pc(*opnd);
        loc_info->type = UB_PC_TYPE;
        opnd_size_t size_opnd = opnd_get_size(*opnd);
        loc_info->size = opnd_size_in_bytes(size_opnd);

    }
}

