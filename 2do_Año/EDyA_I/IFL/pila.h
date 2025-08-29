#ifndef __PILA_H_
#define __PILA_H_

#include "dlist.h"

typedef DList *Pila;

Pila pila_crear(FuncionCopiadora copiar, FuncionDestructora destruir);

void pila_push(void *dato, Pila p);

void pila_pop(Pila p);

void *pila_top(Pila p);

void pila_destruir(Pila p);

#endif // __PILA_H_
