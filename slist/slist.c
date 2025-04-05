#include "slist.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista){
	int i = 0;
	for(; lista != NULL; lista = lista->sig, i++);
	return i;
}

SList slist_concatenar(SList lista1, SList lista2){
	SNodo *temp = lista1;
	for(; temp->sig != NULL; temp = temp->sig);
	temp->sig = lista2;
	
	return lista1;
}

SList slist_insertar(SList lista, int dato, int posicion){
	SNodo *nuevoNodo = malloc(sizeof(SNodo));
	nuevoNodo->dato = dato;
	nuevoNodo->sig = NULL;
	if(lista == NULL)
		return nuevoNodo;

	if(posicion == 0){
		nuevoNodo->sig = lista;
		return nuevoNodo;
	}

	SNodo *temp = lista;
	for(int i = 0; temp->sig != NULL && i < posicion-1; temp = temp->sig, i++);

	SNodo *aux = temp->sig;

	temp->sig = nuevoNodo;
	nuevoNodo->sig = aux;

	return lista;
}


