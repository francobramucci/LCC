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
void inicializar_matriz_cuadrada (char ***matriz, int n);


/*
 * Toma un doble puntero que apunta a una matriz de n*n, el entero n y un char
 * y llena a la matriz con dicho valor char.
 */
void llenar_matriz_con_char (char **matriz, int n, char valor);


/* 
 * Verifica si un par ordenado de numeros se encuentra en un cuadrado de
 * dimension n*n.
 */
int dentro_cuadrado(pair cord, int dimension);

#endif

