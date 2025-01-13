#include "generacion.h"

void liberar_tablero(Tablero* tab){
	liberar_matriz(tab->matriz, tab->dimension);
	free(tab);
}

void abortar(Tablero* tab, FILE* archivo){
	liberar_tablero(tab);
	fclose(archivo);
	exit(1);
}



void validar_entrada(Tablero* tab, FILE* archivo){
	int dimension = tab->dimension;
	int cantObstaculos = tab->cantObstaculosFijos + tab->cantObstaculosAleatorios;
	pair ini = tab->inicio, fin = tab->final;
	
	if(!dentro_matriz(ini, dimension, dimension) || !dentro_matriz(fin, dimension, dimension)){
		fprintf(stderr, "\nError: La posicion de inicio y final deben estar dentro del cuadrado de la dimension dada.\n");
		abortar(tab, archivo);
	}

	if(tab->matriz[ini.x - 1][ini.y - 1] == '1')
		cantObstaculos--;

	if(tab->matriz[fin.x - 1][fin.y - 1] == '1')
		cantObstaculos--;

	if(cantObstaculos > dimension * dimension - 2){
		fprintf(stderr, "\nError: La cantidad de obstaculos debe ser menor que la dimension^2 - 2\n");
		abortar(tab, archivo);
	}
	if(ini.x == fin.x && ini.y == fin.y){
		fprintf(stderr, "Error: La posicion de inicio no debe coincidir con la del objetivo.\n");
		abortar(tab, archivo);
	}
	
}

void leer_dimension(FILE *archivo, Tablero* tab){
	int dimension;
	if(fscanf(archivo, "%*s %d %*[^\n]", &dimension) != 1){
		fprintf(stderr, "\nError en la lectura del archivo.\n");
		abortar(tab, archivo);
	}
	
	tab->dimension = dimension;
}

void leer_obstaculos_fijos(FILE *archivo, Tablero* tab){
	int x, y, cantFijos = 0, dimension;
	dimension = tab->dimension;
	
	while(fscanf(archivo, " (%d,%d)", &x, &y) != 0){
		if(x > 0 && x <= dimension && y > 0 && y <= dimension){
			tab->matriz[x-1][y-1] = '1';
			cantFijos++;
		}
	}
	
	tab->cantObstaculosFijos = cantFijos;
}

void leer_cant_obstaculos_aleatorios(FILE *archivo, Tablero *tab){
	int cantAleatorios;
	if(fscanf(archivo, "%*[^\n] %d", &cantAleatorios) != 1){
		fprintf(stderr, "\nError en la lectura del archivo.\n");
		abortar(tab, archivo);
	}

	tab->cantObstaculosAleatorios = cantAleatorios;
}

void leer_posicion_inicio(FILE *archivo, Tablero *tab){
	pair ini; 
	if(fscanf(archivo, " %*[^\n] (%d,%d)", &ini.x, &ini.y) != 2){
		fprintf(stderr, "\nError en la lectura del archivo.\n");
		abortar(tab, archivo);
	}

	tab->inicio = ini;
}

void leer_posicion_final(FILE *archivo, Tablero *tab){
	pair fin; 
	if(fscanf(archivo, " %*[^\n] (%d,%d)", &fin.x, &fin.y) != 2){
		fprintf(stderr, "\nError en la lectura del archivo.\n");
		abortar(tab, archivo);
	}
	
	tab->final = fin;
}

Tablero *obtener_informacion(FILE *archivo){
		
	Tablero* tab = malloc(sizeof(Tablero));
	
	leer_dimension(archivo, tab);
	int dimension = tab->dimension;

	inicializar_matriz(&tab->matriz, dimension, dimension);
	llenar_matriz_con_char (tab->matriz, dimension, dimension, '0');

	leer_obstaculos_fijos(archivo, tab);
	leer_cant_obstaculos_aleatorios(archivo, tab);
	
	leer_posicion_inicio(archivo, tab);
	leer_posicion_final(archivo, tab);
	pair ini, fin;

	ini = tab->inicio;
	fin = tab->final;

	validar_entrada(tab, archivo);

	tab->matriz[ini.x - 1][ini.y - 1] = 'I';
	tab->matriz[fin.x - 1][fin.y - 1] = 'X';

	return tab;
}

void colocar_obstaculos_aleatorios (Tablero* tab){
	srand(time(NULL));
	int x, y, dim, cantAleatorios;
	
	char** matriz = tab->matriz;
	cantAleatorios = tab->cantObstaculosAleatorios;
	dim = tab->dimension;
	
	while(cantAleatorios--){
		x = generar_aleatorio(dim);
		y = generar_aleatorio(dim);

		while(matriz[x][y] != '0'){
			x = generar_aleatorio(dim);
			y = generar_aleatorio(dim);
		}
		matriz[x][y] = '1';
	}

}

