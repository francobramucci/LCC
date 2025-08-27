#include "hash.h"
/*
 * Encadenamiento: requiere memoria adicional.
 * Listas mezcladas: eliminación costosa. No afecta en este caso.
 * Linear probing: clustering.
 * Doble hash: mayor costo computacional al
 *
 * */

unsigned thash_hash(char *key, int largoTabla) {
    unsigned hashval;

    for (hashval = 0; *key != '\0'; key++) {
        hashval = *key + 67 * hashval;
    }

    return hashval % largoTabla;
}

THash *thash_crear(int capacidad, FuncionDestructora destr) {
    THash *tablaHash = malloc(sizeof(THash));
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

Entrada *entrada_crear(char *key, void *valor) {
    Entrada *entrada = malloc(sizeof(Entrada));
    entrada->key = key;
    entrada->valor = valor;
    entrada->sig = -1;

    return entrada;
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

void thash_rehash(THash *tablaHash) {
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

// void imprimir_tabla_hash(THash *tabla) {
//     printf("%-10s | %-15s | %s\n", "Posicion", "Valor", "Siguiente");
//     printf("-------------------------------------------\n");
//     for (int i = 0; i < tabla->capacidad; i++) {
//         char *valor = tabla->tabla[i] == NULL ? "NULL" : tabla->tabla[i]->key;
//         int sig = tabla->tabla[i] == NULL ? -1 : tabla->tabla[i]->sig;
//         printf("%-10d | %-15s | %d\n", i, valor, sig);
//     }
// }

// int main() {
//     srand(1);
//     THash *hTable = crear_tabla_hash(1217);
//     char stringArray[1200][100];
//     for (int i = 0; i < 1200; i++) {
//         sprintf(stringArray[i], "[%d, %d, %d, %d, %d, %d]", rand() % 100, rand() % 100, rand() % 100, rand() % 100,
//                 rand() % 100, rand() % 100);
//         insertar(stringArray[i], stringArray[i], hTable);
//     }
//
//     imprimir_tabla_hash(hTable);
//     char *a = buscar("[49, 18, 12, 34, 84, 30]", hTable);
//     printf("\n%s", a);
//     return 0;
// }
