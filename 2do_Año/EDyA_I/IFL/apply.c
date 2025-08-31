#include "apply.h"
#include "dlist.h"
#include "utils.h"

int Od(DList *lista) {
    int i = 0;
    dlist_agregar_final(lista, &i);
    return NO_ERROR;
}

int Oi(DList *lista) {
    int i = 0;
    dlist_agregar_inicio(lista, &i);
    return NO_ERROR;
}

int Sd(DList *lista) {
    if (lista->primero != NULL) {
        (*(int *)(lista->ultimo->dato))++;
        return NO_ERROR;
    }
    return ERROR_DOMINIO;
}

int Si(DList *lista) {
    if (lista->primero != NULL) {
        (*(int *)lista->primero->dato)++;
        return NO_ERROR;
    }
    return ERROR_DOMINIO;
}

int Dd(DList *lista) {
    if (lista->primero != NULL) {
        dlist_eliminar_final(lista);
        return NO_ERROR;
    }
    return ERROR_DOMINIO;
}

int Di(DList *lista) {
    if (lista->primero != NULL) {
        dlist_eliminar_inicio(lista);
        return NO_ERROR;
    }
    return ERROR_DOMINIO;
}

int apply(FLista *funcion, DList *lista, THash *tablaHashFunciones) {
    int cantMaxEjecuciones = MAX_EJECUCIONES_APPLY;

    int errorCode = apply_flista(funcion, lista, tablaHashFunciones, &cantMaxEjecuciones);

    // if (errorCode == NO_ERROR) {
    //     dlist_imprimir(lista, (FuncionVisitante)imprimir_puntero_entero);
    // }

    return errorCode;
}

int apply_flista(FLista *funcion, DList *lista, THash *tablaHashFunciones, int *cantMaxEjecuciones) {
    int errorCode = NO_ERROR;
    Pila p = pila_crear((FuncionCopiadora)copiar_puntero_entero, (FuncionDestructora)destruir_puntero_entero);

    for (int i = 0; i <= funcion->ultimo && !errorCode; i++) {

        if (!(*cantMaxEjecuciones))
            errorCode = ERROR_CANT_EJECUCIONES;

        if (funcion->def[i][0] == '<') {
            if (dlist_largo_mayor_a_uno(lista)) {
                if (comparar_referencia_puntero_entero(lista->primero->dato, lista->ultimo->dato)) {
                    pila_push(&i, p);
                } else {
                    int cont = 1;
                    while (cont != 0) {
                        i++;
                        if (funcion->def[i][0] == '<')
                            cont++;
                        if (funcion->def[i][0] == '>')
                            cont--;
                    }
                }
            } else
                errorCode = ERROR_DOMINIO;
        } else if (funcion->def[i][0] == '>') {
            if (dlist_largo_mayor_a_uno(lista)) {
                if (comparar_referencia_puntero_entero(lista->primero->dato, lista->ultimo->dato))
                    i = *(int *)pila_top(p);
                else
                    pila_pop(p);
            } else
                errorCode = ERROR_DOMINIO;
        } else {
            errorCode = aplicacion_singular(funcion->def[i], lista, tablaHashFunciones, cantMaxEjecuciones);
            (*cantMaxEjecuciones)--;
        }
    }
    pila_destruir(p);

    return errorCode;
}

int aplicacion_singular(char *funcion, DList *lista, THash *tablaHashFunciones, int *cantMaxEjecuciones) {
    int error = NO_ERROR;
    if (!strcmp(funcion, "Oi"))
        return Oi(lista);
    if (!strcmp(funcion, "Od"))
        return Od(lista);
    if (!strcmp(funcion, "Si"))
        return Si(lista);
    if (!strcmp(funcion, "Sd"))
        return Sd(lista);
    if (!strcmp(funcion, "Di"))
        return Di(lista);
    if (!strcmp(funcion, "Dd"))
        return Dd(lista);

    return apply_flista(thash_buscar(funcion, tablaHashFunciones), lista, tablaHashFunciones, cantMaxEjecuciones);
}
