#include "utils.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

char *copiar_string(char *str) {
    if (str == NULL)
        return NULL;

    char *copia = malloc(strlen(str) + 1);
    assert(copia);
    strcpy(copia, str);

    return copia;
}

int *copiar_entero(int *i) {
    int *j = malloc(sizeof(int));
    assert(j);
    *j = *i;

    return j;
}

void destruir_entero(int *i) {
    free(i);
}

int comparar_enteros(int *i, int *j) {
    if (*i < *j)
        return -1;
    if (*i > *j)
        return 1;
    return 0;
}

void *retornar_puntero(void *a) {
    return a;
}

void liberar_puntero(void *a) {
    free(a);
}

void funcion_vacia(void *a) {
    (void)a;
    return;
}
