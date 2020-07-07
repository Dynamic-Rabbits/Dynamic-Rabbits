/*
 * @file ib_option.c
 */

#include "ib_option.h"
#include "utility_bunny.h"

// Indexes of options
#define CONC_BIT 0

#define OPCODE_BIT 1

#define SIZE_BIT 2

#define ADDRESS_GEN_BIT 3

#define FLAG_BIT 4

#define PC_BIT 5

#define LOC_TYPE_BIT 6
#define LOC_SIZE_BIT 7

#define OPND_STORE_FULL_BIT 8
#define ADDRESS_GEN_FULL_BIT 9

#define ADDR_OPND_BIT 10
#define REG_OPND_BIT 11
#define IMMED_OPND_BIT 12

/***********************************************************************
 * Implementation
 */

bool ib_options_is_addr_opnd_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, ADDR_OPND_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_reg_opnd_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, REG_OPND_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_immed_opnd_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, IMMED_OPND_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_conc_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, CONC_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_opcode_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, OPCODE_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_opnd_count_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, SIZE_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_addr_gen_mode_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, ADDRESS_GEN_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_flag_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, FLAG_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_pc_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, PC_BIT, true);

#ifdef DEBUG_CHECK_ASSESS

    return true;

#else
    return ub_byte_are_all_bit_set(options, 1, bit_check);

#endif

}

bool ib_options_is_loc_type_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, LOC_TYPE_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_loc_size_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, LOC_SIZE_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_full_opnd_storage_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, OPND_STORE_FULL_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);
}

bool ib_options_is_full_address_gen_enabled(IB_INSTRUM_OPT options) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, ADDRESS_GEN_FULL_BIT, true);

    return ub_byte_are_all_bit_set(options, 1, bit_check);

}

