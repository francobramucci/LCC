#ifndef __SGLIST_H__
#define __SGLIST_H__

#include "glist.h"

typedef GList SGList;

SGList sglist_crear();

void sglist_destruir(SGList lista, FuncionDestructora destroy);

int sglist_vacia(SGList lista);

void sglist_recorrer(SGList lista, FuncionVisitante visit);

SGList sglist_insertar(SGList lista, void *dato, FuncionCopia copy, FuncionComparadora comp);

int sglist_buscar(SGList lista, void *datoABuscar, FuncionComparadora comp);

SGList sglist_arr(void **arr, int longitud, FuncionCopia copy, FuncionComparadora comp);

#endif
