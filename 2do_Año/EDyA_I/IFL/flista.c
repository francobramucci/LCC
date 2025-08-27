#include "flista.h"

FLista *flista_crear(int tamBuffer) {
    FLista *funcion = malloc(sizeof(FLista));
    funcion->def = malloc(sizeof(char *) * tamBuffer);
    funcion->largo = 0;

    return funcion;
}

void flista_destruir(FLista *funcion) {
    if (funcion) {
        for (int i = 0; i < funcion->largo; i++) {
            free(funcion->def[i]);
        }
        free(funcion->def);
        free(funcion);
    }
}
