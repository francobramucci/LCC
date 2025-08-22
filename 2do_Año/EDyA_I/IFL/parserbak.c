#include "dlist.h"
#include "hash.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Aclaraciones:
 *  - Los identificadores deberán comenzar con una letra.
 *
 * */

// TO DO:
// - parsear_apply
// - parsear_search
// - reemplazar con copiar_substring
// - agregar mensajes de error
// - eliminar posActual como parametro de las funciones de parseo
// - hacer enum con tipos de error

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

char *copiar_substring(const char *str, int ini, int fin) {
    if (ini < 0 || fin < ini) {
        return NULL;
    }

    int largo = fin - ini;
    char *copia = malloc(largo + 1);
    if (!copia) {
        perror("Error reservando memoria en copiar_substring");
        exit(EXIT_FAILURE);
    }

    strncpy(copia, str + ini, largo);
    copia[largo] = '\0';

    return copia;
}

void actualizar_token(TokenType type, char *value, Token *token) {
    token->type = type;
    token->value = value;
}

void liberar_token(Token *token) {
    if (token) {
        free(token->value);
        free(token);
    }
}

void saltear_espacios(char *input, int *posActual) {
    while (input[*posActual] != '\0' && isspace(input[*posActual])) {
        (*posActual)++;
    }
}

