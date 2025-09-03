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

// Crea una lista doblemente enlazada
DList *dlist_crear();

// Agrega un elemento al inicio de la lista
void dlist_agregar_inicio(DList *lista, int dato);

// Agrega un elemento al final de la lista
void dlist_agregar_final(DList *lista, int dato);

// Elimina el primer elemento de la lista
void dlist_eliminar_inicio(DList *lista);

// Elimina el ultimo elemento de la lista
void dlist_eliminar_final(DList *lista);

// Destruye la lista
void dlist_destruir(DList *lista);

// Dada una lista, retorna una copia de la misma
DList *dlist_copiar(DList *lista);

// Dadas dos listas, devuelve 1 si son iguales y 0 si no
int dlist_igual(DList *l1, DList *l2);

// Dada una lista, la imprime
void dlist_imprimir(DList *lista);

// Dada una lista, retorna 1 si la lista tiene largo mayor a uno y 0 sino
int dlist_largo_mayor_a_uno(DList *lista);

/* Dada una lista l cualquiera y una listaParametro se convierte l a listaParametro.
 * Es decir, se copia el valor de cada uno de los nodos de listaParametro a cada nodo de l. Si l tiene mas nodos que
 * listaParametro entonces se eliminan. Si l tiene menos nodos entonces se agregan. Esta funcion logra copiar una lista
 * reutilizando nodos ya definidos. De esta forma se reducen la cantidad de mallocs y frees realizados. Util cuando se
 * aplica una operacion sobre una lista y se quiere volver al estado anterior.
 */
void dlist_transformar_int(DList *lista, DList *listaParametro);

#endif /* __DLIST_H__ */
