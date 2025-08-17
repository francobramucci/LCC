#include <stdio.h>
#include <stdlib.h>
/*
 * Encadenamiento: requiere memoria adicional.
 * Listas mezcladas: eliminación costosa. No afecta en este caso.
 * Linear probing: clustering.
 * Doble hash: mayor costo computacional al
 *
 * */

typedef struct _Entrada {
        char *clave;
        int valor;
        struct _Entrada *next;
} Entrada;

typedef struct {
        Entrada **tabla;
        int capacidad;
        int ocupados;
} TablaHash;

unsigned hash(char *key) {
    unsigned hashval;

    for (hashval = 0; *key != '\0'; key++) {
        hashval = *key + 31 * hashval;
    }

    return hashval;
}

void buscar(char *key, TablaHash *hashTable)

    void insertar(char *key, TablaHash *hashTable) {
    float factorDeCarga = (float)hashTable->ocupados / (float)hashTable->capacidad;
    if (factorDeCarga >)
        unsigned val = hash(key);
}
