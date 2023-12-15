#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(8080);
  saddr.sin_addr.s_addr = INADDR_ANY;

  int connection;
  connection = connect(server_socket, (struct sockadd *)&saddr, sizeof(saddr));
  if (connection == -1)
    printf("error de conexión con el servidor");

  char msg[256] = "hola desde el cliente";
  send(server_socket, msg, sizeof(msg), 0);
  recv(server_socket, &msg, sizeof(msg), 0);

  printf("mensaje del server: %s", msg);
  close(server_socket);

  return 0;
}
