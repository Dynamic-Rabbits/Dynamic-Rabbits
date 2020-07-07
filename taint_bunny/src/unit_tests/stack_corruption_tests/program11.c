#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void func(char *userInput)
{
  char arr[20];

  for (int i = 0; i < 300; i++){
    userInput[i] = userInput[i] ^ 8;
  }

  strcpy(arr, userInput);
}

int main(int argc, char *argv[])
{
  int res, fd = -1;
  char *heapArr = NULL;
  fd = open(argv[1], O_RDONLY);

  heapArr = malloc(300 * sizeof(char));
  res = read(fd, heapArr, 300);

  func(heapArr);

  return 0;
}
