# Implementación del algoritmo NAT en c

## Descripción
El algoritmo NAT (*Network Addres Translation*) es un mecanismo utilizado por routers para cambiar paquetes entre redes.

La implementación se hará con procesos en vez de redes, cada proceso teniendo su propia identidad, no podrán interactuar directamente entre ellos, y un proceso que emulará un router, recibiendo y mandando mensajes entre procesos al proceso objetivo.

## Implementación
Cada proceso tiene su propio codigo en C, el cual es el que le dará su identidad unica, y a traves del cual se mandarán y recibirán los mensajes.

El proceso principal (router.c) emula al router, y su trabajo es recibir mensajes de las computadoras, mandarlos al servidor, recibir una respuesta del servidor y mandarlos de regreso a la computadora que lo mandó en primer lugar.
Despues de iniciar las conexiones necesarias, espera a un cliente (pc) que mande un mensaje, seguido de ello manda el mensaje al servidor, el cual lo modifica y lo manda de regreso al router, éste lo manda directamente de regreso al cliente que mandó el mensaje.

El proceso que actua como el servidor espera a recibir un mensaje, el cual llega solamente de parte del router, posteriormente convierte a mayusculas el mensaje y lo envía de regreso al router.

Los procesos "clientes" (pc) piden al usuario una cadena, la mandan al router y esperan una respuesta para despues imprimirla.
