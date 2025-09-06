#include "search.h"
#include "dlist.h"
#include "flista.h"
#include "pila.h"
#include "thash.h"
#include "utils.h"
#include "vector.h"
#include <stdio.h>
#include <string.h>

#define PROFUNDIDAD_MAX 8
#define MAX_EJEC_APPLY_PARA_SEARCH 10000

/*
 * Busca recursivamente una secuencia de subfunciones que transforme listaInput en listaOutput.
 *
 * La búsqueda se realiza explorando todas las funciones definidas en tablaFunciones, aplicándolas a una copia
 * de listaInput y verificando si el resultado coincide con listaOutput.
 *
 * En cada llamada de la función se pasa listaInput modificada con la última aplicacion hecha, de esta forma no se
 * recomputa toda la función en cada llamada sino que se va almacenando el resultado.
 *
 * En caso de que aplicacion_singular o probar_funcion_con_resto_de_pares de una funcion arroje error hará que dicha
 * función no se considere, por lo que elimina la última subfuncion y continúa probando con el resto.
 *
 * Si se encuentra una función válida que transforma la listaInput original con listaOutput entonces se prueba con el
 * resto, si cumple con todos los pares de listas en paresDeListas, se retorna 1.
 *
 * Si no se encuentra ninguna, retorna 0.
 */
static int buscar_funcion(Pila *pilaFuncion, DList *listaInput, DList *listaOutput, Vector *elementosTabla,
                          THash *tablaFunciones, Vector *paresDeListas);

/*
 * Determina si conviene podar la búsqueda en función de la última subfunción aplicada.
 *
 * Retorna 1 si agregar una subfuncion inmediatamente después de la última función aplicada en funcion es redundante
 * o contradictorio (por ejemplo, "Oi" seguido de "Di"). En caso contrario retorna 0.
 */
static int podar(Pila *pilaFuncion, char *subfuncion);

/*
 * Verifica que la función encontrada sirva no solo con el par (listaInput, listaOutput) actual,
 * sino también con el resto de pares en listas.
 *
 * Para cada par de listas adicionales en listas, aplica funcion a la lista de entrada y compara con la salida esperada.
 *
 * Retorna SUCCESS si la función es válida para todos los pares.
 * Retorna FAIL si la aplicación no genera la lista resultado esperada para alguno de los pares.
 * Retorna un código de error (ERROR_DOMINIO, ERROR_CANT_EJECUCIONES) si alguna aplicación falla.
 */
static int probar_funcion_con_resto_de_pares(FLista *funcion, Vector *listas, THash *tablaFunciones);

void search(Vector *paresDeListas, THash *tablaFunciones) {
    Vector *elementosTabla = thash_elementos_a_vector(tablaFunciones);
    Pila *pilaFuncion = pila_crear(PROFUNDIDAD_MAX, retornar_puntero, funcion_vacia);

    int funcionEncontrada =
        buscar_funcion(pilaFuncion, (DList *)vector_acceder(paresDeListas, 0),
                       (DList *)vector_acceder(paresDeListas, 1), elementosTabla, tablaFunciones, paresDeListas);

    if (funcionEncontrada == 1) {
        for (int i = 0; i < pila_largo(pilaFuncion); i++) {
            printf("%s ", (char *)vector_acceder(pilaFuncion, i)); // FUNCION IMPRIMIR VECTOR
        }
    }

    else
        printf("No se ha encontrado la funcion.");

    pila_destruir(pilaFuncion);
    vector_destruir(elementosTabla);
}

static int buscar_funcion(Pila *pilaFuncion, DList *listaInput, DList *listaOutput, Vector *elementosTabla,
                          THash *tablaFunciones, Vector *paresDeListas) {

    if (pila_largo(pilaFuncion) >= PROFUNDIDAD_MAX)
        return 0;

    Entrada **funciones = (Entrada **)elementosTabla->arr;
    int cantFunciones = vector_largo(elementosTabla);
    DList *copiaInput = dlist_copiar(listaInput);

    int funcionEncontrada = 0;

    for (int i = 0; i < cantFunciones && !funcionEncontrada; i++) {
        if (funciones[i] && !podar(pilaFuncion, funciones[i]->key)) {
            char *subFuncion = funciones[i]->key;

            int cantMaxEjecuciones = MAX_EJEC_APPLY_PARA_SEARCH;
            int resultadoAplicacion = aplicacion_singular(subFuncion, copiaInput, tablaFunciones, &cantMaxEjecuciones);

            if (resultadoAplicacion != ERROR_DOMINIO && resultadoAplicacion != ERROR_CANT_EJECUCIONES) {
                pila_push(pilaFuncion, subFuncion);

                if (dlist_igual(copiaInput, listaOutput)) {
                    FLista *funcion = (FLista *)pilaFuncion;
                    int resultadoResto = probar_funcion_con_resto_de_pares(pilaFuncion, paresDeListas, tablaFunciones);

                    if (resultadoResto == SUCCESS) {
                        funcionEncontrada = 1;
                    }
                    if (resultadoResto == FAIL) {
                        funcionEncontrada = buscar_funcion(pilaFuncion, copiaInput, listaOutput, elementosTabla,
                                                           tablaFunciones, paresDeListas);
                    }
                } else
                    funcionEncontrada = buscar_funcion(pilaFuncion, copiaInput, listaOutput, elementosTabla,
                                                       tablaFunciones, paresDeListas);

                if (!funcionEncontrada)
                    pila_pop(pilaFuncion);
            }

            dlist_convertir(copiaInput, listaInput);
        }
    }

    dlist_destruir(copiaInput);

    return funcionEncontrada;
}

static int podar(Pila *pilaFuncion, char *subfuncion) {
    if (!flista_es_vacia(pilaFuncion)) {
        char *ultimaFuncion = pila_top(pilaFuncion);
        return (strcmp(ultimaFuncion, "Oi") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Od") == 0 && strcmp(subfuncion, "Dd") == 0) ||
               (strcmp(ultimaFuncion, "Si") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Sd") == 0 && strcmp(subfuncion, "Dd") == 0);
    }
    return 0;
}

static int probar_funcion_con_resto_de_pares(Pila *pilaFuncion, Vector *paresDeListas, THash *tablaFunciones) {
    int sonIguales = 1;
    int resultadoApply = SUCCESS;
    FLista *funcion = (FLista *)pilaFuncion;
    int largo = vector_largo(paresDeListas);

    if (vector_largo(paresDeListas) <= 2) {
        return SUCCESS;
    }

    // En las posiciones pares se guardan las listas de input y en las impares
    // las listas de output
    for (int i = 2; i < largo - 1 && sonIguales && resultadoApply == SUCCESS; i += 2) {
        DList *listaInput = dlist_copiar((DList *)vector_acceder(paresDeListas, i));
        DList *listaOutput = (DList *)vector_acceder(paresDeListas, i + 1);

        resultadoApply = apply(funcion, listaInput, tablaFunciones, 0);
        if (resultadoApply == SUCCESS)
            sonIguales = dlist_igual(listaInput, listaOutput);

        dlist_destruir(listaInput);
    }

    if (resultadoApply == SUCCESS && sonIguales)
        return SUCCESS;
    if (resultadoApply != SUCCESS)
        return resultadoApply;
    return FAIL;
}
