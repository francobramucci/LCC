#ifndef __PILA_H_
#define __PILA_H_

#include "dlist.h"

typedef DList *Pila;

Pila pila_crear();

void pila_push(int dato, Pila p);

void pila_pop(Pila p);

int pila_top(Pila p);

void pila_destruir(Pila p);

#endif // __PILA_H_
