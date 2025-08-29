#include "pila.h"
#include "dlist.h"

Pila pila_crear(FuncionCopiadora copiar, FuncionDestructora destruir) {
    return dlist_crear(copiar, destruir);
}

void pila_push(void *dato, Pila p) {
    dlist_agregar_inicio(p, dato);
}

void pila_pop(Pila p) {
    dlist_eliminar_inicio(p);
}

void *pila_top(Pila p) {
    if (!p->primero)
        return p->primero->dato;
    return NULL;
}

void pila_destruir(Pila p) {
    dlist_destruir(p);
}
