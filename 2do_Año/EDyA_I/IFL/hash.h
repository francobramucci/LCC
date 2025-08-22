#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// TO DO: hacer tabla hash generalizada

typedef struct _Entrada {
        char *key;
        char *valor;
        int sig;
} Entrada;

typedef struct {
        Entrada **tabla;
        int capacidad;
        int tamRegionDirecciones;
        int indiceRegionColisiones;
} TablaHash;

int es_primo(int n);

int primo_mas_cercano(int n);

unsigned hash(char *key, int largoTabla);

TablaHash *crear_tabla_hash(int capacidad);

char *buscar(char *key, TablaHash *hashTable);

Entrada *crear_entrada(char *key, char *valor);

void insertar(char *key, char *value, TablaHash *hashTable);

void rehash(TablaHash *hashTable);

void imprimir_tabla_hash(TablaHash *tabla);
