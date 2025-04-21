#include "gpilas.h"

GPila gpila_crear(){
	GPila gpila = glist_crear();
	return gpila;
}

void gpila_destruir(GPila gpila, FuncionDestructora destruir){
	glist_destruir(gpila, destruir);
}

int gpila_es_vacia(GPila gpila){
	return glist_vacia(gpila);
}

void* gpila_tope(GPila gpila, FuncionVisitante visit){
	return gpila->data;	
}

GPila gpila_apilar(GPila gpila, void* dato, FuncionCopia copy){
	return glist_agregar_inicio(gpila, dato, copy);
}

GPila gpila_desapilar(GPila gpila, FuncionDestructora destruir){
	GPila cola = NULL;
	if(!glist_vacia(gpila->lista)){
		cola = gpila->sig;
		destruir(gpila->data);
		free(gpila);
	}
	return cola;
}

void gpila_imprimir(GPila gpila, FuncionVisitante visit){
	glist_recorrer(gpila, visit);
}

