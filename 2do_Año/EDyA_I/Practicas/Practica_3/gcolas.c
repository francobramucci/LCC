#include "gcolas.h"

GCola cola_crear() {
    GCola cola = (GCola)malloc(sizeof(_GCola));
    cola->ultimo = NULL;
    cola->lista = glist_crear();
    return cola;
}

void cola_destruir(GCola cola, FuncionDestructora destroy) {
    glist_destruir(cola->lista, destroy);
    free(cola);
}

int cola_es_vacia(GCola cola) {
    return glist_vacia(cola->lista);
}

void *cola_inicio(GCola cola) {
    return cola->lista->data;
}

void cola_encolar(GCola cola, void *dato, FuncionCopia copy) {
    if (cola_es_vacia(cola)) {
        cola->lista = glist_agregar_inicio(cola->lista, dato, copy);
        cola->ultimo = cola->lista;
    } else {
        cola->ultimo->next = glist_agregar_inicio(NULL, dato, copy);
    }
}

void cola_desencolar(GCola cola, FuncionDestructora destroy) {
    GNode *nodoAEliminar = cola->lista;
    cola->lista = cola->lista->next;
    destroy(nodoAEliminar->data);
    free(nodoAEliminar);
}

void cola_recorrer(GCola cola, FuncionVisitante visit) {
    glist_recorrer(cola->lista, visit);
}
