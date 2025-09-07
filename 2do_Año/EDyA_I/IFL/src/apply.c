#include "apply.h"
#include "dlist.h"
#include "flista.h"
#include "lista.h"
#include "pila.h"
#include "thash.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

/**
 * Aplica una función de lista sobre la lista provista.
 * La lista es modificada en el lugar.
 * Retorna:
 *   - SUCCESS si la aplicación fue exitosa
 *   - ERROR_DOMINIO si la lista no pertenece al dominio de la función
 *   - ERROR_CANT_EJECUCIONES si se supera MAX_EJECUCIONES_APPLY
 */
static int apply_flista(FLista *funcion, Lista *lista, THash *tablaFunciones, int *cantMaxEjecuciones);

/**
 * Dada una función de lista y la posición inicial de una repetición,
 * devuelve la posición del final correspondiente de dicha repetición.
 */
static int avanzar_hasta_repeticion_fin(FLista *funcion, int i);

/**
 * Funciones primitivas de listas:
 *   Oi -> agrega un 0 a la izquierda
 *   Od -> agrega un 0 a la derecha
 *   Si -> incrementa en 1 el elemento izquierdo
 *   Sd -> incrementa en 1 el elemento derecho
 *   Di -> elimina el elemento izquierdo
 *   Dd -> elimina el elemento derecho
 */
static int Oi(Lista *lista);
static int Od(Lista *lista);
static int Si(Lista *lista);
static int Sd(Lista *lista);
static int Di(Lista *lista);
static int Dd(Lista *lista);

int apply(FLista *funcion, Lista *lista, THash *tablaFunciones, int imprimir) {
    int cantMaxEjecuciones = MAX_EJECUCIONES_APPLY;

    int errorCode = apply_flista(funcion, lista, tablaFunciones, &cantMaxEjecuciones);

    if (errorCode == SUCCESS) {
        if (imprimir)
            lista_imprimir(lista);
        return SUCCESS;
    }

    if (errorCode == ERROR_DOMINIO && imprimir)
        printf("Error: La lista no pertenece al dominio de la funcion.");

    if (errorCode == ERROR_CANT_EJECUCIONES && imprimir)
        printf("Error: Se ha superado la cantidad maxima de ejecuciones.");

    return errorCode;
}

static int apply_flista(FLista *funcion, Lista *lista, THash *tablaFunciones, int *cantMaxEjecuciones) {
    int errorCode = SUCCESS;
    Pila *p = pila_crear((FuncionCopiadora)copiar_entero, (FuncionDestructora)destruir_entero);
    int largoFuncion = flista_largo(funcion);

    for (int i = 0; i < largoFuncion && errorCode == SUCCESS; i++) {

        if (!(*cantMaxEjecuciones))
            errorCode = ERROR_CANT_EJECUCIONES;

        if (flista_acceder(funcion, i)[0] == '<') {
            if (lista_largo_mayor_a_uno(lista)) {
                if (lista_comparar_extremos(lista))
                    pila_push(p, &i);
                else
                    i = avanzar_hasta_repeticion_fin(funcion, i);
            } else
                errorCode = ERROR_DOMINIO;
        }

        else if (flista_acceder(funcion, i)[0] == '>') {
            if (lista_largo_mayor_a_uno(lista)) {
                if (lista_comparar_extremos(lista))
                    i = *(int *)pila_top(p);
                else
                    pila_pop(p);
            } else
                errorCode = ERROR_DOMINIO;
        }

        else {
            errorCode = aplicacion_singular(flista_acceder(funcion, i), lista, tablaFunciones, cantMaxEjecuciones);
            (*cantMaxEjecuciones)--;
        }
    }

    pila_destruir(p);

    return errorCode;
}

static int avanzar_hasta_repeticion_fin(FLista *funcion, int i) {
    int cont = 1;
    while (cont != 0) {
        i++;
        if (flista_acceder(funcion, i)[0] == '<')
            cont++;
        if (flista_acceder(funcion, i)[0] == '>')
            cont--;
    }

    return i;
}

int aplicacion_singular(char *id, Lista *lista, THash *tablaFunciones, int *cantMaxEjecuciones) {
    if (!strcmp(id, "Oi"))
        return Oi(lista);
    if (!strcmp(id, "Od"))
        return Od(lista);
    if (!strcmp(id, "Si"))
        return Si(lista);
    if (!strcmp(id, "Sd"))
        return Sd(lista);
    if (!strcmp(id, "Di"))
        return Di(lista);
    if (!strcmp(id, "Dd"))
        return Dd(lista);

    return apply_flista(thash_buscar(id, tablaFunciones), lista, tablaFunciones, cantMaxEjecuciones);
}

static int Oi(Lista *lista) {
    lista_agregar_inicio(lista, 0);
    return SUCCESS;
}

static int Od(Lista *lista) {
    lista_agregar_final(lista, 0);
    return SUCCESS;
}

static int Si(Lista *lista) {
    if (!lista_es_vacia(lista)) {
        lista_incrementar_izq(lista);
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}

static int Sd(Lista *lista) {
    if (!lista_es_vacia(lista)) {
        lista_incrementar_der(lista);
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}

static int Di(Lista *lista) {
    if (!lista_es_vacia(lista)) {
        lista_eliminar_izq(lista);
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}

static int Dd(Lista *lista) {
    if (!lista_es_vacia(lista)) {
        lista_eliminar_der(lista);
        return SUCCESS;
    }
    return ERROR_DOMINIO;
}
