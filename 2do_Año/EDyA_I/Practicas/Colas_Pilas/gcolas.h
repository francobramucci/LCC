#ifndef __GCOLAS_H__
#define __GCOLAS_H__
#include "../Listas/glist/glist.h"

typedef struct {
        GNode *ultimo;
        GList lista;
} _GCola;

typedef _GCola *GCola;

GCola cola_crear();

void cola_destruir(GCola cola, FuncionDestructora destroy);

int cola_es_vacia(GCola cola);

void *cola_inicio(GCola cola);

void cola_encolar(GCola cola, void *dato, FuncionCopia copy);

void cola_desencolar(GCola cola, FuncionDestructora destroy);

void cola_recorrer(GCola cola, FuncionVisitante visit);

#endif
