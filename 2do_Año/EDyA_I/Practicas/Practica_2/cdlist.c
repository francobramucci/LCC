#include "cdlist.h"

CDList crear_cdlist(){
	return NULL;
}

CDList cdlist_agregar_inicio(CDList lista, int dato){
	CDNodo* nuevoNodo = malloc(sizeof(CDNodo));
	nuevoNodo->dato = dato;

	if(lista == NULL){
		nuevoNodo->ant = nuevoNodo;
		nuevoNodo->sig = nuevoNodo;
	}
	else{
		nuevoNodo->sig = lista;
		nuevoNodo->ant = lista->ant;
	}

	return nuevoNodo;
}

void cdlist_recorrer_aux(CDList lista, CDList ultimo_elemento, void(*visit)(int)){
	if(lista == ultimo_elemento)
		visit(lista->dato);

	visit(lista->dato);
	cdlist_recorrer_aux(lista->sig, ultimo_elemento, visit);
}

void cdlist_recorrer(CDList lista, void (*visit)(int)){
	cdlist_recorrer_aux(lista, lista->ant, visit);
}
