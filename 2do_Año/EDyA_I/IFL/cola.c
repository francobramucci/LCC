#include "cola.h"

Cola cola_crear(FuncionCopiadora copiar, FuncionDestructora destruir) {
    return dlist_crear(copiar, destruir);
}

void cola_encolar(Cola q, void *dato) {
    dlist_agregar_final(q, dato);
}

void *cola_desencolar(Cola q) {
    if (!q->primero)
        return NULL;

    void *dato = q->primero->dato;
    q->primero->dato = NULL;
    dlist_eliminar_inicio(q);

    return dato;
}

void *cola_top(Cola q) {
    if (!q->primero)
        return NULL;

    return q->primero->dato;
}
