
#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Devuelve una copia del string recibido.
 */
char *copiar_string(char *str);

/**
 * Devuelve una copia del entero recibido.
 */
int *copiar_entero(int *i);

/**
 * Libera la memoria de un entero.
 */
void destruir_entero(int *i);

/**
 * Compara dos enteros.
 * Retorna 0 si son iguales, negativo si i < j, positivo si i > j.
 */
int comparar_enteros(int *i, int *j);

/**
 * Retorna el mismo puntero recibido.
 */
void *retornar_puntero(void *a);

/**
 * Libera la memoria de un puntero genérico.
 */
void liberar_puntero(void *a);

/**
 * Función vacía que no realiza ninguna operación.
 */
void funcion_vacia(void *a);

#endif // __UTILS_H__
