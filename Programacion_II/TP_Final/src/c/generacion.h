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
	int cantObstaculosFijos;
	pair inicio;
	pair final;
} Tablero;


/*
 * Toma un puntero a tablero y libera la memoria reservada para este
 */
void liberar_tablero(Tablero* tab);


/*
 * Libera la memoria reservada para el tablero y cierra el archivo de entrada.
 */
void abortar(Tablero* tab, FILE* archivo);


/*
 * Valida ciertas condiciones necesarias para el funcionamiento del programa.
 * En caso de que haya un obstaculo en la posicion de inicio o final dicho
 * obstaculo sera eliminado, no contado y se colocara la posicion de inicio o
 * fin correspondiente. En caso de que alguna de estas condiciones necesarias
 * no sea cumplida se terminara la ejecucion del programa.
 */
void validar_entrada(Tablero* tab, FILE* archivo);


/*
 * Recibe un archivo de entrada y lee y guarda un entero en un campo del
 * tablero que representa la dimension.
 */
void leer_dimension(FILE *archivo, Tablero* tab);


/*
 * Lee de la entrada pares ordenados que representan los obstaculos fijos y
 * marca dichas posiciones en la matriz cuadrada del tablero. En caso de que
 * alguna posicion sea invalida se termina la ejecucion del programa.
 */
void leer_obstaculos_fijos(FILE *archivo, Tablero *tab);


/*
 * Lee la cantidad de obstaculos aleatorios y se almacena en la estructura
 * Tablero.
 */
void leer_cant_obstaculos_aleatorios(FILE *archivo, Tablero *tab);


/*
 * Lee un par ordenado que representa la posicion inicial del laberinto y se
 * almacena en un campo del tablero para su posterior verificacion.
 */
void leer_posicion_inicio(FILE *archivo, Tablero *tab);


/*
 * Lee un par ordenado que representa la posicion del objetivo del laberinto y
 * se almacena en un campo del tablero para su posterior verificacion.
 */
void leer_posicion_final(FILE *archivo, Tablero *tab);


/*
 * Recibe un puntero a archivo y lee la informacion formateada de la forma
 * propuesta para luego guardarla en la estructura de tipo Tablero.
 */
Tablero *obtener_informacion (FILE *archivo);


/*
 * Genera posiciones aleatorias para colocar los obstaculos en la matriz dentro
 * de la estructura Tablero. Se considera que una posicion valida de un
 * obstaculo aleatorio es aquella donde no hay un obstaculo o una posicion de
 * inicio o final.
 */
void colocar_obstaculos_aleatorios (Tablero* tab);

#endif
