#ifndef __DLIST_H__
#define __DLIST_H__

typedef struct _DNodo {
        int dato;
        struct _DNodo *sig;
        struct _DNodo *ant;
} DNodo;

typedef struct {
        DNodo *primero;
        DNodo *ultimo;
} DList;

/**
 * Crea una lista doblemente enlazada vacía y devuelve un puntero a ella.
 */
DList *dlist_crear();

/**
 * Inserta un elemento al inicio de la lista. Precondición: 'lista' no es NULL.
 */
void dlist_agregar_inicio(DList *lista, int dato);

/**
 * Inserta un elemento al final de la lista. Precondición: 'lista' no es NULL.
 */
void dlist_agregar_final(DList *lista, int dato);

/**
 * Elimina el primer elemento de la lista.
 */
void dlist_eliminar_inicio(DList *lista);

/**
 * Elimina el último elemento de la lista.
 */
void dlist_eliminar_final(DList *lista);

/**
 * Libera toda la memoria asociada a la lista.
 */
void dlist_destruir(DList *lista);

/**
 * Devuelve una copia física de la lista.
 */
DList *dlist_copiar(DList *lista);

/**
 * Compara dos listas y devuelve 1 si son iguales elemento a elemento, 0 en caso contrario.
 */
int dlist_igual(DList *l1, DList *l2);

/**
 * Imprime el contenido de la lista en la salida estándar.
 */
void dlist_imprimir(DList *lista);

/**
 * Devuelve si la dlist es vacía o no.
 */
int dlist_es_vacia(DList *lista);

/*
 * Devuelve 1 si la lista tiene longitud mayor a 1, 0 en caso contrario.
 */
int dlist_largo_mayor_a_uno(DList *lista);

/**
 * Devuelve 1 si los extremos de la lista son iguales, 0 si no.
 */
int dlist_comparar_extremos(DList *lista);

/**
 * Convierte la lista 'lista' en una copia de 'listaParametro', reutilizando nodos cuando sea posible.
 * - Si 'lista' tiene más nodos que 'listaParametro', se eliminan los nodos sobrantes.
 * - Si 'lista' tiene menos nodos, se crean nodos adicionales.
 * - Se copian directamente los valores elemento a elemento.
 *
 * Esta función minimiza la cantidad de mallocs y frees realizados, lo que la hace útil cuando se requiere
 * transformar una lista existente al estado de otra sin recrearla desde cero.
 */
void dlist_convertir(DList *lista, DList *listaParametro);

#endif /* __DLIST_H__ */
