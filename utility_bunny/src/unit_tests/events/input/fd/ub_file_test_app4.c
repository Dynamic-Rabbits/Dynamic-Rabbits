/**
 *  @file ub_file_test_app4.c
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

	if (file) {

		int file2 = dup(file);

		char buf[13];
		read(file, buf, 12);
		buf[12] = '\0';
		printf("String is %s\n", buf);

		if (lseek(file, 3, SEEK_SET) < 0)
			return 1;

		close(file);

		read(file2, buf, 1);
		putchar(*buf);

		close(file2);
	}
}
