#include "search.h"
#include "apply.h"
#include "dlist.h"
#include "utils.h"
#include "vector.h"
#include <stdio.h>

#define PROFUNDIDAD_MAX 8

// Agregar bandera para imprimir de apply
// Implementar colas
// Funcion que agrega primitivas y funciones definidas

// int probar_funcion_con_resto_de_pares(FLista *funcion, DList *listas, THash *tablaFunciones) {
//     DNodo *nodoInput = NULL;
//     DNodo *nodoOutput = NULL;
//     int sonIguales = 1;
//     int finDeLista = 0;
//     if (!listas->primero->sig->sig)
//         return 1;
//
//     // Asignamos como input el primer elemento del segundo par de listas
//     // y el segundo del segundo par como el output
//     nodoInput = listas->primero->sig->sig;
//     nodoOutput = nodoInput->sig;
//
//     while (!finDeLista && sonIguales) {
//         DList *listaInput = dlist_copiar(nodoInput->dato);
//         DList *listaOutput = nodoOutput->dato;
//
//         int resultadoApply = apply(funcion, listaInput, tablaFunciones, 0);
//         if (resultadoApply == SUCCESS)
//             sonIguales = dlist_igual(listaInput, listaOutput,
//             (FuncionComparadora)comparar_referencia_puntero_entero);
//         else
//             sonIguales = 0;
//
//         if (nodoOutput->sig == NULL)
//             finDeLista = 1;
//         else {
//             nodoInput = nodoOutput->sig;
//             nodoOutput = nodoOutput->sig->sig;
//         }
//         dlist_destruir(listaInput);
//     }
//
//     return sonIguales;
// }
//
int probar_funcion_con_resto_de_pares(FLista *funcion, Vector *listas, THash *tablaFunciones) {
    int sonIguales = 1;
    int resultadoApply = SUCCESS;

    if (listas->ultimo < 2) {
        return SUCCESS;
    }

    for (int i = 2; i < listas->ultimo && sonIguales && resultadoApply == SUCCESS; i += 2) {
        DList *listaInput = dlist_copiar(listas->arr[i]);
        DList *listaOutput = listas->arr[i + 1];

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
//
// void search(DList *listaDePares, THash *tablaFunciones) {
//     FLista *funcion = flista_crear(PROFUNDIDAD_MAX, retornar_puntero, funcion_vacia);
//
//     int funcionEncontrada = buscar_funcion(funcion, listaDePares->primero->dato, listaDePares->primero->sig->dato,
//                                            tablaFunciones, listaDePares);
//
//     if (funcionEncontrada == SUCCESS) {
//         for (int i = 0; i <= funcion->ultimo; i++) {
//             printf("%s ", flista_acceder(funcion, i));
//         }
//     }
//
//     flista_destruir(funcion);
// }

void search(Vector *paresDeListas, THash *tablaFunciones) {
    FLista *funcion = flista_crear(PROFUNDIDAD_MAX, retornar_puntero, funcion_vacia);

    int funcionEncontrada = buscar_funcion(funcion, (DList *)paresDeListas->arr[0], (DList *)paresDeListas->arr[1],
                                           tablaFunciones, paresDeListas);
    if (funcionEncontrada == 1) {
        for (int i = 0; i <= funcion->ultimo; i++) {
            printf("%s ", flista_acceder(funcion, i));
        }
    }

    flista_destruir(funcion);
}

int podar(FLista *funcion, char *subfuncion) {
    if (!flista_es_vacia(funcion)) {
        char *ultimaFuncion = flista_acceder(funcion, funcion->ultimo);
        return (strcmp(ultimaFuncion, "Oi") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Od") == 0 && strcmp(subfuncion, "Dd") == 0) ||
               (strcmp(ultimaFuncion, "Si") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Sd") == 0 && strcmp(subfuncion, "Dd") == 0);
    }
    return 0;
}

// int buscar_funcion(FLista *funcion, DList *listaInput, DList *listaOutput, THash *tablaFunciones, DList
// *listaDePares) {
//     if (funcion->ultimo + 1 >= PROFUNDIDAD_MAX)
//         return FAIL;
//
//     DList *copiaInput = dlist_copiar(listaInput);
//
//     int resultado = FAIL;
//     for (int i = 0; i < tablaFunciones->capacidad && resultado != SUCCESS; i++) {
//         if (tablaFunciones->tabla[i] && !podar(funcion, tablaFunciones->tabla[i]->key)) {
//             char *subFuncion = tablaFunciones->tabla[i]->key; // DList *copia = dlist_copiar(listaInput);
//             int cantMaxEjecuciones = MAX_EJECUCIONES_APPLY;
//             resultado = aplicacion_singular(subFuncion, copiaInput, tablaFunciones, &cantMaxEjecuciones);
//
//             if (resultado != ERROR_DOMINIO && resultado != ERROR_CANT_EJECUCIONES) {
//                 flista_insertar(funcion, subFuncion);
//                 if (dlist_igual(copiaInput, listaOutput, (FuncionComparadora)comparar_referencia_puntero_entero) &&
//                     probar_funcion_con_resto_de_pares(funcion, listaDePares, tablaFunciones)) {
//                     resultado = SUCCESS;
//                 } else {
//                     resultado = buscar_funcion(funcion, copiaInput, listaOutput, tablaFunciones, listaDePares);
//                     if (resultado != SUCCESS)
//                         funcion->ultimo--;
//                 }
//             }
//             dlist_transformar_int(copiaInput, listaInput);
//         }
//     }
//
//     dlist_destruir(copiaInput);
//
//     return resultado;
// }

int buscar_funcion(FLista *funcion, DList *listaInput, DList *listaOutput, THash *tablaFunciones,
                   Vector *paresDeListas) {

    if (funcion->ultimo + 1 >= PROFUNDIDAD_MAX)
        return 0;

    DList *copiaInput = dlist_copiar(listaInput);

    int funcionEncontrada = 0;

    for (int i = 0; i < tablaFunciones->capacidad && !funcionEncontrada; i++) {
        if (tablaFunciones->tabla[i] && !podar(funcion, tablaFunciones->tabla[i]->key)) {
            char *subFuncion = tablaFunciones->tabla[i]->key;

            int cantMaxEjecuciones = MAX_EJECUCIONES_APPLY;
            int resultadoAplicacion = aplicacion_singular(subFuncion, copiaInput, tablaFunciones, &cantMaxEjecuciones);

            if (resultadoAplicacion != ERROR_DOMINIO && resultadoAplicacion != ERROR_CANT_EJECUCIONES) {
                flista_insertar(funcion, subFuncion);

                // for (int j = 0; j <= funcion->ultimo; j++) {
                //     fprintf(stderr, "%s ", flista_acceder(funcion, j));
                // }
                // fprintf(stderr, "\n");

                if (dlist_igual(copiaInput, listaOutput)) {
                    int resultadoResto = probar_funcion_con_resto_de_pares(funcion, paresDeListas, tablaFunciones);
                    // fprintf(stderr, "%d", resultadoResto);
                    if (resultadoResto == SUCCESS) {
                        funcionEncontrada = 1;
                    }
                    if (resultadoResto == FAIL) {
                        funcionEncontrada =
                            buscar_funcion(funcion, copiaInput, listaOutput, tablaFunciones, paresDeListas);
                    }
                } else
                    funcionEncontrada = buscar_funcion(funcion, copiaInput, listaOutput, tablaFunciones, paresDeListas);

                if (!funcionEncontrada)
                    vector_eliminar_ultimo(funcion);
            }

            dlist_transformar_int(copiaInput, listaInput);
        }
    }

    dlist_destruir(copiaInput);

    return funcionEncontrada;
}
