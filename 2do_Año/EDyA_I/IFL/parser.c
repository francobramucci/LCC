#include "parser.h"
#include "lista.h"
#include "thash.h"
#include "token.h"
#include "utils.h"
#include <stdio.h>

/**
 * Verifica y procesa la definición de una lista en el input a partir de la posición dada.
 * Formato esperado: identificador = [a_0, a_1, ..., a_n];
 * - Cada a_i debe ser un número natural.
 * - Se permiten espacios arbitrarios entre símbolos.
 * Si la definición es válida, almacena la lista en la tabla de listas usando el identificador como clave.
 * En caso contrario, imprime un error.
 */
static void parsear_defl(char *input, int *posActual, THash *tablaListas);

/**
 * Parsea un string con el formato de lista: [a_0, a_1, ..., a_n]
 * - Cada a_i debe ser un número natural.
 * - Se permiten espacios arbitrarios entre números y símbolos.
 * Retorna la lista como un Lista* o NULL en caso de error.
 */
static Lista *parsear_lista(char *lista);

/**
 * Verifica y procesa la definición de una función de lista en el input a partir de la posición dada.
 * Formato esperado: identificador = funcion_de_lista;
 * Si es válida, la función se almacena en la tabla de funciones usando el identificador como clave.
 * En caso contrario, imprime un error.
 */
static void parsear_deff(char *input, int *posActual, THash *tablaFunciones);

/**
 * Parsea y valida una función de lista desde el input.
 * - Comprueba que cada subfunción esté definida.
 * - Garantiza que los identificadores estén separados por un solo espacio.
 * - Verifica que las repeticiones tengan inicio y fin, y no estén vacías.
 * Retorna un FLista* o NULL en caso de error. Actualiza errorCode en caso de fallo.
 */
static FLista *parsear_funcion(char *input, int *posActual, THash *tablaHash, int *errorCode);

/**
 * Parsea y ejecuta una aplicación de función sobre una lista.
 * Formato esperado: identificador_funcion identificador_lista | lista_literal
 * Si es válido, aplica la función a la lista. En caso contrario, imprime un error.
 */
static void parsear_apply(char *input, int *posActual, THash *tablaListas, THash *tablaFunciones);

/**
 * Parsea y valida una lista de pares de listas en el formato:
 *   {L11, L12; L21, L22; ... Ln1, Ln2};
 * donde Lij pueden ser tanto identificadores de listas como listas literales
 * Si es válido, aplica search en dicha lista de pares.
 */
static void parsear_search(char *input, int *posActual, THash *tablaListas, THash *tablaFunciones);

/**
 * Imprime el mensaje de error correspondiente a un código de error.
 */
static void imprimir_errores(int errorCode);

void parsear_expresion(char *input, THash *tablaListas, THash *tablaFunciones) {
    int posActual = 0;
    Token *tok = crear_token();

    obtener_siguiente_token(input, &posActual, 1, tok);
    switch (tok->type) {
    case TOKEN_DEFL:
        parsear_defl(input, &posActual, tablaListas);
        break;
    case TOKEN_DEFF:
        parsear_deff(input, &posActual, tablaFunciones);
        break;
    case TOKEN_APPLY:
        parsear_apply(input, &posActual, tablaListas, tablaFunciones);
        break;
    case TOKEN_SEARCH:
        parsear_search(input, &posActual, tablaListas, tablaFunciones);
        break;
    default:
        printf("Tipo de sentencia invalida");
        break;
    }

    liberar_token(tok);
}

static void parsear_defl(char *input, int *posActual, THash *tablaListas) {
    int esValido = 0;
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
    char *identificador = NULL;
    char *listaLiteral = NULL;
    Lista *lista = NULL;
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

                        lista = parsear_lista(listaLiteral);
                        if (lista && !thash_buscar(identificador, tablaListas)) {

                            thash_insertar(identificador, lista, tablaListas);
                            esValido = 1;

                            printf("%s <-- ", identificador);
                            lista_imprimir(lista);
                        } else {
                            if (!lista)
                                errorCode = ERROR_SINTAXIS_LISTA;
                            else
                                errorCode = ERROR_LISTA_YA_DEFINIDA;
                        }
                    }
                }
            }
        }
    }

    if (!esValido) {
        imprimir_errores(errorCode);
        free(identificador);
        lista_destruir(lista);
    }

    free(listaLiteral);
    liberar_token(tok);
}

