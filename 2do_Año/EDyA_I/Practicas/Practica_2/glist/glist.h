#ifndef __GLIST_H__
#define __GLIST_H__
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);

typedef struct _GNode {
        void *data;
        struct _GNode *next;
} GNode;

typedef GNode *GList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * Dada una lista de contactos y un predicado, devuelve una lista con los
 * contactos que cumplen el predicado
 */
GList glist_filtrar(GList lista, FuncionCopia copy, Predicado predicado);

#endif /* __GLIST_H__ */
