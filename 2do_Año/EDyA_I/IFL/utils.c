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

int *copia_fisica_int(int *i) {
    int *copia = malloc(sizeof(int));
    *copia = *i;
    return copia;
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