static Lista *parsear_lista(char *listaLiteral) {
    int posActual = 0;
    int esValido = 1;
    Lista *lista = lista_crear();
    Token *tok = crear_token();

    obtener_siguiente_token_lista(listaLiteral, &posActual, tok);
    if (tok->type == TOKEN_NUM || tok->type == TOKEN_EOF) {

        while (tok->type != TOKEN_EOF && esValido) {
            switch (tok->type) {

            case TOKEN_NUM: {
                int num = atoi(tok->value);
                lista_agregar_final(lista, num);

                obtener_siguiente_token_lista(listaLiteral, &posActual, tok);
                if (tok->type != TOKEN_COMA && tok->type != TOKEN_EOF)
                    esValido = 0;
                break;
            }
            case TOKEN_COMA:
                obtener_siguiente_token_lista(listaLiteral, &posActual, tok);
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
        lista_destruir(lista);
        return NULL;
    }

    return lista;
}

static void parsear_deff(char *input, int *posActual, THash *tablaFunciones) {
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
    int esValido = 0;
    FLista *funcion = NULL;
    char *identificador = NULL;
    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type == TOKEN_IDENTIFICADOR) {
        identificador = tok->value;
        tok->value = NULL;
        if (!thash_buscar(identificador, tablaFunciones)) {
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type == TOKEN_ASIGNACION) {

                funcion = parsear_funcion(input, posActual, tablaFunciones, &errorCode);
                if (funcion != NULL) {
                    thash_insertar(identificador, funcion, tablaFunciones);
                    esValido = 1;
                }
            }
        } else
            errorCode = ERROR_FUNCION_YA_DEFINIDA;
    }

    if (!esValido) {
        imprimir_errores(errorCode);
        free(identificador);
        flista_destruir(funcion);
    } else {
        printf("%s <-- ", identificador);
        flista_imprimir(funcion);
    }
    liberar_token(tok);
}

static FLista *parsear_funcion(char *input, int *posActual, THash *tablaHash, int *errorCode) {
    *errorCode = ERROR_SINTAXIS_FUNCION;
    FLista *funcion = flista_crear(50, retornar_puntero, liberar_puntero);
    int esValido = 1;
    int cont = 0;

    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_REPETICION_INI)
        esValido = 0;

    while (esValido && tok->type != TOKEN_EOF) {
        switch (tok->type) {

        case TOKEN_IDENTIFICADOR:
            if (thash_buscar(tok->value, tablaHash)) {
                flista_insertar(funcion, tok->value);
                tok->value = NULL;
                obtener_siguiente_token(input, posActual, 0, tok);
                if (tok->type != TOKEN_COMPOSICION && tok->type != TOKEN_REPETICION_FIN &&
                    tok->type != TOKEN_SEMICOLON) {
                    esValido = 0;
                }
            } else {
                esValido = 0;
                *errorCode = ERROR_SUBFUNCION_NO_DEFINIDA;
            }
            break;

        case TOKEN_REPETICION_INI:
            flista_insertar(funcion, copiar_string("<"));
            cont++;

            obtener_siguiente_token(input, posActual, 0, tok);
            if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_REPETICION_INI)
                esValido = 0;
            break;

        case TOKEN_REPETICION_FIN:
            flista_insertar(funcion, copiar_string(">"));
            cont--;

            obtener_siguiente_token(input, posActual, 0, tok);
            if (cont < 0 ||
                (tok->type != TOKEN_COMPOSICION && tok->type != TOKEN_SEMICOLON && tok->type != TOKEN_REPETICION_FIN))
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

static void parsear_apply(char *input, int *posActual, THash *tablaListas, THash *tablaFunciones) {
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
    int esValido = 0;
    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type == TOKEN_IDENTIFICADOR) {

        FLista *funcion = thash_buscar(tok->value, tablaFunciones);
        if (funcion) {

            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type == TOKEN_IDENTIFICADOR) {

                Lista *lista = thash_buscar(tok->value, tablaListas);
                if (lista) {

                    obtener_siguiente_token(input, posActual, 1, tok);
                    if (tok->type == TOKEN_SEMICOLON) {

                        obtener_siguiente_token(input, posActual, 1, tok);
                        if (tok->type == TOKEN_EOF) {
                            esValido = 1;
                            Lista *copia = lista_copiar(lista);
                            apply(funcion, copia, tablaFunciones, 1);
                            lista_destruir(copia);
                        }
                    }
                } else
                    errorCode = ERROR_LISTA_NO_DEFINIDA;
            }

            if (tok->type == TOKEN_LIST_LITERAL) {
                Lista *lista = parsear_lista(tok->value);

                obtener_siguiente_token(input, posActual, 1, tok);
                if (tok->type == TOKEN_SEMICOLON) {

                    obtener_siguiente_token(input, posActual, 1, tok);
                    if (tok->type == TOKEN_EOF) {
                        esValido = 1;
                        apply(funcion, lista, tablaFunciones, 1);
                    }
                }
                lista_destruir(lista);
            }
        } else {
            errorCode = ERROR_FUNCION_NO_DEFINIDA;
        }
    }
    if (!esValido)
        imprimir_errores(errorCode);

    liberar_token(tok);
}

