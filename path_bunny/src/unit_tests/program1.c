#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

void func(char *userInput) {

    if (userInput[70] != 'C') {
        userInput[70] = '\0';
    }

    if (userInput[8] == 'A') {
        printf("Hello there!");
    }

    if (userInput[0] == 'A') {
        printf("Hello there!2");
    }

    if (userInput[8] == userInput[7]) {
        printf("John F.X. Galea");

    }

    int i = userInput[9] * userInput[2];
    if (i > ((intptr_t) userInput)) {
        printf("John F.X. Galea 2");
    }

    i = userInput[8] + userInput[2];
    if (((intptr_t) userInput) < i) {
        printf("John F.X. Galea 3");
    }

    int *integer = (int *) &(userInput[50]);

    if (*integer == 982){
        printf("John F.X. Galea 4");
    }
}

int main(int argc, char *argv[]) {
    int res, fd = -1;
    char *heapArr = NULL;

    FILE *fp;
    fp = fopen(argv[1], "r");

    heapArr = malloc(300 * sizeof(char));
    fread(heapArr, 300, 1, fp);

    printf("THE POINTER IS !!!!!!!!!!!!! %p !!!!!!!\n", heapArr);

    func(heapArr);

    return 0;
}
