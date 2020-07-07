/**
 *  @file instrumentation_bunny.h
 *  @brief The instrumentation Bunny is useful for instrumenting instructions. Multiple
 *  bunnies can hook instr, where the instrumentation bunny will ensure minimal context
 *  switching.
 *  @author John F.X. Galea
 */

#ifndef SLICER_BUNNY_H_
#define SLICER_BUNNY_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"

#include "utility_bunny.h"

#include <stdint.h>

/**
 * Initialises slicer.
 */
DR_EXPORT void *sb_init();

/**
 *  Destroys slicer.
 *
 *  @param slicer The slicer to destroy.
 */
DR_EXPORT void sb_exit(void *slicer);

/**
 *  Registers a module slicer. It tracks instructions which need to be sliced.
 *
 *  @param module_list A file containing a list of names of modules to slice.
 */
DR_EXPORT void sb_register_module_slicer(void *slicer, file_t module_list);

/**
 *  Registers a PC slicer. It tracks PCs to which need to be sliced.
 *
 *  @param pc_list A file containing a list of names of modules to slice.
 */
DR_EXPORT void sb_register_pc_slicer(void *slicer, file_t pc_list);

/**
 *  Determines whether to slice an instruction.
 *
 *  @param instr_addr The instr address to check
 *  @return Returns true if the instruction should be sliced.
 */
DR_EXPORT bool sb_slice_instr(void *slicer, app_pc instr_addr);

#endif /* SLICER_BUNNY_H_ */
