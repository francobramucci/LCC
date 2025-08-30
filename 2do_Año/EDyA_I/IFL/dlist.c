#include "dlist.h"

DList *dlist_crear(FuncionCopiadora copiar, FuncionDestructora destruir) {
    DList *lista = malloc(sizeof(DList));
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->copiar = copiar;
    lista->destruir = destruir;

    return lista;
}

void dlist_agregar_inicio(DList *lista, void *dato) {
    DNodo *nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = lista->copiar(dato);
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

void dlist_agregar_final(DList *lista, void *dato) {
    DNodo *nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = lista->copiar(dato);
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
            lista->destruir(lista->primero->dato);
            free(lista->primero);
            lista->primero = NULL;
            lista->ultimo = NULL;
        } else {
            DNodo *segundo = lista->primero->sig;
            segundo->ant = NULL;
            lista->destruir(lista->primero->dato);
            free(lista->primero);
            lista->primero = segundo;
        }
    }
}

void dlist_eliminar_final(DList *lista) {
    if (lista->ultimo != NULL) {
        if (lista->ultimo->ant == NULL) {
            lista->destruir(lista->ultimo->dato);
            free(lista->ultimo);
            lista->ultimo = NULL;
            lista->primero = NULL;
        } else {
            DNodo *penultimo = lista->ultimo->ant;
            penultimo->sig = NULL;
            lista->destruir(lista->ultimo->dato);
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
            lista->destruir(nodoAEliminar->dato);
            free(nodoAEliminar);
        }
    }
    free(lista);
}

DList *dlist_copiar(DList *lista) {
    DList *nuevaLista = dlist_crear(lista->copiar, lista->destruir);
    if (lista) {
        for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig)
            dlist_agregar_final(nuevaLista, temp->dato);
    }

    return nuevaLista;
}

int dlist_comparar(DList *l1, DList *l2, FuncionComparadora comparar) {
    if (l1 && !l2 || !l1 && l2)
        return 0;
    if (!l1 && !l2)
        return 1;

    DNodo *temp1 = l1->primero;
    DNodo *temp2 = l2->primero;
    int sonIguales = 1;

    while (temp1 && temp2 && sonIguales) {
        if (comparar(temp1->dato, temp2->dato))
            sonIguales = 0;

        temp1 = temp1->sig;
        temp2 = temp2->sig;
    }

    if (temp1 || temp2)
        return 0;

    return sonIguales;
}

void dlist_imprimir(DList *lista, FuncionVisitante visitar) {
    if (lista != NULL) {
        printf("[");
        for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
            visitar(temp->dato);
            if (temp->sig != NULL)
                printf(",");
        }
        printf("]");
    }
}
