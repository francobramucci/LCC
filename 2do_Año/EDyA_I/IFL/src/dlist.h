#ifndef __DLIST_H__
#define __DLIST_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void* dato1, void* extra);

typedef struct _DNodo {
        void *dato;
        struct _DNodo *sig;
        struct _DNodo *ant;
} DNodo;

typedef struct {
        DNodo *primero;
        DNodo *ultimo;
        FuncionCopiadora copiar;
        FuncionDestructora destruir;
} DList;

/**
 * Crea una lista doblemente enlazada vacía y devuelve un puntero a ella.
 */
DList *dlist_crear(FuncionCopiadora copiar, FuncionDestructora destruir);

/**
 * Inserta un elemento al inicio de la lista.
 */
void dlist_agregar_inicio(DList *lista, void *dato);

/**
 * Inserta un elemento al final de la lista.
 */
void dlist_agregar_final(DList *lista, void *dato);

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
int dlist_igual(DList *l1, DList *l2, FuncionComparadora comparar);

/**
 * Recorre la lista y aplica una funcion visitante con un parametro extra.
 */
void dlist_recorrer(DList *lista, FuncionVisitanteExtra visitar, void* extra);

/**
 * Devuelve si la dlist es vacía o no.
 */
int dlist_es_vacia(DList *lista);

/**
 * Devuelve 1 si la lista tiene longitud mayor a 1, 0 en caso contrario.
 */
int dlist_largo_mayor_a_uno(DList *lista);

/**
 * Devuelve 1 si los extremos de la lista son iguales, 0 si no.
 */
int dlist_comparar_extremos(DList *lista, FuncionComparadora);

#endif // __DLIST_H__
