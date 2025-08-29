#include "search.h"

// Generalizar lista
// Implementar colas
// Funcion que agrega primitivas y funciones definidas
// Crear funcion de igualdad de DList's

void search_primera_lista(DList *lista, THash *tablaFunciones) {
    Queue q;
    q.enqueue(thash_buscar("Oi", tablaFunciones));
    q.enqueue(thash_buscar("Od", tablaFunciones));
    q.enqueue(thash_buscar("Si", tablaFunciones));
    q.enqueue(thash_buscar("Sd", tablaFunciones));
    q.enqueue(thash_buscar("Di", tablaFunciones));
    q.enqueue(thash_buscar("Dd", tablaFunciones));

    int profundidad = 7;

    while (profundidad) {
        funcion = q.dequeue;
        DList *copia = dlist_copiar(lista);
        apply(funcion, copia, tablaFunciones);
    }
}
