/*
 * register.c
 *
 *      Author: john
 */

#include "ub_register.h"

#include "dr_api.h"
#include "drmgr.h"
#include "drutil.h"
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include "../byte/ub_byte_array.h"

#define REG_SIZE 16

static bool ub_is_reg_supported(reg_id_t reg_id) {

    return (reg_is_gpr(reg_id) || reg_is_xmm(reg_id));
}

bool ub_opnd_is_reg(opnd_t *opnd) {

    if (opnd_is_reg(*opnd))
        return ub_is_reg_supported(opnd_get_reg(*opnd));

    return false;
}

DR_EXPORT size_t ub_get_reg_size(reg_id_t reg_id) {

    opnd_t reg_opnd = opnd_create_reg(reg_id);
    opnd_size_t size_opnd = opnd_get_size(reg_opnd);

    return opnd_size_in_bytes(size_opnd);
}

DR_EXPORT unsigned int ub_get_byte_id(reg_id_t reg_id, unsigned int byte_index) {

    DR_ASSERT(ub_is_reg_supported(reg_id));

    switch (reg_id) {

    case DR_REG_SPL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_SP:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_ESP:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XSP * REG_SIZE) + byte_index;

    case DR_REG_BPL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_BP:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_EBP:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XBP * REG_SIZE) + byte_index;

    case DR_REG_AL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_AX:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_EAX:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XAX * REG_SIZE) + byte_index;

    case DR_REG_BL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_BX:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_EBX:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XBX * REG_SIZE) + byte_index;

    case DR_REG_CL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_CX:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_ECX:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XCX * REG_SIZE) + byte_index;

    case DR_REG_DL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_DX:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_EDX:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XDX * REG_SIZE) + byte_index;

    case DR_REG_DIL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_DI:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_EDI:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XDI * REG_SIZE) + byte_index;

    case DR_REG_SIL:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_SI:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_ESI:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_XSI * REG_SIZE) + byte_index;

    case DR_REG_R8L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R8W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R8D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R8 * REG_SIZE) + byte_index;

    case DR_REG_R9L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R9W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R9D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R9 * REG_SIZE) + byte_index;

    case DR_REG_R10L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R10W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R10D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R10 * REG_SIZE) + byte_index;

    case DR_REG_R11L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R11W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R11D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R11 * REG_SIZE) + byte_index;

    case DR_REG_R12L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R12W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R12D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R12 * REG_SIZE) + byte_index;

    case DR_REG_R13L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R13W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R13D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R13 * REG_SIZE) + byte_index;

    case DR_REG_R14L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R14W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R14D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R14 * REG_SIZE) + byte_index;

    case DR_REG_R15L:
        DR_ASSERT(byte_index == 0);
        /* no break */
    case DR_REG_R15W:
        DR_ASSERT(byte_index < 2);
        /* no break */
    case DR_REG_R15D:
        DR_ASSERT(byte_index < 4);
        return (DR_REG_R15 * REG_SIZE) + byte_index;

    case DR_REG_AH:
        DR_ASSERT(byte_index == 0);
        return (DR_REG_XAX * REG_SIZE) + 1;

    case DR_REG_BH:
        DR_ASSERT(byte_index == 0);
        return (DR_REG_XBX * REG_SIZE) + 1;

    case DR_REG_CH:
        DR_ASSERT(byte_index == 0);
        return (DR_REG_XCX * REG_SIZE) + 1;

    case DR_REG_DH:
        DR_ASSERT(byte_index == 0);
        return (DR_REG_XDX * REG_SIZE) + 1;

    default:
        return (reg_id * REG_SIZE) + byte_index;
    }
}

DR_EXPORT reg_id_t ub_get_reg_id(unsigned int reg_byte_id) {

    unsigned int id = reg_byte_id / REG_SIZE;
    return (reg_id_t) id;
}

DR_EXPORT size_t ub_get_reg_byte_index(unsigned int reg_byte_id) {

    unsigned int index = reg_byte_id % REG_SIZE;
    return (size_t) index;
}

DR_EXPORT bool ub_write_reg_byte(dr_mcontext_t *mcontext,
        unsigned int reg_byte_id, byte val) {

    reg_id_t reg_id = ub_get_reg_id(reg_byte_id);
    size_t reg_index = ub_get_reg_byte_index(reg_byte_id);
    uintptr_t reg_val = reg_get_value(reg_id, mcontext);

    return ub_modify_byte_of_value(reg_val, ub_get_reg_size(reg_id), val,
            reg_index);
}
