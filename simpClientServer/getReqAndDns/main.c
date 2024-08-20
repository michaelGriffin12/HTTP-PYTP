#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main()
{
  char* buf = malloc(65536);
  char toSend[] =
  {
"GET /posts/1 HTTP/1.1\n\
Host: jsonplaceholder.typicode.com\n\
Accept: */*\n\n"
  };
  int toSendSize = strlen(toSend);
  // Socket file descriptor
  int sfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sfd == 0) return 1;
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(80);
  // Host name
  struct hostent *hn;
  hn = gethostbyname("jsonplaceholder.typicode.com");
  if (hn == 0)
    return 2;
  if (hn->h_addrtype != AF_INET)
    return 3;
  addr.sin_addr.s_addr = *(in_addr_t*) hn->h_addr;
/*
  if (inet_pton(AF_INET, "104.21.59.19", &addr.sin_addr) <= 0)
    return 3;
*/
  int status = connect(sfd, (struct sockaddr*)&addr, sizeof(addr));
  if (status < 0) return 3;
  send(sfd, toSend, toSendSize, 0);
  int rStatus = read(sfd, buf, 65536);
  printf("%s\n\n", buf);
  printf("%s\n", toSend);
  close(sfd);
  free(buf);
  return 0;
}
