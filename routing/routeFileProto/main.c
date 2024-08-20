#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

// Represents routing file in memory
// WILL NOT BE USED -- UNNECESARRY
struct rout_rfile
{
  int fileSize;
  char* numOfRoutes;
  char* text;
};

// Represents single entry in routing file
struct rout_route
{
  char* rsize; // int
  char* fsize; // int
  char* routeStr; // string
  char* fileStr; // string
};

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

// This function needs to be updated to include the file size for alloc
// This function does not properly check if buffering was successfull
char*
bufFile(char* fileName)
{
  const char* fp = malloc(256);
  getcwd((char*)fp, 256);
  char* fps = seeknull(fp, 256);
  if (fps == 0) return 0;
  int size = 256 - (fps - fp);
  fps = stpncpy(fps, fileName, size);
  int fd = open(fp, O_RDONLY);
  if (fd == 0) return 0;
  free((char*)fp);
  fps = 0;
  char* buf = malloc(65536);
  if(read(fd, buf, 65535) == 0) return 0;
  close(fd);
  return buf;
}

int
main()
{
  const char* routeFile = bufFile("/2entry.rou");
  if (routeFile == 0) return 1;
  printf("%s\n", routeFile);
  struct rout_route* a = malloc(sizeof(struct rout_route));
  char* rFS = (char*)routeFile;
  rFS++;
  a->rsize = rFS;
  a->fsize = (rFS + 1);
  a->routeStr = (rFS + 2);
  a->fileStr = (a->routeStr + *a->rsize);
  write(1, a->routeStr, *a->rsize);
  putchar(0x0A);
  write(1, a->fileStr, *a->fsize);
  putchar(0x0A);
  return 0;
}
