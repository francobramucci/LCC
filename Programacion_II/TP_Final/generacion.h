#ifndef GENERACION_H
#define GENERACION_H

#include "utils.h"

/*
 * Almacena informacion sobre el tablero (dimension y cantidad de obstaculos
 * aleatorios) y una matriz donde se cargarán los obstaculos y las posiciones
 * de inicio y final.
 */
typedef struct {
	int dimension;
	char** matriz;
	int cantObstaculosAleatorios;
} Tablero;


/*
 * Valida que se cumplan ciertas condiciones necesarias para el funcionamiento
 * del programa.
 */
void validar_entrada(int dimension, int cantObstaculos, pair ini, pair fin);


/*
 * Recibe un puntero a archivo y lee la informacion formateada de la forma
 * propuesta para luego guardarla en la estructura de tipo Tablero. Se
 * considera que si la posicion de inicio o final esta sobre un obstaculo
 * previamente fijado se sobreescribira dicha posicion con la de inicio o final
 * descartando al obstaculo
 */
Tablero *obtener_informacion (FILE *archivo);


/*
 * Genera posiciones aleatorias para colocar los obstaculos en la matriz dentro
 * de la estructura Tablero. Se considera que una posicion valida de un
 * obstaculo aleatorio es aquella donde no hay un obstaculo o una posicion de
 * inicio o final.
 */
void colocar_obstaculos_aleatorios (Tablero* tab);

void impimir_tablero(Tablero* tab, FILE* laberinto);

void liberar_tablero(Tablero* tab);


#endif

