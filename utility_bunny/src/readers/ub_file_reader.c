/*
 * ub_file_reader.c
 *
 *      Author: john
 */

#include "ub_file_reader.h"
#include "dr_api.h"
#include "drext.h"
#include <string.h>

DR_EXPORT file_t ub_fr_open_file_with_check(const char *file_path,
		uint mode_flags) {

	file_t file = dr_open_file(file_path, mode_flags);

	if (file == INVALID_FILE)
		DR_ASSERT(false);

	return file;
}

DR_EXPORT bool ub_fr_get_line(file_t file, char *buf, size_t size) {

	char read_char = 0;

	int i = 0;
	ssize_t read_size = 0;

	while (true) {
		// Read a single char.
		read_size = dr_read_file(file, &read_char, 1);

		if (read_char != '\n' && read_char != EOF && read_size != 0) {
			buf[i] = read_char;
			i++;

			DR_ASSERT(i != size);
		} else {
			break;
		}
	}

	buf[i] = '\0';

	return i > 0;
}

DR_EXPORT char *ub_fr_get_basename(char *path) {

	// Get last occurrence of  `/`
	char *basename = strrchr(path, '/');

	if (basename == NULL)
		return path;
	else {
		basename++;
		return basename;
	}
}

