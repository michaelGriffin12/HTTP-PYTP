#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Tested
void
check(int fCheck, int retVal)
{
  if (fCheck == 0)
    exit(retVal);
  else
    return;
}

void
check2(int fCheck, int retVal)
{
  if (fCheck != 0)
    exit(retVal);
  else
    return;
}

int
main()
{
  char* buf = malloc(65536);
  char  toSend[] = "Beep!\n\n";
  int sfd = socket(PF_INET, SOCK_STREAM, 0);
  check(sfd, 1);
  struct sockaddr_in* addr = malloc(sizeof(struct sockaddr_in));
  struct sockaddr_in* cddr = malloc(sizeof(struct sockaddr_in));
  bzero((char*)addr, sizeof(addr));
  bzero((char*)addr, sizeof(addr));
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = htonl(INADDR_ANY);
  addr->sin_port = htons(1337);
  int bindStatus = bind(sfd, (struct sockaddr *)addr,
                        sizeof(struct sockaddr_in));
  check2(bindStatus, 2);
  listen(sfd, 5);
  int* clen = malloc(sizeof(int));
  *clen = 0;
  int cfd = accept(sfd, (struct sockaddr *)cddr, (socklen_t *)clen);
  check(cfd, 3);
  int rStatus = read(cfd, buf, 65536);
  int wStatus = write(cfd, toSend, 7);
  printf("%s\n", buf);
  close(sfd);
  close(cfd);
  free(clen);
  free(buf);
  free(addr);
  return 0;
}
