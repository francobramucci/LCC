#include "btree.h"

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() {
    return NULL;
}

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo, FuncionDestructora destroy) {
    if (nodo != NULL) {
        destroy(nodo->dato);
        btree_destruir(nodo->left, destroy);
        btree_destruir(nodo->right, destroy);
        free(nodo);
    }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) {
    return nodo == NULL;
}

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void *dato, BTree left, BTree right, FuncionCopia copy) {
    BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copy(dato);
    nuevoNodo->left = left;
    nuevoNodo->right = right;
    return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {
    if (arbol != NULL) {
        switch (orden) {
        case BTREE_RECORRIDO_IN:
            btree_recorrer(arbol->left, orden, visit);
            visit(arbol->dato);
            btree_recorrer(arbol->right, orden, visit);
            break;
        case BTREE_RECORRIDO_PRE:
            visit(arbol->dato);
            btree_recorrer(arbol->left, orden, visit);
            btree_recorrer(arbol->right, orden, visit);
            break;
        case BTREE_RECORRIDO_POST:
            btree_recorrer(arbol->left, orden, visit);
            btree_recorrer(arbol->right, orden, visit);
            visit(arbol->dato);
            break;
        }
    }
}

void *copiar_nodo_btree(void *nodo) {
    return nodo;
}

void destruir_generico(void *nodo) {
    return;
}

void btree_recorrer_preorder(BTree arbol, FuncionVisitante visit) {
    GPila pila = gpila_crear();
    pila = gpila_apilar(pila, arbol, copiar_nodo_btree);
    BTree nodo_a_procesar;

    while (!gpila_es_vacia(pila)) {
        nodo_a_procesar = gpila_tope(pila);
        pila = gpila_desapilar(pila, destruir_generico);

        visit(nodo_a_procesar->dato);
        if (nodo_a_procesar->right != NULL)
            pila = gpila_apilar(pila, nodo_a_procesar->right, copiar_nodo_btree);
        if (nodo_a_procesar->left != NULL)
            pila = gpila_apilar(pila, nodo_a_procesar->left, copiar_nodo_btree);
    }
    gpila_destruir(pila, destruir_generico);
}

int btree_nnodos(BTree arbol) {
    if (btree_empty(arbol))
        return 0;
    return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

int btree_buscar(BTree arbol, void *dato, FuncionComparadora comp) {
    if (btree_empty(arbol))
        return 0;
    return comp(dato, arbol->dato) == 0 || btree_buscar(arbol->left, dato, comp) ||
           btree_buscar(arbol->right, dato, comp);
}

BTree btree_copiar(BTree arbol, FuncionCopia copy) {
    if (btree_empty(arbol))
        return NULL;
    BTree copia = btree_crear();
    copia = btree_unir(arbol->dato, btree_copiar(arbol->left, copy), btree_copiar(arbol->right, copy), copy);

    return copia;
}
