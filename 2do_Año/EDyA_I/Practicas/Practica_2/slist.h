#ifndef __SLIST_H__
#define __SLIST_H__
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef int (*FuncionComparadora) (int dato1, int dato2);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

typedef struct SListF{
	SNodo* primero;
	SNodo* ultimo;
} SListF;


/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/**
 * Dada una lista, retorna la longitud de la lista.
 */
int slist_longitud(SList lista);

/**
 * Concatena dos listas dadas.
 */
SList slist_concatenar(SList lista1, SList lista2);

/**
 * Inserta un nuevo nodo con un dato en la posición dada en una lista.
 */
SList slist_insertar(SList lista, int dato, int posicion);

/** 
 * Dadas una lista y un elemento, devuelve si el elemento está presente en la
 * lista
 */
int slist_contiene(SList lista, int dato);

/**
 * Dada una lista y un elemento, devuelve la posicion del elemento o -1 si no
 * está.
 */
int slist_indice(SList lista, int dato);

/**
 * Dadas dos listas, devuelve otra con los elementos en común a ambas.
 */
SList slist_intersecar(SList lista1, SList lista2);

/**
 * Dada una lista, un elemento y una funcion comparadora que define la
 * igualdad, devuelve si el elemento está o no.
 */
int slist_contiene_custom(SList lista, int dato, FuncionComparadora comp);

/**
 * Dadas dos listas y una funcion comparadora, devuelve los elementos comunes a
 * ambas listas.
 */
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparadora comp);

/**
 * Dada una lista y una funcion comparadora, ordena la lista.
 */
SList slist_ordenar(SList lista, FuncionComparadora comp);

/**
 * Dada una lista, retorna su reverso.
 */
SList slist_reverso(SList lista);

/**
 * Dadas dos listas, retorna otra con los elementos de ambas listas
 * intercalados.
 */
SList slist_intercalar(SList lista1, SList lista2);

/**
 * Dada una lista, devuelve el puntero a la segunda mitad de la lista
 */
SList slist_partir(SList lista);

SListF* slistf_crear();

void slistf_agregar_inicio(SListF* lista, int dato);

void slistf_agregar_final(SListF* lista, int dato);

void slistf_recorrer_R_bad(SListF* lista, void(*funcion)(int));

void slistf_recorrer_R_aux(SNodo* nodo, void(*funcion)(int));

void slistf_recorrer_R_ok(SListF* lista, void(*funcion)(int));

#endif /* __SLIST_H__ */
