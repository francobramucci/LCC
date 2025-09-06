#include "dlist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DList *dlist_crear() {
    DList *lista = malloc(sizeof(DList));
    assert(lista);
    lista->primero = NULL;
    lista->ultimo = NULL;

    return lista;
}

void dlist_agregar_inicio(DList *lista, int dato) {
    DNodo *nuevoNodo = malloc(sizeof(DNodo));
    assert(nuevoNodo);
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista->primero;
    nuevoNodo->ant = NULL;

    if (lista->primero != NULL)
        lista->primero->ant = nuevoNodo;
    lista->primero = nuevoNodo;

    if (lista->ultimo == NULL)
        lista->ultimo = nuevoNodo;
}

void dlist_agregar_final(DList *lista, int dato) {
    DNodo *nuevoNodo = malloc(sizeof(DNodo));
    assert(nuevoNodo);
    nuevoNodo->dato = dato;
    nuevoNodo->ant = lista->ultimo;
    nuevoNodo->sig = NULL;

    if (lista->ultimo != NULL)
        lista->ultimo->sig = nuevoNodo;
    lista->ultimo = nuevoNodo;

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

int dlist_igual(DList *l1, DList *l2) {
    if ((l1 && !l2) || (!l1 && l2))
        return 0;
    if (!l1 && !l2)
        return 1;

    DNodo *temp1 = l1->primero;
    DNodo *temp2 = l2->primero;
    int sonIguales = 1;

    while (temp1 && temp2 && sonIguales) {
        if (temp1->dato != temp2->dato)
            sonIguales = 0;

        temp1 = temp1->sig;
        temp2 = temp2->sig;
    }

    if (temp1 || temp2)
        return 0;

    return sonIguales;
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

int dlist_largo_mayor_a_uno(DList *lista) {
    return lista->primero && lista->primero->sig;
}

int dlist_comparar_extremos(DList *lista) {
    return lista->primero->dato == lista->ultimo->dato;
}

void dlist_convertir(DList *lista, DList *listaParametro) {
    DNodo *temp1 = lista->primero;
    DNodo *temp2 = listaParametro->primero;

    while (temp1 != NULL && temp2 != NULL) {
        temp1->dato = temp2->dato;
        temp1 = temp1->sig;
        temp2 = temp2->sig;
    }

    if (!temp1 && !temp2)
        return;

    if (temp1 && !temp2) {
        while (temp1->sig != NULL) {
            dlist_eliminar_final(lista);
        }
        dlist_eliminar_final(lista);
        return;
    }

    if (!temp1 && temp2) {
        while (temp2 != NULL) {
            dlist_agregar_final(lista, temp2->dato);
            temp2 = temp2->sig;
        }
    }
}
