#ifndef __DLIST_H__
#define __DLIST_H__
#include <stdio.h>
#include <stdlib.h>

typedef struct _DNodo {
        int dato;
        struct _DNodo *sig;
        struct _DNodo *ant;
} DNodo;

typedef struct {
        DNodo *primero;
        DNodo *ultimo;
} DList;

DList *dlist_crear();

void dlist_agregar_inicio(DList *lista, int dato);

void dlist_agregar_final(DList *lista, int dato);

void dlist_eliminar_inicio(DList *lista);

void dlist_eliminar_final(DList *lista);

void dlist_destruir(DList *lista);

DList *dlist_copiar(DList *lista);

void dlist_imprimir(DList *lista);

#endif /* __DLIST_H__ */
