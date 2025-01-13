#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Almacena un par de enteros.
typedef struct {
	int x;
	int y;
} pair;


/*
 * Recibe la ruta de un archivo y el modo de apertura y retorna un puntero a
 * archivo.
 */
FILE* abrir_archivo (char *ruta, char *modo);


/*
 * Toma un triple puntero y un entero n y reserva memoria para una matriz de
 * char de n*n.
 */
void inicializar_matriz(char ***matriz, int m, int n);


/*
 * Toma un doble puntero que apunta a una matriz de m*n y un char y llena a la
 * matriz con dicho valor char.
 */
void llenar_matriz_con_char(char **matriz, int m, int n, char valor);


/*
 * Verifica si un par ordenado de numeros se encuentra en una matriz de m*n.
 */
int dentro_matriz(pair cord, int m, int n);


/*
 * Libera una matriz de char de m*n
 */
void liberar_matriz(char **matriz, int m);

/*
 * Genera un numero aleatorio entre 0 y n-1 incluidos
 */
int generar_aleatorio(int n);

/*
 * Imprime una matriz de m*n a una salida
 */
void impimir_matriz(char **matriz, int m, int n, FILE* salida);
#endif

