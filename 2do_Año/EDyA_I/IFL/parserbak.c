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
// - hacer apply
// - hacer search
// - agregar mensajes de error
// - eliminar posActual como parametro de las funciones de parseo
// - hacer enum con tipos de error
typedef struct {
        DList *fst;
        DList *snd;
} DListPair;

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
    if (ini < 0 || fin < ini)
        return NULL;

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

Token *crear_token() {
    Token *token = malloc(sizeof(Token));
    token->type = 0;
    token->value = NULL;

    return token;
}

void actualizar_token(TokenType type, char *value, Token *token) {
    free(token->value);
    token->type = type;
    token->value = value;
    fprintf(stderr, "%d\n", token->type);
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

    // 6. Identificar puntuacion
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
    Token *tok = crear_token();

    obtener_siguiente_token_lista(lista, &posActual, tok);
    if (tok->type == TOKEN_NUM || tok->type == TOKEN_EOF) {

        while (tok->type != TOKEN_EOF && esValido) {
            switch (tok->type) {
            case TOKEN_NUM:
                dlist_agregar_final(dlist, atoi(tok->value));

                obtener_siguiente_token_lista(lista, &posActual, tok);
                if (tok->type != TOKEN_COMA && tok->type != TOKEN_EOF)
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

    liberar_token(tok);

    if (!esValido) {
        dlist_destruir(dlist);
        return NULL;
    }

    return dlist;
}

void parsear_defl(char *input, int *posActual, THash *tablaHash) {
    int esValido = 0;
    char *identificador;
    char *listaLiteral;
    Token *tok = crear_token();
    obtener_siguiente_token(input, posActual, 1, tok);

    if (tok->type == TOKEN_IDENTIFICADOR) {
        identificador = tok->value;
        tok->value = NULL;

        obtener_siguiente_token(input, posActual, 1, tok);
        if (tok->type == TOKEN_ASIGNACION) {

            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type == TOKEN_LIST_LITERAL) {
                listaLiteral = tok->value;
                tok->value = NULL;

                obtener_siguiente_token(input, posActual, 1, tok);
                if (tok->type == TOKEN_SEMICOLON) {

                    obtener_siguiente_token(input, posActual, 1, tok);
                    if (tok->type == TOKEN_EOF) {

                        DList *dlist = parsear_lista(listaLiteral);
                        if (dlist) {
                            thash_insertar(identificador, dlist, tablaHash);
                            esValido = 1;
                        }
                    }
                }
            }
        }
    }

    if (!esValido)
        free(identificador);

    free(listaLiteral);
    liberar_token(tok);
}

char *parsear_funcion(char *input, int *posActual, THash *tablaHash) {
    saltear_espacios(input, posActual);
    int inicioFuncion = *posActual;
    Token *tok = malloc(sizeof(Token *));
    int esValido = 1;

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_REPETICION_INI) {
        liberar_token(tok);
        return NULL;
    }

    int cont = 0;
    while (esValido && tok->type != TOKEN_EOF) {
        switch (tok->type) {

        case TOKEN_IDENTIFICADOR:
            if (thash_buscar(tok->value, tablaHash)) {
                obtener_siguiente_token(input, posActual, 0, tok);
                if (tok->type != TOKEN_COMPOSICION && tok->type != TOKEN_REPETICION_FIN)
                    esValido = 0;
            } else
                perror("La subfuncion no se encuentra definida");
            break;

        case TOKEN_REPETICION_INI:
            cont++;

            obtener_siguiente_token(input, posActual, 0, tok);
            if (tok->type != TOKEN_IDENTIFICADOR)
                esValido = 0;
            break;

        case TOKEN_REPETICION_FIN:
            cont--;

            obtener_siguiente_token(input, posActual, 0, tok);
            if (cont < 0 || (tok->type != TOKEN_COMPOSICION && tok->type != TOKEN_SEMICOLON))
                esValido = 0;
            break;

        case TOKEN_COMPOSICION:
            obtener_siguiente_token(input, posActual, 0, tok);
            if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_REPETICION_INI)
                esValido = 0;
            break;

        case TOKEN_SEMICOLON:
            obtener_siguiente_token(input, posActual, 0, tok);
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

void parsear_deff(char *input, int *posActual, THash *tablaHashFunciones) {
    int esValido = 0;
    char *funcion;
    char *identificador;
    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type == TOKEN_IDENTIFICADOR) {
        identificador = tok->value;
        tok->value = NULL;

        obtener_siguiente_token(input, posActual, 1, tok);
        if (tok->type == TOKEN_ASIGNACION) {

            funcion = parsear_funcion(input, posActual, tablaHashFunciones);
            if (funcion != NULL) {
                thash_insertar(identificador, funcion, tablaHashFunciones);
                esValido = 1;
            }
        }
    }

    if (!esValido) {
        free(identificador);
    }
    liberar_token(tok);
}

void apply(char *funcion, DList *lista) {
    printf("Sentencia apply es valida");
}

void parsear_apply(char *input, int *posActual, THash *tablaHashListas, THash *tablaHashFunciones) {
    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type == TOKEN_IDENTIFICADOR) {

        char *funcion = thash_buscar(tok->value, tablaHashFunciones);
        if (funcion) {

            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type == TOKEN_IDENTIFICADOR) {

                DList *lista = thash_buscar(tok->value, tablaHashListas);
                if (lista) {

                    obtener_siguiente_token(input, posActual, 1, tok);
                    if (tok->type == TOKEN_SEMICOLON) {

                        obtener_siguiente_token(input, posActual, 1, tok);
                        if (tok->type == TOKEN_EOF)
                            apply(funcion, lista);
                    }
                }
            }
        }
    }

    liberar_token(tok);
}

