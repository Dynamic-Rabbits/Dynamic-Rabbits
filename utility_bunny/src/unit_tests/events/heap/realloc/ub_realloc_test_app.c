/**
 *  @file ub_realloc_test_app.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	for (int i = 0; i < 8; i++){

		int *my_integer = (int *) malloc(1111);
		*my_integer = 9;
		printf("The value in mallloc is %d\n", *((int *) my_integer));

		my_integer = (int *) realloc(my_integer, 2222);
		printf("The value in realloc is %d\n", *((int *) my_integer));

		free(my_integer);
	}
}

