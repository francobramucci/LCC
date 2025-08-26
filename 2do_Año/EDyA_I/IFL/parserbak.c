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

void imprimir_lista(DList *lista) {
    if (lista != NULL) {
        printf("La lista es: ");
        for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
            printf("%d ", temp->dato);
        }
    }
}

typedef DList *Pila;

Pila pila_crear() {
    return dlist_crear();
}

void pila_push(int dato, Pila p) {
    dlist_agregar_inicio(p, dato);
}

void pila_pop(Pila p) {
    dlist_eliminar_inicio(p);
}

int pila_top(Pila p) {
    return p->primero->dato;
}

void pila_destruir(Pila p) {
    dlist_destruir(p);
}

FLista *flista_crear(int tamBuffer) {
    FLista *funcion = malloc(sizeof(FLista));
    funcion->def = malloc(sizeof(char *) * tamBuffer);
    funcion->largo = 0;

    return funcion;
}

void flista_destruir(FLista *funcion) {
    if (funcion) {
        for (int i = 0; i < funcion->largo; i++) {
            free(funcion->def[i]);
        }
        free(funcion->def);
        free(funcion);
    }
}

typedef struct {
        DList *fst;
        DList *snd;
} DLPair;

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
    char *identificador = NULL;
    char *listaLiteral = NULL;
    DList *dlist = NULL;
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

                        dlist = parsear_lista(listaLiteral);
                        if (dlist && !thash_buscar(identificador, tablaHash)) {
                            thash_insertar(identificador, dlist, tablaHash);
                            esValido = 1;
                        }
                    }
                }
            }
        }
    }

    if (!esValido) {
        free(identificador);
        dlist_destruir(dlist);
    }

    free(listaLiteral);
    liberar_token(tok);
}

FLista *parsear_funcion(char *input, int *posActual, THash *tablaHash) {
    FLista *funcion = flista_crear(1000);
    int esValido = 1;
    int cont = 0;

    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_REPETICION_INI) {
        flista_destruir(funcion);
        liberar_token(tok);
        return NULL;
    }

    while (esValido && tok->type != TOKEN_EOF) {
        switch (tok->type) {

        case TOKEN_IDENTIFICADOR:
            if (thash_buscar(tok->value, tablaHash)) {
                funcion->def[funcion->largo] = tok->value;
                funcion->largo++;
                tok->value = NULL;
                obtener_siguiente_token(input, posActual, 0, tok);
                if (tok->type != TOKEN_COMPOSICION && tok->type != TOKEN_REPETICION_FIN &&
                    tok->type != TOKEN_SEMICOLON) {
                    esValido = 0;
                }
            } else {
                esValido = 0;
                perror("La subfuncion no se encuentra definida");
            }
            break;

        case TOKEN_REPETICION_INI:
            funcion->def[funcion->largo] = strdup("<");
            funcion->largo++;
            cont++;

            obtener_siguiente_token(input, posActual, 0, tok);
            if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_REPETICION_INI)
                esValido = 0;
            break;

        case TOKEN_REPETICION_FIN:
            funcion->def[funcion->largo] = strdup(">");
            funcion->largo++;
            cont--;

            obtener_siguiente_token(input, posActual, 0, tok);
            if (cont < 0 ||
                tok->type != TOKEN_COMPOSICION && tok->type != TOKEN_SEMICOLON && tok->type != TOKEN_REPETICION_FIN)
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

    if (!esValido) {
        flista_destruir(funcion);
        return NULL;
    }

    return funcion;
}

void parsear_deff(char *input, int *posActual, THash *tablaHashFunciones) {
    int esValido = 0;
    FLista *funcion = NULL;
    char *identificador = NULL;
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
        free(funcion);
    }
    liberar_token(tok);
}

void Od(DList *lista) {
    dlist_agregar_final(lista, 0);
}

void Oi(DList *lista) {
    dlist_agregar_inicio(lista, 0);
}

void Sd(DList *lista) {
    lista->ultimo->dato++;
}

void Si(DList *lista) {
    lista->primero->dato++;
}

void Dd(DList *lista) {
    dlist_eliminar_final(lista);
}

void Di(DList *lista) {
    dlist_eliminar_inicio(lista);
}

void aplicacion_singular(char *funcion, DList *lista, THash *tablaHashFunciones) {
    if (!strcmp(funcion, "Oi"))
        Oi(lista);
    else if (!strcmp(funcion, "Od"))
        Od(lista);
    else if (!strcmp(funcion, "Si"))
        Si(lista);
    else if (!strcmp(funcion, "Sd"))
        Sd(lista);
    else if (!strcmp(funcion, "Di"))
        Di(lista);
    else if (!strcmp(funcion, "Dd"))
        Dd(lista);
    else
        apply(thash_buscar(funcion, tablaHashFunciones), lista, tablaHashFunciones);
}

void apply(FLista *funcion, DList *lista, THash *tablaHashFunciones) {
    Pila p = pila_crear();
    for (int i = 0; i < funcion->largo; i++) {
        if (funcion->def[i][0] == '<') {
            if (lista->primero->dato != lista->ultimo->dato) {
                pila_push(i, p);
            } else {
                int cont = 1;
                while (cont != 0) {
                    i++;
                    if (funcion->def[i][0] == '<')
                        cont++;
                    if (funcion->def[i][0] == '>')
                        cont--;
                }
            }
        } else if (funcion->def[i][0] == '>') {
            if (lista->primero->dato != lista->ultimo->dato)
                i = pila_top(p);
            else
                pila_pop(p);
        } else
            aplicacion_singular(funcion->def[i], lista, tablaHashFunciones);
    }
    pila_destruir(p);
}

