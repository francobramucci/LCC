#ifndef __PARSER_H__
#define __PARSER_H__
#include "search.h"
#include "token.h"

// Codigos de error
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

/*
 * Parsea una expresión completa desde el input.
 * Según el contenido, delega el análisis a las funciones correspondientes:
 *   - Definición de lista
 *   - Definición de función
 *   - Aplicación de función
 *   - Búsqueda sobre pares de listas
 * Los resultados se almacenan en las tablas hash de listas o funciones, según corresponda.
 * En caso de error, imprime el mensaje correspondiente.
 */
void parsear_expresion(char *input, THash *tablaHashListas, THash *tablaHashFunciones);

#endif // __PARSER_H__
