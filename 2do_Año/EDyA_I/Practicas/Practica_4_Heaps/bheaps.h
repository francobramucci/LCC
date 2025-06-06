#ifndef __BHEAPS_H_
#define __BHEAPS_H_

#include <stdio.h>
#include <stdlib.h>

typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void *(*FuncionCopiadora)(void *dato);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _BHeap *BHeap;

#endif /* __BHEAPS_H_ */
