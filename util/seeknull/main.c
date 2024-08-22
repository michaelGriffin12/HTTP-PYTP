#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char*
seeknull(const char* buf, int size)
{
  int i = 0;
  char* nbuf = (char*)buf;
  while ((*nbuf != 0x00) && (i < size))
  {
    nbuf++;
    i++;
  }
  if (*nbuf != 0x00) return 0;
  return nbuf;
}

int
main()
{
  const char* file = malloc(80);
  getcwd((char*)file, 80);
  char* files = seeknull(file, 80);
  if (files == 0x00) return 1;
  int filessize = 80 - (files - file);
  printf("%i\n", filessize);
  strncpy(files, "/test.txt", filessize);
  printf("%s\n", file);
  return 0;
}
