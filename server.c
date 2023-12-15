#include "mensaje.h" //incluye el archivo de encabezado que define la estructura de mensaje
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char mensaje[256]; //variable para almacenar msjs
    int server_socket = socket(AF_INET, SOCK_STREAM, 0); //crear un socket para el server
    int router_socket; //variable para almacenar el socket dle router

    //configuracion de la direccion del server
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8081);
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&saddr, sizeof(saddr)); //vincular el socket del server a la direccion

    listen(server_socket, 5); //escuchar conexiones entrantes en el socket del server

    struct Mensaje m; //struct para almacenar los mensajes

    while (1) {
        router_socket = accept(server_socket, NULL, NULL); //aceptar la conexion entrante desde el router
        recv(router_socket, &m, sizeof(m), 0); //recibir el msj del router
        printf("Recibido mensaje del router: %s\n", m.msg);

        //convertir a mayusculas
        for (int i = 0; i < sizeof(m.msg); i++) {
            mensaje[i] = toupper(m.msg[i]);
        }

        //enviar el msj convertido al router
        send(router_socket, mensaje, sizeof(mensaje), 0);

        //no cerrar las conexiones en cada iterracion, debe mantenerse la conexion abierta para futuras comunicaciones
    }

    return 0;
}