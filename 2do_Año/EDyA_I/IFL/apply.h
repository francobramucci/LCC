#ifndef __APPLY_H__
#define __APPLY_H__
#include "dlist.h"
#include "flista.h"
#include "thash.h"

#define MAX_EJECUCIONES_APPLY 1e8

enum {
    SUCCESS = 0,

    ERROR_DOMINIO,

    ERROR_CANT_EJECUCIONES,

    FAIL
};

/*
 * Dada una funcion de lista y una lista se aplica la funcion a la lista.
 * La aplicacion modifica la lista provista.
 * Se toma un parametro imprimir para indicar si la funcion imprime resultados o errores.
 */
int apply(FLista *funcion, DList *lista, THash *tablaFunciones, int imprimir);

/*
 * Dado un identificador de una funcion de lista y una lista, comprueba si el identificador es de una funcion primitiva.
 * En caso de que lo sea, aplica la respectiva funcion. En caso contrario obtiene su definicion en la tabla de funciones
 * y llama a apply_flista con dicha definicion.
 */
int aplicacion_singular(char *id, DList *lista, THash *tablaFunciones, int *cantMaxEjecuciones);

#endif // !__APPLY_H__
