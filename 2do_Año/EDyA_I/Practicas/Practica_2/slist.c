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
	if (lista1 == NULL)
		return lista2;

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

SList slist_eliminar(SList lista, int posicion){
	if(lista == NULL)
		return NULL;

	if(posicion == 0){
		SNodo* segundo_elemento = lista->sig;
		free(lista);
		return segundo_elemento;
	}
	
	SNodo* anterior = lista;
	for(int i = 0; anterior->sig->sig != NULL && i < posicion-1; anterior = anterior->sig, i++);
	
	SNodo* nodoAEliminar = anterior->sig;
	anterior->sig = anterior->sig->sig;
	free(nodoAEliminar);

	return lista;
}

int slist_contiene(SList lista, int dato){
	for(int i = 0; lista->dato != dato && lista != NULL; lista= lista->sig, i++);
	return lista != NULL;
}

int slist_indice(SList lista, int dato){
	int i = 0;
	for(; lista->dato != dato && lista != NULL; lista = lista->sig, i++);

	return (lista == NULL) ? -1:0;
}

SList slist_intersecar(SList lista1, SList lista2){
	SNodo* interseccion = NULL;
	for(SNodo* temp = lista1; temp->sig != NULL; temp = temp->sig){
		if(slist_contiene(lista2, temp->dato) && !slist_contiene(interseccion, temp->dato))
			slist_agregar_inicio(interseccion, temp->dato);
	}
	return interseccion;
}

int slist_contiene_custom(SList lista, int dato, FuncionComparadora comp){
	SNodo* temp = lista;
	for(; !comp(dato, temp->dato) && temp != NULL; temp = temp->sig);

	return temp != NULL;
}

SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparadora comp){
	SNodo* interseccion = NULL;
		for(SNodo* temp = lista1; temp->sig != NULL; temp = temp->sig){
			if(slist_contiene_custom(lista2, temp->dato, comp) && !slist_contiene_custom(interseccion, temp->dato, comp))
				interseccion = slist_agregar_inicio(interseccion, temp->dato);
		}
	return interseccion;
}

SList slist_ordenar(SList lista, FuncionComparadora comp){
	if(lista == NULL)
		return NULL;

	if(lista->sig == NULL)
		return lista;

	int primer_elemento = lista->dato;
	SList elementos_goq = NULL;
	SList elementos_lt = NULL;
	
	for(SList temp = lista->sig; temp != NULL; temp = temp->sig){
		if(comp(temp->dato, primer_elemento) >= 0)
			elementos_goq = slist_agregar_inicio(elementos_goq, temp->dato);
		else
			elementos_lt = slist_agregar_inicio(elementos_lt, temp->dato);
	}

	return slist_concatenar(slist_agregar_final(slist_ordenar(elementos_lt, comp), primer_elemento), slist_ordenar(elementos_goq, comp));
}

SList slist_reverso(SList lista){
	SList reverse = NULL;
	for(SNodo* temp = lista; temp != NULL; temp = temp->sig){
		reverse = slist_agregar_inicio(reverse, temp->dato);
	}
	return reverse;
}

SList slist_intercalar(SList lista1, SList lista2){
	if(lista1 == NULL)
		return lista2;
	if(lista2 == NULL)
		return lista1;

	SList resultado = lista1;
	resultado->sig = lista2;
	resultado->sig->sig = slist_intercalar(lista1->sig, lista2->sig);

	return resultado;
}

SList slist_partir(SList lista){
	if(lista == NULL)
		return NULL;
	if(lista->sig == NULL)
		return lista;

	SNodo* mitad = lista;
	SNodo* temp = lista;
	for(; temp != NULL && temp->sig != NULL; temp = temp->sig->sig, mitad = mitad->sig);
	
	return (temp->sig == NULL) ? mitad->sig : mitad;
}


