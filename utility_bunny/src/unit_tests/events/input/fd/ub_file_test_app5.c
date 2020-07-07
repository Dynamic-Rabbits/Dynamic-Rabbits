/**
 *  @file ub_file_test_app5.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int file = open("ub_file_input_test1.txt", O_RDONLY);
	int file2 = open("ub_file_input_test2.txt", O_RDONLY);

	if (file) {

		int file3 = dup(file2);

		char buf[5];
		read(file3, buf, 4);
		buf[4] = '\0';
		printf("String is %s\n", buf);

		read(file, buf, 1);
		buf[1] = '\0';
		printf("String is %s\n", buf);

		dup2(file, file3);

		close(file);

		read(file2, buf, 1);
		buf[1] = '\0';
		printf("String is %s\n", buf);

		read(file3, buf, 1);
		putchar(*buf);

		close(file3);
		close(file2);
	}
}


