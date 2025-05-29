#include "bstree.h"

/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */

/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstree_crear() {
    return NULL;
}

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
    if (raiz != NULL) {
        bstree_destruir(raiz->izq, destr);
        bstree_destruir(raiz->der, destr);
        destr(raiz->dato);
        free(raiz);
    }
};

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
    if (raiz == NULL)
        return 0;
    else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
        return 1;
    else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
        return bstree_buscar(raiz->izq, dato, comp);
    else // raiz->dato < dato
        return bstree_buscar(raiz->der, dato, comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
BSTree bstree_insertar(BSTree raiz, void *dato, FuncionCopiadora copia, FuncionComparadora comp) {
    if (raiz == NULL) { // insertar el dato en un nuevo nodo
        struct _BST_Nodo *nuevoNodo = malloc(sizeof(struct _BST_Nodo));
        assert(nuevoNodo != NULL);
        nuevoNodo->dato = copia(dato);
        nuevoNodo->izq = nuevoNodo->der = NULL;
        return nuevoNodo;
    } else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
        raiz->izq = bstree_insertar(raiz->izq, dato, copia, comp);
    else if (comp(dato, raiz->dato) > 0) // raiz->dato < dato
        raiz->der = bstree_insertar(raiz->der, dato, copia, comp);
    // si el dato ya se encontraba, no es insertado
    return raiz;
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden, FuncionVisitanteExtra visita, void *extra) {
    if (raiz != NULL) {
        if (orden == BTREE_RECORRIDO_PRE) {
            visita(raiz->dato, extra);
            bstree_recorrer(raiz->izq, orden, visita, extra);
            bstree_recorrer(raiz->der, orden, visita, extra);
        }
        if (orden == BTREE_RECORRIDO_IN) {
            bstree_recorrer(raiz->izq, orden, visita, extra);
            visita(raiz->dato, extra);
            bstree_recorrer(raiz->der, orden, visita, extra);
        }
        if (orden == BTREE_RECORRIDO_POST) {
            bstree_recorrer(raiz->izq, orden, visita, extra);
            bstree_recorrer(raiz->der, orden, visita, extra);
            visita(raiz->dato, extra);
        }
    }
}

int bstree_validar_aux(BSTree arbol, void **max, FuncionComparadora comp) {
    if (arbol == NULL)
        return 1;

    if (!bstree_validar_aux(arbol->izq, max, comp))
        return 0;

    if (*max != NULL && comp(arbol->dato, *max) <= 0)
        return 0;

    *max = arbol->dato;

    return bstree_validar_aux(arbol->der, max, comp);
}

int bstree_validar(BSTree arbol, FuncionComparadora comp) {
    void *max = NULL;
    return bstree_validar_aux(arbol, &max, comp);
}

BSTree bstree_padre_minimo_derecho(BSTree arbol) {
    if (arbol == NULL || arbol->der == NULL)
        return NULL;
    if (arbol->der->izq != NULL)
        for (arbol = arbol->der; arbol->izq->izq != NULL; arbol = arbol->izq)
            ;
    return arbol;
}

BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora comp, FuncionDestructora destroy) {
    if (arbol == NULL)
        return arbol;

    if (comp(dato, arbol->dato) > 0)
        arbol->der = bstree_eliminar(arbol->der, dato, comp, destroy);

    if (comp(dato, arbol->dato) < 0)
        arbol->izq = bstree_eliminar(arbol->izq, dato, comp, destroy);

    if (comp(dato, arbol->dato) == 0) {
        if (arbol->izq == NULL && arbol->der == NULL) {
            bstree_destruir(arbol, destroy);
            return NULL;
        }
        if (arbol->izq != NULL && arbol->der != NULL) {
            BSTree padreMinimo = bstree_padre_minimo_derecho(arbol);
            int condicion = comp(padreMinimo->dato, arbol->dato) == 0;
            BSTree minimo = condicion ? padreMinimo->der : padreMinimo->izq;
            destroy(arbol->dato);
            arbol->dato = minimo->dato;

            if (condicion) {
                padreMinimo->der = minimo->der;
            } else {
                padreMinimo->izq = minimo->der;
            }

            free(minimo);

            return arbol;
        } else {
            BSTree nodoNoNulo = arbol->izq != NULL ? arbol->izq : arbol->der;
            destroy(arbol->dato);
            free(arbol);
            return nodoNoNulo;
        }
    }
    return arbol;
}
