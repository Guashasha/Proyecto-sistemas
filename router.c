// router.c
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
    int router_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in raddr;
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(8080);
    raddr.sin_addr.s_addr = INADDR_ANY;

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8081);
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(router_socket, (struct sockaddr*)&raddr, sizeof(raddr));

    listen(router_socket, 5);

    int client_socket;
    int server_socket;
    int connection;
    struct Mensaje m;

    while (1) {
        client_socket = accept(router_socket, NULL, NULL);
        recv(client_socket, &m, sizeof(m), 0);
        printf("Recibido mensaje de la computadora: %s\n", m.msg);

        // Convertir a mayúsculas
        for (int i = 0; i < sizeof(m.msg); i++) {
            m.msg[i] = toupper(m.msg[i]);
        }

        // Conectar con el servidor, enviar y recibir mensaje
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        connection = connect(server_socket, (struct sockaddr*)&saddr, sizeof(saddr));
        send(server_socket, &m, sizeof(m), 0);
        recv(server_socket, &m, sizeof(m), 0);
        printf("Recibido mensaje del servidor: %s\n", m.msg);

        // Enviar mensaje a la computadora
        send(client_socket, &m, sizeof(m), 0);

        // Cerrar el socket del servidor
        close(server_socket);

        // Cerrar el socket de la computadora
        close(client_socket);
    }

    return 0;
}
