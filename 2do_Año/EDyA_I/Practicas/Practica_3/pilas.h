#ifndef __PILAS_H__
#define __PILAS_H__

#include "arregloenteros.h"

struct _Pila {
	ArregloEnteros *arr;
	int ultimo;
};

typedef struct _Pila *Pila;

