#include "bheaps.h"
#include <stdlib.h>

#define HIJO_IZQUIERDO(i) (2 * i + 1)
#define HIJO_DERECHO(i) (2 * i + 2)
#define PADRE(i) ((i - 1) / 2)
struct _BHeap {
        void **arr;
        int capacidad;
        int ultimo;
        FuncionComparadora comp;
        FuncionCopiadora copy;
        FuncionDestructora destr;
};

void swap(void **dato1, void **dato2) {
    void *aux = *dato1;
    *dato1 = *dato2;
    *dato2 = aux;
}

BHeap bheap_crear(int capacidad, FuncionComparadora comp, FuncionCopiadora copy, FuncionDestructora destr) {
    struct _BHeap *heap = malloc(sizeof(struct _BHeap));
    heap->arr = malloc(sizeof(void *) * capacidad);
    heap->capacidad = capacidad;
    heap->ultimo = -1;
    heap->comp = comp;
    heap->copy = copy;
    heap->destr = destr;

    return heap;
}

void bheap_destruir(BHeap heap) {
    for (int i = 0; i <= heap->ultimo; i++) {
        heap->destr(heap->arr[i]);
    }
    free(heap->arr);
    free(heap);
}

int bheap_es_vacio(BHeap heap) {
    return heap->ultimo == -1;
}

void bheap_recorrer(BHeap heap, FuncionVisitante visit) {
    for (int i = 0; i <= heap->ultimo; i++) {
        visit(heap->arr[i]);
    }
}

void bheap_flotar_recursivo(BHeap heap, int posNodoAFlotar) {
    if (posNodoAFlotar > 0 && heap->comp(heap->arr[posNodoAFlotar], heap->arr[PADRE(posNodoAFlotar)]) > 0) {
        bheap_flotar_recursivo(heap, PADRE(posNodoAFlotar));
    }
}

void bheap_flotar(BHeap heap, int posNodoAFlotar) {
    while (posNodoAFlotar > 0 && heap->comp(heap->arr[posNodoAFlotar], heap->arr[PADRE(posNodoAFlotar)]) > 0) {
        swap(&heap->arr[posNodoAFlotar], &heap->arr[PADRE(posNodoAFlotar)]);
        posNodoAFlotar = PADRE(posNodoAFlotar);
    }
}

void bheap_insertar(BHeap heap, void *dato) {
    int ultimo = heap->ultimo;
    int capacidad = heap->capacidad;
    if (ultimo == capacidad - 1) {
        heap->arr = realloc(heap->arr, capacidad * 2);
        heap->capacidad = capacidad * 2;
    }
    ultimo++;
    heap->ultimo = ultimo;
    heap->arr[ultimo] = heap->copy(dato);
    bheap_flotar(heap, ultimo);
}

void bheap_hundir(BHeap heap, int posNodoAHundir) {
    int ultimo = heap->ultimo;
    while (HIJO_IZQUIERDO(posNodoAHundir) <= ultimo) {
        int posHijoIzquierdo = HIJO_IZQUIERDO(posNodoAHundir);
        int posHijoDerecho = HIJO_DERECHO(posNodoAHundir);

        int posNodoASwapear = posHijoIzquierdo;
        if (posHijoDerecho <= ultimo && heap->comp(heap->arr[posHijoDerecho], heap->arr[posHijoIzquierdo]) > 0)
            posNodoASwapear = posHijoDerecho;

        if (heap->comp(heap->arr[posNodoASwapear], heap->arr[posNodoAHundir]) > 0)
            swap(&heap->arr[posNodoASwapear], &heap->arr[posNodoAHundir]);
        posNodoAHundir = posNodoASwapear;
    }
}

void bheap_eliminar(BHeap heap, void *dato) {
    int i = 0;
    int ultimo = heap->ultimo;
    while (i <= ultimo && heap->comp(heap->arr[i], dato) != 0) i++;
    if (i <= ultimo) {
        swap(&heap->arr[i], &heap->arr[ultimo]);
        heap->destr(heap->arr[ultimo]);
        heap->ultimo--;
        bheap_hundir(heap, i);
    }
}

// int particionar(void **arr, int inicio, int final, void *pivot, FuncionComparadora comp) {
//     int j = 0;
//     int i = 0;
//     while (i <= final) {
//         if (comp(arr[i], pivot) > 0) {
//             if (i != j)
//                 swap(&arr[i], &arr[j]);
//             j++;
//         }
//         i++;
//     }
//     return j;
// }
//
// void quicksort(void **arr, int inicio, int final, FuncionComparadora comp) {
//     if (inicio >= final)
//         return;
//     void *pivot = arr[final];
//     int posPivot = particionar(arr, inicio, final - 1, pivot, comp);
//     swap(&arr[posPivot], &arr[final]);
//     quicksort(arr, inicio, posPivot - 1, comp);
//     quicksort(arr, posPivot + 1, final, comp);
// }

// BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copy, FuncionComparadora comp,
//                             FuncionDestructora destr) {
//     BHeap heap = bheap_crear(largo, comp, copy, destr);
//     quicksort(arr, 0, largo - 1, comp);
//
//     int i = 0;
//     while (i < largo) {
//         heap->arr[i] = copy(arr[i]);
//     }
//     return heap;
// }

BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionComparadora comp, FuncionCopiadora copy,
                            FuncionDestructora destr) {
    BHeap heap = bheap_crear(largo, comp, copy, destr);
    heap->ultimo = largo - 1;

    int i = 0;
    while (i < largo) {
        heap->arr[i] = copy(arr[i]);
        bheap_flotar(heap, i);
        i++;
    }

    return heap;
}

void **bheap_ordenar_array(void **arr, int largo, FuncionComparadora comp, FuncionCopiadora copy,
                           FuncionDestructora destr) {
    BHeap heap = bheap_crear_desde_arr(arr, largo, comp, copy, destr);
    while (heap->ultimo) {
        swap(&heap->arr[0], &heap->arr[heap->ultimo]);
        heap->ultimo--;
        bheap_hundir(heap, 0);
    }
    void **arrayOrdenado = heap->arr;
    free(heap);
    return arrayOrdenado;
}
