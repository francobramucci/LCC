#include "search.h"
#include "apply.h"
#include "cola.h"
#include "dlist.h"
#include "flista.h"
#include "utils.h"

// Implementar colas
// Funcion que agrega primitivas y funciones definidas

int probar_funcion_con_resto_de_pares(DList *listas, FLista *funcion, THash *tablaFunciones) {
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
        DList *input = dlist_copiar(nodoInput->dato);
        DList *output = nodoOutput->dato;

        apply(funcion, input, tablaFunciones);

        sonIguales = dlist_comparar(input, output, (FuncionComparadora)dlist_comparar);

        if (nodoOutput->sig == NULL)
            finDeLista = 1;
        else {
            nodoInput = nodoOutput->sig;
            nodoOutput = nodoOutput->sig->sig;
        }
    }

    return sonIguales;
}

void expandir_nivel(Cola q, FLista *funcion, THash tablaFunciones) {
}

void search_primera_lista(DList *listas, THash *tablaFunciones) {
    DList *listaInput = listas->primero->dato;
    DList *listaOutput = listas->primero->sig->dato;

    Cola q = cola_crear((FuncionCopiadora)retornar_puntero, (FuncionDestructora)flista_destruir);

    cola_encolar(q, thash_buscar("Oi", tablaFunciones));
    cola_encolar(q, thash_buscar("Od", tablaFunciones));
    cola_encolar(q, thash_buscar("Si", tablaFunciones));
    cola_encolar(q, thash_buscar("Sd", tablaFunciones));
    cola_encolar(q, thash_buscar("Di", tablaFunciones));
    cola_encolar(q, thash_buscar("Dd", tablaFunciones));

    int profundidad = 1;

    while (profundidad < 8) {
        int largo = 0;
        while (largo <= profundidad) {
            FLista *funcion = cola_desencolar(q);
            DList *copia = dlist_copiar(listaInput);
            apply(funcion, copia, tablaFunciones);
            int sonIguales =
                dlist_comparar(listaInput, listaOutput, (FuncionComparadora)comparar_referencia_puntero_entero);

            if (sonIguales)
                probar_funcion_con_resto_de_pares(listas, funcion, tablaFunciones);
            else {
                expandir(q, funcion, tablaFunciones);
            }
            FLista *proximaFuncion = cola_top(q);
            largo = proximaFuncion->ultimo + 1;
        }
        profundidad++;
    }
}
