#include "arregloenteros.h"

ArregloEnteros* arreglo_enteros_crear(int capacidad){	
	ArregloEnteros *p_Arrint = malloc(sizeof(ArregloEnteros));
	p_Arrint->direccion = malloc(sizeof(int) * capacidad); // = arr[capacidad];
	p_Arrint->capacidad = capacidad;
	return p_Arrint;
}

void arreglo_enteros_destruir(ArregloEnteros* arreglo){
	free(arreglo->direccion);
	free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos){
	printf("%d", arreglo->direccion[pos]);
	return arreglo->direccion[pos];
}

void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato){
	arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros* arreglo){
	return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros* arreglo){
	for(int i = 0; i < arreglo->capacidad; i++)
		printf("%d\n", arreglo->capacidad[i]);
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad){
	arreglo->direccion = malloc(sizeof(int) * capacidad);
	arreglo->capacidad = capacidad;
}
