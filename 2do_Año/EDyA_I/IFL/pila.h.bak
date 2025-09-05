#ifndef __PILA_H_
#define __PILA_H_

#include "dlist.h"

typedef DList *Pila;

/*
 * Crea una pila vacía y retorna un puntero a ella.
 */
Pila pila_crear();

/*
 * Inserta un elemento en el tope de la pila.
 */
void pila_push(Pila p, int dato);

/*
 * Elimina el elemento en el tope de la pila.
 */
void pila_pop(Pila p);

/*
 * Retorna el valor almacenado en el tope de la pila sin eliminarlo.
 * Si la pila está vacía, retorna -1.
 */
int pila_top(Pila p);

/*
 * Libera toda la memoria asociada a la pila.
 */
void pila_destruir(Pila p);

#endif // __PILA_H_
