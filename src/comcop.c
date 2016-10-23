#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BUFFER_SIZE 100

/* Prototypes */
void display_usage_information();
void exit_with_error(int error_code);
void exit_with_usage();
int save(char *command, char *args[], int exit_code);

int
main(int argc, char *argv[])
{
  if (argc <= 1)
    exit_with_usage();

  if (strncmp(argv[1], "save", 4) == 0) {
    char *command;
    char *args;
    int exit_code;

    if (argc < 3)
      exit_with_usage();

    if (strncmp(argv[2], "--command", 9) == 0 || strncmp(argv[2], "-c", 2) == 0) {
      command = (char *)malloc(sizeof(argv[3]) - 1);
      strcpy(command, argv[3]);
    }

    save(command, &args, exit_code);

  } else {
    exit_with_usage();
  }

  exit(EXIT_SUCCESS);
}

void
exit_with_error(int error_code)
{
  exit(error_code);
}

void
exit_with_usage()
{
  display_usage_information();
  exit(-1);
}

void
display_usage_information()
{
  printf("Usage: bhc <operation> [...]\n");
  printf("operations:\n");
  printf("\tbhc {-h --help}\n");
  printf("\tbhc {-v --version}\n");
  printf("\tbhc save [options]\n");
  printf("\toptions:\n");
  printf("\n");
}

/* The save() function attempts to connect with the daemon and send it
 * a command, its arguments and exit code to record for future look-ups */
int
save(char *command, char *args[], int exit_code)
{
  const char *SOCKET_NAME = "/tmp/testsock";
  int sfd;
  struct sockaddr_un addr;
  ssize_t write_len;
  char buf[BUFFER_SIZE];

  sfd = socket(AF_UNIX, SOCK_STREAM, 0);

  if (sfd == -1) 
    exit_with_error(-1);

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

  if (connect(sfd, (struct sockaddr *)&addr, 
              SUN_LEN(&addr)) == -1)
    exit_with_error(-1);

  /* strncpy(buf, command, sizeof(command) -1); */
  write_len = write(sfd, command, BUFFER_SIZE);
  
  if (write_len == -1)
    exit_with_error(-5);

  return 0;
}
