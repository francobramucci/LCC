#include "gpilas.h"
#include "pilas.h"

void *copiar_puntero_entero(void *i) {
    int *dato = malloc(sizeof(int));
    *dato = (*(int *)i);

    return dato;
}

void imprimir_puntero_entero(void *i) {
    printf("%d ", (*(int *)i));
}

void destruir_puntero_entero(void *i) {
    free(i);
}

int main() {
    Pila p = pila_crear(10);
    pila_apilar(p, 10);
    pila_imprimir(p);
    pila_destruir(p);

    GPila gp = gpila_crear();

    int *i = malloc(sizeof(int));
    *i = 4;
    gp = gpila_apilar(gp, i, copiar_puntero_entero);
    free(i);

    gpila_imprimir(gp, imprimir_puntero_entero);
    printf("\n");

    gpila_destruir(gp, destruir_puntero_entero);

    return 0;
}