void obtener_siguiente_token(char *input, int *posActual, int saltearEspacios, Token *token) {
    // 1. Saltar espacios en blanco
    if (saltearEspacios) {
        saltear_espacios(input, posActual);
    }

    // 2. Chequear si se llego al final de la entrada
    if (input[*posActual] == '\0') {
        actualizar_token(TOKEN_EOF, NULL, token);
        return;
    }

    // 3. Identificar palabras clave o identificadores
    if (isalpha(input[*posActual])) {
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

    // 4. Identificar listas en formato string
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

    // 5. Identificar operadores
    switch (input[*posActual]) {
    case '=':
        (*posActual)++;
        actualizar_token(TOKEN_ASIGNACION, NULL, token);
    case '<':
        (*posActual)++;
        actualizar_token(TOKEN_REPETICION_INI, NULL, token);
    case '>':
        (*posActual)++;
        actualizar_token(TOKEN_REPETICION_FIN, NULL, token);
    case ' ':
        actualizar_token(TOKEN_COMPOSICION, NULL, token);
        return;
    }

    // 6. Identificar puntuacion
    switch (input[*posActual]) {
    case '{':
        (*posActual)++;
        actualizar_token(TOKEN_LBRACE, NULL, token);
    case '}':
        (*posActual)++;
        actualizar_token(TOKEN_RBRACE, NULL, token);
    case ',':
        (*posActual)++;
        actualizar_token(TOKEN_COMA, NULL, token);
    case ';':
        (*posActual)++;
        actualizar_token(TOKEN_SEMICOLON, NULL, token);
        return;
    }

    // 7. Si no hay coindidencias es un error
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

DList *parsear_lista(char *lista) {
    int posActual = 0;
    int esValido = 1;
    DList *dlist = dlist_crear();
    Token *tok = malloc(sizeof(Token));

    obtener_siguiente_token_lista(lista, &posActual, tok);
    if (tok->type == TOKEN_NUM) {

        while (tok->type != TOKEN_EOF && esValido) {
            switch (tok->type) {
            case TOKEN_NUM:
                dlist_agregar_final(dlist, atoi(tok->value));
                free(tok->value);

                obtener_siguiente_token_lista(lista, &posActual, tok);
                if (tok->type != TOKEN_COMA || tok->type != TOKEN_EOF)
                    esValido = 0;
                break;

            case TOKEN_COMA:
                obtener_siguiente_token_lista(lista, &posActual, tok);
                if (tok->type != TOKEN_NUM)
                    esValido = 0;
                break;

            default:
                esValido = 0;
            }
        }
    }

    free(tok);

    if (!esValido) {
        dlist_destruir(dlist);
        return NULL;
    }

    return dlist;
}

void parsear_defl(char *input, int *posActual, TablaHash *tablaHash) {
    Token *tok = malloc(sizeof(Token));
    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type == TOKEN_IDENTIFICADOR) {
        char *identificador = tok->value;
        tok->value = NULL;
        liberar_token(tok);

        tok = obtener_siguiente_token(input, posActual, 1);
        if (tok->type == TOKEN_ASIGNACION) {
            liberar_token(tok);

            tok = obtener_siguiente_token(input, posActual, 1);
            if (tok->type == TOKEN_LIST_LITERAL) {
                char *listaLiteral = tok->value;
                tok->value = NULL;
                liberar_token(tok);

                tok = obtener_siguiente_token(input, posActual, 1);
                if (tok->type == TOKEN_SEMICOLON) {
                    liberar_token(tok);

                    obtener_siguiente_token(input, posActual, 1);
                    if (tok->type == TOKEN_EOF) {
                        liberar_token(tok);

                        DList *dlist = parsear_lista(listaLiteral);
                        insertar(identificador, dlist, tablaHash);

                        free(listaLiteral);
                    }
                }
            }
        }
    }
}

char *parsear_funcion(char *input, int *posActual, TablaHash *tablaHash) {
    saltear_espacios(input, posActual);
    int inicioFuncion = *posActual;
    Token *tok = obtener_siguiente_token(input, posActual, 1);

    int esValido = 1;
    if (tok->type != TOKEN_IDENTIFICADOR || tok->type != TOKEN_REPETICION_INI)
        return NULL;
    int cont = 0;
    while (esValido && tok->type != TOKEN_EOF) {
        switch (tok->type) {

        case TOKEN_IDENTIFICADOR:
            if (buscar(tok->value, tablaHash) != NULL) {
                liberar_token(tok);

                tok = obtener_siguiente_token(input, posActual, 0);
                if (tok->type != TOKEN_COMPOSICION || tok->type != TOKEN_REPETICION_FIN)
                    esValido = 0;
            } else
                perror("La subfuncion no se encuentra definida");
            break;

        case TOKEN_REPETICION_INI:
            cont++;
            liberar_token(tok);

            tok = obtener_siguiente_token(input, posActual, 0);
            if (tok->type != TOKEN_IDENTIFICADOR)
                esValido = 0;
            break;

        case TOKEN_REPETICION_FIN:
            cont--;
            liberar_token(tok);

            tok = obtener_siguiente_token(input, posActual, 0);
            if (cont < 0 || tok->type != TOKEN_COMPOSICION || tok->type != TOKEN_SEMICOLON)
                esValido = 0;
            break;

        case TOKEN_COMPOSICION:
            liberar_token(tok);

            tok = obtener_siguiente_token(input, posActual, 0);
            if (tok->type != TOKEN_IDENTIFICADOR || tok->type != TOKEN_REPETICION_INI)
                esValido = 0;
            break;

        case TOKEN_SEMICOLON:
            liberar_token(tok);

            tok = obtener_siguiente_token(input, posActual, 0);
            if (tok->type != TOKEN_EOF)
                esValido = 0;
            break;

        default:
            esValido = 0;
        }
    }
    liberar_token(tok);

    int finalFuncion = (*posActual) - 1;

    return esValido ? copiar_substring(input, inicioFuncion, finalFuncion) : NULL;
}

void parsear_deff(char *input, int *posActual, TablaHash *tablaHash) {
    char *funcion;
    Token *tok = obtener_siguiente_token(input, posActual, 1);
    char *identificador;
    if (tok->type == TOKEN_IDENTIFICADOR) {
        identificador = tok->value;
        tok->value = NULL;
        liberar_token(tok);

        tok = obtener_siguiente_token(input, posActual, 1);
        if (tok->type == TOKEN_ASIGNACION) {
            liberar_token(tok);

            funcion = parsear_funcion(input, posActual, tablaHash);
            if (funcion != NULL) {
                insertar(identificador, funcion, tablaHash);
            }
        }
    }
}

void parsear_apply(char *input, int *posActual, TablaHash *tablaHashFunciones, TablaHash *tablaHashListas) {
    Token *tok = obtener_siguiente_token(input, posActual, 1);

    if (tok->type == TOKEN_IDENTIFICADOR) {
        char *funcion = buscar(tok->value, tablaHashFunciones);
        liberar_token(tok);

        if (funcion) {
            tok = obtener_siguiente_token(input, posActual, 1);

            if (tok->type == TOKEN_IDENTIFICADOR) {
                DList *lista = buscar(tok->value, tablaHashListas);
                liberar_token(tok);

                if (lista) {
                    tok = obtener_siguiente_token(input, posActual, 1);

                    if (tok->type == TOKEN_SEMICOLON)
                }
                liberar_token(tok);
            }
            liberar_token(tok);
        }
        liberar_token(tok);
    }
    liberar_token(tok);
}

void parsear_expresion(char *input, TablaHash *tablaHash) {
    int posActual = 0;

    Token *tok = obtener_siguiente_token(input, &posActual, 1);
    switch (tok->type) {
    case TOKEN_DEFL:
        parsear_defl(input, &posActual, tablaHash);
        break;
    case TOKEN_DEFF:
        parsear_deff(input, &posActual);
        break;
    case TOKEN_APPLY:
        parsear_apply(input, &posActual);
        break;
    case TOKEN_SEARCH:
        parsear_search(input, &posActual);
        break;
    default:
        perror("Tipo de sentencia invalida");
        break;
    }

    liberar_token(tok);
}
