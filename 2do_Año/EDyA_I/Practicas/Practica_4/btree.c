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
BTree btree_unir(void* dato, BTree left, BTree right, FuncionCopia copy) {
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
	if(arbol != NULL){
		if(orden == 0){ /* IN */
			btree_recorrer(arbol->left, orden, visit);
			visit(arbol->dato);
			btree_recorrer(arbol->right, orden, visit);
		}

		if(orden == 1){ /* PRE */
			visit(arbol->dato);
			btree_recorrer(arbol->left, orden, visit);
			btree_recorrer(arbol->right, orden, visit);
		}

		if(orden == 2){ /*POST*/
			btree_recorrer(arbol->left, orden, visit);
			btree_recorrer(arbol->right, orden, visit);
			visit(arbol->dato);
		}
	}
}

BTree copiar_nodo_btree(BTree nodo){
	return nodo;
}

void destruir_btree_pointer(BTree nodo){
	return;
}

void btree_recorrer_preorder(BTree arbol, FuncionVisitante visit) {
	GPila pila = gpila_crear();
	pila = gpila_apilar(pila, arbol, (FuncionCopia) copiar_nodo_btree);
	BTree nodo_procesado = arbol;

	while(!gpila_es_vacia(pila)){
		while(nodo_procesado != NULL){
			visit(nodo_procesado->dato);
			nodo_procesado = nodo_procesado->left;
			if(nodo_procesado != NULL){
				pila = gpila_apilar(pila, nodo_procesado, (FuncionCopia) copiar_nodo_btree);
			}
		}
		
		nodo_procesado = gpila_tope(pila, (FuncionVisitante) visit);
		nodo_procesado = nodo_procesado->right;
		pila = gpila_desapilar(pila, (FuncionDestructora) destruir_btree_pointer);
		if(nodo_procesado != NULL)
			pila = gpila_apilar(pila, nodo_procesado, (FuncionCopia) copiar_nodo_btree); 
	}

	gpila_destruir(pila, (FuncionDestructora) destruir_btree_pointer);
}

int btree_nnodos(BTree arbol){
	if(btree_empty(arbol))
		return 0;
	return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

int btree_buscar(BTree arbol, void* dato, FuncionComparadora comp){
	if(btree_empty(arbol))
		return 0;
	return comp(dato, arbol->dato) == 0 || btree_buscar(arbol->left, dato, comp) || btree_buscar(arbol->right, dato, comp);
}

BTree btree_copiar(BTree arbol, FuncionCopia copy){
	if(btree_empty(arbol))
		return NULL;
	BTree copia = btree_crear();
	copia = btree_unir(arbol->dato, btree_copiar(arbol->left, copy), btree_copiar(arbol->right, copy), copy);

	return copia;
}





