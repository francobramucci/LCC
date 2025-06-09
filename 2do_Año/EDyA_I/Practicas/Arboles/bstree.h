#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
    BTREE_RECORRIDO_IN,  /** Inorden */
    BTREE_RECORRIDO_PRE, /** Preorden */
    BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;

struct _BST_Nodo {
        void *dato;
        struct _BST_Nodo *izq;
        struct _BST_Nodo *der;
};

typedef struct _BST_Nodo *BSTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstree_crear();

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree, FuncionDestructora);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree, void *, FuncionComparadora);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
BSTree bstree_insertar(BSTree, void *, FuncionCopiadora, FuncionComparadora);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree, BSTreeRecorrido, FuncionVisitanteExtra, void *extra);

int bstree_validar_aux(BSTree arbol, void **max, FuncionComparadora comp);

int bstree_validar(BSTree arbol, FuncionComparadora comp);

BSTree bstree_extraer_minimo(BSTree arbol);

BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora comp, FuncionDestructora destroy);

void *obtener_k_esimo_menor(BSTree arbol, int *punteroK);

void *bstree_k_esimo_menor(BSTree arbol, int k);

#endif //__BSTREE_H__
