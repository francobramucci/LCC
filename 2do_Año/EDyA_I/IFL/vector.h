#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>

typedef void *(*FuncionCopiadora)(void *);
typedef void (*FuncionDestructora)(void *);

typedef struct {
        void **arr;
        int ultimo;
        int capacidad;
        FuncionCopiadora copiar;
        FuncionDestructora destruir;
} Vector;

Vector *vector_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir);

void vector_insertar(Vector *vec, void *dato);

void vector_redimensionar(Vector *vec);

void vector_destruir(Vector *vec);

void vector_eliminar_ultimo(Vector *vec);

int vector_es_vacio(Vector *vec);

#endif // !__VECTOR_H__
