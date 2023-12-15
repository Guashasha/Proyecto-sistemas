// pc.c
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct Message {
    char text[256];
    int receptor;
    int transmisor;
};

int main(int argc, char *argv[]) {
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in router_addr;
    router_addr.sin_family = AF_INET;
    router_addr.sin_port = htons(8080);
    router_addr.sin_addr.s_addr = INADDR_ANY;

    int connection;
    connection = connect(client_socket, (struct sockaddr*)&router_addr, sizeof(router_addr));
    if (connection == -1) {
        perror("Error al conectarse con el router.");
        exit(EXIT_FAILURE);
    }

    struct Message msg;
    printf("Digite la cadena: ");
    fgets(msg.text, sizeof(msg.text), stdin);

    // Envía la estructura al router
    send(client_socket, &msg, sizeof(struct Message), 0);

    // Recibe la respuesta del router
    recv(client_socket, &msg, sizeof(struct Message), 0);
    printf("Mensaje del router: %s\n", msg.text);

    // Cierra el socket del cliente después de recibir la respuesta
    close(client_socket);

    return 0;
}
