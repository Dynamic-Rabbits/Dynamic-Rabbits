/**
 *  @file ub_file_test_app.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int file = open("ub_file_input_test1.txt", O_RDONLY);

	if (file) {

		char buf[13];
		read(file, buf, 12);
		buf[12] = '\0';
		printf("String is %s\n", buf);

		close(file);
	}
}
