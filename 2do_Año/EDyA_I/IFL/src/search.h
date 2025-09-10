#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "apply.h"

/**
 * Busca una función de lista que transforme el primer elementro de cada par de listas (posicion par) en el
 * segundo (posicion impar) en paresDeListas.
 * Si se encuentra una función válida, la imprime.
 * Si no, imprime un mensaje indicando que no se ha encontrado.
 */
void search(Vector *paresDeListas, THash *tablaFunciones);

#endif // __SEARCH_H__
