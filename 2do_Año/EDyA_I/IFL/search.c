#include "search.h"
#include "dlist.h"
#include "utils.h"

#define PROFUNDIDAD_MAX 8

// Agregar bandera para imprimir de apply
// Implementar colas
// Funcion que agrega primitivas y funciones definidas

int probar_funcion_con_resto_de_pares(FLista *funcion, DList *listas, THash *tablaFunciones) {
    DNodo *nodoInput = NULL;
    DNodo *nodoOutput = NULL;
    int sonIguales = 1;
    int finDeLista = 0;
    if (!listas->primero->sig->sig)
        return 1;

    // Asignamos como input el primer elemento del segundo par de listas
    // y el segundo del segundo par como el output
    nodoInput = listas->primero->sig->sig;
    nodoOutput = nodoInput->sig;

    while (!finDeLista && sonIguales) {
        DList *listaInput = dlist_copiar(nodoInput->dato);
        DList *listaOutput = nodoOutput->dato;

        int resultadoApply = apply(funcion, listaInput, tablaFunciones, 0);
        if (resultadoApply == SUCCESS)
            sonIguales = dlist_igual(listaInput, listaOutput, (FuncionComparadora)comparar_referencia_puntero_entero);
        else
            sonIguales = 0;

        if (nodoOutput->sig == NULL)
            finDeLista = 1;
        else {
            nodoInput = nodoOutput->sig;
            nodoOutput = nodoOutput->sig->sig;
        }
        dlist_destruir(listaInput);
    }

    return sonIguales;
}

void search(DList *listaDePares, THash *tablaFunciones) {
    FLista *funcion = flista_crear(PROFUNDIDAD_MAX, retornar_puntero, funcion_vacia);

    int funcionEncontrada = buscar_funcion(funcion, listaDePares->primero->dato, listaDePares->primero->sig->dato,
                                           tablaFunciones, listaDePares);

    if (funcionEncontrada == SUCCESS) {
        for (int i = 0; i <= funcion->ultimo; i++) {
            printf("%s ", flista_acceder(funcion, i));
        }
    }

    flista_destruir(funcion);
}

int podar(FLista *funcion, char *subfuncion) {
    if (!flista_es_vacia(funcion)) {
        char *ultimo_str = flista_acceder(funcion, funcion->ultimo);
        return (strcmp(ultimo_str, "Oi") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimo_str, "Od") == 0 && strcmp(subfuncion, "Dd") == 0) ||
               (strcmp(ultimo_str, "Si") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimo_str, "Sd") == 0 && strcmp(subfuncion, "Dd") == 0);
    }
    return 0;
}

int buscar_funcion(FLista *funcion, DList *listaInput, DList *listaOutput, THash *tablaFunciones, DList *listaDePares) {
    if (funcion->ultimo + 1 >= PROFUNDIDAD_MAX)
        return FAIL;

    DList *copiaInput = dlist_copiar(listaInput);

    int resultado = FAIL;
    for (int i = 0; i < tablaFunciones->capacidad && resultado != SUCCESS; i++) {
        if (tablaFunciones->tabla[i] && !podar(funcion, tablaFunciones->tabla[i]->key)) {
            char *subFuncion = tablaFunciones->tabla[i]->key;
            // DList *copia = dlist_copiar(listaInput);

            int cantMaxEjecuciones = MAX_EJECUCIONES_APPLY;
            resultado = aplicacion_singular(subFuncion, copiaInput, tablaFunciones, &cantMaxEjecuciones);

            if (resultado != ERROR_DOMINIO && resultado != ERROR_CANT_EJECUCIONES) {
                flista_insertar(funcion, subFuncion);
                if (dlist_igual(copiaInput, listaOutput, (FuncionComparadora)comparar_referencia_puntero_entero) &&
                    probar_funcion_con_resto_de_pares(funcion, listaDePares, tablaFunciones)) {
                    resultado = SUCCESS;
                } else {
                    resultado = buscar_funcion(funcion, copiaInput, listaOutput, tablaFunciones, listaDePares);
                    if (resultado != SUCCESS)
                        funcion->ultimo--;
                }
            }
            dlist_transformar_int(copiaInput, listaInput);
        }
    }

    dlist_destruir(copiaInput);

    return resultado;
}
