#ifndef __FLISTA_H__
#define __FLISTA_H__

#include <stdlib.h>

typedef struct {
        char **def;
        int ultimo;
        int capacidad;
} FLista;

FLista *flista_crear(int capacidad);

void flista_insertar(FLista *funcion, char *subFuncion);

void flista_redimensionar(FLista *funcion);

void flista_destruir(FLista *funcion);

int flista_es_vacia(FLista *funcion);

#endif // !__FLISTA_H__
