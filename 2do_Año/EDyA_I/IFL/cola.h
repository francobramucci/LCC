#ifndef __COLA_H__
#define __COLA_H__
#include "dlist.h"

typedef DList *Cola;

Cola cola_crear(FuncionCopiadora copiar, FuncionDestructora destruir);

void cola_encolar(Cola q, void *dato);

void *cola_desencolar(Cola q);

void *cola_top(Cola q);

#endif // !__COLA_H__
