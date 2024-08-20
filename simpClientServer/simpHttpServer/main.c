#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

char*
seeknull(const char* buf, int size)
{
  int i = 0;
  char* nbuf = (char*) buf;
  while ((*nbuf != 0x00) && (i < size))
  {
    nbuf++;
    i++;
  }
  if (*nbuf != 0x00) return 0;
  return nbuf;
}

char*
getIndex()
{
  const char* fp = malloc(256);
  getcwd((char *)fp, 256);
  char* fps = seeknull(fp, 256);
  if (fps == 0) return 0;
  int size = 256 - (fps - fp);
  fps = stpncpy(fps, "/index.html", size);
  int fd = open(fp, O_RDONLY);
  if (fd == 0) return 0;
  free((char *)fp);
  fps = 0;
  char* buf = malloc(65536);
  if (read(fd, buf, 65535) == 0) return 0;
  close(fd);
  return buf;
}

int
main()
{
  char* indp = getIndex();
// -- BEGIN OF STRING --
  char hedp[] = \
"\
HTTP/1.1 200 OK\n\
CONTENT-TYPE: TEXT/HTML\n\
SERVER: SUSHISERVER V0.0.1\n\n";
  char* wbuf = malloc(65536);
  bzero(wbuf, 65536);
  char* wbufs = stpncpy(wbuf, hedp, 65536);
  wbufs = stpncpy(wbufs, indp, 65536 - (wbufs - wbuf));
// -- END OF STRING --
  if (indp == 0) return 1;
  int sfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sfd == 0) return 2;
  struct sockaddr_in* addr = malloc(sizeof(struct sockaddr_in));
  struct sockaddr_in* cddr = malloc(sizeof(struct sockaddr_in));
  bzero((char*)addr, sizeof(addr));
  bzero((char*)cddr, sizeof(cddr));
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = htonl(INADDR_ANY);
  addr->sin_port = htons(1337);
  int bs = bind(sfd, (struct sockaddr*)addr, sizeof(struct sockaddr_in));
  if(bs == -1) return 3;
  listen(sfd, 5);
  int* clen = malloc(sizeof(int));
  *clen = 0;
  int cfd = 0;
  int rs = 0;
  int ws = 0;
  char* buf = malloc(65536);
  while (1)
  {
    cfd = accept(sfd, (struct sockaddr *)cddr, (socklen_t *)clen);
    if(cfd == -1) continue;
    else
    {
      bzero(buf, 65536); // PROBABLY SLOW
      rs = read(cfd, buf, 65536);
      ws = write(cfd, wbuf, 65536);
      close(cfd);
    }
  }
  free(indp);
  free(addr);
  free(cddr);
  return 0;
}
