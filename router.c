#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sock_rout, sock_cli;
  struct sockaddr_un saddr, caddr;

  int result;

  if ((sock_rout = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
    perror("socket fallado");
    exit(EXIT_FAILURE);
  }

  saddr.sun_family = AF_UNIX;
  strcpy(saddr.sun_path, "unix_socket");
  int slen = sizeof(sock_rout);

  bind(sock_rout, (struct sockaddr *)&sock_rout, slen);

  listen(sock_rout, 5);

  while (1) {
    char ch;
    int clen = sizeof(caddr);
    sock_cli = accept(sock_rout, (struct sockaddr *)&caddr, &clen);
    read(sock_cli, &ch, 1);
    ch++;
    write(sock_cli, &ch, 1);
    close(sock_cli);
  }

  return 0;
}
