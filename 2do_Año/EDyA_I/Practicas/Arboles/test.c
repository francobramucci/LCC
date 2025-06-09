#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimir_entero(int *data) {
    printf("%d ", *data);
}

int *copiar_entero(int *data) {
    int *copia = malloc(sizeof(int));
    *copia = *data;
    return copia;
}

void destruir_entero(int *dato) {
    free(dato);
}

int main() {
    int a_1 = 1, a_2 = 2, a_3 = 3, a_4 = 4;
    BTree ll = btree_unir(&a_1, btree_crear(), btree_crear(), (FuncionCopia)copiar_entero);
    BTree l = btree_unir(&a_2, ll, btree_crear(), (FuncionCopia)copiar_entero);
    BTree r = btree_unir(&a_3, btree_crear(), btree_crear(), (FuncionCopia)copiar_entero);
    BTree raiz = btree_unir(&a_4, l, r, (FuncionCopia)copiar_entero);
    // 	 4
    // 	2 3
    // 1

    btree_recorrer(raiz, BTREE_RECORRIDO_PRE, (FuncionVisitante)imprimir_entero);
    puts("");

    btree_recorrer_preorder(raiz, (FuncionVisitante)imprimir_entero);

    btree_destruir(raiz, (FuncionDestructora)destruir_entero);

    return 0;
}
