#include "bheaps.h"

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
    for (int i = 1; i <= heap->ultimo; i++) {
        visit(heap->arr[i]);
    }
}

void bheap_flotar(BHeap heap, int posNodoAFlotar) {
    if (posNodoAFlotar > 0 && heap->comp(heap->arr[posNodoAFlotar], heap->arr[PADRE(posNodoAFlotar)]) > 0) {
        swap(&heap->arr[posNodoAFlotar], &heap->arr[PADRE(posNodoAFlotar)]);
        bheap_flotar(heap, PADRE(posNodoAFlotar));
    }
}

void bheap_flotar(BHeap heap, int posNodoAFlotar) {
}

void bheap_insertar(BHeap heap, void *dato) {
    int ultimo = heap->ultimo;
    int capacidad = heap->capacidad;
    if (capacidad == ultimo + 1) {
        heap->arr = realloc(heap->arr, capacidad * 2);
        heap->capacidad = capacidad * 2;
    }
    ultimo++;
    heap->arr[ultimo] = heap->copy(dato);
    bheap_flotar(heap, ultimo);
}

void bheap_hundir(BHeap heap, int posNodoAHundir) {
    int ultimo = heap->ultimo;
    int posHijoDerecho = HIJO_DERECHO(posNodoAHundir);
    int posHijoIzquierdo = HIJO_IZQUIERDO(posNodoAHundir);
    while (posHijoIzquierdo <= ultimo && posHijoDerecho <= ultimo) {
        int posNodoASwapear =
            heap->comp(heap->arr[posHijoDerecho], heap->arr[posHijoIzquierdo]) > 0 ? posHijoDerecho : posHijoIzquierdo;
        swap(&heap->arr[posNodoAHundir], &heap->arr[posNodoASwapear]);

        posNodoAHundir = posNodoASwapear;
        posHijoDerecho = HIJO_DERECHO(posNodoAHundir);
        posHijoIzquierdo = HIJO_IZQUIERDO(posNodoAHundir);
    }
    if (posHijoIzquierdo <= ultimo && heap->comp(heap->arr[posHijoIzquierdo], heap->arr[posNodoAHundir]) > 0)
        swap(heap->arr[posHijoIzquierdo], heap->arr[posNodoAHundir]);
}

void bheap_eliminar(BHeap heap, void *dato) {
    int i = 0;
    int ultimo = heap->ultimo;
    while (i <= ultimo && heap->arr[i] != dato) i++;
    swap(&heap->arr[i], &heap->arr[ultimo]);
    heap->destr(heap->arr[ultimo]);
    heap->ultimo--;
    bheap_hundir(heap, i);
}
