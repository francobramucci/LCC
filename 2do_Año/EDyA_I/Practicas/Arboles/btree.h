#ifndef __BTREE_H__
#define __BTREE_H__
#include "../Practica_3/gpilas.h"
#include <assert.h>
#include <stdlib.h>

typedef void *(*FuncionSuma)(void *dato1, void *dato2);
typedef void *(*FuncionCero)();
typedef void *(*FuncionVisitanteExtra)(void *dato, void *extra);

struct _BTNodo {
        void *dato;
        struct _BTNodo *left;
        struct _BTNodo *right;
};

typedef enum { BTREE_RECORRIDO_IN, BTREE_RECORRIDO_PRE, BTREE_RECORRIDO_POST } BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo, FuncionDestructora destroy);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void *dato, BTree left, BTree right, FuncionCopia copy);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

void *copiar_nodo_btree(void *nodo);

void destruir_generico(void *nodo);

void btree_recorrer_preorder(BTree arbol, FuncionVisitante visit);

int btree_nnodos(BTree arbol);

int btree_buscar(BTree arbol, void *dato, FuncionComparadora comp);

BTree btree_copiar(BTree arbol, FuncionCopia copy);

int btree_altura(BTree arbol);
int btree_nnodos_profundidad(BTree arbol, int profundidad);
int btree_profundidad(BTree arbol, void *dato, FuncionComparadora comp);
void *btree_sumar(BTree arbol, FuncionSuma suma, FuncionCero cero);
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit,
                          FuncionVisitanteExtra visit_extra, void *extra);
void btree_recorrer_nivel(BTree arbol, int nivel, FuncionVisitante visit);
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit);
#endif /* __BTREE_H__ */
