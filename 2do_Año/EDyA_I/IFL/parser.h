#ifndef __PARSER_H__
#define __PARSER_H__
#include "search.h"
#include "token.h"
#include "utils.h"
#include <ctype.h>

enum {
    ERROR_SINTAXIS_SENTENCIA,

    ERROR_SINTAXIS_LISTA,

    ERROR_LISTA_NO_DEFINIDA,

    ERROR_LISTA_YA_DEFINIDA,

    ERROR_SUBFUNCION_NO_DEFINIDA,

    ERROR_SINTAXIS_FUNCION,

    ERROR_FUNCION_NO_DEFINIDA,

    ERROR_FUNCION_YA_DEFINIDA
};

void saltear_espacios(char *input, int *posActual);

void obtener_siguiente_token(char *input, int *posActual, int saltearEspacios, Token *token);

void obtener_siguiente_token_lista(char *lista, int *posActual, Token *token);

DList *parsear_lista(char *lista);

void parsear_defl(char *input, int *posActual, THash *tablaHash);

FLista *parsear_funcion(char *input, int *posActual, THash *tablaHash, int *errorCode);

void parsear_deff(char *input, int *posActual, THash *tablaHashFunciones);

void parsear_apply(char *input, int *posActual, THash *tablaHashListas, THash *tablaHashFunciones);

void parsear_search(char *input, int *posActual, THash *tablaHashListas, THash *tablaFunciones);

void parsear_expresion(char *input, THash *tablaHashListas, THash *tablaHashFunciones);

#endif // __PARSER_H__
