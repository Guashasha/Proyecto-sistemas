#include "mensaje.h" //incluye el archivo de encabezado que define la estructura del mensaje
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  char mensaje[256]; //variable para almacenar los mensajes
  int router_socket = socket(AF_INET, SOCK_STREAM, 0); //crear un socket para el router

  //configuracion del router (direccion)
  struct sockaddr_in raddr;
  raddr.sin_family = AF_INET;
  raddr.sin_port = htons(8080);
  raddr.sin_addr.s_addr = INADDR_ANY;

  //configuracion del server (direccion)
  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(8081);
  saddr.sin_addr.s_addr = INADDR_ANY;

  //vincular el socket del router a la direccion
  bind(router_socket, (struct sockaddr *)&raddr, sizeof(raddr));

  //"escuchar" conexiones entrantes en el socket del router
  listen(router_socket, 5);

  int client_socket;
  int server_socket;
  int connection;
  struct Mensaje m; //struct para almacenar msjs

  while(1){
    client_socket = accept(router_socket, NULL, NULL); //aceptar la conexion entrante desde la computadora (proceso)
    recv(client_socket, &m, sizeof(m), 0); //recibir el mensaje de la computadora (proceso)
    printf("Recibido mensaje de la computadora: %s\n", m.msg);

    server_socket = socket(AF_INET, SOCK_STREAM, 0); //crear un nuevo socket para conectarse al server
    connection = connect(server_socket, (struct sockaddr *)&saddr, sizeof(saddr)); //conectarse al server
    send(server_socket, &m, sizeof(m), 0); //enviar msj al server
    recv(server_socket, &m, sizeof(m), 0); //recibir la respuesta del server
    printf("Recibido mensaje del servidor: %s\n", m.msg);

    //enviar la respuesta del server de vuelta a la computadora (server)
    send(client_socket, &m, sizeof(m), 0);

    close(server_socket); //cerrar el socket del server

    close(client_socket); //cerrar el socket de la computadora (proceso)
  }

  return 0;
}