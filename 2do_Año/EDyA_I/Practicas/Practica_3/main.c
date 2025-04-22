#include "pilas.h"
#include "gpilas.h"

void* copiar_entero(void* i){
	int* dato = malloc(sizeof(int));
	*dato = (*(int*)i);

	return dato;
}

void imprimir_entero(void* i){
	printf("%d ", (*(int*)i));
}


int main(){
	Pila p = pila_crear(10);
	pila_apilar(p, 10);
	pila_imprimir(p);

	GPila gp = gpila_crear();
	int* i = malloc(sizeof(int));
	*i = 4;
	gp = gpila_apilar(gp, i, copiar_entero);
	
	gpila_imprimir(gp, imprimir_entero);

	return 0;
}
