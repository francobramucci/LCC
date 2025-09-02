#include "pila.h"
#include "dlist.h"

Pila pila_crear() {
    return dlist_crear();
}

void pila_push(Pila p, int dato) {
    dlist_agregar_inicio(p, dato);
}

void pila_pop(Pila p) {
    dlist_eliminar_inicio(p);
}

int pila_top(Pila p) {
    if (!p->primero)
        return -1;

    return p->primero->dato;
}

void pila_destruir(Pila p) {
    dlist_destruir(p);
}
