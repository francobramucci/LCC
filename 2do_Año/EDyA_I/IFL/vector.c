#include "vector.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Dado un vector lo redimensiona al doble de la capacidad original
 */
static void vector_redimensionar(Vector *vec);

Vector *vector_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir) {
    Vector *vec = malloc(sizeof(Vector));
    assert(vec);
    vec->arr = malloc(sizeof(void *) * capacidad);
    assert(vec->arr);
    vec->capacidad = capacidad;
    vec->ultimo = -1;
    vec->copiar = copiar;
    vec->destruir = destruir;

    return vec;
}

void vector_insertar(Vector *vec, void *dato) {
    int ultimo = vec->ultimo;
    if (ultimo + 1 == vec->capacidad)
        vector_redimensionar(vec);
    vec->arr[ultimo + 1] = vec->copiar(dato);
    vec->ultimo++;
}

void vector_destruir(Vector *vec) {
    if (vec) {
        for (int i = 0; i <= vec->ultimo; i++) {
            vec->destruir(vec->arr[i]);
        }
        free(vec->arr);
        free(vec);
    }
}

void vector_eliminar_ultimo(Vector *vec) {
    if (!vector_es_vacio(vec)) {
        vec->destruir(vec->arr[vec->ultimo]);
        vec->ultimo--;
    }
}

int vector_es_vacio(Vector *vec) {
    return vec->ultimo == -1;
}

void *vector_acceder(Vector *vec, int indice) {
    if (indice >= 0 && indice <= vec->ultimo)
        return vec->arr[indice];
    return NULL;
}

int vector_largo(Vector *vec) {
    return vec->ultimo + 1;
}

static void vector_redimensionar(Vector *vec) {
    vec->capacidad *= 2;
    vec->arr = realloc(vec->arr, vec->capacidad * sizeof(void *));
}
