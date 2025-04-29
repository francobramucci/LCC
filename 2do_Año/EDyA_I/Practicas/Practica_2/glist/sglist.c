#include "sglist.h"

SGList sglist_crear() {
    return NULL;
}

void sglist_destruir(SGList lista, FuncionDestructora destroy) {
    glist_destruir(lista, destroy);
}

int sglist_vacia(SGList lista) {
    return glist_vacia(lista);
}

void sglist_recorrer(SGList lista, FuncionVisitante visit) {
    glist_recorrer(lista, visit);
}

SGList sglist_insertar(SGList lista, void *dato, FuncionCopia copy, FuncionComparadora comp) {
    if (sglist_vacia(lista)) {
        GNode *nuevoNodo = malloc(sizeof(GNode));
        nuevoNodo->data = dato;
        nuevoNodo->next = NULL;
        return nuevoNodo;
    }
    if (comp(dato, lista->data) >= 0) {
        GNode *nuevoNodo = malloc(sizeof(GNode));
        nuevoNodo->data = dato;
        nuevoNodo->next = lista;
        return nuevoNodo;
    } else {
        lista->next = sglist_insertar(lista->next, dato, copy, comp);
    }
    return lista;
}

int sglist_buscar(SGList lista, void *datoABuscar, FuncionComparadora comp) {
    if (sglist_vacia(lista))
        return 0;
    if (comp(datoABuscar, lista->data) == 0)
        return 1;
    if (comp(datoABuscar, lista->data) == 1)
        return 0;
    return sglist_buscar(lista->next, datoABuscar, comp);
}

SGList sglist_arr(void **arr, int longitud, FuncionCopia copy, FuncionComparadora comp) {
    SGList lista = sglist_crear();
    for (int i = 0; i < longitud; i++) {
        sglist_insertar(lista, arr[i], copy, comp);
    }

    return lista;
}
