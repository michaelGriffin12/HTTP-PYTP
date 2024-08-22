#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char*
seeknull(const char* buf, int size)
{
  int i = 0;
  char* nbuf = (char *)buf;
  while ((*nbuf != 0x00) && (i < size))
  {
    nbuf++;
    i++;
  }
  if (*nbuf != 0x00) return 0;
  return nbuf;
}

char*
bufFile(char* fileName)
{
  const char* fp = malloc(256);
  getcwd((char*)fp, 256);
  char* fps = seeknull(fp, 256);
  if (fps == 0) return 0;
  int size = 256 - (fps - fp);
  if (size > 1)
  {
    *fps = '/';
    fps++;
    size = size - 1;
  }
  fps = stpncpy(fps, fileName, size);
  int fd = open(fp, O_RDONLY);
  free((char*)fp);
  fps = 0;
  int fSize = lseek(fd, 0, SEEK_END) + 1;
  lseek(fd, 0, SEEK_SET);
  if (fSize == 0)
  {
    printf("File probably does not exist.\n");
    return 0;
  }
  char* buf = malloc(fSize);
  read(fd, buf, fSize);
  close(fd);
  return buf;
}

int
main()
{
  char* test = bufFile("test.txt");
  if (test == 0) return 1;
  printf("%s", test);
  return 0;
}
