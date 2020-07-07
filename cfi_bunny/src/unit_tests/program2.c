#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef void (*func_t)(void );

void func(char *userInput)
{
    func_t *my_faulty_func_ptr= (func_t *) userInput;
    func_t my_faulty_func = *my_faulty_func_ptr;
    my_faulty_func();
}

int main(int argc, char *argv[])
{
	int res, fd = -1;
	char *heapArr = NULL;

	FILE *fp;
        fp = fopen(argv[1], "r");

	heapArr = malloc(300 * sizeof(char));
    fread(heapArr, 300, 1, fp);

    func(heapArr);

	return 0;
}
