#ifndef __DLIST_H__
#define __DLIST_H__
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct _DNodo {
	int dato;
	struct _DNodo *sig;
	struct _DNodo *ant;
} DNodo;

typedef struct {
	DNodo* primero;
	DNodo* ultimo;
} DList;

typedef enum {
	DLIST_RECORRIDO_HACIA_ADELANTE,
	DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

DList* dlist_crear();

void dlist_agregar_inicio(DList* lista, int dato);

void dlist_recorrer(DList *lista, DListOrdenDeRecorrido orden, void(*funcion)(int));

#endif /* __DLIST_H__ */
