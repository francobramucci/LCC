#include "thash.h"
#include <assert.h>
#include <math.h>
#include <string.h>

static unsigned thash_hash(char *key, int largoTabla);
static void thash_rehash(THash *tablaHash);
static Entrada *entrada_crear(char *key, void *valor);
static int es_primo(int n);
static int primo_mas_cercano(int n);

/*
 * Encadenamiento: requiere memoria adicional.
 * Listas mezcladas: eliminación costosa. No afecta en este caso.
 * Linear probing: clustering.
 * Doble hash: mayor costo computacional al
 *
 * */

THash *thash_crear(int capacidad, FuncionDestructora destr) {
    THash *tablaHash = malloc(sizeof(THash));
    assert(tablaHash);
    tablaHash->capacidad = capacidad;
    tablaHash->tamRegionDirecciones = primo_mas_cercano(ceil(0.86 * (float)capacidad));
    tablaHash->tabla = calloc(capacidad, sizeof(Entrada *));
    tablaHash->indiceRegionColisiones = capacidad - 1;
    tablaHash->destr = destr;

    return tablaHash;
}

void *thash_buscar(char *key, THash *tablaHash) {
    Entrada **tabla = tablaHash->tabla;
    int index = thash_hash(key, tablaHash->tamRegionDirecciones);
    if (tabla[index] == NULL)
        return NULL;
    while (index != -1 && strcmp(tabla[index]->key, key)) {
        index = tabla[index]->sig;
    }
    return index == -1 ? NULL : tabla[index]->valor;
}

void thash_insertar(char *key, void *value, THash *tablaHash) {
    Entrada **tabla = tablaHash->tabla;
    int index = thash_hash(key, tablaHash->tamRegionDirecciones);
    int indiceAnterior;

    if (tabla[index] == NULL) {
        tabla[index] = entrada_crear(key, value);
        return;
    }

    while (index != -1 && strcmp(tabla[index]->key, key)) {
        indiceAnterior = index;
        index = tabla[index]->sig;
    }

    if (index == -1) {
        int indiceRegionColisiones = tablaHash->indiceRegionColisiones;
        while (indiceRegionColisiones >= 0 && tabla[indiceRegionColisiones] != NULL)
            indiceRegionColisiones--;
        tablaHash->indiceRegionColisiones = indiceRegionColisiones;
        if (indiceRegionColisiones == -1) { // Overflow
            thash_rehash(tablaHash);
            thash_insertar(key, value, tablaHash);
            return;
        }
        tabla[indiceAnterior]->sig = indiceRegionColisiones;
        tabla[indiceRegionColisiones] = entrada_crear(key, value);
    }
}

void thash_destruir(THash *tablaHash) {
    FuncionDestructora destr = tablaHash->destr;
    Entrada **tabla = tablaHash->tabla;
    for (int i = 0; i < tablaHash->capacidad; i++) {
        if (tabla[i] != NULL) {
            destr(tabla[i]->valor);
            free(tabla[i]->key);
            free(tabla[i]);
        }
    }
    free(tabla);
    free(tablaHash);
}

static unsigned thash_hash(char *key, int largoTabla) {
    unsigned hashval;

    for (hashval = 0; *key != '\0'; key++) {
        hashval = *key + 67 * hashval;
    }

    return hashval % largoTabla;
}

static void thash_rehash(THash *tablaHash) {
    THash tablaVieja = *tablaHash;
    tablaHash->capacidad = tablaHash->capacidad * 2;
    tablaHash->indiceRegionColisiones = tablaHash->capacidad - 1;
    tablaHash->tabla = calloc(tablaHash->capacidad, sizeof(Entrada *));
    tablaHash->tamRegionDirecciones = primo_mas_cercano(ceil(0.86 * (float)tablaHash->capacidad));

    for (int i = 0; i < tablaVieja.capacidad; i++) {
        if (tablaVieja.tabla[i] != NULL) {
            thash_insertar(tablaVieja.tabla[i]->key, tablaVieja.tabla[i]->valor, tablaHash);
            free(tablaVieja.tabla[i]);
        }
    }
    free(tablaVieja.tabla);
}

static Entrada *entrada_crear(char *key, void *valor) {
    Entrada *entrada = malloc(sizeof(Entrada));
    assert(entrada);
    entrada->key = key;
    entrada->valor = valor;
    entrada->sig = -1;

    return entrada;
}

static int es_primo(int n) {
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    int esPrimo = 1;

    for (int i = 5; i * i <= n && esPrimo; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            esPrimo = 0;
    }

    return esPrimo;
}

static int primo_mas_cercano(int n) {
    int p = 0;

    for (int i = 0; p == 0; i++) {
        if (es_primo(n - i))
            p = n - i;
        else if (es_primo(n + i))
            p = n + i;
    }

    return p;
}
