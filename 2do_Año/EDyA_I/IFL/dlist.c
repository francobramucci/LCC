#include "dlist.h"

DList *dlist_crear() {
    DList *lista = malloc(sizeof(DList));
    lista->primero = NULL;
    lista->ultimo = NULL;

    return lista;
}

void dlist_agregar_inicio(DList *lista, int dato) {
    DNodo *nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista->primero;
    nuevoNodo->ant = NULL;

    if (lista->primero == NULL) {
        lista->primero = nuevoNodo;
    } else {
        lista->primero->ant = nuevoNodo;
        lista->primero = nuevoNodo;
    }

    if (lista->ultimo == NULL)
        lista->ultimo = nuevoNodo;
}

void dlist_agregar_final(DList *lista, int dato) {
    DNodo *nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->ant = lista->ultimo;
    nuevoNodo->sig = NULL;

    if (lista->ultimo == NULL) {
        lista->ultimo = nuevoNodo;
    } else {
        lista->ultimo->sig = nuevoNodo;
        lista->ultimo = nuevoNodo;
    }

    if (lista->primero == NULL)
        lista->primero = nuevoNodo;
}

void dlist_eliminar_inicio(DList *lista) {
    if (lista->primero != NULL) {
        if (lista->primero->sig == NULL) {
            free(lista->primero);
            lista->primero = NULL;
            lista->ultimo = NULL;
        } else {
            DNodo *segundo = lista->primero->sig;
            segundo->ant = NULL;
            free(lista->primero);
            lista->primero = segundo;
        }
    }
}

void dlist_eliminar_final(DList *lista) {
    if (lista->ultimo != NULL) {
        if (lista->ultimo->ant == NULL) {
            free(lista->ultimo);
            lista->ultimo = NULL;
            lista->primero = NULL;
        } else {
            DNodo *penultimo = lista->ultimo->ant;
            penultimo->sig = NULL;
            free(lista->ultimo);
            lista->ultimo = penultimo;
        }
    }
}

void dlist_destruir(DList *lista) {
    if (lista != NULL) {
        DNodo *nodoAEliminar;
        while (lista->primero != NULL) {
            nodoAEliminar = lista->primero;
            lista->primero = lista->primero->sig;
            free(nodoAEliminar);
        }
    }
    free(lista);
}

DList *dlist_copiar(DList *lista) {
    DList *nuevaLista = dlist_crear();
    if (lista) {
        for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig)
            dlist_agregar_final(nuevaLista, temp->dato);
    }

    return nuevaLista;
}

void dlist_imprimir(DList *lista) {
    if (lista != NULL) {
        printf("[");
        for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
            printf("%d", temp->dato);
            if (temp->sig != NULL)
                printf(",");
        }
        printf("]");
    }
}
