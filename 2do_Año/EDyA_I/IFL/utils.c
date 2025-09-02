#include "utils.h"
#include <string.h>

char *copiar_string(char *str) {
    if (str == NULL)
        return NULL;

    char *copia = malloc(strlen(str) + 1);
    strcpy(copia, str);

    return copia;
}

char *copiar_substring(const char *str, int ini, int fin) {
    if (ini < 0 || fin < ini)
        return NULL;

    int largo = fin - ini;
    char *copia = malloc(largo + 1);

    if (!copia) {
        perror("Error reservando memoria en copiar_substring");
        exit(EXIT_FAILURE);
    }

    strncpy(copia, str + ini, largo);
    copia[largo] = '\0';

    return copia;
}

int es_primo(int n) {
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    int esPrimo = 1;

    for (int i = 5; i * i <= n && esPrimo; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            esPrimo = 0;
    }

    return esPrimo;
}

int primo_mas_cercano(int n) {
    int p = 0;

    for (int i = 0; p == 0; i++) {
        if (es_primo(n - i))
            p = n - i;
        else if (es_primo(n + i))
            p = n + i;
    }

    return p;
}

int *copiar_puntero_entero(int *i) {
    int *j = malloc(sizeof(int));
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
    // (void)a;
    return;
}
