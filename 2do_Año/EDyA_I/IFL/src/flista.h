#ifndef __FLISTA_H__
#define __FLISTA_H__

#include "vector.h"

typedef struct {
        Vector *vec;
} FLista;

/**
 * Crea una función de lista vacía con la capacidad inicial especificada.
 * Recibe funciones de copia y destrucción para manejar la memoria de los elementos.
 * Retorna un puntero a la nueva función de lista.
 */
FLista *flista_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir);

/**
 * Inserta una subfunción (operador o identificador) al final de la función de lista.
 */
void flista_insertar(FLista *funcion, char *subFuncion);

/**
 * Libera toda la memoria asociada a la función de lista,
 * destruyendo sus elementos con la función destructora provista.
 */
void flista_destruir(FLista *funcion);

/**
 * Retorna 1 si la función de lista está vacía, 0 en caso contrario.
 */
int flista_es_vacia(FLista *funcion);

/**
 * Elimina el último elemento de una flista.
 */
void flista_eliminar_ultimo(FLista *funcion);

/**
 * Devuelve la subfunción en la posición indicada (índice).
 */
char *flista_acceder(FLista *funcion, int indice);

/**
 * Devuelve el largo de la FLista.
 */
int flista_largo(FLista *funcion);

/**
 * Devuelve el último elemento de una FLista.
 */
char *flista_ultimo_elemento(FLista *funcion);

/**
 * Imprime en salida estándar todos las subfunciones de la función de lista
 */
void flista_imprimir(FLista *funcion);

#endif // __FLISTA_H__
