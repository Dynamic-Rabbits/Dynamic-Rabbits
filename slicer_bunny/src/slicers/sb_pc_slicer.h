/**
 *  @file sb_pc_slicer.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef SB_PC_SLICER_H_
#define SB_PC_SLICER_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"

/**
 *  Initialises the PC slicer.
 *
 *  Reads the file by making use of ub_file_reader.c
 */
void *sb_pc_slicer_init();

/**
 * Destroys the PC slicer.
 */
void sb_pc_slicer_destroy(void *pc_slicer);

/**
 * Registers the pc addr to slice, which are listed in a given file.
 *
 * @param pc_file The file listing the instr addresses to slice.
 */
void sb_pc_slicer_register_file(void *pc_slicer, file_t pc_file);

/**
 *  States whether to slice the proc address.
 *
 *  @param proc_address The proc address to check.
 *  @return Returns True if the proc_address should be sliced (not analysed).
 */
bool sb_pc_slicer_slice_out(void *pc_slicer, app_pc proc_address);

#endif /* SB_PC_SLICER_C_ */
