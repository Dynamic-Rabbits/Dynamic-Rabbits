/**
 *  @file ub_cl_arg_app.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	for (int i = 0; i < argc; i++) {

		printf("String at index %d is %s.\n", i, argv[i]);
	}
}
