#include "search.h"

#define PROFUNDIDAD_MAX 8
#define MAX_EJEC_APPLY_PARA_SEARCH 100000

static int buscar_funcion(FLista *funcion, DList *listaInput, DList *listaOutput, THash *tablaFunciones,
                          Vector *paresDeListas);
static int podar(FLista *funcion, char *subfuncion);
static int probar_funcion_con_resto_de_pares(FLista *funcion, Vector *listas, THash *tablaFunciones);

void search(Vector *paresDeListas, THash *tablaFunciones) {
    FLista *funcion = flista_crear(PROFUNDIDAD_MAX, retornar_puntero, funcion_vacia);

    int funcionEncontrada = buscar_funcion(funcion, (DList *)paresDeListas->arr[0], (DList *)paresDeListas->arr[1],
                                           tablaFunciones, paresDeListas);
    if (funcionEncontrada == 1) {
        for (int i = 0; i <= funcion->ultimo; i++) {
            printf("%s ", flista_acceder(funcion, i));
        }
    } else {
        printf("No se ha encontrado la funcion");
    }

    flista_destruir(funcion);
}

static int buscar_funcion(FLista *funcion, DList *listaInput, DList *listaOutput, THash *tablaFunciones,
                          Vector *paresDeListas) {

    if (funcion->ultimo + 1 >= PROFUNDIDAD_MAX)
        return 0;

    DList *copiaInput = dlist_copiar(listaInput);

    int funcionEncontrada = 0;

    for (int i = 0; i < tablaFunciones->capacidad && !funcionEncontrada; i++) {
        if (tablaFunciones->tabla[i] && !podar(funcion, tablaFunciones->tabla[i]->key)) {
            char *subFuncion = tablaFunciones->tabla[i]->key;

            int cantMaxEjecuciones = MAX_EJEC_APPLY_PARA_SEARCH;
            int resultadoAplicacion = aplicacion_singular(subFuncion, copiaInput, tablaFunciones, &cantMaxEjecuciones);

            if (resultadoAplicacion != ERROR_DOMINIO && resultadoAplicacion != ERROR_CANT_EJECUCIONES) {
                flista_insertar(funcion, subFuncion);

                if (dlist_igual(copiaInput, listaOutput)) {
                    int resultadoResto = probar_funcion_con_resto_de_pares(funcion, paresDeListas, tablaFunciones);

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

static int podar(FLista *funcion, char *subfuncion) {
    if (!flista_es_vacia(funcion)) {
        char *ultimaFuncion = flista_acceder(funcion, funcion->ultimo);
        return (strcmp(ultimaFuncion, "Oi") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Od") == 0 && strcmp(subfuncion, "Dd") == 0) ||
               (strcmp(ultimaFuncion, "Si") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimaFuncion, "Sd") == 0 && strcmp(subfuncion, "Dd") == 0);
    }
    return 0;
}

static int probar_funcion_con_resto_de_pares(FLista *funcion, Vector *listas, THash *tablaFunciones) {
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
