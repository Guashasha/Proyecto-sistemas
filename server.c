#include "mensaje.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char mensaje[256];
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int router_socket;

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8081);
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&saddr, sizeof(saddr));

    listen(server_socket, 5);

    struct Mensaje m;

    while (1) {
        router_socket = accept(server_socket, NULL, NULL);
        recv(router_socket, &m, sizeof(m), 0);
        printf("Recibido mensaje del router: %s\n", m.msg);

        for (int i = 0; i < sizeof(m.msg); i++) {
            mensaje[i] = toupper(m.msg[i]);
        }

        send(router_socket, mensaje, sizeof(mensaje), 0);

        // No cierres las conexiones en cada iteración
    }

    return 0;
}
