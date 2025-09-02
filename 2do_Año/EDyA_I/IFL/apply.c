#include "apply.h"

int Od(DList *lista) {
    dlist_agregar_final(lista, 0);
    return SUCCESS;
}

int Oi(DList *lista) {
    dlist_agregar_inicio(lista, 0);
    return SUCCESS;
}

int Sd(DList *lista) {
    if (lista->primero != NULL) {
        lista->ultimo->dato++;
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}

int Si(DList *lista) {
    if (lista->primero != NULL) {
        lista->primero->dato++;
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}

int Dd(DList *lista) {
    if (lista->primero != NULL) {
        dlist_eliminar_final(lista);
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}

int Di(DList *lista) {
    if (lista->primero != NULL) {
        dlist_eliminar_inicio(lista);
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}

int apply(FLista *funcion, DList *lista, THash *tablaHashFunciones, int imprimir) {
    int cantMaxEjecuciones = MAX_EJECUCIONES_APPLY;

    int errorCode = apply_flista(funcion, lista, tablaHashFunciones, &cantMaxEjecuciones);

    if (errorCode == SUCCESS) {
        if (imprimir)
            dlist_imprimir(lista);
        return SUCCESS;
    }

    if (errorCode == ERROR_DOMINIO && imprimir)
        printf("La lista no pertenece al dominio de la funcion");

    if (errorCode == ERROR_CANT_EJECUCIONES && imprimir)
        printf("Se ha superado la cantidad maxima de ejecuciones");

    return errorCode;
}

int apply_flista(FLista *funcion, DList *lista, THash *tablaHashFunciones, int *cantMaxEjecuciones) {
    int errorCode = SUCCESS;
    Pila p = pila_crear();

    for (int i = 0; i <= funcion->ultimo && !errorCode; i++) {

        if (!(*cantMaxEjecuciones))
            errorCode = ERROR_CANT_EJECUCIONES;

        if (flista_acceder(funcion, i)[0] == '<') {
            if (dlist_largo_mayor_a_uno(lista)) {
                if (lista->primero->dato != lista->ultimo->dato) {
                    pila_push(p, i);
                } else {
                    int cont = 1;
                    while (cont != 0) {
                        i++;
                        if (flista_acceder(funcion, i)[0] == '<')
                            cont++;
                        if (flista_acceder(funcion, i)[0] == '>')
                            cont--;
                    }
                }
            } else
                errorCode = ERROR_DOMINIO;
        } else if (flista_acceder(funcion, i)[0] == '>') {
            if (dlist_largo_mayor_a_uno(lista)) {
                if (lista->primero->dato != lista->ultimo->dato)
                    i = pila_top(p);
                else
                    pila_pop(p);
            } else
                errorCode = ERROR_DOMINIO;
        } else {
            errorCode = aplicacion_singular(flista_acceder(funcion, i), lista, tablaHashFunciones, cantMaxEjecuciones);
            (*cantMaxEjecuciones)--;
        }
    }
    pila_destruir(p);

    return errorCode;
}

int aplicacion_singular(char *funcion, DList *lista, THash *tablaHashFunciones, int *cantMaxEjecuciones) {
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
