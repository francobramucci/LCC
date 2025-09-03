#include "flista.h"
#include <stdio.h>

FLista *flista_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir) {
    FLista *funcion = vector_crear(capacidad, copiar, destruir);
    return funcion;
}

void flista_insertar(FLista *funcion, char *subFuncion) {
    vector_insertar(funcion, subFuncion);
}

void flista_destruir(FLista *funcion) {
    vector_destruir(funcion);
}

int flista_es_vacia(FLista *funcion) {
    return funcion->ultimo == -1;
}

void flista_eliminar_ultimo(FLista *funcion) {
    vector_eliminar_ultimo(funcion);
}

char *flista_acceder(FLista *funcion, int indice) {
    return (char *)funcion->arr[indice];
}

void flista_imprimir(FLista *funcion) {
    char *opAnt = flista_acceder(funcion, 0);
    printf("%s", flista_acceder(funcion, 0));

    for (int i = 1; i <= funcion->ultimo; i++) {
        char *opActual = flista_acceder(funcion, i);
        if (opAnt[0] == '<' || opActual[0] == '>')
            printf("%s", opActual);
        else
            printf(" %s", opActual);

        opAnt = opActual;
    }
}
