#ifndef __PILA_H_
#define __PILA_H_

#include "vector.h"

typedef Vector Pila;

/**
 * Crea una pila vacía y retorna un puntero a ella.
 */
Pila *pila_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir);

/**
 * Inserta un elemento en el tope de la pila.
 */
void pila_push(Pila *p, void *dato);

/**
 * Elimina el elemento en el tope de la pila.
 */
void pila_pop(Pila *p);

/**
 * Retorna el valor almacenado en el tope de la pila sin eliminarlo.
 * Si la pila está vacía, retorna -1.
 */
void *pila_top(Pila *p);

/**
 * Libera toda la memoria asociada a la pila.
 */
void pila_destruir(Pila *p);

/**
 * Retorna 1 si la pila es vacia y 0 si no.
 */
int pila_es_vacia(Pila *p);

/*
 * Libera toda la memoria asociada a la pila.
 */
int pila_largo(Pila *p);

#endif // __PILA_H_
