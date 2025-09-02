#ifndef __FLISTA_H__
#define __FLISTA_H__

#include "vector.h"

typedef Vector FLista;

FLista *flista_crear(int capacidad, FuncionCopiadora copia, FuncionDestructora destruir);

void flista_insertar(FLista *funcion, char *subFuncion);

void flista_redimensionar(FLista *funcion);

void flista_destruir(FLista *funcion);

int flista_es_vacia(FLista *funcion);

char *flista_acceder(FLista *funcion, int indice);

#endif // !__FLISTA_H__
