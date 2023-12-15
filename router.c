#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char mensaje[256] = "mensaje del servidor";

  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(8080);
  saddr.sin_addr.s_addr = INADDR_ANY;

  bind(server_socket, (struct sockadd *)&saddr, sizeof(saddr));

  listen(server_socket, 5);

  int client_socket;

  while (1) {
    client_socket = accept(server_socket, NULL, NULL);
    recv(client_socket, msg, sizeof(msg), 0);

    send(client_socket, mensaje, sizeof(mensaje), 0);

    close(server_socket);
  }

  return 0;
}
