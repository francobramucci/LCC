#include "lista.h"
#include "dlist.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Lista *lista_crear() {
    Lista *lista = malloc(sizeof(Lista));
    assert(lista);
    lista->dlist = dlist_crear((FuncionCopiadora)copiar_entero, (FuncionDestructora)destruir_entero);

    return lista;
}

void lista_destruir(Lista *lista) {
    if (lista) {
        dlist_destruir(lista->dlist);
        free(lista);
    }
}

int lista_comparar_extremos(Lista *lista) {
    return dlist_comparar_extremos(lista->dlist, (FuncionComparadora)comparar_enteros);
}

void lista_agregar_inicio(Lista *lista, int nat) {
    dlist_agregar_inicio(lista->dlist, &nat);
}

void lista_agregar_final(Lista *lista, int nat) {
    dlist_agregar_final(lista->dlist, &nat);
}

void lista_incrementar_izq(Lista *lista) {
    (*(int *)lista->dlist->primero->dato)++;
}

void lista_incrementar_der(Lista *lista) {
    (*(int *)lista->dlist->ultimo->dato)++;
}

void lista_eliminar_izq(Lista *lista) {
    dlist_eliminar_inicio(lista->dlist);
}

void lista_eliminar_der(Lista *lista) {
    dlist_eliminar_final(lista->dlist);
}

Lista *lista_copiar(Lista *lista) {
    Lista *listaCopia = malloc(sizeof(Lista));
    assert(listaCopia);
    listaCopia->dlist = dlist_copiar(lista->dlist);

    return listaCopia;
}

int lista_es_vacia(Lista *lista) {
    return dlist_es_vacia(lista->dlist);
}

int lista_igual(Lista *l1, Lista *l2) {
    return dlist_igual(l1->dlist, l2->dlist, (FuncionComparadora)comparar_enteros);
}

void lista_imprimir(Lista *lista) {
    if (lista->dlist != NULL) {
        printf("[");
        for (DNodo *temp = lista->dlist->primero; temp != NULL; temp = temp->sig) {
            printf("%d", *(int *)temp->dato);
            if (temp->sig != NULL)
                printf(",");
        }
        printf("]");
    }
}

int lista_largo_mayor_a_uno(Lista *lista) {
    return dlist_largo_mayor_a_uno(lista->dlist);
}
