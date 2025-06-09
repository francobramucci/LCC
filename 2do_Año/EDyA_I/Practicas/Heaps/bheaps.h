#ifndef __BHEAPS_H_
#define __BHEAPS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void *(*FuncionCopiadora)(void *dato);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _BHeap *BHeap;

void swap(void **dato1, void **dato2);

BHeap bheap_crear(int capacidad, FuncionComparadora comp, FuncionCopiadora copy, FuncionDestructora destr);

void bheap_destruir(BHeap heap);

int bheap_es_vacio(BHeap heap);

void bheap_recorrer(BHeap heap, FuncionVisitante visit);

void bheap_flotar_recursivo(BHeap heap, int posNodoAFlotar);

void bheap_flotar(BHeap heap, int posNodoAFlotar);

void bheap_insertar(BHeap heap, void *dato);

void bheap_hundir(BHeap heap, int posNodoAHundir);

void bheap_eliminar(BHeap heap, void *dato);

BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionComparadora comp, FuncionCopiadora copy,
                            FuncionDestructora destr);
void **bheap_ordenar_array(void **arr, int largo, FuncionComparadora comp, FuncionCopiadora copy,
                           FuncionDestructora destr);
#endif /* __BHEAPS_H_ */
