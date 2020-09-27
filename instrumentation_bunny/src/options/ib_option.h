/**
 *  @file ib_option.h
 *  @brief Header file for handing option settings of the instrumenter.
 *  @author: John F.X. Galea
 */

#ifndef IB_OPTION_H_
#define IB_OPTION_H_

#include "../ib_data.h"

bool ib_options_is_addr_opnd_enabled(IB_INSTRUM_OPT options);
bool ib_options_is_reg_opnd_enabled(IB_INSTRUM_OPT options);
bool ib_options_is_immed_opnd_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should store conc data.
 *  @param options options for instrumentation.
 *  @returns if conc flag is set.
 */
bool ib_options_is_conc_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should store conc data.
 *
 *  @param options options for instrumentation.
 *  @returns if opcode flag is set.
 */
bool ib_options_is_opcode_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should store operand size data.
 *
 *  @param options options for instrumentation.
 *  @returns if opnd size flag is set.
 */
bool ib_options_is_opnd_count_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should be in addr gen mode.
 *
 *  @param options options for instrumentation.
 *  @returns if addr gen mode flag is set.
 */
bool ib_options_is_addr_gen_mode_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should store flag data.
 *
 *  @param options options for instrumentation.
 *  @returns if the `flag` flag is set.
 */
bool ib_options_is_flag_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should store PC data.
 *
 *  @param options options for instrumentation.
 *  @returns if the PC flag is set.
 */
bool ib_options_is_pc_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should store Type data.
 *
 *  @param options options for instrumentation.
 *  @returns if the LOC TYPE is set.
 */
bool ib_options_is_loc_type_enabled(IB_INSTRUM_OPT options);

/**
 *  Checks whether the intrumenter should store Size data.
 *
 *  @param options options for instrumentation.
 *  @returns if the LOC SIZE flag is set.
 */
bool ib_options_is_loc_size_enabled(IB_INSTRUM_OPT options);


/**
 *  Checks whether the intrumenter should store partial data.
 *
 *  @param options options for instrumentation.
 *  @returns if the LOC SIZE flag is set.
 */
bool ib_options_is_full_opnd_storage_enabled(IB_INSTRUM_OPT options);


/**
 *  Checks whether the intrumenter should store partial data.
 *
 *  @param options options for instrumentation.
 *  @returns if the LOC SIZE flag is set.
 */
bool ib_options_is_full_address_gen_enabled(IB_INSTRUM_OPT options);

#endif /* SRC_INSTRUMENTATION_UB_INSTRUM_OPTION_H_ */
