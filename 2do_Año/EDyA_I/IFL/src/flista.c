#include "flista.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

FLista *flista_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir) {
    FLista *funcion = malloc(sizeof(FLista));
    assert(funcion);
    funcion->vec = vector_crear(capacidad, copiar, destruir);
    return funcion;
}

void flista_insertar(FLista *funcion, char *subFuncion) {
    vector_insertar(funcion->vec, subFuncion);
}

void flista_destruir(FLista *funcion) {
    if (funcion) {
        vector_destruir(funcion->vec);
        free(funcion);
    }
}

int flista_es_vacia(FLista *funcion) {
    return vector_es_vacio(funcion->vec);
}

void flista_eliminar_ultimo(FLista *funcion) {
    vector_eliminar_ultimo(funcion->vec);
}

char *flista_acceder(FLista *funcion, int indice) {
    return (char *)vector_acceder(funcion->vec, indice);
}

int flista_largo(FLista *funcion) {
    return vector_largo(funcion->vec);
}

char *flista_ultimo_elemento(FLista *funcion) {
    return flista_acceder(funcion, flista_largo(funcion) - 1);
}

void flista_imprimir(FLista *funcion) {
    char *opAnt = flista_acceder(funcion, 0);
    printf("%s", flista_acceder(funcion, 0));

    for (int i = 1; i < flista_largo(funcion); i++) {
        char *opActual = flista_acceder(funcion, i);
        if (opAnt[0] == '<' || opActual[0] == '>')
            printf("%s", opActual);
        else
            printf(" %s", opActual);

        opAnt = opActual;
    }
}
