#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "comcop.h"

/* Prototypes */
void exit_with_error(int error_code);

int
main(int argc, char *argv[])
{
  const char *SOCKET_NAME = "/tmp/testsock";
  char buf[BUFFER_SIZE];
  int sfd, cfd;
  struct sockaddr_un addr;
  ssize_t read_len;

  sfd = socket(AF_UNIX, SOCK_STREAM, 0);

  if (sfd == -1) 
    exit_with_error(-1);

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

  if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    exit_with_error(-1);

  if (listen(sfd, 10) == -1)
    exit_with_error(-2);


  for (;;) {
    cfd = accept(sfd, NULL, NULL);

    if (cfd == -1)
      exit_with_error(-3);
     
    while ((read_len = read(cfd, buf, BUFFER_SIZE)) > 0) {
      if (write(STDOUT_FILENO, buf, read_len) != read_len)
        exit_with_error(-4);
    }

    if (read_len == -1)
      exit_with_error(-5);

    if (close(cfd) == -1)
      exit_with_error(-6);
  }
}

void
exit_with_error(int error_code)
{
  printf("[ERROR]\n");
  exit(error_code);
}
