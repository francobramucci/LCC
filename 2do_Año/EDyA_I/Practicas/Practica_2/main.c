#include "slist.h"

static void imprimir_entero(int dato) {
	printf("%d ", dato);
}

static int comparar_enteros(int x, int y){
	if(x > y)
		return 1;
	if(x < y)
		return -1;
	return 0;
}

int main(int argc, char *argv[]) {

	SList lista = slist_crear();

	lista = slist_agregar_inicio(lista, 3);
	lista = slist_agregar_inicio(lista, 2);
	lista = slist_agregar_inicio(lista, 1);
	lista = slist_agregar_final(lista, 4);
	lista = slist_agregar_final(lista, 10);
	lista = slist_agregar_final(lista, 9);
	lista = slist_insertar(lista, 9, 1);

	slist_recorrer(lista, imprimir_entero);
	printf("\n");
	lista = slist_ordenar(lista, comparar_enteros);
	printf("\n");
	slist_recorrer(lista, imprimir_entero);

	SList segundaMitad = slist_partir(lista);
	printf("\n");
	slist_recorrer(segundaMitad, imprimir_entero);
	puts("");

	slist_destruir(lista);

	return 0;
}