void parsear_search(char *input, int *posActual, THash *tablaHashListas) {
    int esValido = 1;
    int esPrimerIdentificador = 1;
    int corcheteDerLeido = 0;
    DListPair DLpair[1000];
    int indiceDLPair = 0;

    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type != TOKEN_LBRACE) {
        liberar_token(tok);
        return;
    }

    while (tok != TOKEN_EOF && esValido) {
        switch (tok->type) {

        case TOKEN_LBRACE:
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type != TOKEN_IDENTIFICADOR)
                esValido = 0;
            break;

        case TOKEN_IDENTIFICADOR: {
            DList *lista = thash_buscar(tok->value, tablaHashListas);
            if (lista) {
                obtener_siguiente_token(input, posActual, 1, tok);
                if (esPrimerIdentificador) {
                    DLpair[indiceDLPair].fst = lista;
                    if (tok->type != TOKEN_COMA)
                        esValido = 0;
                } else {
                    DLpair[indiceDLPair].snd = lista;
                    if (tok->type != TOKEN_SEMICOLON && tok->type != TOKEN_RBRACE)
                        esValido = 0;
                    indiceDLPair++;
                }
                esPrimerIdentificador = !esPrimerIdentificador;
            } else
                esValido = 0;
            break;
        }

        case TOKEN_COMA:
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type != TOKEN_IDENTIFICADOR)
                esValido = 0;
            break;

        case TOKEN_SEMICOLON:
            obtener_siguiente_token(input, posActual, 1, tok);
            if (corcheteDerLeido) {
                if (tok->type != TOKEN_EOF)
                    esValido = 0;
            } else {
                if (tok->type != TOKEN_IDENTIFICADOR)
                    esValido = 0;
            }
            break;

        case TOKEN_RBRACE:
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type != TOKEN_SEMICOLON)
                esValido = 0;
            break;

        default:
            esValido = 0;
        }
    }

    liberar_token(tok);

    // if (esValido)
    //     search(DLpair);
}

void parsear_expresion(char *input, THash *tablaHashListas, THash *tablaHashFunciones) {
    int posActual = 0;
    Token *tok = crear_token();

    obtener_siguiente_token(input, &posActual, 1, tok);
    switch (tok->type) {
    case TOKEN_DEFL:
        parsear_defl(input, &posActual, tablaHashListas);
        break;
    case TOKEN_DEFF:
        parsear_deff(input, &posActual, tablaHashFunciones);
        break;
    case TOKEN_APPLY:
        parsear_apply(input, &posActual, tablaHashListas, tablaHashFunciones);
        break;
    case TOKEN_SEARCH:
        parsear_search(input, &posActual, tablaHashListas);
        break;
    default:
        perror("Tipo de sentencia invalida");
        break;
    }

    liberar_token(tok);
}

int main() {
    char *l = "";
    DList *lista = parsear_lista(l);
    if (lista != NULL) {
        printf("La lista es: ");
        for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
            printf("%d ", temp->dato);
        }
    }

    //
    // THash *tabla = crear_tabla_hash(100);
    // char *a = "L1 = [1];";
    // char *b = "L1 = [2];";
    // char *id = "L1";
    // int posActual = 0;
    //
    // parsear_defl(a, &posActual, tabla);
    // posActual = 0;
    // parsear_defl(b, &posActual, tabla);
    //
    // DList *lista = buscar(id, tabla);
    // if (lista != NULL) {
    //     printf("La lista es: ");
    //     for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
    //         printf("%d ", temp->dato);
    //     }
    // }

    // srand(1);
    // THash *hTable = crear_tabla_hash(1217);
    // char stringArray[1200][100];
    // for (int i = 0; i < 1200; i++) {
    //     sprintf(stringArray[i], "L%d = [%d, %d, %d, %d, %d, %d];", i, rand() % 100, rand() % 100, rand() % 100,
    //             rand() % 100, rand() % 100, rand() % 100);
    //     int posActual = 0;
    //     parsear_defl(stringArray[i], &posActual, hTable);
    // }
    // char *id = "L1190";
    // DList *lista = buscar(id, hTable);
    // if (lista != NULL) {
    //     printf("La lista es: ");
    //     for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
    //         printf("%d ", temp->dato);
    //     }
    // }
}
