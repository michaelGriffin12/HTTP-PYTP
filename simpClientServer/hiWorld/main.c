#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main()
{
  char* buf = malloc(65536);
  char toSend[] =
  {
"GET / HTTP/1.1\n\
Host: www.google.com\n\
Accept: */*\n\n"
  };
  int toSendSize = strlen(toSend);
  int sfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sfd == 0) return 1;
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(80);
  if (inet_pton(AF_INET, "64.233.180.103", &addr.sin_addr) <=0)
    return 2;
  int status = connect(sfd, (struct sockaddr*)&addr, sizeof(addr));
  if (status < 0) return 3;
  send(sfd, toSend, toSendSize, 0);
  int rStatus;
  do
  {
    rStatus = read(sfd, buf, 65536);
    printf("%s\n", buf);
  } while(rStatus != -1);
  printf("%s\n", toSend);
  close(sfd);
  free(buf);
  return 0;
}
