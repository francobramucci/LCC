#include "token.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * Avanza hasta el primer caracter distinto de espacio.
 * Dado un input y un puntero, avanza desde la posicion almacenada en el puntero hasta el
 * primer caracter distinto de espacio y actualiza el puntero a esa posicion.
 */
static void saltear_espacios(char *input, int *posActual);

/**
 * Dado un string, un inicio y final, retorna el substring delimitados por dicho inicio y final
 */
static char *copiar_substring(const char *str, int ini, int fin);

Token *crear_token() {
    Token *token = malloc(sizeof(Token));
    assert(token);
    token->type = 0;
    token->value = NULL;

    return token;
}

static void actualizar_token(TokenType type, char *value, Token *token) {
    free(token->value);
    token->type = type;
    token->value = value;
}

void liberar_token(Token *token) {
    if (token) {
        free(token->value);
        free(token);
    }
}

void obtener_siguiente_token(char *input, int *posActual, int saltearEspacios, Token *token) {
    // Saltar espacios en blanco
    if (saltearEspacios) {
        saltear_espacios(input, posActual);
    }

    // Chequear si se llego al final de la entrada
    if (input[*posActual] == '\0') {
        actualizar_token(TOKEN_EOF, NULL, token);
        return;
    }

    // Identificar palabras clave o identificadores
    if (isalnum(input[*posActual])) {
        int inicio = *posActual;
        while (isalnum(input[*posActual]) || input[*posActual] == '_') {
            (*posActual)++;
        }
        int fin = *posActual;
        char *identificador = copiar_substring(input, inicio, fin);

        // Chequear si es una keyword
        if (strcmp(identificador, "defl") == 0) {
            free(identificador);
            actualizar_token(TOKEN_DEFL, NULL, token);
        } else if (strcmp(identificador, "deff") == 0) {
            free(identificador);
            actualizar_token(TOKEN_DEFF, NULL, token);
        } else if (strcmp(identificador, "apply") == 0) {
            free(identificador);
            actualizar_token(TOKEN_APPLY, NULL, token);
        } else if (strcmp(identificador, "search") == 0) {
            free(identificador);
            actualizar_token(TOKEN_SEARCH, NULL, token);
        } else {
            // Es un identificador
            actualizar_token(TOKEN_IDENTIFICADOR, identificador, token);
        }
        return;
    }

    // Identificar listas en formato string
    if (input[*posActual] == '[') {
        (*posActual)++;
        int inicio = *posActual;

        while (input[*posActual] != ']' && input[*posActual] != '\0') {
            (*posActual)++;
        }
        if (input[*posActual] == ']') {
            int fin = *posActual;
            (*posActual)++;

            actualizar_token(TOKEN_LIST_LITERAL, copiar_substring(input, inicio, fin), token);
        } else {
            // Error: Lista abierta por derecha
            actualizar_token(TOKEN_ERROR, NULL, token);
        }
        return;
    }

    // Identificar operadores
    switch (input[*posActual]) {
    case '=':
        actualizar_token(TOKEN_ASIGNACION, NULL, token);
        (*posActual)++;
        return;
    case '<':
        actualizar_token(TOKEN_REPETICION_INI, NULL, token);
        (*posActual)++;
        return;
    case '>':
        actualizar_token(TOKEN_REPETICION_FIN, NULL, token);
        (*posActual)++;
        return;
    case ' ':
        actualizar_token(TOKEN_COMPOSICION, NULL, token);
        (*posActual)++;
        return;
    }

    // Identificar puntuacion
    switch (input[*posActual]) {
    case '{':
        actualizar_token(TOKEN_LBRACE, NULL, token);
        (*posActual)++;
        return;
    case '}':
        actualizar_token(TOKEN_RBRACE, NULL, token);
        (*posActual)++;
        return;
    case ',':
        actualizar_token(TOKEN_COMA, NULL, token);
        (*posActual)++;
        return;
    case ';':
        actualizar_token(TOKEN_SEMICOLON, NULL, token);
        (*posActual)++;
        return;
    }

    // Si no hay coindidencias es un error
    actualizar_token(TOKEN_ERROR, NULL, token);
}

void obtener_siguiente_token_lista(char *lista, int *posActual, Token *token) {
    saltear_espacios(lista, posActual);

    if (lista[*posActual] == '\0') {
        actualizar_token(TOKEN_EOF, NULL, token);
    }

    else if (isdigit(lista[*posActual])) {
        int inicio = *posActual;
        while (isdigit(lista[*posActual]))
            (*posActual)++;
        int fin = *posActual;

        char *num = copiar_substring(lista, inicio, fin);

        actualizar_token(TOKEN_NUM, num, token);
    }

    else if (lista[*posActual] == ',') {
        (*posActual)++;
        actualizar_token(TOKEN_COMA, NULL, token);
    }

    else
        actualizar_token(TOKEN_ERROR, NULL, token);
}

static void saltear_espacios(char *input, int *posActual) {
    while (input[*posActual] != '\0' && isspace(input[*posActual])) {
        (*posActual)++;
    }
}

static char *copiar_substring(const char *str, int ini, int fin) {
    if (ini < 0 || fin < ini)
        return NULL;

    int largo = fin - ini;
    char *copia = malloc(largo + 1);
    assert(copia);

    strncpy(copia, str + ini, largo);
    copia[largo] = '\0';

    return copia;
}
