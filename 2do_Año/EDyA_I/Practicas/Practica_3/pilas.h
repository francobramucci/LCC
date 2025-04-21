#ifndef __PILAS_H__
#define __PILAS_H__

#include "../Practica_1/arregloenteros.h"

struct _Pila {
	ArregloEnteros *arr;
	int ultimo;
};

typedef struct _Pila *Pila;

Pila pila_crear(int capacidad);

void pila_destruir(Pila stack);

int pila_es_vacia(Pila stack);

int pila_tope(Pila stack);

void pila_apilar(Pila stack, int dato);

void pila_desapilar(Pila stack);

void pila_imprimir(Pila stack);

#endif 
