//mensaje.h
#ifndef MENSAJE_H
#define MENSAJE_H

struct Mensaje {
    char msg[256];
    int receptor;
    int transmisor;
};

#endif