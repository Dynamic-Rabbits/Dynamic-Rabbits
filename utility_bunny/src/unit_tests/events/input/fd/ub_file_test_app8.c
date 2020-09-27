/**
 *  @file ub_file_test_app8.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int file = open("ub_file_input_test1.txt", O_RDONLY);

	if (file) {

		ssize_t bytes_read;

		char buf0[1];
		char buf1[1];
		char buf2[1];

		int iovcnt;
		struct iovec iov[3];

		iov[0].iov_base = buf0;
		iov[0].iov_len = 1;
		iov[1].iov_base = buf1;
		iov[1].iov_len = 1;
		iov[2].iov_base = buf2;
		iov[2].iov_len = 1;
		iovcnt = sizeof(iov) / sizeof(struct iovec);

		bytes_read = preadv(file, iov, iovcnt, 4);

		printf("Bytes read %d", bytes_read);
		printf("Buf 1 is %c\n", buf0[0]);
		printf("Buf 2 is %c\n", buf1[0]);
		printf("Buf 3 is %c\n", buf2[0]);

		char buf[7];
		buf[6]='\0';

		read(file, buf, 6);
		printf("Bytes read is %s", buf);

		close(file);
	}
}


