#include "bheaps.h"

#define CANT 10000

struct _BHeap {
        void **arr;
        int capacidad;
        int ultimo;
        FuncionComparadora comp;
        FuncionCopiadora copy;
        FuncionDestructora destr;
};
static void *copiar_puntero_entero(void *i) {
    int *p = malloc(sizeof(int));
    *p = *(int *)i;
    return p;
}

static int comparar_puntero_entero(void *i1, void *i2) {
    return (*(int *)i1 - *(int *)i2);
}

static void destruir_puntero_entero(void *i) {
    free(i);
}

static void imprimir_puntero_entero(void *i) {
    printf("%d ", *(int *)i);
}

int main() {
    srand(time(NULL));
    BHeap heap = bheap_crear(8, comparar_puntero_entero, copiar_puntero_entero, destruir_puntero_entero);
    int numeros[] = {10, 20, 15, 25, 30, 16, 18, 19};
    for (int i = 0; i < 8; i++) {
        bheap_insertar(heap, numeros + i);
    }

    bheap_recorrer(heap, imprimir_puntero_entero);
    puts("");

    bheap_eliminar(heap, numeros + 4);
    bheap_recorrer(heap, imprimir_puntero_entero);
    puts("");

    void *arr[8];
    for (int i = 0; i < 8; i++) {
        arr[i] = numeros + i;
    }

    BHeap heapDesdeArr =
        bheap_crear_desde_arr(arr, 8, comparar_puntero_entero, copiar_puntero_entero, destruir_puntero_entero);
    bheap_recorrer(heapDesdeArr, imprimir_puntero_entero);
    puts("");

    void **arrayOrdenado =
        bheap_ordenar_array(arr, 8, comparar_puntero_entero, copiar_puntero_entero, destruir_puntero_entero);
    for (int i = 0; i < 8; i++) {
        imprimir_puntero_entero(arrayOrdenado[i]);
    }
    puts("");

    int numArray[CANT];
    void *numArrayPointers[CANT];
    for (int i = 0; i < CANT; i++) {
        numArray[i] = rand() % CANT;
        numArrayPointers[i] = numArray + i;
    }
    void **numArrayOrdenado = bheap_ordenar_array(numArrayPointers, CANT, comparar_puntero_entero,
                                                  copiar_puntero_entero, destruir_puntero_entero);
    for (int i = 0; i < CANT; i++) {
        imprimir_puntero_entero(numArrayOrdenado[i]);
    }
    puts("");
    return 0;
}
