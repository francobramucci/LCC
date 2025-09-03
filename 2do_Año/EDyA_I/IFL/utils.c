#include "utils.h"
#include <assert.h>

char *copiar_string(char *str) {
    if (str == NULL)
        return NULL;

    char *copia = malloc(strlen(str) + 1);
    assert(copia);
    strcpy(copia, str);

    return copia;
}

int *copiar_puntero_entero(int *i) {
    int *j = malloc(sizeof(int));
    assert(j);
    *j = *i;

    return j;
}

void destruir_puntero_entero(int *i) {
    free(i);
}

int comparar_referencia_puntero_entero(int *i, int *j) {
    if (!i || !j)
        return 0;
    if (*i > *j)
        return 1;
    if (*i < *j)
        return -1;
    return 0;
}

void imprimir_puntero_entero(int *i) {
    printf("%d", *i);
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
