#include "pilas.h"

Pila pila_crear(int capacidad){
	Pila stack = malloc(sizeof(struct _Pila));
	stack->arr = arreglo_enteros_crear(capacidad);
	stack->ultimo = -1;

	return stack;
}

void pila_destruir(Pila stack){
	arreglo_enteros_destruir(stack->arr);
	free(stack);
}

int pila_es_vacia(Pila stack){
	return stack->ultimo == -1 ? 1 : 0;
}

int pila_tope(Pila stack){
	return stack->arr[stack->ultimo];
}

void pila_apilar(Pila stack, int dato){
	int capacidad = arreglo_enteros_capacidad(stack->arr);

	if(stack->ultimo == capacidad - 1)
		arreglo_enteros_ajustar(stack->arr, capacidad*2);
	stack->ultimo += 1;
	stack->arr[stack->ultimo] = dato;
}

void pila_desapilar(Pila stack){
	stack->ultimo -= 1;
}

void pila_imprimir(Pila stack){
	for(int i = 0; i <= stack->ultimo; i++){
		printf("%d ", stack[i]);
	}
}


