#include "utils.h"

FILE* abrir_archivo (char *ruta, char *modo){
	FILE* archivo = fopen(ruta, modo);
	if(archivo == NULL){
		fprintf(stderr, "El archivo no existe o ha ocurrido un problema al abrirlo.\n");
		exit(1);
	}

	return archivo;
}

void inicializar_matriz(char ***matriz, int m, int n){
	*matriz = malloc(sizeof(char*) * m);
	int aux = n;
	while(aux--){
		(*matriz)[aux] = malloc(sizeof(char) * n);
	}
}

void llenar_matriz_con_char(char **matriz, int m, int n, char valor){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			matriz[i][j] = valor;
}

int dentro_matriz(pair cord, int m, int n){
	return cord.x > 0 && cord.x <= n && cord.y > 0 && cord.y <= m;
}

void liberar_matriz(char **matriz, int m){
	for(int i = 0; i < m; i++)
		free(matriz[i]);
	free(matriz);
}

int generar_aleatorio(int n){
	return rand() % n;
}

void impimir_matriz(char **matriz, int m, int n, FILE* salida){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			fprintf(salida, "%c", matriz[i][j]);
		}
		fprintf(salida, "\n");
	}
}
