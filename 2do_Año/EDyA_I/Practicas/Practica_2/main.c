#include "slist.h"
#include "dlist.h"

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

	SListF *listF = slistf_crear();
	slistf_agregar_inicio(listF, 19);
	
	printf("!%d!\n", listF->primero->dato);
	
	DList *dlist = dlist_crear();
	dlist_agregar_inicio(dlist, 4);
	dlist_agregar_inicio(dlist, 3);
	dlist_agregar_inicio(dlist, 2);
	dlist_agregar_inicio(dlist, 1);

	dlist_recorrer(dlist, 1, imprimir_entero);

	return 0;
}
