/**
 *  @file ub_file_test_app7.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int c;
	int file = open("ub_file_input_test1.txt", O_RDONLY);

	if (file) {

		char buf[10];
		size_t size =pread(file, buf, 15, 4);
		buf[size] = '\0';
		printf("String is %s\n", buf);

		char buf1[7];
		buf1[6]='\0';

		read(file, buf1, 6);
		printf("Bytes read is %s", buf);

		close(file);
	}
}
