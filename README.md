# Implementación del algoritmo NAT en c

## Descripción
El algoritmo NAT (*Network Addres Translation*) es un mecanismo utilizado por routers para cambiar paquetes entre dos redes.

La implementación se hará con procesos en vez de redes, cada proceso teniendo su propia identidad, no podrán interactuar directamente entre ellos, y un proceso que emulará un router, recibiendo y mandando mensajes entre procesos al proceso objetivo.

## Implementación
Cada proceso tiene su propio codigo en C, el cual es el que le dará su identidad unica, y a traves del cual se mandarán los mensajes al router.

Ademas de los procesos que mandan mensajes hay procesos que reciben los mensajes y mandan una respuesta, éstos también tendrán su propio archivo en C.

El proceso principal, el que emula al router, al recibir mensajes guardará la información del Emisor y del Receptor, y enviará el mensaje al receptor, recibirá otro mensaje y lo transmitirá al Emisor original.
