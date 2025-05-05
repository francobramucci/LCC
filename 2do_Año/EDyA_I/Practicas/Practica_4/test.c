#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int* data) {
	printf("%d ", *data);
}

int* copiar_entero(int *data){
	int *copia = malloc(sizeof(int));
	*copia = *data;
	return copia;
}

void destruir_entero(int *dato){
	free(dato);
}

int main() {
	BTree ll = btree_unir(&1, btree_crear(), btree_crear(), (FuncionCopia) copiar_entero);
	BTree l = btree_unir(&2, ll, btree_crear());
	BTree r = btree_unir(&3, btree_crear(), btree_crear(), (FuncionCopia) copiar_entero);
	BTree raiz = btree_unir(&4, l, r, (FuncionCopia) copiar_entero);
// 	 4
// 	2 3
// 1

	btree_recorrer(raiz, BTREE_RECORRIDO_POST, (FuncionVisitante) imprimir_entero);
	puts("");

	btree_recorrer_preorder(raiz, (FuncionVisitante)imprimir_entero);

	btree_destruir(raiz, (FuncionDestructora) destruir_entero);

	return 0;
}
