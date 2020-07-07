#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char func(FILE* fd)
{
  char c;
  size_t i = 0;

  char mybuff[30];

  while((c =fgetc(fd)) != EOF)
  {
    mybuff[i] = c;
    i++;    
  }
  return mybuff[29];
}

int main(int argc, char *argv[])
{
  FILE* fd;
  fd = fopen(argv[1], "r");

  char c = func(fd);

  printf("Char at pos 29 is : %c", c);
  return 0;
}
