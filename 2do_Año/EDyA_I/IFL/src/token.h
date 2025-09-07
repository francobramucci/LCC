#ifndef __TOKEN_H__
#define __TOKEN_H__

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

/**
 * Crea un nuevo token en memoria y lo retorna.
 */
Token *crear_token();

/**
 * Libera la memoria asociada a un token previamente creado.
 * Libera cualquier string almacenado como valor.
 */
void liberar_token(Token *token);

/**
 * Función para tokenizar posibles inputs del intérprete de funciones de listas.
 * Extrae el siguiente token del input a partir de la posición indicada por posActual. Dicho token puede ser de
 * cualquier tipo perteneciente a TokenType. Si saltearEspacios es distinto de cero, ignora los espacios en blanco antes
 * de obtener el token. Almacena el token obtenido en el puntero a Token.
 */
void obtener_siguiente_token(char *input, int *posActual, int saltearEspacios, Token *token);

/**
 * Función para tokenizar listas.
 * Extrae el siguiente token de una lista en formato string a partir de la posición posActual.
 * Diseñada para listas numéricas con elementos separados por comas es decir de la forma a_1, a_2, ..., a_n sin
 * corchetes. El token puede ser de tipo TOKEN_NUM, TOKEN_COMA o TOKEN_EOF.
 */
void obtener_siguiente_token_lista(char *lista, int *posActual, Token *token);

#endif // __TOKEN_H__
