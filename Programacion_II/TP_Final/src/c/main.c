#include "generacion.h"

int main(int argc, char **argv){
	if(argc != 2){
		printf("Ingrese el archivo con la informacion del tablero\n");
		return 1;
	}
	FILE* entrada = abrir_archivo(argv[1], "r");

	Tablero* tablero;
	tablero = obtener_informacion(entrada);
	colocar_obstaculos_aleatorios(tablero);
	
	int dimension = tablero->dimension;

	FILE* laberinto = abrir_archivo("SalidaLaberinto.txt", "w+");
	impimir_matriz(tablero->matriz, dimension, dimension, laberinto);
	
	liberar_tablero(tablero);
	fclose(entrada);
	fclose(laberinto);

	return 0;
}

