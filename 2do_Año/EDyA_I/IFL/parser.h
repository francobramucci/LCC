#ifndef __PARSER_H__
#define __PARSER_H__
#include "apply.h"
#include "token.h"
#include "utils.h"
#include <ctype.h>

void saltear_espacios(char *input, int *posActual);

void obtener_siguiente_token(char *input, int *posActual, int saltearEspacios, Token *token);

void obtener_siguiente_token_lista(char *lista, int *posActual, Token *token);

DList *parsear_lista(char *lista);

void parsear_defl(char *input, int *posActual, THash *tablaHash);

FLista *parsear_funcion(char *input, int *posActual, THash *tablaHash);

void parsear_deff(char *input, int *posActual, THash *tablaHashFunciones);

void parsear_apply(char *input, int *posActual, THash *tablaHashListas, THash *tablaHashFunciones);

void parsear_search(char *input, int *posActual, THash *tablaHashListas);

void parsear_expresion(char *input, THash *tablaHashListas, THash *tablaHashFunciones);

#endif // __PARSER_H__
