#ifndef __FLISTA_H__
#define __FLISTA_H__

#include <stdlib.h>

typedef struct {
        char **def;
        int largo;
} FLista;

FLista *flista_crear(int tamBuffer);

void flista_destruir(FLista *funcion);

#endif // !__FLISTA_H__
