#ifndef __APPLY_H__
#define __APPLY_H__
#include "dlist.h"
#include "flista.h"
#include "hash.h"
#include "pila.h"

#define MAX_EJECUCIONES_APPLY 100000

enum {
    SUCCESS = 0,

    ERROR_DOMINIO,

    ERROR_CANT_EJECUCIONES,

    ERROR_APPLY,

    FAIL
};

int Od(DList *lista);

int Oi(DList *lista);

int Sd(DList *lista);

int Si(DList *lista);

int Dd(DList *lista);

int Di(DList *lista);

int apply(FLista *funcion, DList *lista, THash *tablaHashFunciones, int imprimir);

int apply_flista(FLista *funcion, DList *lista, THash *tablaHashFunciones, int *cantMaxEjecuciones);

int aplicacion_singular(char *funcion, DList *lista, THash *tablaHashFunciones, int *cantMaxEjecuciones);

#endif // !__APPLY_H__
