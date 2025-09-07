#ifndef __LISTA_H__
#define __LISTA_H__

#include "dlist.h"

typedef struct {
        DList *dlist;
} Lista;

/**
 * Crea una nueva lista vacía.
 */
Lista *lista_crear();

/**
 * Destruye una lista liberando toda la memoria asociada.
 */
void lista_destruir(Lista *lista);

/**
 * Compara los elementos de los extremos de la lista.
 * Retorna 1 si son iguales, 0 en caso contrario.
 */
int lista_comparar_extremos(Lista *lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
void lista_agregar_inicio(Lista *lista, int nat);

/**
 * Agrega un elemento al final de la lista.
 */
void lista_agregar_final(Lista *lista, int nat);

/**
 * Incrementa en uno el valor del primer elemento de la lista.
 */
void lista_incrementar_izq(Lista *lista);

/**
 * Incrementa en uno el valor del último elemento de la lista.
 */
void lista_incrementar_der(Lista *lista);

/**
 * Elimina el primer elemento de la lista.
 */
void lista_eliminar_izq(Lista *lista);

/**
 * Elimina el último elemento de la lista.
 */
void lista_eliminar_der(Lista *lista);

/**
 * Retorna una copia de la lista recibida.
 */
Lista *lista_copiar(Lista *lista);

/**
 * Retorna 1 si la lista está vacía, 0 en caso contrario.
 */
int lista_es_vacia(Lista *lista);

/**
 * Retorna 1 si dos listas son iguales, 0 en caso contrario.
 */
int lista_igual(Lista *l1, Lista *l2);

/**
 * Imprime el contenido de la lista.
 */
void lista_imprimir(Lista *lista);

/**
 * Retorna 1 si la lista tiene largo mayor a uno, 0 en caso contrario.
 */
int lista_largo_mayor_a_uno(Lista *lista);

#endif
