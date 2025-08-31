#include "flista.h"

FLista *flista_crear(int capacidad) {
    FLista *funcion = malloc(sizeof(FLista));
    funcion->def = malloc(sizeof(char *) * capacidad);
    funcion->capacidad = capacidad;
    funcion->ultimo = -1;

    return funcion;
}

void flista_insertar(FLista *funcion, char *subFuncion) {
    int ultimo = funcion->ultimo;
    if (ultimo + 1 == funcion->capacidad)
        flista_redimensionar(funcion);
    funcion->def[ultimo + 1] = subFuncion;
    funcion->ultimo++;
}

void flista_redimensionar(FLista *funcion) {
    funcion->capacidad *= 2;
    funcion->def = realloc(funcion->def, funcion->capacidad);
}

void flista_destruir(FLista *funcion) {
    if (funcion) {
        for (int i = 0; i <= funcion->ultimo; i++) {
            free(funcion->def[i]);
        }
        free(funcion->def);
        free(funcion);
    }
}

int flista_es_vacia(FLista *funcion) {
    return funcion->ultimo == -1;
}
