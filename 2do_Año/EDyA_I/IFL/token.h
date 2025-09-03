#ifndef __TOKEN_H__
#define __TOKEN_H__
#include <ctype.h>
#include <stdlib.h>

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_ERROR,

    // Tipos de sentencia
    TOKEN_DEFL,
    TOKEN_DEFF,
    TOKEN_APPLY,
    TOKEN_SEARCH,

    // Identificadores
    TOKEN_IDENTIFICADOR,

    // Operadores
    TOKEN_ASIGNACION,
    TOKEN_REPETICION_INI,
    TOKEN_REPETICION_FIN,
    TOKEN_COMPOSICION,

    // Listas
    TOKEN_LIST_LITERAL,

    // Puntuacion
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COMA,
    TOKEN_SEMICOLON,

    // Numero
    TOKEN_NUM
} TokenType;

typedef struct {
        TokenType type;
        char *value;
} Token;

Token *crear_token();

void liberar_token(Token *token);

void obtener_siguiente_token(char *input, int *posActual, int saltearEspacios, Token *token);

void obtener_siguiente_token_lista(char *lista, int *posActual, Token *token);

#endif // !__TOKEN_H__
