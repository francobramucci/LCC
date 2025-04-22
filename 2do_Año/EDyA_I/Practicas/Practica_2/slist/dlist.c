#include "dlist.h"

DList* dlist_crear(){
	DList *lista = malloc(sizeof(DList));
	lista->primero = NULL;
	lista->ultimo = NULL;

	return lista;
}

void dlist_agregar_inicio(DList* lista, int dato){
	DNodo* nuevoNodo = malloc(sizeof(DNodo));
	nuevoNodo->dato = dato;
	nuevoNodo->sig = lista->primero;
	nuevoNodo->ant = NULL;

	if(lista->primero == NULL){
		lista->primero = nuevoNodo;
	}
	else{
		lista->primero->ant = nuevoNodo;
		lista->primero = nuevoNodo;
	}

	if(lista->ultimo == NULL)
		lista->ultimo = nuevoNodo;
}

void dlist_recorrer(DList *lista, DListOrdenDeRecorrido orden, void(*funcion)(int)){
	if(!orden){
		for(DNodo* temp = lista->primero; temp != NULL; temp = temp->sig)
			funcion(temp->dato);
	}
	else{
		for(DNodo* temp = lista->ultimo; temp != NULL; temp = temp->ant)
			funcion(temp->dato);
	}
}



