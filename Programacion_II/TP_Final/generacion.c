#include "generacion.h"
// TODO:: Comentar el codigo, hacer los .h, makefile, archivo con disposiciones anteriores, chequear valgrind.


typedef struct {
	int x;
	int y;
} pair;

typedef struct {
	int dimension;
	char** matriz;
	int cantObstaculosFijos;
	int cantObstaculosAleatorios;
	pair inicio;
	pair final;
} Tablero;

FILE* abrir_archivo (char *ruta, char *modo){
	FILE* archivo = fopen(ruta, modo);
	if(archivo == NULL){
		fprintf(stderr, "El archivo no existe o ha ocurrido un problema al abrirlo.\n");
		exit(1);
	}

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

int dentro_cuadrado(pair cord, int n){
	return cord.x > 0 && cord.x <= n && cord.y > 0 && cord.y <= n;
}

void liberar_tablero(Tablero* tab){
	int dim = tab->dimension;
	for(int i = 0; i < dim; i++)
		free(tab->matriz[i]);

	free(tab->matriz);
	free(tab);
}

void limpiar(Tablero* tab, FILE* archivo){
	liberar_tablero(tab);
	fclose(archivo);
}

void validar_entrada(Tablero* tab, FILE* archivo){
	int dimension = tab->dimension;
	int cantObstaculos = tab->cantObstaculosFijos + tab->cantObstaculosAleatorios;
	pair ini = tab->inicio, fin = tab->final;
	
	if(!dentro_cuadrado(ini, dimension) || !dentro_cuadrado(fin, dimension)){
		fprintf(stderr, "\nError: La posicion de inicio y final deben estar dentro del cuadrado de la dimension dada.\n");
		limpiar(tab, archivo);
		exit(1);
	}

	if(tab->matriz[ini.x - 1][ini.y - 1] == '1')
		cantObstaculos--;

	if(tab->matriz[fin.x - 1][fin.y - 1] == '1')
		cantObstaculos--;

	if(cantObstaculos > dimension * dimension - 2){
		fprintf(stderr, "\nError: La cantidad de obstaculos debe ser menor que la dimension^2 - 2\n");
		limpiar(tab, archivo);
		exit(1);
	}
	if(ini.x == fin.x && ini.y == fin.y){
		fprintf(stderr, "Error: La posicion de inicio no debe coincidir con la del objetivo.\n");
		limpiar(tab, archivo);
		exit(1);
	}
	
}

void leer_dimension(FILE *archivo, Tablero* tab){
	int dimension;
	fscanf(archivo, "%*s %d %*[^\n]", &dimension);
	
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
	fscanf(archivo, "%*[^\n] %d", &cantAleatorios);

	tab->cantObstaculosAleatorios = cantAleatorios;
}

void leer_posicion_inicio(FILE *archivo, Tablero *tab){
	pair ini; 
	fscanf(archivo, " %*[^\n] (%d,%d)", &ini.x, &ini.y);
	
	tab->inicio = ini;
}

void leer_posicion_final(FILE *archivo, Tablero *tab){
	pair fin; 
	fscanf(archivo, " %*[^\n] (%d,%d)", &fin.x, &fin.y);
	
	tab->final = fin;
}

Tablero *obtener_informacion(FILE *archivo){
		
	Tablero* tab = malloc(sizeof(Tablero));
	
	leer_dimension(archivo, tab);
	int dimension = tab->dimension;

	inicializar_matriz_cuadrada(&tab->matriz, dimension);
	llenar_matriz_con_char (tab->matriz, dimension, '0');

	leer_obstaculos_fijos(archivo, tab);
	int cantFijos = tab->cantObstaculosFijos;
	
	leer_cant_obstaculos_aleatorios(archivo, tab);
	int cantAleatorios = tab->cantObstaculosAleatorios;
	
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

int generar_aleatorio(int n){
	return rand() % n;
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

void impimir_tablero(Tablero* tab, FILE* laberinto){
	int dimension = tab->dimension;
	char** matriz = tab->matriz;
	for(int i = 0; i < dimension; i++){
		for(int j = 0; j < dimension; j++){
			fprintf(laberinto, "%c", matriz[i][j]);
		}
		fprintf(laberinto, "\n");
	}

}


int main(int argc, char **argv){
	if(argc != 2){
		printf("Ingrese el archivo con la informacion del tablero\n");
		return 1;
	}
	FILE* entrada = abrir_archivo(argv[1], "r");

	Tablero* tablero;
	tablero = obtener_informacion(entrada);
	colocar_obstaculos_aleatorios(tablero);

	FILE* laberinto = abrir_archivo("laberinto.txt", "w+");
	impimir_tablero(tablero, laberinto);
	
	limpiar(tablero, entrada);
	fclose(laberinto);

	return 0;
}

