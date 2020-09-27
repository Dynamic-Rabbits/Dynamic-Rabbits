#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "taint_annotations/annotations/tb_annotations.h"


void func(char *userInput)
{
	char arr[20];

	strcpy(arr, userInput);
	printf("Hello there: %s", arr);
}

int main(int argc, char *argv[])
{
	int res, fd = -1;
	char *heapArr = NULL;

	FILE *fp;
        fp = fopen(argv[1], "r");

	heapArr = malloc(300 * sizeof(char));
    fread(heapArr, 300, 1, fp);

    /* Rely on annotation to taint entire buffer instead
     * of hooking to input functions.
     */
    TR_TAINT((void *) heapArr, 300);

    printf("THE POINTER IS !!!!!!!!!!!!! %p !!!!!!!\n", heapArr);

	func(heapArr);

	return 0;
}
