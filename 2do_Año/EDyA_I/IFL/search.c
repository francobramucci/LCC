#include "search.h"
#include "apply.h"
#include "dlist.h"
#include "flista.h"
#include "utils.h"
#include <stdio.h>

#define PROFUNDIDAD_MAX 8

// Agregar bandera para imprimir de apply
// Implementar colas
// Funcion que agrega primitivas y funciones definidas

// int probar_funcion_con_resto_de_pares(DList *listas, FLista *funcion, THash *tablaFunciones) {
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
//         DList *input = dlist_copiar(nodoInput->dato);
//         DList *output = nodoOutput->dato;
//
//         apply(funcion, input, tablaFunciones);
//
//         sonIguales = dlist_comparar(input, output, (FuncionComparadora)dlist_comparar);
//
//         if (nodoOutput->sig == NULL)
//             finDeLista = 1;
//         else {
//             nodoInput = nodoOutput->sig;
//             nodoOutput = nodoOutput->sig->sig;
//         }
//     }
//
//     return sonIguales;
// }
//
// void expandir_nivel(Cola q, FLista *funcion, THash tablaFunciones) {
// }
//
// void search_primera_lista(DList *listas, THash *tablaFunciones) {
//     DList *listaInput = listas->primero->dato;
//     DList *listaOutput = listas->primero->sig->dato;
//
//     Cola q = cola_crear((FuncionCopiadora)retornar_puntero, (FuncionDestructora)flista_destruir);
//
//     cola_encolar(q, thash_buscar("Oi", tablaFunciones));
//     cola_encolar(q, thash_buscar("Od", tablaFunciones));
//     cola_encolar(q, thash_buscar("Si", tablaFunciones));
//     cola_encolar(q, thash_buscar("Sd", tablaFunciones));
//     cola_encolar(q, thash_buscar("Di", tablaFunciones));
//     cola_encolar(q, thash_buscar("Dd", tablaFunciones));
//
//     int profundidad = 1;
//
//     while (profundidad < 8) {
//         int largo = 0;
//         while (largo <= profundidad) {
//             FLista *funcion = cola_desencolar(q);
//             DList *copia = dlist_copiar(listaInput);
//             apply(funcion, copia, tablaFunciones);
//             int sonIguales =
//                 dlist_comparar(listaInput, listaOutput, (FuncionComparadora)comparar_referencia_puntero_entero);
//
//             if (sonIguales)
//                 probar_funcion_con_resto_de_pares(listas, funcion, tablaFunciones);
//             else {
//                 expandir(q, funcion, tablaFunciones);
//             }
//             FLista *proximaFuncion = cola_top(q);
//             largo = proximaFuncion->ultimo + 1;
//         }
//         profundidad++;
//     }
// }

int probar_funcion(FLista *funcion, DNodo *listas, THash *tablaFunciones) {
    if (!listas)
        return SUCCESS;

    DNodo *nodoInput = listas;
    DNodo *nodoOutput = nodoInput->sig;

    DList *listaInput = dlist_copiar(nodoInput->dato);
    DList *listaOutput = nodoOutput->dato;

    if (apply(funcion, listaInput, tablaFunciones, 1) == ERROR_APPLY)
        return ERROR_APPLY;

    if (dlist_igual(listaInput, listaOutput, (FuncionComparadora)comparar_referencia_puntero_entero)) {
        dlist_destruir(listaInput);
        return probar_funcion(funcion, nodoOutput->sig, tablaFunciones);
    }

    dlist_destruir(listaInput);
    return FAIL;
}

// FLista *generate(int length, int pos, int indices[], THash *tablaFunciones, DList *listas) {
//     if (pos == length) {
//         FLista *funcion = flista_crear(8);
//         for (int i = 0; i < length; i++)
//             flista_insertar(funcion, tablaFunciones->tabla[indices[i]]->key);
//         if (probar_funcion(funcion, listas->primero, tablaFunciones))
//             return funcion;
//         // flista_destruir(funcion);
//         return NULL;
//     }
//     FLista *funcion = NULL;
//     for (int i = 0; i < tablaFunciones->capacidad && !funcion; i++) {
//         if (tablaFunciones->tabla[i] != NULL) {
//             indices[pos] = i;
//             funcion = generate(length, pos + 1, indices, tablaFunciones, listas);
//         }
//     }
//
//     return funcion;
// }
//
void search(DList *listas, THash *tablaFunciones) {
    FLista *funcion = flista_crear(PROFUNDIDAD_MAX);
    int funcionEncontrada = buscar_funcion(PROFUNDIDAD_MAX, 0, tablaFunciones, listas, funcion);
    // printf("La funcion: ");
    if (funcionEncontrada == SUCCESS) {
        for (int i = 0; i <= funcion->ultimo; i++) {
            printf("%s ", funcion->def[i]);
        }
    }

    free(funcion->def);
    free(funcion);
}

int podar(FLista *funcion, char *subfuncion) {
    if (!flista_es_vacia(funcion)) {
        char *ultimo_str = funcion->def[funcion->ultimo];
        return (strcmp(ultimo_str, "Oi") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimo_str, "Od") == 0 && strcmp(subfuncion, "Dd") == 0) ||
               (strcmp(ultimo_str, "Si") == 0 && strcmp(subfuncion, "Di") == 0) ||
               (strcmp(ultimo_str, "Sd") == 0 && strcmp(subfuncion, "Dd") == 0);
    }
    return 0;
}

int buscar_funcion(int length, int pos, THash *tablaFunciones, DList *listas, FLista *f) {
    if (pos == length)
        return FAIL;

    int resultado = FAIL;
    for (int i = 0; i < tablaFunciones->capacidad && resultado != SUCCESS; i++) {
        if (tablaFunciones->tabla[i] && !podar(f, tablaFunciones->tabla[i]->key)) {
            // fprintf(stderr, "%s", tablaFunciones->tabla[i]->key);

            flista_insertar(f, tablaFunciones->tabla[i]->key);

            for (int j = 0; j <= f->ultimo; j++) {
                fprintf(stderr, "%s ", f->def[j]);
            }
            printf("\n");

            resultado = probar_funcion(f, listas->primero, tablaFunciones);
            if (resultado == ERROR_APPLY) {
                fprintf(stderr, " ERROR:%d\n", resultado);
                f->ultimo--;
            }

            if (resultado == FAIL) {
                resultado = buscar_funcion(length, pos + 1, tablaFunciones, listas, f);
                f->ultimo--;
            }
        }
    }

    return resultado;
}
