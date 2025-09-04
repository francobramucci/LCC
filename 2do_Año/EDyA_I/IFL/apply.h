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
 * Aplica una función de lista sobre la lista dada.
 * - La lista es modificada en el lugar.
 * - El parámetro `imprimir` indica si deben mostrarse resultados y/o errores.
 * Retorna un código definido en la enumeración anterior.
 */
int apply(FLista *funcion, DList *lista, THash *tablaFunciones, int imprimir);

/*
 * Aplica una función singular sobre una lista.
 * - Si `id` corresponde a una función primitiva, se ejecuta directamente.
 * - En caso contrario, se busca su definición en `tablaFunciones` y se llama a `apply_flista`.
 * - `cantMaxEjecuciones` se utiliza como contador/límite de aplicaciones.
 * Retorna un código definido en la enumeración anterior.
 */
int aplicacion_singular(char *id, DList *lista, THash *tablaFunciones, int *cantMaxEjecuciones);

#endif // !__APPLY_H__
