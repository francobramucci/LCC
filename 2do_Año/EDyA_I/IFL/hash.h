#include "dlist.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// TO DO: hacer tabla hash generalizada
typedef void (*FuncionDestructora)(void *);

typedef struct {
        char **def;
        int largo;
} FLista;

typedef struct _Entrada {
        char *key;
        void *valor;
        int sig;
} Entrada;

typedef struct {
        Entrada **tabla;
        int capacidad;
        int tamRegionDirecciones;
        int indiceRegionColisiones;
        FuncionDestructora destr;
} THash;

int es_primo(int n);

int primo_mas_cercano(int n);

unsigned thash_hash(char *key, int largoTabla);

THash *thash_crear(int capacidad, FuncionDestructora destr);

void *thash_buscar(char *key, THash *hashTable);

Entrada *entrada_crear(char *key, void *valor);

void thash_insertar(char *key, void *value, THash *hashTable);

void thash_rehash(THash *hashTable);

void thash_destruir(THash *hashTable);

void imprimir_tabla_hash(THash *tabla);

void aplicacion_singular(char *funcion, DList *lista, THash *tablaHashFunciones);

void apply(FLista *funcion, DList *lista, THash *tablaHashFunciones);

void parsear_apply(char *input, int *posActual, THash *tablaHashListas, THash *tablaHashFunciones);
