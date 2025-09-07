#include "pila.h"
#include "dlist.h"
#include <stdlib.h>

Pila *pila_crear(FuncionCopiadora copiar, FuncionDestructora destruir) {
    Pila *pila = malloc(sizeof(Pila));
    pila->dlist = dlist_crear(copiar, destruir);

    return pila;
}

void pila_push(Pila *p, void *dato) {
    dlist_agregar_inicio(p->dlist, dato);
}

void pila_pop(Pila *p) {
    dlist_eliminar_inicio(p->dlist);
}

void *pila_top(Pila *p) {
    if (p && !dlist_es_vacia(p->dlist))
        return p->dlist->primero->dato;
    return NULL;
}

int pila_es_vacia(Pila *p) {
    return dlist_es_vacia(p->dlist);
}

void pila_destruir(Pila *p) {
    if (p) {
        dlist_destruir(p->dlist);
        free(p);
    }
}
