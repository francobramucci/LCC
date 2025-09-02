#include "parser.h"
#include "dlist.h"

void imprimir_errores(int errorCode) {
    switch (errorCode) {

    case ERROR_SINTAXIS_SENTENCIA:
        printf("Error: sintaxis de sentencia invalido");
        break;

    case ERROR_SINTAXIS_LISTA:
        printf("Error: sintaxis de lista invalido");
        break;

    case ERROR_LISTA_NO_DEFINIDA:
        printf("Error: lista no definida");
        break;

    case ERROR_LISTA_YA_DEFINIDA:
        printf("Error: lista ya definida");
        break;

    case ERROR_SUBFUNCION_NO_DEFINIDA:
        printf("Error: subfuncion no definida");
        break;

    case ERROR_SINTAXIS_FUNCION:
        printf("Error: sintaxis de funcion invalida");
        break;

    case ERROR_FUNCION_NO_DEFINIDA:
        printf("Error: funcion no definida");
        break;

    case ERROR_FUNCION_YA_DEFINIDA:
        printf("Error: funcion ya definida");
        break;
    default:
        printf("Error desconocido");
    }
}

void saltear_espacios(char *input, int *posActual) {
    while (input[*posActual] != '\0' && isspace(input[*posActual])) {
        (*posActual)++;
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

DList *parsear_lista(char *lista) {
    int posActual = 0;
    int esValido = 1;
    // DList *dlist = dlist_crear((FuncionCopiadora)copiar_puntero_entero, (FuncionDestructora)destruir_puntero_entero);
    DList *dlist = dlist_crear();
    Token *tok = crear_token();

    obtener_siguiente_token_lista(lista, &posActual, tok);
    if (tok->type == TOKEN_NUM || tok->type == TOKEN_EOF) {

        while (tok->type != TOKEN_EOF && esValido) {
            switch (tok->type) {

            case TOKEN_NUM: {
                int num = atoi(tok->value);
                // dlist_agregar_final(dlist, &num);
                dlist_agregar_final(dlist, num);

                obtener_siguiente_token_lista(lista, &posActual, tok);
                if (tok->type != TOKEN_COMA && tok->type != TOKEN_EOF)
                    esValido = 0;
                break;
            }
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
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
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

                            printf("%s <-- ", identificador);
                            // dlist_imprimir(dlist, (FuncionVisitante)imprimir_puntero_entero);
                            dlist_imprimir(dlist);
                        } else {
                            if (!dlist)
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
        dlist_destruir(dlist);
    }

    free(listaLiteral);
    liberar_token(tok);
}

FLista *parsear_funcion(char *input, int *posActual, THash *tablaHash, int *errorCode) {
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

void parsear_deff(char *input, int *posActual, THash *tablaHashFunciones) {
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
    int esValido = 0;
    FLista *funcion = NULL;
    char *identificador = NULL;
    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type == TOKEN_IDENTIFICADOR) {
        identificador = tok->value;
        tok->value = NULL;
        if (!thash_buscar(identificador, tablaHashFunciones)) {
            obtener_siguiente_token(input, posActual, 1, tok);
            if (tok->type == TOKEN_ASIGNACION) {

                funcion = parsear_funcion(input, posActual, tablaHashFunciones, &errorCode);
                if (funcion != NULL) {
                    thash_insertar(identificador, funcion, tablaHashFunciones);
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
    }
    liberar_token(tok);
}

void parsear_apply(char *input, int *posActual, THash *tablaHashListas, THash *tablaHashFunciones) {
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
    int esValido = 0;
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
                            esValido = 1;
                            DList *copia = dlist_copiar(lista);
                            apply(funcion, copia, tablaHashFunciones, 1);
                            dlist_destruir(copia);
                        }
                    }
                } else
                    errorCode = ERROR_LISTA_NO_DEFINIDA;
            }

            if (tok->type == TOKEN_LIST_LITERAL) {
                DList *lista = parsear_lista(tok->value);

                obtener_siguiente_token(input, posActual, 1, tok);
                if (tok->type == TOKEN_SEMICOLON) {

                    obtener_siguiente_token(input, posActual, 1, tok);
                    if (tok->type == TOKEN_EOF) {
                        esValido = 1;
                        apply(funcion, lista, tablaHashFunciones, 1);
                    }
                }
                dlist_destruir(lista);
            }
        } else {
            errorCode = ERROR_FUNCION_NO_DEFINIDA;
        }
    }
    if (!esValido)
        imprimir_errores(errorCode);

    liberar_token(tok);
}

void parsear_search(char *input, int *posActual, THash *tablaHashListas, THash *tablaFunciones) {
    int errorCode = ERROR_SINTAXIS_SENTENCIA;
    int esValido = 1;
    int esPrimerIdentificador = 1;
    int corcheteDerLeido = 0;
    // DList *listaDePares = dlist_crear(retornar_puntero, funcion_vacia);
    Vector *paresDeListas = vector_crear(50, retornar_puntero, funcion_vacia);

    Token *tok = crear_token();

    obtener_siguiente_token(input, posActual, 1, tok);
    if (tok->type != TOKEN_LBRACE) {
        liberar_token(tok);
        return;
    }

    while (tok->type != TOKEN_EOF && esValido) {
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
                    if (tok->type != TOKEN_COMA)
                        esValido = 0;
                } else {
                    if (tok->type != TOKEN_SEMICOLON && tok->type != TOKEN_RBRACE)
                        esValido = 0;
                }
                esPrimerIdentificador = !esPrimerIdentificador;
                // dlist_agregar_final(listaDePares, lista);
                vector_insertar(paresDeListas, lista);
            } else {
                esValido = 0;
                errorCode = ERROR_LISTA_NO_DEFINIDA;
            }
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
        // search(listaDePares, tablaFunciones);
        search(paresDeListas, tablaFunciones);
    else
        imprimir_errores(errorCode);

    vector_destruir(paresDeListas);
    // dlist_destruir(listaDePares);
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
        parsear_search(input, &posActual, tablaHashListas, tablaHashFunciones);
        break;
    default:
        printf("Tipo de sentencia invalida");
        break;
    }

    liberar_token(tok);
}
