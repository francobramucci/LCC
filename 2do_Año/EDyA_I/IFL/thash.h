#ifndef __THASH_H__
#define __THASH_H__
#include <stdlib.h>

typedef void (*FuncionDestructora)(void *);

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

THash *thash_crear(int capacidad, FuncionDestructora destr);

void *thash_buscar(char *key, THash *hashTable);

void thash_insertar(char *key, void *value, THash *hashTable);

void thash_destruir(THash *hashTable);

#endif // !__THASH_H__
