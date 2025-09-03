#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *copiar_string(char *str);

int *copiar_puntero_entero(int *i);

void destruir_puntero_entero(int *i);

int comparar_referencia_puntero_entero(int *i, int *j);

void imprimir_puntero_entero(int *i);

void *retornar_puntero(void *a);

void liberar_puntero(void *a);

void funcion_vacia(void *a);

#endif // !__UTILS_H__
