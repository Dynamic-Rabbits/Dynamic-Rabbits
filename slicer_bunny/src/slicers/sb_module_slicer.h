/**
 *  @file preslicer_module.h
 *  @brief Enables the slicing of instuctions found in uninteresting modules.
 *  @author John F.X. Galea
 */

#ifndef MODULE_SLICER_H_
#define MODULE_SLICER_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"

/**
 *  Initialises the module slicer.
 *
 *  Reads the file by making use of ub_file_reader.c
 */
void *sb_module_slicer_init(drmgr_priority_t *priority);

/**
 * Destroys the module slicer.
 */
void sb_module_slicer_destroy(void *module_slicer);

/**
 * Registers the modules to slice, which are listed in a given file.
 *
 * @param module_file The file listing the module names to slice.
 */
void sb_module_slicer_register_file(void *module_slicer, file_t module_file);

/**
 *  States whether to slice the proc address.
 *
 *  @param proc_address The proc address to check.
 *  @return Returns True if the proc_address should be sliced (not analysed).
 */
bool sb_slicer_module_slice_out(void *module_slicer, app_pc proc_address);

#endif
