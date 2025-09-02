#include "flista.h"
#include "vector.h"

FLista *flista_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir) {
    FLista *funcion = vector_crear(capacidad, copiar, destruir);
    return funcion;
}

void flista_insertar(FLista *funcion, char *subFuncion) {
    vector_insertar(funcion, subFuncion);
}

void flista_redimensionar(FLista *funcion) {
    vector_redimensionar(funcion);
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
