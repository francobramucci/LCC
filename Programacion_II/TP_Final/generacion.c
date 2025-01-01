#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	int x;
	int y;
} pair;

typedef struct {
	char** matriz;
	int cantObstaculosAleatorios;
} Tablero;

FILE* abrir_archivo (char *ruta, char *modo){
	FILE* archivo = fopen(ruta, modo);
	assert(archivo != NULL);

	return archivo;
}

void inicializar_matriz_cuadrada (char ***matriz, int n){
	*matriz = malloc(sizeof(char*) * n);
	int aux = n;
	while(aux--){
		(*matriz)[aux] = malloc(sizeof(char) * n);
	}
}

void llenar_matriz_con_char (char **matriz, int n, char valor){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			matriz[i][j] = valor;
}

// Asegurarse de que la cantidad de obstaculos posibilita una solución y que 
// no hay obstaculos ni en el inicio ni en el final y que la posicion de inicio
// no coincida con la del objetivo.
int validar_entrada(char **matriz, int dimension, int cantObstaculos, pair ini, pair fin){
	if(cantObstaculos <= dimension * dimension - 2){
		printf("La cantidad de obstaculos debe ser menor que la dimension^2-2\n");
		return 1;
	}
	if(matriz[ini.x][ini.y] != '1'){
		printf("No debe haber obstaculos en la posicion de inicio\n");
		return 1;
	}
	if(matriz[fin.x][fin.y] != '1'){
		printf("No debe haber obstaculos en la posicion del objetivo\n");
		return 1;
	}
	if(ini.x != fin.x || ini.y != fin.y){
		printf("La posicion de inicio no debe coincidir con la del objetivo\n");
		return 1;
	}

	return 0;
}

// Se lee el archivo con el formato propuesto. Se guarda la informacion en una 
Tablero *obtener_informacion (FILE *archivo){
		
	Tablero* tab = malloc(sizeof(Tablero));
	
	int dimension;
	fscanf(archivo, "%*s %d %*[^\n]", &dimension);

	inicializar_matriz_cuadrada(&tab->matriz, dimension);
	llenar_matriz_con_char (tab->matriz, dimension, '0');

	int x;
	int y;
	int cantFijos = 0;

	while(fscanf(archivo, " (%d,%d)", &x, &y) != 0){
		if(x > 0 && x < dimension && y > 0 && y < dimension){
			tab->matriz[x-1][y-1] = '1';
			cantFijos++;
		}
	}
	
	pair ini, fin;
	fscanf(archivo, "%*[^\n] %d (%d,%d) %*s (%d,%d)", &tab->cantObstaculosAleatorios, &ini.x, &ini.y, &fin.x, &fin.y);
	assert(validar_entrada(tab->matriz, dimension, cantFijos + tab->cantObstaculosAleatorios, ini, fin) != 1);
		
	tab->matriz[ini.x][ini.y] = 'I';
	tab->matriz[fin.x][fin.y] = 'X';

	return tab;
}


int main(int argc, char **argv){
	if(argc != 2){
		printf("Ingrese el archivo con la informacion del tablero\n");
		return 1;
	}
	FILE* archivo = abrir_archivo(argv[1], "r");
	
	Tablero* tablero;
	tablero = obtener_informacion(archivo);
	


	return 0;
}

