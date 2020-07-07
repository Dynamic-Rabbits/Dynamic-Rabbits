#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void func(char *userInput, char *trap)
{
	char arr[20];

        printf("The first 20 chars are %s", trap);
	
	char test[21];
	strcpy(test, trap);

	printf("Test: %s\n\n", test);

	strcpy(arr, userInput);
}

int main(int argc, char *argv[])
{
	int res, fd = -1;
	char *heap_arr = NULL;
        char trap[31];

	fd = open(argv[1], O_RDONLY);

	heap_arr = malloc(300 * sizeof(char));
	res = read(fd, heap_arr, 300);

	memcpy(trap, heap_arr+30, 30);
	trap[30]= '\0';

	func(heap_arr, trap);

	return 0;
}
