/**
 *  @file ub_string.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_string.h"
#include "dr_api.h"
#include "drext.h"
#include <string.h>

char *ub_string_create_copy(const char *string) {

	char *copy_string = dr_global_alloc(
			(strlen(string) + 1) * sizeof(char));
	strcpy(copy_string, string);

	return copy_string;
}

void ub_string_destroy(char *string) {

	DR_ASSERT(string != NULL);
	dr_global_free(string, (strlen(string) + 1) * sizeof(char));
}
