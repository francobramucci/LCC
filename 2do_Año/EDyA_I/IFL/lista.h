#ifndef __LISTA_H__
#define __LISTA_H__

#include "dlist.h"

typedef struct {
        DList *dlist;
} Lista;

Lista *lista_crear();

void lista_destruir(Lista *lista);

int lista_comparar_extremos(Lista *lista);

void lista_agregar_inicio(Lista *lista, int nat);

void lista_agregar_final(Lista *lista, int nat);

void lista_incrementar_izq(Lista *lista);

void lista_incrementar_der(Lista *lista);

void lista_eliminar_izq(Lista *lista);

void lista_eliminar_der(Lista *lista);

Lista *lista_copiar(Lista *lista);

int lista_es_vacia(Lista *lista);

int lista_igual(Lista *l1, Lista *l2);

void lista_imprimir(Lista *lista);

int lista_largo_mayor_a_uno(Lista *lista);

void lista_convertir(Lista *lista, Lista *listaParametro);

#endif
