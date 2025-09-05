#include "pila.h"
#include "vector.h"

Pila *pila_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir) {
    return vector_crear(capacidad, copiar, destruir);
}

void pila_push(Pila *p, void *dato) {
    vector_insertar(p, dato);
}

void pila_pop(Pila *p) {
    vector_eliminar_ultimo(p);
}

void *pila_top(Pila *p) {
    return vector_acceder(p, p->ultimo);
}

int pila_cant_elementos(Pila *p) {
    return vector_cant_elementos(p);
}

void pila_destruir(Pila *p) {
    vector_destruir(p);
}