static void parsear_search(char *input, int *posActual, THash *tablaListas, THash *tablaFunciones) {
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
    int esValido = 1;
    int esPrimeraLista = 1;
    int corcheteDerLeido = 0;
    Vector *paresDeListas = vector_crear(50, (FuncionCopiadora)lista_copiar, (FuncionDestructora)lista_destruir);

    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type != TOKEN_LBRACE)
        esValido = 0;

    while (tok->type != TOKEN_EOF && esValido) {
        switch (tok->type) {

        case TOKEN_LBRACE:
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_LIST_LITERAL)
                esValido = 0;
            break;

        case TOKEN_IDENTIFICADOR: {
            Lista *lista = thash_buscar(tok->value, tablaListas);
            if (lista) {
                obtener_siguiente_token(input, posActual, 1, tok);
                if (esPrimeraLista) {
                    if (tok->type != TOKEN_COMA)
                        esValido = 0;
                } else {
                    if (tok->type != TOKEN_SEMICOLON && tok->type != TOKEN_RBRACE)
                        esValido = 0;
                }
                esPrimeraLista = !esPrimeraLista;
                vector_insertar(paresDeListas, lista);
            } else {
                esValido = 0;
                errorCode = ERROR_LISTA_NO_DEFINIDA;
            }
            break;
        }

        case TOKEN_LIST_LITERAL: {
            Lista *lista = parsear_lista(tok->value);
            if (lista) {
                obtener_siguiente_token(input, posActual, 1, tok);
                if (esPrimeraLista) {
                    if (tok->type != TOKEN_COMA)
                        esValido = 0;
                } else {
                    if (tok->type != TOKEN_SEMICOLON && tok->type != TOKEN_RBRACE)
                        esValido = 0;
                }
                esPrimeraLista = !esPrimeraLista;
                vector_insertar(paresDeListas, lista);
            } else {
                esValido = 0;
                errorCode = ERROR_SINTAXIS_LISTA;
            }
            lista_destruir(lista);
            break;
        }

        case TOKEN_COMA:
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_LIST_LITERAL)
                esValido = 0;
            break;

        case TOKEN_SEMICOLON:
            obtener_siguiente_token(input, posActual, 1, tok);
            if (corcheteDerLeido) {
                if (tok->type != TOKEN_EOF)
                    esValido = 0;
            } else {
                if (tok->type != TOKEN_IDENTIFICADOR && tok->type != TOKEN_LIST_LITERAL)
                    esValido = 0;
            }
            break;

        case TOKEN_RBRACE:
            corcheteDerLeido = 1;
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type != TOKEN_SEMICOLON)
                esValido = 0;
            break;

        default:
            esValido = 0;
        }
    }

    liberar_token(tok);

    if (esValido)
        search(paresDeListas, tablaFunciones);
    else
        imprimir_errores(errorCode);

    vector_destruir(paresDeListas);
}

static void imprimir_errores(int errorCode) {
    switch (errorCode) {

    case ERROR_SINTAXIS_SENTENCIA:
        printf("Error: sintaxis de sentencia invalida.");
        break;

    case ERROR_SINTAXIS_LISTA:
        printf("Error: sintaxis de lista invalida.");
        break;

    case ERROR_LISTA_NO_DEFINIDA:
        printf("Error: lista no definida.");
        break;

    case ERROR_LISTA_YA_DEFINIDA:
        printf("Error: lista ya definida.");
        break;

    case ERROR_SUBFUNCION_NO_DEFINIDA:
        printf("Error: subfuncion no definida.");
        break;

    case ERROR_SINTAXIS_FUNCION:
        printf("Error: sintaxis de funcion invalida.");
        break;

    case ERROR_FUNCION_NO_DEFINIDA:
        printf("Error: funcion no definida.");
        break;

    case ERROR_FUNCION_YA_DEFINIDA:
        printf("Error: funcion ya definida.");
        break;
    default:
        printf("Error desconocido.");
    }
}
