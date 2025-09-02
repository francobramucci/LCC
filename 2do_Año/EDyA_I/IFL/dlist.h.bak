#ifndef __DLIST_H__
#define __DLIST_H__
#include <stdio.h>
#include <stdlib.h>

typedef void *(*FuncionCopiadora)(void *);
typedef void (*FuncionDestructora)(void *);
typedef int (*FuncionComparadora)(void *a, void *b); // 1 si a > b, 0 si a == b y -1 si a < b
typedef void (*FuncionVisitante)(void *);

typedef struct _DNodo {
        void *dato;
        struct _DNodo *sig;
        struct _DNodo *ant;
} DNodo;

typedef struct {
        DNodo *primero;
        DNodo *ultimo;
        FuncionCopiadora copiar;
        FuncionDestructora destruir;
} DList;

DList *dlist_crear(FuncionCopiadora copiar, FuncionDestructora destruir);

void dlist_agregar_inicio(DList *lista, void *dato);

void dlist_agregar_final(DList *lista, void *dato);

void dlist_eliminar_inicio(DList *lista);

void dlist_eliminar_final(DList *lista);

void dlist_destruir(DList *lista);

DList *dlist_copiar(DList *lista);

int dlist_igual(DList *l1, DList *l2, FuncionComparadora comparar);

void dlist_imprimir(DList *lista, FuncionVisitante visitar);

int dlist_largo_mayor_a_uno(DList *lista);

void dlist_transformar_int(DList *lista, DList *listaParametro);
#endif /* __DLIST_H__ */
