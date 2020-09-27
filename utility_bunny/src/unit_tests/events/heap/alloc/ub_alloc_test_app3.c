/**
 *  @file ub_alloc_test_app3.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	for (int i = 0; i < 8; i++){
		void *my_integer = calloc(1, 1111);
		printf("The value in mallloc is %d %p\n", *((int *) my_integer), my_integer);
	}
}
