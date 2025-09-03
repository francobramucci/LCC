#ifndef __FLISTA_H__
#define __FLISTA_H__

#include "vector.h"

typedef Vector FLista;

// Crea una funcion de lista
FLista *flista_crear(int capacidad, FuncionCopiadora copia, FuncionDestructora destruir);

// Agrega un operador o identificador a una funcion de lista
void flista_insertar(FLista *funcion, char *subFuncion);

// Destruye una funcion de lista
void flista_destruir(FLista *funcion);

// Retorna si la funcion de lista es vacia o no
int flista_es_vacia(FLista *funcion);

// Accede a un elemento de la funcion de lista
char *flista_acceder(FLista *funcion, int indice);

// Imprime la funcion de lista
void flista_imprimir(FLista *funcion);

#endif // !__FLISTA_H__
