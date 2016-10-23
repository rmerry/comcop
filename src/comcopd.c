#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BACKLOG_SIZE 5
#define BUFFER_SIZE 100

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

  printf("Opening socket...");
  sfd = socket(AF_UNIX, SOCK_STREAM, 0);

  if (sfd == -1) 
    exit_with_error(-1);

  printf("[DONE]\n");

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

  printf("Binding socket...");

  if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    exit_with_error(-1);

  printf("[DONE]\n");

  printf("Listening on  socket...");

  if (listen(sfd, 10) == -1)
    exit_with_error(-2);

  printf("[DONE]\n");

  for (;;) {
    cfd = accept(sfd, NULL, NULL);

    if (cfd == -1)
      exit_with_error(-3);
     
    while ((read_len = read(cfd, buf, BUFFER_SIZE)) > 0) {
      printf("\n\tread_len == %d\n", read_len);
      printf("\tbuf == %s\n", buf);
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
