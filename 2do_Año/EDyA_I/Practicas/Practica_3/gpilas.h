#ifndef __GPILA_H__
#define __GPILA_H__

#include "../Practica_2/glist/glist.h"

typedef GList GPila;

GPila gpila_crear();

void gpila_destruir(GPila gpila, FuncionDestructora destruir);

int gpila_es_vacia(GPila gpila);

void *gpila_tope(GPila gpila);

GPila gpila_apilar(GPila gpila, void *dato, FuncionCopia copy);

GPila gpila_desapilar(GPila gpila, FuncionDestructora destruir);

void gpila_imprimir(GPila gpila, FuncionVisitante visit);

void *copia_simbolica(void *dato);

void _destruir(void *dato);

void glist_reversa(GList lista);

#endif
