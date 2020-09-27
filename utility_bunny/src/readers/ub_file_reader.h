/*
 * ub_file_reader.h
 *
 *  Created on: 29 Nov 2017
 *      Author: john
 */

#ifndef READERS_FILE_READERS_UB_FILE_READER_H_
#define READERS_FILE_READERS_UB_FILE_READER_H_

#include "dr_defines.h"
#include "drext.h"

/**
 * Opens file with a check for its validity.
 */
DR_EXPORT file_t ub_fr_open_file_with_check(const char *file_path, uint mode_flags);

/*
 *  Reads a line from the slice file.
 *
 *  @param file The file to read from
 *  @param buf The buffer to store the read line
 *  @param size The size in bytes to read
 *  @return True upon successful read.
 */
DR_EXPORT bool ub_fr_get_line(file_t file, char *buf, size_t size);

/**
 *  Returns a str pointer referring to the file name specified in a path.
 *
 *  @param path The path of the file.
 *  @return Returns a pointer to the start of the base name.
 */
DR_EXPORT char *ub_fr_get_basename(char *path);

#endif /* READERS_FILE_READERS_UB_FILE_READER_H_ */
