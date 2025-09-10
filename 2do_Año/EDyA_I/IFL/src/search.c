#include "search.h"
#include "flista.h"
#include "lista.h"
#include "thash.h"
#include "utils.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROFUNDIDAD_MAX 11
#define MAX_EJEC_APPLY_PARA_SEARCH 10000

/**
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
static int buscar_funcion(FLista *funcion, Lista *listaInput, Lista *listaOutput, Vector *elementosTabla,
                          THash *tablaFunciones, Vector *paresDeListas, THash *tablaEstadoslista);

/**
 * Determina si conviene podar la búsqueda en función de la última subfunción aplicada.
 *
 * Retorna 1 si agregar una subfuncion inmediatamente después de la última función aplicada en funcion es redundante
 * o contradictorio (por ejemplo, "Oi" seguido de "Di"). En caso contrario retorna 0.
 */
static int podar(FLista *funcion, char *subfuncion);

/**
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

typedef struct {
        Lista *lista;
        int profundidad;
} estadoLista;

estadoLista *estadoLista_crear(Lista *lista, int profundidad) {
    estadoLista *nuevoEstado = malloc(sizeof(estadoLista));
    nuevoEstado->lista = lista;
    nuevoEstado->profundidad = profundidad;

    return nuevoEstado;
}

int lista_comparar(Lista *l1, Lista *l2) {
    return !lista_igual(l1, l2);
}

void search(Vector *paresDeListas, THash *tablaFunciones) {
    THash *tablaEstadosLista =
        thash_crear(300000, (FuncionHash)lista_hash, retornar_puntero, retornar_puntero,
                    (FuncionDestructora)lista_destruir, liberar_puntero, (FuncionComparadora)lista_comparar);
    Vector *elementosTabla = thash_elementos_a_vector(tablaFunciones);
    FLista *funcion = flista_crear(PROFUNDIDAD_MAX, retornar_puntero, funcion_vacia);

    int funcionEncontrada =
        buscar_funcion(funcion, (Lista *)vector_acceder(paresDeListas, 0), (Lista *)vector_acceder(paresDeListas, 1),
                       elementosTabla, tablaFunciones, paresDeListas, tablaEstadosLista);

    if (funcionEncontrada == 1) {
        flista_imprimir(funcion);
    }

    else
        printf("No se ha encontrado la funcion.");

    flista_destruir(funcion);
    vector_destruir(elementosTabla);
    thash_destruir(tablaEstadosLista);
}

static int buscar_funcion(FLista *funcion, Lista *listaInput, Lista *listaOutput, Vector *elementosTabla,
                          THash *tablaFunciones, Vector *paresDeListas, THash *tablaEstadosLista) {

    int largoFuncion = flista_largo(funcion);

    if (largoFuncion >= PROFUNDIDAD_MAX)
        return 0;

    Entrada **funciones = (Entrada **)elementosTabla->arr;
    int cantFunciones = vector_largo(elementosTabla);

    int funcionEncontrada = 0;

    for (int i = 0; i < cantFunciones && !funcionEncontrada; i++) {
        if (!podar(funcion, funciones[i]->key)) {
            char *subFuncion = funciones[i]->key;

            Lista *copiaInput = lista_copiar(listaInput);

            int cantMaxEjecuciones = MAX_EJEC_APPLY_PARA_SEARCH;
            int resultadoAplicacion = aplicacion_singular(subFuncion, copiaInput, tablaFunciones, &cantMaxEjecuciones);

            if (resultadoAplicacion != ERROR_DOMINIO && resultadoAplicacion != ERROR_CANT_EJECUCIONES) {
                flista_insertar(funcion, subFuncion);

                largoFuncion++;

                estadoLista *estadoExistente = (estadoLista *)thash_buscar(copiaInput, tablaEstadosLista);

                // Si el estado no existe o existe pero fue generado por una función de mayor profundidad
                // seguimos por la rama.
                if (!estadoExistente || (estadoExistente && estadoExistente->profundidad > largoFuncion)) {

                    if (lista_igual(copiaInput, listaOutput)) {
                        int resultadoResto = probar_funcion_con_resto_de_pares(funcion, paresDeListas, tablaFunciones);

                        if (resultadoResto == SUCCESS) {
                            funcionEncontrada = 1;
                        }
                        if (resultadoResto == FAIL) {
                            funcionEncontrada = buscar_funcion(funcion, copiaInput, listaOutput, elementosTabla,
                                                               tablaFunciones, paresDeListas, tablaEstadosLista);
                        }
                    } else {
                        if (estadoExistente && estadoExistente->profundidad > largoFuncion) {
                            estadoExistente->profundidad = largoFuncion;
                        } else {
                            Lista *copiaListaApply = lista_copiar(copiaInput);
                            estadoLista *estado = estadoLista_crear(copiaListaApply, largoFuncion);
                            thash_insertar(copiaListaApply, estado, tablaEstadosLista);
                        }
                        funcionEncontrada = buscar_funcion(funcion, copiaInput, listaOutput, elementosTabla,
                                                           tablaFunciones, paresDeListas, tablaEstadosLista);
                    }

                    if (!funcionEncontrada) {
                        flista_eliminar_ultimo(funcion);
                        largoFuncion--;
                    }
                } else {
                    flista_eliminar_ultimo(funcion);
                    largoFuncion--;
                }
            }

            lista_destruir(copiaInput);
        }
    }

    return funcionEncontrada;
}

static int podar(FLista *funcion, char *subfuncion) {
    if (!flista_es_vacia(funcion)) {
        char *ultimaFuncion = flista_ultimo_elemento(funcion);
        return (strcmp(ultimaFuncion, "Oi") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Od") == 0 && strcmp(subfuncion, "Dd") == 0) ||
               (strcmp(ultimaFuncion, "Si") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Sd") == 0 && strcmp(subfuncion, "Dd") == 0);
    }
    return 0;
}

static int probar_funcion_con_resto_de_pares(FLista *funcion, Vector *paresDeListas, THash *tablaFunciones) {
    int sonIguales = 1;
    int resultadoApply = SUCCESS;
    int largo = vector_largo(paresDeListas);

    if (vector_largo(paresDeListas) <= 2) {
        return SUCCESS;
    }

    // En las posiciones pares se guardan las listas de input y en las impares
    // las listas de output
    for (int i = 2; i < largo - 1 && sonIguales && resultadoApply == SUCCESS; i += 2) {
        Lista *listaInput = lista_copiar((Lista *)vector_acceder(paresDeListas, i));
        Lista *listaOutput = (Lista *)vector_acceder(paresDeListas, i + 1);

        resultadoApply = apply(funcion, listaInput, tablaFunciones, 0);
        if (resultadoApply == SUCCESS)
            sonIguales = lista_igual(listaInput, listaOutput);

        lista_destruir(listaInput);
    }

    if (resultadoApply == SUCCESS && sonIguales)
        return SUCCESS;
    if (resultadoApply != SUCCESS)
        return resultadoApply;
    return FAIL;
}
