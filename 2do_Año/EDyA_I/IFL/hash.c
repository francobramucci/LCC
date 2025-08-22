#include "hash.h"
/*
 * Encadenamiento: requiere memoria adicional.
 * Listas mezcladas: eliminación costosa. No afecta en este caso.
 * Linear probing: clustering.
 * Doble hash: mayor costo computacional al
 *
 * */
int es_primo(int n) {
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

int primo_mas_cercano(int n) {
    int p = 0;

    for (int i = 0; p == 0; i++) {
        if (es_primo(n - i))
            p = n - i;
        else if (es_primo(n + i))
            p = n + i;
    }

    return p;
}

unsigned hash(char *key, int largoTabla) {
    unsigned hashval;

    for (hashval = 0; *key != '\0'; key++) {
        hashval = *key + 67 * hashval;
    }

    return hashval % largoTabla;
}

TablaHash *crear_tabla_hash(int capacidad) {
    TablaHash *tablaHash = malloc(sizeof(TablaHash));
    tablaHash->capacidad = capacidad;
    tablaHash->tamRegionDirecciones = primo_mas_cercano(ceil(0.86 * (float)capacidad));
    tablaHash->tabla = calloc(capacidad, sizeof(Entrada *));
    tablaHash->indiceRegionColisiones = capacidad - 1;

    return tablaHash;
}

void *buscar(char *key, TablaHash *hashTable) {
    Entrada **tabla = hashTable->tabla;
    int index = hash(key, hashTable->tamRegionDirecciones);
    if (tabla[index] == NULL)
        return NULL;
    while (index != -1 && strcmp(tabla[index]->key, key)) {
        index = tabla[index]->sig;
    }
    return index == -1 ? NULL : tabla[index]->valor;
}

Entrada *crear_entrada(char *key, void *valor) {
    Entrada *entrada = malloc(sizeof(Entrada));
    entrada->key = key;
    entrada->valor = valor;
    entrada->sig = -1;

    return entrada;
}

void insertar(char *key, void *value, TablaHash *hashTable) {
    Entrada **tabla = hashTable->tabla;
    int index = hash(key, hashTable->tamRegionDirecciones);
    int indiceAnterior;

    if (tabla[index] == NULL) {
        tabla[index] = crear_entrada(key, value);
        return;
    }

    while (index != -1 && strcmp(tabla[index]->key, key)) {
        indiceAnterior = index;
        index = tabla[index]->sig;
    }

    if (index == -1) {
        int indiceRegionColisiones = hashTable->indiceRegionColisiones;
        while (indiceRegionColisiones >= 0 && tabla[indiceRegionColisiones] != NULL)
            indiceRegionColisiones--;
        hashTable->indiceRegionColisiones = indiceRegionColisiones;
        if (indiceRegionColisiones == -1) { // Overflow
            rehash(hashTable);
            insertar(key, value, hashTable);
            return;
        }
        tabla[indiceAnterior]->sig = indiceRegionColisiones;
        tabla[indiceRegionColisiones] = crear_entrada(key, value);
    }
}

void rehash(TablaHash *hashTable) {
    TablaHash tablaVieja = *hashTable;
    hashTable->capacidad = hashTable->capacidad * 2;
    hashTable->indiceRegionColisiones = hashTable->capacidad - 1;
    hashTable->tabla = calloc(hashTable->capacidad, sizeof(Entrada *));
    hashTable->tamRegionDirecciones = primo_mas_cercano(ceil(0.86 * (float)hashTable->capacidad));

    for (int i = 0; i < tablaVieja.capacidad; i++) {
        insertar(tablaVieja.tabla[i]->key, tablaVieja.tabla[i]->valor, hashTable);
    }
    free(tablaVieja.tabla);
}

void imprimir_tabla_hash(TablaHash *tabla) {
    printf("%-10s | %-15s | %s\n", "Posicion", "Valor", "Siguiente");
    printf("-------------------------------------------\n");
    for (int i = 0; i < tabla->capacidad; i++) {
        char *valor = tabla->tabla[i] == NULL ? "NULL" : tabla->tabla[i]->valor;
        int sig = tabla->tabla[i] == NULL ? -1 : tabla->tabla[i]->sig;
        printf("%-10d | %-15s | %d\n", i, valor, sig);
    }
}

int main() {
    srand(1);
    TablaHash *hTable = crear_tabla_hash(1217);
    char stringArray[1200][100];
    for (int i = 0; i < 1200; i++) {
        sprintf(stringArray[i], "[%d, %d, %d, %d, %d, %d]", rand() % 100, rand() % 100, rand() % 100, rand() % 100,
                rand() % 100, rand() % 100);
        insertar(stringArray[i], stringArray[i], hTable);
    }

    imprimir_tabla_hash(hTable);
    char *a = buscar("[49, 18, 12, 34, 84, 30]", hTable);
    printf("\n%s", a);
    return 0;
}