void parsear_apply(char *input, int *posActual, THash *tablaHashListas, THash *tablaHashFunciones) {
    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type == TOKEN_IDENTIFICADOR) {

        FLista *funcion = thash_buscar(tok->value, tablaHashFunciones);
        if (funcion) {

            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type == TOKEN_IDENTIFICADOR) {

                DList *lista = thash_buscar(tok->value, tablaHashListas);
                if (lista) {

                    obtener_siguiente_token(input, posActual, 1, tok);
                    if (tok->type == TOKEN_SEMICOLON) {

                        obtener_siguiente_token(input, posActual, 1, tok);
                        if (tok->type == TOKEN_EOF) {
                            DList *copia = dlist_copiar(lista);
                            apply(funcion, copia, tablaHashFunciones);
                            imprimir_lista(copia);
                            dlist_destruir(copia);
                        }
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
    DLPair DLpair[1000];
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
    // THash *tabla = thash_crear(100, (FuncionDestructora)flista_destruir);
    // char *id = "F";
    // char *input = strdup("F = <Dd> Od Sd");
    // int posActual = 0;
    // char *key1 = strdup("Dd");
    // FLista *value1 = flista_crear(10);
    // char *key2 = strdup("Od");
    // FLista *value2 = flista_crear(10);
    // char *key3 = strdup("Sd");
    // FLista *value3 = flista_crear(10);
    //
    // thash_insertar(key1, value1, tabla);
    // thash_insertar(key2, value2, tabla);
    // thash_insertar(key3, value3, tabla);
    //
    // parsear_deff(input, &posActual, tabla);
    // FLista *res = thash_buscar(id, tabla);
    //
    // if (res != NULL) {
    //     for (int i = 0; i < res->largo; i++) {
    //         printf("%s ", res->def[i]);
    //     }
    // }
    //
    // free(input);
    //
    // thash_destruir(tabla);

    // char *l = "";
    // DList *lista = parsear_lista(l);
    // if (lista != NULL) {
    //     printf("La lista es: ");
    //     for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
    //         printf("%d ", temp->dato);
    //     }
    // }
    // dlist_destruir(lista);

    // THash *tabla = thash_crear(100, (FuncionDestructora)dlist_destruir);
    // char *a = "L1 = [1];";
    // char *b = "L1 = [2];";
    // char *id = "L1";
    // int posActual = 0;
    //
    // parsear_defl(a, &posActual, tabla);
    // posActual = 0;
    // parsear_defl(b, &posActual, tabla);
    //
    // DList *lista = thash_buscar(id, tabla);
    // if (lista != NULL) {
    //     printf("La lista es: ");
    //     for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
    //         printf("%d ", temp->dato);
    //     }
    // }
    // thash_destruir(tabla);
    // dlist_destruir(lista);
    //
    // srand(1);
    // THash *hTable = thash_crear(1217, (FuncionDestructora)dlist_destruir);
    // char **stringArray = malloc(1300 * sizeof(char *));
    //
    // for (int i = 0; i < 1300; i++) {
    //     stringArray[i] = malloc(100 * sizeof(char));
    // }
    //
    // for (int i = 0; i < 1300; i++) {
    //     sprintf(stringArray[i], "L%d = [%d, %d, %d, %d, %d, %d];", i, rand() % 100, rand() % 100, rand() % 100,
    //             rand() % 100, rand() % 100, rand() % 100);
    //     int posActual = 0;
    //     parsear_defl(stringArray[i], &posActual, hTable);
    // }
    // char *id = "L1190";
    // DList *lista = thash_buscar(id, hTable);
    // if (lista != NULL) {
    //     printf("La lista es: ");
    //     for (DNodo *temp = lista->primero; temp != NULL; temp = temp->sig) {
    //         printf("%d ", temp->dato);
    //     }
    // }
    //
    // thash_destruir(hTable);
    // for (int i = 0; i < 1300; i++) {
    //     free(stringArray[i]);
    // }
    // free(stringArray);
    //

    THash *tablaF = thash_crear(100, (FuncionDestructora)flista_destruir);
    THash *tablaL = thash_crear(100, (FuncionDestructora)dlist_destruir);

    char *input1 = "defl L1 = [10,2,3];";
    char *input2 = "deff Mi = Oi <Si> Dd;";
    char *input3 = "apply Mi L1;";

    char *key1 = strdup("Oi");
    FLista *value1 = flista_crear(10);
    char *key2 = strdup("Od");
    FLista *value2 = flista_crear(10);
    char *key3 = strdup("Si");
    FLista *value3 = flista_crear(10);
    char *key4 = strdup("Sd");
    FLista *value4 = flista_crear(10);
    char *key5 = strdup("Di");
    FLista *value5 = flista_crear(10);
    char *key6 = strdup("Dd");
    FLista *value6 = flista_crear(10);

    thash_insertar(key1, value1, tablaF);
    thash_insertar(key2, value2, tablaF);
    thash_insertar(key3, value3, tablaF);
    thash_insertar(key4, value4, tablaF);
    thash_insertar(key5, value5, tablaF);
    thash_insertar(key6, value6, tablaF);

    parsear_expresion(input1, tablaL, tablaF);
    parsear_expresion(input2, tablaL, tablaF);
    parsear_expresion(input3, tablaL, tablaF);

    thash_destruir(tablaL);
    thash_destruir(tablaF);
    return 0;
}
