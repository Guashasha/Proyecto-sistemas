#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "unix_socket"

int main() {
    int client_socket;
    struct sockaddr_un router_addr;
    char buffer[1024];

    if ((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("error al crear");
        exit(EXIT_FAILURE);
    }

    router_addr.sun_family = AF_UNIX;
    strcpy(router_addr.sun_path, SOCKET_PATH);

    if (connect(client_socket, (struct sockaddr *)&router_addr, sizeof(router_addr)) == -1) {
        perror("error al conectar");
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, "ayuda");
    send(client_socket, buffer, strlen(buffer), 0);

    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("respuesta: %s\n", buffer);

    close(client_socket);

    return 0;
}
