#ifndef __BTREE_H__
#define __BTREE_H__
#include <assert.h>
#include <stdlib.h>
#include "../Practica_3/gpilas.h"

struct _BTNodo {
	void* dato;
	struct _BTNodo *left;
	struct _BTNodo *right;
};

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

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
BTree btree_unir(void* dato, BTree left, BTree right, FuncionCopia copy);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

BTree copiar_nodo_btree(BTree nodo);

void destruir_btree_pointer(BTree nodo);

void btree_recorrer_preorder(BTree arbol, FuncionVisitante visit);

void destruir_btree_pointer(BTree nodo);

void btree_recorrer_preorder(BTree arbol, FuncionVisitante visit);

int btree_nnodos(BTree arbol);

int btree_buscar(BTree arbol, void* dato, FuncionComparadora comp);

BTree btree_copiar(BTree arbol, FuncionCopia copy);

#endif /* __BTREE_H__ */
